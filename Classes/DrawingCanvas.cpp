//
//  DrawingCanvas.cpp
//  Doodler
//
//  Created by air on 16/1/29.
//
//

#include "DrawingCanvas.hpp"
using namespace cocos2d;

bool DrawingCanvas::init()
{
    if (Node::init()) {
        //获取屏幕可视内容区域大小
        visibleSize = Director::getInstance()->getVisibleSize();
        originSize = Director::getInstance()->getVisibleOrigin();
        
        //添加颜色层
        background = LayerColor::create(Color4B(COLOR_WHITE));
        
        //添加到节点
        addChild(background);
        //初始化drawNode
        drawNode = DrawNode::create();
        
        //添加到节点
        addChild(drawNode);
        
        //设置默认选中颜色
        selecedColor = COLOR_GREEN;
        return true;
    }
    return false;
}

void DrawingCanvas::onEnter()
{
    Node::onEnter();
    setContentSize(visibleSize);
    drawNode->setContentSize(visibleSize);
    
    //添加菜单
    setupMenus();
    //添加手势监听事件
    setupTouchHandling();
}

void DrawingCanvas::setupTouchHandling()
{
    //记录开始触摸位置
    static Vec2 lastTouchPos;
    static float lastRadius = INITIAL_RADIUS;
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = [&](Touch * touch , Event * event){
        lastTouchPos = drawNode->convertTouchToNodeSpace(touch);
        lastRadius = INITIAL_RADIUS;  //初始化
        return true;
    };
    
    touchListener->onTouchMoved = [&](Touch * touch, Event * event){
        Vec2 touchPos = drawNode->convertTouchToNodeSpace(touch);
        float distance = lastTouchPos.distance(touchPos);  //计算两点之间距离
        
        float dt = 1.0f / 60.0f;
        float rc = 1.0f;
        float alpha = dt / (rc + dt);
        float radius = (alpha * distance) + (1.0f - alpha) * lastRadius;
        drawNode->drawSegment(lastTouchPos, touchPos, radius, selecedColor);
        lastRadius = radius; //重新设置半径
        lastTouchPos = touchPos; //重新设置最后触摸点
        
    };
    
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
    
}

void DrawingCanvas::setupMenus()
{
    //清除按钮
    ui::Button * clearButton = ui::Button::create();
    clearButton->setAnchorPoint(Vec2(0.5f,0.5f));
    clearButton->setPosition(Vec2(visibleSize.width-20 + originSize.x, visibleSize.height - 20+ originSize.y));
    clearButton->loadTextures("clearButton.png", "clearButtonPressed.png");
    clearButton->addTouchEventListener(CC_CALLBACK_2(DrawingCanvas::clearButtonPressed, this));
    addChild(clearButton);
    
    //返回按钮
    ui::Button * backButton = ui::Button::create();
    backButton->setAnchorPoint(Vec2(0.5f,0.5f));
    backButton->setPosition(Vec2(20+ originSize.x, visibleSize.height - 20+ originSize.y));
    backButton->loadTextures("backButton.png", "backButtonPressed.png");
    backButton->addTouchEventListener(CC_CALLBACK_2(DrawingCanvas::backButtonPressed, this));
    addChild(backButton);
    
    //选中图标精灵
    check = Sprite::create("checkMark.png");
    check->setAnchorPoint(Vec2(0.5f, 0.5f));
    check->setNormalizedPosition(Vec2(0.5f, 0.5f));
    
    //颜色控制节点
    Node * colorButtonLayout = Node::create();
    colorButtonLayout->setAnchorPoint(Vec2(0.5f, 0.0f));
    colorButtonLayout->setContentSize(Size(visibleSize.width, visibleSize.height * 0.2f));
    colorButtonLayout->setPosition(Vec2(visibleSize.width / 2.0f + originSize.x, 0.0f + originSize.y));
    addChild(colorButtonLayout);
    
    //添加五组颜色选择
    for (int i = 1; i<=5; i++) {
        ui::Button * colorButton = ui::Button::create();
        colorButton->setColor(Color3B(COLOR_BLUE));
        colorButton->setAnchorPoint(Vec2(0.5f, 0.0f));
        colorButton->loadTextures("colorSwatch.png", "colorSwatch.png");
        colorButton->setPosition(Vec2(visibleSize.width * i * (1.0f/6.0f), 0.0f));
        colorButton->addTouchEventListener(CC_CALLBACK_2(DrawingCanvas::colorChangePressed, this));
        
        switch (i) {
            case 0:
                colorButton->setColor(Color3B(COLOR_RED));
                break;
            case 1:
                colorButton->setColor(Color3B(COLOR_YELLOW));
                break;
            case 2:
                colorButton->setColor(Color3B(COLOR_GREEN));
                colorButton->addChild(check); //默认选中绿色
                break;
            case 3:
                colorButton->setColor(Color3B(COLOR_BLUE));
                break;
            case 4:
                colorButton->setColor(Color3B(COLOR_PURPLE));
                break;
            default:
                colorButton->setColor(Color3B(COLOR_RED));
                break;
        }
        //添加到颜色控制器中
        colorButtonLayout->addChild(colorButton);
        
    }
    
}
/**
 *  清除事件
 *
 *  @param rSender         实例对象
 *  @param eEventTouchType 事件类型
 */
void DrawingCanvas::clearButtonPressed(cocos2d::Ref *rSender, ui::Widget::TouchEventType eEventTouchType)
{
    drawNode->clear();
}

/**
 *  返回事件
 *
 *  @param rSender         实例对象
 *  @param eEventTouchType 事件类型
 */
void DrawingCanvas::backButtonPressed(cocos2d::Ref *rSender, ui::Widget::TouchEventType eEventTouchType){
    Director::getInstance()->popScene();
}

/**
 *  选择颜色事件
 *
 *  @param rSender         实例对象
 *  @param eEventTouchType 事件类型
 */
void DrawingCanvas::colorChangePressed(cocos2d::Ref *rSender, ui::Widget::TouchEventType eEventTouchType){
    ui::Button* pressedButton = static_cast<ui::Button*>(rSender);
    if (eEventTouchType == ui::Widget::TouchEventType::ENDED) {
        selecedColor = Color4F(pressedButton->getColor());
        
        //当前选中
        check->retain();
        check->removeFromParent();
        pressedButton->addChild(check);
        check->release();
        
    }
}

/**
 *  设置绘画板网络会话状态
 *
 *  @param networked 是否接入网络
 */
void DrawingCanvas::setNetworkedSession(bool networkedSession)
{
    this->networkedSession = networkedSession;
}

/**
 *  获取当前网络状态
 *
 *  @return 网络状态
 */
bool DrawingCanvas::getNetworkedSession()
{
    return this->networkedSession;
}
