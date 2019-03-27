#include "Slope.h"

Slope::Slope(cocos2d::Scene* parentScene, const cocos2d::Vec2 &start, const cocos2d::Vec2 &end, 
	float a_friction, float a_angle) :
	slopeNode(cocos2d::DrawNode::create()), angle(a_angle), friction(a_friction)
{
	slopeNode->drawLine(cocos2d::Vec2(0.0f, 0.0f), end - start,
		cocos2d::Color4F(1.0f, 0.0f, 0.0f, 1.0f));
	slopeNode->setPosition(start);

	getPrimitive()->setRotation(getAngle());

	this->parentScene = parentScene;
	parentScene->addChild(slopeNode);
}

Slope::~Slope()
{
}

cocos2d::DrawNode * Slope::getPrimitive()
{
	return slopeNode;
}

float Slope::getFriction()
{
	return friction;
}

void Slope::setFriction(float a_friction)
{
	this->friction = a_friction;
}

float Slope::getAngle()
{
	return angle;
}

void Slope::setAngle(float a_angle)
{
	this->angle = a_angle;
}
