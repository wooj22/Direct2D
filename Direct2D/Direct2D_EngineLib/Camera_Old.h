#pragma once
#include "GameObject.h"
#include "Transform.h"

// TODO :: this remove, ī�޶� ������Ʈ �ۼ�
class Camera_Old : public GameObject
{
public:
	float width, height;
	Transform* transform;

	Camera_Old() { transform = AddComponent<Transform>(); }
	Camera_Old(int w, int h) : Camera_Old() { width = w; height = h; }
	~Camera_Old() { }
	void SetSize(int w, int h) { width = w;	height = h; }

	// ��� ���� (GameObject�� Component templete�� ����ϱ� ���� ����)
	// ���� �������� �ٸ� ��ũ��Ʈ���� componenet�� get�ؼ� ���� �ڵ� �ۼ�
	void Awake() override {}
	void SceneStart() override {}
	void Update() override {}
	void Destroyed() override {}
};

