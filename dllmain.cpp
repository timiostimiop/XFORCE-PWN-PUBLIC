// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"


typedef bool (WINAPI* pAllocConsole)(void);
pAllocConsole oAllocConsole = NULL;

typedef BOOL(WINAPI* pVirtualProtect)(LPVOID, SIZE_T, DWORD, PDWORD);
pVirtualProtect oVirtualProtect = NULL;

bool canpatch = false;
DWORD64 hMod = NULL;

bool WINAPI hkAllocConsole()
{
    canpatch = true;
    return oAllocConsole();
}

BOOL hkVirtualProtect(LPVOID lpAddress, SIZE_T dwSize, DWORD flNewProtect, PDWORD lpflOldProtect)
{
    return oVirtualProtect(lpAddress, dwSize, flNewProtect, lpflOldProtect);
}



BYTE hookBytes[6];
BYTE oBytes[5];

DWORD WINAPI VPRESTORE()
{
        while (TRUE)
        {
            HMODULE ntDll = GetModuleHandleA("ntdll.dll");
            HMODULE k32 = GetModuleHandleA("kernel32.dll");
            HMODULE ntx = GetModuleHandleA("ntdll.dll");

            
            if (ntDll != 0)
            {
                auto vpAddy = (DWORD64)GetProcAddress(ntDll, "NtProtectVirtualMemory");
                auto umVpAddy = (DWORD64)GetProcAddress(k32, "VirtualProtect");
                auto raiseharderror = (DWORD64)GetProcAddress(ntx, "NtRaiseHardError");

            
               

                BYTE restoreUsermodeVP2_W21_H2[] =
                {
                0x48, 0xFF, 0x25, 0xD1, 0x5B
                };

                BYTE restoreUsermodeW10_2004[] =
                {
                0x48, 0xFF, 0x25, 0x19, 0x5c
                };

                BYTE fixRaiseHardError[] =
                {
                0xC3, 0x90, 0x90
                };

                
                WriteProcessMemory(GetCurrentProcess(), (LPVOID)umVpAddy, &restoreUsermodeVP2_W21_H2, sizeof(restoreUsermodeVP2_W21_H2), NULL);
                WriteProcessMemory(GetCurrentProcess(), (LPVOID)raiseharderror, &fixRaiseHardError, sizeof(fixRaiseHardError), NULL);

            }




        }

    Sleep(10);

        return 1;
}

//A
void MemCpy(void* dest, void* src, size_t size)
{
    DWORD oProtect = NULL;
    VirtualProtect(dest, size, PAGE_EXECUTE_READWRITE, &oProtect);
    memcpy(dest, src, size);
    VirtualProtect(dest, size, oProtect, NULL);
}

DWORD WINAPI Init()
{
    AllocConsole();
    freopen("CONOUT$", "w", stdout);

    HMODULE k32 = GetModuleHandleA("kernel32.dll");
    auto umVpAddy = (DWORD64)GetProcAddress(k32, "VirtualProtect");
    ReadProcessMemory(GetCurrentProcess(), (void*)umVpAddy, &oBytes, sizeof(oBytes), NULL);

    printf("your restoreUsermodeVP bytes: \n\n");

    for (int i = 0; i < sizeof(oBytes); i++)
    {
        printf("0x%x\n", oBytes[i]);
    }

    Sleep(4000);
    CreateThread(0, 0, (LPTHREAD_START_ROUTINE)&VPRESTORE, 0, 0, 0);

    if (MH_Initialize() != MH_OK) { printf(("failed to init mh\n")); return false; }

    
    printf("waiting for xforce...\n");

    HMODULE kernelnigga = GetModuleHandleA("kernelbase.dll");
    HMODULE ntnigga = GetModuleHandleA("ntdll.dll");
    HMODULE kernel32nigga = GetModuleHandleA("kernel32.dll");

    auto neger_loch = (DWORD64)GetProcAddress(kernelnigga, "AllocConsole");
    auto addyRtlCopyMemory = (DWORD64)GetProcAddress(ntnigga, "RtlCopyMemory");
    auto addyCT = (DWORD64)GetProcAddress(kernel32nigga, "CreateThread");
    auto addyVirtualProtect = (DWORD64)GetProcAddress(kernelnigga, "VirtualProtect");

    if (neger_loch && addyVirtualProtect)
    {

        MH_CreateHook((DWORD_PTR*)neger_loch, &hkAllocConsole, reinterpret_cast<void**>(&oAllocConsole));
        MH_EnableHook(MH_ALL_HOOKS);

        MH_CreateHook((DWORD_PTR*)addyVirtualProtect, &hkVirtualProtect, reinterpret_cast<void**>(&oVirtualProtect));
        MH_EnableHook(MH_ALL_HOOKS);


        auto nAddy = (DWORD64)GetProcAddress(kernelnigga, "VirtualProtect");

        ReadProcessMemory(GetCurrentProcess(), (void*)nAddy, hookBytes, sizeof(hookBytes), NULL);
    }

    DWORD64 addr1 = NULL;

    while (addr1 == 0)
    {
        addr1 = (DWORD64)GetModuleHandleA("xf.dll");
        hMod = (DWORD64)GetModuleHandleA("xf.dll");
        Sleep(1);
    }



    printf("waiting for continue bool...\n");

    while (!canpatch)
    {
        Sleep(1);
    }

    if (GetModuleHandleA("xf.dll") == 0)
    {
        printf("mod is not xforce bru\nexiting...\n");
        Sleep(5000);
        exit(0x0);
    }
    printf("patching...\n");


    //  DWORD ADDRESS_000 = (DWORD64)hMod + 0x2CC03E;
    DWORD64 ADDRESS_00 = (DWORD64)hMod + 0x18F250;
    DWORD64 ADDRESS_01 = (DWORD64)hMod + 0x192D40;
    DWORD64 ADDRESS_02 = (DWORD64)hMod + 0x252E4A;
    DWORD64 ADDRESS_03 = (DWORD64)hMod + 0x2531D0;
    DWORD64 ADDRESS_04 = (DWORD64)hMod + 0x253440;
    DWORD64 ADDRESS_05 = (DWORD64)hMod + 0x254D40;
    DWORD64 ADDRESS_06 = (DWORD64)hMod + 0x255880;
    DWORD64 ADDRESS_07 = (DWORD64)hMod + 0x256F90;
    DWORD64 ADDRESS_08 = (DWORD64)hMod + 0x2588D3;
    DWORD64 ADDRESS_09 = (DWORD64)hMod + 0x258970;
    DWORD64 ADDRESS_10 = (DWORD64)hMod + 0x258C10;
    DWORD64 ADDRESS_11 = (DWORD64)hMod + 0x258CC0;
    DWORD64 ADDRESS_12 = (DWORD64)hMod + 0x258D90;
    DWORD64 ADDRESS_13 = (DWORD64)hMod + 0x2C35C0;
    DWORD64 ADDRESS_14 = (DWORD64)hMod + 0x2C7050;
    DWORD64 ADDRESS_15 = (DWORD64)hMod + 0x2C71FD;
    DWORD64 ADDRESS_16 = (DWORD64)hMod + 0x2CADC0;
    DWORD64 ADDRESS_17 = (DWORD64)hMod + 0x2CB087;
    DWORD64 ADDRESS_18 = (DWORD64)hMod + 0x2CC5E7;
    DWORD64 ADDRESS_19 = (DWORD64)hMod + 0x4EFC75;
    DWORD64 ADDRESS_20 = (DWORD64)hMod + 0x6DC3A0;
    DWORD64 ADDRESS_21 = (DWORD64)hMod + 0x6DED90;
    DWORD64 ADDRESS_22 = (DWORD64)hMod + 0x6E0AC0;
    DWORD64 ADDRESS_23 = (DWORD64)hMod + 0x162FD6E;



    BYTE Patch00[] = {
0xC3, 0x90
    };

    BYTE Patch0[] = {
0xC3, 0x90, 0x90, 0x90, 0x90
    };

    BYTE Patch1[] = {
0xC3, 0x90, 0x90, 0x90, 0x90
    };
    BYTE Patch2[] = {
0xeb
    };
    BYTE Patch3[] = {
0xC3, 0x90, 0x90, 0x90, 0x90
    };
    BYTE Patch4[] = {
0xC3, 0x90, 0x90, 0x90, 0x90
    };
    BYTE Patch5[] = {
0xC3, 0x90, 0x90
    };
    BYTE Patch6[] = {
  0xC3, 0x90
    };
    BYTE Patch7[] = {
0xC3, 0x90
    };
    BYTE Patch8[] = {
0x90,0x90
    };
    BYTE Patch9[] = {
0xC3, 0x90, 0x90
    };
    BYTE Patch10[] = {
0xC3, 0x90, 0x90, 0x90
    };
    BYTE Patch11[] = {
0xC3, 0x90
    };
    BYTE Patch12[] = {
0xC3, 0x90
    };
    BYTE Patch13[] = {
0xC3, 0x90
    };
    BYTE Patch14[] = {
0xC3, 0x90, 0x90
    };
    BYTE Patch15[] = {
0xeb
    };
    BYTE Patch16[] = {
0xB0, 0x01, 0xC3, 0x90, 0x90
    };
    BYTE Patch17[] = {
0x90, 0x90
    };
    BYTE Patch18[] = {
0xeb
    };
    BYTE Patch19[] = {
0xeb
    };
    BYTE Patch20[] = {
0xC3, 0x90, 0x90
    };
    BYTE Patch21[] = {
0xC3, 0x90, 0x90, 0x90, 0x90
    };
    BYTE Patch22[] = {
0xC3, 0x90, 0x90, 0x90, 0x90
    };
    BYTE Patch23[] = {
        0xC3, 0x90, 0x90, 0x90, 0x90
    };

    BYTE Patch25[] = {
   0xC3, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90
    };

    BYTE Patch26[] = {
   0xC3, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90
    };


    HMODULE ntDll = GetModuleHandleA("ntdll.dll");
    auto memcpyAddy = (DWORD64)GetProcAddress(ntDll, "RtlCopyMemory");

    BYTE p[1];
    ReadProcessMemory(GetCurrentProcess(), (LPVOID)memcpyAddy, &p[1], sizeof(p), NULL);
    if (p[1] == 0x48)
    {

        int x = 1;
        // MemCpy((void*)ADDRESS_000, Patch00, sizeof(Patch00));
        MemCpy((void*)ADDRESS_00, Patch0, sizeof(Patch0));
        MemCpy((void*)ADDRESS_01, Patch1, sizeof(Patch1));
        MemCpy((void*)ADDRESS_02, Patch2, sizeof(Patch2));
        MemCpy((void*)ADDRESS_03, Patch3, sizeof(Patch3));
        MemCpy((void*)ADDRESS_04, Patch4, sizeof(Patch4));
        MemCpy((void*)ADDRESS_05, Patch5, sizeof(Patch5));
        MemCpy((void*)ADDRESS_06, Patch6, sizeof(Patch6));
        MemCpy((void*)ADDRESS_07, Patch7, sizeof(Patch7));
        MemCpy((void*)ADDRESS_08, Patch8, sizeof(Patch8));
        MemCpy((void*)ADDRESS_09, Patch9, sizeof(Patch9));
        MemCpy((void*)ADDRESS_10, Patch10, sizeof(Patch10));
        MemCpy((void*)ADDRESS_11, Patch11, sizeof(Patch11));
        MemCpy((void*)ADDRESS_12, Patch12, sizeof(Patch12));
        MemCpy((void*)ADDRESS_13, Patch13, sizeof(Patch13));
        MemCpy((void*)ADDRESS_14, Patch14, sizeof(Patch14));
        MemCpy((void*)ADDRESS_15, Patch15, sizeof(Patch15));
        MemCpy((void*)ADDRESS_16, Patch16, sizeof(Patch16));
        MemCpy((void*)ADDRESS_17, Patch17, sizeof(Patch17));
        MemCpy((void*)ADDRESS_18, Patch18, sizeof(Patch18));
        MemCpy((void*)ADDRESS_19, Patch19, sizeof(Patch19));
        MemCpy((void*)ADDRESS_20, Patch20, sizeof(Patch20));
        MemCpy((void*)ADDRESS_21, Patch21, sizeof(Patch21));
        MemCpy((void*)ADDRESS_22, Patch22, sizeof(Patch22));
        MemCpy((void*)ADDRESS_23, &x, sizeof(x));

        Sleep(15000);
        printf("\n\npatched. greetz - \ntimiostimio#0629\n"); 

    }




    return 1;
}
BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        DisableThreadLibraryCalls(hModule);
        CreateThread(0, 0, (LPTHREAD_START_ROUTINE)&Init, 0, 0, 0);
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

