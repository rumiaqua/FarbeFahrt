//+ ― + *☆*+― + *☆*+― + *☆*+― + *☆*+― + *☆*+― + ― + *☆*+― + *☆*+― + *☆*+― + *☆*+― + *☆*+― +
//責任者:なりたん
//+ ― + *☆*+― + *☆*+― + *☆*+― + *☆*+― + *☆*+― + ― + *☆*+― + *☆*+― + *☆*+― + *☆*+― + *☆*+― +
#pragma once
#include "Def.h"
#include <string>
#include <unordered_map>

class Loader
{
public:
	

	Loader();
	~Loader();
	void loadModel(const std::string& name, const std::string& filename);
	void loadTexture(const std::string& name, const std::string& filename);
	void loadBGM(const std::string& name, const std::string& filename);
	void loadSE(const std::string& name, const std::string& filename);
	void load();
	void cleanUp();
	bool isLoad();
public:
	ContentMap& getModelList();//renderで使う
	ContentMap& getTextureList();//こっちもrenderで使う
	ContentMap& getBGMList();//ただしおめーはダメだ
	ContentMap& getSEList();//ただしおめーはダメだ
	//セーブデータとかできたら増えるかも
private:
	ContentMap m_modelList;
	ContentMap m_textureList;
	ContentMap m_BGMList;
	ContentMap m_SEList;
	bool isLoadCompleted;
};
