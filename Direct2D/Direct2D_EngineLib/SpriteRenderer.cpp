#include "SpriteRenderer.h"
#include "Transform.h"
#include "GameObject.h"

void SpriteRenderer::OnEnable() 
{
	transform = this->owner->GetComponent<Transform>();
}

void SpriteRenderer::Update() 
{

}

void SpriteRenderer::Render() 
{
	if (!transform || !sprite) return;

	D2D1_RECT_F srcRect = sprite->sourceRect;
	D2D1_SIZE_F spriteSize = sprite->size;

	float pivotX = sprite->pivot.x;
	float pivotY = 1.0f - sprite->pivot.y;

	destRect = {
		-spriteSize.width * pivotX,
		-spriteSize.height * pivotY,
		spriteSize.width * (1.0f - pivotX),
		spriteSize.height * (1.0f - pivotY)
	};
	
	// render
	RenderSystem::Get().renderTarget->SetTransform(transform->GetScreenMatrix());
	RenderSystem::Get().renderTarget->DrawBitmap(
		sprite->texture->texture2D.Get(),
		destRect,           // ��� ��ġ �� ũ��
		alpha,				// ������
		D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
		srcRect             // source rect
	);
}

void SpriteRenderer::OnDestroy()
{
	sprite = nullptr;
}