//
//  ProjectileSoundData.h
//  TinyZodiacs
//
//  Created by NhutVM on 6/24/14.
//
//

#ifndef __TinyZodiacs__ProjectileSoundData__
#define __TinyZodiacs__ProjectileSoundData__

#include <iostream>
#include "cocos2d.h"

USING_NS_CC;
class ProjectileSoundData
{
private:
protected:
public:
    CC_SYNTHESIZE(std::string, createSoundStr, CreateSoundStr);
    CC_SYNTHESIZE(std::string, shootSoundStr, ShootSoundStr);
    CC_SYNTHESIZE(std::string, hitSoundStr, HitSoundStr);
    CC_SYNTHESIZE(std::string, dieSoundStr, DieSoundStr);
};
#endif /* defined(__TinyZodiacs__ProjectileSoundData__) */
