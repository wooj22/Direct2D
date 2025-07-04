#pragma once
#include <wrl/client.h> 
#include <d2d1_1.h>
#include <string>

/* [Texture2D]
* 2D bitmap ���ҽ� �ϳ��� ������ Ŭ����
* Sprite�� ����� ��ϵǾ� SpriteRenderer, ImageRenderer���� ���ҽ��� ���Ǹ�
* ResourceManager���� �����ȴ�. (TODO :: Sprite Ŭ���� �����)
*/

class Texture2D
{
public:
	std::string filePath;
	D2D1_SIZE_F size;
	Microsoft::WRL::ComPtr<ID2D1Bitmap1> texture2D;
};