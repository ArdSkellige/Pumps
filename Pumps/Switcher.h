#pragma once
#include "Pump.h"

// currentPump - указатель на работающий насос
// sparePump - указатель на запасной насос
// normalPumpingTime - расчётное время работы насоса
// realPumpingTime - фактическое время работы насоса
// switchTime - время между переключениями насоса
// isDryPump - датчика сухого хода разомкнут (да/нет)

// PutIntoWork(Pump& pump) - взять в работу насос
// MakeSparePump(Pump& pump) - определить запасной насос
// SwitchOnPump() - включить основной насос
// SwitchOffPump() - выключить основной насос
// SetRealWorkTime(unsigned int time) - устанавливаю фактически отработанное время для насоса и добавляю в его общее время работы
// NormalWorkTime() - запланированное время работы за включение
// GetRealWorkTime() - получить фактически отработанное время за одно включение
// GetAllTime() - получить общее время работы насоса
// MalfunctionPump() - установить текущий насос в состояние неисправности

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

