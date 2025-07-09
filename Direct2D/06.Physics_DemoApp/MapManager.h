#pragma once
#include "../Direct2D_EngineLib/GameObject.h"
#include "../Direct2D_EngineLib/Transform.h"
#include "../Direct2D_EngineLib/Time.h"
#include "SkyBackground.h"

class MapManager : public GameObject
{
private:
    Transform* transform;
    float mapslidSpeed = 5.0f;
public:
	SkyBackground* map1;
	SkyBackground* map2;
	SkyBackground* map3;

public:
    // game object cycle
    MapManager() 
    {
        transform = AddComponent<Transform>();
    }
    ~MapManager() override {}

    void Awake() override {}              // ������Ʈ�� ������ ��

    void SceneStartInit() override       // Scene�� Start
    {
        map1->transform->SetParent(transform);
        map2->transform->SetParent(transform);
        map3->transform->SetParent(transform);

        map1->transform->SetPosition(-100, 0);
        map2->transform->SetPosition(1110, 0);
        map3->transform->SetPosition(2210, 0);
    }
    void Update()  override              // Scene�� Update
    {
        transform->Translate(-mapslidSpeed * Time::GetDeltaTime(), 0);
    }
    void Destroyed() override {}         // Scene�� Exit, GameObject Delete
};

