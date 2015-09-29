//+ ― + *☆*+― + *☆*+― + *☆*+― + *☆*+― + *☆*+― + ― + *☆*+― + *☆*+― + *☆*+― + *☆*+― + *☆*+― +
//責任者:なりたん
//+ ― + *☆*+― + *☆*+― + *☆*+― + *☆*+― + *☆*+― + ― + *☆*+― + *☆*+― + *☆*+― + *☆*+― + *☆*+― +
#pragma once
#include <string>
#include <unordered_map>
#include <atomic>
#include "DxLib.h"
#include "Utility/Def.h"
//描画のためのデータ

struct ModelData{
	int modelHandle;
	int animNumber = -1;
	int playAnim1;
	int playAnim2;
	float animPlayCount1;
	float animPlayCount2;
	float animBlendRate = 1.0f;
	bool isSkinMesh = false;
	ModelData(int modelHandle, int playAnim1, int playAnim2, float animPlayCount1, float animPlayCount2)
	{
		this->modelHandle = modelHandle;
		this->playAnim1 = playAnim1;
		this->playAnim2 = playAnim2;
		this->animPlayCount1 = animPlayCount1;
		this->animPlayCount2 = animPlayCount2;
	}
	ModelData(){}
};

class Renderer
{
public:
	Renderer();
	~Renderer();
public://MyGameで実装
	void setModelData(const ContentMap& modelData);
	void setTextureData(const ContentMap& textureData);
	void draw()const;
public:
	void drawNormalModel(const std::string& name, const VECTOR& position, const VECTOR& rotation)const;
	void drawSkinModel(const std::string& name, const VECTOR& position, const VECTOR& rotation, int animNumber, float speed);//アニメーション付き
	void setScale(const std::string& name, const VECTOR& scale);

	//2D系関数
	void drawTexture(const std::string& name, int x, int y, float width, float height,float angle);
private:
	std::unordered_map<std::string, ModelData> m_modelData;
	std::unordered_map<std::string, int> m_textureData;

};