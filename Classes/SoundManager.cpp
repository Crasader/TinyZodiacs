//
//  SoundManager.cpp
//  TinyZodiacs
//
//  Created by NhutVM on 6/7/14.
//
//

#include "SoundManager.h"
#include "CharacterSoundFactory.h"
#include "SimpleAudioEngine.h"

static std::vector<SoundStruct> listSoundId;

CharacterSoundData SoundManager::loadCharacterSoundData(const char* soundId)
{
    CharacterSoundData data = CharacterSoundFactory::loadCharacterSoundData(soundId);
    
    string val = soundId;
    if(val != "")
    {
        if(data.getDeathSoundStr() != "")
        {
            addSoundId(data.getDeathSoundStr().c_str(), SOUND_EFFECT);
        }
        if(data.getHurtSoundStr() != "")
        {
            addSoundId(data.getHurtSoundStr().c_str(), SOUND_EFFECT);
        }
        if(data.getJumpSoundStr() != "")
        {
            addSoundId(data.getJumpSoundStr().c_str(), SOUND_EFFECT);
        }
    }

    
    return data;
}

void SoundManager::addSoundId(const char* soundID, SoundType type)
{
    SoundStruct soundStruct;
    soundStruct.soundId = soundID;
    soundStruct.type = type;
    
    if(isAdded(soundStruct))
    {
        listSoundId.push_back(soundStruct);
    }
}

bool SoundManager::isAdded(SoundStruct soundStruct)
{
    for(int i=0 ; i<listSoundId.size() ; i++)
    {
        SoundStruct soundStruct1 = listSoundId[i];
        
        string val1 = soundStruct.soundId;
        string val2 = soundStruct1.soundId;
        if(val1 == val2)
        {
            return false;
        }
    }
    return true;
}

void SoundManager::removeSoundId(const char* soundID)
{

}

void SoundManager::removeAllList()
{
    listSoundId.clear();
}

void SoundManager::preLoadAllAddedSound()
{
    for(int i=0 ; i<listSoundId.size() ; i++)
    {
        SoundStruct soundStruct = listSoundId[i];
        switch (soundStruct.type) {
            case MUSIC:
                CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic(soundStruct.soundId.c_str());
                break;
            case SOUND_EFFECT:
                CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(soundStruct.soundId.c_str());
                break;
            default:
                break;
        }
    }
}

void SoundManager::unLoadAllAddedSound(bool shouldCleanList)
{
    for(int i=0 ; i<listSoundId.size() ; i++)
    {
        SoundStruct soundStruct = listSoundId[i];
        switch (soundStruct.type) {
            case MUSIC:
                CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(true);
                break;
            case SOUND_EFFECT:
                CocosDenshion::SimpleAudioEngine::sharedEngine()->unloadEffect(soundStruct.soundId.c_str());
                break;
            default:
                break;
        }
    }
    SoundManager::removeAllList();
}

void SoundManager::playSoundEffect(const char* soundId, bool isLoop)
{
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(soundId, isLoop);
}

void SoundManager::playMusic(const char* soundId, bool isLoop)
{
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(soundId, isLoop);
}

void SoundManager::stopSoundEffect(const char* soundId)
{
}

void SoundManager::stopMusic(const char* soundId)
{
    CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(true);
}