// VDMHelper.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"

#include "VDMHelper.h"

namespace VDM
{
	
	bool Helper::init()
	{
		mMoveWindowToDesktopMessage = RegisterWindowMessage(RequestMoveWindowToDesktop);
		// initialize com
		CoInitialize(nullptr);
		

		CComPtr<IServiceProvider> pServiceProvider;
		auto hr = CoCreateInstance(CLSID_ImmersiveShell, nullptr, CLSCTX_LOCAL_SERVER, IID_PPV_ARGS(&pServiceProvider));
		if (FAILED(hr)) return false;
		hr = pServiceProvider->QueryService(__uuidof(IVirtualDesktopManager), &mpVdm);
		if(FAILED(hr)) return false;
		return true;
	}

	bool Helper::deinit()
	{
		if(mpVdm)
		{
			mpVdm->Release();
			mpVdm = nullptr;
		}
		CoUninitialize();
		return true;
	}

	bool Helper::process(HWND hwnd, UINT msg, ::WPARAM wParam, ::LPARAM lParam)
	{
		if (msg != mMoveWindowToDesktopMessage) return false;
		if (!mpVdm) return false;
		mpVdm->MoveWindowToDesktop(hwnd, *reinterpret_cast<GUID*>(lParam));
		return true;
	}
}