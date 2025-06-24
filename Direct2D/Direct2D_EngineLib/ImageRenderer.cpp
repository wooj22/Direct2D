#include "ImageRenderer.h"
#include "RectTransform.h"
#include "GameObject.h"

void ImageRenderer::OnEnable()
{
	rectTransform = this->owner->GetComponent<RectTransform>();

	// brush ����
	RenderSystem::Get().renderTarget->CreateSolidColorBrush(textColor, brush.GetAddressOf());
}

void ImageRenderer::Update()
{

}

void ImageRenderer::Render()
{
	if (!rectTransform) return;

    // pivot�� ����� ��ġ
	RenderSystem::Get().renderTarget->SetTransform(rectTransform->GetScreenMatrix());

    // pivot�� �̹� ����Ǿ� �����Ƿ� �׸� ������ ����
    auto size = rectTransform->GetSize();
    if (sprite)
    {
        D2D1_SIZE_F spriteSize = sprite->GetSize();
        rect = { 0.0f, 0.0f, size.width, size.height };
        RenderSystem::Get().renderTarget->DrawBitmap(sprite.Get(), rect);
    }
    else
    {
        // sprite�� ���� ��� white box �׸���
        rect = { 0.0f, 0.0f, size.width, size.height };
        RenderSystem::Get().renderTarget->FillRectangle(rect, brush.Get());
    }
}

void ImageRenderer::OnDestroy() 
{
	sprite = nullptr;
}

void ImageRenderer::SetImage(const wchar_t* path)
{
	RenderSystem::Get().CreateBitmapFromFile(path, this->sprite.GetAddressOf());
}