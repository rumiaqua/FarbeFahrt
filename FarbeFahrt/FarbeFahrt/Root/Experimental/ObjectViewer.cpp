# include "ObjectViewer.h"

# include "Utility/Debug.h"
# include "Utility/Matrix.h"
# include "Utility/Def.h"
# include "Utility/Loader.h"
# include "Utility/Math.h"
# include "Utility/Input.h"
# include "Utility/HandleList.h"
# include "Utility/SingletonFinalizer.h"

# include "Scene/ISceneMediator.h"

ObjectViewer::ObjectViewer()
	: m_loader(NULL)
	, m_currentModelNum(0)
	, m_models()
	, m_files()
	 ,m_pose()
	, m_animNumber(0)
	, m_progress(0.0f)
	, m_handle(-1)
	, m_maxAnimNum(0)
{

}

void ObjectViewer::loadContents(Loader& loader)
{
	m_loader = &loader;
}

void ObjectViewer::initialize()
{
	Debug::SetClear(true);

	/*Matrix view = Matrix::LookAt({ 0.0f, 100.0f, -100.0f }, Vector3::Zero(), Vector3::Up());
	SetCameraViewMatrix(view);
	SetupCamera_ProjectionMatrix(Matrix::Perspective(45.0, 1.33334f, 0.1f, 1000.0f));

	view.inverse();

	m_camera.setPosition(Matrix::Translation(view));
	m_camera.setDirection(Vector3(Matrix::Forward(view)));*/

	SetDragFileValidFlag(TRUE);
}

void ObjectViewer::update()
{
	// ドラッグアンドドロップ受付
	dragAndDrop();

	// アニメーション操作
	animUpdate();

	// カメラ処理
	cameraUpdate();
}

void ObjectViewer::draw(Renderer& render)
{
	Debug::Println(String::Create("CurrentModelNum : ", m_currentModelNum));
	Debug::Println(String::Create("AnimNumber : ", m_animNumber));
	Debug::Println(String::Create("Progress : ", m_progress));

	// カメラ適用
	// m_camera.apply();

	// モデル描画
	drawModel(render);
}

void ObjectViewer::post()
{
	for (auto&& file : m_files)
	{
		auto&& split = String::Split(file, '\\');
		std::string directory;
		for (auto it = split.rbegin(); it != split.rend(); ++it)
		{
			if (*it == "Resources")
			{
				break;
			}

			directory = *it + (directory == "" ? "" : "/") + directory;
		}

		m_models.emplace_back(file);

		m_loader->loadContent(file, directory);
		m_loader->load();

		m_animNumber = 0;
		m_progress = 0.0f;
		m_maxAnimNum = -1;
	}
	m_files.clear();
}

void ObjectViewer::cleanUp()
{
	SetDragFileValidFlag(FALSE);
}

bool ObjectViewer::isSwallow() const
{
	return true;
}

void ObjectViewer::dragAndDrop()
{
	// ドラッグアンドドロップ
	int num = GetDragFileNum();
	if (num != 0)
	{
		char buffer[256];
		for (int i = 0; i < num; ++i)
		{
			if (GetDragFilePath(buffer))
			{
				continue;
			}
			m_files.push_back(buffer);
		}
	}
}

void ObjectViewer::animUpdate()
{
	if (m_models.empty())
	{
		return;
	}

	if (m_maxAnimNum == -1)
	{
		auto& name = m_models.at(m_currentModelNum);
		m_handle = Singleton<HandleList>::Instance().getHandle(name);
		m_maxAnimNum = MV1GetAnimNum(m_handle);
	}

	// タイマー進める
	if (Input::IsPressed(KEY_INPUT_1))
	{
		m_progress += 0.01f;
		m_progress = Math::Min({ m_progress, 0.9999f });
	}
	// タイマー戻す
	if (Input::IsPressed(KEY_INPUT_2))
	{
		m_progress -= 0.01f;
		m_progress = Math::Max({ m_progress, 0.0f });
	}
	// 次のアニメーション
	if (Input::IsClicked(KEY_INPUT_3))
	{
		++m_animNumber %= m_maxAnimNum;
		m_progress = 0.0f;
	}
	// 前のアニメーション
	if (Input::IsClicked(KEY_INPUT_4))
	{
		m_animNumber = (--m_animNumber += m_maxAnimNum) % m_models.size();
		m_progress = 0.0f;
	}
	// 次のモデル
	if (Input::IsClicked(KEY_INPUT_5))
	{
		++m_currentModelNum %= m_models.size();
		setMaxAnimNum();
	}
	// 前のモデル
	if (Input::IsClicked(KEY_INPUT_6))
	{
		m_currentModelNum = (--m_currentModelNum += m_models.size()) % m_models.size();
		setMaxAnimNum();
	}
}

void ObjectViewer::drawModel(Renderer& renderer)
{
	if (m_models.empty())
	{
		return;
	}

	if (m_currentModelNum == -1)
	{
		return;
	}
	auto& name = m_models.at(m_currentModelNum);
	renderer.setScale(name, Vector3::One());
	renderer.drawSkinModel(name, m_pose, m_animNumber, m_progress);
}

void ObjectViewer::cameraUpdate()
{
	// 各方向ベクトルの定義
	Vector3 right = m_camera.right();
	Vector3 up = m_camera.up();
	Vector3 forward = m_camera.forward();

	// 移動処理
	const float SPEED = 0.6f;
	move(SPEED, right, up, forward);

	// 回転処理
	const double ANGLE = Math::ToRadian(1.0);
	rotate(ANGLE, right, up, forward);
}

void ObjectViewer::setMaxAnimNum()
{
	int handle = Singleton<HandleList>::Instance().getHandle(m_models.at(m_currentModelNum));
	m_maxAnimNum = MV1GetAnimNum(handle);
}

void ObjectViewer::setCameraData()
{
	
}

void ObjectViewer::move(float speed, const Vector3& right, const Vector3& up, const Vector3& forward)
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

void ObjectViewer::rotate(double angle, const Vector3& X, const Vector3& Y, const Vector3& Z)
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
