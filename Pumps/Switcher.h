#pragma once
#include "Pump.h"

// currentPump - ��������� �� ���������� �����
// sparePump - ��������� �� �������� �����
// normalPumpingTime - ��������� ����� ������ ������
// realPumpingTime - ����������� ����� ������ ������
// switchTime - ����� ����� �������������� ������
// isDryPump - ������� ������ ���� ��������� (��/���)

// PutIntoWork(Pump& pump) - ����� � ������ �����
// MakeSparePump(Pump& pump) - ���������� �������� �����
// SwitchOnPump() - �������� �������� �����
// SwitchOffPump() - ��������� �������� �����
// SetRealWorkTime(unsigned int time) - ������������ ���������� ������������ ����� ��� ������ � �������� � ��� ����� ����� ������
// NormalWorkTime() - ��������������� ����� ������ �� ���������
// GetRealWorkTime() - �������� ���������� ������������ ����� �� ���� ���������
// GetAllTime() - �������� ����� ����� ������ ������
// MalfunctionPump() - ���������� ������� ����� � ��������� �������������

class Switcher
{
private:
	Pump* currentPump;
	Pump* sparePump;
	unsigned int normalPumpingTime;
	unsigned int realPumpingTime;
	unsigned int switchTime;
	bool isDryPump;
public:
	Switcher(Pump* pumpMain = nullptr, Pump* pumpSpare = nullptr, bool dry = false, unsigned int pumpTime = 50, unsigned int swTime = 10);
	~Switcher();

	void PutIntoWork(Pump& pump);
	void MakeSparePump(Pump& pump);
	void SwitchOnPump();
	void SwitchOffPump();
	bool IsPumpWork();
	bool IsPumpBroken();
	void SetTimer(unsigned int timePump, unsigned int swTime);
	void SwitchPump();
	unsigned int NormalWorkTime() const;
	void SetRealWorkTime(unsigned int time);
	unsigned int GetRealWorkTime() const;
	unsigned int GetAllTime() const;
	void MalfunctionPump();

};

