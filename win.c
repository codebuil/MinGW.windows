#include <windows.h>
//./gcc -o minha_janela.exe win.c -mwindows
// Protótipo da função de janela
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

#include <windows.h>
const int WIDTH = 640;
const int HEIGHT = 480;

void DesenharLinha(HDC hdc, int x1, int y1, int x2, int y2) {
    MoveToEx(hdc, x1, y1, NULL);
    LineTo(hdc, x2, y2);
}

// Protótipo da função de janela
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

// Função principal
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // Define as informações da janela
    const char* CLASS_NAME = "MinhaJanela";
    const char* WINDOW_NAME = "Minha Janela";
    
    // Registra a classe da janela
    WNDCLASS wc = {0};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hbrBackground = (HBRUSH) (COLOR_WINDOW+1); // Define a cor de fundo da janela como azul
    RegisterClass(&wc);

    // Cria a janela
    HWND hwnd = CreateWindow(CLASS_NAME, WINDOW_NAME, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, WIDTH, HEIGHT, NULL, NULL, hInstance, NULL);

    // Exibe a janela
    ShowWindow(hwnd, nCmdShow);

    // Loop principal da janela
    MSG msg = {0};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    // Retorna 0
    return 0;
}

// Função de janela
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    int i=0,x,y;
    switch (msg) {
        case WM_PAINT: {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);
            RECT rc;
            GetClientRect(hwnd, &rc);
            HBRUSH hBrush = CreateSolidBrush(RGB(0, 0, 255)); // Cria uma escova sólida com a cor azul
            FillRect(hdc, &rc, hBrush); // Pinta o retângulo com a cor azul
            SelectObject(hdc, GetStockObject(BLACK_PEN));

        for (i = 0; i <= WIDTH; i += 10)
        {
            MoveToEx(hdc, i, 0, NULL);
            LineTo(hdc, i, HEIGHT);
        }

        for (i = 0; i <= HEIGHT; i += 10)
        {
            MoveToEx(hdc, 0, i, NULL);
            LineTo(hdc, WIDTH, i);
        }
 
            DeleteObject(hBrush); // Libera a memória da escova
            EndPaint(hwnd, &ps);
            break;
        }
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

