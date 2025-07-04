#include "Scene2.h"

void Scene2::Awake()
{
	// camera init
	camera = DemoApp::mainCamera;
	camera->transform->SetPosition(0, 0);

	// gameobject create
	Scene2ObjectCreate(); // ������()->ComponentInit()->Awake()
}

void Scene2::Start()
{
	// game object -> SceneStartInit
	__super::Start();

	Scene2ObjectSetting();

	// Button event ���
	createButton->button->onClickListeners.AddListener(
		this, std::bind(&Scene2::CreateButtonClick, this));
	deleteButton->button->onClickListeners.AddListener(
		this, std::bind(&Scene2::DeleteButtonClick, this));
}

void Scene2::Update()
{
	// game object -> Update
	__super::Update();

	// camera move
	if (Input::GetKey(VK_LEFT)) camera->transform->AddPosition(-300 * Time::GetDeltaTime(), 0);
	if (Input::GetKey(VK_RIGHT)) camera->transform->AddPosition(300 * Time::GetDeltaTime(), 0);
	if (Input::GetKey(VK_UP)) camera->transform->AddPosition(0, 300 * Time::GetDeltaTime());
	if (Input::GetKey(VK_DOWN)) camera->transform->AddPosition(0, -300 * Time::GetDeltaTime());

	// camera ����� update
	Transform::SetCameraMatrix(camera->transform->GetWorldMatrix());

	// ����
	if (Input::GetKeyDown('T')) ResourceManager::Get().Trim();
	if (Input::GetKeyDown(VK_SHIFT))
		memoryUsageText->screenTextRenderer->SetText(ResourceManager::Get().GetMemoryUsageString());

	// scene change
	if (Input::GetKeyDown(VK_SPACE)) {
		SceneManager::Get().ChangeScene(DemoApp::SceneName::SCENE1);
	}
}

void Scene2::Exit()
{
	// game object -> destroy
	camera = nullptr;
	__super::Exit();
}

void Scene2::Scene2ObjectCreate()
{
	titleBackground = CreateObject<UI_Image>();
	titleText = CreateObject<UI_Text>();
	adviceText = CreateObject<UI_Text>();
	memoryUsageText = CreateObject<UI_Text>();
	createButton = CreateObject<UI_Button>();
	deleteButton = CreateObject<UI_Button>();
}

void Scene2::Scene2ObjectSetting()
{
	titleBackground->rectTransform->SetPosition(0, 400);
	titleBackground->rectTransform->SetSize(600, 100);

	titleText->rectTransform->SetPosition(0, 400);
	titleText->rectTransform->SetSize(600, 100);
	titleText->screenTextRenderer->SetText(L"Resource Memory Test \n<Scene 2>");
	titleText->screenTextRenderer->SetFontSize(40);
	titleText->screenTextRenderer->SetColor(D2D1::ColorF(D2D1::ColorF::DarkRed));

	adviceText->rectTransform->SetPosition(0, 300);
	adviceText->rectTransform->SetSize(600, 100);
	adviceText->screenTextRenderer->SetText(L"[T] Trim, [Shift] �޸� Ȯ��\n [Spacebar] �� ��ȯ");

	memoryUsageText->rectTransform->SetPivot(0, 1);
	memoryUsageText->rectTransform->SetPosition(-640, 200);
	memoryUsageText->rectTransform->SetSize(600, 300);

	auto buttonTexture = ResourceManager::Get().CreateTexture2D("../Resource/UI_Button.png");
	auto new_sprite = ResourceManager::Get().CreateSprite(buttonTexture, "ButtonSprite");

	createButton->rectTransform->SetPosition(-150, -300);
	createButton->rectTransform->SetSize(130, 60);
	createButton->imageRenderer->sprite = new_sprite;
	createButton->screenTextRenderer->SetText(L"Create");

	deleteButton->rectTransform->SetPosition(150, -300);
	deleteButton->rectTransform->SetSize(130, 60);
	deleteButton->imageRenderer->sprite = new_sprite;
	deleteButton->screenTextRenderer->SetText(L"Delete");
}

void Scene2::CreateButtonClick()
{
	CreateObject<Cat>();
}

void Scene2::DeleteButtonClick()
{
	TestCatPop();
}