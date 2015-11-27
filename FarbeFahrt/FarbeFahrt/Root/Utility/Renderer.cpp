#include "Renderer.h"
#include <algorithm>
#include "Actor\Camera\Camera.h"

Renderer::Renderer()
{
	initDepthBuffer();
	loadShader();
}

Renderer::~Renderer()
{
}
void Renderer::initDepthBuffer()
{
	MV1SetSemiTransDrawMode(DX_SEMITRANSDRAWMODE_NOT_SEMITRANS_ONLY);
	SetDrawValidFloatTypeGraphCreateFlag(TRUE);
	SetCreateDrawValidGraphChannelNum(1);

	m_buffer.depthBuffer = MakeScreen(4096, 4096, FALSE);

	SetDrawValidFloatTypeGraphCreateFlag(FALSE);
	SetCreateDrawValidGraphChannelNum(4);
	SetCreateGraphColorBitDepth(32);
}
void Renderer::loadShader()
{
	m_shaderHandle.depthRecord_normal = LoadVertexShader("Resources/Shader/depthRecord_normal.vso");
	m_shaderHandle.depthRecord_skin = LoadVertexShader("Resources/Shader/depthRecord_skin.vso");
	m_shaderHandle.depthRecord_pixel = LoadPixelShader("Resources/Shader/depthRecord_pixel.pso");
	m_shaderHandle.render_normal = LoadVertexShader("Resources/Shader/render_normal.vso");
	m_shaderHandle.render_skin = LoadVertexShader("Resources/Shader/render_skin.vso");
	m_shaderHandle.render_pixel = LoadPixelShader("Resources/Shader/render_pixel.pso");

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
void Renderer::drawDepth()
{
	Vector3 lightDirection = GetLightDirection();
	Vector3 lightPosition = {40.0f,100.0f,-150.0f};
	Vector3 lightTarget = Vector3::Zero();
	SetDrawScreen(m_buffer.depthBuffer);

	SetBackgroundColor(255, 255, 255);
	ClearDrawScreen();
	SetBackgroundColor(0, 0, 0);

	SetupCamera_Ortho(300.0f);
	SetCameraNearFar(1.0f, 300.0f);
	SetCameraPositionAndTarget_UpVecY(lightPosition, lightTarget);

	m_lightCamera.viewMatrix = GetCameraViewMatrix();
	m_lightCamera.projectionMatrix = GetCameraProjectionMatrix();

	MV1SetUseOrigShader(TRUE);
	SetUsePixelShader(m_shaderHandle.depthRecord_pixel);
	for (auto model : m_modelData)
	{
		if (model.second.isSkinMesh)//スキンメッシュの影描画用
		{
			SetUseVertexShader(m_shaderHandle.depthRecord_skin);
		}
		//剛体メッシュの影描画用
		else
		{
			SetUseVertexShader(m_shaderHandle.depthRecord_normal);
		}
		MV1DrawModel(model.second.modelHandle);
	}
	MV1SetUseOrigShader(FALSE);
	SetDrawScreen(DX_SCREEN_BACK);
}
void Renderer::drawModelWithDepthShadow()
{
	SetCameraNearFar(1.0f, 12000.0f);
	SetCameraPositionAndTarget_UpVecY(m_cameraData.pos, m_cameraData.terget);
	MV1SetUseOrigShader(TRUE);
	SetUsePixelShader(m_shaderHandle.render_pixel);
	SetVSConstFMtx(43, m_lightCamera.viewMatrix);
	SetVSConstFMtx(47, m_lightCamera.projectionMatrix);

	// 影用深度記録画像をテクスチャ１にセット
	SetUseTextureToShader(1, m_buffer.depthBuffer);
	for (auto model : m_modelData)
	{
		if (model.second.isSkinMesh)//スキンメッシュの影描画用
		{
			SetUseVertexShader(m_shaderHandle.render_skin);
		}
		//剛体メッシュの影描画用
		else
		{
			SetUseVertexShader(m_shaderHandle.render_normal);
		}
		MV1DrawModel(model.second.modelHandle);
	}
	MV1SetUseOrigShader(FALSE);
	SetUseTextureToShader(1, -1);
	ResetVSConstF(43, 8);
}
void Renderer::draw()
{
	m_cameraData.pos = GetCameraPosition();
	m_cameraData.terget = GetCameraTarget();
	drawDepth();
	drawModelWithDepthShadow();
}

void Renderer::drawNormalModel(const std::string& name, const Vector3& position, const Matrix& rotation)const
{
	const int &handle = m_modelData.at(name).modelHandle;
	MV1SetPosition(handle, position);
	MV1SetRotationMatrix(handle, rotation);

	//MV1DrawModel(handle);

}
void Renderer::refreshAnimParam(const std::string& name)
{
	auto& modeldata = m_modelData.at(name);
	modeldata.playAnim1 = -1;
	modeldata.playAnim2 = -1;
	modeldata.animPlayCount1 = 0.0f;
	modeldata.animPlayCount2 = 0.0f;

}
void Renderer::refreshAnimParam()
{
	for (auto&& model : m_modelData)
	{
		refreshAnimParam(model.first);
	}
}
void Renderer::drawSkinModel(const std::string& name, const Vector3& position,
	const Matrix& rotation, int animNumber, float frame)
{
	//見辛いから後々関数分けする予定
	//サンプル丸パクリスペクト
	float animTotalTime;
	auto& modelData = m_modelData.at(name);
	modelData.isSkinMesh = true;
	if (animNumber != modelData.animNumber)//アニメーションが切り替わった時
	{
		modelData.animNumber = animNumber;
		if (modelData.playAnim2 != -1)
		{
			int result = MV1DetachAnim(modelData.modelHandle, modelData.playAnim2);
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
		modelData.animPlayCount1 = frame;
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
		modelData.animPlayCount2 = frame;
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

void Renderer::setScale(const std::string& name, const Vector3& scale)
{
	MV1SetScale(m_modelData.at(name).modelHandle, scale);
}

void Renderer::drawSkinModel(const std::string& name, const Pose& pose, int animNumber, float t)
{
	//見辛いから後々関数分けする予定
	//サンプル丸パクリスペクト
	float animTotalTime;
	auto& modelData = m_modelData.at(name);
	modelData.isSkinMesh = true;
	if (animNumber != modelData.animNumber)//アニメーションが切り替わった時
	{
		modelData.animNumber = animNumber;
		if (modelData.playAnim2 != -1)
		{
			int result = MV1DetachAnim(modelData.modelHandle, modelData.playAnim2);
			modelData.playAnim2 = -1;
		}
		modelData.playAnim2 = modelData.playAnim1;
		modelData.animPlayCount2 = modelData.animPlayCount1;

		modelData.playAnim1 = MV1AttachAnim(modelData.modelHandle, modelData.animNumber);
		modelData.animPlayCount1 = 0.0f;
		modelData.animBlendRate = modelData.playAnim2 == -1 ? 1.0f : 0.0f;

	}

	float totalTime = MV1GetAttachAnimTotalTime(m_modelData.at(name).modelHandle, modelData.playAnim1);
	float frame =  totalTime * t;

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
		modelData.animPlayCount1 = frame;
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
		modelData.animPlayCount2 = frame;
		if (modelData.animPlayCount2 >= animTotalTime)
		{
			modelData.animPlayCount2 = fmod(modelData.animPlayCount2, animTotalTime);
		}
		MV1SetAttachAnimTime(modelData.modelHandle, modelData.playAnim2, modelData.animPlayCount2);
		MV1SetAttachAnimBlendRate(modelData.modelHandle, modelData.playAnim2, 1.0f - modelData.animBlendRate);
	}
	//現在のアニメーションを再生

	drawNormalModel(name, pose.position, pose.rotation);
}

void Renderer::drawTexture(const std::string& name, int x, int y,int cx,int cy, float width, float height, float angle) const
{
	DrawRotaGraph3(x, y,cx, cy, width, height,
		(double)angle, m_textureData.at(name), FALSE, FALSE);
}
void Renderer::drawTexture(const std::string& name, int x, int y)
{
	DrawGraph(x, y, m_textureData.at(name),TRUE);
}