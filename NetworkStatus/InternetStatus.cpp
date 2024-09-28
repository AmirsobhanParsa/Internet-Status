#include "icmplib.h"
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <string>

using namespace std;

wstring GetCurrentPath() {
    TCHAR buffer[MAX_PATH] = { 0 };
    GetModuleFileName(NULL, buffer, MAX_PATH);
    wstring::size_type pos = wstring(buffer).find_last_of(L"\\/");
    return wstring(buffer).substr(0, pos);
}

int main()
{
    //Hide Console
    ShowWindow(GetConsoleWindow(), SW_HIDE);

    //Initialize Tray Icon
    NOTIFYICONDATAA nid = {};
    AllocConsole();
    HWND h = FindWindowA("ConsoleWindowClass", NULL);
    nid.cbSize = sizeof(nid);
    nid.hWnd = h;
    nid.uFlags = NIF_ICON | NIF_TIP;
    memcpy(nid.szTip, "Internet Status", 128);
    Shell_NotifyIconA(NIM_ADD, &nid);

    //Ping Address
    string address = "8.8.8.8";

     while(true){
         try {
             auto result = icmplib::Ping(address, ICMPLIB_TIMEOUT_1S);
             if (result.response != icmplib::PingResponseType::Success) {
                 //No Internet Connection
                 wstring p = GetCurrentPath() + L"\\Disconnect.ico";
                 nid.hIcon = (HICON)LoadImage(NULL, p.c_str(), IMAGE_ICON, 0, 0, LR_LOADFROMFILE | LR_SHARED);
                 Shell_NotifyIconA(NIM_MODIFY, &nid);
                 DestroyIcon(nid.hIcon);
             }
             else {
                 if (result.delay < 60)
                 {
                     //DarkGreen
                     wstring p = GetCurrentPath() + L"\\DarkGreen.ico";
                     nid.hIcon = (HICON)LoadImage(NULL, p.c_str(), IMAGE_ICON, 0, 0, LR_LOADFROMFILE | LR_SHARED);
                     Shell_NotifyIconA(NIM_MODIFY, &nid);
                     DestroyIcon(nid.hIcon);
                 }
                 else if (result.delay < 200) {
                     //BrightGreen
                     wstring p = GetCurrentPath() + L"\\BrightGreen.ico";
                     nid.hIcon = (HICON)LoadImage(NULL, p.c_str(), IMAGE_ICON, 0, 0, LR_LOADFROMFILE | LR_SHARED);
                     Shell_NotifyIconA(NIM_MODIFY, &nid);
                     DestroyIcon(nid.hIcon);
                 }
                 else if (result.delay < 400) {
                     //Yellow
                     wstring p = GetCurrentPath() + L"\\Yellow.ico";
                     nid.hIcon = (HICON)LoadImage(NULL, p.c_str(), IMAGE_ICON, 0, 0, LR_LOADFROMFILE | LR_SHARED);
                     Shell_NotifyIconA(NIM_MODIFY, &nid);
                     DestroyIcon(nid.hIcon);
                 }
                 else
                 {
                     //Red
                     wstring p = GetCurrentPath() + L"\\Red.ico";
                     nid.hIcon = (HICON)LoadImage(NULL, p.c_str(), IMAGE_ICON, 0, 0, LR_LOADFROMFILE | LR_SHARED);
                     Shell_NotifyIconA(NIM_MODIFY, &nid);
                     DestroyIcon(nid.hIcon);
                 }
             }
             Sleep(2000); 
         }
         catch (const exception& e) {
             // Do nothing  
         }
    }  
}