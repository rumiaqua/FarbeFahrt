#pragma once
#include <string>
#include "DxLib.h"
typedef int Handle
class ResourceList
{
public:
	void add(const std::string& name);//���O�����ă��X�g�ɒǉ�
	int get(const std::string& name);
	ResourceList();
	~ResourceList();
};

