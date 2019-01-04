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
	for(DWORD i = 0; i < lst->length; i++)
	{
		BYOND::Variables::ListElement* elem = lst->at(i);
		if(elem->type == BYOND::Variables::VariableType::Number)
		{
			MessageBoxA(NULL, std::to_string(elem->asNumber()).c_str(), "value of number element", NULL);
		}
		else if(elem->type == BYOND::Variables::VariableType::String)
		{
			MessageBoxA(NULL, elem->asString(vars).c_str(), "value of string element", NULL);
		}
	}
	
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

