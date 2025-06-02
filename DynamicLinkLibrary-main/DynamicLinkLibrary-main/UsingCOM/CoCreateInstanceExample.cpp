#include "CoCreateInstanceExample.h"

#include "../MyCOMLib/IMyCOM.h"
#include <windows.h>

void Run_CoCreateInstance_Example()
{
	IMyCOMObject2* p = nullptr;
	// COM ���̺귯���� ����ϱ����� �ʿ��Ѱ� 
	// 1. ������Ʈ���� ��ϵ� ClassID (DLL��ġ�� �����) 
	// 2. ���̺귯�� Ŭ������ �ν��Ͻ��� ����ϱ����� �������̽�
	HRESULT hr = CoCreateInstance(CLSID_MyCOMObject, // ������ COM Ŭ���� ID 
		nullptr, CLSCTX_INPROC_SERVER, // ���� ���μ����� COM��ü �ν��Ͻ��� �����ϰڴ�.
		__uuidof(p),   // �������̽� ID
		(void**)&p);  // ������ �ν��Ͻ��� �������̽� �ּҸ� ������ ���� 
	
	if (SUCCEEDED(hr)) 
	{
		// Client(ȣ���ϴ���) / Server(COM��ü �ν��Ͻ�)    
		p->Hello();
		p->Bye();

		// ������ �ν��Ͻ� ����
		p->Release(); 	
	}
	
}
