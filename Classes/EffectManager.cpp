//
//  EffectManager.cpp
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 5/3/14.
//
//

#include "EffectManager.h"
static EffectManager* instance;

EffectManager::EffectManager()
{
    this->listEffect = CCArray::create();
    this->listEffect->retain();
}

EffectManager::~EffectManager()
{
    
}

EffectManager* EffectManager::getInstance()
{
    if (instance == NULL)
    {
        instance = EffectManager::create();
    }
    return instance;
}

void EffectManager::runEffect(Effect* effect, CCPoint position)
{
   // this->listEffect->addObject(effect);
    
    
    effect->setPosition(position);
    this->holder->addChild(effect);
    effect->run();
    
}

void EffectManager::runEffect(Effect* effect, CCPoint position, int layerIndex)
{
    effect->setPosition(position);
    this->holder->addChild(effect, layerIndex);
    
    effect->run();
    
}

void EffectManager::stopEffect(Effect* effect)
{
    if(effect != NULL)
    {
        effect->stop();
    }
}

void EffectManager::update(float dt)
{
}

void EffectManager::clean()
{
    std::vector<Effect*> arrEffectRemoved;
    
    CCObject* object = NULL;
    CCARRAY_FOREACH(this->listEffect, object)
    {
        Effect* effect = static_cast<Effect*>(object);
        
        arrEffectRemoved.push_back(effect);
        
    }
    for(int i = 0; i < arrEffectRemoved.size(); i++)
    {
        arrEffectRemoved[i]->removeFromParent();
        this->listEffect->removeObject(arrEffectRemoved[i]);
    }
    arrEffectRemoved.clear();
    
}