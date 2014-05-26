//
//  Controller.h
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 5/23/14.
//
//

#ifndef __TinyZodiacs__Controller__
#define __TinyZodiacs__Controller__

class Controller;

#include <iostream>
#include "cocos2d.h"
#include "ControllerManager.h"
#include "Constants.h"

USING_NS_CC;
using namespace std;

class Controller
{
private:
protected:
public:
    vector<Controller*> listSubController;
    Controller();
    ~Controller();
    
    virtual bool receiveCommand(CommandID commandID, void* data);
    virtual bool removeSubController(Controller* controller);
    virtual void removeAllSubController();
};

#endif /* defined(__TinyZodiacs__Controller__) */
