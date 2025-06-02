#include "pch.h"
#include "MyFactory.h"
#include "MyCOMObject.h"
#include "OtherObject.h"

STDMETHODIMP MyFactory::CreateInstance(IUnknown* pUnkOuter, REFIID riid, void** ppv)
{
	if (ppv == nullptr)
		return E_POINTER;
	*ppv = nullptr;

	if (pUnkOuter != nullptr)
		return CLASS_E_NOAGGREGATION; // �� ������ Aggregation�� �������� ����

	MyCOMObject* pObj = new (std::nothrow) MyCOMObject();
	if (!pObj)
		return E_OUTOFMEMORY;

	HRESULT hr = pObj->QueryInterface(riid, ppv);
	pObj->Release(); // ���� �� ���� refcount 2 �� ���⼭ 1 ����
	return hr;
}

HRESULT MyFactory::CreateOther(IOtherObject** ppObj)
{
	if (!ppObj) return E_POINTER;
	*ppObj = new OtherObject();
	return S_OK;
}

extern "C" HRESULT CreateMyFactory(REFIID riid, void** ppv)
{
	if (!ppv)
		return E_POINTER;

	*ppv = nullptr;

	MyFactory* pObj = new (std::nothrow) MyFactory();
	if (!pObj)
		return E_OUTOFMEMORY;

	HRESULT hr = pObj->QueryInterface(riid, ppv);
	pObj->Release();  // QueryInterface�� AddRef �����Ƿ� ���⼭ 1 ����

	return hr;
}
