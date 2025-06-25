#include "MenuScene.h"

void MenuScene::Awake()
{
	// camera init
	camera = DemoApp::mainCamera;
	camera->transform->SetPosition(0, 0);

	// menu scene game object
	background = CreateObject<MenuBackground>();
	cat = CreateObject<Cat>();
	fish = CreateObject<Fish>();
	
	menuUIManager = CreateObject<MenuUIManager>();
	menuUIManager->titleImage = CreateObject<UI_Image>();
	menuUIManager->titleText = CreateObject<UI_Text>();
	menuUIManager->button1 = CreateObject<UI_Button>();
	menuUIManager->button2 = CreateObject<UI_Button>();
	
	// game object -> awake (component add)
	__super::Awake();
}

void MenuScene::Start() 
{
	// �θ���� ����
	fish->transform->SetParent(cat->transform);

	// Button event ���
	menuUIManager->button1->button->onClickListeners.AddListener(
		&cat, std::bind(&Cat::Button1Click, cat));
	menuUIManager->button1->button->onClickListeners.AddListener(
		&fish, std::bind(&Fish::Button1Click, fish));

	menuUIManager->button2->button->onClickListeners.AddListener(
		&cat, std::bind(&Cat::Button2Click, cat));
	menuUIManager->button2->button->onClickListeners.AddListener(
		&fish, std::bind(&Fish::Button2Click, fish));

	// game object -> start (init lojic)
	__super::Start();
}

void MenuScene::Update() 
{
	// camera move
	if (Input::GetKey(VK_LEFT)) camera->transform->AddPosition(-200 * Time::GetDeltaTime(), 0);
	if (Input::GetKey(VK_RIGHT)) camera->transform->AddPosition(200 * Time::GetDeltaTime(), 0);
	if (Input::GetKey(VK_UP)) camera->transform->AddPosition(0, 200 * Time::GetDeltaTime());
	if (Input::GetKey(VK_DOWN)) camera->transform->AddPosition(0, -200 * Time::GetDeltaTime());

	// camera ����� update
	Transform::SetCameraMatrix(camera->transform->GetWorldMatrix());

	// game object -> update
	__super::Update();

	// scene change
	if (Input::GetKeyDown(VK_SPACE)) {
		SceneManager::Get().ChangeScene(DemoApp::SceneName::PLAY);
	}
}

void MenuScene::Exit()
{
	// game object -> destroy
	camera = nullptr;
	__super::Exit();
}