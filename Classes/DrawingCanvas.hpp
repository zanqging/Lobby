//
//  DrawingCanvas.hpp
//  Doodler
//
//  Created by air on 16/1/29.
//
//

#ifndef DrawingCanvas_hpp
#define DrawingCanvas_hpp
#include "cocos2d.h"
#include "CocosGUI.h"
#include "Constants.h"
USING_NS_CC;
class DrawingCanvas : public cocos2d::Node {
    
private:
    Size visibleSize;
    Vec2 originSize;
public:
    CREATE_FUNC(DrawingCanvas);
    void setNetworkedSession(bool networkedSession);
    bool getNetworkedSession();
    
protected:
    cocos2d::DrawNode * drawNode;
    LayerColor * background;
    Sprite * check; //选中精灵
    Color4F  selecedColor; //当前选中颜色
    
    bool init() override; //初始化
    bool networkedSession; //网络会话状态
    void onEnter() override; //进入场景
    void setupTouchHandling(); //设置触摸事件
    void setupMenus(); //设置菜单
    void clearButtonPressed(Ref * rSender, ui::Widget::TouchEventType eEventTouchType); //清除
    void backButtonPressed(Ref * rSender, ui::Widget::TouchEventType eEventTouchType); //返回
    void colorChangePressed(Ref * rSender, ui::Widget::TouchEventType eEventTouchType); //选择颜色
    
    
    
};


#endif /* DrawingCanvas_hpp */
