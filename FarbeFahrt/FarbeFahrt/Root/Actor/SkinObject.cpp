#include "SkinObject.h"
#include "Utility/Math.h"

#include "Utility/Input.h"
#include "Utility\SingletonFinalizer.h"
#include "Utility\HandleList.h"

namespace 
{
	float frame = 0.0f;
}

SkinObject::SkinObject(IWorld & world, const String& modelName, const Vector3 & position, int anmNo, float frameSpeed,float maxframe) :
	BaseActor(world, modelName, position, Matrix::Rotation(Vector3::Up(), Math::PI), nullptr)
{
	m_name = modelName;
	m_frameSpeed = frameSpeed;
	m_maxframe = maxframe;
	m_anmNo = anmNo;
}

void SkinObject::frameReset()
{
	frame = 0;
}

void SkinObject::onUpdate()
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
			frame = fmodf(frame, m_maxframe);
		}
	}

	BaseActor::onUpdate();
}

void SkinObject::onDraw(Renderer & render) const
{
	render.drawSkinModel(m_name.toNarrow(), getPosition(), getRotation(), m_anmNo, frame);

	BaseActor::onDraw(render);
}

void SkinObject::onMessage(const String & message, void* parameter)
{
	if (message == "Rotation")
		Matrix::Rotate(getRotation(), Vector3::Up(), *(const float*)parameter);
	BaseActor::onMessage(message, parameter);
}