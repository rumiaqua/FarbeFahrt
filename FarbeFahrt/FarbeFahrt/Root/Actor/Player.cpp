#include "Player.h"
#include "Utility/Input.h"
#include "Utility/SE.h"
#include "Utility/Math.h"

# include "Collision/Sphere.h"

# include "Utility/Debug.h"

Player::Player(IWorld& world, const VECTOR position) :
BaseActor(world, "Player", position, VGet(0, DX_PI_F, 0))
{
	moveSpeed = 1.5f;
	state = PlayerState::standing;
	moveFlag = false;
}
void Player::onUpdate()
{
	IShape* s = new Sphere(position, 10.0f);

	IShape* t = new Sphere({ 0, position.y, 0 }, 10.0f);

	Debug::print("s:(%f, %f, %f)\n", s->origin.x, s->origin.y, s->origin.z);
	Debug::print("t:(%f, %f, %f)\n", t->origin.x, t->origin.y, t->origin.z);

	if (s->intersects(t))
	{
		Debug::print("Hello C++ World\n");
	}

	delete s;
	delete t;

	playerInput();
}
void Player::playerInput()
{
	// �ړ���
	VECTOR moveVec = VGet(0.0f, 0.0f, 0.0f);
	// �J�������W
	const VECTOR cameraPos = world->findCamera()->getPosition();
	// �J������Y��]��
	const float cameraRotateY = world->findCamera()->getRotation().y;
	// �O���x�N�g��
	VECTOR frontVec = VSub(position, cameraPos);
	// �����x�N�g��
	VECTOR leftVec = VCross(frontVec, VGet(0.0f, 1.0f, 0.0f));

	// XZ���ʂɎˉe���Đ��K��
	leftVec.y = 0;
	leftVec = VNorm(leftVec);
	frontVec.y = 0;
	frontVec = VNorm(frontVec);

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
		moveVec = VAdd(moveVec, VScale(leftVec, moveSpeed));
	}
	/*if (Input::isPressed(KEY_INPUT_S))
	{
		moveVec = VAdd(moveVec, VScale(frontVec, -moveSpeed));
	}*/
	if (Input::isPressed(KEY_INPUT_D))
	{
		moveVec = VAdd(moveVec, VScale(leftVec, -moveSpeed));
	}

	// �ړ��ʂ�0�łȂ���Έړ������ƃ��f������
	if (VSquareSize(moveVec) != 0.0f)
	{
		// ���s�ړ�
		position = VAdd(position, moveVec);
		// �ړ��ʂɍ��킹�ă��f������]
		float angle = VRad(frontVec, moveVec) * Math::Sign(VCross(frontVec, moveVec).y);
		rotation.y = cameraRotateY - angle + DX_PI;

		state = PlayerState::walking;
	}
	else
	{
		state = PlayerState::standing;
	}
}
void Player::onDraw(Renderer& render)const
{
	//�����ŕ`����@�ς����܂���
	render.drawSkinModel("Player", position, rotation,(int)state,1.0f);
}