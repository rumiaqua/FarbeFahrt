# pragma once

# include "Actor/ActorManager/ActorManager.h"
# include "StageData.h"

class World;

class Stage
{
public:

	Stage(World* world);

public:

	/// <summary>�X�e�[�W�f�[�^����\������</summary>
	/// <param name="data">�\���f�[�^</param>
	/// <param name="isClear">�A�N�^�[���X�g���N���A���邩�ǂ���</param>
	void apply(const StageData& data, bool isClear = true);

	/// <summary>�X�V</summary>
	void update();

	/// <summary>�`��</summary>
	void draw(Renderer& renderer) const;

	/// <summary>�A�N�^�[�̒ǉ�</summary>
	/// <param name="tag">�A�N�^�[�^�O</param>
	/// <param name="actor">�A�N�^�[</param>
	void addActor(const ActorTag& tag, const Actor& actor);

	/// <summary>�A�N�^�[�̌���</summary>
	/// <param name="name">���O</param>
	Actor findActor(const std::string& name) const;

	/// <summary>�t�B�[���h�̌���</summary>
	Actor findField() const;

	/// <summary>�A�N�^�[�̃N���A</summary>
	void clearActor();

private:

	World* m_world;

	Actor m_field;

	ActorManager m_actorManager;
};
