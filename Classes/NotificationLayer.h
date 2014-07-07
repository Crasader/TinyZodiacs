//
//  NotificationLayer.h
//  TinyZodiacs
//
//  Created by NhutVM on 7/4/14.
//
//

#ifndef __TinyZodiacs__NotificationLayer__
#define __TinyZodiacs__NotificationLayer__

#include <iostream>
#include "cocos2d.h"
#include "Controller.h"

USING_NS_CC;
class NotificationLayer: public CCLayer, public Controller
{
private:
protected:
public:
    NotificationLayer();
    ~NotificationLayer();
    
    bool init();
    
    CREATE_FUNC(NotificationLayer);
};
#endif /* defined(__TinyZodiacs__NotificationLayer__) */
