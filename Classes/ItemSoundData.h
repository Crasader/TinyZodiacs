//
//  ItemSoundData.h
//  TinyZodiacs
//
//  Created by NhutVM on 6/27/14.
//
//

#ifndef __TinyZodiacs__ItemSoundData__
#define __TinyZodiacs__ItemSoundData__

#include <iostream>
#include "cocos2d.h"

USING_NS_CC;
class ItemSoundData
{
private:
protected:
public:
    CC_SYNTHESIZE(std::string, appearSoundStr, AppearSoundStr);
    CC_SYNTHESIZE(std::string, disappearSoundStr, DisappearSoundStr);
    CC_SYNTHESIZE(std::string, consumeSoundStr, ConsumeSoundStr);
    CC_SYNTHESIZE(std::string, destroySoundStr, DestroySoundStr);
};
#endif /* defined(__TinyZodiacs__ItemSoundData__) */
