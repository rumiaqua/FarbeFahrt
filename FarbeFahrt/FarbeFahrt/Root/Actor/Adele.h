#pragma once
# include "Actor\BaseActor.h"
# include "Utility\Renderer.h"

# include "Scene\SceneManager.h"

class Adele : public BaseActor
{
public:

	Adele(IWorld& world, const std::string& name, const Vector3& position,ISceneMediator* manager);

private:

	virtual void onUpdate() override;
	virtual void onDraw(Renderer& renderer) const override;

public:
	virtual void onMessage(const std::string& message, void* parameter);
private:
	bool m_isCollide;
	Renderer m_renderer;
	ISceneMediator* m_manager;
};

