#pragma once
#include <wrl/client.h> 
#include <d2d1_1.h>
#include "IRenderer.h"
#include "RenderSystem.h"

#include "Texture2D.h"
#include "ResourceManager.h"
#include "iostream"

/* [Sprite Renderer Conponent]
* <World>�� �̹��� �� ��(sprite)�� render�� ����ϴ� component��
* ������Ʈ ������ RenderSystem�� ��ϵǾ� sprite�� �Լ� render�Ѵ�.
* render�� �ʿ��� transform�� �� ������Ʈ�� ��ϵ� ������Ʈ�� transform�� �����Ϳ� ��� Ȱ���Ѵ�
*/

class Transform;
class SpriteRenderer : public IRenderer
{
private:
	Transform* transform;
	D2D1_RECT_F centerRect;
	shared_ptr<Texture2D> sprite;	// ���� �ڿ� // TODO :: Sptie Class �����

public:
	// component cycle
	SpriteRenderer() 
	{ 
		RenderSystem::Get().Regist(this); 
		OutputDebugStringA("SpriteRenderer()\n");
	};
	~SpriteRenderer() override
	{ 
		RenderSystem::Get().Unregist(this);
		OutputDebugStringA("~SpriteRenderer()\n");
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

