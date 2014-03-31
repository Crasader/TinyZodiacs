//
//  ScheduleManager.h
//  TinyZodiacs
//
//  Created by Nhut on 3/26/14.
//
//

#ifndef __TinyZodiacs__ScheduleManager__
#define __TinyZodiacs__ScheduleManager__

#include <iostream>
#include "cocos2d.h"
#include "GameObject.h"
#include "AbstractSkill.h"


USING_NS_CC;
class ScheduleManager: public CCNode
{
private:
protected:
    ScheduleManager();
    ~ScheduleManager();
public:
    void scheduleForGameObject(GameObject* object, float duration);
    void scheduleForSkill(AbstractSkill* object, float duration, int fuctionCall);

    static ScheduleManager* getInstance();
    static void release();

};
#endif /* defined(__TinyZodiacs__ScheduleManager__) */
