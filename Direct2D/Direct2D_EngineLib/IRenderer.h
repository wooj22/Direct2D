#pragma once
#include "Component.h"

/* Renderer Componenets Interface */

enum class RenderType
{
	UI, GameObject
};

class IRenderer : public Component
{
public : 
	virtual ~IRenderer() = default;

	virtual void Update() = 0;
	virtual void Render() = 0;

	// gameobject ���� ui �׸��� (�ϴ� �̷��� ��)
	RenderType rendertype = RenderType::GameObject;
};