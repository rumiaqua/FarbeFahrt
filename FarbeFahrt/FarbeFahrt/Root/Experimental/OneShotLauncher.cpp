# include "OneShotLauncher.h"
# include "OneShotStage.h"

# include "Utility/Input.h"
# include "Utility/Renderer.h"

# include "Scene/ISceneMediator.h"
# include "Scene/Scene.h"

OneShotLauncher::OneShotLauncher()
{

}

void OneShotLauncher::loadContents(Loader & loader)
{
}

void OneShotLauncher::initialize()
{
}

void OneShotLauncher::update()
{
	clickToStage(KEY_INPUT_F1, "Resources/Script/Stage/PlainA.txt");
	clickToStage(KEY_INPUT_F2, "Resources/Script/Stage/PlainB.txt");
	clickToStage(KEY_INPUT_F3, "Resources/Script/Stage/ForestA.txt");
	clickToStage(KEY_INPUT_F4, "Resources/Script/Stage/ForestA.txt");
	clickToStage(KEY_INPUT_F5, "Resources/Script/Stage/ForestB.txt");
	clickToStage(KEY_INPUT_F6, "Resources/Script/Stage/ForestC.txt");
	clickToStage(KEY_INPUT_F7, "Resources/Script/Stage/ForestD.txt");
	clickToStage(KEY_INPUT_F8, "Resources/Script/Stage/DimForest.txt");
	clickToStage(KEY_INPUT_F9, "Resources/Script/Stage/Lowles.txt");
	clickToStage(KEY_INPUT_F10, "Resources/Script/Stage/Heiles.txt");
	clickToStage(KEY_INPUT_F11, "Resources/Script/Stage/DangerSwamp.txt");
}

void OneShotLauncher::draw(Renderer & render)
{

}

void OneShotLauncher::post()
{
}

void OneShotLauncher::cleanUp()
{
}

bool OneShotLauncher::isSwallow() const
{
	return true;
}

void OneShotLauncher::clickToStage(int key, const std::string& name)
{
	if (Input::IsClicked(key))
	{
		OneShotStage::load(name);
		m_manager->changeScene(Scene::OneShotStage, 30.0f);
	}
}
