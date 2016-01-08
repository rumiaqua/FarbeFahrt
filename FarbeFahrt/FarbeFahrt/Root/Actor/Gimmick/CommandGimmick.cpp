#include "CommandGimmick.h"
#include "Utility/Math.h"
#include "Utility/Input.h"

#include "Utility/Debug.h"
#include "Utility/SingletonFinalizer.h"
#include "Utility/HandleList.h"
#include "Actor/Gimmick/GimmickManager.h"

namespace
{
	float frame = 0.0f;
}

CommandGimmick::CommandGimmick(IWorld & world, const std::string& modelName, const Vector3 & position, int anmNo, float frameSpeed, float maxframe, float radius,int commandNo) :
	BaseActor(world, modelName, position, Matrix::Rotation(Vector3::Up(), Math::PI / 2), std::make_unique<Sphere>(Vector3::Zero(), radius))
{
	m_name = modelName;
	m_frameSpeed = frameSpeed;
	m_maxframe = maxframe;
	m_anmNo = anmNo;
	m_commandNo = commandNo;
	isAnimate = false;
	m_flag = false;
}

void CommandGimmick::frameReset()
{
	frame = 0;
}

//ê”îCé“Å@Ç»ÇËÇΩÇÒ
void CommandGimmick::animation()
{
	m_maxframe = (float)MV1GetFrameNum(Singleton<HandleList>::Instance().getHandle(m_name));
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

void CommandGimmick::onUpdate()
{
	animation();

	BaseActor::onUpdate();
}

void CommandGimmick::onDraw(Renderer & render) const
{
	if (MV1GetAnimNum(Singleton<HandleList>::Instance().getHandle(m_name)) > 0)
	{
		render.drawSkinModel(m_name, getPosition(), getRotation(), m_anmNo, frame, false);
	}
	else
	{
		render.drawNormalModel(m_name, getPosition(), getRotation());
	}

	Debug::Println("gimmickFlag:%d", m_flag);

	BaseActor::onDraw(render);
}

void CommandGimmick::onMessage(const std::string& message, void* parameter)
{
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

	if (message == "OnGimmick")
	{
		if (!m_flag)
		{
			m_world->findGroup(ActorTag::Field)->sendMessage("WorkGimmick", (int*)m_commandNo);
			GimmickManager::add(1);
			m_flag = true;
		}
	}

	BaseActor::onMessage(message, parameter);
}