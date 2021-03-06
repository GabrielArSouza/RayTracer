#ifndef _BOUNDS3F_H_
#define _BOUNDS3F_H_

/**
 * @file bounds3.h
 * @author Gabriel Araújo de Souza (gabriel_feg@hotmail.com)
 * @brief implements the Bounds3 class 
 * @version 0.1
 * @date 2019-05-28
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include <limits>
#include <algorithm>
#include "../common.h"

/**
 * @brief A class to represents a bounding box for
 * a shape. Reference: Matt Pharr, Wenzel Jakob, Greg 
 * Humphreys - Physically Based Rendering, Third Edition_ 
 * From Theory to Implementation (2016, Morgan Kaufmann)
 */
class Bounds3 {

public:

    point3 pMin, pMax;

    /**
     * @brief Construct a new Bounds 3 object
     */
    Bounds3(){
        float minNum = std::numeric_limits<float>::lowest();
        float maxNum = std::numeric_limits<float>::max();
        pMin = point3(maxNum, maxNum, maxNum);
        pMax = point3(minNum, minNum, minNum);
    }

    /**
     * @brief Construct a new Bounds 3 object
     * @param p the point 3D
     */
    Bounds3( const point3 &p ) 
        : pMin(p), pMax(p) 
        { /*empty*/ }

    /**
     * @brief Construct a new Bounds 3 object
     * 
     * @param p1 the first point
     * @param p2 the second point
     */
    Bounds3 ( const point3 &p1, const point3 &p2 )
        : pMin{ point3 {std::min(p1.x(), p2.x()), 
                        std::min(p1.y(), p2.y()), 
                        std::min(p1.z(), p2.z())} },
          pMax{ point3 {std::max(p1.x(), p2.x()), 
                        std::max(p1.y(), p2.y()),
                        std::max(p1.z(), p2.z())} } 
        { /*empty*/ }

    /**
     * @brief select between the two points at the
     * corners of the box. Select between pMin and pMax
     * based on the value of i
     * 
     * @param i  the value 
     * @return const point3& the const point 
     */
    const point3  &operator[] (int i) const;
    
    /**
     * @brief select between the two points at the
     * corners of the box. Select between pMin and pMax
     * based on the value of 
     * 
     * @param i  the value 
     * @return point3& the point 
     */
    point3 &operator[](int i);

    /**
     * @brief returns the coordinates of one of 
     * the eight corners of the bounding box.
     * 
     * @param corner the corner
     * @return point3  the coordinates of one of the 
     * either corners of bounding box
     */
    point3 corner( int corner ) const {

        return point3 ( (*this)[(corner & 1)].x(),
                        (*this)[(corner & 2) ? 1 : 0].y(),
                        (*this)[(corner & 4) ? 1 : 0].z() );
    }

    /**
     * @brief The union between a bounding box
     * and a point
     * 
     * @tparam T The type (int or float)
     * @param b  the bounding box
     * @param p  the point
     *
     * @return Bounds3 <T> a new bounding box
     * that encompasses that point as well as 
     * the original box
     */
    Bounds3 
    get_union( const Bounds3 &b, const point3 &p){
       
        return Bounds3(

            point3 {std::min(b.pMin.x(), p.x()),
                    std::min(b.pMin.y(), p.y()),
                    std::min(b.pMin.z(), p.z())},

            point3 {std::max(b.pMax.x(), p.x()),
                    std::max(b.pMax.y(), p.y()),
                    std::max(b.pMax.z(), p.z())}
            );
    }

    /**
     * @brief The union between two bounding boxes
     * 
     * @tparam T The tyoe (int or float)
     * @param b1 the first bounding box
     * @param b2 the second bounding box
     * 
     * @return Bounds3 <T>  a new box that bounds
     * the space encompassed by two other 
     * bounding boxes.
     */
    Bounds3
    get_union( const Bounds3 &b1, const Bounds3 &b2 ){
        return Bounds3(
            point3 (std::min(b1.pMin.x(), b2.pMin.x()),
                    std::min(b1.pMin.y(), b2.pMin.y()),
                    std::min(b1.pMin.z(), b2.pMin.z())),
            point3 (std::max(b1.pMax.x(), b2.pMax.x()),
                    std::max(b1.pMax.y(), b2.pMax.y()),
                    std::max(b1.pMax.z(), b2.pMax.z())));
    }

    /**
     * @brief The intersection of two bounding boxes.
     * computing the maximum of their two respective
     * minimum coordinates and the minimum of their
     * maximum coordinates.
     * 
     * @tparam T The tyoe (int or float)
     * @param b1 the first bounding box
     * @param b2 the second bounding box
     *  
     * @return Bounds3<T> a new box
     */
    Bounds3
    intersect( const Bounds3 &b1, const Bounds3 &b2 ){
        return Bounds3(
            point3 (std::max(b1.pMin.x(), b2.pMin.x()),
                    std::max(b1.pMin.y(), b2.pMin.y()),
                    std::max(b1.pMin.z(), b2.pMin.z())),
            point3 (std::min(b1.pMax.x(), b2.pMax.x()),
                    std::min(b1.pMax.y(), b2.pMax.y()),
                    std::min(b1.pMax.z(), b2.pMax.z())));        
    }

    /**
     * @brief determine if two bounding boxes overlap
     * 
     * @tparam T The tyoe (int or float)
     * @param b1 the first bounding box
     * @param b2 the second bounding box
     * 
     * @return true   if is overlap 
     * @return false  otherwise
     */
    bool overlaps(const Bounds3 &b1, const Bounds3 &b2) {
        
        bool x = ( b1.pMax.x() >= b2.pMin.x() ) && ( b1.pMin.x() <= b2.pMax.x() );
        bool y = ( b1.pMax.y() >= b2.pMin.y() ) && ( b1.pMin.y() <= b2.pMax.y() );
        bool z = ( b1.pMax.z() >= b2.pMin.z() ) && ( b1.pMin.z() <= b2.pMax.z() );

        return ( x && y && z );

    }

    /**
     * @brief  determine if a given point is 
     * inside the bounding box
     * 
     * @tparam T The tyoe (int or float)
     * @param p The point
     * @param b The bounding box
     * 
     * @return true   if inside
     * @return false  otherwise
     */
    bool inside(const point3 &p, const Bounds3 &b) {
        return (p.x() >= b.pMin.x() && p.x() <= b.pMax.x() &&
                p.y() >= b.pMin.y() && p.y() <= b.pMax.y() &&
                p.z() >= b.pMin.z() && p.z() <= b.pMax.z());
    }


    /**
     * @brief The InsideExclusive() variant of Inside() 
     * doesn’t consider points on the upper boundary to
     * be inside the bounds. It is mostly useful with 
     * integer-typed bounds
     * 
     * @tparam T The tyoe (int or float)
     * @param p The point
     * @param b The bounding box
     * 
     * @return true  if inside exclusie
     * @return false otherwise
     */
    bool inside_exclusive(const point3 &p, const Bounds3 &b) {
        return (p.x() >= b.pMin.x() && p.x() < b.pMax.x() &&
                p.y() >= b.pMin.y() && p.y() < b.pMax.y() &&
                p.z() >= b.pMin.z() && p.z() < b.pMax.z());
    }

    /**
     * @brief  pads the bounding box by a constant 
     * factor in both dimensions
     * 
     * @tparam T The tyoe (int or float)
     * @param b  the bounding box
     * @param delta the constant
     * 
     * @return Bounds3<T> a new box with the pad   
     */
    Bounds3
    expand(const Bounds3 &b, float delta);

    /**
     * @brief  get the bounding box diagonal
     * 
     * @return vector the vector along the box 
     * diagonal from the minimum point to the
     * maximum point. 
     */
    vector diagonal() const;

    /**
     * @brief computing the surface area 
     * of the six faces of the box
     * 
     * @return float the surface area
     */
    float surface_area() const;

    /**
     * @brief the volume inside of it are 
     * also frequently useful
     * 
     * @return float the volume
     */
    float volume () const;

    /**
     * @brief get the maximum extent
     * 
     * @return int  the index of which 
     * of the three axes is longest
     */
    int maximum_extent() const;

    /**
     * @brief The bounding box offset 
     * 
     * @param p the point
     * 
     * @return vector the continuous position of 
     * a point relative to the corners of the box,
     * where a point at the minimum corner has 
     * offset (0, 0, 0), a point at the maximum corner
     * has offset (1, 1, 1), and so forth.
     */
    vector offset( const point3 &p ) const;

    // void bounding_sphere(Point3 *center, Float *radius) const {
    //     *center = (pMin + pMax) / 2;
    //     *radius = Inside(*center, *this) ? Distance(*center, pMax) : 0;
    // }


    /**
     * ---------------------------------
     * specific bounding box to shapes +
     * ---------------------------------
     */

    void bounding_to_sphere ( point3 *center, float *radius );
    
};

#endif