#pragma once
#include <wrl/client.h> 
#include <d2d1_1.h>
#include "IRenderer.h"
#include "RenderSystem.h"

/* [Image Renderer Conponent]
* <UI>�� �̹��� �� ��(sprite)�� render�� ����ϴ� component��
* ������Ʈ ������ RenderSystem�� ��ϵǾ� sprite�� �Լ� render�Ѵ�.
* sprite�� �ִٸ� sprite ���, ���ٸ� white box ĥ�ϱ�
* render�� �ʿ��� rectTransform�� �� ������Ʈ�� ��ϵ� ������Ʈ�� rectTransform�� �����Ϳ� ��� Ȱ���Ѵ�
*/

class RectTransform;
class ImageRenderer : public IRenderer
{
private:
	RectTransform* rectTransform;
	D2D1_RECT_F rect;
	Microsoft::WRL::ComPtr<ID2D1Bitmap1> sprite;

	// sprite�� ���� ��� box draw
	ComPtr<ID2D1SolidColorBrush> brush;
	D2D1_COLOR_F textColor = D2D1::ColorF(D2D1::ColorF::White);

public:
	// component cycle
	ImageRenderer() { RenderSystem::Get().Regist(this); };
	~ImageRenderer() override { RenderSystem::Get().Unregist(this); }

	void OnEnable() override;
	void Update() override;
	void Render() override;
	void OnDestroy() override;

	// set
	void SetImage(const wchar_t* path);
};

