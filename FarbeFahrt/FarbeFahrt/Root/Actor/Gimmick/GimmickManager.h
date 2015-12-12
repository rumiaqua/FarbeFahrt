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
private:
	unsigned int m_point;
};