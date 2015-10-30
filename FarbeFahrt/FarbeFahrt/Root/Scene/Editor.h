# pragma once

# include "Frame/BaseScene.h"

# include "Utility/FreeCamera.h"

class Editor : public BaseScene
{
public:

	Editor();
	
	void loadContents(Loader& loader)override;
	
	void initialize()override;
	
	void update()override;
	
	void draw(Renderer& render)override;
	
	void cleanUp() override;

	bool isSwallow() const override;

private:

	void mode();

	void move(float speed, const Vector3& right, const Vector3& up, const Vector3& forward);

	void rotate(double angle, const Vector3& X, const Vector3& Y, const Vector3& Z);

	void scene();

private:

	FreeCamera m_camera;

	bool m_isWorldMode;

	bool m_isAccel;
};
