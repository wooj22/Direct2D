#pragma once
#include <wrl/client.h> 
#include <d2d1_1.h>
#include "IRenderer.h"
#include "RenderSystem.h"

#include "Texture2D.h"
#include "ResourceManager.h"
#include "iostream"

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
	shared_ptr<Texture2D> sprite;	// ���� �ڿ�  // TODO :: Sptie Class �����

	// sprite�� ���� ��� box draw
	ComPtr<ID2D1SolidColorBrush> brush;
	D2D1_COLOR_F textColor = D2D1::ColorF(D2D1::ColorF::White);

public:
	// component cycle
	ImageRenderer() { 
		RenderSystem::Get().Regist(this);
		OutputDebugStringA("ImageRenderer()\n");
	};
	~ImageRenderer() override 
	{
		RenderSystem::Get().Unregist(this); 
		OutputDebugStringA("~ImageRenderer()\n");
	}

	void OnEnable() override;
	void Update() override;
	void Render() override;
	void OnDestroy() override;

public:
	// function
	void CreateTexture2D(const std::string& path)
	{
		sprite = ResourceManager::Get().CreateTexture2D(path);
	}
};

