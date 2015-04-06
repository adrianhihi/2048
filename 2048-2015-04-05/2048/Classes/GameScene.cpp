//
//  GameScene.cpp
//  Game2048
//
//  Created by ZhaoLei on 2/6/15.
//
//

#include "GameScene.h"
#include <iostream>
#include <SimpleAudioEngine.h>
#include "GameOver.h"
using namespace CocosDenshion;
Scene * Game::createScene() {
    auto scene = Scene::create();
    auto layer = Game::create();
    scene->addChild(layer);
    return scene;
};

bool Game::init(){
    if (!Layer::init()) {
        return false;
    }
    
    auto labelGame = Label::createWithBMFont("fonts/futura-48.fnt", "2048");
    labelGame->setPosition(Point(labelGame->getContentSize().width/2, GAME_SCREEN_HEIGHT - labelGame->getContentSize().height/2));

    this->addChild(labelGame);
    
    auto labelRestart = Label::createWithBMFont("fonts/futura-48.fnt", "Restart");
    auto restartItem = MenuItemLabel::create(labelRestart, CC_CALLBACK_1(Game::menuRestart, this));
    restartItem->setScale(1.3);
    auto menu = Menu::create(restartItem, NULL);
    menu->setPosition(Point(Director::getInstance()->getWinSize().width/2, 150));
    this->addChild(menu);
    
    //net
     colorBack = LayerColor::create(Color4B(170, 170, 170, 255), GAME_TILED_WIDTH * GAME_COLs + GAME_TILED_BOARD_WIDTH * (GAME_COLs + 1), GAME_TILED_HEIGHT * GAME_ROWS + GAME_TILED_BOARD_WIDTH * (GAME_ROWS + 1));
    colorBack->ignoreAnchorPointForPosition(false);
    colorBack->setPosition(Point(GAME_SCREEN_WIDTH/2, GAME_SCREEN_HEIGHT/2));
    this->addChild(colorBack);
    //score
    score = 0;
    auto labelScore = Label::createWithBMFont("fonts/futura-48.fnt", "Score: 0");
    labelScore->setPosition(Point(GAME_SCREEN_WIDTH/2, GAME_SCREEN_HEIGHT - labelGame->getContentSize().height/2));
    this->addChild(labelScore);
    labelScore->setTag(120);
    
    //elements
    for (int row = 0; row < GAME_ROWS; row++) {
        for (int col = 0; col < GAME_COLs; col ++) {
            auto layerTiled = LayerColor::create(Color4B(70, 70, 70, 255), GAME_TILED_WIDTH, GAME_TILED_HEIGHT);
            layerTiled->setPosition(Point(GAME_TILED_WIDTH * col + GAME_TILED_BOARD_WIDTH * (col + 1), GAME_TILED_HEIGHT * (row) + GAME_TILED_BOARD_WIDTH * (row + 1)));
            colorBack->addChild(layerTiled);
        }
    }
    //initial net
    for (int i = 0; i<GAME_ROWS; i++) {
        for (int j = 0; j<GAME_COLs; j++) {
            map[i][j] = 0;
        }
    }
    
    
    //initial number
    newMovedTiled();
    
    //touch
    auto event = EventListenerTouchOneByOne::create();
    event->onTouchBegan = [&](Touch * t, Event* e) {
        m_x = t->getLocation().x;
        m_y = t->getLocation().y;
        m_startMove = true;
        return true;
    };
    
    event->onTouchMoved = [&](Touch * t, Event * e) {
        int x = t->getLocation().x;
        int y = t->getLocation().y;
//        std::cout<<"m_y - y is: " << m_y -y <<std::endl;
//        std::cout<<"m_x - x is: " << m_x -x <<std::endl;
//        std::cout << "m_start is" << m_startMove<<std::endl;
        if (m_startMove && (abs(m_x-x) >30 || abs(m_y-y) > 30)) {
            m_startMove = false;
            MOVE_DIR dir;
            if (abs(m_x - x) > abs(m_y - y)) {
                if (m_x < x) {
                    dir = RIGHT;
                } else{
                    dir = LEFT;
                }
            }
            else{
                if (m_y < y) {
                    dir = UP;
                }
                else {
                    dir = DOWN;
                }
                
            }
            moveAllTiled(dir);
        }
    };
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(event, this);
    return true;
};


void Game::moveAllTiled(MOVE_DIR dir){
    soundClear = false;
    //
    switch (dir) {
        case DOWN:
            moveDown();
            break;
            
        case UP:
            moveUp();
            break;
            
        case LEFT:
            moveLeft();
            break;
            
        case RIGHT:
            moveRight();
            break;
            
        default:
            break;
    }
    //audio
    if (soundClear) {
        SimpleAudioEngine::getInstance()->playEffect("moveClear.wav");
    }
    else{
       SimpleAudioEngine::getInstance()->playEffect("move1.wav"); 
    }
    
    //score
    auto labelScore = (Label *)this->getChildByTag(120);
    labelScore->setString(StringUtils::format("score: %d", score));
    //game over
    
    //new part generate
    newMovedTiled();
};

void Game::newMovedTiled() {
    auto tiled = MovedTiled::create();
    int freeCount = 16 - allTiled.size();
    int num = random(0, freeCount-1);
    int count = -1;
    int row = 0, col = 0;
    bool find = false;
    for (; row < GAME_ROWS; row++) {
        for (col = 0; col < GAME_COLs; col++) {
            if (map[row][col] == 0) {
                count ++;
                if (count == num) {
                    find = true;
                    break;
                }
            }
        }
        if (find) {
            break;
        }
    }
    if (freeCount !=0) {
        tiled->showAt(row, col);
        colorBack->addChild(tiled);
        allTiled.pushBack(tiled);
        map[row][col] = allTiled.getIndex(tiled) + 1;
    }

    if (freeCount == 1) {
        for (int r=0; r<GAME_ROWS; r++) {
            for (int c=0; c<GAME_COLs; c++) {
                int num = allTiled.at(map[r][c] -1)->m_number;
                int objNum = 0;
                if (r + 1 < GAME_ROWS) {
                    objNum = allTiled.at(map[r+1][c]-1)->m_number;
                    if (num==objNum) {
                        return;
                    }
                }
                if (r-1>=0) {
                    objNum = allTiled.at(map[r-1][c]-1)->m_number;
                    if (num==objNum) {
                        return;
                    }
                }
                if (c+1<GAME_COLs) {
                    objNum = allTiled.at(map[r][c+1]-1)->m_number;
                    if (num==objNum) {
                        return;
                    }
                }
                if (c-1>=0) {
                    objNum = allTiled.at(map[r][c-1]-1)->m_number;
                    if (num==objNum) {
                        return;
                    }
                }
            }
        }
        
        auto scene =GameOver::createScene();
        Director::getInstance()->replaceScene(TransitionFadeDown::create(0.5, scene));
        return;
    }
};
void Game::moveUp() {
    for (int col = 0; col < GAME_COLs; col++) {
        for (int row = GAME_ROWS - 1; row >= 0; row--) {
            if (map[row][col] > 0) {
                for (int row_temp = row; row_temp < GAME_ROWS - 1; row_temp++) {
                    if (map[row_temp + 1][col] == 0) {
                        map[row_temp+1][col] = map[row_temp][col];
                        map[row_temp][col] = 0;
                        allTiled.at(map[row_temp+1][col] - 1)->moveTo(UP);
                    }
                    else {
                        int numObj = allTiled.at(map[row_temp + 1][col] - 1)->m_number;
                        int numNow = allTiled.at(map[row_temp][col] - 1)->m_number;
                        if (numNow == numObj) {
                            soundClear = true;
                            score += numNow*2;
                            allTiled.at(map[row_temp + 1][col] -1)->doubleNumber();
                            allTiled.at(map[row_temp][col] -1)->runAction(Sequence::create(MoveBy::create(0.1,Point ::ZERO), RemoveSelf::create(),NULL));
                            int index = map[row_temp][col];
                            allTiled.erase(map[row_temp][col]-1);
                            map[row_temp][col] = 0;
                            for (int r=0; r<GAME_ROWS ; r++) {
                                for (int c=0; c<GAME_COLs; c++) {
                                    if (map[r][c] > index) {
                                        map[r][c]--;
                                    }
                                }
                            }
                        }
                        break;
                    }
                }
            }
        }
    }
    
    
};
void Game::moveDown() {
    for (int col = 0; col < GAME_COLs; col++) {
        for (int row = 0; row < GAME_ROWS; row++) {
            if (map[row][col] > 0) {
                for (int row_temp = row; row_temp > 0; row_temp--) {
                    if (map[row_temp - 1][col] == 0) {
                        map[row_temp-1][col] = map[row_temp][col];
                        map[row_temp][col] = 0;
                        allTiled.at(map[row_temp-1][col] - 1)->moveTo(DOWN);
                    }
                    else {
                        int numObj = allTiled.at(map[row_temp - 1][col] - 1)->m_number;
                        int numNow = allTiled.at(map[row_temp][col] - 1)->m_number;
                        if (numNow == numObj) {
                            soundClear = true;
                            score += numNow*2;
                            allTiled.at(map[row_temp - 1][col] -1)->doubleNumber();
                            allTiled.at(map[row_temp][col] -1)->runAction(Sequence::create(MoveBy::create(0.1,Point ::ZERO), RemoveSelf::create(),NULL));
                            int index = map[row_temp][col];
                            allTiled.erase(map[row_temp][col]-1);
                            map[row_temp][col] = 0;
                            for (int r=0; r<GAME_ROWS ; r++) {
                                for (int c=0; c<GAME_COLs; c++) {
                                    if (map[r][c] > index) {
                                        map[r][c]--;
                                    }
                                }
                            }
                        }
                        break;
                    }
                }
            }
        }
    }
    
};
void Game::moveLeft() {
    for (int row = 0; row < GAME_ROWS; row++) {
        for (int col = 0; col < GAME_COLs; col++) {
            if (map[row][col] > 0) {
                for (int col_temp = col; col_temp > 0; col_temp--) {
                    if (map[row][col_temp-1] == 0) {
                        map[row][col_temp-1] = map[row][col_temp];
                        map[row][col_temp] = 0;
                        allTiled.at(map[row][col_temp-1] - 1)->moveTo(LEFT);
                    }
                    else {
                        int numObj = allTiled.at(map[row][col_temp-1] - 1)->m_number;
                        int numNow = allTiled.at(map[row][col_temp] - 1)->m_number;
                        if (numNow == numObj) {
                            soundClear = true;
                            score += numNow*2;
                            allTiled.at(map[row][col_temp-1] -1)->doubleNumber();
                            allTiled.at(map[row][col_temp] -1)->runAction(Sequence::create(MoveBy::create(0.1,Point ::ZERO), RemoveSelf::create(),NULL));
                            int index = map[row][col_temp];
                            allTiled.erase(map[row][col_temp]-1);
                            map[row][col_temp] = 0;
                            for (int r=0; r<GAME_ROWS ; r++) {
                                for (int c=0; c<GAME_COLs; c++) {
                                    if (map[r][c] > index) {
                                        map[r][c]--;
                                    }
                                }
                            }
                        }
                        break;
                    }
                }
            }
        }
    }
    
};
void Game::moveRight() {
    for (int row = 0; row < GAME_ROWS; row++) {
        for (int col = GAME_COLs -1; col >= 0; col--) {
            if (map[row][col] > 0) {
                for (int col_temp = col; col_temp < GAME_COLs-1; col_temp++) {
                    if (map[row][col_temp+1] == 0) {
                        map[row][col_temp+1] = map[row][col_temp];
                        map[row][col_temp] = 0;
                        allTiled.at(map[row][col_temp+1] - 1)->moveTo(RIGHT);
                    }
                    else {
                        int numObj = allTiled.at(map[row][col_temp+1] - 1)->m_number;
                        int numNow = allTiled.at(map[row][col_temp] - 1)->m_number;
                        if (numNow == numObj) {
                            soundClear = true;
                            score += numNow*2;
                            allTiled.at(map[row][col_temp+1] -1)->doubleNumber();
                            allTiled.at(map[row][col_temp] -1)->runAction(Sequence::create(MoveBy::create(0.1,Point ::ZERO), RemoveSelf::create(),NULL));
                            int index = map[row][col_temp];
                            allTiled.erase(map[row][col_temp]-1);
                            map[row][col_temp] = 0;
                            for (int r=0; r<GAME_ROWS ; r++) {
                                for (int c=0; c<GAME_COLs; c++) {
                                    if (map[r][c] > index) {
                                        map[r][c]--;
                                    }
                                }
                            }
                        }
                        break;
                    }
                }
            }
        }
    }
    
};

void Game::menuRestart(Ref * pSender) {
    Director::getInstance()->replaceScene(Game::createScene());
}