#ifndef _SPHERE_H_
#define _SPHERE_H_

/**
 * @file sphere.h
 * @author Gabriel Araújo de Souza (gabriel_feg@hotmail.com)
 * @brief It implements the Shape class to represent a sphere
 * @version 0.1
 * @date 2019-04-30
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include "shape.h"
#include "../surfaceInteraction.h"

#include <cmath>

/**
 * @brief The only geometric shape defines so far.
 * This class derives from Shape
 */
class Sphere : public Shape {

private:

    point3 center;  //<! the center of sphere
    float radius;   //<! the radius of sphere
    float eps = 0.001;
public:
    /**
     * @brief Construct a new Sphere object
     * 
     * @param center   the center of sphere
     * @param radius   the radius of sphere
     */
    Sphere ( const point3 &center, 
             float radius, 
             Material * material)
    : Shape{material}, center{center}, radius{radius}{};

    /**
     * @brief Destroy the Sphere object
     */
    // ~Sphere(){};

    // @Override
    bool intersect ( const Ray& r, 
                     SurfaceInteraction * surface) 
                     const
    {

        point3 origin = r.get_origin();
        vector direction = r.get_direction();

        vector oc = origin - this->center;

        float a = dot(direction, direction);
        float b = 2.0 * dot(oc, direction);
        float c = dot(oc,oc) - (this->radius * this->radius);
        
        float delta = (b * b) - (4.0 * a * c);

        if (delta < 0.0) return false;

        float r1 = (-b + sqrt(delta)) / (2 * a);
        float r2 = (-b - sqrt(delta)) / (2 * a);

        auto tHit = fmin(r1,r2);
        if (tHit > r.tMax || tHit < 0)
            return false; 

        if (surface != nullptr){
            surface->t = tHit;
            surface->p = r(surface->t);
            surface->m = material;
            // auto n = surface->p - center; // a interval between -1 and 1
            // surface->n = 0.5*Vec3(n.x()+1, n.y()+1, n.z()+1); // normalize between 0 and 1
            surface->n = unit_vector(2.0 * ( surface->p - center));
            surface->wo = unit_vector( -1.0 * (direction - origin));

            //displacement
            surface->p = surface->p + (eps * surface->n);
        }
        

        return true;
    }

    // @Override
    bool intersect_p(const Ray& r) const
    {
        // std::cout << r << std::endl;
        auto origin = r.get_origin();
        auto direction = r.get_direction();
        
        vector oc = origin - this->center;
        float a = dot(direction, direction);
        float b = 2.0 * dot(oc, direction);
        float c = dot(oc,oc) - (this->radius * this->radius);
        
        float delta = (b * b) - (4.0 * a * c); 
       
        return (delta >= 0.0);
    }
    
    Bounds3 bounding_box () const {
        
        vector r { radius, radius, radius };
        
        auto upper_bound = center + r;
        auto lower_bound = center - r;

        return Bounds3 {lower_bound, upper_bound};
    }

};

#endif