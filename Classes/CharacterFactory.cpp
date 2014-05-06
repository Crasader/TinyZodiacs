//
//  CharacterFactory.cpp
//  TinyZodiacs
//
//  Created by Nhut on 3/24/14.
//
//

#include "CharacterFactory.h"
#include "XMLHelper.h"
#include "DataCollector.h"

using namespace tinyxml2;


CharacterDTO CharacterFactory::loadXMLFile(const char *xmlFileName)
{
    
    //
    CharacterDTO data ;
    
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
    data.data.setSkill0(readSkill(docElement->FirstChildElement(TAG_SKILL_0)));
    data.data.setSkill1(readSkill(docElement->FirstChildElement(TAG_SKILL_1)));
    data.data.setSkill2(readSkill(docElement->FirstChildElement(TAG_SKILL_2)));

    
    delete []pFileData;
    return data;
}

string CharacterFactory::readBodyData(tinyxml2::XMLElement* root)
{
    return XMLHelper::readString(root, "");
}

string CharacterFactory::readAnimationData(tinyxml2::XMLElement* root)
{
    return XMLHelper::readString(root, "");
}

int CharacterFactory::readHealthData(tinyxml2::XMLElement* root)
{
    return XMLHelper::readInt(root, 0);
}

int CharacterFactory::readAttackData(tinyxml2::XMLElement* root)
{
    return XMLHelper::readInt(root, 0);
}

string CharacterFactory::readSkill(tinyxml2::XMLElement *root)
{
    return XMLHelper::readString(root, "");
}

int CharacterFactory::readDefenseData(tinyxml2::XMLElement* root)
{
    return XMLHelper::readInt(root, 0);
}

int CharacterFactory::readSpeedData(tinyxml2::XMLElement* root)
{
    return XMLHelper::readInt(root, 0);
}

float CharacterFactory::readAttackSpeedData(tinyxml2::XMLElement* root)
{
    return XMLHelper::readFloat(root, 0);
}

int CharacterFactory::readMaxJumpData(tinyxml2::XMLElement* root)
{
    return XMLHelper::readInt(root, 0);
}

int CharacterFactory::readJumpHeightData(tinyxml2::XMLElement* root)
{
    return XMLHelper::readInt(root, 0);
}

Hero* CharacterFactory::createHero(CharacterDTO heroDTOData, b2World* world, bool isLocal)
{
    Hero* hero = Hero::create();
//    hero->getSprite()->setScale(0);
    //
    hero->setOriginCharacterData(heroDTOData.data);
    
    //Create Animation
    string run = heroDTOData.animation;
    string attack = heroDTOData.animation;
    string idle = heroDTOData.animation;
    string fall = heroDTOData.animation;
    string fly = heroDTOData.animation;
    string jump = heroDTOData.animation;
    string skill = heroDTOData.animation;

    hero->runAnimation = DataCollector::getInstance()->getAnimationObjectByKey(string(std::string(run) + std::string(RUN)).c_str());
    hero->attackAnimation = DataCollector::getInstance()->getAnimationObjectByKey(attack.append(ATTACK).c_str());
    hero->jumpAnimation = DataCollector::getInstance()->getAnimationObjectByKey(jump.append(JUMP).c_str());
    hero->idleAnimation = DataCollector::getInstance()->getAnimationObjectByKey(idle.append(IDLE).c_str());
    hero->fallAnimation = DataCollector::getInstance()->getAnimationObjectByKey(fall.append(FALL).c_str());
    hero->flyAnimation = DataCollector::getInstance()->getAnimationObjectByKey(fly.append(FLY).c_str());
    hero->skill1Animation = DataCollector::getInstance()->getAnimationObjectByKey(skill.append(SKILL).c_str());

    //
    hero->attackAnimation->getAnimation()->setDelayPerUnit(hero->getOriginCharacterData().getAttackSpeed());
    
    loadBody(heroDTOData, hero, world);
  //  hero->getSprite()->setVisible(false);

    
    hero->setNormalAttack(SkillFactory::createSkill(heroDTOData.data.getSkill0().c_str(), world, hero, isLocal, SKILL_0_BUTTON));
    hero->setSkill1(SkillFactory::createSkill(heroDTOData.data.getSkill1().c_str(), world, hero, isLocal, SKILL_1_BUTTON));
    hero->setSkill2(SkillFactory::createSkill(heroDTOData.data.getSkill2().c_str(), world, hero, isLocal, SKILL_2_BUTTON));
    //
    hero->retain();
       //
    
    return hero;
}

void CharacterFactory::loadBody(CharacterDTO heroDTOData, Character* character, b2World* world)
{
    //Create body
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.angle = ccpToAngle(ccp(0,0));
    bodyDef.fixedRotation = true;
    bodyDef.userData = character;
    
    b2Body *body = world->CreateBody(&bodyDef);
    
    gbox2d::GB2ShapeCache *sc =  gbox2d::GB2ShapeCache::sharedGB2ShapeCache();
    sc->addFixturesToBody(body, heroDTOData.body.c_str());
    character->setSpriteAnchorPoint(sc->anchorPointForShape(heroDTOData.body.c_str()));
    character->getSprite()->setAnchorPoint(sc->anchorPointForShape(heroDTOData.body.c_str()));
    character->setSkin(body, character->getSprite());
}


Hero* CharacterFactory::createMonkeyHero(b2World* world, bool isLocal)
{
    if (world == NULL) {
        return  NULL;
    }
    CharacterDTO dtoData = loadXMLFile(CHARACTER_MONKEY_XML_FILE);
    
    return createHero(dtoData, world, isLocal);
}

Hero* CharacterFactory::createHero(string ID,b2World* world, bool isLocal)
{
    if (world == NULL) {
        return  NULL;
    }
    CharacterDTO dtoData = loadXMLFile(ID.c_str());
    
    return createHero(dtoData, world, isLocal);
}

CharacterDTO* CharacterFactory::loadXMLFile1(const char* xmlFileName)
{
    //
    CharacterDTO* data = CharacterDTO::create();
    
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
    data->body = readBodyData(docElement->FirstChildElement(TAG_BODY));
    data->animation = readAnimationData(docElement->FirstChildElement(TAG_ANIMATION));
    data->data.setAttack(readAttackData(docElement->FirstChildElement(TAG_ATTACK)));
    data->data.setHealth(readHealthData(docElement->FirstChildElement(TAG_HP)));
    data->data.setDefense(readDefenseData(docElement->FirstChildElement(TAG_DEFENSE)));
    data->data.setSpeed(readSpeedData(docElement->FirstChildElement(TAG_SPEED)));
    data->data.setAttackSpeed(readAttackSpeedData(docElement->FirstChildElement(TAG_ATTACK_SPEED)));
    data->data.setMaxJumpTimes(readMaxJumpData(docElement->FirstChildElement(TAG_MAX_JUMP)));
    data->data.setJumpHeight(readJumpHeightData(docElement->FirstChildElement(TAG_JUMP_HEIGHT)));
    data->data.setSkill0(readSkill(docElement->FirstChildElement(TAG_SKILL_0)));
    data->data.setSkill1(readSkill(docElement->FirstChildElement(TAG_SKILL_1)));
    data->data.setSkill2(readSkill(docElement->FirstChildElement(TAG_SKILL_2)));
    
    delete []pFileData;
    return data;
}


