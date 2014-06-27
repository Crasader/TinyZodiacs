//
//  SoundManager.cpp
//  TinyZodiacs
//
//  Created by NhutVM on 6/7/14.
//
//

#include "SoundManager.h"
#include "SoundFactory.h"
#include "SimpleAudioEngine.h"

static std::vector<SoundStruct> listSoundId;

CharacterSoundData SoundManager::loadCharacterSoundData(const char* soundId)
{
    CharacterSoundData data = SoundFactory::loadCharacterSoundData(soundId);
    
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

ProjectileSoundData SoundManager::loadProjectileSoundData(const char* soundId)
{
    ProjectileSoundData data = SoundFactory::loadProjectileSoundData(soundId);
    string val = soundId;
    if(val != "")
    {
        if(data.getCreateSoundStr() != "")
        {
            addSoundId(data.getCreateSoundStr().c_str(), SOUND_EFFECT);
        }
        if(data.getShootSoundStr() != "")
        {
            addSoundId(data.getShootSoundStr().c_str(), SOUND_EFFECT);
        }
        if(data.getDieSoundStr() != "")
        {
            addSoundId(data.getDieSoundStr().c_str(), SOUND_EFFECT);
        }
        if(data.getHitSoundStr() != "")
        {
            addSoundId(data.getHitSoundStr().c_str(), SOUND_EFFECT);
        }
    }
    return data;
}

SkillSoundData SoundManager::loadSkillSoundData(const char* soundId)
{
    SkillSoundData data = SoundFactory::loadSkillSoundData(soundId);
    string val = soundId;
    if(val != "")
    {
        if(data.getexcuteSoundStr() != "")
        {
            addSoundId(data.getexcuteSoundStr().c_str(), SOUND_EFFECT);
        }
        if(data.getHitSoundStr() != "")
        {
            addSoundId(data.getHitSoundStr().c_str(), SOUND_EFFECT);
        }
        if(data.getStopSoundStr() != "")
        {
            addSoundId(data.getStopSoundStr().c_str(), SOUND_EFFECT);
        }
    }
    return data;
}

std::string SoundManager::loadBackGroundMusic(const char* soundId)
{
    return "";
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
        CCLOG("preload %s", soundStruct.soundId.c_str());
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
        CCLOG("unload %s", soundStruct.soundId.c_str());
    }
    SoundManager::removeAllList();
}

unsigned int SoundManager::playSoundEffect(const char* soundId, bool isLoop)
{
    return CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(soundId, isLoop);
}

void SoundManager::playMusic(const char* soundId, bool isLoop)
{
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(soundId, isLoop);
}

void SoundManager::stopSoundEffect(unsigned int soundId)
{
    CocosDenshion::SimpleAudioEngine::sharedEngine()->stopEffect(soundId);
}

void SoundManager::stopMusic(const char* soundId)
{
    CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(true);
}

void SoundManager::playMenuMusic()
{
    //set background music
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("AssetMusic_Commons_WitchTheme.mp3", true);
}