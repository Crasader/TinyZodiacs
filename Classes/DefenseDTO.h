//
//  DefenseDTO.h
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 6/9/14.
//
//

#ifndef __TinyZodiacs__DefenseDTO__
#define __TinyZodiacs__DefenseDTO__

#include <iostream>
#include "cocos2d.h"

USING_NS_CC;
using namespace std;

class DefenseDTO: public CCObject
{
private:
protected:
public:
    DefenseDTO();
    ~DefenseDTO();
    
    virtual bool init();
    
    string id;
    string icon;
    int cost;
    
    
    CREATE_FUNC(DefenseDTO);
};

#endif /* defined(__TinyZodiacs__DefenseDTO__) */
