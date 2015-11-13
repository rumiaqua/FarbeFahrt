#include "Field.h"

# include "Collision/ModelCollider.h"

# include "Utility/Math.h"
# include "Utility/SingletonFinalizer.h"
# include "Utility/HandleList.h"

# include "Utility/Debug.h"

Field::Field(IWorld& world, const String& name, float scale)
	:BaseActor(world, name, Vector3(0.0f, -90.0f, 0.0f), Matrix::Rotation(Vector3::Up(), Math::PI),
		std::make_unique<ModelCollider>(name)), m_scale(scale)
{
}

void Field::onUpdate()
{
	BaseActor::onUpdate();
}
void Field::onDraw(Renderer& render) const
{
	render.setScale(m_name.toNarrow(), VGet(m_scale, m_scale, m_scale));
	render.drawNormalModel(m_name.toNarrow(), getPosition(), getRotation());

	BaseActor::onDraw(render);
}

void Field::onMessage(const String& message, void* parameter)
{
	if (message == "onCollide")
	{
		BaseActor* actor = static_cast<BaseActor*>(parameter);
		if (isCollide(actor))
		{
			// actor->onMessage("HitGround", (void*)this);
			const Vector3& pos = actor->getPosition();
			Debug::Println(pos.ToString());
			String& name = static_cast<ModelCollider*>(m_shape.get())->name;
			int handle = Singleton<HandleList>::Instance().getHandle(name);

			Vector3 start = pos + Vector3::Up() * 50.0f;
			Vector3 end = pos + Vector3::Down() * 1.0f;

			MV1SetupCollInfo(handle, -1);
			MV1_COLL_RESULT_POLY dim = MV1CollCheck_Line(handle, -1, start, end);
			if (dim.HitFlag == TRUE)
			{
				HITRESULT_LINE result = HitCheck_Line_Triangle(
					start, end, dim.Position[0], dim.Position[1], dim.Position[2]);

				Vector3 fixPos = result.Position;

				actor->sendMessage("HitGround", (void*)&fixPos);
			}
			MV1TerminateCollInfo(handle, -1);
		}
	}

	BaseActor::onMessage(message, parameter);
}
