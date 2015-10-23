#include "Skydome.h"

Skydome::Skydome(IWorld& world) :
BaseActor(world, "Skydome", Vector3::zero(), Matrix::identity())
{

}
void Skydome::onUpdate()
{
	//カメラのポジションを取得
	getPosition() = world->findCamera()->getPosition();
}
void Skydome::onDraw(Renderer& render)const
{
	render.setScale("sky", VGet(100.0f, 100.0f, 100.0f));
	render.drawNormalModel("sky", getPosition(), getRotation());
}