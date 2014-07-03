//
//  SkillManager.h
//  TinyZodiacs
//
//  Created by NhutVM on 7/3/14.
//
//

#ifndef __TinyZodiacs__SkillManager__
#define __TinyZodiacs__SkillManager__

#include <iostream>
#include "cocos2d.h"
#include "Constants.h"
#include "AbstractSkill.h"
using namespace std;

USING_NS_CC;
class SkillManager: public CCObject
{
private:
protected:
    CCArray* listStopSkill;
public:
    SkillManager();
    ~SkillManager();
    virtual bool init();
    static SkillManager* getInstance();
    void addSkillToBeStop(AbstractSkill* skill);
    void update(float dt);
    static void release();
    CREATE_FUNC(SkillManager);
};
#endif /* defined(__TinyZodiacs__SkillManager__) */
