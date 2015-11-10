# include "ModelCollider.h"

# include "Collision.h"

# include "Utility/SingletonFinalizer.h"

# include "Experimental/HandleManager.h"

# include <DxLib.h>

ModelCollider::ModelCollider(const String& name)
	: name(name)
{

}

bool ModelCollider::intersects(const IShape& shape) const
{
	return shape.intersects(*this);
}

bool ModelCollider::intersects(const Sphere& shape) const
{
	return Collision::intersects(*this, shape);
}

bool ModelCollider::intersects(const Capsule& shape) const
{
	return Collision::intersects(*this, shape);
}

bool ModelCollider::intersects(const Line& shape) const
{
	return Collision::intersects(*this, shape);
}

bool ModelCollider::intersects(const Triangle& shape) const
{
	return Collision::intersects(*this, shape);
}

bool ModelCollider::intersects(const ModelCollider& shape) const
{
	// ���f���ƃ��f���̏Փ˔���͂��Ȃ���������
	return false;
}

void ModelCollider::draw() const
{
	MV1DrawModelDebug(Singleton<HandleManager>::Instance().At(name),
		-1, FALSE, 0.0f, TRUE, TRUE);
}
