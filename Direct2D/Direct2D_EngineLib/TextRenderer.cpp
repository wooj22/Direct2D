#include "TextRenderer.h"
#include "Transform.h"
#include "GameObject.h"

void TextRenderer::OnEnable() 
{
	transform = this->owner->GetComponent<Transform>();

	// �⺻ �귯��
	RenderSystem::Get().renderTarget->CreateSolidColorBrush(textColor, brush.GetAddressOf());
	isTextDirty = true;
}

void TextRenderer::Update() 
{
	if (isTextDirty) {
		// �ؽ�Ʈ ���� �����
		RenderSystem::Get().dWriteFactory->CreateTextFormat(
			fontName.c_str(),              // ��Ʈ
			nullptr,                       // Ŀ���� ��Ʈ �÷��� (null�̸� �ý��� �⺻)
			DWRITE_FONT_WEIGHT_NORMAL,     // ����
			DWRITE_FONT_STYLE_NORMAL,      // ��Ÿ��(����� ����)
			DWRITE_FONT_STRETCH_NORMAL,    // ��Ʈ��Ī
			fontSize,                      // ũ��
			L"",                           // ������ (""�̸� �ý��� �⺻ ���)
			textFormat.GetAddressOf()
		);
		
		// ����
		textFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
		textFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);

		// �ؽ�Ʈ ���̾ƿ� �����
		RenderSystem::Get().dWriteFactory->CreateTextLayout(
			text.c_str(),                       // ����� ���ڿ�
			static_cast<UINT32>(text.length()), // ���ڿ� ����
			textFormat.Get(),                   
			width, height,                      // ���̾ƿ� ũ��
			textLayout.GetAddressOf()
		);

		// center
		centerPoint = { -width / 2.0f,-height / 2.0f };

		isTextDirty = false;
	}
}

void TextRenderer::Render() 
{
	if (!transform || !textLayout) return;
	
	// render
	RenderSystem::Get().renderTarget->SetTransform(transform->GetScreenMatrix());
	RenderSystem::Get().renderTarget->DrawTextLayout(
		centerPoint,
		textLayout.Get(),
		brush.Get()
	);
}

void TextRenderer::OnDestroy() 
{
	brush = nullptr;
	textFormat = nullptr;
	textLayout = nullptr;
}

void TextRenderer::SetText(const std::wstring& newText)
{
	text = newText;
	isTextDirty = true;
}

void TextRenderer::SetFontSize(float newSize)
{
	fontSize = newSize;
	isTextDirty = true;
}

void TextRenderer::SetFontName(const std::wstring& newName)
{
	fontName = newName;
	isTextDirty = true;
}

void TextRenderer::SetColor(const D2D1_COLOR_F& newColor)
{
	textColor = newColor;
	if (brush) {
		brush->SetColor(textColor);
	}
	else {
		RenderSystem::Get().renderTarget->CreateSolidColorBrush(textColor, brush.GetAddressOf());
	}
}

void TextRenderer::SetLayout(int width, int height) 
{
	this->width = width; this->height = height;
	isTextDirty = true;
}