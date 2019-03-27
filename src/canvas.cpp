#include "canvas.h"

Canvas::Canvas (uint m_width, uint m_heigth)
{
	this->m_width = m_width;
	this->m_heigth = m_heigth;
	this->image = new uint[ this->get_size_canvas() ]; 
}

Canvas::~Canvas ()
{
	delete image;
}

Canvas& Canvas::operator= (const Canvas & rhs)
{
	this->m_width = rhs.m_width;
	this->m_heigth = rhs.m_heigth;
	this->image = rhs.image;
	return *this;
}

/**
 * Main functions
 */

#include <iostream>
void Canvas::color_pixel (int x, int y, Color &color)
{
	int init_pixel = this->get_position_pixel(x, y);
	std::cout << init_pixel << " " << get_size_canvas() << "\n";
	for (int i=0; i < VALUES_PER_PIXEL; i++)
		this->image[init_pixel+i] = abs(color[i]);
}

int Canvas::get_position_pixel(int x, int y)
{
	if ( (unsigned int) x > this->m_width || 
		 (unsigned int) y > this->m_heigth ||
		 (unsigned int) x < 1 ||
		 (unsigned int) y < 1)
		return 0;

	/**
	 * A imagem está armazena sequenciamente em um grande array
	 * de unsigned char. A ordem de inserção no array é linha por 
	 * linha. Cada pixel possui uma quantidade de valores definida
	 * na constante VALUES_PER_PIXEL. A expressão abaixo define a
	 * quantidade de caracteres necessários para representar uma 
	 * linha da imagem.
	 */
	int line_size = this->m_width * VALUES_PER_PIXEL;


	/**
	 * Com o valor do eixo x do pixel podemos encontrar a possição
	 * do array em que a linha onde o pixel se encontra começa. Como
	 * a representação do array começa em 0 é necessário diminuir 1
	 * do valor de x_axis recebido. A expressão abaixo encontra o 
	 * início da linha onde o pixel está.
	 */
	int init_line_of_pixel = (x - 1) * line_size;


	/**
	 * Seguindo a lógica para encontrar o início da linha, agora 
	 * é necessário encontrar a posição onde começa o pixel. A 
	 * expressão abaixo realiza este cálculo.
	 */
	int init_pixel = init_line_of_pixel + (m_heigth-y) * VALUES_PER_PIXEL ;

	return init_pixel;
}

/**
 * Getters and Setters 
 */

uint * Canvas::get_image ()
{ return this->image; }

uint Canvas::get_width ()
{ return this->m_width; }

uint Canvas::get_heigth ()
{ return this->m_heigth; }

uint Canvas::get_size_canvas ()
{ return this->m_width * this->m_heigth * VALUES_PER_PIXEL; }