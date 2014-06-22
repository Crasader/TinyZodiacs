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
#include "Constants.h"

class SoundManager
{
private:
protected:
    static void addSoundId(const char* soundID, SoundType type);
    static void removeSoundId(const char* soundID);
    static void removeAllList();
    static bool isAdded(SoundStruct soundStruct);
public:
    static CharacterSoundData loadCharacterSoundData(const char* soundId);
    static void preLoadAllAddedSound();
    static void unLoadAllAddedSound(bool shouldCleanList);
    static void playSoundEffect(const char* soundId, bool isLoop);
    static void playMusic(const char* soundId, bool isLoop);
    static void stopSoundEffect(const char* soundId);
    static void stopMusic(const char* soundId);
};
#endif /* defined(__TinyZodiacs__SoundManager__) */
