#include <windows.h>
#include <stdio.h>

// Control IDs
#define ID_INPUT_A     1
#define ID_INPUT_B     2
#define ID_BTN_ADD     3
#define ID_BTN_SUB     4
#define ID_BTN_MUL     5
#define ID_BTN_DIV     6
#define ID_RESULT      7

HWND hInputA, hInputB, hResult;

void calculate(HWND hwnd, char op) {
    char bufA[50], bufB[50], bufResult[100];
    GetWindowText(hInputA, bufA, 50);
    GetWindowText(hInputB, bufB, 50);

    int a = atoi(bufA);
    int b = atoi(bufB);

    switch (op) {
        case '+': sprintf(bufResult, "%d + %d = %d", a, b, a + b); break;
        case '-': sprintf(bufResult, "%d - %d = %d", a, b, a - b); break;
        case '*': sprintf(bufResult, "%d * %d = %d", a, b, a * b); break;
        case '/':
            if (b == 0)
                sprintf(bufResult, "Error: Can't divide by zero!");
            else
                sprintf(bufResult, "%d / %d = %d", a, b, a / b);
            break;
    }
    SetWindowText(hResult, bufResult);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_CREATE:
            CreateWindow("STATIC", "Number 1:", WS_VISIBLE | WS_CHILD,
                20, 20, 80, 20, hwnd, NULL, NULL, NULL);
            hInputA = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER,
                110, 18, 150, 24, hwnd, (HMENU)ID_INPUT_A, NULL, NULL);

            CreateWindow("STATIC", "Number 2:", WS_VISIBLE | WS_CHILD,
                20, 60, 80, 20, hwnd, NULL, NULL, NULL);
            hInputB = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER,
                110, 58, 150, 24, hwnd, (HMENU)ID_INPUT_B, NULL, NULL);

            CreateWindow("BUTTON", "+", WS_VISIBLE | WS_CHILD,
                20, 100, 60, 30, hwnd, (HMENU)ID_BTN_ADD, NULL, NULL);
            CreateWindow("BUTTON", "-", WS_VISIBLE | WS_CHILD,
                90, 100, 60, 30, hwnd, (HMENU)ID_BTN_SUB, NULL, NULL);
            CreateWindow("BUTTON", "*", WS_VISIBLE | WS_CHILD,
                160, 100, 60, 30, hwnd, (HMENU)ID_BTN_MUL, NULL, NULL);
            CreateWindow("BUTTON", "/", WS_VISIBLE | WS_CHILD,
                230, 100, 60, 30, hwnd, (HMENU)ID_BTN_DIV, NULL, NULL);

            CreateWindow("STATIC", "Result:", WS_VISIBLE | WS_CHILD,
                20, 150, 60, 20, hwnd, NULL, NULL, NULL);
            hResult = CreateWindow("STATIC", "—", WS_VISIBLE | WS_CHILD,
                90, 150, 200, 20, hwnd, (HMENU)ID_RESULT, NULL, NULL);
            break;

        case WM_COMMAND:
            switch (LOWORD(wParam)) {
                case ID_BTN_ADD: calculate(hwnd, '+'); break;
                case ID_BTN_SUB: calculate(hwnd, '-'); break;
                case ID_BTN_MUL: calculate(hwnd, '*'); break;
                case ID_BTN_DIV: calculate(hwnd, '/'); break;
            }
            break;

        case WM_DESTROY:
            PostQuitMessage(0);
            break;
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine, int nCmdShow) {
    WNDCLASS wc = {0};
    wc.lpfnWndProc   = WndProc;
    wc.hInstance     = hInstance;
    wc.lpszClassName = "CalcWindow";
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    RegisterClass(&wc);

    HWND hwnd = CreateWindow("CalcWindow", "Calculator",
        WS_OVERLAPPEDWINDOW, 100, 100, 320, 220,
        NULL, NULL, hInstance, NULL);

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}