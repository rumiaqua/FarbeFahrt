#include "Player.h"
#include "Utility/Input.h"
#include "Utility/SE.h"
#include "Utility/Math.h"

# include "Collision/Sphere.h"

# include "Utility/Debug.h"

# include "Utility/Mouse.h"

# include "Utility/Vector3.h"
# include "Utility/MemoryCast.h"

Player::Player(IWorld& world, const Vector3& position) :
BaseActor(world, "Player", position, Vector3(0.0f, DX_PI_F, 0.0f))
, capsule(position, position, 5.0f)
{
	moveSpeed = 1.5f;
	state = PlayerState::standing;
	moveFlag = false;
}
void Player::onUpdate()
{
	/*IShape* s = new Sphere(position, 10.0f);

	IShape* t = new Sphere({ 0, position.y, 0 }, 10.0f);

	Debug::print("s:(%f, %f, %f)\n", s->origin.x, s->origin.y, s->origin.z);
	Debug::print("t:(%f, %f, %f)\n", t->origin.x, t->origin.y, t->origin.z);

	if (s->intersects(t))
	{
		Debug::print("Hello C++ World\n");
	}

	delete s;
	delete t;*/

	playerInput();
}
void Player::playerInput()
{
	// �ړ���
	// VECTOR moveVec = VGet(0.0f, 0.0f, 0.0f);
	Vector3 moveVec;
	// �J�������W
	const VECTOR cameraPos = world->findCamera()->getPosition();
	// �J������Y��]��
	const float cameraRotateY = world->findCamera()->getRotation().y;
	// �O���x�N�g��
	// VECTOR frontVec = VSub(position, cameraPos);
	Vector3 frontVec = memory_cast<Vector3>(VSub(position, cameraPos));
	// �����x�N�g��
	// VECTOR leftVec = VCross(frontVec, VGet(0.0f, 1.0f, 0.0f));
	Vector3 leftVec = Vector3::cross(frontVec, Vector3::up());

	// XZ���ʂɎˉe���Đ��K��
	leftVec.y = 0;
	// leftVec = VNorm(leftVec);
	leftVec.normalize();
	frontVec.y = 0;
	// frontVec = VNorm(frontVec);
	frontVec.normalize();

	if (Input::isClicked(KEY_INPUT_SPACE))
	{
		SE::playSE("bang");
	}

	// �ړ�����
	/*if (Input::isPressed(KEY_INPUT_W))
	{
		moveVec = VAdd(moveVec, VScale(frontVec, moveSpeed));
	}*/
	if (Input::isPressed(KEY_INPUT_A))
	{
		// moveVec = VAdd(moveVec, VScale(leftVec, moveSpeed));
		moveVec += leftVec * moveSpeed;
	}
	/*if (Input::isPressed(KEY_INPUT_S))
	{
		moveVec = VAdd(moveVec, VScale(frontVec, -moveSpeed));
	}*/
	if (Input::isPressed(KEY_INPUT_D))
	{
		// moveVec = VAdd(moveVec, VScale(leftVec, -moveSpeed));
		moveVec -= leftVec * moveSpeed;
	}

	// �ړ��ʂ�0�łȂ���Έړ������ƃ��f������
	// if (VSquareSize(moveVec) != 0.0f)
	if (moveVec.lengthSquared() != 0.0f)
	{
		// ���s�ړ�
		// position = VAdd(position, moveVec);
		position = memory_cast<Vector3>(position) + moveVec;
		// �ړ��ʂɍ��킹�ă��f������]
		float angle = Vector3::angle(frontVec, moveVec) * (float)Math::sign(Vector3::cross(frontVec, moveVec).y);
		// float angle = VRad(frontVec, moveVec) * Math::Sign(VCross(frontVec, moveVec).y);
		rotation.y = cameraRotateY - angle + DX_PI_F;

		state = PlayerState::walking;
	}
	else
	{
		state = PlayerState::standing;
	}

	if (Mouse::isClicked(MOUSE_INPUT_MIDDLE))
	{
		Vector3 nearClip = Mouse::screenPointToWorld(0.0f);
		Vector3 farClip = Mouse::screenPointToWorld(1.0f);
		struct Ray
		{
			Vector3 origin;
			Vector3 direction;
		} ray;
		ray.origin = position;
		ray.direction = //VNorm(VSub(farClip, nearClip));
			Vector3::normalize(farClip - nearClip);

		capsule.origin = ray.origin;
		capsule.end = // VAdd(ray.origin, VScale(ray.direction, 100.0f));
			ray.origin + ray.direction * 100.0f;
	}
}
void Player::onDraw(Renderer& render)const
{
	//�����ŕ`����@�ς����܂���
	render.drawSkinModel("Player", position, rotation,(int)state,1.0f);
	capsule.draw();
}