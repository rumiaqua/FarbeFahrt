#pragma once
#include "Utility/Renderer.h"
#include "IWorld.h"
#include "Actor.h"
#include <string>
#include <algorithm>
#include <functional>
#include <forward_list>
class BaseActor
{
public:
	BaseActor(IWorld& world, const std::string& name, const VECTOR& position, const VECTOR& rotation);
	BaseActor(const std::string& name = "none");
	virtual ~BaseActor();

	void update();
	void draw(Renderer& render)const;

	bool isDead()const;
	void kill();

	const std::string& getName()const;

	VECTOR getPosition()const;
	VECTOR getRotation()const;

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
	VECTOR position;
	VECTOR rotation;
	bool dead;
private:
	std::forward_list<Actor>children;
};
