//
//  Controller.cpp
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 5/23/14.
//
//

#include "Controller.h"

Controller::Controller()
{
    
}

Controller::~Controller()
{
    
}

bool Controller::receiveCommand(CommandID commandID, void* data)
{
    for (int i = 0; i < this->listSubController.size(); i++)
    {
        Controller* controller = static_cast<Controller*>(this->listSubController[i]);
        controller->receiveCommand(commandID, data);
    }
    return true;
}

bool Controller::removeSubController(Controller* controller)
{
    for( std::vector<Controller*>::iterator iter = this->listSubController.begin(); iter != this->listSubController.end(); ++iter )
    {
        if( *iter == controller )
        {
            this->listSubController.erase( iter );
            break;
        }
    }
    return true;
}

void Controller::removeAllSubController()
{
    for (int i = 0; i < this->listSubController.size(); i++)
    {
        this->listSubController[i]->removeAllSubController();
    }
    this->listSubController.clear();
}
