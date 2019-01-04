// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
#include "BYOND.h"
#define msg(x) MessageBoxA(NULL, x, "message", NULL)

void test_run()
{
	BYOND::Variables vars;
	if(!vars.GetFunctionPointers())
	{
		msg("Failed to get all function pointers!");
		return;
	}
	vars.GenerateStringTable();
	BYOND::Variables::ByondList* lst = vars.getListPointer(2);
	BYOND::Variables::ListElement* elem = lst->elements;
	elem++;
	MessageBoxA(NULL, std::to_string(Pocket::DwordToFloat(elem->value)).c_str(), "value of list element", NULL);
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
		DWORD dwThreadId;
		CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)&test_run, NULL, NULL, &dwThreadId);
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

