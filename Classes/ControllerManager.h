//
//  ControllerManager.h
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 5/23/14.
//
//

#ifndef __TinyZodiacs__ControllerManager__
#define __TinyZodiacs__ControllerManager__

#include <iostream>
#include "Controller.h"
#include <map>
#include "Constants.h"

using namespace std;

class ControllerManager
{
private:
protected:
    map<ControllerID, Controller*> listController;
public:
    ControllerManager();
    ~ControllerManager();
    
    static ControllerManager* getInstance();
    
//    bool registerController(const char* controllerID, Controller* controller);
//  //   bool registerController(const char* controllerID1, const char* controllerID2);
//    bool unregisterController(const char* controllerID, Controller* controller);
//    
//    bool sendCommand(const char* controllerID, CommandID commandID);
//    bool sendCommand(const char* controllerID, CommandID commandID, void* data);
    
    bool registerController(ControllerID controllerID, Controller* controller);
    bool unregisterController(ControllerID controllerID, Controller* controller);
    bool isRegisteredWith(ControllerID controllerID, Controller* controller);

    
    bool sendCommand(ControllerID controllerID, CommandID commandID);
    bool sendCommand(ControllerID controllerID, CommandID commandID, void* data);
    
    void clean();
};

#endif /* defined(__TinyZodiacs__ControllerManager__) */
