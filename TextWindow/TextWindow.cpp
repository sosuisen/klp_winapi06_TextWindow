#include <windows.h>
#include <string>

LRESULT CALLBACK WndProc(
    HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int APIENTRY wWinMain(HINSTANCE hInstance,
    HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
    TCHAR szAppName[] = L"TextWindow";
    WNDCLASS wc;
    HWND hwnd;
    MSG msg;

    // ウィンドウクラスの属性を設定
    wc.style = CS_HREDRAW | CS_VREDRAW; // リサイズ時に WM_PAINTメッセージ送信
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
        szAppName,
        // L"TextWindow",
        L"真空溶媒",
        WS_OVERLAPPEDWINDOW,
        50, 50,
        400, 300,
        NULL, NULL,
        hInstance, NULL);

    if (!hwnd) return 0;

    // ウィンドウを表示
    ShowWindow(hwnd, nCmdShow);

    /*
    std::wstring str = L"GetDCでこんにちは";
    HDC hdc = GetDC(hwnd);
    // HDC hdc = GetDC(GetDesktopWindow());
    TextOut(hdc, 10, 50, str.c_str(), str.length());
    ReleaseDC(hwnd, hdc);
    */

    // return 0;

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
    //std::wstring str = L"こんにちは、KCG!";
    std::wstring str = L"やあ　こんにちは\nいや　いゝおてんきですな\nどちらへ　ごさんぽですか";

    // デバッグ情報表示用
    wchar_t format[] = L"%d,%d,%d,%d\n";
    wchar_t* buf = new wchar_t[18]; // (8文字+終端ヌル1文字)x2バイト。いわゆるASCIIコードの範囲はUTF16でも1文字2バイトに収まる

    RECT rc;

    switch (uMsg) {
    case WM_PAINT:
        PAINTSTRUCT paint;
        GetClientRect(hwnd, &rc);
        hdc = BeginPaint(hwnd, &paint);

//        TextOut(hdc, 10, 10, str.c_str(), str.length());
        SetTextColor(hdc, RGB(255, 155, 0));
        DrawText(hdc,
            str.c_str(),
            -1,
            &rc,
            DT_RIGHT);


        // 更新領域の左上座標と幅、高さを表示
        // x, y, width, height
        swprintf_s(buf, 18, format,
            paint.rcPaint.left,
            paint.rcPaint.top,
            paint.rcPaint.right- paint.rcPaint.left,
            paint.rcPaint.bottom - paint.rcPaint.top);
        OutputDebugString(buf);

        EndPaint(hwnd, &paint);
        return 0;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}