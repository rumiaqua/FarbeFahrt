#include "Field.h"
Field::Field(IWorld& world, const String& name)
	:BaseActor(world, name, Vector3(0.0f, -90.0f, 0.0f), Matrix::identity(), nullptr)
{
}

void Field::onUpdate()
{
}
void Field::onDraw(Renderer& render)const
{
	render.setScale(m_name.toNarrow(), VGet(0.5f, 0.5f, 0.5f));
	render.drawNormalModel(m_name.toNarrow(), getPosition(), getRotation());
}

void Field::onCollide(BaseActor& actor)
{

}