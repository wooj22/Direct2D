#pragma once
#include "Singleton.h"
#include <vector>
using namespace std;

/* CameraSystem�� ����
* 1. Camera ������Ʈ ����� udpate
*/

class Camera;
class CameraSystem : public Singleton<CameraSystem>
{
private:
	vector<Camera*> components;

public:
	void Regist(Camera* component);
	void Unregist(Camera* component);
	void Update();
};

