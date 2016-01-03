//
//  Obstacle.cpp
//  flapySample
//
//  Created by Nomura Takahisa on 2015/12/30.
//
//

#include "Obstacle.h"
#include <random>

USING_NS_CC;

bool Obstacle::init()
{
    if (!Node::init()) {
        return false;
    }
    _isPass = false;
  
    Size visibleSize = Director::getInstance()->getVisibleSize();
    std::random_device rnd;
    std::mt19937 mt(rnd());
    std::uniform_int_distribution<> rand100(100, visibleSize.height - 100);
    auto pathPosY = rand100(mt);

    _spriteList = std::vector<Sprite*>();
    auto upSprite = Sprite::create();
    Rect upRect = Rect(0, 0, 50, visibleSize.height - (pathPosY + 50));
    upSprite->setTextureRect(upRect);
    upSprite->setColor(Color3B::GREEN);
    upSprite->setAnchorPoint(Vec2(0, 0));
    upSprite->setPosition(0, pathPosY + 50);
    _spriteList.push_back(upSprite);
    this->addChild(upSprite);
 
    auto downSprite = Sprite::create();
    Rect downRect = Rect(0, 0, 50, pathPosY - 50);
    downSprite->setTextureRect(downRect);
    downSprite->setColor(Color3B::RED);
    downSprite->setAnchorPoint(Vec2(0, 0));
    downSprite->setPosition(0, 0);
    _spriteList.push_back(downSprite);
    this->addChild(downSprite);
   
    return true;
}

void Obstacle::setSpritePosX(float x)
{
    _spritePosX = x;
    for (auto sprite : _spriteList) {
        sprite->setPositionX(x);
    }
}
bool Obstacle::intersects(cocos2d::Rect rect)
{
    for (auto sprite : _spriteList) {
        if (sprite->getBoundingBox().intersectsRect(rect)) {
            return true;
        }
    }
    return false;
}