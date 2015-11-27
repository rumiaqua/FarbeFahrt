#include "SkinObject.h"
#include "Utility/Math.h"

#include "Utility/Input.h"
#include "Utility\SingletonFinalizer.h"
#include "Utility\HandleList.h"

namespace
{
	float frame = 0.0f;
}

SkinObject::SkinObject(IWorld& world, const std::string& modelName, const Vector3& position, int anmNo, float frameSpeed, float maxFrame, float scale, float angle, bool isLoop) :
	BaseActor(world, modelName, position, Matrix::Rotation(Vector3::Up(), Math::ToRadian(angle)), nullptr)
{
	m_name = modelName;
	m_frameSpeed = frameSpeed;
	m_maxframe = maxFrame;
	m_anmNo = anmNo;
	m_scale = scale;
	m_isLoop = isLoop;
}

void SkinObject::frameReset()
{
	frame = 0;
}

void SkinObject::onUpdate()
{
	if (isAnimate)
	{
		if (frame <= m_maxframe * m_frameSpeed)
		{
			frame += m_frameSpeed;
		}
		else
		{
			frame = fmodf(frame, m_maxframe);
		}
	}

	BaseActor::onUpdate();
}

void SkinObject::onDraw(Renderer & render) const
{
	auto worldPose = getWorldPose();
	Vector3 position = Matrix::Translation(worldPose);
	Matrix rotate = Matrix::Rotation(worldPose);
	render.setScale(m_name, Vector3(m_scale, m_scale, m_scale));
	render.drawSkinModel(m_name, position, rotate, m_anmNo, frame);

	BaseActor::onDraw(render);
}

void SkinObject::onMessage(const std::string& message, void* parameter)
{
	if (message == "Rotation")
	{
		Matrix::Rotate(getRotation(), Vector3::Up(), *(const float*)parameter);
	}
	if (message == "startAnimation")
	{
		isAnimate = true;
	}
	if (message == "stopAnimation")
	{
		isAnimate = false;
	}
	if (message == "resetAnimation")
	{
		frame = 0.0f;
	}
	BaseActor::onMessage(message, parameter);
}