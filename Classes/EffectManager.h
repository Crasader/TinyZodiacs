//
//  EffectManager.h
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 5/3/14.
//
//

#ifndef __TinyZodiacs__EffectManager__
#define __TinyZodiacs__EffectManager__

#include <iostream>
#include "cocos2d.h"
#include "Effect.h"
#include "Constants.h"

USING_NS_CC;

class EffectManager: public CCNode
{
private:
    CC_SYNTHESIZE(GameHolder, holder, Holder);
    CCArray* listEffect;
protected:
    EffectManager();
public:
    virtual ~EffectManager();
    
    virtual void update(float dt);
    
    static EffectManager* getInstance();
    
    
    void runEffect(Effect* effect, CCPoint position);
    void runEffect(Effect* effect, CCPoint position, int layerIndex);
    void runEffect(Effect* effect, CCPoint position, CCNode* holder);

    void stopEffect(Effect* effect);
    
    void clean();
    
    CREATE_FUNC(EffectManager);
};
#endif /* defined(__TinyZodiacs__EffectManager__) */
