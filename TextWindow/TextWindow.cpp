#include <windows.h>
#include <string>

LRESULT CALLBACK WndProc(
    HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int APIENTRY wWinMain(HINSTANCE hInstance,
    HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
    TCHAR szAppName[] = L"TestApp";
    WNDCLASS wc;
    HWND hwnd;
    MSG msg;

    // ウィンドウクラスの属性を設定
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = szAppName;

    // ウィンドウクラスを登録
    if (!RegisterClass(&wc)) return 0;

    // ウィンドウを作成
    hwnd = CreateWindow(
        szAppName, L"Title",
        WS_OVERLAPPEDWINDOW,
        50, 50,
        400, 300,
        NULL, NULL,
        hInstance, NULL);

    if (!hwnd) return 0;

    // ウィンドウを表示
    ShowWindow(hwnd, nCmdShow);

    // ウィンドウを再描画
    UpdateWindow(hwnd);

    std::wstring str = L"GetDCでこんにちは";
    HDC hdc;
    // Windows Vista 以降は、ウィンドウの重なりでは WM_PAINTが呼ばれないので、消えない
    // https://learn.microsoft.com/en-us/windows/win32/learnwin32/the-desktop-window-manager?redirectedfrom=MSDN
    hdc = GetDC(hwnd);
    TextOut(hdc, 10, 50, str.c_str(), str.length());
    //    Rectangle(hdc, 50, 50, 200, 150);  // 描画

    ReleaseDC(hwnd, hdc);

    while (GetMessage(&msg, NULL, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam;
}

LRESULT CALLBACK WndProc(
    HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    std::wstring str = L"こんにちは、KCG!";

    switch (uMsg) {
    case WM_PAINT:
        PAINTSTRUCT paint;
        hdc = BeginPaint(hwnd, &paint);
        TextOut(hdc, 10, 10, str.c_str(), str.length());
        EndPaint(hwnd, &paint);
        return 0;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}