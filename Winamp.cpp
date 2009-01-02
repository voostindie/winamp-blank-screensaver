// Winamp.cpp : Defines the entry point for the application.
//
// Winamp Blank Screensaver
//
// Copyright (c) 1999 by Vincent Oostindie
//
// This is a simple blank screensaver that overrides the KEYDOWN messages
// for the Z, X, C, V and B keys. When Winamp is running, it sends these
// messages to this application, so that you can control Winamp while the
// screen stays blank.
//
// This application uses the screensaver library (SCRNSAVE.LIB), so that
// only three functions have to be defined:
// - ScreenSaverProc
// - ScreenSaverConfigureDialog
// - RegisterDialogClasses
//
// See "scrnsave.h" for details.
// 

#include "stdafx.h"
#include "windows.h"
#include "scrnsave.h"
#include "resource.h"

extern HINSTANCE hMainInstance;

CHAR szAppName[] = "Winamp Blank Screensaver";

LRESULT WINAPI ScreenSaverProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HWND hWinamp; // Handle to Winamp

	switch(message)
	{
		case WM_CREATE:

            /* Retrieve the application name from the .rc file. */ 
            LoadString(hMainInstance, idsAppName, szAppName, 40); 

			// Locate Winamp (== NULL when not found)
			hWinamp = FindWindow("Winamp v1.x", NULL);

			break;

		case WM_ERASEBKGND:

			// Erase the background
            HDC hdc;
			hdc = GetDC(hWnd); 
			RECT rc;
            GetClientRect(hWnd, &rc); 
            FillRect (hdc, &rc, (HBRUSH)GetStockObject(BLACK_BRUSH)); 
            ReleaseDC(hWnd,hdc); 
            break; 
 
		case WM_KEYDOWN:
			
			// If Winamp was not found, break
			if (hWinamp == NULL)
				break;

			// Handle the Z, X, C, V and B keys
			int key = (int)wParam;
			if (key == int('z') || key == int('Z') ||
				key == int('x') || key == int('X') || 
				key == int('c') || key == int('C') ||
				key == int('v') || key == int('V') || 
				key == int('b') || key == int('B')
				) {
					// Send a message to Winamp
					PostMessage(hWinamp, WM_KEYDOWN, wParam, lParam);
					return 0;
			}
	    } 
 
	// Handle all other messages
	return (DefScreenSaverProc(hWnd, message, wParam, lParam));
}

BOOL WINAPI ScreenSaverConfigureDialog (HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	// There is no configure dialog, so simply return TRUE
	return TRUE; 
}

BOOL WINAPI RegisterDialogClasses (HANDLE hInst)
{
	return TRUE; // we use only standard window classes
}
