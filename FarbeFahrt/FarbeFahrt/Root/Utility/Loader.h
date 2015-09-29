//+ �\ + *��*+�\ + *��*+�\ + *��*+�\ + *��*+�\ + *��*+�\ + �\ + *��*+�\ + *��*+�\ + *��*+�\ + *��*+�\ + *��*+�\ +
//�ӔC��:�Ȃ肽��
//+ �\ + *��*+�\ + *��*+�\ + *��*+�\ + *��*+�\ + *��*+�\ + �\ + *��*+�\ + *��*+�\ + *��*+�\ + *��*+�\ + *��*+�\ +
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
	ContentMap& getModelList();//render�Ŏg��
	ContentMap& getTextureList();//��������render�Ŏg��
	ContentMap& getBGMList();//���������߁[�̓_����
	ContentMap& getSEList();//���������߁[�̓_����
	//�Z�[�u�f�[�^�Ƃ��ł����瑝���邩��
private:
	ContentMap m_modelList;
	ContentMap m_textureList;
	ContentMap m_BGMList;
	ContentMap m_SEList;
	bool isLoadCompleted;
};
