#pragma once

class GimmickManager
{
public:
	GimmickManager();
	static int get();
	static void add(unsigned int point);
	static void sub(unsigned int point);
	static void reset();
	static bool isPoint(unsigned int point);
	static void setMax(unsigned int point);
	static int getMax();
private:
	unsigned int m_point;
	unsigned int m_maxPoint;
};