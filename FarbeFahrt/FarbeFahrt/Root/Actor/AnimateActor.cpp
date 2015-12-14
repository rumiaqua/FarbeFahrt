# include "AnimateActor.h"

# include "Utility/Loader.h"
# include "Utility/Renderer.h"
# include "Utility/Math.h"


AnimateActor::AnimationInfo::AnimationInfo()
	: animationNumber(-1)
	, animationTime(0.0f)
	, isReversed(false)
	, onStartedCallback()
	, onCompletedCallback()
{

}


AnimateActor::AnimateActor(
	IWorld& world,
	const std::string& name,
	const Vector3& position,
	float scale)
	: BaseActor(world, name, position, Matrix::identity(), nullptr)
	, m_scale(scale)
	, m_animationNumber(-1)
	, m_elapsedTime(0.0f)
	, m_animationTime(0.0f)
	, m_isAnimating(false)
	, m_isReversed(false)
{

}

void AnimateActor::onUpdate()
{
	// �J�n���R�[���o�b�N�����݂�
	if (m_onStartedCallback)
	{
		m_onStartedCallback(*this);
		// ������
		m_onStartedCallback = Callback();
	}

	// �A�j���[�V�������Ȃ�A�j���[�V�����������s�Ȃ�
	if (m_isAnimating)
	{
		m_elapsedTime += 1.0f;
		// ���݃t���[�����A�j���[�V�����t���[�������ł���΃A�j���[�V������
		m_isAnimating = m_elapsedTime < m_animationTime;
		// �N�����v
		m_elapsedTime = Math::Min({ m_elapsedTime, m_animationTime });
	}

	// �A�j���[�V�������łȂ���ΏI�����R�[���o�b�N�����݂�
	if (!m_isAnimating &&
		m_onCompletedCallback)
	{
		m_onCompletedCallback(*this);
		m_onCompletedCallback = Callback();
	}

	BaseActor::onUpdate();
}

void AnimateActor::onDraw(Renderer& renderer) const
{
	renderer.setScale(m_name, { m_scale, m_scale, m_scale });

	float t = Math::Min({ m_elapsedTime / m_animationTime, 0.99999f });

	// ���]�t���O�������Ă���Δ��]����
	if (m_isReversed)
	{
		t = 1.0f - t;
	}

	renderer.drawSkinModel(m_name, m_pose, m_animationNumber, t);

	BaseActor::onDraw(renderer);

}

void AnimateActor::onMessage(const std::string& message, void* parameter)
{
	if (message == "Animate")
	{
		AnimationInfo* info = (AnimationInfo*)parameter;
		m_animationNumber = info->animationNumber;
		m_elapsedTime = 0.0f;
		m_animationTime = info->animationTime;
		m_isAnimating = true;
		m_isReversed = info->isReversed;
		m_onStartedCallback = info->onStartedCallback;
		m_onCompletedCallback = info->onCompletedCallback;
	}

	return BaseActor::onMessage(message, parameter);
}
