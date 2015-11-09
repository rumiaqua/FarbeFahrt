#include "Field.h"

# include "Collision/ModelCollider.h"

# include "Utility/Math.h"

Field::Field(IWorld& world, const String& name, float scale)
	:BaseActor(world, name, Vector3(0.0f, -90.0f, 0.0f), Matrix::Rotation(Vector3::Up(), Math::PI), 
		std::make_unique<ModelCollider>(name)), m_scale(scale)
{
}

void Field::onUpdate()
{
}
void Field::onDraw(Renderer& render)const
{
	render.setScale(m_name.toNarrow(), VGet(m_scale, m_scale, m_scale));
	render.drawNormalModel(m_name.toNarrow(), getPosition(), getRotation());
}

void Field::onCollide(BaseActor& actor)
{

}
