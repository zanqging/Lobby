//
//  SceneManager.hpp
//  Doodler
//
//  Created by air on 16/1/30.
//
//

#ifndef SceneManager_hpp
#define SceneManager_hpp
#include "cocos2d.h"
#include "NetworkingWrapper.h"
class DrawingCanvas;
USING_NS_CC;
class SceneManager : public NetworkingDelegate {
    
    
public:
    static SceneManager * getInstance(); //单例
    DrawingCanvas * drawingCanvas; //画板
    
    void enterSoloGame(); //进入绘画状态
    void returnToLobby(); //返回主页
private:
    void receivedData(const void * data, unsigned long length) override;  //接受数据信息
    void stateChanged(ConnectionState state) override; //状态改变
    void loadDrawingScene(bool networked); //加载绘画场景(networked:网络状态)
    
    SceneManager();
    ~SceneManager();
};

#endif /* SceneManager_hpp */
