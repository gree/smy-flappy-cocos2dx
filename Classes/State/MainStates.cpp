#include "Main.h"
#include "StateMachineMacros.h"
#include "GameScene.h"
#include "Player.h"

USING_NS_CC;
namespace flappySample {

// [state2cpp]__common__

std::string Main::DumpState() const { return TO_STRING(); }
void Main::ExecState() { EXEC(); }
void Main::StartState() {
    SPAWN(StateStart);
}

// [state2cpp]Start:653feed0affe4d551895e7fbeefa19373409fc97

void Main::StateStart() {
    _gameScene = GameScene::createWithPhysics();
    Director::getInstance()->runWithScene(_gameScene);
    SWITCH_TO(StateWaitStartGame);
}

// [state2cpp]WaitStartGame:1133078d4ec92c70d9ee72a630c56dd4e416f4d4

void Main::StateWaitStartGame() {
    if (_gameScene->getIsTap()) {// タップ
        _gameScene->setIsTap(false);
        _gameScene->start();
        
        SWITCH_TO(StateStartGame);
    }
}

// [state2cpp]StartGame:cef9bd675fa0cc09061b42c6da929cc088275e23

void Main::StateStartGame() {
    _gameScene->updateGame(_dt);
    if (_gameScene->getIsGameOver()) {// 障害物に衝突
        SWITCH_TO(StateGameOver);
    }
}

// [state2cpp]GameOver:b25fbce5f390846e1ee6730a72ee7fc9cb99cfaf

void Main::StateGameOver() {
    auto player = _gameScene->getPlayer();
    if (player->getPositionY() < 125.0f) {// GameOverアニメーション終了
        player->getPhysicsBody()->setEnabled(false);
        player->setPositionY(100.0f + player->getBoundingBox().size.height / 2);
        SWITCH_TO(StateWaitInitGame);
    }
}

// [state2cpp]WaitInitGame:801924da6276589bc7f5ed2e12319b9920b9665a

void Main::StateWaitInitGame() {
    if (_gameScene->getIsTap()) {// タップ
        _gameScene->initGame();
        _gameScene->setIsTap(false);
        SWITCH_TO(StateWaitStartGame);
    }
}

// [state2cpp]__end__
} // namespace flappySample
