#pragma once
#include <wrl/client.h> 
#include <d2d1_1.h>
#include "IRenderer.h"
#include "Transform.h"
#include "D2DRenderManager.h"

/* Bitmap Render Conponent */
// Render, UnInit�� Manager���� ȣ���ϸ� Manager���� ���յ��� ���߱� ���� �������̽��� Ȱ���Ѵ�.
class BitmapRenderer : public IRenderer
{
public:
	BitmapRenderer() { D2DRenderManager::Get().RenderListAdd(this); };
	~BitmapRenderer() {}

	Transform transform;
	Microsoft::WRL::ComPtr<ID2D1Bitmap1> image;

	void Render() override;
	void UnInit() override;
};

