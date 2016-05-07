#pragma once

#include <windows.h>

namespace ProcessHelper
{
	int CreateConsoleProcess(WCHAR* cmdLine, WCHAR* workingDir);
	void SendCtrlC();
};

