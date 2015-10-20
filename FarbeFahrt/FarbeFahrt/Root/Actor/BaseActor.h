#pragma once
#include "Utility/Renderer.h"
#include "IWorld.h"
#include "Actor.h"
#include <string>
#include <algorithm>
#include <functional>
#include <forward_list>
# include "Utility/Vector3.h"
class BaseActor
{
public:
	BaseActor(IWorld& world, const std::string& name, const Vector3& position, const Vector3& rotation);
	BaseActor(const std::string& name = "none");
	virtual ~BaseActor();

	void update();
	void draw(Renderer& render)const;

	bool isDead()const;
	void kill();

	const std::string& getName()const;

	Vector3 getPosition()const;
	Vector3 getRotation()const;

	Actor findChildren(const std::string& name);
	Actor findChildren(std::function<bool(const BaseActor&)>func);

	void addChild(const Actor& child);
	void eachChildren(std::function<void(BaseActor&)>func);
	void eachChildren(std::function<void(const BaseActor&)>func)const;
	void removeChildren(std::function<bool(BaseActor&)>func);
	void clearChildren();
	void removeChildren();

	BaseActor(const BaseActor& other) = delete;
	BaseActor& operator = (const BaseActor& other) = delete;

private:
	virtual void onUpdate();
	virtual void onDraw(Renderer& render)const;
protected:
	IWorld* world;
	std::string name;
	Vector3 position;
	Vector3 rotation;
	bool dead;
private:
	std::forward_list<Actor>children;
};
