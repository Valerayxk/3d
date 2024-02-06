// lab1_3d.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "lab1_3d.h"
#include "math.h"

#define MAX_LOADSTRING 100

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

double people[12][3] = {
    {60, 10, 1},
    {65, 15, 1},
    {60, 20, 1},
    {55, 15, 1},
    {60, 40, 1},
    {60, 25, 1,},
    {70, 35, 1},
    {50, 35, 1},
    {65, 50, 1},
    {70, 50, 1},
    {55, 50, 1},
    {50, 50, 1}
};
double people2[12][3] = {
    {60, 10, 1},
    {65, 15, 1},
    {60, 20, 1},
    {55, 15, 1},
    {60, 40, 1},
    {60, 25, 1,},
    {70, 35, 1},
    {50, 35, 1},
    {65, 50, 1},
    {70, 50, 1},
    {55, 50, 1},
    {50, 50, 1}
};

//уменшение по y в 2 раза
double size[3][3] = {
{1, 0, 0},
{0, 0.5, 0},
{0, 0, 1}
};

//отражение по x
double reflection[3][3] = {
    {1, 0, 0},
    {0, -1, 0},
    {20, 50, 1}
};

//поворот на 45 градусов
double turn[3][3] = {
    {cos(0.785), sin(0.785), 0},
    {-sin(0.785), cos(0.785),0},
    {0, 0, 1}
};

double start[3][3] = {
    {1, 0, 0},
    {0, 1,0},
    {0, 0, 1}
};

//void Matrix(double AffinMatrix[3][3]) {
//    double time_matrix[12][3] = { 0 }; // Временный массив для хранения результатов
//
//    for (int k = 0; k < 12; k++) {
//        for (int i = 0; i < 3; i++) {
//            double sum = 0;
//            for (int j = 0; j < 3; j++) {
//                sum += people2[k][j] * AffinMatrix[j][i];
//            }
//
//            time_matrix[k][i] = sum;
//        }
//    }
//
//    // Обновление оригинального массива после всех расчетов
//  /*  for (int k = 0; k < 12; k++) {
//        for (int i = 0; i < 3; i++) {
//            people2[k][i] = tmp[k][i];
//        }
//    }*/
//
//    return;
//
//}

void Matrix(double AffinMatrix[3][3]) {

    double time_matrix = 0;

    for (int k = 0; k < 12; k++) {
        for (int i = 0; i < 3; i++) {

            for (int j = 0; j < 3; j++) {
                time_matrix += people2[k][j] * AffinMatrix[j][i];
            }

            people[k][i] = time_matrix;
            time_matrix = 0;
        }
    }

    return;
}


// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Разместите код здесь.

    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_LAB13D, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAB13D));

    MSG msg;

    // Цикл основного сообщения:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  ФУНКЦИЯ: MyRegisterClass()
//
//  ЦЕЛЬ: Регистрирует класс окна.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAB13D));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_LAB13D);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   ЦЕЛЬ: Сохраняет маркер экземпляра и создает главное окно
//
//   КОММЕНТАРИИ:
//
//        В этой функции маркер экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ЦЕЛЬ: Обрабатывает сообщения в главном окне.
//
//  WM_COMMAND  - обработать меню приложения
//  WM_PAINT    - Отрисовка главного окна
//  WM_DESTROY  - отправить сообщение о выходе и вернуться
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Разобрать выбор в меню:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;

            case  ID_size:
                Matrix(size);
                InvalidateRect(hWnd, NULL, TRUE);
                UpdateWindow(hWnd);
                break;
            case  ID_reflection:
                Matrix(reflection);
                InvalidateRect(hWnd, NULL, TRUE);
                UpdateWindow(hWnd);
                break;
            case  ID_turn:
                Matrix(turn);
                InvalidateRect(hWnd, NULL, TRUE);
                UpdateWindow(hWnd);
                break;
            case  ID_start:
                Matrix(start);
                InvalidateRect(hWnd, NULL, TRUE);
                UpdateWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Добавьте сюда любой код прорисовки, использующий HDC...

            MoveToEx(hdc, people[0][0], people[0][1],0);
            LineTo(hdc, people[1][0], people[1][1]);
            LineTo(hdc, people[2][0], people[2][1]);
            LineTo(hdc, people[3][0], people[3][1]);
            LineTo(hdc, people[0][0], people[0][1]);
            MoveToEx(hdc, people[2][0], people[2][1], 0);
            LineTo(hdc, people[4][0], people[4][1]);
            MoveToEx(hdc, people[5][0], people[5][1], 0);
            LineTo(hdc, people[6][0], people[6][1]);
            MoveToEx(hdc, people[5][0], people[5][1], 0);
            LineTo(hdc, people[7][0], people[7][1]);
            MoveToEx(hdc, people[4][0], people[4][1], 0);
            LineTo(hdc, people[8][0], people[8][1]);
            LineTo(hdc, people[9][0], people[9][1]);
            MoveToEx(hdc, people[4][0], people[4][1], 0);
            LineTo(hdc, people[10][0], people[10][1]);
            LineTo(hdc, people[11][0], people[11][1]);


           

            EndPaint(hWnd, &ps);
        }

        

        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Обработчик сообщений для окна "О программе".
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
