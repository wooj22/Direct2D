#pragma once
#include <vector>
#include <windows.h> 
#include "GameObject.h"
#include "Object.h"

using namespace std;

/* [Scene Ŭ����]
* ���� ������������ Scene�� Base�� �� ���� GameObect�� ��Ͻ��� GameObject�� Cycle�� ȣ���Ѵ�.
* SceneManager -> Scene(this) -> GameObject
*/

class GameObject;
class Scene : public Object
{
private:
	vector<GameObject*> objectList;

public:
	Scene() = default;
	virtual ~Scene() { Clear(); }

	// Scene Life Cycle
	virtual void Awake();		// GameObjects->Awake()
	virtual void Start();		// GameObjects->Start()
	virtual void Update();		// GameObjects->Update()
	virtual void Exit();		// GameObjects->Destroyed()
	void Clear();

	// Game Object
	template<typename T, typename... Args>
	T* CreateObject(Args&&... args)
	{
		T* pObject = new T(std::forward<Args>(args)...);
		objectList.push_back(pObject);
		return pObject;
	}

	// Create�� �����ͷθ� delete ������
	// TODO :: GameObject Find�� �����ϴ� ��� ã�ƺ���
	template<typename T>
	void DeleteObject(T object)
	{
		auto it = find(objectList.begin(), objectList.end(), object);
		if (it != objectList.end()) {
			objectList.erase(it);
			return;
		}
		else {
			OutputDebugStringA("������ GameObject�� �����ϴ�.\n");
			return;
		}
	}

	// ���ҽ� ���ſ� test �Լ�
	void TestCatPop() {
		if (objectList.back()->name == "Cat") {
			objectList.back()->Destroyed();
			delete objectList.back();
			objectList.pop_back();
		}

		OutputDebugStringA("������ Cat�� �����ϴ�.\n");
	}
};

