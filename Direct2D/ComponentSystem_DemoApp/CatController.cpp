#include "CatController.h"

void CatController::OnEnable()
{
	// get component
	transform = this->owner->GetComponent<Transform>();
	sr = this->owner->GetComponent<SpriteRenderer>();
	tr = this->owner->GetComponent<WorldTextRenderer>();

	// set
	transform->SetPosition(0, 0);
	sr->CreateTexture2D("../Resource/Cat.png");
	tr->SetText(L"�� ��ƺ���\n [Spacebar] �� ����");
	tr->SetColor(D2D1::ColorF(D2D1::ColorF::Yellow));
	tr->SetLayout(300, 100);
}

void CatController::Update()
{
	transform->AddPosition(0, moveSpeed * moveDirection * Time::GetDeltaTime());
	
	// GameObject::Find("Fish")->GetComponent<Transform>();
	// OnEnable()�ÿ� Fish�� fishTransform�� �����Ǿ����� ���� ���� �־� Start()������ �ʿ���
	// ������ onwer���� ���� Find�Ͽ� ��������
	fishTransform->AddRotation(120 * -1 * Time::GetDeltaTime());
}

void CatController::OnDestroy() 
{
	
}

void CatController::Button1Click()
{
	moveDirection *= -1;
	tr->SetColor(D2D1::ColorF(D2D1::ColorF::Red));
}

void CatController::Button2Click()
{
	moveDirection *= -1;
	tr->SetColor(D2D1::ColorF(D2D1::ColorF::Yellow));
}