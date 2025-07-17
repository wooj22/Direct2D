#pragma once
#include <vector>
#include <windows.h> 
#include "GameObject.h"
#include "Object.h"

using namespace std;

/* [Scene]
* ���ӿ�����Ʈ�� �����̳� ������ �����ϸ� ���� ������Ʈ ����Ŭ�� ȣ���Ѵ�.
* ���� GameObject�� ������ �� : GameObject->Awake()
* ���� Start�� �� : GameObject->SceneStartInit()
* ���� Update�� �� : GameObject->Update()
* ���� GameObject�� ������ų �� : GameObject->Destroyed()
*/

class GameObject;
class Scene : public Object
{
private:
	vector<GameObject*> objectList;

public:
	Scene() = default;
	virtual ~Scene() { Clear(); }

	/* Scene Life Cycle */
	virtual void Awake() = 0;
	virtual void Start();		// GameObjects->SceneStartInit()
	virtual void Update();		// GameObjects->Update()
	virtual void Exit();		// GameObjects->Destroyed()
	void Clear();

	// Create
	template<typename T, typename... Args>
	T* CreateObject(Args&&... args)
	{
		T* pObject = new T(std::forward<Args>(args)...);
		objectList.push_back(pObject);
		pObject->Awake();			// GameObject->Awake()
		return pObject;
	}

	// Delete
	template<typename T>
	void DeleteObject(T object)
	{
		auto it = find(objectList.begin(), objectList.end(), object);
		if (it != objectList.end()) {
			(*it)->Destroyed();;
			delete *it;
			objectList.erase(it);
		}

		else {
			OutputDebugStringA("������ GameObject�� �����ϴ�.\n");
		}
	}
};

