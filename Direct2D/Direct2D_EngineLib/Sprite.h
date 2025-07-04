#pragma once
#include <d2d1_1.h>
#include <string>
#include <iostream>
#include "Texture2D.h"

/* [Sprite]
* Texture2D�� Rect�� ��Ÿ �����͸� ���� �׷��� ��ü.
* ��Ʈ�� �ε� ����� ���δ�.
* SpriteRenderer, ImageRenderer���� ������ ���ҽ��� ���Ǹ� ResourceManager���� �����ȴ�.
*/

class Sprite
{
public:
	std::string name;
	D2D1_SIZE_F size = { 0, 0 };
	D2D1_RECT_F sourceRect = { 0, 0, 0, 0 };
	D2D1_POINT_2F pivot = { 0.5f, 0.5f };
	std::shared_ptr<Texture2D> texture = nullptr;

public:
    // texture ��ü������ sprite�� ����
    Sprite(std::shared_ptr<Texture2D> tex, std::string spriteName)
    {
        texture = tex;
        name = spriteName;
        size = tex->size;
        sourceRect = { 0, 0, tex->size.width, tex->size.height };
    }

    // texture�� �Ϻο����� sprite�� ����
    Sprite(std::shared_ptr<Texture2D> tex, std::string spriteName, D2D1_RECT_F rect, D2D1_POINT_2F pivotPoint)
    {
        texture = tex;
        name = spriteName;
        size = tex->size;
        sourceRect = rect;
        pivot = pivotPoint;

        size.width = rect.right - rect.left;
        size.height = rect.bottom - rect.top;
    }
};

