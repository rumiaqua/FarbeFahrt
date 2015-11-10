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
	bool use;
	ContentDataAndTag(ContentTag tag, int handle, const std::string& filename,bool use)
	{
		this->tag = tag;
		this->handle = handle;
		this->filename = filename;
		this->use = use;
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
	bool isLoad() const;
	bool onCompleted();
private:
	void ErrLog(int ContentHandle, const std::string& filename);
	void deleteModel();//�ʃX���b�h����
	ContentMap getContentList(const ContentTag& tag) const;
public:
	ContentMap getModelList() const;//render�Ŏg��
	ContentMap getTextureList() const;//��������render�Ŏg��
	ContentMap getBGMList() const;//���������߁[�̓_����
	ContentMap getSEList() const;//���������߁[�̓_����
	//�Z�[�u�f�[�^�Ƃ��ł����瑝���邩��
private:
	ContentMapPlusTag m_ContentList;
	ContentMapPlusTag m_oldContentList;
	std::unordered_map<std::string, FuncAndTag> m_LoadFunc;
	bool isLoadCompleted;
};
