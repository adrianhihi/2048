//
//  GameOver.cpp
//  Game2048
//
//  Created by ZhaoLei on 2/7/15.
//
//

#include "GameOver.h"
#include "gameDefine.h"
#include "GameScene.h"
Scene * GameOver::createScene(){
    auto scene= Scene::create();
    auto layer = GameOver::create();
    scene->addChild(layer);
    return scene;
};
bool GameOver::init(){
    if (!Layer::init()) {
        return false;
    }
    //display
    auto labelGame = Label::createWithBMFont("fonts/futura-48.fnt", "Game Over");
    labelGame->setPosition(Point(GAME_SCREEN_WIDTH/2, GAME_SCREEN_HEIGHT/2));
    labelGame->setScale(1.5);
    this->addChild(labelGame);
    
    //restart
     auto label = Label::createWithBMFont("fonts/futura-48.fnt", "Restart Game");
    auto labelItem=MenuItemLabel::create(label, CC_CALLBACK_1(GameOver::menuCallBack, this));
    labelItem->setPosition(Point(GAME_SCREEN_WIDTH/2, GAME_SCREEN_HEIGHT/4));
    auto menu = Menu::create(labelItem, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu);
    return true;
};

void GameOver::menuCallBack(Ref * obj){
    auto scene =Game::createScene();
    Director::getInstance()->replaceScene(TransitionFadeDown::create(0.5, scene));
};