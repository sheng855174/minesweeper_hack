#include <windows.h>
#include <iostream>
#include <inttypes.h>
#include <stdint.h>
#include <string> 
#include "MyForm.h"

void HackThead(HMODULE hModule) {
	char msg_buff[4096];
	System::String^ msg;

	Project1::MyForm^ form = gcnew Project1::MyForm();
	form->appendLog("dll injection 成功.\n");

	//取得基址
	uintptr_t moduleBase = (uintptr_t)GetModuleHandle(L"Minesweeper.exe");
	moduleBase = (uintptr_t)GetModuleHandle(NULL);

	snprintf(msg_buff, sizeof(msg_buff), "%016" PRIxPTR "\n", (uintptr_t)moduleBase);
	msg = gcnew System::String(msg_buff);
	form->appendLog("Minesweeper.exe 地址 : " + msg);

	form->ShowDialog();
}



BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD ul_reason_for_call,
	LPVOID lpReserved)
{
	switch (ul_reason_for_call) {
		case DLL_PROCESS_ATTACH:
			CloseHandle(CreateThread(0, 0, (LPTHREAD_START_ROUTINE)HackThead, hModule, 0, 0));
			break;
		case DLL_THREAD_ATTACH:
			break;
		case DLL_THREAD_DETACH:
			break;
		case DLL_PROCESS_DETACH:
			break;
	}
	return true;
}