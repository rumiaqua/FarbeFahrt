#pragma once
#include <string>
#include <unordered_map>

// �ϐ����g�p���Ȃ����Ƃ𖾎�����
# define NoUse(Variable) ((void)Variable)

//�𑜓x���擾����
#define nScreenSizeX GetSystemMetrics(SM_CXSCREEN)
#define nScreenSizeY GetSystemMetrics(SM_CYSCREEN)
//��ʂ̒��S(�E�B���h�E�̒��S����Ȃ���)
#define nScreenCenterX (nScreenSizeX / 2)
#define nScreenCenterY (nScreenSizeY / 2)
//Player�N���X
#define ANIM_BLEND_SPEED 0.1f
//Player�N���X�����܂�
struct ContentData{
	int handle;
	std::string filename;
	ContentData(int handle,const std::string& filename)
	{
		this->handle = handle;
		this->filename = filename;
	}
	ContentData(){}
};
using ContentMap = std::unordered_map<std::string, ContentData>;
