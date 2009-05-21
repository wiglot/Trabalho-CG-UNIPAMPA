/*
 * falange.h
 *
 *  Created on: 18/05/2009
 *      Author: 2623110
 */

#ifndef FALANGE_H_
#define FALANGE_H_

#include <GL/glut.h>

class Falange {
private:
	float comprimento;
	float espessura;

public:
	Falange(float size, float diametro)
			:comprimento(size)
			,espessura(diametro)
		{

		}
	~Falange() { }


	void draw(){

		glBegin(GL_QUADS);
			glVertex3f(0.0,0.0,0.0);
			glVertex3f(0.0,0.0,this->comprimento);
			glVertex3f(0.0,-this->espessura,this->comprimento);
			glVertex3f(0.0,-this->espessura,0.0);

			glVertex3f(0.0,0.0,0.0);
			glVertex3f(0.0,0.0,this->comprimento);
			glVertex3f(this->espessura,0.0,this->comprimento);
			glVertex3f(this->espessura,0.0, 0.0);

			glVertex3f(this->espessura,0.0, 0.0);
			glVertex3f(this->espessura,0.0,this->comprimento);
			glVertex3f(this->espessura,-this->espessura,this->comprimento);
			glVertex3f(this->espessura,-this->espessura, 0.0);

			glVertex3f(this->espessura,-this->espessura, 0.0);
			glVertex3f(0.0,-this->espessura,0.0);
			glVertex3f(0.0,-this->espessura,this->comprimento);
			glVertex3f(this->espessura,-this->espessura, this->comprimento);

			glVertex3f(0.0,0.0, 0.0);
			glVertex3f(0.0,-this->espessura, 0.0);
			glVertex3f(this->espessura,-this->espessura, 0.0);
			glVertex3f(this->espessura,0.0, 0.0);

			glVertex3f(0.0, 0.0, this->comprimento);
			glVertex3f(0.0,-this->espessura, this->comprimento);
			glVertex3f(this->espessura,-this->espessura, this->comprimento);
			glVertex3f(this->espessura,0.0, this->comprimento);

		glEnd();

	}

    float getComprimento() const
    {
        return comprimento;
    }

    float getEspessura() const
    {
        return espessura;
    }


};

#endif /* FALANGE_H_ */
