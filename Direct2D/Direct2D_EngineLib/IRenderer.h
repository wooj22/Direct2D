#pragma once

// Q. ���� IRenderer�� ������ ����
// A. Ȯ�强 - ����� ��Ӱ��谡 BitmapRenderer�ۿ� ������ ���� �߰��� ���ɼ��� ����
//          - ShapeRenderer, TextRenderer, SpriteRenderer, EffectRenderer, ParticleRenderer ��
//    ������ - Render(), UnInit()�� ȣ���ϴ� RenderManager���� 
//            �� �Լ� ���� BitmapRenderer����� ������ ���� ���� ������ �߻� �������̽��� Ȱ���Ͽ� ���յ��� ����

/* �������̽� */
class IRenderer
{
public : 
	virtual void Render() = 0;
	virtual void UnInit() = 0;
};

