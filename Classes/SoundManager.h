//
//  SoundManager.h
//  TinyZodiacs
//
//  Created by NhutVM on 6/7/14.
//
//

#ifndef __TinyZodiacs__SoundManager__
#define __TinyZodiacs__SoundManager__

#include <iostream>
#include "CharacterSoundFactory.h"
class SoundManager
{
private:
protected:
public:
    static CharacterSoundData loadCharacterSoundData(const char* soundId);
};
#endif /* defined(__TinyZodiacs__SoundManager__) */
