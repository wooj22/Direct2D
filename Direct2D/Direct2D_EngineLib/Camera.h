#pragma once
#include "GameObject.h"
#include "Transform.h"

class Camera : public GameObject
{
public:
	float width, height;
	Transform* transform;

	Camera() { }
	Camera(int w, int h) : width(w), height(h) {};
	~Camera() { }
	void SetSize(int w, int h) { width = w;	height = h; }

	// ��� ���� (GameObject�� Component templete�� ����ϱ� ���� ����)
	// ���� �������� �ٸ� ��ũ��Ʈ���� componenet�� get�ؼ� ���� �ڵ� �ۼ�
	void Start() override {}
	void Update() override {}
	void Destroy() override {}
};

