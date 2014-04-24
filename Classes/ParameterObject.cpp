//
//  ParameterObject.cpp
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 4/18/14.
//
//

#include "ParameterObject.h"

ParameterObject::ParameterObject()
{
    this->canDelete = false;
    this->isCCObject = false;
    this->data = NULL;
    this->className = "";
}

ParameterObject::~ParameterObject()
{
    if (canDelete) {
        if(isCCObject)
        {
            ((CCObject*)data)->release();
        }
        else
        {
            deleteData(data);
        }
    }
}

bool ParameterObject::init()
{
    return true;
}

void ParameterObject::deleteData(void* data)
{
    if (typeid(ParameterObject).name() == className) {
        delete static_cast<ParameterObject*>(data);
    }
//    else if()
//    {
//    }
}

void ParameterObject::setData(bool canDelete, bool isCCObject, void* data)
{
    this->canDelete = canDelete;
    this->isCCObject = isCCObject;
    this->data = data;
}

