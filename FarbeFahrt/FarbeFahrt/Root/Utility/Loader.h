//+ �\ + *��*+�\ + *��*+�\ + *��*+�\ + *��*+�\ + *��*+�\ + �\ + *��*+�\ + *��*+�\ + *��*+�\ + *��*+�\ + *��*+�\ +
//�ӔC��:�Ȃ肽��
//+ �\ + *��*+�\ + *��*+�\ + *��*+�\ + *��*+�\ + *��*+�\ + �\ + *��*+�\ + *��*+�\ + *��*+�\ + *��*+�\ + *��*+�\ +
#pragma once
#include "Def.h"
#include <string>
#include <unordered_map>
#include <functional>
#include "Utility\String.h"
enum class ContentTag
{
	Model = 0,
	Texture,
	BGM,
	SE,
	VertexShader,
	PixelShader
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
	std::function<int(const char*)> loadFunc;
	FuncAndTag(ContentTag tag, std::function<int(const char*)> loadFunc)
	{
		this->tag = tag;
		this->loadFunc = loadFunc;
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
	void loadASync();
	void cleanUp();
	bool isLoad() const;
	bool onCompleted();
private:
	void ErrLog(int ContentHandle, const std::string& filename);
	void deleteContents();//�ʃX���b�h����
	ContentMap getContentList(const ContentTag& tag) const;
public:
	ContentMap getModelList() const;//render�Ŏg��
	ContentMap getTextureList() const;//��������render�Ŏg��
	ContentMap getBGMList() const;//���������߁[�̓_����
	ContentMap getSEList() const;//���������߁[�̓_����
	//�Z�[�u�f�[�^�Ƃ��ł����瑝���邩��
private:
	ContentMapPlusTag m_ContentsList;
	ContentMapPlusTag m_oldContentsList;
	std::unordered_map<std::string, FuncAndTag> m_LoadFunc;
	std::unordered_map < ContentTag, std::function<int(int)> >m_deleteFunc;

	bool m_onCompleted;
	bool m_isChangedScene;
};
