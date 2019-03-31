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

	block = new Block(this, cocos2d::Vec2(0, 900), cocos2d::Vec2(200, 1000), 200.0f, 
		cocos2d::Vec2(0.0f, 0.0f), cocos2d::Vec2(0.0f,0.0f), 30.0f, 0.10f, 0.10f);
	slope = new Slope(this, cocos2d::Vec2(0, 900), cocos2d::Vec2(2000, 900), 0.20f, 30.0f);
	
}

void HelloWorld::update(float dt) {
	if (q == true) {
		block->setStaticFriction(block->getStaticFriction() - 1);
	}
	if (e == true) {
		block->setStaticFriction(block->getStaticFriction() + 1);
	}
	if (a == true) {
		block->setDynamicFriction(block->getDynamicFriction() - 1);
	}
	if (d == true) {
		block->setDynamicFriction(block->getDynamicFriction() + 1);
	}
	if (up == true) {
		block->setAngle(block->getAngle()-1);
		slope->setAngle(slope->getAngle()-1);
		block->getPrimitive()->setRotation(block->getAngle() - 1);
		slope->getPrimitive()->setRotation(slope->getAngle() - 1);
	}
	if (down == true) {
		block->setAngle(block->getAngle() + 1);
		slope->setAngle(slope->getAngle() + 1);
		block->getPrimitive()->setRotation(block->getAngle() + 1);
		slope->getPrimitive()->setRotation(slope->getAngle() + 1);
	}
	if (space == true) {
		block->getPrimitive()->setPosition(cocos2d::Vec2(0, 900));
		block->setVelocity(cocos2d::Vec2(0.0f, 0.0f));
		//space = false;
	}

	if (block->getPrimitive()->getPosition().y < 0.0f) {
		block->setVelocity(cocos2d::Vec2(0.0f, 0.0f));
	}

	block->update(dt);

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
