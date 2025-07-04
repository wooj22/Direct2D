#include "AnimationClip.h"


/// LoadSpritesFromJson
/// �Ѱܹ��� Texture�� �������� json data�� ���� sprite���� �����Ѵ�.
void AnimationClip::LoadSpritesFromJson(shared_ptr<Texture2D> texture, const string& jsonPath)
{
    nlohmann::json j = nlohmann::json::parse(ifstream(jsonPath));

    auto sprites = j["sprites"];
    for (const auto& spriteJson : sprites)
    {
        string name = spriteJson["name"].get<string>();
        float x = spriteJson["x"].get<float>();
        float y = spriteJson["y"].get<float>();
        float w = spriteJson["width"].get<float>();
        float h = spriteJson["height"].get<float>();
        float pivotX = spriteJson["pivotX"].get<float>();
        float pivotY = spriteJson["pivotY"].get<float>();

        D2D1_RECT_F rect = { x, y, x + w, y + h };
        D2D1_POINT_2F pivot = { pivotX, pivotY };

        // Texture2D �Ϻ� ������ ������ Sprite ����
        ResourceManager::Get().CreateSprite(texture, name, rect, pivot);
    }
}

/// LoadAnimationClipFromJson
/// 
void AnimationClip::LoadAnimationClipFromJson(shared_ptr<Texture2D> texture, const string& jsonPath)
{
    nlohmann::json j = nlohmann::json::parse(ifstream(jsonPath));

    name = j["clipName"].get<std::string>();
    loop = j["loop"].get<bool>();
    duration = j["duration"].get<float>();

    const auto& jsonFrames = j["frames"];
    for (const auto& frameJson : jsonFrames)
    {
        string spriteName = frameJson["sprite"].get<string>();
        float time = frameJson["time"].get<float>();

        // ������ �̹� sprite���� ��������Ƿ� shared_prt�� �ް� ��
        auto sprite = ResourceManager::Get().CreateSprite(texture, spriteName);

        // animation frame create
        AnimationFrame frame;
        frame.sprite = sprite;
        frame.time = time;
        frames.push_back(frame);
    }
}