//
//  SplashScene.h
//  Game2048
//
//  Created by ZhaoLei on 2/6/15.
//
//

#ifndef __Game2048__SplashScene__
#define __Game2048__SplashScene__

#include "cocos2d.h"
#include "gameDefine.h"
USING_NS_CC;

class Splash:Layer {
public:
    bool init();
    CREATE_FUNC(Splash);
    static Scene * createScene();
    void jumpToGame(float t);
};

#endif /* defined(__Game2048__SplashScene__) */
