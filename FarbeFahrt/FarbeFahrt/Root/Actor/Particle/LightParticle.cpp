#include "LightParticle.h"
#include "Utility/HandleList.h"
#include "Utility/SingletonFinalizer.h"
#include "Utility/RandomDevice.hpp"
#include "Utility/Point2.h"

#include "Utility/Debug.h"

namespace
{
	const float Death = 5.0f;	//パーティクルの描画時間
	const int AlphaSpeed = 5;	//パーティクルの透過速度
	const float Rise = 0.3f;	//パーティクルのy軸方向の上昇値
	const float Size = 5.0f;	//パーティクルのサイズ
}

LightParticle::LightParticle(IWorld & world, const Vector3 & position)
	: BaseActor(
		world,
		"LightParticle",
		position,
		Matrix::zero(),
		std::make_unique<Sphere>(Vector3::Zero(), 15.0f))
	, m_alpha(0)
	, m_angle(0.0f)
	, m_timer(0.0f)
{
	m_rand = RandomDevice::Range(1, 3);
}

void LightParticle::onUpdate()
{
	m_timer++;
	//m_angle += Math::ToRadian(m_rand);
	m_angle += Math::ToRadian(1);
	getPosition().y += Rise;

	if (m_timer <= Death * 60 / 2)
	{
		m_alpha <= 255 ? m_alpha += AlphaSpeed : m_alpha = 255;
	}
	else
	{
		m_alpha >= 0 ? m_alpha -= AlphaSpeed : m_alpha = 0;
	}
	
	//m_alpha = Math::Max({ m_alpha - AlphaDown, 0 });

	if (m_timer >= Death * 60)
	{
		kill();
	}
}

void LightParticle::onDraw(Renderer & renderer) const
{
	renderer.draw3DTexture(m_name, getPosition(), 0.5f, 0.5f, Size, m_angle, m_alpha);

	BaseActor::onDraw(renderer);
}

void LightParticle::onMessage(const std::string & message, void * parameter)
{

	BaseActor::onMessage(message, parameter);
}
