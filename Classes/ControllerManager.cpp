//
//  ControllerManager.cpp
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 5/23/14.
//
//

#include "ControllerManager.h"

static ControllerManager* instance = NULL;

ControllerManager::ControllerManager()
{
    
}

ControllerManager::~ControllerManager()
{
    
}

ControllerManager* ControllerManager::getInstance()
{
    if(instance == NULL)
    {
        instance = new ControllerManager();
    }
    return instance;
}
//
//bool ControllerManager::registerController(const char* controllerID, Controller* controller)
//{
//    map<string, Controller*>::iterator it = listController.find(controllerID);
//
//    if(it == listController.end())
//    {
//        this->listController.insert(make_pair(controllerID, controller));
//        return false;
//    }
//
//    Controller* con = it->second;
//    con->getListSubController().push_back(controller);
//    return true;
//}


//bool ControllerManager::registerController(const char* controllerID1, const char* controllerID2)
//{
//    map<string, Controller*>::iterator it1 = listController.find(controllerID1);
//
//    if(it1 == listController.end())
//    {
//        return false;
//    }
//    Controller* con1 = it1->second;
//
//    map<string, Controller*>::iterator it2 = listController.find(controllerID2);
//    Controller* con2 = it2->second;
//
//    con1->listSubController.push_back(con2);
//    return true;
//}

//bool ControllerManager::unregisterController(const char* controllerID, Controller* controller)
//{
//    map<string, Controller*>::iterator it = listController.find(controllerID);
//
//    if(it == listController.end())
//    {
//        return false;
//    }
//
//    Controller* con = it->second;
//    con->removeSubController(controller);
//    return true;
//}
//
//bool ControllerManager::sendCommand(const char* controllerID, CommandID commandID)
//{
//    map<string, Controller*>::iterator it = listController.find(controllerID);
//
//    if(it != listController.end())
//    {
//        Controller* con = it->second;
//        con->receiveCommand(commandID, NULL);
//        return true;
//    }
//    return false;
//}
//
//bool ControllerManager::sendCommand(const char* controllerID, CommandID commandID, void* data)
//{
//    map<string, Controller*>::iterator it = listController.find(controllerID);
//
//    if(it != listController.end())
//    {
//        Controller* con = it->second;
//        con->receiveCommand(commandID, data);
//        return true;
//    }
//    return false;
//}

bool ControllerManager::registerController(ControllerID controllerID, Controller* controller)
{
    map<ControllerID, Controller*>::iterator it = listController.find(controllerID);
    
    if(it == listController.end())
    {
        this->listController.insert(make_pair(controllerID, controller));
        return false;
    }
    
    Controller* con = it->second;
    con->listSubController.push_back(controller);
    return true;
}

//bool ControllerManager::registerController(const char* controllerID1, const char* controllerID2)
//{
//    map<string, Controller*>::iterator it1 = listController.find(controllerID1);
//
//    if(it1 == listController.end())
//    {
//        return false;
//    }
//    Controller* con1 = it1->second;
//
//    map<string, Controller*>::iterator it2 = listController.find(controllerID2);
//    Controller* con2 = it2->second;
//
//    con1->listSubController.push_back(con2);
//    return true;
//}

bool ControllerManager::unregisterController(ControllerID controllerID, Controller* controller)
{
    map<ControllerID, Controller*>::iterator it = listController.find(controllerID);
    
    if(it == listController.end())
    {
        return false;
    }
    
    Controller* con = it->second;
    
    if(controller == con)
    {
        this->listController.erase(it);
    }
    else
    {
        con->removeSubController(controller);
    }
    
    return true;
}

bool ControllerManager::isRegisteredWith(ControllerID controllerID, Controller* controller)
{
    map<ControllerID, Controller*>::iterator it = listController.find(controllerID);
    
    if(it != listController.end())
    {
        
        Controller* con = it->second;
        if (con->containController(controller))
        {
            return true;
        }
    }
    return false;

}

bool ControllerManager::sendCommand(ControllerID controllerID, CommandID commandID)
{
    map<ControllerID, Controller*>::iterator it = listController.find(controllerID);
    
    if(it != listController.end())
    {
        Controller* con = it->second;
        con->receiveCommand(commandID, NULL);
        return true;
    }
    return false;
}

bool ControllerManager::sendCommand(ControllerID controllerID, CommandID commandID, void* data)
{
    map<ControllerID, Controller*>::iterator it = listController.find(controllerID);
    
    if(it != listController.end())
    {
        Controller* con = it->second;
        con->receiveCommand(commandID, data);
        return true;
    }
    return false;
}



