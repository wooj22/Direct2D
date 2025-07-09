#pragma once
#include "../Direct2D_EngineLib/GameObject.h"
#include "../Direct2D_EngineLib/Transform.h"
#include "../Direct2D_EngineLib/Time.h"
#include "SkyBackground.h"
#include "Cloud.h"

// gameobject cycle�� Ȱ���Ͽ�, script ������Ʈ�� ������� �ʰ� ������ ������Ʈ�� �ٷ� setting

class MapManager : public GameObject
{
private:
    Transform* transform;
    float mapslidSpeed = 5.0f;
public:
    // background
	SkyBackground* map1;
	SkyBackground* map2;
	SkyBackground* map3;

    // map object
    Cloud* cloud1;
    Cloud* cloud2;
    Cloud* cloud3;
    Cloud* cloud4;
    Cloud* cloud5;

public:
    // game object cycle
    MapManager() 
    {
        transform = AddComponent<Transform>();
    }
    ~MapManager() override {}

    // ������ ����
    void Awake() override         
    {

    }

    // Scene�� Start
    void SceneStart() override       
    {
        map1->transform->SetParent(transform);
        map2->transform->SetParent(transform);
        map3->transform->SetParent(transform);

        map1->transform->SetPosition(-100, 0);
        map2->transform->SetPosition(1110, 0);
        map3->transform->SetPosition(2210, 0);

        cloud1->transform->SetPosition(-50, -100);
        cloud2->transform->SetPosition(400, -70);
        cloud3->transform->SetPosition(800, 0);
        cloud4->transform->SetPosition(1200, 50);
        cloud5->transform->SetPosition(1600, 10);
    }

    // Scene�� Update
    void Update()  override             
    {
        transform->Translate(-mapslidSpeed * Time::GetDeltaTime(), 0);
    }

    // Scene�� Exit, GameObject Delete
    void Destroyed() override 
    {
        
    }         
};

