#include "Stand.h"
#include "Utility/Math.h"

#include "Utility/Debug.h"

Stand::Stand(IWorld& world, const Vector3& position) :
	BaseActor(world, "Stand", position, Matrix::rotation(Vector3::forward(),Math::toRadian(45)))
	, capsule(position, position, 5.0f)
{
}
void Stand::onUpdate()
{
	
}
void Stand::onDraw(Renderer& render)const
{
	Debug::println(getPose().toString());
	Debug::println("");
	Debug::println(getWorldPose().toString());

	Matrix pose = getWorldPose();
	Vector3 pos = Matrix::translation(pose);
	Matrix rot = Matrix::rotation(pose);

	//‚±‚±‚Å•`‰æ•û–@•Ï‚¦‚ç‚ê‚Ü‚·‚æ
	render.drawNormalModel("Player", pos, rot);
}

void Stand::onMessage(const String & message, const void * parameter)
{
	if (message == "Rotation")
		Matrix::rotate(getRotation(), Vector3::up(), *(const float*)parameter);
}
