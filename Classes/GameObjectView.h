//
//  GameObjectInfoView.h
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 3/29/14.
//
//

#ifndef __TinyZodiacs__GameObjectInfoView__
#define __TinyZodiacs__GameObjectInfoView__
class GameObjectView;
#include <iostream>
#include "cocos2d.h"
#include "HealthBar.h"
#include "GameObject.h"

USING_NS_CC;

class GameObjectView: public CCNode
{
private:
protected:
    GameObject* gameObject;

public:
    GameObjectView();
    virtual ~GameObjectView();
    
    virtual bool init();
    virtual void update(float dt);

    void attach(GameObject* gameObject);
    virtual void notifyChange() = 0;
};

#endif /* defined(__TinyZodiacs__GameObjectInfoView__) */
