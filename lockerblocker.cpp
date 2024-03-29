#include <windows.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <iostream>
using namespace std;

void movemouse(int dx, int dy)
{
	INPUT *input = new INPUT[3];
	input->type = INPUT_MOUSE;
	input->mi.dx = dx;
	input->mi.dy = dy;
	input->mi.mouseData = 0;
	input->mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE;
	input->mi.time = 0;
	input->mi.dwExtraInfo = 0;
	SendInput(3, input, sizeof(INPUT));
	
	delete [] input;
}

void main(int argc, const char* argv[]){
	
	cout << "Press Esc to quit.";
	// Television recording is beginning. Enable away mode and prevent
	// the sleep idle time-out.
	//
	SetThreadExecutionState(ES_CONTINUOUS | ES_SYSTEM_REQUIRED | ES_AWAYMODE_REQUIRED);
		
	int x = 200;
	int y = 200;
	
	float a = 0;
	int mult = 1;
	float t = 0;
	
	char cIn=1;

	int step = 0;

	while(int(cIn) != 27){
		if (_kbhit()){
			cIn=_getch();
		}
		x = ceil(10000 + 100*a*sin(float(a*t)));
		y = ceil(10000 + 100*a*cos(float(a*t)));
		
		movemouse(x,y);
		t = t + 0.1;
		a = a + mult;

		if(a>50){
			mult = - 1;
		}
		
		if(a<1){
			mult = 1;
		}
		
		if(step==100){
			cout << "\n";
			for(int j = 0; j < 20; j++){
				char c;
				srand((unsigned int) time(NULL)*rand());
				c = (rand() % 1024);
				if(c!=7){
					cout << c;
				}
			}
			step = 0;
		}

		step = step + 1;

		Sleep(50);
	}
	
	//
	// Clear EXECUTION_STATE flags to disable away mode and allow the system to idle to sleep normally.
	//
	SetThreadExecutionState(ES_CONTINUOUS);

	exit(0);

}