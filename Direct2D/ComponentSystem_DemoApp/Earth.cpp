#include "Earth.h"

void Earth::Awake()
{
	
}

void Earth::SceneStart()
{
	transform->SetPosition(150, 0);
	transform->SetScale(0.5, 0.5);
	sr->CreateTexture2D("../Resource/Earth.png");
}

void Earth::Update()
{
	transform->AddRotation(-rotationSpeed * Time::GetDeltaTime());
}

void Earth::Destroyed()
{

}