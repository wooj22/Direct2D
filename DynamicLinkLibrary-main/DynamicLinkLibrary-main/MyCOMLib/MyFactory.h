#pragma once
#include "IMyCOM.h"

class MyFactory : public IMyFactory2 {
	ULONG m_refCount = 1;
public:
	HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void** ppv) override 
	{
		if (riid == IID_IUnknown || riid == IID_IClassFactory) 
			*ppv = static_cast<IClassFactory*>(this);
		else if (riid == IID_IMyFactory)
			*ppv = static_cast<IMyFactory*>(this);
		else if (riid == IID_IMyFactory2)
			*ppv = static_cast<IMyFactory2*>(this);
		else {
			*ppv = nullptr;
			return E_NOINTERFACE;
		}
		AddRef();
		return S_OK;
	}
	ULONG STDMETHODCALLTYPE AddRef() override { return ++m_refCount; }
	ULONG STDMETHODCALLTYPE Release() override {
		if (--m_refCount == 0) { delete this; return 0; }
		return m_refCount;
	}
	
	// �������� COM���α׷����� ���丮�� �ϳ��� Ŭ���� �ν��Ͻ��� �����Ѵ�.
	STDMETHOD(CreateInstance)(IUnknown* pUnkOuter, REFIID riid, void** ppv) override;
	STDMETHOD(LockServer)(BOOL) { return S_OK; }


	HRESULT CreateOther(IOtherObject** ppObj) override;
};

extern "C" HRESULT CreateMyFactory(REFIID riid, void** ppv);
