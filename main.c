#include <windows.h>

HHOOK hHook;

LRESULT CALLBACK MouseProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode == HC_ACTION) {
        MSLLHOOKSTRUCT *pMouseStruct = (MSLLHOOKSTRUCT *)lParam;
        if (pMouseStruct != NULL && wParam == WM_MOUSEWHEEL) {
            INPUT inputs[2] = {};

            // Simulate key press
            inputs[0].type = INPUT_KEYBOARD;
            inputs[0].ki.wVk = VK_SPACE;

            // Simulate key release
            inputs[1].type = INPUT_KEYBOARD;
            inputs[1].ki.wVk = VK_SPACE;
            inputs[1].ki.dwFlags = KEYEVENTF_KEYUP;

            SendInput(2, inputs, sizeof(INPUT));
            return 1;
        }
    }
    return CallNextHookEx(hHook, nCode, wParam, lParam);
}

int main() {
    HINSTANCE hInstance = GetModuleHandle(NULL);
    hHook = SetWindowsHookEx(WH_MOUSE_LL, MouseProc, hInstance, 0);
    if (!hHook) {
        return 1;
    }

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    UnhookWindowsHookEx(hHook);
    return 0;
}