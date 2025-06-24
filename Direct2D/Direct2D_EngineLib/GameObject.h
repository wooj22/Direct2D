#pragma once
#include <vector>
#include <typeinfo>
#include "Component.h"

/* [GameObject Ŭ����]
* Component�� ��Ͻ�ų �� �ִ� ������Ʈ��,
* ���� �������� Ȱ���� ������Ʈ�� �� Ŭ������ ��ӹ޾� ������Ʈ�� �����Ͽ� �����Ѵ�.
* ���� ������Ʈ�� Scene�� ��ϵǾ� Scene Life Cycle��� Cycle�� ȣ��ȴ�.
* SceneManager -> Scene -> GameObject(this)
*/

class Component;
class GameObject {
private:
    std::vector<Component*> components;

public:
    GameObject() {};
    virtual ~GameObject()
    {
        for (Component* comp : components) {
            comp->OnDestroy();
            delete comp;
        }
        components.clear();
    }

    // Cycle
    virtual void Awake() {};
    virtual void Start() {};
    virtual void Update() {};
    virtual void Destroy() {};

public:
    // Component
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