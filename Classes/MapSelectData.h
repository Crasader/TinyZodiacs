//
//  MapSelectData.h
//  TinyZodiacs
//
//  Created by NhutVM on 6/7/14.
//
//

#ifndef __TinyZodiacs__MapSelectData__
#define __TinyZodiacs__MapSelectData__

#include <iostream>
#include "cocos2d.h"
#include "Constants.h"

USING_NS_CC;
class MapSelectData
{
private:
protected:
public:
    CC_SYNTHESIZE(TextureSelector, selector, Selector);
    CC_SYNTHESIZE(bool, state, state);
    CC_SYNTHESIZE(std::string, id, ID);
};
#endif /* defined(__TinyZodiacs__MapSelectData__) */
