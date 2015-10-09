#include "Loader.h"
#include <algorithm>
#include "DxLib.h"

Loader::Loader()
{


	m_ContentList.clear();






	//std::string�ƁAenum��const char*�������ɂƂ�int��Ԃ��֐��̍\����
	//��std::unordred_map
	//��emplace����
	//���߂�const char*�ƁAenum�ƁAconst char*�������ɂƂ�int��Ԃ��֐�
	//�������ɂƂ�֐�
	using namespace std::placeholders;
	using Func = std::function<int(const char*)>;
	std::function<void(const char*, ContentTag, Func)> emplaceFunc =
		[this](const char* c, ContentTag tag, Func& DXfunc)
	{
		this->m_LoadFunc.emplace(std::piecewise_construct, 
			std::forward_as_tuple(c), std::forward_as_tuple(tag, DXfunc));
	};
	static const Func bindLoadGraph = std::bind(LoadGraph, _1, 0);
	static const Func bindLoadSoundMem = std::bind(LoadSoundMem, _1, 3, -1);

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



}
std::string GetExtension(const std::string& filename)
{
	std::string ext;
	auto pos1 = filename.rfind('.');
	if (pos1 != std::string::npos){
		ext = filename.substr(pos1 + 1, filename.size() - pos1);
		auto itr = ext.begin();
		while (itr != ext.end()){
			*itr = tolower(*itr);
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
void Loader::load()
{
	//SetUseASyncLoadFlag(TRUE);
	for (auto& data : m_ContentList)
	{
		data.second.handle = m_LoadFunc[GetExtension(data.second.filename)].func( ("Resources/" + data.second.filename).c_str());
	}
	//SetUseASyncLoadFlag(FALSE);
	isLoadCompleted = false;
}
bool Loader::isLoad()
{
	int count = std::count_if(m_ContentList.begin(), m_ContentList.end(),
		[&](const std::pair<std::string, ContentDataPlusTag>& contentData)
	{return (CheckHandleASyncLoad(contentData.second.handle) == TRUE); });
	//count > 0 �œǂݍ��ݒ�
	return !!count;
}
void Loader::loadContent(const std::string& name, const std::string& filename)
{
	m_ContentList.emplace(std::piecewise_construct,
		std::forward_as_tuple(name),
		std::forward_as_tuple(m_LoadFunc[GetExtension(filename)].tag, 0, filename));
}
ContentMap Loader::getContentList(const ContentTag& tag)
{
	ContentMap returnData;
	for (auto& data : m_ContentList)
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
ContentMap Loader::getModelList()
{
	return getContentList(ContentTag::Model);
}
ContentMap Loader::getTextureList()
{
	return getContentList(ContentTag::Texture);
}
ContentMap Loader::getBGMList()
{
	return getContentList(ContentTag::BGM);
}
ContentMap Loader::getSEList()
{
	return getContentList(ContentTag::SE);
}
void Loader::cleanUp()
{
	for (auto &data : m_ContentList)
	{
		MV1DeleteModel(data.second.handle);
	}
	m_ContentList.clear();
}
Loader::~Loader()
{
}