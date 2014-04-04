//
//  GameObjectInfoView.h
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 3/29/14.
//
//

#ifndef __TinyZodiacs__GameObjectInfoView__
#define __TinyZodiacs__GameObjectInfoView__

#include <iostream>
#include "cocos2d.h"
#include "HealthBar.h"
#include "GameObject.h"

USING_NS_CC;

class GameObjectInfoView: public CCNode
{
private:
protected:
    GameObject* gameObject;
    HealthBar* healthBar;
    CCLabelTTF* textName;

public:
    GameObjectInfoView();
    virtual ~GameObjectInfoView();
    
    virtual bool init();
    virtual void update(float dt);
    
    void setHealthBar(HealthBar* healthBar);
    void setTextName(CCLabelTTF* textName);
    void attach(GameObject* gameObject);
    
    CREATE_FUNC(GameObjectInfoView);
};

#endif /* defined(__TinyZodiacs__GameObjectInfoView__) */
