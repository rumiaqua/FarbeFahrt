#include "Skydome.h"

Skydome::Skydome(IWorld& world, const String& name) :
BaseActor(world, name, Vector3::Zero(), Matrix::identity(), nullptr)
{

}
void Skydome::onUpdate()
{
	//カメラのポジションを取得
	getPosition() = m_world->findCamera()->getPosition();
}
void Skydome::onDraw(Renderer& render)const
{
	render.setScale(m_name.toNarrow(), VGet(100.0f, 100.0f, 100.0f));
	render.drawNormalModel(m_name.toNarrow(), getPosition(), getRotation());
}
