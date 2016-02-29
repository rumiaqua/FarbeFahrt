# include "AllResourceLoad.h"

# include "Utility/Loader.h"
# include "Utility/Renderer.h"

# include "Scene/ISceneMediator.h"
# include "Scene/Scene.h"

# include "Stage/StageManager.h"

AllResourceLoad::AllResourceLoad()
{

}

void AllResourceLoad::loadContents(Loader& loader)
{
	loader.loadContent("BadEndBGM", "Sound/BGM/bad_end.mp3");
	loader.loadContent("ClearBGM", "Sound/BGM/end2.mp3");

	loader.loadContent("page0", "Texture/demo0.png");
	loader.loadContent("page1", "Texture/demo1.png");
	loader.loadContent("page2", "Texture/demo2.png");
	loader.loadContent("page3", "Texture/demo3.png");

	loader.loadContent("book", "Model/Book/Book.pmx");
	loader.loadContent("desk", "Model/Š÷/‚Â‚­‚¦.mqo");

	loader.loadContent("Clear", "Texture/end/clear.png");
	loader.loadContent("curtain", "Texture/curtain.png");

	loader.loadContent("end1", "Texture/end/end1.png");
	loader.loadContent("end2", "Texture/end/end2.png");
	loader.loadContent("end3", "Texture/end/end3.png");
	loader.loadContent("end5", "Texture/end/end5.png");

	loader.loadContent("Message", "Texture/end/message.png");
	loader.loadContent("staffRoll", "Texture/StaffRoll.png");
	loader.loadContent("Player", "Model/MMD–‚“±Žo’íVer1.1/ƒ~ƒnƒCƒ‹.pmx");
	loader.loadContent("PlayerRiding", "Model/MMD–‚“±Žo’íVer1.1/Žo’í.pmx");
	loader.loadContent("LightParticle", "Texture/Particle.png");

	loader.loadContent("TitleChooseBack", "Texture/TitleChoose/Back.png");
	loader.loadContent("YesOutMouse", "Texture/TitleChoose/yes.png");
	loader.loadContent("YesOnMouse", "Texture/TitleChoose/yes2.png");
	loader.loadContent("NoOutMouse", "Texture/TitleChoose/no.png");
	loader.loadContent("NoOnMouse", "Texture/TitleChoose/no2.png");

	loader.loadContent("HerbAccessory", "Model/3D/ü‚è•r•‰Ô/ü‚è•r•‰Ô.mqo");
	loader.loadContent("MedicineAccessory", "Model/3D/–ò/–ò.mqo");
	loader.loadContent("ElderAccessory", "Model/3D/—¢’·¬•r/¬•r.mqo");

	StageManager manager;
	manager.initialize("Resources/Script/Stage/index.csv");
	for (auto&& data : manager.allStageData())
	{
		for (auto&& resource : data.second.resourceList)
		{
			loader.loadContent(resource.first, resource.second);
		}
	}
}

void AllResourceLoad::initialize()
{
}

void AllResourceLoad::update()
{
	m_manager->popScene();
}

void AllResourceLoad::draw(Renderer & renderer)
{

}

void AllResourceLoad::post()
{
}

void AllResourceLoad::cleanUp()
{
}

bool AllResourceLoad::isSwallow() const
{
	return true;
}
