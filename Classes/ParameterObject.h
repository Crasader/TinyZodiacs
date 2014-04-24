//
//  ParameterObject.h
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 4/18/14.
//
//

#ifndef __TinyZodiacs__ParameterObject__
#define __TinyZodiacs__ParameterObject__

#include <iostream>
#include "cocos2d.h"

USING_NS_CC;

class ParameterObject: public CCObject {
   

public:
    
    bool canDelete;
    bool isCCObject;
    void* data;
    std::string className;
    void deleteData(void* data);
    
    ParameterObject();
    virtual ~ParameterObject();
    virtual bool init();
    void setData(bool canDelete, bool isCCObject, void* data);

    CREATE_FUNC(ParameterObject);
};

#endif /* defined(__TinyZodiacs__ParameterObject__) */
