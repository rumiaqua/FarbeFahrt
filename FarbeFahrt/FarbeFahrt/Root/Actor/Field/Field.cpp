#include "Field.h"

Field::Field(IWorld& world)
	:BaseActor(world, "field", Vector3(0.0f, -90.0f, 0.0f), Matrix::identity())
{
}

void Field::onUpdate()
{

}
void Field::onDraw(Renderer& render)const
{
	render.setScale("book", VGet(2.0f, 2.0f, 2.0f));
	render.drawNormalModel("book", getPosition(), getRotation());
}