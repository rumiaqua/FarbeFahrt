#pragma once
#include "Utility/Renderer.h"
# include "Utility/Pose.h"
# include "Utility/String.h"

#include "IWorld.h"
#include "Actor.h"

#include <string>
#include <algorithm>
#include <functional>
#include <forward_list>

class IShape;
using IShapePtr = std::shared_ptr<IShape>;

/// <summary>�A�N�^�[���N���X</summary>
class BaseActor
{
public:

	/// <summary>�R���X�g���N�^</summary>
	BaseActor(IWorld& world, const std::string& name, const Vector3& position, const Matrix& rotation, const IShapePtr& shape);

	explicit BaseActor(const std::string& name = "none");

	/// <summary>���z�f�X�g���N�^</summary>
	virtual ~BaseActor();

	/// <summary>�X�V</summary>
	void update();

	/// <summary>�`��</summary>
	void draw(Renderer& renderer) const;

	/// <summary>�Փ˔���</summary>
	void collide(BaseActor* folder);

	/// <summary>���S���Ă��邩��Ԃ�</summary>
	bool isDead()const;

	/// <summary>�E��</summary>
	void kill();

	/// <summary>���O���擾����</summary>
	const std::string& getName()const;

	/// <summary>�p����Ԃ�</summary>
	Matrix getPose() const;

	/// <summary>���[���h�p����Ԃ�</summary>
	Matrix getWorldPose() const;

	/// <summary>���W��Ԃ�</summary>
	Vector3& getPosition();

	/// <summary>���W��Ԃ�</summary>
	const Vector3& getPosition() const;

	/// <summary>��]��Ԃ�</summary>
	Matrix& getRotation();

	/// <summary>��]��Ԃ�</summary>
	const Matrix& getRotation() const;

	/// <summary>�q������</summary>
	Actor find(const std::string& name) const;

	/// <summary>�����Ɉ�v����q����������</summary>
	Actor findPred(const std::function<bool(const BaseActor&)>& func) const;

	/// <summary>�q������</summary>
	std::vector<Actor> finds(const std::string& name) const;

	/// <summary>�q�ɒǉ�</summary>
	void addChild(const Actor& child);

	/// <summary>�q�ɏ��������s����</summary>
	void eachChildren(const std::function<void(BaseActor&)>& func);

	/// <summary>�q�ɏ��������s����</summary>
	void eachChildren(const std::function<void(const BaseActor&)>& func)const;

	/// <summary>�����Ɉ�v����q���폜����</summary>
	void removeChildren(const std::function<bool(BaseActor&)>& func);

	/// <summary>�q��S�č폜����</summary>
	void removeChildren();

	/// <summary>���b�Z�[�W�𑗐M����</summary>
	void sendMessage(const std::string& message, void* parameter);

	/// <summary>�R�s�[�R���X�g���N�^���폜</summary>
	BaseActor(const BaseActor& other) = delete;

	/// <summary>������Z�q���폜</summary>
	BaseActor& operator = (const BaseActor& other) = delete;

	bool isCollide(const BaseActor* other) const;

	IShape* const getShape() const;

protected:

	/// <summary>�X�V</summary>
	virtual void onUpdate();

	/// <summary>�`��</summary>
	virtual void onDraw(Renderer& render)const;

	/// <summary>�Փˉ���</summary>
	virtual void onCollide(BaseActor* actor);
public:
	/// <summary>���b�Z�[�W����M</summary>
	virtual void onMessage(const std::string& message, void* parameter);

protected:

	/// <summary>���[���h</summary>
	IWorld* m_world;

	/// <summary>���O</summary>
	std::string m_name;

	/// <summary>�p��</summary>
	Pose m_pose;

	Pose m_previousPose;

	/// <summary>���S���Ă��邩</summary>
	bool m_dead;

	/// <summary>�e�A�N�^�[�|�C���^</summary>
	ActorRef m_parent;

	/// <summary>�q�A�N�^�[���X�g</summary>
	std::forward_list<Actor> m_children;

	/// <summary>�Փː}�`</summary>
	IShapePtr m_shape;
};
