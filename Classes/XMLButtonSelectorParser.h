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
