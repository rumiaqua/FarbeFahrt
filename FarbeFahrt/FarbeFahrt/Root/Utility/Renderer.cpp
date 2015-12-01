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

// �[�x�`��H
void Renderer::drawDepth()
{
	// �����p�����[�^
	Vector3 lightDirection = GetLightDirection();
	Vector3 lightPosition = {40.0f,100.0f,-150.0f};
	Vector3 lightTarget = Vector3::Zero();
	// �[�x�o�b�t�@�ɕ`��^�[�Q�b�g��ݒ�
	SetDrawScreen(m_buffer.depthBuffer);

	// �w�i�𔒂ŃN���A
	SetBackgroundColor(255, 255, 255);
	// �`��^�[�Q�b�g���N���A
	ClearDrawScreen();
	// �w�i�F�����ŃN���A
	SetBackgroundColor(0, 0, 0);

	// �J�����̓����ˉe�s��𐳎ˉe�ɕύX
	SetupCamera_Ortho(300.0f);
	// �N���b�v�ʂ̐ݒ�
	SetCameraNearFar(1.0f, 300.0f);
	// �J�����̃r���[�s������C�g���猩���ʒu�ɕύX
	SetCameraPositionAndTarget_UpVecY(lightPosition, lightTarget);

	// ���݂̐ݒ��ێ�
	m_lightCamera.viewMatrix = GetCameraViewMatrix();
	m_lightCamera.projectionMatrix = GetCameraProjectionMatrix();

	// ����V�F�[�_�[�̎g�p�J�n
	MV1SetUseOrigShader(TRUE);
	// �s�N�Z���V�F�[�_�[���w��
	SetUsePixelShader(m_shaderHandle.depthRecord_pixel);
	// �S���f���f�[�^�̕\��
	for (auto model : m_modelData)
	{
		// �X�L�����b�V���ł����
		if (model.second.isSkinMesh)//�X�L�����b�V���̉e�`��p
		{
			// �X�L�����b�V���p�̒��_�V�F�[�_�[���g�p
			SetUseVertexShader(m_shaderHandle.depthRecord_skin);
		}
		//���̃��b�V���̉e�`��p
		// �����łȂ����
		else
		{
			// ���̃��b�V���p�̒��_�V�F�[�_�[���g�p
			SetUseVertexShader(m_shaderHandle.depthRecord_normal);
		}
		// ���f���̕`��
		MV1DrawModel(model.second.modelHandle);
	}
	// ����V�F�[�_�[�̎g�p�I��
	MV1SetUseOrigShader(FALSE);
	// �`��^�[�Q�b�g��w�ʂɕύX
	SetDrawScreen(DX_SCREEN_BACK);
}
// ���f�����e�ƈꏏ�ɕ`��
void Renderer::drawModelWithDepthShadow()
{
	// �N���b�v�ʂ̎w��
	SetCameraNearFar(1.0f, 12000.0f);
	// �J�����̃r���[�s���ۑ������s��ɕύX
	SetCameraPositionAndTarget_UpVecY(m_cameraData.pos, m_cameraData.terget);
	// ����V�F�[�_�[�̎g�p�J�n
	MV1SetUseOrigShader(TRUE);
	// �s�N�Z���V�F�[�_�[���w��
	SetUsePixelShader(m_shaderHandle.render_pixel);
	// �r���[�s����V�F�[�_�[�ɃZ�b�g
	SetVSConstFMtx(43, m_lightCamera.viewMatrix);
	// �����ˉe�s����V�F�[�_�[�ɃZ�b�g
	SetVSConstFMtx(47, m_lightCamera.projectionMatrix);

	// �e�p�[�x�L�^�摜���e�N�X�`���P�ɃZ�b�g
	SetUseTextureToShader(1, m_buffer.depthBuffer);
	// �S���f���f�[�^�̕`��
	for (auto model : m_modelData)
	{
		// �X�L�����b�V���ł����
		if (model.second.isSkinMesh)//�X�L�����b�V���̉e�`��p
		{
			// 
			// �X�L�����b�V���p�̒��_�V�F�[�_�[���g�p
			SetUseVertexShader(m_shaderHandle.render_skin);
		}
		//���̃��b�V���̉e�`��p
		// �����łȂ����
		else
		{
			// ���̃��b�V���p�̒��_�V�F�[�_�[���g�p
			SetUseVertexShader(m_shaderHandle.render_normal);
		}
		// ���f���̕`��
		MV1DrawModel(model.second.modelHandle);
	}
	// ����V�F�[�_�[�̎g�p�I��
	MV1SetUseOrigShader(FALSE);
	// �e�N�X�`���P�𖳌��ɂ���
	SetUseTextureToShader(1, -1);
	// �X���b�g43���������H
	ResetVSConstF(43, 8);
}
void Renderer::draw()
{
	// ���݂̐ݒ��ێ�
	m_cameraData.pos = GetCameraPosition();
	m_cameraData.terget = GetCameraTarget();
	// �[�x�̕`��
	drawDepth();
	// �e�̕`��
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
	//���h�������X�֐���������\��
	//�T���v���ۃp�N���X�y�N�g
	float animTotalTime;
	auto& modelData = m_modelData.at(name);
	modelData.isSkinMesh = true;
	if (animNumber != modelData.animNumber)//�A�j���[�V�������؂�ւ������
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
	//���݂̃A�j���[�V�������Đ�

	drawNormalModel(name, position, rotation);
}

void Renderer::setScale(const std::string& name, const Vector3& scale)
{
	MV1SetScale(m_modelData.at(name).modelHandle, scale);
}

void Renderer::drawSkinModel(const std::string& name, const Pose& pose, int animNumber, float t)
{
	//���h�������X�֐���������\��
	//�T���v���ۃp�N���X�y�N�g
	float animTotalTime;
	auto& modelData = m_modelData.at(name);
	modelData.isSkinMesh = true;
	if (animNumber != modelData.animNumber)//�A�j���[�V�������؂�ւ������
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
	//���݂̃A�j���[�V�������Đ�

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