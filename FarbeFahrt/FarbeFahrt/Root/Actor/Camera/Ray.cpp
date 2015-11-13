#include "Ray.h"
#include "Utility/Math.h"

#include "Utility/Debug.h"

Ray::Ray(IWorld & world, const Vector3 & begin, const Vector3& end)
	:BaseActor(world, "Ray", begin, Matrix::Rotation(Vector3::Up(), Math::PI), std::make_unique<Line>(Vector3::Zero(), end - begin))
{
}

void Ray::onUpdate()
{
	//������A�܂������폜���Ă��܂���
	BaseActor::onUpdate();
}

void Ray::onCollide(BaseActor* actor)
{
	kill();
	actor->sendMessage("HitGimmick",nullptr);
	// actor->onMessage("HitGimmick", nullptr);
}


