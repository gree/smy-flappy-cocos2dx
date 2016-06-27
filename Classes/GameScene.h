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
    GameScene():_isTap(false), _statusLabel(nullptr), _scoreLabel(nullptr), _isGameOver(false), _player(nullptr){};
    virtual bool initWithPhysics();
    void initGame();
    void start();
    CC_SYNTHESIZE(bool, _isTap, IsTap);
    CC_SYNTHESIZE_READONLY(cocos2d::Label*, _statusLabel, StatusLabel);
    CC_SYNTHESIZE_READONLY(cocos2d::Label*, _scoreLabel, ScoreLabel);
    CC_SYNTHESIZE_READONLY(bool, _isGameOver, IsGameOver);
    CC_SYNTHESIZE_READONLY(Player*, _player, Player);
    void updateGame(float delta);
private:
    int _score = 0;
    std::vector<Obstacle*> _obstacleList;
};