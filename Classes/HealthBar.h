//
//  HealthBar.h
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 3/28/14.
//
//

#ifndef __TinyZodiacs__HealthBar__
#define __TinyZodiacs__HealthBar__

#include <iostream>
#include "cocos2d.h"

USING_NS_CC;

class HealthBar : public CCNode
{
private:
    CCSprite* background;
    CCSprite* foreground;
protected:
  
public:
    HealthBar();
    virtual ~HealthBar();
    virtual bool init();
    
    void setBackground(const char* imageName);
    void setForeground(const char* imageName);
    
    void updateProgress(float max, float current);
    
    CREATE_FUNC(HealthBar);
};

#endif /* defined(__TinyZodiacs__HealthBar__) */
