//
//  Lobby.hpp
//  Doodler
//
//  Created by air on 16/1/29.
//
//

#ifndef Lobby_hpp
#define Lobby_hpp
#include "cocos2d.h"
#include "CocosGUI.h"
USING_NS_CC;
class Lobby :public cocos2d::Node {
    
private:
    Size visibleSize;
    Vec2 originSize;
public:
    CREATE_FUNC(Lobby);
protected:
    
    
    bool init() override;
    void onEnter() override;
    void setupUI();
    void soloPressed(Ref * pSender, ui::Widget::TouchEventType  eEventType);
    void duoPressed(Ref * pSender, ui::Widget::TouchEventType eEventType);
};

#endif /* Lobby_hpp */
