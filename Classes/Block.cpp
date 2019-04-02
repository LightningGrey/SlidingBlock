#include "Block.h"

Block::Block(cocos2d::Scene* parentScene, const cocos2d::Vec2 &start, const cocos2d::Vec2 &end, float a_mass, 
	cocos2d::Vec2 a_velocity, cocos2d::Vec2 a_acceleration, float a_angle, float a_staticFriction, 
	float a_kineticFriction) 
	: blockNode(cocos2d::DrawNode::create()), mass (a_mass), velocity (a_velocity), 
	acceleration (a_acceleration), angle (a_angle), staticFriction (a_staticFriction),
	kineticFriction(a_kineticFriction)
{
	stopped = true;
	//drawRect draws from corner of node to distant between start and end position
	//draws rectangle to node instead of relative position from node, easier to understand positioning
	blockNode->drawSolidRect(cocos2d::Vec2(0.0f, 0.0f), end - start,
		cocos2d::Color4F(0.0f, 1.0f, 0.0f, 1.0f));
	blockNode->setPosition(start);

	getPrimitive()->setRotation(getAngle());
	position = blockNode->getPosition();

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

float Block::getKineticFriction()
{
	return kineticFriction;
}

void Block::setKineticFriction(float a_kineticFriction)
{
	this->kineticFriction = a_kineticFriction;
}

cocos2d::Vec2 Block::getPosition()
{
	return position;
}

void Block::setPosition(cocos2d::Vec2 a_Position)
{
	this->position = position;
}

bool Block::getStopped()
{
	return stopped;
}

void Block::setStopped(bool a_stopped)
{
	this->stopped = a_stopped;
}

void Block::update(float dt)
{
	//force = cocos2d::Vec2((mass * 9.80f * sin(angle*3.14f / 180.f)) - ((mass * 9.80f)*kineticFriction),
	//	mass * -9.80f * cos(angle*3.14f / 180.f));
	force = cocos2d::Vec2((mass * 9.80f * sin(angle*3.14f / 180.f)) - ((mass * 9.80f)*kineticFriction),
			mass * 9.80f * cos(angle*3.14f / 180.f));
	if (sqrt((force.x * force.x) + (force.y * force.y)) <= mass * 9.80f * staticFriction) {
		setVelocity(cocos2d::Vec2(0,0));
		stopped = true;
	}
	else {
		acceleration = cocos2d::Vec2(9.80f*(cos(angle*3.14f / 180.f) - (kineticFriction*sin(angle*3.14f / 180.f))),
			-9.80f*cos(angle*3.14f / 180.f));
		//acceleration = cocos2d::Vec2(9.80f * (sin(angle*3.14f / 180.f) - (kineticFriction*cos(angle*3.14f / 180.f))),
		//	-9.80f * cos(angle*3.14f / 180.f));
		velocity += acceleration * dt;
		position = getPrimitive()->getPosition() + (velocity * dt);
		getPrimitive()->setPosition(position);
	}
}
