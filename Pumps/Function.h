#pragma once
#include <windows.h>
#include <iostream>

#include "Switcher.h"

using std::cout;
using std::endl;
using std::cin;

void InputTimer(unsigned int& time1, unsigned int& time2);
void PumpsIsWorking(Pump& pump1, Pump& pump2, Switcher& sw, bool start);