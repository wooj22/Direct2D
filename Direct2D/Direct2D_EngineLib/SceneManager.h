#pragma once
#include <vector>
#include "Singleton.h"
using namespace std;

/* [SceneManager Ŭ����]
* ���� ���������� ���� ���۽� CreateScene()���� ��ü ���� SceneManager�� ��Ͻ�Ű��,
* ��� Scene���� sceneList�� �����Ͽ� ���� ���� Update�� ȣ���Ѵ�.
* SceneManager���� ���� ���� Updete�� ȣ�� -> Scene���� ������Ʈ���� update ȣ��
*/

class Scene;
class SceneManager : public Singleton<SceneManager>
{
private:
	vector<Scene*> sceneList;		   // �� ����Ʈ
	Scene* currentScene = nullptr;     // ���� ��
	Scene* nextScene = nullptr;        // ���� ��

public:
	SceneManager() = default;
	~SceneManager() = default;

	void Init();
	void Update();
	void UnInit();

	template<typename T>
	void CreateScene()
	{
		Scene* pScene = new T();
		sceneList.push_back(pScene);
	}

	void SetCurrentScene(size_t index);
	Scene* GetCurrentScene();
	void ChangeScene(size_t index);
};

