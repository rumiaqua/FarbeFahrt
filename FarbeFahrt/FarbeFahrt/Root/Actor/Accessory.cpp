# include "Accessory.h"
# include "StaticObject.h"
# include "Collision/Empty.h"
# include "Utility/Math.h"

Accessory::Accessory(IWorld& world)
	: BaseActor(world, "Accessory", Vector3::Zero(), Matrix::identity(), std::make_shared<Empty>())
	, m_herb()
	, m_medicine()
	, m_elder()
{
	m_herb = std::make_shared<StaticObject>(
		*m_world, "HerbAccessory", Vector3(150.0f, 20.0f, 50.0f), (float)Math::ToRadian(-90.0), 0.75f);

	m_medicine = std::make_shared<StaticObject>(
		// *m_world, "MedicineAccessory", Vector3(-300.0f, 20.0f, 50.0f), (float)Math::ToRadian(-60.0), 0.75f);
		*m_world, "MedicineAccessory", Vector3(150.0f, 20.0f, 50.0f), (float)Math::ToRadian(-120.0), 0.75f);

	m_elder = std::make_shared<StaticObject>(
		// *m_world, "ElderAccessory", Vector3(-300.0f, 20.0f, -50.0f), (float)Math::ToRadian(-90.0), 0.75f);
		*m_world, "ElderAccessory", Vector3(150.0f, 20.0f, 50.0f), (float)Math::ToRadian(-90.0), 0.75f);

	addChild(m_herb);
	addChild(m_medicine);
	addChild(m_elder);

	m_herb->sendMessage("Invisible", nullptr);
	m_medicine->sendMessage("Invisible", nullptr);
	m_elder->sendMessage("Invisible", nullptr);
}

void Accessory::onMessage(const std::string& message, void* parameter)
{
	if (message == "VisibleAccessory")
	{
		std::string name = *(std::string*)parameter;
		m_herb->sendMessage(m_herb->getName() == name ? "Visible" : "InVisible", nullptr);
		m_medicine->sendMessage(m_medicine->getName() == name ? "Visible" : "Invisible", nullptr);
		m_elder->sendMessage(m_elder->getName() == name ? "Visible" : "Invisible", nullptr);
	}

	BaseActor::onMessage(message, parameter);
}
