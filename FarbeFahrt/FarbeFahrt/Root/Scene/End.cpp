# include "End.h"

# include "Utility/Loader.h"
# include "Utility/Renderer.h"
# include "Utility/StoryManager/StoryManager.h"
# include "Utility/Input.h"
# include "Utility/HandleList.h"
# include "Utility/SingletonFinalizer.h"

# include "Manager/EndManager.h"
# include "Manager/MessageManager.h"

# include "Scene/ISceneMediator.h"

# include "Scene.h"

End::End()
	: m_endNum()
{

}

void End::loadContents(Loader& loader)
{

}

void End::initialize()
{
	std::string end = EndManager::Get();
	MessageManager::Add(end);
	MessageManager::SetShow(true);
	m_manager->pushScene(Scene::Message);
}

void End::update()
{
	m_manager->changeScene(EndManager::IsShowStaffRoll() ? Scene::StaffRoll : Scene::Title, 15.0f);
}

void End::draw(Renderer& renderer)
{

}

void End::post()
{

}

void End::cleanUp()
{

}

bool End::isSwallow() const
{
	return true;
}
