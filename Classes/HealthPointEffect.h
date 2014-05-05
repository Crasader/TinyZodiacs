//
//  HealthPointEffect.h
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 5/3/14.
//
//

#ifndef __TinyZodiacs__HealthPointEffect__
#define __TinyZodiacs__HealthPointEffect__

#include <iostream>
#include "cocos2d.h"
#include "GameEffect.h"
#include "DataCollector.h"

USING_NS_CC;

class HealthPointEffect: public GameEffect
{
private:
    float healthPoint;
    CCLabelTTF* label;
protected:
public:
    HealthPointEffect();
    virtual ~HealthPointEffect();
    
    virtual bool init();
    virtual void update(float dt);
    void run();
    void stop();
  
    void setHealthPoint(float hp);
    
    CREATE_FUNC(HealthPointEffect);
};




#endif /* defined(__TinyZodiacs__HealthPointEffect__) */
