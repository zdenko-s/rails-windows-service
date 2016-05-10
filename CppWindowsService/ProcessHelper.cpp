#include "ProcessHelper.h"

#define INI_FILE_SECTION L"Command"
#define CMD_LINE L"CommandLine"
#define WORKING_DIR L"WorkingDir"

namespace ProcessHelper
{

	PROCESS_INFORMATION pi;
	HANDLE hOutFile = INVALID_HANDLE_VALUE;

	DWORD CreateConsoleProcess()
	{
		// Read settings from .ini file
		wchar_t fileName[MAX_PATH];
		wchar_t cmdLine[MAX_PATH];
		wchar_t workingDir[MAX_PATH];
		workingDir[0] = cmdLine[0] = 0;
		if (GetModuleFileName(nullptr, fileName, MAX_PATH))
		{
			// Append .ini to the module name
			wcscat(fileName, L".ini");
			//WritePrivateProfileString(L"Rails", L"key", L"value", fileName);
			GetPrivateProfileString(INI_FILE_SECTION, CMD_LINE, nullptr, cmdLine, MAX_PATH, fileName);
			GetPrivateProfileString(INI_FILE_SECTION, WORKING_DIR, nullptr, workingDir, MAX_PATH, fileName);
			CreateConsoleProcess(cmdLine, workingDir);
		}
		return 0;
	}

	int CreateConsoleProcess(WCHAR* cmdLine, WCHAR* workingDir)
	{
		//Create inheritable STD handles
		SECURITY_ATTRIBUTES sa;
		sa.nLength = sizeof(sa);
		sa.lpSecurityDescriptor = NULL;
		sa.bInheritHandle = TRUE;
		// Create file where Process STDOUT will be redirected
		hOutFile = CreateFile(L"stdout.log",
			FILE_APPEND_DATA, FILE_SHARE_WRITE | FILE_SHARE_READ, &sa,
			OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		// Startup info: No window, Use std handles
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
		// Process ceation
		ret = CreateProcess(NULL, cmdLine, NULL, NULL, TRUE, flags, NULL, workingDir, &si, &pi);
		if (ret)
		{
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
