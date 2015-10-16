//+ �\ + *��*+�\ + *��*+�\ + *��*+�\ + *��*+�\ + *��*+�\ + �\ + *��*+�\ + *��*+�\ + *��*+�\ + *��*+�\ + *��*+�\ +
//�ӔC��:�Ȃ肽��
//+ �\ + *��*+�\ + *��*+�\ + *��*+�\ + *��*+�\ + *��*+�\ + �\ + *��*+�\ + *��*+�\ + *��*+�\ + *��*+�\ + *��*+�\ +
#pragma once
#include "Def.h"
#include <string>
#include <unordered_map>
#include <functional>
enum class ContentTag
{
	Model = 0,
	Texture,
	BGM,
	SE
};
struct ContentDataAndTag
{
	ContentTag tag;
	int handle;
	std::string filename;
	ContentDataAndTag(ContentTag tag, int handle, const std::string& filename)
	{
		this->tag = tag;
		this->handle = handle;
		this->filename = filename;
	}
	ContentDataAndTag(){}
};
struct FuncAndTag
{
	ContentTag tag;
	std::function<int(const char*)> func;
	FuncAndTag(ContentTag tag, std::function<int(const char*)> func)
	{
		this->tag = tag;
		this->func = func;
	}
	FuncAndTag(){}
};
using ContentMapPlusTag = std::unordered_map<std::string, ContentDataAndTag>;
class Loader
{
public:
	Loader();
	~Loader();
	void loadContent(const std::string& name, const std::string& filename);
	void DuplicateContent(const std::string& basename, const std::string& duplicate);
	void load();
	void cleanUp();
	bool isLoad();
private:
	void ErrLog(int ContentHandle, const std::string& filename);
	ContentMap getContentList(const ContentTag& tag);
public:
	ContentMap getModelList();//render�Ŏg��
	ContentMap getTextureList();//��������render�Ŏg��
	ContentMap getBGMList();//���������߁[�̓_����
	ContentMap getSEList();//���������߁[�̓_����
	//�Z�[�u�f�[�^�Ƃ��ł����瑝���邩��
private:
	ContentMapPlusTag m_ContentList;
	std::unordered_map<std::string, FuncAndTag> m_LoadFunc;
	bool isLoadCompleted;
};
