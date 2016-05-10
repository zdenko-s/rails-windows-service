#pragma once

#include <windows.h>

namespace ProcessHelper
{
	//************************************
	// Method:    CreateConsoleProcess
	// FullName:  ProcessHelper::CreateConsoleProcess
	// Access:    public 
	// Returns:   DWORD
	// Qualifier:
	// Read configuration data from ini file and delegate invocation.
	//************************************
	DWORD CreateConsoleProcess();
	//************************************
	// Method:    CreateConsoleProcess
	// FullName:  ProcessHelper::CreateConsoleProcess
	// Access:    public 
	// Returns:   int
	// Qualifier:
	// Parameter: WCHAR * cmdLine
	// Parameter: WCHAR * workingDir
	// Creates process and redirects STDOU to file
	//************************************
	int CreateConsoleProcess(WCHAR* cmdLine, WCHAR* workingDir);
	//************************************
	// Method:    SendCtrlC
	// FullName:  ProcessHelper::SendCtrlC
	// Access:    public 
	// Returns:   void
	// Qualifier:
	// Sends Ctrl-C to created process
	//************************************
	void SendCtrlC();
};

