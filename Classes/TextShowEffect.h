//
//  TextShowEffect.h
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 5/29/14.
//
//

#ifndef __TinyZodiacs__TextShowEffect__
#define __TinyZodiacs__TextShowEffect__

#include <iostream>
#include "cocos2d.h"
#include "Effect.h"
#include "DataCollector.h"

USING_NS_CC;
using namespace std;

class TextShowEffect: public Effect
{
private:
    string content;
    CCLabelTTF* label;
protected:
public:
    TextShowEffect();
    virtual ~TextShowEffect();
    
    virtual bool init();
    virtual void update(float dt);
    void setContent(string content);
    void setLabelStyle(CCLabelTTF* label);
    void run();
    void stop();
    
    CREATE_FUNC(TextShowEffect);
};

#endif /* defined(__TinyZodiacs__TextShowEffect__) */
