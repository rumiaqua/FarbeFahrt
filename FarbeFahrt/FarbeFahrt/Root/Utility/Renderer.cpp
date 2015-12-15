#include "Renderer.h"
#include <algorithm>
#include "Actor\Camera\Camera.h"

# include "Point2.h"
# include "Vector2.h"
# include "Math.h"

# include "Collision/IShape.h"

# include "Debug.h"

Renderer::Renderer()
{
	initDepthBuffer();
	loadShader();
	setFont();
}

Renderer::~Renderer()
{
	RemoveFontResourceEx("Resources/Font/cinecaption2.28.ttf", FR_PRIVATE, NULL);
}
void Renderer::setFont()
{
	if (AddFontResourceEx("Resources/Font/cinecaption2.28.ttf", FR_PRIVATE, NULL) > 0) {
	}
	else {
		// �t�H���g�Ǎ��G���[����s
		MessageBox(NULL, "�t�H���g�Ǎ����s", "", MB_OK);
	}
	m_fontData.fontHandle = CreateFontToHandle("���˂���Ղ����", fontSize, 3, DX_FONTTYPE_ANTIALIASING_EDGE, -1, 2);
	ChangeFontType(DX_FONTTYPE_ANTIALIASING_EDGE);

	ChangeFont("���˂���Ղ����", DX_CHARSET_DEFAULT);

}
void Renderer::drawPrimitive(const IShape& shape) const
{
	if (!Debug::IsEnabled())
	{
		return;
	}
	m_primitives.push_back([&shape] () { shape.draw(); });
}
void Renderer::initDepthBuffer()
{
	MV1SetSemiTransDrawMode(DX_SEMITRANSDRAWMODE_NOT_SEMITRANS_ONLY);
	SetDrawValidFloatTypeGraphCreateFlag(TRUE);
	SetCreateDrawValidGraphChannelNum(1);

	m_buffer.depthBuffer = MakeScreen(2048, 2048, FALSE);

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
		m_textureData.emplace(data.first, data.second.handle);
	}
}

// �[�x�`��H
void Renderer::drawDepth()
{
	Vector3 lightPosition = { 20.0f,120.0f,-70.0f };
	Vector3 lightTarget{ -45.0f,-30.0f,0.0f };
	SetDrawScreen(m_buffer.depthBuffer);
	SetBackgroundColor(255, 255, 255);
	// �`��^�[�Q�b�g���N���A
	ClearDrawScreen();
	// �w�i�F�����ŃN���A
	SetBackgroundColor(0, 0, 0);

	SetupCamera_Ortho(500.0f);
	SetCameraNearFar(1.0f, 500.0f);
	SetCameraPositionAndTarget_UpVecY(lightPosition, lightTarget);

	// ���݂̐ݒ��ێ�
	m_lightCamera.viewMatrix = GetCameraViewMatrix();
	m_lightCamera.projectionMatrix = GetCameraProjectionMatrix();

	// ����V�F�[�_�[�̎g�p�J�n
	MV1SetUseOrigShader(TRUE);
	// �s�N�Z���V�F�[�_�[���w��
	SetUsePixelShader(m_shaderHandle.depthRecord_pixel);
	// �S���f���f�[�^�̕\��
	for (auto&& model : m_modelData)
	{
		if (model.second.Use == false)
		{
			continue;
		}
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
	SetCameraNearFar(1.0f, 600.0f);
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
	for (auto& model : m_modelData)
	{
		if (model.second.Use == false)
		{
			continue;
		}
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
		model.second.Use = false;
	}
	// ����V�F�[�_�[�̎g�p�I��
	MV1SetUseOrigShader(FALSE);
	// �e�N�X�`���P�𖳌��ɂ���
	SetUseTextureToShader(1, -1);
	// �X���b�g43���������H
	ResetVSConstF(43, 8);
}
void Renderer::setDrawList(const std::string& name, int handle)
{
	drawList.push_back(std::make_pair(name, handle));
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

	// �v���~�e�B�u�̕`��
	for (auto&& func : m_primitives)
	{
		func();
	}
	m_primitives.clear();

	// �t�H���g�̕`��
	drawFont();
}
void Renderer::drawFont()
{
	// �t�H���g�n���h��
	int handle = m_fontData.fontHandle;
	// �����F
	unsigned int color = GetColor(255, 255, 255);
	// ���F
	int edge = GetColor(0, 0, 0);

	// ��ʕ�
	int windowWidth = getWindowSize().x;
	// ��ʍ���
	int windowHeight = getWindowSize().y;

	for (auto&& data : m_fontData.buffer)
	{
		// �e�L�X�g�̒���
		std::string::size_type size = data.length;
		// �e�L�X�g�̉���
		int textWidth = GetDrawStringWidthToHandle(data.text.c_str(), data.text.length(), handle);
		// �e�L�X�g�̏c��
		int textHeight = fontSize + 6;

		// x���W
		int x;
		switch (data.widthPlacement)
		{
		case WidthPlacement::Left:
			x = 0;
			break;
		case WidthPlacement::Right:
			x = windowWidth - textWidth;
			break;
		case WidthPlacement::Center:
			x = (windowWidth - textWidth) / 2.0f;
			break;
		}

		// y���W
		int y;
		switch (data.heightPlacement)
		{
		case HeightPlacement::Top:
			y = 0;
			break;
		case HeightPlacement::Bottom:
			y = windowHeight - textHeight;
			break;
		case HeightPlacement::Center:
			y = (windowHeight - textHeight) / 2.0f;
			break;
		}

		// �`��
		std::string renderingText = String::ToNarrow(String::ToWide(data.text).substr(0, data.length));
		DrawStringToHandle(x + data.x, y + data.y, renderingText.c_str(), color, handle, edge);
	}
	m_fontData.buffer.clear();
}
void Renderer::drawNormalModel(const std::string& name, const Vector3& position, const Matrix& rotation)
{
	const int &handle = m_modelData.at(name).modelHandle;
	MV1SetPosition(handle, position);
	MV1SetRotationMatrix(handle, rotation);
	m_modelData.at(name).Use = true;
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
	const Matrix& rotation, int animNumber, float frame, bool isBlend)
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
	float frame = totalTime * t;

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

void Renderer::drawTexture(const std::string& name, int x, int y, int cx, int cy, float width, float height, float angle) const
{
	DrawRotaGraph3(x, y, cx, cy, width, height,
		(double)angle, m_textureData.at(name), FALSE, FALSE);
}
void Renderer::drawTexture(const std::string& name, int x, int y)
{
	DrawGraph(x, y, m_textureData.at(name), TRUE);
}

void Renderer::drawTexture(const std::string& name, const AspectType& type)
{
	drawTexture(name, type, Vector2::Zero(), { 0.5f, 0.5f });
}
void Renderer::drawTexture(const std::string& name, const AspectType& type, const Vector2& position, const Vector2& center)
{
	int handle = m_textureData.at(name);
	Point2 size;
	GetGraphSize(handle, &size.x, &size.y);
	Vector2 textureSize = (Vector2)size;
	GetWindowSize(&size.x, &size.y);
	Vector2 windowSize = (Vector2)size;

	Vector2 ext;

	// �������Ȃ�
	if (type == AspectType::None)
	{
		ext = Vector2::One();
	}
	// ��ʂɍ��킹�ĐL�k
	if (type == AspectType::Fit)
	{
		ext = windowSize / textureSize;
	}
	// ����
	if (type == AspectType::LetterBox)
	{
		ext = windowSize / textureSize;
		ext.x = ext.y = Math::Min({ ext.x, ext.y });
	}
	// �g��
	if (type == AspectType::Expand)
	{
		ext = windowSize / textureSize;
		ext.x = ext.y = Math::Max({ ext.x, ext.y });
	}

	Vector2 correctionSize = textureSize * ext;
	Vector2 pos = (windowSize - correctionSize) * center + position;

	DrawRotaGraph3F(pos.x, pos.y, 0.0f, 0.0f, ext.x, ext.y, 0.0, handle, TRUE, FALSE);
}
void Renderer::drawFont(const std::string& text)
{
	m_fontData.buffer.emplace_back(
		text,
		String::ToWide(text).length(),
		0, WidthPlacement::Left,
		0, HeightPlacement::Top);
}

void Renderer::drawFont(const std::string& text, int x, int y)
{
	m_fontData.buffer.emplace_back(
		text,
		String::ToWide(text).length(),
		x, WidthPlacement::Left,
		y, HeightPlacement::Top);
}

void Renderer::drawFontCenter(const std::string& text, int y)
{
	m_fontData.buffer.emplace_back(
		text,
		String::ToWide(text).length(),
		0, WidthPlacement::Center,
		y, HeightPlacement::Top);
}

void Renderer::drawFont(const std::string& text, int length, int x, const WidthPlacement& width, int y, const HeightPlacement& height)
{
	m_fontData.buffer.emplace_back(
		text,
		length,
		x, width,
		y, height);
}

Point2 Renderer::getTextureSize(const std::string& name)
{
	Point2 size;
	GetGraphSize(m_textureData.at(name), &size.x, &size.y);
	return size;
}

Point2 Renderer::getWindowSize()
{
	Point2 size;
	GetWindowSize(&size.x, &size.y);
	return size;
}

Vector2 Renderer::getCorrectionSize(const std::string& name, const AspectType& type)
{
	Vector2 textureSize(getTextureSize(name));
	Vector2 windowSize(getWindowSize());

	Vector2 ext;

	// �������Ȃ�
	if (type != AspectType::None)
	{
		ext = Vector2::One();
	}
	// ��ʂɍ��킹�ĐL�k
	if (type == AspectType::Fit)
	{
		ext = windowSize / textureSize;
	}
	// ����
	if (type == AspectType::LetterBox)
	{
		ext = windowSize / textureSize;
		ext.x = ext.y = Math::Min({ ext.x, ext.y });
	}
	// �g��
	if (type == AspectType::Expand)
	{
		ext = windowSize / textureSize;
		ext.x = ext.y = Math::Max({ ext.x, ext.y });
	}

	return textureSize * ext;
}
