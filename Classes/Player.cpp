//
//  Player.cpp
//  flapySample
//
//  Created by Nomura Takahisa on 2015/12/30.
//
//

#include "Player.h"

USING_NS_CC;

const float Player::JUMP_UP = 200.0f;

bool Player::init()
{
    if (!Sprite::init()) {
        return false;
    }
 
    Rect rect = Rect(0, 0, 25, 25);
    this->setTextureRect(rect);
    this->setColor(Color3B::WHITE);
  
    Size visibleSize = Director::getInstance()->getVisibleSize();
    this->setPosition(visibleSize.width / 4, visibleSize.height / 2);
  
    auto pb = PhysicsBody::createBox(Size(this->getContentSize().width, this->getContentSize().height));
    pb->setEnabled(true);
    pb->setMass(1.0f);
    pb->setVelocity(Vect(0,1));
    pb->setVelocityLimit(200.0);
    pb->setRotationEnable(false);
    pb->setAngularVelocityLimit(150.0f);
    this->setPhysicsBody(pb);
    return true;
}

void Player::jump()
{
  this->getPhysicsBody()->applyImpulse(Vect(0, JUMP_UP), Point(0, this->getContentSize().height*-1));
}