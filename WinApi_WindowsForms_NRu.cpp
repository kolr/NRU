// СПО ЛБ4.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <Windows.h>
#include <time.h>
#define DEFPUSHBUTTON_1 101
#define ZERO 0
#define ONE 1
#define SIZE 15
LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM);
char szStr[];   
char Buf[100];
char Buf1[100];
PCOPYDATASTRUCT pMyCDS;		
RECT rect;
int buttonPress;
int activePages[4] = {0,0,0,0};
int pages[SIZE];
int counters[SIZE];
int counter = 0;
int interCounter = 0;
void CreateOM();
void ShowOM();
void Run();
void WINAPI TimeTick();
void CreateObjects();
HWND hwnd7;
HWND hwnd;
HWND hwnd1;
	int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
	{
		static char szAppName[]="MyWindowApp";
		static char szWinCaption[] = "NRU";
		MSG msg;
		WNDCLASSEX wndclass;
		wndclass.cbSize=sizeof(wndclass);// размер структуры
		wndclass.style=CS_HREDRAW|CS_VREDRAW;//стиль окна - перерисовывание при изминении размеров
		wndclass.lpfnWndProc=WndProc;//показатель на функцию обратной связи для обработки сообщений
		wndclass.cbClsExtra=0;//число дополнительных байтов в конце этой структуры
		wndclass.cbWndExtra=0;//число дополнительных байтов за экземпляром окна
		wndclass.hInstance=hInstance;//дескиптор экземпляра в котором находится процедура окна
		wndclass.hIcon=LoadIcon(NULL, IDI_APPLICATION);//дескриптор ярлыка для класса окна
		wndclass.hCursor=LoadCursor(NULL, IDC_ARROW);//дескриптор курсора для класса окна
		wndclass.hbrBackground=(HBRUSH) GetStockObject(COLOR_WINDOW+1);//дескриптор кисточки окна
		wndclass.lpszMenuName=NULL;//имя меню
		wndclass.lpszClassName=szAppName;//имя класса
		wndclass.hIconSm=LoadIcon(NULL, IDI_APPLICATION);//дескриптор ярлыка для заголовка окон программы
		RegisterClassEx (&wndclass);//регестрация класса окна
		hwnd=CreateWindow ((LPCSTR)szAppName,(LPCSTR)szWinCaption,WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,CW_USEDEFAULT,700,300,NULL,NULL,hInstance,NULL);
		ShowWindow(hwnd,iCmdShow);//изображение окна на єкране
		UpdateWindow(hwnd);//перерисовывание содержимого окна

		while (GetMessage (&msg, NULL, 0, 0))//цикл получения сообщений из очереди
			{
				TranslateMessage (&msg);//превращение сообщения от клавиатуры
				DispatchMessage (&msg);//отправка сообщения оконной функции
			}
	return msg.wParam;
}
	LRESULT CALLBACK WndProc (HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
	{
		unsigned long uThreadID;
		unsigned long uThreadID1;
		srand(unsigned(time(NULL)));
		char MyStr[128];
		HDC hdc = GetWindowDC(hwnd);
		HPEN hPen;
		PAINTSTRUCT ps;
		RECT rect;//оброботка сообщения
		switch (iMsg)
		{
		int x,y,sx,sy;
		HDC hDC;
		case WM_CREATE://создание окна
			hwnd7=CreateWindow("BUTTON", "Старт", WS_CHILD|SS_CENTERIMAGE|SS_PATHELLIPSIS,10,130,70,30,hwnd, (HMENU) DEFPUSHBUTTON_1,NULL,NULL);
			ShowWindow (hwnd7, SW_SHOW);		
			return 0;
			break;
		case WM_SIZE:
			sx = 680;
			sy = 130;
		case WM_PAINT:
			hdc = BeginPaint(hwnd, &ps);
			hPen = CreatePen(PS_DASHDOTDOT, 3, RGB(0, 0, 0));
			SelectObject(hdc, hPen);
			for (x = 20; x < sx; x += sx/15)
			{
				MoveToEx(hdc, x, 20, NULL);
				LineTo(hdc, x, sy);
			}
			for (y = 20; y < sy; y += sy/5)
			{
				MoveToEx(hdc, 20, y, NULL);
				LineTo(hdc, sx, y);
			}
			ValidateRect(hwnd, NULL);
			EndPaint (hwnd, &ps);
			return 0;
			break;
		case WM_DESTROY://уничтожение окна
			PostQuitMessage (0);//запрос ОС на уничтожение окна
			return 0;
		case WM_COMMAND:
			if (wParam==DEFPUSHBUTTON_1) //двойной клик например
			{
				for(int i = 0; i < SIZE; i++){
					pages[i] = rand()%10 + 1;
				}
				wsprintf(Buf1,"%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",pages[0],pages[1],pages[2],pages[3],pages[4],
					pages[5],pages[6],pages[7],pages[8],pages[9],pages[10],pages[11],pages[12],pages[13],pages[14]);
				TextOut(hdc,10,250,Buf1,100);
				CreateThread(0,0,(LPTHREAD_START_ROUTINE)TimeTick,0,0,&uThreadID);
				CreateObjects();
				CreateThread(0,0,(LPTHREAD_START_ROUTINE)Run,0,0,&uThreadID);
			}
			return 0;
			break;
		default:
		//обработка по умолчанию всех сообщений, что не были обработвны в программе
		return DefWindowProc (hwnd, iMsg, wParam, lParam);
			 }	
    }
	struct OBJ{
	int number;
	int r;
	int m;
}objects[6];

void CreateObjects(){
	for(int i = 0; i < 6; i++){
		objects[i].number = i+1;
		objects[i].m = 0;
		objects[i].r = 0;
	}
}

void CreateOM(){
	for(int i = 0; i < SIZE; i++){
		pages[i] = rand()%5 + 1;
	}
}

void ShowOM(){
	for(int i = 0; i < SIZE; i++){
	}
}

void Run(){
	HDC hdc1 = GetWindowDC(hwnd);
	char Buf2[10];
	for(int i = 0; i < SIZE; i++){
		int temp = 0;
		for(int j = 0; j < 4; j++){
			if(activePages[j] == 0){
				temp = j;
				interCounter++;
				break;
			}
			else{
				for(int q = 0; q < 4; q++){
					if(activePages[q]==pages[i]){
						goto m1;
						break;
					}
				}
				for(int q = 0; q < 4; q++){
					if(objects[activePages[q]].r == 0){
						temp = q;
						interCounter++;
						break;
					}
				}
				break;
			}
		}
		
		goto m2;
m1: 
		for(int j = 0; j < 4; j++){
			itoa(activePages[j],Buf2,10);
			TextOut(hdc1,44.7*(i+1),25*(j+2.2),Buf2,2);
		}
		goto m3;
m2:
		activePages[temp] = pages[i]; 
		objects[pages[i]].r = 1;
		counters[i] = i+1;
		objects[pages[i]].number = i+1;
		
		for(int j = 0; j < 4; j++){
			itoa(activePages[j],Buf2,10);
			TextOut(hdc1,44.7*(i+1),25*(j+2.2),Buf2,2);
		}
		
m3:
		Sleep(1000);
	}
	itoa(interCounter,Buf2,10);
	TextOut(hdc1,250,500,Buf2,2);
}

void WINAPI TimeTick(){
	int i = 0;
	while(1){
		Sleep(4000);
		for(int j = 0; j < 6; j++){
			objects[pages[j]].r = 0;
			objects[pages[j]].number = 0;
		}
	}
}

