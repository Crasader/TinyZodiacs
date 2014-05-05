//
//  ContainerItem.h
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 5/3/14.
//
//

#ifndef __TinyZodiacs__ContainerItem__
#define __TinyZodiacs__ContainerItem__

#include <iostream>
#include "cocos2d.h"
#include "GameObject.h"

USING_NS_CC;

class ContainerItem: public GameObject
{
private:
protected:
    
public:
    ContainerItem();
    virtual ~ContainerItem();
    
    virtual bool init();
    
    CREATE_FUNC(ContainerItem);
};


#endif /* defined(__TinyZodiacs__ContainerItem__) */
