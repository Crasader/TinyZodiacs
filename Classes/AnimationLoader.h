//
//  AnimationLoader.h
//
//
//  Created by HoaPhat on 1/4/14.
//
//

#ifndef __SampleCocosProject__AnimationLoader__
#define __SampleCocosProject__AnimationLoader__

#include <iostream>
#include "cocos2d.h"
#include "AnimationObject.h"
#include "XMLHelper.h"

using namespace tinyxml2;
USING_NS_CC;

class AnimationLoader
{
private:
protected:
public:
    static bool loadData();
    static bool loadDataByFileName(const char* fileName);
};

#endif /* defined(__TinyZodiacs__AnimationLoader__) */
