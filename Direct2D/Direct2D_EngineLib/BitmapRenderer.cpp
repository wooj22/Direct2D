#include "BitmapRenderer.h"

void BitmapRenderer::AxisCoreection() {
	if (!image) return;

	D2D1_SIZE_F size = image->GetSize();
	destRect = {
		-size.width / 2.0f,  // ����
		-size.height / 2.0f, // ��
		size.width / 2.0f,   // ������
		size.height / 2.0f   // �Ʒ�
	};
}

void BitmapRenderer::Render() 
{
	// �߰��� �� ������ �ʿ���. ������ �̹����� ���� ���� �����ε�,
	// �� ��ǥ�� �̹����� �������� ��µǵ��� �Űܼ� �׷�����
	// �̹��� ����� Microsoft::WRL::ComPtr<ID2D1Bitmap1> image; �� ����Ǿ�����
	D2DRenderManager::Get().renderTarget->SetTransform(transform.GetScreenMatrix());
	D2DRenderManager::Get().renderTarget->DrawBitmap(image.Get(), destRect);
}

void BitmapRenderer::UnInit()
{
	image = nullptr;
}