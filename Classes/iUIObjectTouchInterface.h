//
//  iUIObjectTouchInterface.h
//  CharacterDemo
//
//  Created by Nhut on 3/23/14.
//
//

#ifndef __CharacterDemo__iUIObjectTouchInterface__
#define __CharacterDemo__iUIObjectTouchInterface__

#include <iostream>
#include "cocos2d.h"

USING_NS_CC;
enum ButtonType {LEFT_BUTTON, RIGHT_BUTTON, JUMP_BUTTON};

class iUIObjectTouchEventInterface
{
public:
    virtual void touchBegan(void* sender ,CCSet* pTouches, CCEvent* event);
	virtual void touchHold(void* sender ,CCSet* pTouches, CCEvent* event);
	virtual void touchEnded(void* sender ,CCSet* pTouches, CCEvent* event);
};
#endif /* defined(__CharacterDemo__iUIObjectTouchInterface__) */
