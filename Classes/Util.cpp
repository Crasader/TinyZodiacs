//
//  Util.cpp
//  TinyZodiacs
//
//  Created by Nhut on 3/28/14.
//
//

#include "Util.h"
b2AABB Util::getBodyBoundingBox(b2Body* body)
{
    if(body != NULL)
    {
        //Calculate b
        b2AABB aabb;
        
        b2Transform t;
        t.SetIdentity();
        
        aabb.lowerBound = b2Vec2(FLT_MAX,FLT_MAX);
        aabb.upperBound = b2Vec2(-FLT_MAX,-FLT_MAX);
        b2Fixture* fixture = body->GetFixtureList();
        while (fixture != NULL)
        {
            //            aabb.Combine(aabb, fixture->GetAABB(0));
            //            fixture = fixture->GetNext();
            const b2Shape *shape = fixture->GetShape();
            const int childCount = shape->GetChildCount();
            for (int child = 0; child < childCount; ++child) {
                const b2Vec2 r(shape->m_radius, shape->m_radius);
                b2AABB shapeAABB;
                shape->ComputeAABB(&shapeAABB, t, child);
                shapeAABB.lowerBound = shapeAABB.lowerBound + r;
                shapeAABB.upperBound = shapeAABB.upperBound - r;
                aabb.Combine(shapeAABB);
            }
            fixture = fixture->GetNext();
        }
        return aabb;
    }
    return b2AABB();
}

b2Vec2 Util::getb2VecAnchor(b2Body* body, JointDef jointDef)
{
    if(body == NULL)
    {
        return b2Vec2(0,0);
    }
    //set joint anchor A
    b2AABB boundingBox = Util::getBodyBoundingBox(body);
    
    b2Vec2 jointAAnchor(0,0);
    
    switch (jointDef.x) {
        case JOINT_CENTER:
            jointAAnchor.x = (boundingBox.lowerBound.x+boundingBox.upperBound.x)/2+jointDef.offsetX;
            break;
        case JOINT_REAR:
        case JOINT_BOTTOM_OR_LEFT:
            jointAAnchor.x = boundingBox.lowerBound.x - jointDef.offsetX;
            break;
        case JOINT_TOP_OR_RIGHT:
            jointAAnchor.x = boundingBox.upperBound.x + jointDef.offsetX;
            break;
        default:
            break;
    }
    
    switch (jointDef.y) {
        case JOINT_CENTER:
            jointAAnchor.y = (boundingBox.lowerBound.y+boundingBox.upperBound.y)/2+jointDef.offsetY;
            break;
        case JOINT_REAR:
        case JOINT_BOTTOM_OR_LEFT:
            jointAAnchor.y = boundingBox.lowerBound.y - jointDef.offsetY;
            break;
        case JOINT_TOP_OR_RIGHT:
            jointAAnchor.y = boundingBox.upperBound.y + jointDef.offsetY;
            break;
        default:
            break;
    }
    
    return jointAAnchor;
}