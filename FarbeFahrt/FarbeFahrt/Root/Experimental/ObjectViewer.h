# pragma once

# include "Frame/BaseScene.h"

# include "Actor/SkinObject.h"

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

	void dragAndDrop();

	void animUpdate();

	void drawModel(Renderer& renderer);

	void cameraUpdate();

private:

	void move(float speed, const Vector3& right, const Vector3& up, const Vector3& forward);

	void rotate(double angle, const Vector3& X, const Vector3& Y, const Vector3& Z);

private:

	// ローダー
	Loader* m_loader;

	// モデル
	int m_currentModelNum;
	std::vector<std::string> m_models;
	std::vector<std::string> m_files;
	Pose m_pose;
	int m_animNumber;
	float m_progress;
	int m_handle;
	int m_maxAnimNum;

	// カメラ
	FreeCamera m_camera;
};
