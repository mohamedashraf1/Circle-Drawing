#if defined(UNICODE) && !defined(_UNICODE)
#define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
#define UNICODE
#endif
#include <cmath>
#include <tchar.h>
#include <windows.h>
#include "iostream"
using namespace std;
/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

/*  Make the class name into a global variable  */
TCHAR szClassName[ ] = _T("CodeBlocksWindowsApp");

int WINAPI WinMain (HINSTANCE hThisInstance,
                    HINSTANCE hPrevInstance,
                    LPSTR lpszArgument,
                    int nCmdShow)
{
    HWND hwnd;               /* This is the handle for our window */
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default colour as the background of the window */
    wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND;

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx (
               0,                   /* Extended possibilites for variation */
               szClassName,         /* Classname */
               _T("Code::Blocks Template Windows App"),       /* Title Text */
               WS_OVERLAPPEDWINDOW, /* default window */
               CW_USEDEFAULT,       /* Windows decides the position */
               CW_USEDEFAULT,       /* where the window ends up on the screen */
               544,                 /* The programs width */
               375,                 /* and height in pixels */
               HWND_DESKTOP,        /* The window is a child-window to desktop */
               NULL,                /* No menu */
               hThisInstance,       /* Program Instance handler */
               NULL                 /* No Window Creation data */
           );

    /* Make the window visible on the screen */
    ShowWindow (hwnd, nCmdShow);

    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage (&messages, NULL, 0, 0))
    {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}

int getR(int x1,int y1, int x2, int y2)
{

    int tmp = pow((x1-x2),2) + pow((y1-y2),2);
    int R = (int)sqrt((double)tmp);
    return R;
}

/*  This function is called by the Windows function DispatchMessage()  */


void Draweightpoint(HDC hdc,int xc,int a,int yc,int b, COLORREF color)
{
    SetPixel(hdc, xc+a, yc+b, color);//1
    SetPixel(hdc, xc-a, yc+b, color);
    SetPixel(hdc, xc-a, yc-b, color);
    SetPixel(hdc, xc+a, yc-b, color);
    SetPixel(hdc, xc+b, yc+a, color);//1
    SetPixel(hdc, xc-b, yc+a, color);
    SetPixel(hdc, xc-b, yc-a, color);
    SetPixel(hdc, xc+b, yc-a, color);
}


void DrawLine2(HDC hdc,int xs,int ys,int xe,int ye,COLORREF color)
{
    int dx=xe-xs;
    int dy=ye-ys;
    if(abs(dy)<=abs(dx))
    {
        double slope=(double)dy/dx;
        if(xs>xe)
        {
            swap(xs,xe);
            swap(ys,ye);
        }
        for(int x=xs; x<=xe; x++)
        {
            int y=round(ys+(x-xs)*slope);
            SetPixel(hdc,x,y,color);
        }
    }
    else
    {
        double islope=(double)dx/dy;
        if(ys>ye)
        {
            swap(xs,xe);
            swap(ys,ye);
        }
        for(int y=ys; y<=ye; y++ ){    int x=round(xs+(y-ys)*islope);    SetPixel(hdc,x,y,color);   }

    }
}

void drawLines(HDC hdc,int xc,int yc,int R,COLORREF color)
{
    DrawLine2(hdc,xc-R,yc,xc+R,yc,color);

    DrawLine2(hdc,xc,yc-R,xc,yc+R,color);

    DrawLine2(hdc,xc-0.707*R,yc-0.707*R,xc+0.707*R,yc+0.707*R,color);

    DrawLine2(hdc,xc-0.707*R,yc+0.707*R,xc+0.707*R,yc-0.707*R,color);

}
void Drawcircle(HDC hdc,int xc,int yc,int R)
{
    int x=0;
    int y=R;
    int d=y-R;
    Draweightpoint(hdc,(int)xc,(int)x,(int)yc,(int)y,'red');

    while(x<y)
    {
        if (d>=0)
        {
            d+=2*(x-y)+5;
            x++;
            y--;
        }
        else
        {
            d+=(2*x)+3;
            x++;
        }
        Draweightpoint(hdc,(int)xc,(int)x,(int)yc,(int)y,'red');

    }

}




int xc,x2,yc,y2,R;
LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HDC hdc = GetDC(hwnd);

    switch (message)                  /* handle the messages */
    {
    case WM_LBUTTONDBLCLK:{
        xc = LOWORD(lParam);
        yc = HIWORD(lParam);

        //PostQuitMessage (0);      /* send a WM_QUIT to the message queue */
        break;}
    case WM_RBUTTONDBLCLK:{
        x2 = LOWORD(lParam);
        y2 = HIWORD(lParam);
        R = getR(xc,yc,x2,y2);
        Drawcircle(hdc,xc,yc,R);
        drawLines(hdc,xc,yc,R,RGB(255,0,0));


        break;
    }
    default:                      /* for messages that we don't deal with */
        return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}
