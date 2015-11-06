#include "Ray.h"
#include "Utility/Math.h"

Ray::Ray(IWorld & world, const Vector3 & begin, const Vector3& end)
	:BaseActor(world, "Ray", begin, Matrix::Rotation(Vector3::Up(), Math::PI), std::make_unique<Line>(begin, end))
{
}
