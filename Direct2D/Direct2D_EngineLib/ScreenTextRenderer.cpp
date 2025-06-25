#include "ScreenTextRenderer.h"
#include "RectTransform.h"
#include "GameObject.h"

void ScreenTextRenderer::OnEnable()
{
	rectTransform = this->owner->GetComponent<RectTransform>();

	// brush ����
	RenderSystem::Get().renderTarget->CreateSolidColorBrush(textColor, brush.GetAddressOf());
	isTextDirty = true;
}

void ScreenTextRenderer::Update()
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
			text.c_str(),
			static_cast<UINT32>(text.length()),
			textFormat.Get(),
			rectTransform->GetSize().width, rectTransform->GetSize().height,
			textLayout.GetAddressOf()
		);

		// center  (���� �ʿ�. rectTransform�� pivot�� ������)
		//centerPoint = { -rectTransform->GetSize().width / 2.0f,-rectTransform->GetSize().height / 2.0f };

		isTextDirty = false;
	}
}

void ScreenTextRenderer::Render()
{
	if (!rectTransform || !textLayout) return;

	// render
	RenderSystem::Get().renderTarget->SetTransform(rectTransform->GetScreenMatrix());
	RenderSystem::Get().renderTarget->DrawTextLayout(
		{0,0}, textLayout.Get(), brush.Get());
}

void ScreenTextRenderer::OnDestroy()
{
	brush = nullptr;
	textFormat = nullptr;
	textLayout = nullptr;
}

void ScreenTextRenderer::SetText(const std::wstring& newText)
{
	text = newText;
	isTextDirty = true;
}

void ScreenTextRenderer::SetFontSize(float newSize)
{
	fontSize = newSize;
	isTextDirty = true;
}

void ScreenTextRenderer::SetFontName(const std::wstring& newName)
{
	fontName = newName;
	isTextDirty = true;
}

void ScreenTextRenderer::SetColor(const D2D1_COLOR_F& newColor)
{
	textColor = newColor;
	if (brush) {
		brush->SetColor(textColor);
	}
	else {
		RenderSystem::Get().renderTarget->CreateSolidColorBrush(textColor, brush.GetAddressOf());
	}
}