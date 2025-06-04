#include "ManualFactoryExample.h"

#include <windows.h>
#include "../MyCOMLib/IMyCOM.h"

#include <wrl.h>	// ComPtr
using namespace Microsoft::WRL;

#ifdef _DEBUG
#pragma comment(lib, "../x64/Debug/3_MyCOMLib.lib")
#else
#pragma comment(lib, "../x64/Release/3_MyCOMLib.lib")
#endif


void Run_ManualFactory_Example()
{	
	// �������̽� �����͸� �ٷ�� ����Ʈ ������
	// ������ �ı��ɶ� Ŭ���� ���ο��� �������̽��� Release�� ȣ���Ѵ�.
	IMyFactory2* pIMyFactory;
	ComPtr<IMyCOMObject2> cpMyCOMObject2;
	ComPtr<IMyCOMObjectExtraFeature> cpMyCOMObjectExtraFeature;
	ComPtr<IOtherObject> cpOtherObject;
	
	IID test = __uuidof(pIMyFactory);
	CreateMyFactory(test,	   // ���丮�� �������̽� ID
		(void**)&pIMyFactory); // �������̽� �����͸� ������ ����
	
	// ���丮�� 1:1�� ����Ǵ� COM��ü
	pIMyFactory->CreateInstance(nullptr,
		__uuidof(cpMyCOMObject2), // COM��ü�� ����ȯ�Ͽ� ����� �������̽� ID
		(void**)cpMyCOMObject2.GetAddressOf()); // �������̽� �����͸� ������ ����

	// COM��ü�� ���
	cpMyCOMObject2->Hello();
	cpMyCOMObject2->Bye();

	// ���丮�� �ΰ������� ������ COM��ü
	pIMyFactory->CreateOther(cpOtherObject.GetAddressOf());
	// COM��ü�� ���
	cpOtherObject->Say();

	// ���� �ν��Ͻ������� �ٸ� �������̽� ���
	// IMyCOMObjectExtraFeature
	cpMyCOMObject2->QueryInterface(__uuidof(cpMyCOMObjectExtraFeature),
		(void**)cpMyCOMObjectExtraFeature.GetAddressOf());
	cpMyCOMObjectExtraFeature->Jump();
	

	pIMyFactory->Release(); // ������ 0�϶� ������ delete
}
