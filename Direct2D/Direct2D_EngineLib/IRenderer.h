#pragma once
#include "Component.h"
// Q. ���� IRenderer�� ������ ����
// A. Ȯ�强 - ����� ��Ӱ��谡 BitmapRenderer�ۿ� ������ ���� �߰��� ���ɼ��� ����
//          - ShapeRenderer, TextRenderer, SpriteRenderer, EffectRenderer, ParticleRenderer ��
//    ������ - Render(), UnInit()�� ȣ���ϴ� RenderManager���� 
//            �� �Լ� ���� BitmapRenderer����� ������ ���� ���� ������ �߻� �������̽��� Ȱ���Ͽ� ���յ��� ����

/* �������̽� */
class IRenderer : public Component
{
public : 
	virtual ~IRenderer() = default;

	//void OnEnable() override {};
	virtual void Update() = 0;
	virtual void Render() = 0;
	//void OnDestroy() override {};
};

