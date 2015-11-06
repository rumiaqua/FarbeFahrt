//+ ― + *☆*+― + *☆*+― + *☆*+― + *☆*+― + *☆*+― + ― + *☆*+― + *☆*+― + *☆*+― + *☆*+― + *☆*+― +
//責任者:なりたん
//+ ― + *☆*+― + *☆*+― + *☆*+― + *☆*+― + *☆*+― + ― + *☆*+― + *☆*+― + *☆*+― + *☆*+― + *☆*+― +
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
	void deleteModel();//別スレッドだよ
	ContentMap getContentList(const ContentTag& tag) const;
public:
	ContentMap getModelList() const;//renderで使う
	ContentMap getTextureList() const;//こっちもrenderで使う
	ContentMap getBGMList() const;//ただしおめーはダメだ
	ContentMap getSEList() const;//ただしおめーはダメだ
	//セーブデータとかできたら増えるかも
private:
	ContentMapPlusTag m_ContentList;
	ContentMapPlusTag m_oldContentList;
	std::unordered_map<std::string, FuncAndTag> m_LoadFunc;
	bool isLoadCompleted;
};
