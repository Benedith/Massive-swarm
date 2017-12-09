#define Win32

#ifdef Win32
#include <Windows.h>
#include "Display.h"
#include "Simulation.h"
#include <windows.h>
#include <iostream>
#include <fstream>
#include <conio.h>
#include <stdio.h>
#ifndef _USE_OLD_OSTREAMS
using namespace std;
#endif
#include "guicon.h"


#include <crtdbg.h>


#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")

//Windows starting point
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR szCmdLine, int iCmdShow)
{
#ifdef _DEBUG
	RedirectIOToConsole();
#endif

	//// test CrtDbg output
	_CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDERR);
	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_ERROR, _CRTDBG_FILE_STDERR);
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDERR);
	//_RPT0(_CRT_WARN, "This is testing _CRT_WARN output\n");
	//_RPT0(_CRT_ERROR, "This is testing _CRT_ERROR output\n");
	//_ASSERT(0 && "testing _ASSERT");
	//_ASSERTE(0 && "testing _ASSERTE");

	Display* display = new Display(hInstance, iCmdShow, 800, 600, "Massive Swarm");
	Display::setDisplay(display);
	Simulation* sim = new Simulation();

	while (!display->isClosed())
	{
		sim->Tick();
		display->StartDraw();
		sim->Draw();
		display->EndDraw();
	}

	delete display;
	delete sim;
	return 0;
}


#endif // Win32


//#include <windows.h>
//#include <stdio.h>
//#include <stdlib.h>
//#include <math.h>
//#include <GL\glew.h>
//
//#include "Bmath.h"
//
//
//
//#pragma comment(lib, "opengl32.lib")
//#pragma comment(lib, "glu32.lib")
//	
//
//#pragma region Explanation of Steps
///////////////////////////
//// BIG PICTURE:
////
//// Here's the big picture of what
//// we're going to be doing here:
//
///*
//
//|---------|  draws to   |-------|  copied out   |---------|  shows in  |-----------|
//|         | ==========> |       | ============> |         | =========> |           |
//|---------|             |-------|               |---------|            |-----------|
//OPENGL                  HGLRC                     HDC                 application
//FUNCTION                                                                 window
//CALLS
//
//*/
//
////////////////////////
//// In code:  this is the steps
//// we'll follow.
////
//// 1.  CREATE WINDOW AS USUAL.
////
//// 2.  GET DC OF WINDOW.
////     Get the HDC of our window using a line like:
////          hdc = GetDC( hwnd );
////
//// 3.  SET PIXEL FORMAT OF HDC.
////     You do 3 things here:
////          Create a PFD ('pixel format descriptor')
////          ChoosePixelFormat()
////          SetPixelFormat()
////
//// 4.  CREATE RENDERING CONTEXT (HGLRC).
////          wglCreateContext()
////     Create the surface to which OpenGL
////     shall draw.  It is created such that
////     it shall be completely compatible
////     with the DC of our window, (it will
////     use the same pixel format!)
////
//// 5.  CONNECT THE RENDER CONTEXT (HGLRC)
////     WITH THE DEVICE CONTEXT (HDC) OF WINDOW.
////          wglMakeCurrent()
////
//// 6.  DRAW USING OPENGL.
////          glVertex3d(); glColor3d(); // ETC!
////     You call OpenGL functions to perform
////     your drawing!  OpenGL will spit out
////     its result picture to the HGLRC, which is
////     connected to the backbuffer of your HDC.
////
//// 7.  SWAP BUFFERS.
////          SwapBuffers( hdc );	
////     Assuming you've picked a DOUBLE BUFFERED
////     pixel format all the way back in step 2, 
////     you'll need to SWAP the buffers so that
////     the image you've created using OpenGL on
////     the backbuffer of your hdc is shown
////     in your application window.
//#pragma endregion
//struct Globals
//{
//	
//
//	
//	HINSTANCE hInstance; // window app instance
//
//	HWND hwnd; //handle for the window
//
//	HDC hdc; //handle to device context
//
//	HGLRC hglrc; //handle
//
//	int width, height; //Drawable region of the window
//
//					   //angle of rotation
//	float angle = 0.0;
//	//actual vecotr representing the cameras direction
//	float lx = 0.0f, lz = 0.0f;
//	//XZ pos of camera
//	float x = 0.0f, z = 10.0f;
//	float c = 0;
//	float s = 0;
//	
//	
//};
//
////Globals
////declare one struct Globals called g
//
//Globals g;
/////////////
//
////Function Prototypes
//LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);
//int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR szCmdLine, int iCmdShow);
//void draw();			//Drawing function containing OpenGl function calls
//
//int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR szCmdLine, int iCmdShow)
//{
//	
//	//Save a copy of the hInstance parameter inside globals
//	g.hInstance = hInstance;
//
//#pragma region part 1 - create a window;
//	// Create a WNDCLASS describes the properties of the window
//
//	WNDCLASS wc;
//	wc.cbClsExtra = 0;
//	wc.cbWndExtra = 0;
//	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
//	wc.hCursor = LoadCursor(NULL, IDI_APPLICATION);
//	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
//	wc.hInstance = hInstance;
//	wc.lpfnWndProc = WndProc;
//	wc.lpszClassName = TEXT("BEN");
//	wc.lpszMenuName = 0;
//	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
//
//	//Register the class with the windows OS
//	RegisterClass(&wc);
//
//	//Rect Structure for window
//	//         TOP
//	//       --------
//	//       |      |
//	// LEFT  |      | RIGHT
//	//       --------
//	//        BOTTOM
//	RECT rect;
//	SetRect(&rect, 50, //Left
//		50,	//Top
//		850, // RIGHT
//		650); //Bottom
//
//				//Save the width and height
//	g.width = rect.right - rect.left;
//	g.height = rect.bottom - rect.top;
//
//	//Adjust it
//	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);
//	
//	// AdjustWindowRect() expands the RECT
//	// so that the CLIENT AREA (drawable region)
//	// has EXACTLY the dimensions we specify
//
//	//Call Create window with our adjusted Rect
//	g.hwnd = CreateWindow(TEXT("BEN"),
//						  TEXT("WINDOW.TEST"),
//						  WS_OVERLAPPEDWINDOW,
//						  rect.left, rect.top, //Adjust x,y pos
//						  rect.right - rect.left, rect.bottom - rect.top, //Adjust width and hieght
//						  NULL, NULL,
//						  hInstance, NULL);
//	
//	
//	//Window Created check
//	if (g.hwnd == NULL)
//	{
//		FatalAppExit(NULL, TEXT("CreateWindow() failed!"));
//	}
//
//	//and show
//	ShowWindow(g.hwnd, iCmdShow);
//	#pragma endregion
//
//
//	#pragma region Part 2 - Get DC of window
//	//Get DC and put in our global
//	g.hdc = GetDC(g.hwnd);
//	#pragma endregion
//
//	#pragma region Part 3 - Set Pixel FORMAT OF HDC	
//	//Pixel Format describes the qualities of each pixel in window
//
//	// There are 3 substeps here:
//	//    A> create the PFD and set it up to describe
//	//       the pixel format we DESIRE (dream of having!)
//	//
//	//    B> call ChoosePixelFormat() to make windows
//	//       choose us the ID of the appropriate pixel format that
//	//       is CLOSEST to our dream pixel format.
//	//
//	//    C> Call SetPixelFormat() using the integer ID number
//	//       that ChoosePixelFormat() returned to us in step B>
//	
//	PIXELFORMATDESCRIPTOR pfd = { 0 }; //create pfd
//
//									   //Set fields in PDF we care about
//	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR); //JUST ITS SIZE
//	pfd.nVersion = 1; //always 1
//
//	pfd.dwFlags = PFD_SUPPORT_OPENGL |	//OpenGL Support - Not DirectDraw
//		PFD_DOUBLEBUFFER |	//double buffering support
//		PFD_DRAW_TO_WINDOW;	//draw to the app window, not to a bitmap image
//
//	pfd.iPixelType = PFD_TYPE_RGBA;		// red, green, blue, alpha for each pixel
//	pfd.cColorBits = 24;	// 24 bit == 8 bits for red, 8 for green, 8 for blue.
//							// This count of color bits EXCLUDES alpha.
//	pfd.cDepthBits = 32;	//measure of pixel depth
//
//
//
//
//							// We'll make a call to a function called
//							// ChoosePixelFormat().  ChoosePixelFormat()
//							// will examine the PIXELFORMATDESCRIPTOR
//							// structure that you send it, then it will
//							// give you back an ID for the pixel format
//							// that MOST CLOSELY MATCHES the pixel format you
//							// SAID you wanted.
//	
//	int chosenPixelFormat = ChoosePixelFormat(g.hdc, &pfd);
//	//returns from ChoosePixelFormat() is an integer identifier
//	//for a specific pixel format windows knows about
//	if (chosenPixelFormat == 0)
//	{
//		FatalAppExit(NULL, TEXT("ChosenPixelFormat() Failed!"));
//	}
//
//	char b[100];
//	/*sprintf_s(b, "You got ID# %d as your pixelformat!\n", chosenPixelFormat);
//	MessageBoxA(NULL, b, "Your PixelFormat", MB_OK);*/
//		// C> So finally, we call SetPixelFormat() using the integer ID number
//		// that ChoosePixelFormat() returned to us previously.
//	int result = SetPixelFormat(g.hdc, chosenPixelFormat, &pfd);
//
//	if (result == NULL)
//	{
//		FatalAppExit(NULL, TEXT("SetPixelFormat() failed!"));
//	}
//
//	#pragma endregion
//
//	#pragma region part 4 - Create The Rendering Context
//	//4.  CREATE RENDERING CONTEXT (HGLRC).
//	// What's a rendering context?
//	// Its the "surface" that OpenGL
//	// will DRAW to.
//	g.hglrc = wglCreateContext(g.hdc);
//	#pragma endregion
//
//	#pragma region Part 4.5 - GLEW INIT
//	//Because i'm using glew i need to call glewInit after creating the rendering context
//	GLenum error = glewInit();
//	if (error != GLEW_OK)
//	{
//		/* Problem: glewInit failed, something is seriously wrong. */
//		fprintf(stderr, "Error: %s\n", glewGetErrorString(error));
//	}
//	#pragma endregion
//
//	#pragma region Part 5 - CONNECT THE RENDERING CONTEXT WITH THE DEVICE CONTEXT OF THE WINDOW
//	//5.  CONNECT THE RENDER CONTEXT (HGLRC)
//	//    WITH THE DEVICE CONTEXT (HDC) OF WINDOW.
//	wglMakeCurrent(g.hdc, g.hglrc);
//	#pragma endregion
//
//	#pragma region message loop
//	MSG msg;
//
//	while (1)
//	{
//		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
//		{
//			if (msg.message == WM_QUIT)
//			{
//				break;
//			}
//
//			TranslateMessage(&msg);
//			DispatchMessage(&msg);
//		}
//		else
//		{
//			//6.  DRAW USING OPENGL.
//			// This region right here is the
//			// heart of our application.  THE MOST
//			// execution time is spent just repeating
//			// this draw() function.
//			draw();
//		}
//	}
//	#pragma endregion
//
//	#pragma region clean up
//	// UNmake your rendering context (make it 'uncurrent')
//	wglMakeCurrent(NULL, NULL);
//
//	// Delete the rendering context, we no longer need it.
//	wglDeleteContext(g.hglrc);
//
//	// release your window's DC
//	ReleaseDC(g.hwnd, g.hdc);
//	#pragma endregion
//
//	// and a cheesy fade exit
//	AnimateWindow(g.hwnd, 200, AW_HIDE | AW_BLEND);
//
//	return msg.wParam;
//}
//
/////////////////////////
////DRAWING FUNCTION
//void draw()
//{
//	
//	glViewport(0, 0, g.width, g.height);  // set viewport
//										 // to be the whole width and height
//										 // of the CLIENT AREA (drawable region) of the window,
//										 // (the CLIENT AREA excludes the titlebar and the 
//										 // maximize/minimize buttons).
//
//	glMatrixMode(GL_PROJECTION);		//2. Projection matrix
//	glLoadIdentity();
//	
//	gluPerspective(45.0, (float)g.width / (float)g.height, 1, 1000);
//
//	//3. viewing transformation
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();
//
//	/*gluLookAt(0.0, 0.0, 10.0,
//			  0.0, 0.0, 0.0,
//			  0.0, 1.0, 0.0);*/
//	gluLookAt(g.x, 0.0f, g.z,
//		g.x + g.lx, 0.0f, /*g.z + */g.lz,
//		0.0f, 1.0f, 0.0f);
//
//	//4. modelling trasformation and drawing 
//	glClearColor(0.5, 0, 0, 0);
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//	static float i = 0.01f;
//	i += 0.0001f;     // increase i by 0.001 from its
//					 // it had on the LAST FUNCTION CALL to the draw() function
//
//	g.c +=i;
//	g.s += 0;
//	for (int i = 0; i < 1; i++)
//	{
//	glBegin(GL_TRIANGLES);
//	glColor3f(g.c, 0, 0);			//red
//	glVertex3f(1+g.c , 0+g.s , 0);
//	glVertex3f(0 +g.c, 1 + g.s, 0);
//	glVertex3f(-1 + g.c, 0+ g.s, 0);
//	glEnd();
//	g.c = g.c+0.1;
//	}
//	
//
//	//7. SWAP BUFFERS
//	
//	SwapBuffers(g.hdc);
//
//
//
//}
//
//LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
//{
//	switch (message)
//	{
//	case WM_CREATE:
//		Beep(50, 10);
//		return 0;
//		break;
//
//	case WM_PAINT:
//	{
//		HDC hdc;
//		PAINTSTRUCT ps;
//		hdc = BeginPaint(hwnd, &ps);
//		// don't draw here.  would be waaay too slow.
//		// draw in the draw() function instead.
//		EndPaint(hwnd, &ps);
//	}
//	return 0;
//	break;
//	
//	case WM_KEYDOWN:
//		switch (wparam)
//		{
//		case VK_LEFT:
//		{
//			//Add camera class
//			g.x = g.x - 1;
//			break;
//		}
//		case VK_RIGHT:
//		{
//			g.x = g.x + 1;
//			/*transform(1,0,0);*/
//			break;
//		}
//		case VK_UP:
//		{
//			g.z = g.z + 1;
//			break;
//		}
//		case VK_DOWN:
//		{
//			g.z = g.z-1;
//			break;
//		}
//		case VK_ESCAPE:
//			PostQuitMessage(0);
//			break;
//		default:
//			break;
//		}
//		return 0;
//
//	case WM_DESTROY:
//		PostQuitMessage(0);
//		return 0;
//		break;
//	}
//
//	return DefWindowProc(hwnd, message, wparam, lparam);
//}
//Change this to go to other OS




