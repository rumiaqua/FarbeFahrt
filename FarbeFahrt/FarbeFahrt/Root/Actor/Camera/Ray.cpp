#include "Ray.h"
#include "Utility/Math.h"

#include "Utility/Debug.h"

Ray::Ray(IWorld & world, const Vector3 & begin, const Vector3& end)
	:BaseActor(world, "Ray", begin, Matrix::Rotation(Vector3::Up(), Math::PI), std::make_unique<Line>(Vector3::Zero(), end - begin))
{
}

void Ray::onUpdate()
{
	//生成後、まだ自動削除していません
	BaseActor::onUpdate();
}

void Ray::onMessage(const String & message, void* parameter)
{
	auto gimmick = static_cast<BaseActor*>(parameter);
	if (message == "onCollide")
	{
		gimmick->sendMessage("HitGimmick", nullptr);
	}

	BaseActor::onMessage(message, parameter);
}


