#include "Loader.h"
#include <algorithm>
#include "DxLib.h"
#include <iostream>
#include <thread>
Loader::Loader()
{
	m_ContentsList.clear();
	//std::string�ƁAenum��const char*�������ɂƂ�int��Ԃ��֐��̍\����
	//��std::unordred_map
	//��emplace����
	//���߂�const char*�ƁAenum�ƁAconst char*�������ɂƂ�int��Ԃ��֐�
	//�������ɂƂ�֐�
	using namespace std::placeholders;
	using loadFunc = std::function<int(const char*)>;
	using deleteFunc = std::function<int(int)>;
	std::function<void(const char*, ContentTag, loadFunc)> emplaceFunc =
		[this](const char* c, ContentTag tag, loadFunc& DXfunc)
	{
		this->m_LoadFunc.emplace(std::piecewise_construct, 
			std::forward_as_tuple(c), std::forward_as_tuple(tag, DXfunc));
	};

	std::function<void(ContentTag, deleteFunc)> emplaceDeleteFunc =
		[this](ContentTag tag, deleteFunc DXfunc)
	{
		this->m_deleteFunc.emplace(tag, DXfunc);
	};
	static const loadFunc bindLoadGraph = std::bind(LoadGraph, _1, 0);
	static const loadFunc bindLoadSoundMem = std::bind(LoadSoundMem, _1, 3, -1);
	static const deleteFunc bindDeleteGraph = std::bind(DeleteGraph, _1, 0);
	static const deleteFunc bindDeleteSoundMem = std::bind(DeleteSoundMem, _1, 0);
	static const deleteFunc bindDeleteModel = [] (int handle) { MV1TerminateCollInfo(handle); return MV1DeleteModel(handle); };

	//�ɂ��g���q��enum�Ɗ֐����ȒP�ɂ܂Ƃ߂邱�Ƃ��ł���
	emplaceFunc("x", ContentTag::Model, MV1LoadModel);
	emplaceFunc("mqo", ContentTag::Model, MV1LoadModel);
	emplaceFunc("pmx", ContentTag::Model, MV1LoadModel);
	emplaceFunc("pmd", ContentTag::Model, MV1LoadModel);
	emplaceFunc("jpg", ContentTag::Texture, bindLoadGraph);
	emplaceFunc("png", ContentTag::Texture, bindLoadGraph);
	emplaceFunc("bmp", ContentTag::Texture, bindLoadGraph);
	emplaceFunc("wav", ContentTag::SE, bindLoadSoundMem);
	emplaceFunc("mp3", ContentTag::BGM, bindLoadSoundMem);
	emplaceFunc("vso", ContentTag::VertexShader, LoadVertexShader);
	emplaceFunc("pso", ContentTag::PixelShader, LoadPixelShader);
	
	emplaceDeleteFunc(ContentTag::Model, bindDeleteModel);
	emplaceDeleteFunc(ContentTag::Texture, bindDeleteGraph);
	emplaceDeleteFunc(ContentTag::BGM, bindDeleteSoundMem);
	emplaceDeleteFunc(ContentTag::SE, bindDeleteSoundMem);
	emplaceDeleteFunc(ContentTag::VertexShader, DeleteShader);
	emplaceDeleteFunc(ContentTag::PixelShader, DeleteShader);

}

std::string GetExtension(const std::string& filename)
{
	std::string ext;
	auto pos1 = filename.rfind('.');
	if (pos1 != std::string::npos){
		ext = filename.substr(pos1 + 1, filename.size() - pos1);
		auto itr = ext.begin();
		while (itr != ext.end()){
			*itr = (char)tolower(*itr);
			itr++;
		}
		itr = ext.end() - 1;
		while (itr != ext.begin()){    // �p�X�̍Ō��\0��X�y�[�X���������Ƃ��̑΍�
			if (*itr == 0 || *itr == 32){
				ext.erase(itr--);
			}
			else{
				itr--;
			}
		}
	}
	return ext;
}
void Loader::ErrLog(int contentHandle, const std::string& filename)
{
	if (contentHandle == -1)
	{
		MessageBox(NULL, (filename + "�ǂݍ��݂Ɏ��s���܂���").c_str(), "�t�@�C���ǂݍ��݃G���[", MB_ICONEXCLAMATION | MB_OK);
	}
}

void Loader::deleteContents()
{
	for (auto& data : m_oldContentsList)
	{
		if (!data.second.use)//�g���Ă��Ȃ����f�����폜
			m_deleteFunc[data.second.tag];
	}
}
void Loader::load()
{
	isLoadCompleted = false;
	SetUseASyncLoadFlag(TRUE);
	for (auto& data : m_ContentsList)
	{
		if (m_ContentsList.find(data.first)->second.handle != 0)
		{
			continue;
		}

		data.second.handle = m_LoadFunc[GetExtension(data.second.filename)].loadFunc( ("Resources/" + data.second.filename).c_str());
		MV1SetupCollInfo(data.second.handle);
	}
	SetUseASyncLoadFlag(FALSE);
}
bool Loader::isLoad() const
{
	int count = std::count_if(m_ContentsList.begin(), m_ContentsList.end(),
		[&](const std::pair<std::string, ContentDataAndTag>& contentData)
	{return (CheckHandleASyncLoad(contentData.second.handle) == TRUE); });
	//count > 0 �œǂݍ��ݒ�
	return !!count;
}
bool Loader::onCompleted()
{
	// ���[�h���I�����Ă��邩�ǂ���
	bool current = isLoadCompleted;

	// �񓯊��Ǎ�����0���ǂ���
	bool async = GetASyncLoadNum() == 0;

	// ���[�h���I�����Ă���@�������́@�񓯊��Ǎ�����0�łȂ��ꍇ
	return isLoadCompleted = !current && async;
}
void Loader::loadContent(const std::string& name, const std::string& filename)
{
	bool use = true;
	auto i = m_oldContentsList.find(name);
	if (i != m_oldContentsList.end())//�O��Ɠ����̂�����������
	{
		use = false;
	}
	else
	{
		m_oldContentsList[name].use = false;
	}
	m_ContentsList.emplace(std::piecewise_construct,
		std::forward_as_tuple(name),
		std::forward_as_tuple(m_LoadFunc[GetExtension(filename)].tag, 0, filename,use));
}

ContentMap Loader::getContentList(const ContentTag& tag) const
{
	ContentMap returnData;
	for (auto& data : m_ContentsList)
	{
		if (data.second.tag == tag)
		{
			returnData.emplace(std::piecewise_construct,
				std::forward_as_tuple(data.first),
				std::forward_as_tuple(data.second.handle, data.second.filename));
		}
	}
	return returnData;
}
ContentMap Loader::getModelList() const
{
	return getContentList(ContentTag::Model);
}
ContentMap Loader::getTextureList() const
{
	return getContentList(ContentTag::Texture);
}
ContentMap Loader::getBGMList() const
{
	return getContentList(ContentTag::BGM);
}
ContentMap Loader::getSEList() const
{
	return getContentList(ContentTag::SE);
}
void Loader::cleanUp()
{
	m_oldContentsList = m_ContentsList;
	for (auto &data : m_ContentsList)
	{
		m_deleteFunc[data.second.tag];
	}
	m_ContentsList.clear();
}
Loader::~Loader()
{
	for (auto&& data : m_ContentsList)
	{
		m_deleteFunc[data.second.tag](data.second.handle);
	}
}
