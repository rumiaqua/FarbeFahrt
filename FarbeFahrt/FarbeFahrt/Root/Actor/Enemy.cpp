#include "Enemy.h"

Enemy::Enemy(IWorld& world) :
BaseActor(world, "Skydome", Vector3::zero(), Matrix::identity())
{

}
void Enemy::onUpdate()
{

}
void Enemy::onDraw(Renderer& render)const
{

}