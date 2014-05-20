//
//  Observable.h
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 5/13/14.
//
//

#ifndef __TinyZodiacs__Observable__
#define __TinyZodiacs__Observable__
class Observable;
#include <iostream>
#include "cocos2d.h"
#include "Observer.h"

using namespace std;
USING_NS_CC;

class Observable
{
private:
  
protected:
    vector<Observer*> listObserver;
public:
    virtual void attach(Observer* observer) = 0;
    virtual void detach(Observer* observer) = 0;
    virtual void notifyToDestroy() = 0;
};

#endif /* defined(__TinyZodiacs__Observable__) */
