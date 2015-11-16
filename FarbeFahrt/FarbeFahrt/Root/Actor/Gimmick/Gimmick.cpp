#include "Gimmick.h"
#include "Utility/Math.h"
#include "Utility/Input.h"

#include "Utility/Debug.h"
#include "Utility/SingletonFinalizer.h"
#include "Utility\HandleList.h"

namespace
{
	float frame = 0.0f;
}

Gimmick::Gimmick(IWorld & world, const String& modelName, const Vector3 & position, int anmNo, float frameSpeed, float maxframe) :
	BaseActor(world, modelName, position, Matrix::Rotation(Vector3::Up(), Math::PI), std::make_unique<Sphere>(Vector3::Zero(), 5.0f))
{
	m_name = modelName;
	m_frameSpeed = frameSpeed;
	m_maxframe = maxframe;
	m_anmNo = anmNo;
	isAnimate = false;
}

void Gimmick::frameReset()
{
	frame = 0;
}

//ê”îCé“Å@Ç»ÇËÇΩÇÒ
void Gimmick::animation()
{
	m_maxframe = MV1GetFrameNum(Singleton<HandleList>::Instance().getHandle(m_name));
	if (isAnimate)
	{
		if (frame <= m_maxframe * m_frameSpeed)
		{
			frame += m_frameSpeed;
		}
		else
		{
			isAnimate = false;
		}
	}
}

void Gimmick::onUpdate()
{
	animation();
	
	BaseActor::onUpdate();
}

void Gimmick::onDraw(Renderer & render) const
{
	render.drawSkinModel(m_name.toNarrow(), getPosition(), getRotation(), m_anmNo, frame);

	BaseActor::onDraw(render);
}

void Gimmick::onMessage(const String & message, void* parameter)
{
	if (message == "HitGimmick")
	{
		StoryManager::set(BitFlag::GIMMICK);
		
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