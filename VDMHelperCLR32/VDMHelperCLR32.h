// VDMHelperCLR32.h

#pragma once

#include "../VDMHelper32/VDMHelperAPI.h"


using namespace System;
using namespace VDMHelperCLR::Common;

namespace VDMHelperCLR {

	public ref class VdmHelper : public IVdmHelper
	{
	public:
		VdmHelper();
		~VdmHelper();

		virtual bool Init();
		virtual bool DeInit();
		virtual void MoveWindowToDesktop(IntPtr topLevelWindow, Guid desktopId);

	private:
		UINT RequestMoveWindowToDesktopMessage;

		HMODULE hvdm;
		decltype(::VDMHookProc1)* VDMHookProc1;
		decltype(::VDMHookProc2)* VDMHookProc2;
		decltype(::VDMAllocGuid)* VDMAllocGuid;
		decltype(::VDMReleaseGuid)* VDMReleaseGuid;

		HHOOK hCWPHook;
		HHOOK hGMHook;
	};
}
