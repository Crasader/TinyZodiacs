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

    void scheduleForSkill(AbstractSkill* object, float duration, int fuctionCall);
    void stopScheduledObjectAction(CCAction* target);
    
    CCAction* scheduleFunction(CCCallFunc* callFunction, CCCallFunc* endFunction, float duration, int repeatTime);
       static ScheduleManager* getInstance();
    void finishScheduleFunction(CCNode* sender, void* data);
    static void release();
     CCAction* scheduleFunctionForever(CCCallFunc* callFunction, CCCallFunc* endFunction, float duration);

    CCSequence* scheduleFuction(CCCallFunc* funcion, float duration);
    CCRepeat* scheduleFuctionRepeatly(CCCallFunc* funcion, float duration, int times);
};

#endif /* defined(__TinyZodiacs__ScheduleManager__) */
