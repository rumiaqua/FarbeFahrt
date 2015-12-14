#include "Gimmick.h"
#include "Utility/Math.h"
#include "Utility/Input.h"

#include "Utility/Debug.h"
#include "Utility/SingletonFinalizer.h"
#include "Utility/HandleList.h"

namespace
{
	float frame = 0.0f;
}

Gimmick::Gimmick(IWorld & world, const std::string& modelName, const Vector3 & position, int anmNo, float frameSpeed, float maxframe, float radius) :
	BaseActor(world, modelName, position, Matrix::Rotation(Vector3::Up(), Math::PI / 2), std::make_unique<Sphere>(Vector3::Zero(), radius))
{
	m_name = modelName;
	m_frameSpeed = frameSpeed;
	m_maxframe = maxframe;
	m_anmNo = anmNo;
	isAnimate = false;
	m_flag = false;
}

void Gimmick::frameReset()
{
	frame = 0;
}

//ê”îCé“Å@Ç»ÇËÇΩÇÒ
void Gimmick::animation()
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

void Gimmick::onUpdate()
{
	animation();

	BaseActor::onUpdate();
}

void Gimmick::onDraw(Renderer & render) const
{
	if (MV1GetAnimNum(Singleton<HandleList>::Instance().getHandle(m_name)) > 0)
	{
		render.drawSkinModel(m_name, getPosition(), getRotation(), m_anmNo, frame, false);
	}
	else
	{
		render.drawNormalModel(m_name, getPosition(), getRotation());
	}

	Debug::Println("gimmickFlag:%d",m_flag);

	BaseActor::onDraw(render);
}

void Gimmick::onMessage(const std::string& message, void* parameter)
{
	auto player = m_world->findActor("Player");
	auto gimmickObj = m_world->findActor(m_name.substr(0, m_name.length() - 1));
	auto camera = m_world->findCamera();
	if (gimmickObj == nullptr) return;
	if (player	   == nullptr) return;
	if (camera	   == nullptr) return;

	if (message == "OnGimmick")
	{
		m_world->actorSet(gimmickObj->getName());
		isAnimate = true;
		if (!m_flag)
		{
			gimmickObj->sendMessage(m_name, (bool*)m_flag);
			m_flag = true;
		}
		else
		{
			gimmickObj->sendMessage(m_name, (bool*)m_flag);
			m_flag = false;
		}
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

	if (message == "onCollide")
	{
		BaseActor* actor = static_cast<BaseActor*>(parameter);
		actor->sendMessage("HitObstacle", (void*)this);
	}

	BaseActor::onMessage(message, parameter);
}