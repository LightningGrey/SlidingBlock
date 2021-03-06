/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

//HelloWorld::HelloWorld() : block(cocos2d::Vec2(800, 450), cocos2d::Vec2(1000, 550), 100.0f, cocos2d::Vec2(0, 0), 
//	cocos2d::Vec2(0,0), 45.0f, 0.10f, 0.10f){
//
//}

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width/2;
        float y = origin.y + closeItem->getContentSize().height/2;
        closeItem->setPosition(Vec2(x,y));
    }

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

	//setting keyboard for input
	keyboard = cocos2d::EventListenerKeyboard::create();

	keyboard->onKeyPressed = CC_CALLBACK_2(HelloWorld::keyDown, this);
	keyboard->onKeyReleased = CC_CALLBACK_2(HelloWorld::keyUp, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboard, this);

	//update scheduling
	this->scheduleUpdate();

    /////////////////////////////
    // 3. add your codes below...

	slope = new Slope(this, cocos2d::Vec2(0, 900), cocos2d::Vec2(2000, 900), 30.0f);
	block = new Block(this, cocos2d::Vec2(0, 900), cocos2d::Vec2(200, 1000), 200.0f, 
		cocos2d::Vec2(0.0f, 0.0f), cocos2d::Vec2(0.0f,0.0f), slope->getAngle(), 0.10f, 0.20f);
	
	data = cocos2d::Label::createWithTTF("Mass:" + std::to_string(block->getMass()), "fonts/Arial.ttf", 24);
	data->setColor(cocos2d::Color3B::WHITE);
	data->setPosition(1150, 800);
	data->setSystemFontSize(12.0f);
	this->addChild(data);

	data1 = cocos2d::Label::createWithTTF("Mass:" + std::to_string(block->getMass()), "fonts/Arial.ttf", 24);
	data1->setColor(cocos2d::Color3B::WHITE);
	data1->setPosition(1150, 770);
	data1->setSystemFontSize(12.0f);
	this->addChild(data1);

	data2 = cocos2d::Label::createWithTTF("Mass:" + std::to_string(block->getMass()), "fonts/Arial.ttf", 24);
	data2->setColor(cocos2d::Color3B::WHITE);
	data2->setPosition(1150, 740);
	data2->setSystemFontSize(12.0f);
	this->addChild(data2);

}

void HelloWorld::update(float dt) {
	if (q == true && block->getStopped() == true && block->getStaticFriction() >= 0) {
		block->setStaticFriction(block->getStaticFriction() - 1.0f);
	}
	if (e == true && block->getStopped() == true) {
		block->setStaticFriction(block->getStaticFriction() + 1.0f);
	}
	if (a == true && block->getStopped() == true && block->getKineticFriction() >= 0) {
		block->setKineticFriction(block->getKineticFriction() - 1.0f);
	}
	if (d == true && block->getStopped() == true) {
		block->setKineticFriction(block->getKineticFriction() + 1.0f);
	}
	if (up == true && block->getAngle() >= 2.0f && block->getStopped() == true) {
		slope->setAngle(slope->getAngle() - 1.0f);
		block->setAngle(slope->getAngle());
		slope->getPrimitive()->setRotation(slope->getAngle());
		block->getPrimitive()->setRotation(slope->getAngle());

		if (block->getPrimitive()->getRotation() < 30.0f) {
			data->setPosition(400, 150);
			data1->setPosition(400, 120);
			data2->setPosition(400, 90);
		}
	}
	if (down == true && block->getAngle() <= 88.0f && block->getStopped() == true) {
		slope->setAngle(slope->getAngle() + 1.0f);
		block->setAngle(slope->getAngle());
		slope->getPrimitive()->setRotation(slope->getAngle());
		block->getPrimitive()->setRotation(block->getAngle());

		if (block->getPrimitive()->getRotation() > 45.0f) {
			data->setPosition(1150, 800);
			data1->setPosition(1150, 770);
			data2->setPosition(1150, 740);
		}
	}
	if (space == true && block->getStopped() == true) {
		block->setStopped(false);
		block->getPrimitive()->setPosition(cocos2d::Vec2(0, 900));
		block->setVelocity(cocos2d::Vec2(0.0f, 0.0));
	}

	if (block->getStopped() == false){
		block->update(dt);
	}

	if (block->getPrimitive()->getPosition().x > 1700.0f || 
		block->getPrimitive()->getPosition().y < -100.0f) {
		block->setVelocity(cocos2d::Vec2(0.0f, 0.0f));
		block->setAcceleration(cocos2d::Vec2(0.0f, 0.0f));
		block->setStopped(true);
	}

	data->setString("Mass: " + std::to_string(block->getMass()) +  "    Angle: " 
		+ std::to_string(block->getAngle()));
	data1->setString("Static Friction: " + std::to_string(block->getStaticFriction()) + 
		"    Dynamic Friction: " + std::to_string(block->getKineticFriction()));
	data2->setString("Velocity: [" + std::to_string(block->getVelocity().x) + ", " +
		std::to_string(block->getVelocity().y) + "]    Acceleration: [" + 
		std::to_string(block->getAcceleration().x) + ", " + std::to_string(block->getAcceleration().y)
		+ "]");
}

void HelloWorld::keyDown(cocos2d::EventKeyboard::KeyCode key, cocos2d::Event* event) {
	if (key == EventKeyboard::KeyCode::KEY_Q) {
		q = true;
	}
	if (key == EventKeyboard::KeyCode::KEY_E) {
		e = true;
	}
	if (key == EventKeyboard::KeyCode::KEY_A) {
		a = true;
	}
	if (key == EventKeyboard::KeyCode::KEY_D) {
		d = true;
	}
	if (key == EventKeyboard::KeyCode::KEY_UP_ARROW) {
		up = true;
	}
	if (key == EventKeyboard::KeyCode::KEY_DOWN_ARROW) {
		down = true;
	}
	if (key == EventKeyboard::KeyCode::KEY_SPACE) {
		space = true;
	}
}

void HelloWorld::keyUp(cocos2d::EventKeyboard::KeyCode key, cocos2d::Event* event) {
	if (key == EventKeyboard::KeyCode::KEY_Q) {
		q = false;
	}
	if (key == EventKeyboard::KeyCode::KEY_E) {
		e = false;
	}
	if (key == EventKeyboard::KeyCode::KEY_A) {
		a = false;
	}
	if (key == EventKeyboard::KeyCode::KEY_D) {
		d = false;
	}
	if (key == EventKeyboard::KeyCode::KEY_UP_ARROW) {
		up = false;
	}
	if (key == EventKeyboard::KeyCode::KEY_DOWN_ARROW) {
		down = false;
	}
	if (key == EventKeyboard::KeyCode::KEY_SPACE) {
		space = false;
	}
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}
