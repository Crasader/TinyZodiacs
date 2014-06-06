//
//  CharacterSoundData.h
//  TinyZodiacs
//
//  Created by NhutVM on 6/4/14.
//
//

#ifndef __TinyZodiacs__CharacterSoundData__
#define __TinyZodiacs__CharacterSoundData__

#include <iostream>
#include "cocos2d.h"

USING_NS_CC;
class CharacterSoundData
{
private:
protected:
public:
    CC_SYNTHESIZE(std::string, hurtSoundStr, HurtSoundStr);
    CC_SYNTHESIZE(std::string, jumpSoundStr, JumpSoundStr);
    CC_SYNTHESIZE(std::string, deathSoundStr, DeathSoundStr);
};
#endif /* defined(__TinyZodiacs__CharacterSoundData__) */
