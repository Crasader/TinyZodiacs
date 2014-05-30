//
//  TextShowEffect.cpp
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 5/29/14.
//
//

#include "TextShowEffect.h"

#include "AnimationLoader.h"

TextShowEffect::TextShowEffect()
{
    content = "";
    label = CCLabelTTF::create("", "Arial",55);
    this->addChild(label);
}

TextShowEffect::~TextShowEffect()
{

}

bool TextShowEffect::init()
{
    return true;
}

void TextShowEffect::run()
{
    label->setString(content.c_str());
    
    CCScaleTo* scale = CCScaleTo::create(1, 1.1);
    CCFadeIn* fadeIn = CCFadeIn::create(1);
    CCFadeOut* fadeOut = CCFadeOut::create(0.5f);
    CCCallFunc* func = CCCallFunc::create(this, callfunc_selector(TextShowEffect::stop));
    
    CCArray* arr = CCArray::create();
//        arr->addObject(scale);
//    arr->addObject(fadeIn);
    arr->addObject(CCSpawn::create(scale,fadeIn,NULL));
    arr->addObject(fadeOut);
    arr->addObject(func);
   
    this->label->runAction(CCSequence::create(arr));
}

void TextShowEffect::stop()
{
    this->label->stopAllActions();
    this->removeFromParent();
}

void TextShowEffect::setContent(string content)
{
    this->content = content;
}

void TextShowEffect::setLabelStyle(CCLabelTTF* label)
{
    if(this->label != NULL)
    {
        this->label->removeFromParent();
    }
    this->label = label;
    this->addChild(this->label);
}

void TextShowEffect::update(float dt)
{
}