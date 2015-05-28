#define UNICODE
#include <windows.h>
#include <math.h>
#include "resource.h"

TCHAR szClassName[]=TEXT("KitchenTimer");

LRESULT CALLBACK WndProc(HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	static HFONT hFont;
	static HWND hButton[12];
	static HBITMAP hBitmap[5];
	static INT nTime;
	INT i;
	switch(msg)
	{
	case WM_CREATE:
		hFont=CreateFont(24,
			0,0,0,FW_BLACK,
			0,0,0,0,0,0,0,0,TEXT("ÉÅÉCÉäÉI"));
		for (i = 0; i < 12; i++)
		{
			TCHAR szText[16];
			if (i < 10)
				wsprintf(szText, TEXT("%d"), i);
			else if (i == 10)
				lstrcpy(szText, TEXT("ΩƒØÃﬂ\r\n/∏ÿ±"));
			else if (i == 11)
				lstrcpy(szText, TEXT("Ω¿∞ƒ"));
			hButton[i] = CreateWindow(
				TEXT("BUTTON"),
				szText,
				WS_CHILD | WS_VISIBLE | BS_MULTILINE |
				((i == 11) ? BS_DEFPUSHBUTTON : 0),
				(i ? 10 + (((i > 9) ? i : (i - 1)) % 3) * 60 : 10),
				(i ? 64 + (((i > 9) ? i : (i - 1)) / 3) * 50 : 214),
				60,
				50,
				hWnd,
				(HMENU)(ID_0 + i),
				((LPCREATESTRUCT)lParam)->hInstance,
				0);
			SendMessage(hButton[i], WM_SETFONT, (WPARAM)hFont, 0);
		}
		for (i = 0; i < 5; i++)
		{
			hBitmap[i] = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance,
				(LPCTSTR)(IDB_BITMAP1+i));
		}
		break;
	case WM_TIMER:
		if(nTime!=0)
		{
			if (nTime % 10000 == 0)nTime -= 4000;
			if (nTime % 100 == 0)nTime -= 40;
			nTime--;
			InvalidateRect(hWnd, 0, 0);
		}
		if(nTime==0)
		{
			Beep(4000, 300);
			Sleep(100);
			Beep(4000, 300);
		}
		break;
	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hWnd, &ps);
			const int nTop = 10;
			int nLeft=10;
			LPCTSTR lpszText = TEXT("éûï™ïb");
			const HDC hdc_mem = CreateCompatibleDC(hdc);
			SelectObject(hdc, hFont);
			for (i = 0; i<6; i++, nLeft += 23)
			{
				const int n = (nTime / (int)pow(10.0, 5-i)) % 10;
				//àÍî‘è„ÇÃâ°ñ_
				SelectObject(hdc_mem,hBitmap[0]);
				BitBlt(hdc, nLeft + 2, nTop, 16, 5, hdc_mem, 0, 0,
					((n == 0) || (n == 2) ||
					(n == 3) || (n == 5) ||
					(n == 6) || (n == 7) ||
					(n == 8) || (n == 9)) ?
				SRCAND : MERGEPAINT);
				//ç∂è„ÇÃècñ_
				SelectObject(hdc_mem, hBitmap[1]);
				BitBlt(hdc, nLeft, nTop + 2, 5, 18, hdc_mem, 0, 0,
					((n == 0) || (n == 4) ||
					(n == 5) || (n == 6) ||
					(n == 8) || (n == 9)) ?
				SRCAND : MERGEPAINT);
				//âEè„ÇÃècñ_
				SelectObject(hdc_mem, hBitmap[2]);
				BitBlt(hdc, nLeft + 15, nTop + 2, 5, 18, hdc_mem, 0, 0,
					((n == 0) || (n == 1) ||
					(n == 2) || (n == 3) ||
					(n == 4) || (n == 7) ||
					(n == 8) || (n == 9)) ?
				SRCAND : MERGEPAINT);
				//ê^ÇÒíÜÇÃâ°ñ_
				SelectObject(hdc_mem, hBitmap[3]);
				BitBlt(hdc, nLeft + 2, nTop + 18, 16, 5, hdc_mem, 0, 0,
					((n == 2) || (n == 3) ||
					(n == 4) || (n == 5) ||
					(n == 6) || (n == 8) ||
					(n == 9)) ? SRCAND : MERGEPAINT);
				//àÍî‘â∫ÇÃâ°ñ_
				SelectObject(hdc_mem, hBitmap[4]);
				BitBlt(hdc, nLeft + 2, nTop + 36, 16, 5, hdc_mem, 0, 0,
					((n == 0) || (n == 2) ||
					(n == 3) || (n == 5) ||
					(n == 6) || (n == 8) ||
					(n == 9)) ? SRCAND : MERGEPAINT);
				//ç∂â∫ÇÃècñ_
				SelectObject(hdc_mem, hBitmap[1]);
				BitBlt(hdc, nLeft, nTop + 21, 5, 18, hdc_mem, 0, 0, 
					((n == 0) || (n == 2) ||
					(n == 6) || (n == 8)) ?
				SRCAND : MERGEPAINT);
				//âEâ∫ÇÃècñ_
				SelectObject(hdc_mem, hBitmap[2]);
				BitBlt(hdc, nLeft + 15, nTop + 21, 5, 18, hdc_mem, 0, 0, 
					((n == 0) || (n == 1) ||
					(n == 3) || (n == 4) ||
					(n == 5) || (n == 6) ||
					(n == 7) || (n == 8) ||
					(n == 9)) ? SRCAND : MERGEPAINT);
				if (i == 1 || i == 3 || i == 5)
				{
					nLeft += 16;
					TextOut(hdc, nLeft + 5, 33, (LPCTSTR)&lpszText[i / 2], 1);
				}
			}
			DeleteDC(hdc_mem);
			EndPaint(hWnd, &ps);
		}
		break;
	case WM_COMMAND:
		if (ID_0 <= LOWORD(wParam) && LOWORD(wParam) <= ID_9)
		{
			nTime = (nTime * 10 + LOWORD(wParam) - ID_0) % 1000000;
			InvalidateRect(hWnd, 0, 0);
		}
		else if (LOWORD(wParam) == ID_STOP)
		{
			if (!IsWindowEnabled(hButton[0]))
			{
				KillTimer(hWnd, 0x1234);
				for (i = 0; i<12; i++)
				{
					if (i != 10)
						EnableWindow(hButton[i], 1);
				}
			}
			else
			{
				nTime = 0;
				InvalidateRect(hWnd, 0, 0);
			}
			break;
		}
		else if (LOWORD(wParam) == ID_START)
		{
			for (i = 0; i<12; i++)
			{
				if (i != 10)
					EnableWindow(hButton[i], 0);
			}
			SetFocus(hButton[10]);
			SetTimer(hWnd, 0x1234, 1000, 0);
		}
		break;
	case WM_DESTROY:
		KillTimer(hWnd, 0x1234);
		for (i = 0; i < 5; i++)
		{
			DeleteObject(hBitmap[i]);
		}
		DeleteObject(hFont);
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInst,
	LPSTR pCmdLine, int nCmdShow)
{
	MSG msg;
	WNDCLASS wndclass = {
		CS_HREDRAW | CS_VREDRAW,
		WndProc,
		0,
		0,
		hInstance,
		0,
		LoadCursor(0, IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		0,
		szClassName
	};
	RegisterClass(&wndclass);
	RECT rect = { 0, 0, 200, 274 };
	const DWORD dwStyle = WS_CAPTION | WS_SYSMENU | WS_CLIPCHILDREN;
	AdjustWindowRect(&rect, dwStyle, 0);
	HWND hWnd=CreateWindowEx(
			WS_EX_TOPMOST,
			szClassName,
			TEXT("ÉLÉbÉ`ÉìÉ^ÉCÉ}Å["),
			dwStyle,
			CW_USEDEFAULT,
			0,
			rect.right-rect.left,
			rect.bottom-rect.top,
			0,
			0,
			hInstance,
			0
		);
	ShowWindow(hWnd,SW_SHOWDEFAULT);
	UpdateWindow(hWnd);
	HACCEL hAccel=LoadAccelerators(
		hInstance,
		MAKEINTRESOURCE(IDR_ACCELERATOR1));
	while(GetMessage(&msg,0,0,0))
	{
		if(!TranslateAccelerator(hWnd,hAccel,&msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}	
	return msg.wParam;
}
