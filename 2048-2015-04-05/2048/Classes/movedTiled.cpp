//
//  movedTiled.cpp
//  Game2048
//
//  Created by ZhaoLei on 2/6/15.
//
//

#include "movedTiled.h"
#include <iostream>

void MovedTiled::showAt(int r, int c){
//    moveTo(r, c);
    this->m_row = r;
    this->m_col = c;
    this->setPosition(Point(GAME_TILED_WIDTH * c + GAME_TILED_BOARD_WIDTH * (c+1),
                            GAME_TILED_HEIGHT * r + GAME_TILED_BOARD_WIDTH * (r + 1)));
    //
    auto bk = this->getChildByTag(110);
    bk->runAction(Sequence::create(ScaleTo::create(0.1, 0.9),ScaleTo::create(0.1, 1.0),NULL));
    
};
void MovedTiled::moveTo(MOVE_DIR dir){
//    this->m_row = r;
//    this->m_col = c;
//    this->setPosition(Point(GAME_TILED_WIDTH * c + GAME_TILED_BOARD_WIDTH * (c+1),
//                            GAME_TILED_HEIGHT * r + GAME_TILED_BOARD_WIDTH * (r + 1)));
    switch (dir) {
        case UP:
            this->runAction(MoveBy::create(0.1, Point(0,GAME_TILED_HEIGHT * 1 + GAME_TILED_BOARD_WIDTH * (1))));
            break;
            
        case DOWN:
            this->runAction(MoveBy::create(0.1, Point(0, -GAME_TILED_HEIGHT * 1 - GAME_TILED_BOARD_WIDTH * (1))));
            break;
            
        case LEFT:
            this->runAction(MoveBy::create(0.1, Point( - GAME_TILED_WIDTH * 1 - GAME_TILED_BOARD_WIDTH * 1,0)));
            break;
            
        case RIGHT:
            this->runAction(MoveBy::create(0.1, Point(GAME_TILED_WIDTH * 1 + GAME_TILED_BOARD_WIDTH * 1,0)));
            break;
            
        default:
            break;
    }
    
};

bool MovedTiled::init(){
    
    //background
    auto bk = LayerColor::create(Color4B(200, 200, 200, 255), GAME_TILED_WIDTH, GAME_TILED_HEIGHT);
    this->addChild(bk);
    bk->setTag(110);
    //number
    int n = random(0, 9);
    this->m_number = n > 0?2:4;
    auto label = Label::createWithSystemFont(StringUtils::format("%d", this->m_number), "宋体", 80);
    switch (this->m_number) {
        case 2:
            bk->setColor(Color3B(230,220,210));
        case 4:
            bk->setColor(Color3B(230,210,190));
            break;
    }
    label->setTag(10);
    label->setColor(Color3B::BLACK);
    bk->addChild(label);
    label->setPosition(Point(GAME_TILED_WIDTH/2, GAME_TILED_HEIGHT/2));
    
    return true;
};

void MovedTiled::doubleNumber(){
    this->m_number = m_number*2;
    auto bk = this->getChildByTag(110);
    auto label = (Label *) bk->getChildByTag(10);
    label->setString(StringUtils::format("%d", m_number));
    bk->runAction(Sequence::create(ScaleTo::create(0.1, 1.1),ScaleTo::create(0.1, 1.0),NULL));
    switch (this->m_number) {
        case 2:
            bk->setColor(Color3B(230,220,210));
            
        case 4:
            bk->setColor(Color3B(230,210,190));
            break;
        case 8:
            bk->setColor(Color3B(230,150,100));
            label->setColor(Color3B(255,255,255));
            break;
        case 16:
            bk->setColor(Color3B(230,120,80));
            label->setColor(Color3B(255,255,255));
            break;
        case 32:
            bk->setColor(Color3B(230,100,90));
            label->setColor(Color3B(255,255,255));
            break;
        case 64:
            bk->setColor(Color3B(230,70,60));
            label->setColor(Color3B(255,255,255));
            break;
        case 128:
            bk->setColor(Color3B(230,190,60));
            label->setColor(Color3B(255,255,255));
            break;
        case 256:
            bk->setColor(Color3B(230,190,60));
            label->setColor(Color3B(255,255,255));
            break;
        case 512:
            bk->setColor(Color3B(230,190,60));
            label->setColor(Color3B(255,255,255));
            break;
        case 1024:
        case 2048:
            label->setScale(0.5);
            bk->setColor(Color3B(210,180,30));
            label->setColor(Color3B(255,255,255));
    }
};