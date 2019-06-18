#include "shapes/triangle.h"
#include "../vec3.cpp"

bool Triangle::intersect(
            const Ray &r,
            SurfaceInteraction *surface 
        ) const
{
    float EPSILON = 0.000001;
    auto vs = vertices();
    point3 &v1 = std::get<0>(vs);
    point3 &v2 = std::get<1>(vs);
    point3 &v3 = std::get<2>(vs);

    vector edge1, edge2, h, s, q;
    float a,f,u,v;

    edge1 = v2 - v1;
    edge2 = v3 - v2; 

    const auto &origin_ray = r.get_origin();
    const auto &direction_ray = unit_vector(r.get_direction());

    h = cross(direction_ray, edge2);
    a = dot(edge1, h);

    point2f uv;
    float * tHit;

    if (backface_cull){
        if (a < EPSILON)
            return false;
        
        s = origin_ray - v1;
        u = ( dot(s,h) );
    
        if ( u < 0.0 || u > 1.0)
            return false;

        uv.element[0] = u;

        q = cross(s, edge1);
        v = dot(direction_ray, q);
    
        if ( v < 0.0 || (u + v) > a )
            return false;
        
        uv.element[1] = v;

        *tHit = dot(edge2, q);
        f = 1.0/a;
        *tHit *= f;
        uv *= f;

        if ( *tHit < EPSILON )
            return false;

    }else {
        // check if the ray is parallel to this triangle
        if ( a > -EPSILON && a < EPSILON )
            return false;
        
        f = 1.0/a;
        s = origin_ray - v1;
        u = f * ( dot(s,h) );

        if ( u < 0.0 || u > 1.0)
            return false;
        
        uv.element[0] = u;

        q = cross(s, edge1);
        v = f * dot(direction_ray, q);

        if ( v < 0.0 || (u + v) > 1.0 )
            return false;

        uv.element[1] = v;

        *tHit = f * dot(edge2, q);

        if ( *tHit < EPSILON ){
            return false;
    }

    if ( *tHit > r.tMax )
        return false;
    
    if ( surface != nullptr ){
        surface->p = r(*tHit);
        surface->uv = uv;
        surface->wo = -1.0 * r.get_direction();
        surface->t = *tHit;

        auto ns = normals();
        vector &n1 = std::get<0>(ns);
        vector &n2 = std::get<1>(ns);
        vector &n3 = std::get<2>(ns);


        surface->n = unit_vector(
            (1 - uv.element[0] - uv.element[1] * n1 
                + uv.element[0] * n2 + uv.element[1] * n2);
    }

    return true;

}

bool Triangle::intersect_p( const Ray &ray ) const
{
    return this->intersect(ray, nullptr);
}

// Return the triangle's bounding box.
Bounds3 Triangle::bounding_box () const {
    auto p = vertices();
    auto bounds = Bounds3{std::get<0>(p), std::get<1>(p)};

    return bounds.get_union(bounds, std::get<2>(p));
} 