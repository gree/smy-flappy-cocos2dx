//
//  GameScene.cpp
//  flapySample
//
//  Created by Nomura Takahisa on 2015/12/30.
//
//

#include "GameScene.h"
#include "Player.h"
#include "Obstacle.h"

USING_NS_CC;

GameScene* GameScene::createWithPhysics()
{
    GameScene *ret = new (std::nothrow) GameScene();
    if (ret && ret->initWithPhysics()) {
        ret->autorelease();
        return ret;
    } else {
        CC_SAFE_DELETE(ret);
        return nullptr;
    }
}

bool GameScene::initWithPhysics()
{
    if (!Scene::initWithPhysics()) {
        return false;
    }
  
    Vect gravity;
    gravity.setPoint(0, -1);
    this->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    this->getPhysicsWorld()->setSpeed(5.0f);
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    _statusLabel = Label::createWithTTF("Tap Start", "fonts/Marker Felt.ttf", 24);
    _statusLabel->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - _statusLabel->getContentSize().height));
    this->addChild(_statusLabel, 1);
    
    _scoreLabel = Label::createWithTTF("0", "fonts/Marker Felt.ttf", 24);
    _scoreLabel->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - _statusLabel->getContentSize().height - 100));
    this->addChild(_scoreLabel, 1);

    _player = Player::create();
    addChild(_player);
    
    initObstacle();

    auto taplistener = EventListenerTouchAllAtOnce::create();
    taplistener->onTouchesBegan = [this](const std::vector<Touch*>& touch, Event* event) {
        if (this->_isGmaeOver) {
            if (this->_player->getPositionY() < 0) {
                this->restart();
            }
        } else {
            this->_player->jump();
        }
    };
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(taplistener, this);
 
    this->scheduleUpdate();
    return true;
}

void GameScene::initObstacle()
{
    _obstacleList = std::vector<Obstacle*>();
    for (auto i = 0; i < 5; ++i) {
        auto obstacle = Obstacle::create();
        obstacle->setSpritePosX(420 + (i * 300));
        _obstacleList.push_back(obstacle);
        this->addChild(obstacle);
    }
}

void GameScene::restart()
{
    _isGmaeOver = false;
    Size visibleSize = Director::getInstance()->getVisibleSize();
    _player->setPosition(visibleSize.width / 4, visibleSize.height / 2);
    for (auto obstacle : _obstacleList) {
        obstacle->removeFromParent();
    }
    initObstacle();
}

void GameScene::update(float delta)
{
    if (_isGmaeOver) {
        return;
    }
    Size visibleSize = Director::getInstance()->getVisibleSize();
    for (auto it = _obstacleList.begin(); it != _obstacleList.end();) {
        auto obstacle = *it;
        auto x = obstacle->getSpritePosX();
        x -= delta * 150;
        obstacle->setSpritePosX(x);
        
        if (obstacle->intersects(_player->getBoundingBox())) {
            auto rect = _player->getBoundingBox();
            _statusLabel->setString("Game Over");
            _isGmaeOver = true;
        }
        if (x < visibleSize.width / 4 && !obstacle->getIsPass()) {
            obstacle->setIsPass(true);
            _score++;
            _scoreLabel->setString(std::to_string(_score));
        }
        if (x < -100) {
            auto endIt = _obstacleList.rbegin();
            auto endObstacle = *endIt;
            auto newObstacle = Obstacle::create();
            newObstacle->setSpritePosX(endObstacle->getSpritePosX() + 300);
            this->addChild(newObstacle);
            _obstacleList.push_back(newObstacle);
            
            obstacle->removeFromParent();
            it = _obstacleList.erase(it);
        } else {
            it++;
        }
    }
}