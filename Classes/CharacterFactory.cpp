//
//  CharacterFactory.cpp
//  TinyZodiacs
//
//  Created by Nhut on 3/24/14.
//
//

#include "CharacterFactory.h"

using namespace tinyxml2;


CharacterDTO CharacterFactory::loadXMLFile(const char *xmlFileName)
{
    
    //
    CharacterDTO data;
    
    std::string fullPath = CCFileUtils::sharedFileUtils()->fullPathForFilename(xmlFileName);
    
    unsigned long dataSize = 0;
    unsigned char* pFileData = NULL;
    
    pFileData = (unsigned char*) CCFileUtils::sharedFileUtils()->getFileData(fullPath.c_str(), "r", &dataSize);
    //    CCLOG("Empty file: %s", fullPath.c_str());
    
    if (!pFileData)
    {
        //        CCLOG("Empty file: %s", fullPath.c_str());
        return data;
    }
    std::string fileContent;
    fileContent.assign(reinterpret_cast<const char*>( pFileData), dataSize);
    
    XMLDocument document;
    if( document.Parse(fileContent.c_str()) != XML_NO_ERROR)
    {
        CCLOG("Cannot parse file: %s", fullPath.c_str());
        return data;
    }
    
    //Parse data
    XMLElement* docElement = document.FirstChildElement();
    data.body = readBodyData(docElement->FirstChildElement(TAG_BODY));
    data.animation = readAnimationData(docElement->FirstChildElement(TAG_ANIMATION));
    data.data.setAttack(readAttackData(docElement->FirstChildElement(TAG_ATTACK)));
    data.data.setHealth(readHealthData(docElement->FirstChildElement(TAG_HP)));
    data.data.setDefense(readDefenseData(docElement->FirstChildElement(TAG_DEFENSE)));
    data.data.setSpeed(readSpeedData(docElement->FirstChildElement(TAG_SPEED)));
    data.data.setAttackSpeed(readAttackSpeedData(docElement->FirstChildElement(TAG_ATTACK_SPEED)));
    data.data.setMaxJumpTimes(readMaxJumpData(docElement->FirstChildElement(TAG_MAX_JUMP)));
    data.data.setJumpHeight(readJumpHeightData(docElement->FirstChildElement(TAG_JUMP_HEIGHT)));

    
    delete []pFileData;
    return data;
}

string CharacterFactory::readBodyData(tinyxml2::XMLElement* root)
{
    if(root != NULL)
    {
        string bodyId = root->GetText();
        return bodyId;
    }
    return NULL;
}

string CharacterFactory::readAnimationData(tinyxml2::XMLElement* root)
{
    if(root != NULL)
    {
        string animationId = root->GetText();
        return animationId;
    }
    return NULL;
}

int CharacterFactory::readHealthData(tinyxml2::XMLElement* root)
{
    if(root != NULL)
    {
        string healthValue = root->GetText();
        int value = atoi(healthValue.c_str());
        return value;
    }
    return 0;
}

int CharacterFactory::readAttackData(tinyxml2::XMLElement* root)
{
    if(root != NULL)
    {
        string attackValue = root->GetText();
        int value = atoi(attackValue.c_str());
        return value;
    }
    return 0;
}

int CharacterFactory::readDefenseData(tinyxml2::XMLElement* root)
{
    if(root != NULL)
    {
        string defenseValue = root->GetText();
        int value = atoi(defenseValue.c_str());
        return value;
    }
    return 0;
}

int CharacterFactory::readSpeedData(tinyxml2::XMLElement* root)
{
    if(root != NULL)
    {
        string speedValue = root->GetText();
        int value = atoi(speedValue.c_str());
        return value;
    }
    return 0;
}

float CharacterFactory::readAttackSpeedData(tinyxml2::XMLElement* root)
{
    if(root != NULL)
    {
        string attackSpeedValue = root->GetText();
        int value = atof(attackSpeedValue.c_str());
        return value;
    }
    return 0;
}

int CharacterFactory::readMaxJumpData(tinyxml2::XMLElement* root)
{
    if(root != NULL)
    {
        string maxJumpValue = root->GetText();
        int value = atoi(maxJumpValue.c_str());
        return value;
    }
    return 0;
}

int CharacterFactory::readJumpHeightData(tinyxml2::XMLElement* root)
{
    if(root != NULL)
    {
        string jumpHeightValue = root->GetText();
        int value = atoi(jumpHeightValue.c_str());
        return value;
    }
    return 1;
}

Hero* CharacterFactory::createHero(CharacterDTO heroDTOData, b2World* world)
{
    Hero* hero = Hero::create();

    //
    hero->setOriginCharacterData(heroDTOData.data);
    
    //Create Animation
    string run = heroDTOData.animation;
    string attack = heroDTOData.animation;
    string idle = heroDTOData.animation;
    string fall = heroDTOData.animation;
    string fly = heroDTOData.animation;
    string jump = heroDTOData.animation;

    hero->runAnimation = AnimationFactory::getSharedFactory()->getAnimationObjectByName(run.append(RUN).c_str());
    hero->attackAnimation = AnimationFactory::getSharedFactory()->getAnimationObjectByName(attack.append(ATTACK).c_str());
    hero->jumpAnimation = AnimationFactory::getSharedFactory()->getAnimationObjectByName(jump.append(JUMP).c_str());
    hero->idleAnimation = AnimationFactory::getSharedFactory()->getAnimationObjectByName(idle.append(IDLE).c_str());
    hero->fallAnimation = AnimationFactory::getSharedFactory()->getAnimationObjectByName(fall.append(FALL).c_str());
    hero->flyAnimation = AnimationFactory::getSharedFactory()->getAnimationObjectByName(fly.append(FLY).c_str());
    
    //Create body
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.angle = ccpToAngle(ccp(0,0));
    bodyDef.fixedRotation=true;
    bodyDef.userData = hero;
    
    b2Body *body = world->CreateBody(&bodyDef);
    
    gbox2d::GB2ShapeCache *sc =  gbox2d::GB2ShapeCache::sharedGB2ShapeCache();
    sc->addFixturesToBody(body, heroDTOData.body.c_str());
    hero->getSprite()->setAnchorPoint(sc->anchorPointForShape(heroDTOData.body.c_str()));
    //
    hero->setSkin(body, hero->getSprite());
    
    hero->retain();
    
    return hero;
}

Hero* CharacterFactory::createMonkeyHero(b2World* world)
{
    if (world == NULL) {
        return  NULL;
    }
    CharacterDTO dtoData = loadXMLFile(CHARACTER_MONKEY_XML_FILE);
    
    return createHero(dtoData, world);
}


