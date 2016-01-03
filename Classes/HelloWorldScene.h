#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::Layer
{
public:
//    static const float JUMP_UP;
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
  
    bool onTouchBegan(const std::vector<cocos2d::Touch*>& touch, cocos2d::Event* event);
};

#endif // __HELLOWORLD_SCENE_H__
