#pragma once
#include "cocos2d.h"

//slope class 
class Slope{
public:
	Slope(const cocos2d::Vec2 &start, const cocos2d::Vec2 &end, float a_friction, float a_angle);
	~Slope();

	cocos2d::DrawNode* getPrimitive();

	float getFriction();
	void setFriction(float a_friction);
	
	float getAngle();
	void setAngle(float a_angle);

private:
	//drawing
	cocos2d::DrawNode *slopeNode;

	float friction;
	float angle;
};