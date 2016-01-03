//
//  Obstacle.h
//  flapySample
//
//  Created by Nomura Takahisa on 2015/12/30.
//
//

class Obstacle : public cocos2d::Node
{
public:
    CREATE_FUNC(Obstacle);
    virtual bool init();
    bool intersects(cocos2d::Rect rect);
    void setSpritePosX(float x);
    CC_SYNTHESIZE_READONLY(float, _spritePosX, SpritePosX);
    CC_SYNTHESIZE(bool, _isPass, IsPass);
private:
    std::vector<cocos2d::Sprite*> _spriteList;
};
