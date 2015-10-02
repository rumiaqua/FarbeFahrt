#include "Loader.h"
#include <algorithm>
#include "DxLib.h"

Loader::Loader()
{
	m_modelList.clear();
	m_textureList.clear();
	m_BGMList.clear();
	m_SEList.clear();
}
void Loader::load()
{
	SetUseASyncLoadFlag(TRUE);
	for (auto &data : m_textureList)
	{
		data.second.handle = LoadGraph(data.second.filename.c_str());
	}
	for (auto &data : m_modelList)
	{
		data.second.handle = MV1LoadModel(data.second.filename.c_str());
	}
	for (auto &data : m_BGMList)
	{
		data.second.handle = LoadSoundMem(data.second.filename.c_str());
	}
	for (auto &data : m_SEList)
	{
		data.second.handle = LoadSoundMem(data.second.filename.c_str());
	}

	SetUseASyncLoadFlag(FALSE);
	isLoadCompleted = false;
}
bool Loader::isLoad()
{
	int count = 0;

	for (auto& data : m_textureList)
	{
		if (CheckHandleASyncLoad(data.second.handle) == TRUE)
		{
			count += 1;
		}
	}
	for (auto& data : m_modelList)
	{
		if (CheckHandleASyncLoad(data.second.handle) == TRUE)
		{
			count += 1;
		}
	}
	for (auto& data : m_BGMList)
	{
		if (CheckHandleASyncLoad(data.second.handle) == TRUE)
		{
			count += 1;
		}
	}
	for (auto& data : m_SEList)
	{
		if (CheckHandleASyncLoad(data.second.handle) == TRUE)
		{
			count += 1;
		}
	}
	//count > 0 Ç≈ì«Ç›çûÇ›íÜ
	return !!count;
}

void Loader::loadBGM(const std::string& name, const std::string& filename)
{
	m_BGMList.emplace(std::piecewise_construct,
		std::forward_as_tuple(name),
		std::forward_as_tuple(0, filename));
}
void Loader::loadModel(const std::string& name, const std::string& filename)
{
	m_modelList.emplace(std::piecewise_construct,
		std::forward_as_tuple(name),
		std::forward_as_tuple(0, filename));
}
void Loader::loadTexture(const std::string& name, const std::string& filename)
{
	m_textureList.emplace(std::piecewise_construct,
		std::forward_as_tuple(name),
		std::forward_as_tuple(0, filename));
}
void Loader::loadSE(const std::string& name, const std::string& filename)
{
	m_SEList.emplace(std::piecewise_construct,
		std::forward_as_tuple(name),
		std::forward_as_tuple(0, filename));
}
ContentMap& Loader::getModelList()
{
	return m_modelList;
}
ContentMap& Loader::getTextureList()
{
	return m_textureList;
}
ContentMap& Loader::getBGMList()
{
	return m_BGMList;
}
ContentMap& Loader::getSEList()
{
	return m_SEList;
}
void Loader::cleanUp()
{
	for (auto &data : m_modelList)
	{
		MV1DeleteModel(data.second.handle);
	}
	for (auto &data : m_textureList)
	{
		DeleteGraph(data.second.handle);
	}
	for (auto &data : m_BGMList)
	{
		DeleteSoundMem(data.second.handle);
	}for (auto &data : m_SEList)
	{
		DeleteSoundMem(data.second.handle);
	}
	m_modelList.clear();
	m_textureList.clear();
	m_BGMList.clear();
	m_SEList.clear();
}
Loader::~Loader()
{
}