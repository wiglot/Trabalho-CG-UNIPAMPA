/*
 * carpo.h
 *
 *  Created on: 18/05/2009
 *      Author: 2623110
 */

#ifndef CARPO_H_
#define CARPO_H_

class Carpo {
	float altura;
	float largura;
	float comprimento;
public:
	Carpo(float alt, float larg, float comp)
		:altura(alt)
		,largura(larg)
		,comprimento(comp)
		{

		}
	~Carpo();
    float getAltura() const
    {
        return altura;
    }

    float getLargura() const
    {
        return largura;
    }

    float getComprimento() const
    {
        return comprimento;
    }

    void draw(){
		glBegin(GL_QUADS);
			//Topo
			glVertex3f(0.0, 0.0 ,0.0);
			glVertex3f(this->largura, 0.0 ,0.0);
			glVertex3f(this->largura, 0.0 ,this->comprimento);
			glVertex3f(0.0, 0.0 ,this->comprimento);

			//Palma
			glVertex3f(0.0, -this->altura ,0.0);
			glVertex3f(0.0, -this->altura ,this->comprimento);
			glVertex3f(this->largura, -this->altura ,this->comprimento);
			glVertex3f(this->largura, -this->altura ,0.0);

			//Pulso
			glVertex3f(0.0, 0.0 ,0.0);
			glVertex3f(0.0, -this->altura ,0.0);
			glVertex3f(this->largura, -this->altura ,0.0);
			glVertex3f(this->largura, 0.0 ,0.0);

			//Mão
			glVertex3f(0.0, 0.0 ,this->comprimento);
			glVertex3f(this->largura, 0.0 , this->comprimento);
			glVertex3f(this->largura, -this->altura , this->comprimento);
			glVertex3f(0.0, -this->altura ,this->comprimento);

			//Lados
			glVertex3f(0.0, 0.0 ,0.0);
			glVertex3f(0.0, 0.0 ,this->comprimento);
			glVertex3f(0.0, -this->altura ,this->comprimento);
			glVertex3f(0.0, -this->altura ,0.0);

			glVertex3f(this->largura, 0.0 ,0.0);
			glVertex3f(this->largura, -this->altura ,0.0);
			glVertex3f(this->largura, -this->altura ,this->comprimento);
			glVertex3f(this->largura, 0.0 ,this->comprimento);

		glEnd();
	}
};

#endif /* CARPO_H_ */
