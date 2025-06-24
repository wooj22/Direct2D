#pragma once
#include <wrl/client.h> 
#include <d2d1_1.h>
#include "IRenderer.h"
#include "RenderSystem.h"

/* [Sprite Renderer Conponent]
* �̹��� �� ��(sprite)�� render�� ����ϴ� component��
* ������Ʈ ������ RenderSystem�� ��ϵǾ� sprite�� �Լ� render�Ѵ�.
* render�� �ʿ��� transform�� �� ������Ʈ�� ��ϵ� ������Ʈ�� transform�� �����Ϳ� ��� Ȱ���Ѵ�
*/

class Transform;
class SpriteRenderer : public IRenderer
{
private:
	D2D1_RECT_F centerRect;
	Transform* transform;

public:
	Microsoft::WRL::ComPtr<ID2D1Bitmap1> sprite;

	SpriteRenderer() { RenderSystem::Get().Regist(this); };
	~SpriteRenderer() override { RenderSystem::Get().Unregist(this); }

	void OnEnable() override;
	void Update() override;
	void Render() override;
	void OnDestroy() override;

	void SetImage(const wchar_t* path);
};

