#include <windows.h>
//./gcc -o minha_janela.exe win.c -mwindows
// Protótipo da função de janela
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

#include <windows.h>
const int WIDTH = 640;
const int HEIGHT = 480;

#include <windows.h>

void draw_cube(HDC hdc, int x, int y, int z, int size)
{
    // Define as coordenadas dos oito vértices do cubo
    int x1 = x;
    int y1 = y;
    int z1 = z;
    int x2 = x + size;
    int y2 = y;
    int z2 = z;
    int x3 = x + size;
    int y3 = y + size;
    int z3 = z;
    int x4 = x;
    int y4 = y + size;
    int z4 = z;
    int x5 = x;
    int y5 = y;
    int z5 = z + size;
    int x6 = x + size;
    int y6 = y;
    int z6 = z + size;
    int x7 = x + size;
    int y7 = y + size;
    int z7 = z + size;
    int x8 = x;
    int y8 = y + size;
    int z8 = z + size;

    // Desenha as 12 linhas que formam as arestas do cubo
    MoveToEx(hdc, x1, y1, NULL);
    LineTo(hdc, x2, y2);
    MoveToEx(hdc, x2, y2, NULL);
    LineTo(hdc, x3, y3);
    MoveToEx(hdc, x3, y3, NULL);
    LineTo(hdc, x4, y4);
    MoveToEx(hdc, x4, y4, NULL);
    LineTo(hdc, x1, y1);
    MoveToEx(hdc, x5, y5, NULL);
    LineTo(hdc, x6, y6);
    MoveToEx(hdc, x6, y6, NULL);
    LineTo(hdc, x7, y7);
    MoveToEx(hdc, x7, y7, NULL);
    LineTo(hdc, x8, y8);
    MoveToEx(hdc, x8, y8, NULL);
    LineTo(hdc, x5, y5);
    MoveToEx(hdc, x1, y1, NULL);
    LineTo(hdc, x5, y5);
    MoveToEx(hdc, x2, y2, NULL);
    LineTo(hdc, x6, y6);
    MoveToEx(hdc, x3, y3, NULL);
    LineTo(hdc, x7, y7);
    MoveToEx(hdc, x4, y4, NULL);
    LineTo(hdc, x8, y8);
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

            draw_cube(hdc,10,10,10,200);
 
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

