

#include "SplashScene.h"
#include "GameScene.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

bool Splash::init() {
    if (!Layer::init()) {
        return false;
    }
    
    auto labelGame = Label::createWithBMFont("fonts/futura-48.fnt", "2048");
    labelGame->setPosition(Point(GAME_SCREEN_WIDTH/2, GAME_SCREEN_HEIGHT/2));
    labelGame->setScale(1.5);
    this->addChild(labelGame);
    
    auto labelGameVec = Label::createWithBMFont("fonts/futura-48.fnt", "Adrian Bai");
    labelGameVec->setPosition(Point(GAME_SCREEN_WIDTH/2, GAME_SCREEN_HEIGHT/4));
    labelGameVec->setScale(0.8);
    this->addChild(labelGameVec);
    
    this->scheduleOnce(schedule_selector(Splash::jumpToGame), 1);
    return true;
};

Scene * Splash::createScene() {
    auto scene = Scene::create();
    auto layer = Splash::create();
    scene->addChild(layer);
    return scene;
};

void Splash::jumpToGame(float t) {
    SimpleAudioEngine::getInstance()->preloadEffect("move1.wav");
    SimpleAudioEngine::getInstance()->preloadEffect("moveClear.wav");
    auto scene = Game::createScene();
    Director::getInstance()->replaceScene(TransitionProgressOutIn::create(0.5, scene));
};