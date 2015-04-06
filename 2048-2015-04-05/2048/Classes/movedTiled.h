//
//  movedTiled.h
//  Game2048
//
//  Created by ZhaoLei on 2/6/15.
//
//

#ifndef __Game2048__movedTiled__
#define __Game2048__movedTiled__

#include <stdio.h>
#include "cocos2d.h"
#include "gameDefine.h"
USING_NS_CC;

class MovedTiled:public Node {
public:
    int m_row, m_col, m_number;
    void showAt(int r, int c);
    void moveTo(MOVE_DIR dir);
    CREATE_FUNC(MovedTiled);
    bool init();
    void doubleNumber();
};

#endif /* defined(__Game2048__movedTiled__) */
