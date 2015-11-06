#include "BaseActor.h"

# include "Collision/IShape.h"

BaseActor::BaseActor(IWorld& world, const String& name, const Vector3& position, const Matrix& rotation, const IShapePtr& shape)
	: m_world(&world)
	, m_name(name)
	, m_pose(position, rotation)
	, m_dead(false)
	, m_parent(nullptr)
	, m_shape(shape)
{

}
//デフォルトコンストラクタ
BaseActor::BaseActor(const std::string& name)
	: m_world(nullptr)
	, m_name(name)
	, m_pose()
	, m_dead(false)
	, m_parent(nullptr)
	, m_shape(nullptr)
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
void BaseActor::collide(BaseActor& folder)
{
	onCollide(folder);
}
bool BaseActor::isDead()const
{
	return m_dead;
}
void BaseActor::kill()
{
	m_dead = true;
}
const String& BaseActor::getName() const
{
	return m_name;
}
Matrix BaseActor::getPose() const
{
	return m_pose.getPose();
}
Vector3& BaseActor::getPosition()
{
	return m_pose.getPosition();
}
const Vector3& BaseActor::getPosition() const
{
	return m_pose.getPosition();
}
Matrix& BaseActor::getRotation()
{
	return m_pose.getRotation();
}
const Matrix& BaseActor::getRotation() const
{
	return m_pose.getRotation();
}
Matrix BaseActor::getWorldPose() const
{
	Matrix worldPose = getPose();
	const BaseActor* actor = this;
	while (actor = actor->m_parent)
	{
		worldPose *= actor->getPose();
	}

	return worldPose;
}
Actor BaseActor::find(const String& name) const
{
	return findPred([&] (const BaseActor& actor) {return actor.getName() == name; });
}
Actor BaseActor::findPred(const std::function<bool(const BaseActor&)>& func) const
{
	auto i = std::find_if(m_children.begin(), m_children.end(),
		[&] (const Actor& child) {return func(*child); });
	if (i != m_children.end())
	{
		return *i;
	}
	for (auto&& child : m_children)
	{
		auto actor = child->findPred(func);
		if (actor != nullptr)
		{
			return actor;
		}
	}
	return nullptr;
}
void BaseActor::addChild(const Actor& child)
{
	m_children.push_front(child);
	child->m_parent = this;
}
void BaseActor::eachChildren(const std::function<void(BaseActor&)>& func)
{
	std::for_each(m_children.begin(), m_children.end(),
		[&] (const Actor& actor) {func(*actor); });
}
void BaseActor::eachChildren(const std::function<void(const BaseActor&)>& func)const
{
	std::for_each(m_children.begin(), m_children.end(),
		[&] (const Actor& actor) {func(*actor); });
}
void BaseActor::removeChildren(const std::function<bool(BaseActor& actor)>& func)
{
	m_children.remove_if
		([&] (const Actor& actor) {return func(*actor); });
}
void BaseActor::removeChildren()
{
	removeChildren([] (BaseActor& actor) {return actor.isDead(); });
	eachChildren([] (BaseActor&actor) {actor.removeChildren(); });
}

void BaseActor::sendMessage(const String& message, const void* parameter)
{
	onMessage(message, parameter);
}

bool BaseActor::isCollide(const BaseActor& other) const
{
	// 衝突図形が空なら衝突判定は行なわない
	if (!m_shape || !other.m_shape)
	{
		return false;
	}
	return m_shape->intersects(*other.m_shape);
}

void BaseActor::onUpdate()
{
	eachChildren([&] (BaseActor& actor) {actor.update(); });
}

void BaseActor::onDraw(Renderer& render) const
{
	if (m_shape)
	{
		m_shape->transform(getWorldPose())->draw();
	}
	eachChildren([&] (const BaseActor& actor) { actor.draw(render); });
}

void BaseActor::onCollide(BaseActor& actor)
{
	if (isCollide(actor))
	{
		onMessage("Hit", (void*)&actor);
		actor.onMessage("Hit", (void*)&actor);
	}
	eachChildren([&] (BaseActor& child) { child.collide(actor); });
}

void BaseActor::onMessage(const String& message, const void* parameter)
{
	eachChildren([&] (BaseActor& actor) { actor.sendMessage(message, parameter); });
}

BaseActor::~BaseActor()
{

}
