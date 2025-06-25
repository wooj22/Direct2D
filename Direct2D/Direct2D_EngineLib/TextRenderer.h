#pragma once
#include <wrl/client.h> 
#include <d2d1_1.h>
#include <string>
#include "RenderSystem.h"
#include "IRenderer.h"

/* [Text Renderer Conponent]
* <World>�� Text ����� ����ϴ� Component��
* ������Ʈ ������ RenderSystem�� ��ϵǾ� text�� ��� render�Ѵ�.
* ���� ���������� text, font, size, color, layout�� ������ �� �ִ�. (dirty ���� Ȱ��)
* render�� �ʿ��� transform�� �� ������Ʈ�� ��ϵ� ������Ʈ�� transform�� �����Ϳ� ��� Ȱ���Ѵ�
*/

class Transform;
class TextRenderer : public IRenderer
{
private:
	D2D1_POINT_2F centerPoint;
	Transform* transform;

	// text
	std::wstring text = L"";
	float fontSize = 32.0f;
	std::wstring fontName = L"���� ���";
	D2D1_COLOR_F textColor = D2D1::ColorF(D2D1::ColorF::White);
	int width = 100;
	int height = 100;

	// d2d
	ComPtr<ID2D1SolidColorBrush> brush;
	ComPtr<IDWriteTextFormat> textFormat;
	ComPtr<IDWriteTextLayout> textLayout;

	bool isTextDirty;

public:
	// component cycle
	TextRenderer() { RenderSystem::Get().Regist(this); };
	~TextRenderer() override { RenderSystem::Get().Unregist(this); }

	void OnEnable() override;
	void Update() override;
	void Render() override;
	void OnDestroy() override;

	// set
	void SetText(const std::wstring& newText);
	void SetFontSize(float newSize);
	void SetFontName(const std::wstring& newName);
	void SetColor(const D2D1_COLOR_F& newColor);
	void SetLayout(int width, int height);
};

