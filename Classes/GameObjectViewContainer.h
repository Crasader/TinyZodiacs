//
//  GameObjectViewContainer.h
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 5/15/14.
//
//

#ifndef __TinyZodiacs__GameObjectViewContainer__
#define __TinyZodiacs__GameObjectViewContainer__

#include <iostream>
#include "cocos2d.h"
#include "GameObjectView.h"

USING_NS_CC;

class GameObjectViewContainer: public GameObjectView
{
private:
protected:
    CC_SYNTHESIZE(CCArray*, listGameObjectView, ListGameObjectView);
public:
    GameObjectViewContainer();
    ~GameObjectViewContainer();
    
    virtual void update(float dt);
    virtual bool init();
    
    void addGameObjectView(GameObjectView* gameObjectView);
    void removeGameObjectView(GameObjectView* gameObjectView);
    
    virtual void notifyChange();
    
    CREATE_FUNC(GameObjectViewContainer);
};
#endif /* defined(__TinyZodiacs__GameObjectViewContainer__) */
