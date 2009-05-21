/*
 * metacarpo.h
 *
 *  Created on: 18/05/2009
 *      Author: 2623110
 */

#ifndef METACARPO_H_
#define METACARPO_H_

#include <GL/glut.h>

class MetaCarpo {
private:
	float espessura;
	float comprimento;
public:
	MetaCarpo(float larg, float comp)
		:espessura(larg)
		,comprimento(comp)
		{

		}
	~MetaCarpo();
    float getEspessura() const
    {
        return espessura;
    }

    float getComprimento() const
    {
        return comprimento;
    }

    void draw(){
		glBegin(GL_QUADS);
			//Topo
			glVertex3f(0.0, 0.0 ,0.0);
			glVertex3f(this->espessura, 0.0 ,0.0);
			glVertex3f(this->espessura, 0.0 ,this->comprimento);
			glVertex3f(0.0, 0.0 ,this->comprimento);

			//Palma
			glVertex3f(0.0, -this->espessura ,0.0);
			glVertex3f(0.0, -this->espessura ,this->comprimento);
			glVertex3f(this->espessura, -this->espessura ,this->comprimento);
			glVertex3f(this->espessura, -this->espessura ,0.0);

			//Pulso
			glVertex3f(0.0, 0.0 ,0.0);
			glVertex3f(0.0, -this->espessura ,0.0);
			glVertex3f(this->espessura, -this->espessura ,0.0);
			glVertex3f(this->espessura, 0.0 ,0.0);

			//Mão
			glVertex3f(0.0, 0.0 ,this->comprimento);
			glVertex3f(this->espessura, 0.0 , this->comprimento);
			glVertex3f(this->espessura, -this->espessura , this->comprimento);
			glVertex3f(0.0, -this->espessura ,this->comprimento);

			//Lados
			glVertex3f(0.0, 0.0 ,0.0);
			glVertex3f(0.0, 0.0 ,this->comprimento);
			glVertex3f(0.0, -this->espessura ,this->comprimento);
			glVertex3f(0.0, -this->espessura ,0.0);

			glVertex3f(this->espessura, 0.0 ,0.0);
			glVertex3f(this->espessura, -this->espessura ,0.0);
			glVertex3f(this->espessura, -this->espessura ,this->comprimento);
			glVertex3f(this->espessura, 0.0 ,this->comprimento);

		glEnd();

		//Desenha as Falanges proximais
			//ToDo Desenhar Falanges...
	}
};

#endif /* METACARPO_H_ */
