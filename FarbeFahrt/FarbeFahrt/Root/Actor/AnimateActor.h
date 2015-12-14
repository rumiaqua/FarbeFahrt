# pragma once

# include "Actor/BaseActor.h"
# include "Utility/Def.h"

class AnimateActor : public BaseActor
{
public:

	using Callback = std::function<void(BaseActor& actor)>;

	struct AnimationInfo
	{
		AnimationInfo();
		int animationNumber;
		float animationTime;
		bool isReversed;
		Callback onStartedCallback;
		Callback onCompletedCallback;
	};

public:

	AnimateActor(
		IWorld& world,
		const std::string& name,
		const Vector3& position,
		float scale);
public:

	virtual void onUpdate() override;
	virtual void onDraw(Renderer& renderer) const override;
	virtual void onMessage(const std::string& message, void* parameter) override;

private:

	float m_scale;
	int m_animationNumber;
	float m_elapsedTime;
	float m_animationTime;
	bool m_isAnimating;
	bool m_isReversed;
	Callback m_onStartedCallback;
	Callback m_onCompletedCallback;
};
