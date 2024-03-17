#include "Switcher.h"
#include <windows.h>

Switcher::Switcher(Pump* pumpMain, Pump* pumpSpare, bool dry, unsigned int pumpTime, unsigned int swTime) : currentPump(pumpMain), sparePump(pumpSpare), isDryPump(dry), normalPumpingTime(pumpTime), switchTime(swTime)
{
}

Switcher::~Switcher()
{
	currentPump = nullptr;
	sparePump = nullptr;
}

void Switcher::PutIntoWork(Pump& pump)
{
	currentPump = &pump;
}

void Switcher::MakeSparePump(Pump& pump)
{
	sparePump = &pump;
}

void Switcher::SwitchOnPump()
{
	currentPump->SwitchOn();
}

void Switcher::SwitchOffPump()
{
	currentPump->SwitchOff();
}

bool Switcher::IsPumpWork()
{
	return currentPump->InWork();
}

bool Switcher::IsPumpBroken()
{
	return currentPump->IsBroken();
}

void Switcher::SetTimer(unsigned int timePump, unsigned int swTime)
{
	if (timePump > 0)
	{
		normalPumpingTime = timePump;
	}
	if (swTime > 0)
	{
		switchTime = swTime;
	}
}

void Switcher::SwitchPump()
{
	Pump* tmpPump = currentPump;

	currentPump->SwitchOff(); // выключаю основной насос
	//currentPump->AddWorkTime(realPumpingTime); // добавляю время работы основному насосу

	currentPump = sparePump; // запасной насос становится основным
	Sleep(switchTime); // пауза между переключениями насосов
	currentPump->SwitchOn(); // включаю основной насос

	sparePump = tmpPump; // запасным становится насос, который только что работал
	tmpPump = nullptr;
}

unsigned int Switcher::NormalWorkTime() const
{
	return normalPumpingTime;
}

void Switcher::SetRealWorkTime(unsigned int time)
{
	realPumpingTime = time;
	currentPump->AddWorkTime(realPumpingTime);
}

unsigned int Switcher::GetRealWorkTime() const
{
	return realPumpingTime;
}

unsigned int Switcher::GetAllTime() const
{
	return currentPump->GetCommonWorkTime();
}

void Switcher::MalfunctionPump()
{
	currentPump->SetMalfunctionPump();
	currentPump->SwitchOff();
}