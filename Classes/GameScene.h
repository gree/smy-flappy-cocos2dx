//
//  GameScene.h
//  flapySample
//
//  Created by Nomura Takahisa on 2015/12/30.
//
//
#pragma onece

class Player;
class Obstacle;

class GameScene : public cocos2d::Scene
{
public:
    static const float JUMP_UP;
    static GameScene* createWithPhysics();
    virtual bool initWithPhysics();

private:
    void update(float delta);
    void restart();
    void initObstacle();
    Player* _player = nullptr;
    int _score = 0;
    bool _isGmaeOver = false;
    cocos2d::Label* _statusLabel = nullptr;
    cocos2d::Label* _scoreLabel = nullptr;
    std::vector<Obstacle*> _obstacleList;
};