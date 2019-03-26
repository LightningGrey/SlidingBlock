#include "Block.h"

Block::Block(cocos2d::Scene* parentScene, const cocos2d::Vec2 &start, const cocos2d::Vec2 &end, float a_mass, 
	cocos2d::Vec2 a_velocity, cocos2d::Vec2 a_acceleration, float a_angle, float a_staticFriction, 
	float a_dynamicFriction) 
	: blockNode(cocos2d::DrawNode::create()), mass (a_mass), velocity (a_velocity), 
	acceleration (a_acceleration), angle (a_angle), staticFriction (a_staticFriction),
	dynamicFriction(a_dynamicFriction)
{
	//drawRect draws from corner of node to distant between start and end position
	//draws rectangle to node instead of relative position from node, easier to understand positioning
	blockNode->drawSolidRect(cocos2d::Vec2(0.0f, 0.0f), end - start,
		cocos2d::Color4F(0.0f, 1.0f, 0.0f, 1.0f));
	blockNode->setPosition(start);

	this->parentScene = parentScene;
	parentScene->addChild(blockNode);
}

Block::~Block()
{
}

cocos2d::DrawNode * Block::getPrimitive()
{
	return blockNode;
}

float Block::getMass()
{
	return mass;
}

void Block::setMass(float a_mass)
{
	this->mass = a_mass;
}

cocos2d::Vec2 Block::getVelocity()
{
	return velocity;
}

void Block::setVelocity(cocos2d::Vec2 a_velocity)
{
	this->velocity = a_velocity;
}

cocos2d::Vec2 Block::getAcceleration()
{
	return acceleration;
}

void Block::setAcceleration(cocos2d::Vec2 a_acceleration)
{
	this->acceleration = a_acceleration;
}

float Block::getAngle()
{
	return angle;
}

void Block::setAngle(float a_angle)
{
	this->angle = a_angle;
}

float Block::getStaticFriction()
{
	return staticFriction;
}

void Block::setStaticFriction(float a_staticFriction)
{
	this->staticFriction = a_staticFriction;
}

float Block::getDynamicFriction()
{
	return dynamicFriction;
}

void Block::setDynamicFriction(float a_dynamicFriction)
{
	this->dynamicFriction = a_dynamicFriction;
}

void Block::update(float dt)
{
	//force = (this->mass * 9.8, 0);
	//acceleration;
	//velocity = ;
    getPrimitive()->setPosition(position);
}
