#ifndef _COMMON_H_
#define _COMMON_H_

/**
 * @file common.h
 * @author Gabriel Araújo de Souza (gabriel_feg@hotmail.com)
 * @brief 
 * @version 0.1
 * @date 2019-05-02
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include "vec3.h"
#include <memory>

#define MAX_COLOR_VALUE 255      //<! The max value RGB
#define MIN_COLOR_VALUE 0        //<! The min value RGB
#define VALUES_PER_PIXEL 3       //<! Dimension of image: three values (R,G,B);
#define OUTPUT_EXTENSION ".ppm"  //<! Default format image
#define OUTPUT_INDEX "P3"        //<! Default format image PPM
#define PI 3.141592              //<! Pi value
#define RADIANS 0.01745329252    //<! value of a degree in radians

#define UNUSED(x) (void)(x)

typedef Vec3 Color;   //<! alias to color
typedef Vec3 point3;  //<! alias to point 3D
typedef Vec3 vector;  //<! alias to vector
typedef Vec3 point2f; //<! alias to parametric coordinate
typedef Vec3 Color24; //<! alias to Color24
typedef Vec3 Point2i; //<! alias to represent a 2D point
typedef Vec3 normal3f; //<! alias to normal vector

typedef unsigned int uint; //<! alias to unsigned int

#endif