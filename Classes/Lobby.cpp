//
//  Lobby.cpp
//  Doodler
//
//  Created by air on 16/1/29.
//
//

#include "Lobby.hpp"
#include "DrawingCanvas.hpp"
bool Lobby::init()
{
    if (Node::create()) {
        LayerColor * background = LayerColor::create(Color4B(255, 255, 255, 255));
        addChild(background);
        
        visibleSize = Director::getInstance()->getVisibleSize();
        originSize = Director::getInstance()->getVisibleOrigin();
        
        return true;
    }
    return false;
}

void Lobby::onEnter()
{
    Node::onEnter();
    
    //设置logo
    setupUI();
}

/**
 *  设置UI
 */
void Lobby::setupUI()
{
    //设置logo
    Sprite * logo = Sprite::create("doodlerLogo.png");
    logo->setAnchorPoint(Vec2(0.5f, 0.5f));
    logo->setPosition(Vec2(visibleSize.width/2 + originSize.x, visibleSize.height * 0.75f + originSize.y));
    addChild(logo);
    
    //开始游戏按钮
    ui::Button * soloButton = ui::Button::create();
    soloButton->setAnchorPoint(Vec2(0.5f, 0.5f));
    soloButton->setPosition(Vec2(visibleSize.width/2 + originSize.x, visibleSize.height * 0.4 + originSize.y));
    soloButton->loadTextures("soloButton.png", "soloButtonPressed.png");
    soloButton->addTouchEventListener(CC_CALLBACK_2(Lobby::soloPressed, this));
    addChild(soloButton);
    
    //多人对战
    ui::Button * duoButton = ui::Button::create();
    duoButton->setAnchorPoint(Vec2(0.5f,0.5f));
    duoButton->setPosition(Vec2(visibleSize.width/2 + originSize.x, visibleSize.height * 0.25 + originSize.y));
    duoButton->addTouchEventListener(CC_CALLBACK_2(Lobby::duoPressed, this));
    duoButton->loadTextures("duoButton.png", "duoButtonPressed.png");
    addChild(duoButton);
    
}


void Lobby::soloPressed(cocos2d::Ref *pSender, ui::Widget::TouchEventType eEventType){
    if (eEventType == ui::Widget::TouchEventType::ENDED) {
        Scene * scene = Scene::create();
        
        DrawingCanvas * drawingCanvas = DrawingCanvas::create();
        scene->addChild(drawingCanvas);
        
        Director::getInstance()->pushScene(scene);
    }
}

void Lobby::duoPressed(cocos2d::Ref *pSender, ui::Widget::TouchEventType eEventType)
{
    
}
