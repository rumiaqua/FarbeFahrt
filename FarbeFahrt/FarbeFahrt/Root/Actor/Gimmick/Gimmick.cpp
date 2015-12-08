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
	BaseActor(world, modelName, position, Matrix::Rotation(Vector3::Up(), Math::PI), std::make_unique<Sphere>(Vector3::Zero(), radius))
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
	render.drawSkinModel(m_name, getPosition(), getRotation(), m_anmNo, frame);

	BaseActor::onDraw(render);
}

void Gimmick::onMessage(const std::string& message, void* parameter)
{
	bool flag = false;
	auto gimmickObj = m_world->findActor(m_name.substr(0, m_name.length() - 1));
	auto camera = m_world->findCamera();
	if (gimmickObj == nullptr || camera == nullptr) return;

	if (!flag && message == "OnGimmick")
	{
		m_world->actorSet(gimmickObj->getName());
		gimmickObj->sendMessage(m_name, (bool*)flag);
		isAnimate = true;
		flag = true;
	}
	else if (flag && message == "OffGimmick")
	{
		m_world->actorSet(gimmickObj->getName());
		gimmickObj->sendMessage(m_name, (bool*)flag);
		isAnimate = true;
		flag = false;
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