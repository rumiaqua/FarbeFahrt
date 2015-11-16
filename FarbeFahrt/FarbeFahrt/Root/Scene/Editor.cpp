# include "Editor.h"

# include "Utility/Debug.h"
# include "Utility/Matrix.h"
# include "Utility/MemoryCast.h"
# include "Utility/Input.h"
# include "Utility/Math.h"
# include "Utility/Def.h"

# include "ISceneMediator.h"

Editor::Editor()
	: m_camera()
	, m_isWorldMode(false)
	, m_isAccel(false)
{

}

void Editor::loadContents(Loader& loader)
{
	NoUse(loader);
}

void Editor::initialize()
{
	Debug::SetClear(true);

	Matrix view = memory_cast<Matrix>(GetCameraViewMatrix());
	view.inverse();
	Vector3 position = Matrix::Translation(view);
	Vector3 forward = Vector3(Matrix::Forward(view));
	m_camera.setPosition(position);
	m_camera.setDirection(forward);
}

void Editor::update()
{
	// 各方向ベクトルの定義
	Vector3 right = m_camera.right();
	Vector3 up = m_camera.up();
	Vector3 forward = m_camera.forward();

	// モード処理
	mode();

	// 基準処理
	if (m_isWorldMode)
	{
		right = Vector3::Right();
		up = Vector3::Up();
		forward = Vector3::Forward();
	}

	// 加速処理
	const float ACCEL = m_isAccel ? 3.0f : 1.0f;

	// 移動処理
	const float SPEED = 1.0f * ACCEL;
	move(SPEED, right, up, forward);

	// 回転処理
	const double ANGLE = Math::ToRadian(0.5) * ACCEL;
	rotate(ANGLE, right, up, forward);

	// シーン遷移処理
	scene();
}

void Editor::draw(Renderer& render)
{
	NoUse(render);

	Debug::Println("Editor Mode.");
	Debug::Println("Translate");
	Debug::Println("A:Left D:Right E:Up X:Down W:Forward S:Backward");
	Debug::Println("Rotate");
	Debug::Println("←→:XAxis ↑↓:YAxis");
	Debug::Println(String::Create("Toggle Pivot Mode"));
	Debug::Println(String::Create("Space:", m_isWorldMode ? "Local" : "World", " Mode"));
	Debug::Println(String::Create("Toggle Speed Mode"));
	Debug::Println(String::Create("LShift:", m_isAccel ? "Low" : "High", " Speed Mode"));
	Debug::Println("Scene");
	Debug::Println("Return:Pop current Scene.");

	m_camera.apply();
}

void Editor::cleanUp()
{

}

bool Editor::isSwallow() const
{
	return true;
}

void Editor::mode()
{
	if (Input::IsClicked(KEY_INPUT_SPACE))
	{
		m_isWorldMode = !m_isWorldMode;
	}

	if (Input::IsClicked(KEY_INPUT_LSHIFT))
	{
		m_isAccel = !m_isAccel;
	}
}

void Editor::move(float speed, const Vector3& right, const Vector3& up, const Vector3& forward)
{
	if (Input::IsPressed(KEY_INPUT_A))
	{
		m_camera.move(-right * speed);
	}
	if (Input::IsPressed(KEY_INPUT_D))
	{
		m_camera.move(right * speed);
	}
	if (Input::IsPressed(KEY_INPUT_E))
	{
		m_camera.move(up * speed);
	}
	if (Input::IsPressed(KEY_INPUT_X))
	{
		m_camera.move(-up * speed);
	}
	if (Input::IsPressed(KEY_INPUT_W))
	{
		m_camera.move(forward * speed);
	}
	if (Input::IsPressed(KEY_INPUT_S))
	{
		m_camera.move(-forward * speed);
	}
}

void Editor::rotate(double angle, const Vector3& X, const Vector3& Y, const Vector3& Z)
{
	NoUse(Z);

	if (Input::IsPressed(KEY_INPUT_UP))
	{
		m_camera.rotate(X, angle);
	}
	if (Input::IsPressed(KEY_INPUT_DOWN))
	{
		m_camera.rotate(X, -angle);
	}
	if (Input::IsPressed(KEY_INPUT_LEFT))
	{
		m_camera.rotate(Y, angle);
	}
	if (Input::IsPressed(KEY_INPUT_RIGHT))
	{
		m_camera.rotate(Y, -angle);
	}
}

void Editor::scene()
{
	if (Input::IsClicked(KEY_INPUT_RETURN))
	{
		m_manager->popScene();
	}
}
