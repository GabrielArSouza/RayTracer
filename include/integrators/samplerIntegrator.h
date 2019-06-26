#ifndef _SAMPLER_INTEGRATOR_H_
#define _SAMPLER_INTEGRATOR_H_

/**
 * @file samplerIntegrator.h
 * @author Gabriel Araújo de Souza (gabriel_feg@hotmail.com)
 * @brief 
 * @version 0.1
 * @date 2019-05-02
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include "integrator.h"
#include "../common.h"
#include "../sampler.h"
#include "../cameras/camera.h"
#include "../surfaceInteraction.h"
#include "../materials/flatMaterial.h"

/**
 * @brief This class represents an entity that 
 * has a camera, and receives a scene to generate
 * an image from.
 */
class SamplerIntegrator : public Integrator {

//=== Public interface 
public:

    /**
     * @brief Destroy the Sample Integrator object
     */
    virtual ~SamplerIntegrator(){ /*empty*/ };

    /**
     * @brief Construct a new Sample Integrator object
     * 
     * @param cam      the camera 
     * @param sampler  the sampler
     */
    SamplerIntegrator( std::shared_ptr<Camera> cam,
                       std::shared_ptr<Sampler> sampler)
            : camera{cam}, sampler{sampler}{};

    
    /**
     * @brief Construct a new Sampler Integrator object
     * 
     * @param cam      the camera
     * @param sampler  the sampler
     */
    SamplerIntegrator( Camera *& cam, 
                       std::shared_ptr<Sampler> sampler)
            : camera{cam}, sampler{sampler} {} 

    /**
     * @brief  in turn,  is a pure virtual method that
     * returns the incident radiance at the origin of
     * a given ray
     * 
     * @param ray      the ray
     * @param scene    the scene that is processing
     * @param sampler  the sampler
     * 
     * @return Color24 the incident radiance at the origin
     * of a given ray
     */
    virtual Color24 Li( const Ray& ray,
                        const Scene& scene,
                        Sampler& sampler ) 
                        const = 0;
    
    /**
     * @brief  runs the main application loop that 
     * invokes the Li(...) 
     * 
     * @param scene  the scene
     */
    virtual void render( const Scene& scene );
    
    /**
     * @brief An optional method that might prepare a 
     * scene or any auxiliary data structure for future
     * processing.
     * 
     * @param scene 
     */
    virtual void preprocess( const Scene& scene ){UNUSED(scene);}

protected:

    //<! the smart pointer for a camara
    std::shared_ptr<Camera> camera;
    
private:
    
    //<! the smart pointer for a sample
    std::shared_ptr<Sampler> sampler;


};

#endif