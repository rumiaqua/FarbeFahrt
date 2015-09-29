#include "Skydome.h"

Skydome::Skydome(IWorld& world) :
BaseActor(world, "Skydome", VGet(0, 0, 0), VGet(0, 0, 0))
{

}
void Skydome::onUpdate()
{
	//カメラのポジションを取得
	position = world->findCamera()->getPosition();
}
void Skydome::onDraw(Renderer& render)const
{
	render.setScale("sky", VGet(100.0f, 100.0f, 100.0f));
	render.drawNormalModel("sky", position, rotation);
}