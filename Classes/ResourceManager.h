//
//  ResourceManager.h
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 7/15/14.
//
//

#ifndef __TinyZodiacs__ResourceManager__
#define __TinyZodiacs__ResourceManager__

#include <iostream>
#include "cocos2d.h"
#include "Constants.h"
#include "ResourcePack.h"
using namespace std;

USING_NS_CC;

class ResourceManager
{
private:
    CCArray* unusedResourcePackList;
protected:
public:
    ResourceManager();
    ~ResourceManager();
    
    static ResourceManager* getInstance();
    
    void addUnusedResourcePack(ResourcePack* resourcePack);
    void clean();
    
};
#endif /* defined(__TinyZodiacs__ResourceManager__) */
