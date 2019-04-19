#include <iostream>
#include <string>
#include <fstream>

#include "common.h"
#include "raster.h"
#include "xml-parser.h"
#include "orthographic_camera.h"
#include "pespective_camera.h"
#include "primitives/primitive.h"

int main (int argc, char *argv[])
{

	std::string name;
	if (argc == 2)
		name = argv[1];
	else {
		std::cout << "Please, specify the xml file with the scene specification.\n";
		std::cout << "./exe.out <xml_file>\n";
		return 0;	
	}
 
    ParserXML parser = ParserXML(name);
  
    try { parser.run();  }
    catch(std::string e)
    { std::cerr << e << '\n'; }
    
    int w = parser.buffer->get_width();
    int h = parser.buffer->get_heigth();

    Camera *cam = parser.camera;
    auto scene  = parser.scene;

    std::cout << "size:" << scene.size() << std::endl;

    for (int j = h-1; j >= 0; j--){
        for (int i = 0; i < w; i++){
            Ray r = cam->generate_ray(i,j);
            // std::cout << "pixel (" << i << ", " << j << ") ";
            // std::cout << r << std::endl;
            auto color = parser.background->sample(float(i)/float(w), float(j)/float(h));
           
            for ( auto p : scene ) { // Traverse each object.
                if ( p->intersect_p( r ) ) // Does the ray hit any sphere in the scene?
                    color = Color (255,0,0);  // Just paint it red.
            }
           
            parser.buffer->color_pixel(i, j, color);
        }
    }

    Raster raster = Raster(parser.buffer, parser.output);
    raster.draw();
    
	return 0;
	
}
