#pragma once
#include "GameObject.h"
#include "Transform.h"

class Camera : public GameObject
{
public:
	float width, height;
	Transform* transform;

	Camera() { transform = AddComponent<Transform>(); }
	Camera(int w, int h) : Camera() { width = w; height = h; }
	~Camera() { }
	void SetSize(int w, int h) { width = w;	height = h; }

	// ��� ���� (GameObject�� Component templete�� ����ϱ� ���� ����)
	// ���� �������� �ٸ� ��ũ��Ʈ���� componenet�� get�ؼ� ���� �ڵ� �ۼ�
	void Awake() override {}
	void SceneStartInit() override {}
	void Update() override {}
	void Destroyed() override {}
};

