﻿#pragma once
#include <vector>
#include <typeinfo>
#include <iostream>
#include <windows.h> 
#include "Component.h"
#include "Object.h"

/* [GameObject]
* Component를 등록시킬 수 있는 오브젝트로,
* 게임 콘텐츠에 활용할 오브젝트는 이 클래스를 상속받아 컴포넌트를 조합하여 구현한다.
* 즉 GameObject는 Component들의 컨테이너 역할을 한다.
* 
* < GameObject Cycle >
*  : GameObject의 사이클은 기본적으로 사용하지 않아도 된다. (awake부터~)
*    보통 Script 컴포넌트를 활용하여 로직을 작성하며, 
     간단한 오브젝트 같은 경우에 Script 컴포넌트를 만들지 않고 빨리 작성할 수 있도록 냅둔 것이다.
*  1．　게임오브젝트 생성자() : 컴포넌트 생성. 초기화 로직
*  2．　게임오브젝트 Awake()           // 여기서부턴 보통 사용하지 않는다.
*  3．　게임오브젝트 SceneStart()　    // 초기 오브젝트만　해당 (Scene Start() 시점에 생성되어있는 오브젝트)
*  4．　게임오브젝트 Update()
*  5．　게임오브젝트 Destroyed()
* 
* < 콘텐츠 제작시 유의사항 >
* 1) '생성자()'에서 컴포넌트 생성하고 리소스 로드등 초기화를 한다.
* 2) 생성자에서 컴포넌트를 생성할 때 각 컴포넌트의 OnEnable()이 호출된다.
* 3) 만약 Sciprt 컴포넌트가 있다면 그냥 유니티랑 똑같이 생각하고 사용하면 된다. (Awake, Start 보장)
* 4) 오브젝트가 생성될 때 ComponentInit()에 이어 'Awake()'가 호출된다. 즉, this오브젝트의 컴포넌트 등록이 모두 마친 뒤 호출 되는것
* 5) Scene이 Start()될 때 'SceneStart()'가 호출된다. 
     이때는 씬의 모든 게임오브젝트들이 생성되어있는 시점이므로 Find, 부모관계 지정 등의 작업이 가능하다
     ⭐ 만약 Scene의 Update중간에 생성되는 게임오브젝트라면 SceneStart()가 호출되지 않으므로
        SceneStart()안에 코드를 작성하지 않아야 한다.
        중간에 생성되는 오브젝트는 다른 게임오브젝트들이 이미 생성된 시점이기 때문에
        생성자나 Awake()에 초기화 코드를 모두 작성하면 된다.
        그러니까 웬만큼 간단한 오브젝트가 아닌 이상 따로 Script 컴포넌트를 사용하라.
  6) Scene이 Update될 때 'Update()'가 매 프레임 호출된다.
  7) 게임오브젝트가 파괴되거나 씬이 종료될 때 Destroyed()가 호출된다.
*/

class Component;
class GameObject : public Object
{
private:
    std::vector<Component*> components;
    static std::vector<GameObject*> allGameObjects;
public:
    std::string name = "GameObject";

public:
    GameObject(const std::string& objName = "GameObject")
        : name(objName)
    {
        allGameObjects.push_back(this);
        OutputDebugStringA("GameObject()\n");
    }

    virtual ~GameObject()
    {
        // component delete
        for (Component* comp : components) {
            comp->OnDestroy();
            delete comp;
        }
        components.clear();

		// gameobject delete
        auto it = std::find(allGameObjects.begin(), allGameObjects.end(), this);
        if (it != allGameObjects.end())
            allGameObjects.erase(it);

        OutputDebugStringA("~GameObject()\n");
    }

public:
    /* GameObject Cycle */
    virtual void Awake() {};           // 오브젝트가 생성될 때, 생성자 이후
    virtual void SceneStart() {};      // Scene의 Start -> Update중 SceneStart() 호출 보장 x
    virtual void Update() {};          // Scene의 Update
    virtual void Destroyed() {};       // Scene의 Exit, GameObject Delete

public:
    // game object find  // 문제있어서 사용 x 이름도 아직 제어 없음
    static GameObject* Find(const std::string& targetName)
    {
        for (GameObject* obj : allGameObjects)
        {
            if (obj && obj->name == targetName)
                return obj;
        }
        return nullptr;
    }

public:
    // Component
    // TODO :: 스마트 포인터 구조로 바꾸기
    template<typename T, typename... Args>
    T* AddComponent(Args&&... args)
    {
        static_assert(std::is_base_of<Component, T>::value, "T must derive from Component");

        T* comp = new T(std::forward<Args>(args)...);
        comp->owner = this;
        components.push_back(comp);
        comp->OnEnable();
        return comp;
    }

    template<typename T>
    std::vector<T*> GetComponents() {
        std::vector<T*> result;
        for (Component* comp : components) {
            if (auto casted = dynamic_cast<T*>(comp))
                result.push_back(casted);
        }
        return result;
    }

    template<typename T>
    T* GetComponent() {
        for (Component* comp : components) {
            if (typeid(*comp) == typeid(T))
                return static_cast<T*>(comp);
        }
        return nullptr;
    }

    template<typename T>
    bool RemoveComponent(T* target) {

        for (auto it = components.begin(); it != components.end(); ++it) {
            if (*it == target)
            {
                (*it)->OnDestroy();
                delete* it;
                components.erase(it);
                return true;
            }
        }
        return false;
    }
};