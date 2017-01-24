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


HINSTANCE hInst;                                
WCHAR szTitle[MAX_LOADSTRING];                 
WCHAR szWindowClass[MAX_LOADSTRING];           

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

   

    
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_HOMEWORK_TWO, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_HOMEWORK_TWO));

    MSG msg;

   
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


BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; 

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

#define type short 
#define lef 
#define sh 2 
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
int key; 

OPENFILENAME ofn; 
TCHAR NameFile[256] = "MyFile.shf"; 




LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_CHAR: 
				 
		Str[len] = wParam;
		len++; 
		Str[len] = 0; 
					  
		hdc = GetDC(hWnd); 
		SetTextColor(hdc, RGB(0, 0, 0));
		TextOut(hdc, 40, 40, Str, len);
		ReleaseDC(hWnd, hdc);
		break;
	case WM_COMMAND: 
		wmId = LOWORD(wParam); 
		wmEvent = HIWORD(wParam);
		
		switch (wmId) 
		{
		case IDM_ABOUT:  
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		case ID_32771:
			ZeroMemory(&ofn, sizeof(ofn));
			ofn.lStructSize = sizeof(ofn);
			ofn.hwndOwner = hWnd;
			ofn.lpstrFile = NameFile;
			ofn.lpstrFile[0] = '\0';
			ofn.nMaxFile = 255;
			ofn.lpstrFilter = "Øèôðîâàííûå ôàéëû (*.shf)\0*.shf\0Âñå ôàéëû\0*.*\0"; 
			ofn.nFilterIndex = 0;
			ofn.lpstrFileTitle = NULL;
			ofn.nMaxFileTitle = 0;
			ofn.lpstrInitialDir = NULL;
			ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
			ofn.lpstrDefExt = "shf";

			if (GetOpenFileName(&ofn)) 
			{
				
				if (DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, MyDialog) == IDOK)
				{
					FILE *pF1;
					char Shifr[512]; 
					pF1 = fopen(NameFile, "rb"); 
					if (pF1 == 0)
					{
						MessageBox(hWnd, "Error opening the file. Perhaps the file does not exist", "Ñîîáùåíèå îá îøèáêå", MB_OK | MB_ICONHAND);
						return TRUE;
					}
					fread(&len, sizeof(int), 1, pF1);
					fread(Shifr, sizeof(char), len, pF1); 
					fclose(pF1);
					shifrDeshifr(Shifr, Str, len, key, 2);
					Str[len] = 0;
					InvalidateRect(hWnd, 0, TRUE);
				}
				else MessageBox(hWnd, "Äàííûå íå ïðî÷èòàíû. Êëþ÷ íå ââåäåí!!", "Ñîîáùåíèå", MB_OK | MB_ICONHAND);
			}


			break;
		case ID_32772: 
			ofn.lStructSize = sizeof(OPENFILENAME);
			ofn.hwndOwner = hWnd;  
			ofn.lpstrFilter = "Øèôðîâàííûå ôàéëû (*.shf)\0*.shf\0Âñå ôàéëû\0*.*\0"; 
			ofn.lpstrFile = NameFile;  
			ofn.nMaxFile = 255;
			ofn.lpstrFileTitle = NULL;
			ofn.nMaxFileTitle = 0;
			ofn.lpstrInitialDir = NULL;
			ofn.Flags = OFN_SHOWHELP | OFN_OVERWRITEPROMPT;
			ofn.lpstrTitle = NULL;
			ofn.lpstrDefExt = "shf";
			if (GetSaveFileName(&ofn)) 
			{
				
				if (DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, MyDialog) == IDOK)
				{
					char Shifr[512]; 
					shifrDeshifr(Str, Shifr, len, key, 1); 

					FILE *pF1;  
					pF1 = fopen(NameFile, "wb"); 
					if (pF1 == 0)
					{
						MessageBox(hWnd, "Îøèáêà îòêðûòèÿ ôàéëà.", "Ñîîáùåíèå îá îøèáêå", MB_OK | MB_ICONHAND);
						return TRUE;
					}
					fwrite(&len, sizeof(int), 1, pF1); 
					fwrite(Shifr, sizeof(char), len, pF1); 
					fclose(pF1);
					MessageBox(hWnd, "Äàííûå óñïåøíî ñîõðàíåíû.", "Ñîîáùåíèå", MB_OK | MB_ICONINFORMATION);
				}
				else MessageBox(hWnd, "Äàííûå íå ñîõðàíåíû. Êëþ÷ íå ââåäåí!!", "Ñîîáùåíèå", MB_OK | MB_ICONHAND);
			}

			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		
		SetTextColor(hdc, RGB(0, 0, 0));
		TextOut(hdc, 40, 40, Str, len); 
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
			if (LOWORD(wParam) == IDOK) 
			{
				char Str[32];
				SendDlgItemMessage(hDlg, IDC_EDIT1, WM_GETTEXT, 31, (LPARAM)Str); 
																				 
				if (sscanf(Str, "%d", &key) < 1)
				{
					MessageBox(hDlg, "Íåâåðíûé ôîðìàò êëþ÷à. Êëþ÷ äîëæåí áûòü öåëûì ÷èñëîì", "Ñîîáùåíèå î íåâåðíîì ôîðìàòå êëþ÷à", MB_OK | MB_ICONHAND);
					return (INT_PTR)TRUE; 

				}

			}
			EndDialog(hDlg, LOWORD(wParam)); 
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

