#pragma once
#include "StateMachine.h"
class GameScene;
namespace flappySample {

class Main {
public:
    Main();
    void update(float dt);

private:
   GameScene* _gameScene = nullptr;
   float _dt = .0f;
   
#include "MainStates.h"

};
} // namespace

