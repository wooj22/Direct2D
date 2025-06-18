#pragma once
#include <vector>
#include "Component.h"

class Component;
class GameObject {
private:
    std::vector<Component*> components;

public:
    ~GameObject()
    {
        for (Component* comp : components) {
            comp->OnDestroy();
            delete comp;
        }
        components.clear();
    }

    // Class T�� �����ϴ� �Լ� , ���ڱ��� �����Ѵ�.
    template<typename T, typename... Args>
    T* AddComponent(Args&&... args)
    {
        // ������ ������ T�� Component�� ��ӹ��� Ŭ���� ���� Ȯ��
        static_assert(std::is_base_of<Component, T>::value, "T must derive from Component");

        // ���ڱ��� �����ϸ鼭 ����
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
            // ���൵��(Runtime)�� comp�� ����Ű�� �ν��Ͻ��� RTTI���� �̿��Ͽ� 
            // T�̰ų� T�� �ڽ� Ŭ���� �̸� �ּҸ� �����Ѵ�. Ŭ������ ���� �Լ��� �ϳ��� ������,
            // �����Ϸ��� �ش� Ŭ������ ���� vtable + RTTI(Run-Time Type Information, ��Ÿ�� Ÿ�� ����)
            // ���� ����� �����մϴ�.
            if (auto casted = dynamic_cast<T*>(comp))
                result.push_back(casted);
        }
        return result;
    }

    template<typename T>
    T* GetComponent() {
        for (Component* comp : components) {
            if (typeid(*comp) == typeid(T)) //������ ������ Ÿ�Ը�
                return static_cast<T*>(comp); //�����ϰ� static_cast
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