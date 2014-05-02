//
//  ActionZoomFollow.cpp
//  TinyZodiacs
//
//  Created by Nguyễn Hòa Phát on 4/28/14.
//
//

#include "ActionZoomFollow.h"

ActionZoomFollow::ActionZoomFollow(void)
: _followed_node(NULL)
, _old_scale(2.2f)
, _zoom_center(CCDirector::sharedDirector()->getWinSize() * 0.5f)
, _old_zoom_center()
{
}


ActionZoomFollow::~ActionZoomFollow(void)
{
    CC_SAFE_RELEASE(_followed_node);
}

ActionZoomFollow* ActionZoomFollow::create(CCNode *followed_node)
{
    ActionZoomFollow* pRet = new ActionZoomFollow();
    if (pRet && pRet->init(followed_node))
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}

bool ActionZoomFollow::init(CCNode* followed_node)
{
    SetNodeToFollow(followed_node);
    return true;
}

CCObject *ActionZoomFollow::copyWithZone(CCZone *pZone)
{
    CCZone *pNewZone = NULL;
    ActionZoomFollow *pRet = NULL;
    if(pZone && pZone->m_pCopyObject) //in case of being called at sub class
    {
        pRet = (ActionZoomFollow*)(pZone->m_pCopyObject);
    }
    else
    {
        pRet = new ActionZoomFollow();
        pZone = pNewZone = new CCZone(pRet);
    }
    CCAction::copyWithZone(pZone);
    // copy member data
    pRet->m_nTag = m_nTag;
    CC_SAFE_DELETE(pNewZone);
    return pRet;
}

void ActionZoomFollow::startWithTarget(CCNode *target)
{
    CCAction::startWithTarget(target);
    _old_zoom_center = m_pTarget->convertToNodeSpace(_zoom_center);
}

void ActionZoomFollow::step(float dt)
{
    CC_UNUSED_PARAM(dt);
    
    float scale = m_pTarget->getScale();
    CCPoint half_size = CCDirector::sharedDirector()->getWinSize() * 0.5f;
    
    CCPoint pos;
    if (_followed_node)
    {
        pos = half_size - _followed_node->getPosition() * scale;
    }
    else
    {
        CCPoint old_zoom_point = _old_zoom_center * _old_scale;
        CCPoint new_zoom_point = _old_zoom_center * scale;
        pos = m_pTarget->getPosition() + old_zoom_point - new_zoom_point;
    }
    m_pTarget->setPosition(pos);
    _old_scale = scale;
    _old_zoom_center = m_pTarget->convertToNodeSpace(_zoom_center);
}

bool ActionZoomFollow::isDone()
{
    //return ( !_followed_node->isRunning() );
    if (_followed_node && !_followed_node->isRunning())
    {
        _followed_node->release();
        _followed_node = NULL;
    }
    return false;
}

void ActionZoomFollow::stop()
{
    m_pTarget = NULL;
    CCAction::stop();
}

void ActionZoomFollow::SetNodeToFollow(CCNode* followed_node)
{
    CC_SAFE_RELEASE(_followed_node);
    CC_SAFE_RETAIN(followed_node);
    _followed_node = followed_node;
}