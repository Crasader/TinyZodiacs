//
//  TowerFactory.cpp
//  TinyZodiacs
//
//  Created by NhutVM on 4/22/14.
//
//

#include "TowerFactory.h"
#include <string.h>

void TowerFactory::loadBody(CharacterDTO heroDTOData, Character* character, b2World* world)
{
    //Create body
    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;
    bodyDef.angle = ccpToAngle(ccp(0,0));
    bodyDef.fixedRotation=true;
    //    bodyDef.userData = character;
    
    b2Body *body = world->CreateBody(&bodyDef);
    
    gbox2d::GB2ShapeCache *sc =  gbox2d::GB2ShapeCache::sharedGB2ShapeCache();
    sc->addFixturesToBody(body, heroDTOData.body.c_str());
    character->setSpriteAnchorPoint(sc->anchorPointForShape(heroDTOData.body.c_str()));
    character->getSprite()->setAnchorPoint(sc->anchorPointForShape(heroDTOData.body.c_str()));
    character->setSkin(body, character->getSprite());
}

Tower* TowerFactory::createTower(CharacterDTO heroDTOData, b2World* world, bool isLocal)
{
    Tower* tower = Tower::create();
    //    hero->getSprite()->setScale(0);
    //
    tower->setOriginCharacterData(heroDTOData.data);
    
    //Create Animation
    string run = heroDTOData.animation;
    string attack = heroDTOData.animation;
    string idle = heroDTOData.animation;
    string fall = heroDTOData.animation;
    string fly = heroDTOData.animation;
    string jump = heroDTOData.animation;
    
    tower->runAnimation = AnimationFactory::getSharedFactory()->getAnimationObjectByName(run.append(RUN).c_str());
    tower->attackAnimation = AnimationFactory::getSharedFactory()->getAnimationObjectByName(attack.append(ATTACK).c_str());
    tower->jumpAnimation = AnimationFactory::getSharedFactory()->getAnimationObjectByName(jump.append(JUMP).c_str());
    tower->idleAnimation = AnimationFactory::getSharedFactory()->getAnimationObjectByName(idle.append(IDLE).c_str());
    tower->fallAnimation = AnimationFactory::getSharedFactory()->getAnimationObjectByName(fall.append(FALL).c_str());
    tower->flyAnimation = AnimationFactory::getSharedFactory()->getAnimationObjectByName(fly.append(FLY).c_str());
    //
    tower->attackAnimation->getAnimation()->setDelayPerUnit(tower->getOriginCharacterData().getAttackSpeed());
    
    loadBody(heroDTOData, tower, world);
//    tower->getSprite()->setScale(0);
    //
    
    tower->setNormalAttack(SkillFactory::createSkill(heroDTOData.data.getSkill0().c_str(), world, tower, isLocal, SKILL_0_BUTTON));
    tower->setSkill1(SkillFactory::createSkill(heroDTOData.data.getSkill1().c_str(), world, tower, isLocal, SKILL_1_BUTTON));
    tower->setSkill2(SkillFactory::createSkill(heroDTOData.data.getSkill2().c_str(), world, tower, isLocal, SKILL_2_BUTTON));
    //
    tower->retain();
    //
    
    return tower;
}

Tower* TowerFactory::createTower(string ID,b2World* world)
{
    if (world == NULL) {
        return  NULL;
    }
    CharacterDTO dtoData = loadXMLFile(ID.c_str());
    
    return createTower(dtoData, world, false);
}

Tower* TowerFactory::createTower(TowerDTO* towerDTO ,b2World* world)
{
    if (world == NULL) {
        return  NULL;
    }
    CharacterDTO dtoData = loadXMLFile(towerDTO->id.c_str());
    
    Tower*  tower = createTower(dtoData, world, false);
    tower->setPositionInPixel(ccp(towerDTO->x,towerDTO->y));
    if(strcasecmp(towerDTO->group.c_str(),"A") == 0)
    {
        tower->setGroup(GROUP_A);
    }
    else
    {
        tower->setGroup(GROUP_B);
    }
   
    return tower;
}