#include "Stand.h"
#include "Utility/Math.h"

#include "Utility/Debug.h"

Stand::Stand(IWorld& world, const Vector3& position) :
	BaseActor(world, "Stand", position, Matrix::Rotation(Vector3::Forward(), (float)Math::ToRadian(45.0)))
	, capsule(position, position, 5.0f)
{
}
void Stand::onUpdate()
{
	
}
void Stand::onDraw(Renderer& render)const
{
	Debug::Println(getPose().toString());
	Debug::Println("");
	Debug::Println(getWorldPose().toString());

	Matrix pose = getWorldPose();
	Vector3 pos = Matrix::Translation(pose);
	Matrix rot = Matrix::Rotation(pose);

	//‚±‚±‚Å•`‰æ•û–@•Ï‚¦‚ç‚ê‚Ü‚·‚æ
	render.drawNormalModel("Player", pos, rot);
}

void Stand::onMessage(const String & message, const void * parameter)
{
	if (message == "Rotation")
		Matrix::Rotate(getRotation(), Vector3::Up(), *(const float*)parameter);
}
