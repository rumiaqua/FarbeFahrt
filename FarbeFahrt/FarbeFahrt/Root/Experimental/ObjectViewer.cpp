# include "ObjectViewer.h"

# include "Utility/Debug.h"
# include "Utility/Matrix.h"
# include "Utility/Def.h"
# include "Utility/Loader.h"

# include "Scene/ISceneMediator.h"

ObjectViewer::ObjectViewer()
	: m_files()
{

}

void ObjectViewer::loadContents(Loader& loader)
{
	NoUse(loader);
}

void ObjectViewer::initialize()
{
	Debug::SetClear(true);

	SetCameraViewMatrix(Matrix::LookAt({ 0.0f, 100.0f, -100.0f }, Vector3::Zero(), Vector3::Up()));
	SetupCamera_ProjectionMatrix(Matrix::Perspective(45.0, nScreenSizeX / nScreenSizeY, 0.1f, 1000.0f));

	SetDragFileValidFlag(TRUE);
}

void ObjectViewer::update()
{
	int num = GetDragFileNum();
	if (num == 0)
	{
		return;
	}

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

void ObjectViewer::draw(Renderer& render)
{
	NoUse(render);

	for (auto&& file : m_files)
	{
		Debug::Println(file);
	}
}

void ObjectViewer::post()
{
	
}

void ObjectViewer::cleanUp()
{
	SetDragFileValidFlag(FALSE);
}

bool ObjectViewer::isSwallow() const
{
	return true;
}
