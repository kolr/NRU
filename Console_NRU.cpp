#include <Windows.h>
#include <stdio.h>
#include <conio.h>
#include <time.h>
#define ZERO 0
#define ONE 1
#define SIZE 15
int activePages[4] = {0,0,0,0};
int pages[SIZE];
int counters[SIZE];
int counter = 0;

void CreateOM();
void ShowOM();
void Run();

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
	printf("Create OM\n");
	for(int i = 0; i < SIZE; i++){
		pages[i] = rand()%5 + 1;
	}
}

void ShowOM(){
	printf("Show OM\n");
	for(int i = 0; i < SIZE; i++){
		printf("Step %d  - \t %d \n",(i+1),pages[i]);
	}
}

void Run(){
	printf("Run...\n");
	for(int i = 0; i < SIZE; i++){
		int temp = 0;
		for(int j = 0; j < 4; j++){
			if(activePages[j] == 0){
				temp = j;
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
						break;
					}
				}
				break;
			}
		}
		
		goto m2;
m1: 
		printf("\n");
		for(int j = 0; j < 4; j++){
			printf("m1 \t %d \t %d \n",activePages[j],objects[activePages[j]].r);
		}
		
		goto m3;
m2:
		activePages[temp] = pages[i]; 
		objects[pages[i]].r = 1;
		counters[i] = i+1;
		objects[pages[i]].number = i+1;
		printf("\n");
		for(int j = 0; j < 4; j++){
			printf("m2 \t %d \t %d \n",activePages[j],objects[activePages[j]].r);
		}
		
m3:
		Sleep(1000);
	}
}

void WINAPI TimeTick(){
	int i = 0;
	while(1){
		Sleep(4000);
		for(int j = 0; j < 6; j++){
			objects[pages[j]].r = 0;
			objects[pages[j]].number = 0;
			//printf("Reset to 0 bit of element %d",pages[j]);
		}
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	unsigned long uThreadID;
	srand(unsigned(time(NULL)));
	printf("Create OM\n      ");
	for(int i = 0; i < SIZE; i++){
		pages[i] = rand()%10 + 1;
	}
	CreateThread(0,0,(LPTHREAD_START_ROUTINE)TimeTick,0,0,&uThreadID);
	CreateObjects();
	ShowOM();
	Run();
	getch();
	return 0;
}

