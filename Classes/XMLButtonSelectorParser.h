//
//  XMLButtonSelectorParser.h
//  TinyZodiacs
//
//  Created by NhutVM on 6/11/14.
//
//

#ifndef __TinyZodiacs__XMLButtonSelectorParser__
#define __TinyZodiacs__XMLButtonSelectorParser__

#include <iostream>
#include "XMLHelper.h"
#include "Constants.h"

#define TAG_BUTTON "button"
#define ATTRIBUTE_ID "id"
#define ATTRIBUTE_ACTIVE_TEXTURE "active_texture"
#define ATTRIBUTE_DEACTIVE_TEXTURE "deactive_texture"
#define ATTRIBUTE_SELECTED_TEXTURE "selected_texture"


using namespace tinyxml2;
class XMLButtonSelectorParser
{
private:
protected:
    static std::string readActiveTexture(const XMLElement* root);
    static std::string readDeactiveTexture(const XMLElement* root);
    static std::string readSelectedTexture(const XMLElement* root);

    static TextureSelector loadXMLFile(const char *xmlFileName, std::string selectorId);
public:
    static TextureSelector parseData(std::string selectorId);
};
#endif /* defined(__TinyZodiacs__XMLButtonSelectorParser__) */
