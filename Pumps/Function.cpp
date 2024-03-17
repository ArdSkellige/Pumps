#include "Function.h"
#include <cstdlib>
#include <ctime>


void InputTimer(unsigned int& time1, unsigned int& time2)
{
	cout << "Enter the time of normal work, seconds: ";
	cin >> time1;
	cout << "Enter the time between pump switches, seconds: ";
	cin >> time2;
	cout << endl;
}

void PumpsIsWorking(Pump& pump21, Pump& pump22, Switcher& switcher, bool start)
{
	while (start + 1) // +1 дл€ отладки
	{
		// ќпредел€ю, какой насос в работу, какой запасной:
		if (pump21.GetCommonWorkTime() <= pump22.GetCommonWorkTime())
		{
			switcher.PutIntoWork(pump21);
			switcher.MakeSparePump(pump22);

			cout << "Pump21 in work: ";
		}
		else
		{
			switcher.PutIntoWork(pump22);
			switcher.MakeSparePump(pump21);

			cout << "Pump22 in work: ";
		}

		// —брасываю таймер фактической работы в новом цикле:
		unsigned int realWorkTime = 0;
		switcher.SetRealWorkTime(realWorkTime);

		// ѕроверка перед включением, сломан ли выбранный насос (с предыдущего цикла):
		if (switcher.IsPumpBroken()) // если сломан (true)
		{
			switcher.SwitchPump();
			cout << "Switch!" << endl;
			if (switcher.IsPumpBroken())
			{
				cout << "Both pumps are Broken!" << endl;
				break;
			}
		}
		else
		{
			switcher.SwitchOnPump();
		}

		// Ќасос в работе, если фактическое врем€ работы меньше расчЄтного и насос не сломан:
		while (realWorkTime < switcher.NormalWorkTime() && !switcher.IsPumpBroken())
		{
			Sleep(100);
			realWorkTime += (switcher.NormalWorkTime() / 5);

			// провер€ю состо€ние насоса во врем€ работы (сигнал от датчика 10):
			int fault = rand() % 15; // чем больше число, тем меньше веро€тность отказа (дл€ отладки)
			if (fault == 0) // насос вышел из стро€
			{
				switcher.SetRealWorkTime(realWorkTime);
				cout << "Breaking! Switch! Common time: "; // сообщение об аварии
				cout << switcher.GetAllTime() << " seconds; " << endl;
				switcher.MalfunctionPump();
				cout << "Other pump: ";

				switcher.SwitchPump(); // переключаю на другой насос
				if (switcher.IsPumpBroken()) // проверка, не сломан ли второй насос
				{
					cout << "Both pumps are Broken!" << endl;
					break;
				}
				realWorkTime = 0;
			}

			// провер€ю состо€ние сигнала от датчика сухого хода во врем€ работы (сигнал от датчика 14):
			int drySignal = rand() % 5; // (дл€ отладки)
			if (drySignal == 0) // датчик разомкнулс€, сигнал пропал
			{
				cout << "Dry Work. Stop! -> ";
				switcher.SwitchOffPump(); // выключаю насос
				do
				{
					Sleep(300);
					drySignal = rand() % 2; // периодически провер€ю сигнал от датчика 14
				} while (!drySignal);
				cout << "Continuation of work: ";
				switcher.SwitchOnPump(); // включаю насос, продолжение работы
			}
		}

		if (!switcher.IsPumpBroken()) // если хот€ бы один насос работает
		{
			switcher.SetRealWorkTime(realWorkTime);
			cout << switcher.GetRealWorkTime() << " seconds; ";
			cout << switcher.GetAllTime() << " seconds; " << endl;
			switcher.SwitchOffPump();
		}
		else
		{
			cout << "Need to repair both pumps!" << endl;
			break;
		}

	}
}