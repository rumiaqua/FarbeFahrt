#include "Skydome.h"

Skydome::Skydome(IWorld& world, const std::string& name) :
BaseActor(world, name, Vector3::Zero(), Matrix::identity(), nullptr)
{

}
void Skydome::onUpdate()
{
	//カメラのポジションを取得
	getPosition() = m_world->findCamera()->getPosition();
	BaseActor::onUpdate();
}
void Skydome::onDraw(Renderer& render)const
{
	render.setScale(m_name, VGet(100.0f, 100.0f, 100.0f));
	render.drawNormalModel(m_name, getPosition(), getRotation());
	BaseActor::onDraw(render);
}
