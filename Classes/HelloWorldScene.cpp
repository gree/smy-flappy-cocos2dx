#include "HelloWorldScene.h"

USING_NS_CC;


//const float HelloWorld::JUMP_UP = 200.0f;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    //auto scene = Scene::create();
    auto scene = Scene::createWithPhysics();
  
    Vect gravity;
    gravity.setPoint(0, -1);
//    scene->getPhysicsWorld()->setGravity(gravity);
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    scene->getPhysicsWorld()->setSpeed(5.0f);
 
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();
  
  
    // add layer as a child to scene
    scene->addChild(layer);
  
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    sprite->setScale(Director::getInstance()->getContentScaleFactor());

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
  
    Rect rect = Rect(0, 0, 50, 50);
    //白いスプライト
    auto player = Sprite::create();
    player->setTextureRect(rect);
    player->setColor(Color3B::WHITE);
  
    player->setPosition(50, 320);
  
    auto pb = PhysicsBody::createBox(Size(player->getContentSize().width, player->getContentSize().height));
//    auto pb = PhysicsBody::createBox(Size(sprite->getContentSize().width-30, sprite->getContentSize().height-10));
    pb->setEnabled(true);
    pb->setMass(1.0f);
    pb->setVelocity(Vect(0,1));
    pb->setVelocityLimit(200.0);
    pb->setRotationEnable(false);
    pb->setAngularVelocityLimit(150.0f);
//    player->setPosition(Point(228, 708));
    player->setPhysicsBody(pb);
//    sprite->setPhysicsBody(pb);
    addChild(player);
  
    auto taplistener = EventListenerTouchAllAtOnce::create();
    //taplistener->onTouchesBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
    taplistener->onTouchesBegan = [player, pb](const std::vector<Touch*>& touch, Event* event) {
//      pb->setEnabled(true);
//      player->getPhysicsBody()->applyImpulse(Vect(0, JUMP_UP), Point(0, player->getContentSize().height*-1));
    };
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(taplistener, this);
  
    return true;
}

bool HelloWorld::onTouchBegan(const std::vector<Touch*>& touch, Event* event) {
};


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
