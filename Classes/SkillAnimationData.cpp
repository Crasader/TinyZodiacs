//
//  SkillAnimationData.cpp
//  TinyZodiacs
//
//  Created by NhutVM on 6/28/14.
//
//

#include "SkillAnimationData.h"
bool SkillAnimationData::haveAnyData()
{
    if(this->getExcuteAnimation() == NULL
       && this->getPreExcuteAnimation() == NULL
       && this->getStopAnimation() == NULL
       && this->getPreStopAnimation() == NULL)
    {
        return false;
    }
    return true;
}