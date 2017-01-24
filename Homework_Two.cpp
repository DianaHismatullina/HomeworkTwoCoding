// Homework_Two.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Homework_Two.h"
#include <windows.h>
#include <math.h> 
#include <iostream> 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <fstream>

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
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

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_HOMEWORK_TWO, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_HOMEWORK_TWO));

    MSG msg;

    // Main message loop:
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
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_HOMEWORK_TWO));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_HOMEWORK_TWO);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

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

#define type short //тип переменной, размер которого совпадает с размером обрабатываемого блока
#define lef // сдвил влево(lef) или вправо(rig)
#define sh 2 //сдвиг на n бит в нужную сторону
using namespace std;



#ifdef rig;
#endif
#ifdef lef
#define x1 true
#define x2 false
#define sd sizeof(type)
#endif




unsigned right(unsigned a, int n)
{
	unsigned maska = 0;
	for (int i = 0; i<3; i++)
	{
		maska <<= 1;
		maska += 1;
	}
	unsigned b = a & maska;
	b <<= (n - 3);
	a >>= 3;
	return a | b;
}

unsigned left(unsigned a, int n)
{
	unsigned maska = 0;
	for (int i = 0; i<3; i++)
	{
		maska <<= 1;
		maska += 1;
	}
	maska <<= (n - 3);

	unsigned b = a & maska;
	b >>= (n - 3);
	a <<= 3;
	return a | b;
}

void shifrDeshifr(char *in, char *out, int n, int key, int reg)
{
	srand(key);
	unsigned short a, b, gamma;
	int l;
	for (int i = 0; i < n; i += 2)
	{
		if (n % 2 != 0 && i == n - 1)
		{
			a = 0;
			l = 1;

		}
		else l = 2;
		memcpy(&a, in + i, l);
		if (reg == 2)
			a = right(a, l * 8);
		gamma = rand();
		b = gamma ^ a;
		if (reg == 1) b = left(b, l * 8);
		memcpy(out + i, &b, l);

	}
}


char Str[512];
int len = 0;
int key; // Сюда запишем значение секретного ключа

OPENFILENAME ofn; // Структура для стандартных окон "Открыть файл" и "Сохранить"
TCHAR NameFile[256] = "MyFile.shf"; // Сюда будет записано имя файла



//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_CHAR: // Сообщение ввод символа
				  // Записываем символ в строку
		Str[len] = wParam;
		len++; // Длина строки увеличивается на 1
		Str[len] = 0; // Строка заканчивается символом с кодом 0
					  // Вывод строки на экран
		hdc = GetDC(hWnd); // Получаем контекст устройства
		SetTextColor(hdc, RGB(0, 0, 0));
		TextOut(hdc, 40, 40, Str, len); // Вывод строки
		ReleaseDC(hWnd, hdc); // Освобождаем контекст устройства
		break;
	case WM_COMMAND: // Сообщение от выбора элемента меню
		wmId = LOWORD(wParam); // Получаем идентификатор (номер) элемента меню
		wmEvent = HIWORD(wParam);
		// Разобрать выбор в меню:
		switch (wmId) // Обработка отдельных элементов меню
		{
		case IDM_ABOUT: // О программе 
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT: // Выход
			DestroyWindow(hWnd);
			break;
		case ID_32771: // Открыть файл
			ZeroMemory(&ofn, sizeof(ofn));
			ofn.lStructSize = sizeof(ofn);
			ofn.hwndOwner = hWnd;
			ofn.lpstrFile = NameFile; // Сюда будет записано имя файла
									  // Set lpstrFile[0] to '\0' so that GetOpenFileName does not 
									  // use the contents of szFile to initialize itself.
			ofn.lpstrFile[0] = '\0';
			ofn.nMaxFile = 255;
			ofn.lpstrFilter = "Шифрованные файлы (*.shf)\0*.shf\0Все файлы\0*.*\0"; // Фильтр для отображения файлов
			ofn.nFilterIndex = 0;
			ofn.lpstrFileTitle = NULL;
			ofn.nMaxFileTitle = 0;
			ofn.lpstrInitialDir = NULL;
			ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
			ofn.lpstrDefExt = "shf"; // Строка расширение по умолчанию

			if (GetOpenFileName(&ofn)) // Появляется окно "Открыть", функция возвращает истинно, если нажата кнопка Открыть
			{
				// Отображаем окно для ввода ключа
				if (DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, MyDialog) == IDOK)
				{
					FILE *pF1;
					char Shifr[512]; // Зашифрованный текст
					pF1 = fopen(NameFile, "rb"); // Открываем файл для чтения в двоичном режиме
					if (pF1 == 0)
					{
						MessageBox(hWnd, "Error opening the file. Perhaps the file does not exist", "Сообщение об ошибке", MB_OK | MB_ICONHAND);
						return TRUE;
					}
					fread(&len, sizeof(int), 1, pF1); // Читаем Размер данных в байтах
					fread(Shifr, sizeof(char), len, pF1); // Читаем данные из файл
					fclose(pF1);
					shifrDeshifr(Shifr, Str, len, key, 2); // Расшифровываем
					Str[len] = 0; // Строка заканчивается 0
					InvalidateRect(hWnd, 0, TRUE); // Перерисовка окна
				}
				else MessageBox(hWnd, "Данные не прочитаны. Ключ не введен!!", "Сообщение", MB_OK | MB_ICONHAND);
			}


			break;
		case ID_32772: // Сохранить файл
			ofn.lStructSize = sizeof(OPENFILENAME);
			ofn.hwndOwner = hWnd; // родительское окно 
			ofn.lpstrFilter = "Шифрованные файлы (*.shf)\0*.shf\0Все файлы\0*.*\0"; // Маска (фильтр) для отображаемых файлов
			ofn.lpstrFile = NameFile;  // Сюда будет записано полное имя файла
			ofn.nMaxFile = 255;
			ofn.lpstrFileTitle = NULL;//
			ofn.nMaxFileTitle = 0;
			ofn.lpstrInitialDir = NULL;
			ofn.Flags = OFN_SHOWHELP | OFN_OVERWRITEPROMPT;
			ofn.lpstrTitle = NULL;
			ofn.lpstrDefExt = "shf"; // Строка расширение по умолчанию
			if (GetSaveFileName(&ofn)) // Появляется окно "Сохранить", функция возвращает истинно, если нажата кнопка Ok
			{
				// Отображаем окно для ввода ключа
				if (DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, MyDialog) == IDOK)
				{
					char Shifr[512]; // Зашифрованный текст
					shifrDeshifr(Str, Shifr, len, key, 1); // Шифрование данных

					FILE *pF1;  // Файл для сохранения
					pF1 = fopen(NameFile, "wb"); // Для зашифрованных данных файл в двоичном режиме
					if (pF1 == 0)
					{
						MessageBox(hWnd, "Ошибка открытия файла.", "Сообщение об ошибке", MB_OK | MB_ICONHAND);
						return TRUE;
					}
					fwrite(&len, sizeof(int), 1, pF1); // Размер данных в байтах
					fwrite(Shifr, sizeof(char), len, pF1); // Записываем данные в файл
					fclose(pF1);
					MessageBox(hWnd, "Данные успешно сохранены.", "Сообщение", MB_OK | MB_ICONINFORMATION);
				}
				else MessageBox(hWnd, "Данные не сохранены. Ключ не введен!!", "Сообщение", MB_OK | MB_ICONHAND);
			}

			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT: // Перерисовка окна
		hdc = BeginPaint(hWnd, &ps);
		// TODO: добавьте любой код отрисовки...
		SetTextColor(hdc, RGB(0, 0, 255));
		TextOut(hdc, 40, 40, Str, len); // Вывод строки
		EndPaint(hWnd, &ps);
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

// Обработчик сообщений для окна "Ввод секретного ключа.
INT_PTR CALLBACK MyDialog(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			if (LOWORD(wParam) == IDOK) // Читаем секретный ключ из текстового поля
			{
				char Str[32];
				SendDlgItemMessage(hDlg, IDC_EDIT1, WM_GETTEXT, 31, (LPARAM)Str); // Прочитали текст из текстового поля и записали в струку Str
																				  // Читаем данные из строки
				if (sscanf(Str, "%d", &key) < 1) // Целое значение не прочитано из строки
				{
					MessageBox(hDlg, "Неверный формат ключа. Ключ должен быть целым числом", "Сообщение о неверном формате ключа", MB_OK | MB_ICONHAND);
					return (INT_PTR)TRUE; // Выход без закрытия диалогового окна

				}

			}
			EndDialog(hDlg, LOWORD(wParam)); // Закрытие диалогового окна
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

