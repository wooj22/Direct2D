#pragma once
#include "Component.h"

class ITransform : public Component
{
public:
	virtual ~ITransform() = default;
	virtual void Update() = 0;
};

// ���� ������� Ŭ���� ���
// Transform
// (RectTransform)