#pragma once
#include <vector>
using namespace std;

/* [Scene Ŭ����]
* ���� ������������ Scene�� Base�� �� ���� GameObect�� ��Ͻ��� GameObject�� Cycle�� ȣ���Ѵ�.
* SceneManager -> Scene(this) -> GameObject
*/

class GameObject;
class Scene
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

	template<typename T>
	void DeleteObject(T object)
	{
		auto it = find(objectList.begin(), objectList.end(), object);
		objectList.erase(it);
	}
};

