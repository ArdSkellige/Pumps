#include "Pump.h"

Pump::Pump(unsigned int time, bool work, bool broke) : workTime(time), inWork(work), isBroken(broke)
{
}

Pump::~Pump()
{
}

void Pump::AddWorkTime(const int& time)
{
	workTime += time;
}

unsigned int Pump::GetCommonWorkTime() const
{
	return workTime;
}

bool Pump::InWork() const
{
	return inWork;
}

bool Pump::IsBroken() const
{
	return isBroken;
}

void Pump::SwitchOn()
{
	inWork = true;
}

void Pump::SwitchOff()
{
	inWork = false;
}

void Pump::SetMalfunctionPump()
{
	isBroken = true;
}