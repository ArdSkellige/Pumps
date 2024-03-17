#pragma once

// workTime - ����� ����� ������ ������
// inWork - ����� � ������ (��/���)
// isBroken - ����� ������ (��/���)

class Pump
{
private:
	unsigned int workTime;
	bool inWork;
	bool isBroken;
public:
	Pump(unsigned int time = 0, bool work = false, bool broke = false);
	~Pump();

	void AddWorkTime(const int& time);
	unsigned int GetCommonWorkTime() const;
	bool InWork() const;
	bool IsBroken() const;
	void SwitchOn();
	void SwitchOff();
	void SetMalfunctionPump();

};

