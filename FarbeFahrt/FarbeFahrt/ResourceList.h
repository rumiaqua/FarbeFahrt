#pragma once
#include <string>
#include "DxLib.h"
typedef int Handle
class ResourceList
{
public:
	void add(const std::string& name);//名前を入れてリストに追加
	int get(const std::string& name);
	ResourceList();
	~ResourceList();
};

