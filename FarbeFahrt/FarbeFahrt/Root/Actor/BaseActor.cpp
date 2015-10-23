#include "BaseActor.h"

BaseActor::BaseActor(IWorld& world, const String& name, const Vector3& position, const Matrix& rotation)
	:world(&world),
	name(name),
	pose(position, rotation),
	dead(false),
	parent(nullptr)
{
}
//デフォルトコンストラクタ
BaseActor::BaseActor(const std::string& name) :
world(nullptr),
name(name),
pose(),
dead(false),
parent(nullptr)
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
const String& BaseActor::getName()const
{
	return name;
}
Matrix BaseActor::getPose() const
{
	return pose.getPose();
}
Vector3& BaseActor::getPosition()
{
	return pose.getPosition();
}
const Vector3& BaseActor::getPosition() const
{
	return pose.getPosition();
}
Matrix& BaseActor::getRotation()
{
	return pose.getRotation();
}
const Matrix& BaseActor::getRotation() const
{
	return pose.getRotation();
}
Matrix BaseActor::getWorldPose() const
{
	Matrix worldPose = pose.getPose();
	while (ActorRef actor = parent)
	{
		worldPose *= actor->getPose();
	}
	return worldPose;
}
Actor BaseActor::findChildren(const String& name)
{
	return findChildren([&](const BaseActor& actor){return actor.getName() == name; });
}
Actor BaseActor::findChildren(std::function<bool(const BaseActor&)> func)
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
void BaseActor::addChild(const Actor& child)
{
	children.push_front(child);
	child->parent = this;
}
void BaseActor::eachChildren(std::function<void(BaseActor&)> func)
{
	std::for_each(children.begin(), children.end(),
		[&](const Actor& actor){func(*actor); });
}
void BaseActor::eachChildren(std::function<void(const BaseActor&)> func)const
{
	std::for_each(children.begin(), children.end(),
		[&](const Actor& actor){func(*actor); });
}
void BaseActor::removeChildren(std::function<bool(BaseActor& actor)> func)
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

void BaseActor::sendMessage(const String& message, const void* parameter)
{
	onMessage(message, parameter);
}

void BaseActor::onUpdate()
{
	eachChildren([&](BaseActor& actor){actor.update(); });
}

void BaseActor::onDraw(Renderer& render)const
{
	eachChildren([&](const BaseActor& actor){actor.draw(render); });
}

void BaseActor::onMessage(const String& message, const void* parameter)
{
	eachChildren([&] (BaseActor& actor) { actor.sendMessage(message, parameter); });
}

BaseActor::~BaseActor()
{

}
