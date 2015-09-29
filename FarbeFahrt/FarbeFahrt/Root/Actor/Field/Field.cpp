#include "Field.h"

Field::Field(IWorld& world)
	:BaseActor(world, "field", VGet(0.0f, -90.0f, 0.0f), VGet(0.0f, 0.0f, 0.0f))
{
	}

void Field::onUpdate()
{
}
void Field::onDraw(Renderer& render)const
{
	render.setScale("field", VGet(0.5f, 0.5f, 0.5f));
	render.drawNormalModel("field", position, rotation);
}