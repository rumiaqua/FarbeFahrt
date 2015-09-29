#include "BaseActor.h"

BaseActor::BaseActor(IWorld& world, const std::string& name, const VECTOR& position, const VECTOR& rotation)
	:world(&world),
	name(name),
	position(position),
	rotation(rotation),
	dead(false)
{
}
//デフォルトコンストラクタ
BaseActor::BaseActor(const std::string& name) :
world(nullptr),
name(name),
position(VGet(0.0f, 0.0f, 0.0f)),
rotation(VGet(0.0f, 0.0f, 0.0f)),
dead(false)
{
}
void BaseActor::update()
{
	onUpdate();
}
void BaseActor::draw(Renderer& render)const
{
	onDraw(render);
}
bool BaseActor::isDead()const
{
	return dead;
}
void BaseActor::kill()
{
	dead = true;
}
const std::string& BaseActor::getName()const
{
	return name;
}
VECTOR BaseActor::getPosition()const
{
	return position;
}
VECTOR BaseActor::getRotation()const
{
	return rotation;
}
Actor BaseActor::findChildren(const std::string&name)
{
	return findChildren([&](const BaseActor& actor){return actor.getName() == name; });
}
Actor BaseActor::findChildren(std::function<bool(const BaseActor&)>func)
{
	auto i = std::find_if(children.begin(), children.end(),
		[&](const Actor& child){return func(*child); });
	if (i != children.end())
	{
		return *i;
	}
	for (auto child : children)
	{
		auto actor = child->findChildren(func);
		if (actor != nullptr)
		{
			return actor;
		}
	}
	return nullptr;
}
void BaseActor::addChild(const Actor&child)
{
	children.push_front(child);
}
void BaseActor::eachChildren(std::function<void(BaseActor&)>func)
{
	std::for_each(children.begin(), children.end(),
		[&](const Actor& actor){func(*actor); });
}
void BaseActor::eachChildren(std::function<void(const BaseActor&)>func)const
{
	std::for_each(children.begin(), children.end(),
		[&](const Actor& actor){func(*actor); });
}
void BaseActor::removeChildren(std::function<bool(BaseActor& actor)>func)
{
	children.remove_if
		([&](const Actor& actor){return func(*actor); });
}
void BaseActor::clearChildren()
{
	children.clear();
}
void BaseActor::removeChildren()
{
	removeChildren([](BaseActor& actor){return actor.isDead(); });
	eachChildren([](BaseActor&actor){actor.removeChildren(); });
}

void BaseActor::onUpdate()
{
	eachChildren([&](BaseActor& actor){actor.update(); });
}

void BaseActor::onDraw(Renderer& render)const
{
	eachChildren([&](const BaseActor& actor){actor.draw(render); });
}

BaseActor::~BaseActor()
{
}