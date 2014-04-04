//
//  HeroInfoView.h
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 3/29/14.
//
//

#ifndef __TinyZodiacs__HeroInfoView__
#define __TinyZodiacs__HeroInfoView__

#include <iostream>
#include "cocos2d.h"
#include "GameObjectInfoView.h"

USING_NS_CC;

class HeroInfoView: public GameObjectInfoView
{
private:
protected:
public:
    HeroInfoView();
    ~HeroInfoView();

    virtual bool init();
    virtual void update(float dt);
    
    virtual void attach(GameObject* gameObject);
    
    CREATE_FUNC(HeroInfoView);
};

#endif /* defined(__TinyZodiacs__HeroInfoView__) */
