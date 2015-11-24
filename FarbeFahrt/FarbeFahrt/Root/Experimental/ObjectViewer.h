# pragma once

# include "Frame/BaseScene.h"

# include "Utility/FreeCamera.h"

# include <vector>

class ObjectViewer : public BaseScene
{
public:

	ObjectViewer();

	virtual void loadContents(Loader& loader)override;

	virtual void initialize()override;

	virtual void update()override;

	virtual void draw(Renderer& render)override;

	virtual void post() override;

	virtual void cleanUp() override;

	virtual bool isSwallow() const override;

private:

	

private:

	Loader* m_loader;

	std::vector<std::string> m_files;
};
