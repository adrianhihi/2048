//
//  GameOver.h
//  Game2048
//
//  Created by ZhaoLei on 2/7/15.
//
//

#ifndef __Game2048__GameOver__
#define __Game2048__GameOver__

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;
class GameOver: Layer{
public:
    static Scene * createScene();
    bool init();
    CREATE_FUNC(GameOver);
    void menuCallBack(Ref * obj);
};

#endif /* defined(__Game2048__GameOver__) */
