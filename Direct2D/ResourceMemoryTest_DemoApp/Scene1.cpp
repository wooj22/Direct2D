#include "Scene1.h"

void Scene1::Awake()
{
	// camera init
	camera = DemoApp::mainCamera;
	camera->transform->SetPosition(0, 0);

	// gameobject create
	Scene1ObjectCreate();
	Scene1ObjectSetting();
}

void Scene1::Start()
{
	__super::Start();
}

void Scene1::Update()
{
	__super::Update();

	// camera move
	if (Input::GetKey(VK_LEFT)) camera->transform->Translate(-300 * Time::GetDeltaTime(), 0);
	if (Input::GetKey(VK_RIGHT)) camera->transform->Translate(300 * Time::GetDeltaTime(), 0);
	if (Input::GetKey(VK_UP)) camera->transform->Translate(0, 300 * Time::GetDeltaTime());
	if (Input::GetKey(VK_DOWN)) camera->transform->Translate(0, -300 * Time::GetDeltaTime());

	// camera ����� update
	Transform::SetCameraMatrix(camera->transform->GetWorldMatrix());

	// ����
	if (Input::GetKeyDown('N')) CreateObject<Cat>();
	if (Input::GetKeyDown('D')) TestCatPop();
	if (Input::GetKeyDown('T')) ResourceManager::Get().Trim();
	if (Input::GetKeyDown(VK_SHIFT)) 
		memoryUsageText->screenTextRenderer->SetText(ResourceManager::Get().GetMemoryUsageString());

	// scene change
	if (Input::GetKeyDown(VK_SPACE)) {
		SceneManager::Get().ChangeScene(DemoApp::SceneName::SCENE2);
	}
}

void Scene1::Exit()
{
	camera = nullptr;
	__super::Exit();
}

void Scene1::Scene1ObjectCreate() 
{
	titleBackground = CreateObject<UI_Image>();
	titleText = CreateObject<UI_Text>();
	adviceText = CreateObject<UI_Text>();
	memoryUsageText = CreateObject<UI_Text>();
}

void Scene1::Scene1ObjectSetting() 
{
	titleBackground->rectTransform->SetPosition(0, 400);
	titleBackground->rectTransform->SetSize(600, 100);
	
	titleText->rectTransform->SetPosition(0, 400);
	titleText->rectTransform->SetSize(600, 100);
	titleText->screenTextRenderer->SetText(L"Resource Memory Test \n<Scene 1>");
	titleText->screenTextRenderer->SetFontSize(40);
	titleText->screenTextRenderer->SetColor(D2D1::ColorF(D2D1::ColorF::DarkGreen));

	adviceText->rectTransform->SetPosition(0, 300);
	adviceText->rectTransform->SetSize(600, 100);
	adviceText->screenTextRenderer->SetText(L"[N] ����, [D] ����, [T] Trim, [Shift] �޸� Ȯ��\n [Spacebar] �� ��ȯ");

	memoryUsageText->rectTransform->SetPivot(0, 1);
	memoryUsageText->rectTransform->SetPosition(-640, 200);
	memoryUsageText->rectTransform->SetSize(600, 300);
}