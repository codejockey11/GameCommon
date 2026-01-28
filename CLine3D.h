#pragma once

#include "framework.h"

#include "CVec3f.h"

class CLine3D
{
public:

    CVec3f m_cross;
    CVec3f m_D;
    CVec3f m_distance;
    CVec3f m_length;
    CVec3f m_P0;
    CVec3f m_position;

    float m_ddp;
    float m_distanceLine;
    float m_ldc;

    int32_t m_plane;

    CLine3D();
    CLine3D(CVec3f* P0, CVec3f* D);

    float DistToPoint(CVec3f* V);
    float DistSq(CLine3D* L1, CLine3D* L2);
    float Dist(CLine3D* L1, CLine3D* L2);
    bool Intersection(CLine3D* line, CVec3f* intersect);
};