//
//  CharacterFactory.h
//  TinyZodiacs
//
//  Created by Nhut on 3/24/14.
//
//

#ifndef __TinyZodiacs__CharacterFactory__
#define __TinyZodiacs__CharacterFactory__

#include <iostream>
#include "cocos2d.h"
#include "Box2d/Box2D.h"
#include "CharacterDTO.h"
#include "Hero.h"
#include "GB2ShapeCache-x.h"
#include "AnimationFactory.h"
#include "SkillFactory.h"


USING_NS_CC;

#define TAG_BODY "body"
#define TAG_ANIMATION "animation"
#define TAG_HP "hp"
#define TAG_ATTACK "atk"
#define TAG_DEFENSE "def"
#define TAG_SPEED "speed"
#define TAG_ATTACK_SPEED "atk_speed"
#define TAG_MAX_JUMP "max_jump"
#define TAG_JUMP_HEIGHT "jump_height"

#define RUN "-run"
#define ATTACK "-attack"
#define JUMP "-jump"
#define IDLE "-idle"
#define FALL "-fall"
#define FLY "-fly"
#define SKILL "-skill"

#define CHARACTER_MONKEY_ID "monkey"

#define CHARACTER_MONKEY_XML_FILE "character_monkey.xml"

class CharacterFactory
{
private:
protected:
    static CharacterDTO loadXMLFile(const char* xmlFileName);
    
    static string readBodyData(tinyxml2::XMLElement* root);
    static int readHealthData(tinyxml2::XMLElement* root);
    static int readAttackData(tinyxml2::XMLElement* root);
    static int readDefenseData(tinyxml2::XMLElement* root);
    static int readSpeedData(tinyxml2::XMLElement* root);
    static float readAttackSpeedData(tinyxml2::XMLElement* root);
    static int readMaxJumpData(tinyxml2::XMLElement* root);
    static int readJumpHeightData(tinyxml2::XMLElement* root);
    static string readAnimationData(tinyxml2::XMLElement* root);

    static Hero* createHero(CharacterDTO heroDTOData, b2World* world);

public:
    static Hero* createMonkeyHero(b2World* world);
};
#endif /* defined(__TinyZodiacs__CharacterFactory__) */
