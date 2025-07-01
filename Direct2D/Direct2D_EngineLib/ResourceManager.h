#pragma once
#include <d3d11.h>
#include <d2d1_3.h>
#include <wrl.h>
#include <wincodec.h>
#include <unordered_map>
#include <string>
#include <memory>
#include <filesystem>
#include <iostream>
#include "Singleton.h"

using namespace std;
using namespace Microsoft::WRL;

/* [ResourceManager]
* ���� �ڿ��� �ߺ����� �޸𸮿� �ε����� �ʵ��� �ؽ����̺�� �����ϴ� Ŭ����
* filePath�� key������ �Ͽ� weak_ptr�� ���ο��� ������ �ϸ�, �ܺ� ��û�� ������ ���
* shared_ptr�� ��ȯ�Ͽ� �����Ѵ�. (���� ��쿡�� ���� ����)
*/

class Texture2D;
class ResourceManager : public Singleton<ResourceManager>
{
private:
	unordered_map<string, weak_ptr<Texture2D>> map_texture2D;
    ComPtr<IWICImagingFactory> wicImagingFactory;

public:
	shared_ptr<Texture2D> CreateTexture2D(string filePath);
};
