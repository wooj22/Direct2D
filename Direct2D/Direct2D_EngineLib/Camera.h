#pragma once
#include "GameObject.h"
#include "Transform.h"

// TODO :: this remove, 카메라 컴포넌트 작성
class Camera : public GameObject
{
public:
	float width, height;
	Transform* transform;

	Camera() { transform = AddComponent<Transform>(); }
	Camera(int w, int h) : Camera() { width = w; height = h; }
	~Camera() { }
	void SetSize(int w, int h) { width = w;	height = h; }

	// 사용 안함 (GameObject의 Component templete을 사용하기 위한 구조)
	// 게임 콘텐츠의 다른 스크립트에서 componenet만 get해서 제어 코드 작성
	void Awake() override {}
	void SceneStart() override {}
	void Update() override {}
	void Destroyed() override {}
};

