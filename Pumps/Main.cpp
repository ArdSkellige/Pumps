#include <cstdlib>
#include <ctime>

#include "Function.h"

int main()
{
	srand(time(0));

	bool isSwit�hPump = rand() % 2; // ��� �������� ����������� ������� �� ������� ��������� �������

	unsigned int timer = 0;
	unsigned int timer2 = 0;
	InputTimer(timer, timer2);

	Pump pump21;
	Pump pump22;
	Switcher switcher;
	switcher.SetTimer(timer, timer2);

	PumpsIsWorking(pump21, pump22, switcher, isSwit�hPump);

	return 0;
}