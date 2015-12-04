//+ �\ + *��*+�\ + *��*+�\ + *��*+�\ + *��*+�\ + *��*+�\ + �\ + *��*+�\ + *��*+�\ + *��*+�\ + *��*+�\ + *��*+�\ +
//�ӔC��:�Ȃ肽��
//+ �\ + *��*+�\ + *��*+�\ + *��*+�\ + *��*+�\ + *��*+�\ + �\ + *��*+�\ + *��*+�\ + *��*+�\ + *��*+�\ + *��*+�\ +
#pragma once
#include <string>
#include <unordered_map>
#include <atomic>
#include "DxLib.h"
#include "Utility/Def.h"

#include "Collision/IShape.h"
#include "Collision/Sphere.h"
#include "Collision/Capsule.h"
#include "Collision/Line.h"
#include "Collision/Triangle.h"

# include "Vector2.h"
# include "Vector3.h"
# include "Matrix.h"
# include "Pose.h"
//�`��̂��߂̃f�[�^
struct Buffer
{
	int depthBuffer;
};
struct ShaderHandle
{
	int depthRecord_skin;
	int depthRecord_normal;
	int depthRecord_pixel;
	int render_skin;
	int render_normal;
	int render_pixel;
};
struct LightCamera
{
	Matrix viewMatrix;
	Matrix projectionMatrix;
};
struct CameraData
{
	Vector3 pos;
	Vector3 terget;
};
struct FontData {
	int fontHandle;
	std::vector<std::string> text;
};
struct ModelData{
	int modelHandle;
	int animNumber = -1;
	int playAnim1;
	int playAnim2;
	float animPlayCount1;
	float animPlayCount2;
	float animBlendRate = 1.0f;
	bool isSkinMesh = false;
	bool use = true;
	ModelData(int modelHandle, int playAnim1, int playAnim2, float animPlayCount1, float animPlayCount2,bool use)
	{
		this->modelHandle = modelHandle;
		this->playAnim1 = playAnim1;
		this->playAnim2 = playAnim2;
		this->animPlayCount1 = animPlayCount1;
		this->animPlayCount2 = animPlayCount2;
		this->use = use;
	}
	ModelData(){}
};
class Renderer
{
public:
	Renderer();
	~Renderer();
public://MyGame�Ŏ���
	void setModelData(const ContentMap& modelData);
	void setTextureData(const ContentMap& textureData);
	void draw();
public:
	void drawNormalModel(const std::string& name, const Vector3& position, const Matrix& rotation)const;
	void drawSkinModel(const std::string& name, const Vector3& position, const Matrix& rotation, int animNumber, float frame);//�A�j���[�V�����t��
	void setScale(const std::string& name, const Vector3& scale);
	void refreshAnimParam(const std::string& name);
	void refreshAnimParam();

	/// <summary>3D�A�j���[�V�����`��</summary>
	/// <param name="name">���\�[�X��</param>
	/// <param name="pose">�p��</param>
	/// <param name="animationNumber">�A�j���[�V����No</param>
	/// <param name="t">�A�j���[�V�����䗦(0.0~1.0)</param>
	void drawSkinModel(const std::string& name, const Pose& pose, int animNumber, float t);

	//2D�n�֐�
	void drawTexture(const std::string& name, int x, int y, int cx, int cy, float width, float height, float angle) const;
	void drawTexture(const std::string& name, int x, int y);
	enum class AspectType
	{
		// �������Ȃ�
		None,
		// ��ʂɍ��킹�ĐL�k
		Fit,
		// ����
		LetterBox,
		// �g��
		Expand,
	};
	void drawTexture(const std::string& name, const AspectType& type);
	void drawTexture(const std::string& name, const AspectType& type, const Vector2& position, const Vector2& center);
	//�t�H���g�`��n�֐�
	void drawFont(const std::string& text);

	// �e�N�X�`���n���[�e�B���e�B ���Ƃňړ������܂�
	Point2 getTextureSize(const std::string& name);
	Point2 getWindowSize();
	Vector2 getCorrectionSize(const std::string& name, const AspectType& type);
public:
	// -----------------------------------------------------------
	// �v���~�e�B�u�^�`��
	// -----------------------------------------------------------

	void drawPrimitive(const Sphere& sphere) const;
private:
	void initDepthBuffer();
	void loadShader();
	void drawDepth();
	void drawModelWithDepthShadow();
	void setFont();
	void drawFont();
private:
	std::unordered_map<std::string, ModelData> m_modelData;
	std::unordered_map<std::string, int> m_textureData;
	Buffer m_buffer;
	ShaderHandle m_shaderHandle;
	FontData m_fontData;
	LightCamera m_lightCamera; 
	CameraData m_cameraData;
};