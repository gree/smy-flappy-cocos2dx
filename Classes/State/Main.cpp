#include "Main.h"

USING_NS_CC;
using namespace flappySample;

Main::Main() {
    StartState();
}

void Main::update(float dt) {
    _dt = dt;
    ExecState();
}

