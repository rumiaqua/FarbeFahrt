# pragma once
# include "Frame/BaseScene.h"

# include "World.h"

class Opening : public BaseScene
{
public:
	Opening(Renderer* renderer);
	virtual void loadContents(Loader& loader)override;
	virtual void initialize()override;
	virtual void update()override;
	virtual void draw(Renderer& renderer)override;
	virtual void post() override;
	virtual void cleanUp() override;
	virtual bool isSwallow() const override;
private:
	std::shared_ptr<World> m_world;
	bool m_isOnce;
	Renderer* m_renderer;
};
