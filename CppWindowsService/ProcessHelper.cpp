#include "ProcessHelper.h"

namespace ProcessHelper
{

	PROCESS_INFORMATION pi;
	const char *msg = "Message\n";
	HANDLE hOutFile = INVALID_HANDLE_VALUE;

	int CreateConsoleProcess(WCHAR* cmdLine, WCHAR* workingDir)
	{
		SECURITY_ATTRIBUTES sa;
		sa.nLength = sizeof(sa);
		sa.lpSecurityDescriptor = NULL;
		sa.bInheritHandle = TRUE;

		hOutFile = CreateFile(L"out.log",
			FILE_APPEND_DATA,
			FILE_SHARE_WRITE | FILE_SHARE_READ,
			&sa,
			OPEN_ALWAYS,
			FILE_ATTRIBUTE_NORMAL,
			NULL);

		STARTUPINFO si;
		BOOL ret = FALSE;
		DWORD flags = CREATE_NO_WINDOW;

		ZeroMemory(&pi, sizeof(PROCESS_INFORMATION));
		ZeroMemory(&si, sizeof(STARTUPINFO));
		si.cb = sizeof(STARTUPINFO);
		si.dwFlags |= STARTF_USESTDHANDLES;
		si.hStdInput = NULL;
		si.hStdError = hOutFile;
		si.hStdOutput = hOutFile;

		ret = CreateProcess(NULL, cmdLine, NULL, NULL, TRUE, flags, NULL, workingDir, &si, &pi);

		if (ret)
		{
			//WaitForSingleObject(pi.hProcess, 10000);
			CloseHandle(pi.hProcess);
			CloseHandle(pi.hThread);
			return 0;
		}
		else
		{
			DWORD dwLastError = GetLastError();
			return dwLastError;
		}
	}

	void SendCtrlC()
	{
		AttachConsole(pi.dwProcessId); // attach to process console
		SetConsoleCtrlHandler(NULL, TRUE); // disable Control+C handling for our app
		GenerateConsoleCtrlEvent(CTRL_C_EVENT, 0); // generate Control+C event
		Sleep(500);
		if (hOutFile != INVALID_HANDLE_VALUE)
			CloseHandle(hOutFile);
		FreeConsole();
	}
}
