#pragma once
#include "cocos2d.h"

//block class
class Block{
public:
	Block(cocos2d::Scene* parentScene, const cocos2d::Vec2 &start, const cocos2d::Vec2 &end, float a_mass, 
		cocos2d::Vec2 a_velocity, cocos2d::Vec2 a_acceleration, float a_angle, float a_staticFriction, 
		float a_dynamicFriction);
	~Block();

	cocos2d::DrawNode* getPrimitive();

	float getMass();
	void setMass(float a_mass);

	cocos2d::Vec2 getVelocity();
	void setVelocity(cocos2d::Vec2 a_velocity);

	cocos2d::Vec2 getAcceleration();
	void setAcceleration(cocos2d::Vec2 a_acceleration);

	float getAngle();
	void setAngle(float a_angle);

	float getStaticFriction();
	void setStaticFriction(float a_staticFriction);

	float getDynamicFriction();
	void setDynamicFriction(float a_dynamicFriction);

	cocos2d::Vec2 getPosition();
	void setPosition(cocos2d::Vec2 a_Position);

	void update(float dt);

private:
	//drawing
	cocos2d::Scene *parentScene;
	cocos2d::DrawNode *blockNode;

	//block variables
	float mass;
	cocos2d::Vec2 velocity;
	cocos2d::Vec2 acceleration;
	cocos2d::Vec2 force;

	cocos2d::Vec2 position;

	float angle;
	float staticFriction;
	float dynamicFriction;
};