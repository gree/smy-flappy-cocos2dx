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
    gravity.setPoint(0, -50);
    this->getPhysicsWorld()->setGravity(gravity);
    this->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    this->getPhysicsWorld()->setSpeed(6.0f);
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    _statusLabel = Label::createWithSystemFont("Tap Start", "HiraKakuProN-W6", 24);
    _statusLabel->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - _statusLabel->getContentSize().height));
    this->addChild(_statusLabel, 3);
    
    _scoreLabel = Label::createWithSystemFont(std::to_string(_score), "HiraKakuProN-W6", 24);
    _scoreLabel->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - _statusLabel->getContentSize().height - 100));
    this->addChild(_scoreLabel, 3);

    _obstacleList = std::vector<Obstacle*>();
    
    auto ground = Sprite::create();
    Rect rect = Rect(0, 0, visibleSize.width, 100);
    ground->setTextureRect(rect);
    ground->setColor(Color3B::YELLOW);
    ground->setPosition(visibleSize.width / 2, 50);
    this->addChild(ground, 1);
    
    _player = Player::create();
    addChild(_player, 2);
    
    auto taplistener = EventListenerTouchAllAtOnce::create();
    taplistener->onTouchesBegan = [this](const std::vector<Touch*>& touch, Event* event) {
        this->_isTap = true;
    };
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(taplistener, this);
    
    this->initGame();
 
    return true;
}

void GameScene::initGame()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    _player->setPosition(visibleSize.width / 4, visibleSize.height / 2 + 100);
    for (auto obstacle : _obstacleList) {
        obstacle->removeFromParent();
    }
    _obstacleList.clear();
    for (auto i = 0; i < 5; ++i) {
        auto obstacle = Obstacle::create();
        obstacle->setSpritePosX(420 + (i * 300));
        _obstacleList.push_back(obstacle);
        this->addChild(obstacle, 1);
    }
    _statusLabel->setString("Tap Start");
    _score = 0;
    _scoreLabel->setString(std::to_string(_score));
    _isGameOver = false;
}

void GameScene::start()
{
    _player->getPhysicsBody()->setEnabled(true);
    _player->jump();
    _statusLabel->setVisible(false);
}

void GameScene::updateGame(float delta)
{
    if (_isTap) {
        _player->jump();
        _isTap = false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    for (auto it = _obstacleList.begin(); it != _obstacleList.end();) {
        auto obstacle = *it;
        auto x = obstacle->getSpritePosX();
        x -= delta * 150;
        obstacle->setSpritePosX(x);
        
        if (obstacle->intersects(_player->getBoundingBox()) ||
            _player->getPositionY() < (100.0f + _player->getBoundingBox().size.height / 2)) {
            auto rect = _player->getBoundingBox();
            _statusLabel->setString("Game Over");
            _statusLabel->setVisible(true);
            _isGameOver = true;
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