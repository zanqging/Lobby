//
//  SceneManager.cpp
//  Doodler
//
//  Created by air on 16/1/30.
//
//

#include "SceneManager.hpp"
#include "DrawingCanvas.hpp"
static SceneManager * sharedSceneManager = nullptr;
/**
 *  单例工厂
 *
 *  @return 返回实例
 */
SceneManager* SceneManager::getInstance()
{

    if (!sharedSceneManager) {
        sharedSceneManager = new SceneManager();
    }
    return sharedSceneManager;
    
}

/**
 *  构造函数
 */
SceneManager::SceneManager()
{
    //设置初始化默认值
    drawingCanvas = nullptr;
    
}

/**
 *  释放，销毁
 */
SceneManager::~SceneManager()
{
    
}
/**
 *  进入绘画状态
 */
void SceneManager::enterSoloGame()
{
    this->loadDrawingScene(false); //以单人模式加载绘画场景
}
/**
 *  返回首页
 */
void SceneManager::returnToLobby()
{
    //检测当前绘画板是否为空
    if (drawingCanvas) {
        //告知导演：返回上一级 Lobby
        Director::getInstance()->popScene();
        //销毁绘画板
        drawingCanvas = nullptr;
    }
}

void SceneManager::loadDrawingScene(bool networked)
{
    //创建新场景
    Scene * scene = new Scene();
    //创建新绘画板
    drawingCanvas = DrawingCanvas::create();
    //设置网络会话状态
    drawingCanvas->setNetworkedSession(networked);
    
    //将绘画板添加到场景
    scene->addChild(scene);
    
    //切换场景
    Director::getInstance()->pushScene(scene);

    
}
