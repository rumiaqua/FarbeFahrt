#include "Renderer.h"
#include <algorithm>
Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}
void Renderer::setModelData(const ContentMap& modelData)
{
	for (auto &data : modelData)
	{
		m_modelData.emplace(std::piecewise_construct,
			std::forward_as_tuple(data.first),
			std::forward_as_tuple(data.second.handle, -1, -1, 0.0f, 0.0f));
	}

}
void Renderer::setTextureData(const ContentMap& textureData)
{
	for (auto &data : textureData)
	{
		m_textureData.emplace(data.first,data.second.handle);
	}
}

void Renderer::draw()const
{

}

void Renderer::drawNormalModel(const std::string& name, const VECTOR& position, const VECTOR& rotation)const
{
	const int &handle = m_modelData.at(name).modelHandle;
	MV1SetPosition(handle, position);
	MV1SetRotationXYZ(handle, rotation);

	MV1DrawModel(handle);

}
void Renderer::drawSkinModel(const std::string& name, const VECTOR& position, const VECTOR& rotation, int animNumber, float speed)
{
	//見辛いから後々関数分けする予定
	//サンプル丸パクリスペクト
	float animTotalTime;
	auto& modelData = m_modelData[name];
	modelData.isSkinMesh = true;
	if (animNumber != modelData.animNumber)//アニメーションが切り替わった時
	{
		modelData.animNumber = animNumber;
		if (modelData.playAnim2 != -1)
		{
			MV1DetachAnim(modelData.modelHandle, modelData.playAnim2);
			modelData.playAnim2 = -1;
		}
		modelData.playAnim2 = modelData.playAnim1;
		modelData.animPlayCount2 = modelData.animPlayCount1;

		modelData.playAnim1 = MV1AttachAnim(modelData.modelHandle, modelData.animNumber);
		modelData.animPlayCount1 = 0.0f;
		modelData.animBlendRate = modelData.playAnim2 == -1 ? 1.0f : 0.0f;

	}

	if (modelData.animBlendRate < 1.0f)
	{
		modelData.animBlendRate += ANIM_BLEND_SPEED;
		if (modelData.animBlendRate > 1.0f)
		{
			modelData.animBlendRate = 1.0f;
		}
	}
	if (modelData.playAnim1 != -1)
	{
		animTotalTime = MV1GetAttachAnimTotalTime(modelData.modelHandle, modelData.playAnim1);
		modelData.animPlayCount1 += speed;
		if (modelData.animPlayCount1 >= animTotalTime)
		{
			modelData.animPlayCount1 = fmod(modelData.animPlayCount1, animTotalTime);
		}
		MV1SetAttachAnimTime(modelData.modelHandle, modelData.playAnim1, modelData.animPlayCount1);
		MV1SetAttachAnimBlendRate(modelData.modelHandle, modelData.playAnim1, modelData.animBlendRate);
	}
	if (modelData.playAnim2 != -1)
	{
		animTotalTime = MV1GetAttachAnimTotalTime(modelData.modelHandle, modelData.playAnim2);
		modelData.animPlayCount2 += speed;
		if (modelData.animPlayCount2 >= animTotalTime)
		{
			modelData.animPlayCount2 = fmod(modelData.animPlayCount2, animTotalTime);
		}
		MV1SetAttachAnimTime(modelData.modelHandle, modelData.playAnim2, modelData.animPlayCount2);
		MV1SetAttachAnimBlendRate(modelData.modelHandle, modelData.playAnim2, 1.0f - modelData.animBlendRate);
	}
	//現在のアニメーションを再生

	drawNormalModel(name, position, rotation);
}

void Renderer::setScale(const std::string& name, const VECTOR& scale)
{
	MV1SetScale(m_modelData[name].modelHandle, scale);
}

void Renderer::drawTexture(const std::string& name, int x, int y,int cx,int cy, float width, float height, float angle)
{
	DrawRotaGraph3(x, y,cx, cy, width, height,
		(double)angle, m_textureData[name], FALSE, FALSE);
}