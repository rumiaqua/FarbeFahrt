#pragma once
#include <string>
#include "DxLib.h"
typedef int Handle
class ResourceList
{
public:
	void add(const std::string& name);//–¼‘O‚ð“ü‚ê‚ÄƒŠƒXƒg‚É’Ç‰Á
	int get(const std::string& name);
	ResourceList();
	~ResourceList();
};

