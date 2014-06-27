//
//  SkillSoundData.h
//  TinyZodiacs
//
//  Created by NhutVM on 6/26/14.
//
//

#ifndef __TinyZodiacs__SkillSoundData__
#define __TinyZodiacs__SkillSoundData__

#include <iostream>
#include "cocos2d.h"

USING_NS_CC;
class SkillSoundData
{
private:
protected:
public:
    CC_SYNTHESIZE(std::string, excuteSoundStr, excuteSoundStr);
    CC_SYNTHESIZE(std::string, hitSoundStr, HitSoundStr);
    CC_SYNTHESIZE(std::string, stopSoundStr, StopSoundStr);
};
#endif /* defined(__TinyZodiacs__SkillSoundData__) */
