#include "Loader.h"
#include <algorithm>
#include "DxLib.h"
#include <iostream>
#include <thread>

Loader::Loader()
	: m_onCompleted(true),
	m_isChangedScene(false)
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
	static const deleteFunc bindDeleteModel = [](int handle) { MV1TerminateCollInfo(handle); return MV1DeleteModel(handle); };

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

	emplaceDeleteFunc(ContentTag::Model, bindDeleteModel);
	emplaceDeleteFunc(ContentTag::Texture, bindDeleteGraph);
	emplaceDeleteFunc(ContentTag::BGM, bindDeleteSoundMem);
	emplaceDeleteFunc(ContentTag::SE, bindDeleteSoundMem);

}

std::string GetExtension(const std::string& filename)
{
	std::string ext;
	auto pos1 = filename.rfind('.');
	if (pos1 != std::string::npos) {
		ext = filename.substr(pos1 + 1, filename.size() - pos1);
		auto itr = ext.begin();
		while (itr != ext.end()) {
			*itr = (char)tolower(*itr);
			itr++;
		}
		itr = ext.end() - 1;
		while (itr != ext.begin()) {    // �p�X�̍Ō��\0��X�y�[�X���������Ƃ��̑΍�
			if (*itr == 0 || *itr == 32) {
				ext.erase(itr--);
			}
			else {
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
		if (!data.second.contentData.use)//�g���Ă��Ȃ����f�����폜
			m_deleteFunc[data.second.tag];
	}
}
void Loader::load()
{
	m_onCompleted = false;
	m_isChangedScene = true;

	loadASync();
}
void Loader::loadASync()
{

	for (auto& i : m_oldContentsList)//�O��̃V�[���̌Â��R���e���c���X�g�����ĉ��
	{
		auto& j = m_ContentsList.find(i.first);//���̃R���e���c���X�g�ɂ��邩�ǂ������ׂ�
		if (j != m_ContentsList.end())//������Ȃ�������
		{
			j->second.contentData.use = false;//use�t���O��false�ɂ���
		}
	}

	SetUseASyncLoadFlag(TRUE);
	for (auto& data : m_ContentsList)
	{
		if (m_ContentsList.find(data.first)->second.contentData.handle != 0)
		{
			continue;
		}

		data.second.contentData.handle = m_LoadFunc[GetExtension(data.second.contentData.filename)].loadFunc(("Resources/" + data.second.contentData.filename).c_str());
		MV1SetupCollInfo(data.second.contentData.handle);
	}
	SetUseASyncLoadFlag(FALSE);

}
bool Loader::isLoad() const
{
	if (!m_isChangedScene)//�V�[�����ς���ĂȂ��Ȃ��������ł���
	{
		return false;
	}
	int count = std::count_if(m_ContentsList.begin(), m_ContentsList.end(),
		[&](const std::pair<std::string, ContentDataAndTag>& contentData)
	{return (CheckHandleASyncLoad(contentData.second.contentData.handle) == TRUE); });

	//count > 0 �œǂݍ��ݒ�
	return !!count;
}
bool Loader::onCompleted()
{
	if (!m_onCompleted)
	{
		m_onCompleted = true;
		m_isChangedScene = false;
		return true;
	}
	return false;
}

void Loader::loadContent(const std::string& name, const std::string& filename)
{
	auto i = m_oldContentsList.find(name);
	if (i != m_oldContentsList.end())//�O��Ɠ����̂�����������
	{
		return;
	}
	ContentData contentData;
	contentData.filename = filename;
	contentData.handle = 0;
	contentData.use = true;
	m_ContentsList.emplace(std::piecewise_construct,
		std::forward_as_tuple(name),
		std::forward_as_tuple(m_LoadFunc[GetExtension(filename)].tag, contentData));
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
				std::forward_as_tuple(data.second.contentData));
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
ContentMap Loader::getContentsList() const
{
	ContentMap returnData;
	for (auto& data : m_ContentsList)
	{
		returnData.emplace(std::make_pair(data.first, data.second.contentData));
	}
	return returnData;
}
void Loader::cleanUp()
{
	m_oldContentsList = m_ContentsList;

	
}
Loader::~Loader()
{
	for (auto&& data : m_ContentsList)
	{
		m_deleteFunc[data.second.tag](data.second.contentData.handle);
	}
	for (auto&& data : m_oldContentsList)
	{
		m_deleteFunc[data.second.tag](data.second.contentData.handle);
	}
}
