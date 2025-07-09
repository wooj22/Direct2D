#pragma once
#include "../Direct2D_EngineLib/GameObject.h"
#include "../Direct2D_EngineLib/Transform.h"
#include "../Direct2D_EngineLib/SpriteRenderer.h"

class SkyBackground	: public GameObject
{
private:
    Transform* transform;
    SpriteRenderer* spriteRenderer;

public:
    // game object cycle
    SkyBackground() 
    {
        transform = AddComponent<Transform>();
        spriteRenderer = AddComponent<SpriteRenderer>();
    }
    ~SkyBackground() override {}

    void Awake() override             // ������Ʈ�� ������ ��
    {
        auto darkSky = ResourceManager::Get().CreateTexture2D("../Resource/DarkSky.png");
        spriteRenderer->sprite = ResourceManager::Get().CreateSprite(darkSky, "DarkSky");
        transform->Scaleing(1.3, 1.3);
    }
    void SceneStartInit() override {}    // Scene�� Start
    void Update()  override {}           // Scene�� Update
    void Destroyed() override {}         // Scene�� Exit, GameObject Delete
};

