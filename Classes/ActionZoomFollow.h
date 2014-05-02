//
//  ActionZoomFollow.h
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 4/28/14.
//
//

#ifndef __TinyZodiacs__ActionZoomFollow__
#define __TinyZodiacs__ActionZoomFollow__

#include <iostream>
#include "cocos2d.h"

USING_NS_CC;

class ActionZoomFollow :
public CCAction
{
public:
    ActionZoomFollow(void);
    ~ActionZoomFollow(void);
    
    static ActionZoomFollow* create(CCNode* followed_node);
    bool init(CCNode* followed_node);
    virtual CCObject* copyWithZone(CCZone *pZone);
    virtual void step(float dt);
    virtual bool isDone(void);
    virtual void stop(void);
    virtual void startWithTarget(CCNode *target);
    
    void SetNodeToFollow(CCNode* followed_node);
    
private:
    CCNode* _followed_node;
    float  _old_scale;
    CCPoint _zoom_center;
    CCPoint _old_zoom_center;
};


#endif /* defined(__TinyZodiacs__ActionZoomFollow__) */
