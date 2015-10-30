#pragma once
#include "Utility/Renderer.h"
#include "IWorld.h"
#include "Actor.h"
#include <string>
#include <algorithm>
#include <functional>
#include <forward_list>
# include "Utility/Pose.h"
# include "Utility/String.h"
class BaseActor
{
public:
	BaseActor(IWorld& world, const String& name, const Vector3& position, const Matrix& rotation);
	explicit BaseActor(const std::string& name = "none");
	virtual ~BaseActor();

	void update();
	void draw(Renderer& render)const;

	bool isDead()const;
	void kill();

	const String& getName()const;

	Matrix getPose() const;
	Vector3& getPosition();
	const Vector3& getPosition() const;
	Matrix& getRotation();
	const Matrix& getRotation() const;
	Matrix getWorldPose() const;

	Actor findChildren(const String& name);
	Actor findChildren(std::function<bool(const BaseActor&)>func);

	void addChild(const Actor& child);
	void eachChildren(std::function<void(BaseActor&)>func);
	void eachChildren(std::function<void(const BaseActor&)>func)const;
	void removeChildren(std::function<bool(BaseActor&)>func);
	void clearChildren();
	void removeChildren();

	void sendMessage(const String& message, const void* parameter);

	BaseActor(const BaseActor& other) = delete;
	BaseActor& operator = (const BaseActor& other) = delete;

protected:
	virtual void onUpdate();
	virtual void onDraw(Renderer& render)const;
	virtual void onMessage(const String& message, const void* parameter);
protected:
	IWorld* world;
	String name;
	Pose pose;
	bool dead;
private:
	ActorRef parent;
	std::forward_list<Actor>children;
};
