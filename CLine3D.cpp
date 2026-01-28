#include "CLine3D.h"

/*
*/
CLine3D::CLine3D()
{
    memset(this, 0x00, sizeof(CLine3D));
}

/*
*/
CLine3D::CLine3D(CVec3f* P0, CVec3f* D)
{
    memset(this, 0x00, sizeof(CLine3D));

    m_P0 = *P0;
    m_D = *D;
}

/*
*/
float CLine3D::Dist(CLine3D* L1, CLine3D* L2)
{
    //CVec3f Cross = CVec3f::Cross(L1.D, L2.D);
    m_cross = L1->m_D.Cross(&L2->m_D);

    //return Math::Abs(CVec3f::Dot(L2.P0 - L1.P0, Cross)) / Cross.Length();
    return fabsf((L2->m_P0 - L1->m_P0).Dot(&m_cross) / m_cross.Length());
}

/*
*/
float CLine3D::DistSq(CLine3D* L1, CLine3D* L2)
{
    //CVec3f Cross = CVec3f::Cross(L1.D, L2.D);
    m_cross = L1->m_D.Cross(&L2->m_D);

    //float Dot = CVec3f::Dot(L2.P0 - L1.P0, Cross);
    m_length = L2->m_P0 - L1->m_P0;

    m_ldc = m_length.Dot(&m_cross);

    return (m_ldc * m_ldc) / m_cross.LengthSq();
}

/*
*/
float CLine3D::DistToPoint(CVec3f* P)
{
    //float t0 = Dot(D, P - P0) / Vec3f::Dot(D, D);
    m_position = (*P - m_P0) / m_D.Dot(&m_D);

    m_ddp = m_D.Dot(&m_position);
    
    //float distanceLine = Vec3f::Dist(P, P0 + t0 * D);
    m_distance = m_P0 + (m_D * m_ddp);
    
    m_distanceLine = P->Dist(&m_distance);
    
    return m_distanceLine;
}

/*
*/
bool CLine3D::Intersection(CLine3D* line, CVec3f* intersect)
{
    CVec3f p = m_P0; // line1.point;
    CVec3f v = m_D; // line1.direction;
    CVec3f q = line->m_P0; //2.point;
    CVec3f u = line->m_D; //2.direction;

    CVec3f w0 = p - q; // Vector from point on line2 to point on line1

    double a = v.Dot(&v); // dot_product(v, v);
    double b = v.Dot(&u); // dot_product(v, u);
    double c = u.Dot(&u); // dot_product(u, u);
    double d = v.Dot(&w0); // dot_product(v, w0);
    double e = u.Dot(&w0); // dot_product(u, w0);

    double denominator = a * c - b * b;

    const double LOCALEPSILON = 1e-9; // Tolerance for floating-point comparisons}

    if (fabs(denominator) < LOCALEPSILON)
    {
        // Lines are parallel
        // Handle parallel cases (coincident or distinct parallel)
        // For simplicity, returning false (no unique intersection)
        return false;
    }

    double s = (b * e - c * d) / denominator;
    //double t = (a * e - b * d) / denominator; // This 't' is actually the parameter for line2, 'u' in our notation

    // Check if the lines actually intersect at this point by verifying the third dimension
    // or by checking if the shortest distance between them is negligible.
    // For a true intersection, the shortest distance between the lines should be zero.
    // A more robust check involves the cross product method as well.

    // A common method for intersection check:
    // If (v x u) . (w0) is close to zero, they are coplanar.
    // If (v x u) is close to zero, they are parallel.
    // If they are coplanar and not parallel, they intersect.

    CVec3f cross_vu = v.Cross(&u); // cross_product(v, u);

    if (fabs(cross_vu.Dot(&w0)) > LOCALEPSILON) // dot_product(cross_vu, w0)) > EPSILON)
    {
        // Lines are skew, not intersecting
        return false;
    }

    // If they are coplanar and not parallel, they intersect.
    // The calculated 's' (for line1) and 't' (for line2) are the parameters.
    //intersection_point = { p.x + s * v.x, p.y + s * v.y, p.z + s * v.z };

    intersect->m_p.x = p.m_p.x + (float)s * v.m_p.x;
    intersect->m_p.y = p.m_p.y + (float)s * v.m_p.y;
    intersect->m_p.z = p.m_p.z + (float)s * v.m_p.z;

    return true;
}
/*

#include <iostream>
#include <cmath> // For std::abs

struct Vector3 {
    double x, y, z;

    // Add necessary operators like +, -, *, cross product, dot product
    // for vector arithmetic.
};

struct Line {
    Vector3 point;
    Vector3 direction;
};

// Function to calculate the cross product of two Vector3
Vector3 cross_product(const Vector3& v1, const Vector3& v2) {
    return {v1.y * v2.z - v1.z * v2.y,
            v1.z * v2.x - v1.x * v2.z,
            v1.x * v2.y - v1.y * v2.x};
}

// Function to calculate the dot product of two Vector3
double dot_product(const Vector3& v1, const Vector3& v2) {
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

// Function to find the intersection point
bool find_line_intersection(const Line& line1, const Line& line2, Vector3& intersection_point) {
    Vector3 p = line1.point;
    Vector3 v = line1.direction;
    Vector3 q = line2.point;
    Vector3 u = line2.direction;

    Vector3 w0 = p - q; // Vector from point on line2 to point on line1

    double a = dot_product(v, v);
    double b = dot_product(v, u);
    double c = dot_product(u, u);
    double d = dot_product(v, w0);
    double e = dot_product(u, w0);

    double denominator = a * c - b * b;

    const double EPSILON = 1e-9; // Tolerance for floating-point comparisons

    if (std::abs(denominator) < EPSILON) { // Lines are parallel
        // Handle parallel cases (coincident or distinct parallel)
        // For simplicity, returning false (no unique intersection)
        return false;
    }

    double s = (b * e - c * d) / denominator;
    double t = (a * e - b * d) / denominator; // This 't' is actually the parameter for line2, 'u' in our notation

    // Check if the lines actually intersect at this point by verifying the third dimension
    // or by checking if the shortest distance between them is negligible.
    // For a true intersection, the shortest distance between the lines should be zero.
    // A more robust check involves the cross product method as well.

    // A common method for intersection check:
    // If (v x u) . (w0) is close to zero, they are coplanar.
    // If (v x u) is close to zero, they are parallel.
    // If they are coplanar and not parallel, they intersect.

    Vector3 cross_vu = cross_product(v, u);
    if (std::abs(dot_product(cross_vu, w0)) > EPSILON) {
        // Lines are skew, not intersecting
        return false;
    }

    // If they are coplanar and not parallel, they intersect.
    // The calculated 's' (for line1) and 't' (for line2) are the parameters.
    intersection_point = {p.x + s * v.x, p.y + s * v.y, p.z + s * v.z};
    return true;
}

int32_t main() {
    // Example usage
    Line line1 = {{0, 0, 0}, {1, 0, 0}}; // Line along X-axis
    Line line2 = {{0, 0, 0}, {0, 1, 0}}; // Line along Y-axis (intersecting at origin)

    Vector3 intersection_pt;
    if (find_line_intersection(line1, line2, intersection_pt)) {
        std::cout << "Lines intersect at: (" << intersection_pt.x << ", "
                  << intersection_pt.y << ", " << intersection_pt.z << ")" << std::endl;
    } else {
        std::cout << "Lines do not intersect or are parallel." << std::endl;
    }

    return 0;
}

*/