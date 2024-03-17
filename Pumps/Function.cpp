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
	while (start + 1) // +1 ��� �������
	{
		// ���������, ����� ����� � ������, ����� ��������:
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

		// ��������� ������ ����������� ������ � ����� �����:
		unsigned int realWorkTime = 0;
		switcher.SetRealWorkTime(realWorkTime);

		// �������� ����� ����������, ������ �� ��������� ����� (� ����������� �����):
		if (switcher.IsPumpBroken()) // ���� ������ (true)
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

		// ����� � ������, ���� ����������� ����� ������ ������ ���������� � ����� �� ������:
		while (realWorkTime < switcher.NormalWorkTime() && !switcher.IsPumpBroken())
		{
			Sleep(100);
			realWorkTime += (switcher.NormalWorkTime() / 5);

			// �������� ��������� ������ �� ����� ������ (������ �� ������� 10):
			int fault = rand() % 15; // ��� ������ �����, ��� ������ ����������� ������ (��� �������)
			if (fault == 0) // ����� ����� �� �����
			{
				switcher.SetRealWorkTime(realWorkTime);
				cout << "Breaking! Switch! Common time: "; // ��������� �� ������
				cout << switcher.GetAllTime() << " seconds; " << endl;
				switcher.MalfunctionPump();
				cout << "Other pump: ";

				switcher.SwitchPump(); // ���������� �� ������ �����
				if (switcher.IsPumpBroken()) // ��������, �� ������ �� ������ �����
				{
					cout << "Both pumps are Broken!" << endl;
					break;
				}
				realWorkTime = 0;
			}

			// �������� ��������� ������� �� ������� ������ ���� �� ����� ������ (������ �� ������� 14):
			int drySignal = rand() % 5; // (��� �������)
			if (drySignal == 0) // ������ �����������, ������ ������
			{
				cout << "Dry Work. Stop! -> ";
				switcher.SwitchOffPump(); // �������� �����
				do
				{
					Sleep(300);
					drySignal = rand() % 2; // ������������ �������� ������ �� ������� 14
				} while (!drySignal);
				cout << "Continuation of work: ";
				switcher.SwitchOnPump(); // ������� �����, ����������� ������
			}
		}

		if (!switcher.IsPumpBroken()) // ���� ���� �� ���� ����� ��������
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