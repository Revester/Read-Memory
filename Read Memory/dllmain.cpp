#include <Windows.h>

#include "CheatEngineSDK.h"

#define CESDK_VERSION 6;
int selfid;
ExportedFunctions Exported;

BOOL __stdcall MyReadProcessMemory(HANDLE hProcess, LPCVOID lpBaseAddress, LPVOID lpBuffer, SIZE_T nSize, SIZE_T* lpNumberOfBytesRead) {
    return ReadProcessMemory(hProcess, lpBaseAddress, lpBuffer, nSize, lpNumberOfBytesRead);
}

typedef struct PluginVersion {
    unsigned int version;
    char* pluginname;
}* PPluginVersion;

BOOL __stdcall CEPlugin_GetVersion(PPluginVersion pv, int sizeofpluginversion) {
    pv->version = CESDK_VERSION;
    pv->pluginname = "C++ Example (SDK version 4: 6.0+)";
    return true;
}

BOOL __stdcall CEPlugin_InitializePlugin(PExportedFunctions ef, int pluginid) {
    selfid = pluginid;

    //copy the EF list to Exported
    Exported = *ef; //Exported is defined in the .h

    if(Exported.sizeofExportedFunctions != sizeof(Exported))
        return FALSE;

    *ef->ReadProcessMemory = MyReadProcessMemory;

    Exported.ShowMessage("The \"Example C++\" plugin got enabled");

    return true;
}

BOOL __stdcall CEPlugin_DisablePlugin(void) {
    return true;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    switch(ul_reason_for_call) {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}
