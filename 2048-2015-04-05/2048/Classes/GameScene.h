//
//  GameScene.h
//  Game2048
//
//  Created by ZhaoLei on 2/6/15.
//
//

#ifndef __Game2048__GameScene__
#define __Game2048__GameScene__

#include <stdio.h>
#include "cocos2d.h"
#include "gameDefine.h"
#include "movedTiled.h"
USING_NS_CC;
class Game:Layer{
private :
    bool m_startMove;
    int m_x, m_y;
    int score;
public:
    LayerColor * colorBack;
    MOVE_DIR m_dir;
    int map[GAME_ROWS][GAME_COLs];
    Vector<MovedTiled *> allTiled;
    static Scene * createScene();
    CREATE_FUNC(Game);
    bool init();
    void moveAllTiled(MOVE_DIR dir);
    void newMovedTiled();
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
    bool soundClear;
    
    void menuRestart(Ref * pSender);
};

#endif /* defined(__Game2048__GameScene__) */
