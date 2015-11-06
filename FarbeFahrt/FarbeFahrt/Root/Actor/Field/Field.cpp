#include "Field.h"

Field::Field(IWorld& world)
	:BaseActor(world, "field", Vector3(0.0f, -90.0f, 0.0f), Matrix::identity(), nullptr)
{
}

void Field::onUpdate()
{
}
void Field::onDraw(Renderer& render)const
{
	render.setScale("field", VGet(0.5f, 0.5f, 0.5f));
	render.drawNormalModel("field", getPosition(), getRotation());
}

void Field::onCollide(BaseActor& actor)
{

}
