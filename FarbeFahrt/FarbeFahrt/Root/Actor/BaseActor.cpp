#include "BaseActor.h"

# include "Collision/IShape.h"

# include <iterator>

BaseActor::BaseActor(IWorld& world, const std::string& name, const Vector3& position, const Matrix& rotation, const IShapePtr& shape)
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
	m_previousPose = m_pose;
	onUpdate();
}
void BaseActor::draw(Renderer& renderer)const
{
	onDraw(renderer);
}
void BaseActor::collide(BaseActor* folder)
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
const std::string& BaseActor::getName() const
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
Actor BaseActor::find(const std::string& name) const
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
std::vector<Actor> BaseActor::finds(const std::string& name) const
{
	// 検索結果
	std::vector<Actor> result;

	for (auto&& child : m_children)
	{
		// 子供の名前が一致したら追加
		if (child->getName() == name)
		{
			result.push_back(child);
		}

		// 子供の子供から検索
		std::vector<Actor> childs = child->finds(name);
		std::copy(childs.begin(), childs.end(), std::back_inserter(result));
	}

	return result;
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

void BaseActor::sendMessage(const std::string& message, void* parameter)
{
	onMessage(message, parameter);
}

bool BaseActor::isCollide(const BaseActor* other) const
{
	// 衝突図形が空なら衝突判定は行なわない
	if (!m_shape || !other->m_shape)
	{
		return false;
	}
	return getShape()->intersects(*other->getShape());
}

IShape* const BaseActor::getShape() const
{
	return m_shape->transform(getWorldPose());
}

void BaseActor::onUpdate()
{
	eachChildren([&] (BaseActor& actor) {actor.update(); });
}

void BaseActor::onDraw(Renderer& renderer) const
{
	if (m_shape)
	{
		renderer.drawPrimitive(*m_shape->transform(getWorldPose()));
	}
	
	eachChildren([&] (const BaseActor& actor) { actor.draw(renderer); });
}

void BaseActor::onCollide(BaseActor* actor)
{
	if (isCollide(actor))
	{
		onMessage("onCollide", (void*)actor);
		actor->onMessage("onCollide", (void*)this);
	}
	eachChildren([&] (BaseActor& child) { child.collide(actor); });
}

void BaseActor::onMessage(const std::string& message, void* parameter)
{
	eachChildren([&] (BaseActor& actor) { actor.sendMessage(message, parameter); });
}

BaseActor::~BaseActor()
{

}
