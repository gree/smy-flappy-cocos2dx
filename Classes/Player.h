//
//  Player.h
//  flapySample
//
//  Created by Nomura Takahisa on 2015/12/30.
//
//

#pragma once

class Player : public cocos2d::Sprite
{
public:
    static const float JUMP_UP;
    CREATE_FUNC(Player);
    virtual bool init();
    void jump();
    void start();
};
