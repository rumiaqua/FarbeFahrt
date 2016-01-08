#pragma once
#include "Actor/BaseActor.h"
#include "Collision/Capsule.h"
#include "Utility/String.h"

class CommandGimmick :
	public BaseActor
{
public:
	CommandGimmick(IWorld& world, const std::string& modelName, const Vector3& position, int anmNo, float frameSpeed, float maxframe, float radius,int commandNo);
	void frameReset();
private:
	virtual void onUpdate()override;
	virtual void onDraw(Renderer& render)const override;
	virtual void onMessage(const std::string& message, void* parameter)override;
private:
	//�ӔC�ҁ@�Ȃ肽��
	void animation();//�N���b�N���ꂽ��A�j���[�V����
private:
	float m_frameSpeed;
	float m_maxframe;
	int m_anmNo;
	bool isAnimate;
	bool m_flag;
	int m_commandNo;
};
