#include "Enemy.h"

Enemy::Enemy(IWorld& world, const Vector3& position, const String& name) :
BaseActor(world, name, position, Matrix::identity(), nullptr)
{

}
void Enemy::onUpdate()
{

}
void Enemy::onDraw(Renderer& render)const
{
	render.drawNormalModel(m_name.toNarrow(), getPosition(), getRotation());
}
