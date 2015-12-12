#include "SkinObject.h"
#include "Utility/Math.h"

#include "Utility/Input.h"
#include "Utility\SingletonFinalizer.h"
#include "Utility\HandleList.h"

#include "Utility/Debug.h"

namespace
{
	float frame = 0.0f;
}

SkinObject::SkinObject(IWorld& world, const std::string& modelName, const Vector3& position, int anmNo, float frameSpeed, float maxFrame, float scale, float angle, bool isLoop, float radius) :
	BaseActor(world, modelName, position, Matrix::Rotation(Vector3::Up(), Math::PI + Math::ToRadian(angle)), std::make_unique<Sphere>(Vector3::Zero(), radius))
{
	m_name = modelName;
	m_frameSpeed = frameSpeed;
	m_maxframe = maxFrame;
	m_anmNo = anmNo;
	m_scale = scale;
	m_isLoop = isLoop;
	m_point = 0;
	isAnimate = false;

	drawFlag = false;
}

void SkinObject::frameReset()
{
	frame = 0;
}

void SkinObject::onUpdate()
{
	auto player = m_world->findActor("Player");
	if (player == nullptr)return;

	if (isAnimate)
	{
		if (frame <= m_maxframe * m_frameSpeed)
		{
			frame += m_frameSpeed;
		}
		else if (m_isLoop)
		{
			frame = fmodf(frame, m_maxframe);
		}
		else
		{
			player->sendMessage("StartControl",nullptr);
			m_world->actorSet(player->getName());
			isAnimate = false;
		}
	}

	Debug::Println("point:%f", m_point);

	BaseActor::onUpdate();
}

void SkinObject::onDraw(Renderer & render) const
{
	if (drawFlag)
	{
		auto worldPose = getWorldPose();
		Vector3 position = Matrix::Translation(worldPose);
		Matrix rotate = Matrix::Rotation(worldPose);
		render.setScale(m_name, Vector3(m_scale, m_scale, m_scale));
		render.drawSkinModel(m_name, position, rotate, m_anmNo, frame);
	}

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

	if (message == String::Create(m_name, "G"))
	{
		if (!(bool*)parameter)
		{
			drawFlag = true;
			GimmickManager::add(1);
			frameReset();
			isAnimate = true;
		}
		else
		{
			drawFlag = false;
			GimmickManager::sub(1);
			frameReset();
			isAnimate = true;
		}
	}
	BaseActor::onMessage(message, parameter);
}