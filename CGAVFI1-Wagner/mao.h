
#define INDICADOR 0
#define MEDIO 1
#define ANELAR 2
#define MINIMO 3
#define POLEGAR 4

#define X 0
#define Y 1
#define Z 2

#include "carpo.h"
#include "metacarpo.h"
#include "falange.h"

#include <cmath>
#include <iostream>

using namespace std;

class Mao
{
private:
	Carpo* carpo;
	GLuint carpo_dl;

	float anguloMetacarpo[3][5]; //[X|Y|Z][METACARPO]
	MetaCarpo* metacarpo[5];
	GLuint metacarpo_dl[5];

	float anguloProximais[3][5];
	Falange* proximais[5];
	GLuint proximais_dl[5];

	float anguloMedias[3][4];
	Falange* medias[4];
	GLuint medias_dl[4];

	float anguloDistais[3][5];
	Falange* distais[5];
	GLuint distais_dl[4];


public:
	static float drg2rad(float grau){
		return ((grau * 2* M_PI)/ 360.0);
	}

	Mao(){
		unsigned short i, j;
		//Zera Angulos
		for (i = 0; i < 3; i++){
			for (j = 0; j < 4; j++){
				anguloMetacarpo[i][j] =0.0;
				anguloProximais[i][j] = 0.0;
				anguloMedias[i][j] = 0.0;
				anguloDistais[i][j] = 0.0;
			}
			anguloMetacarpo[i][j] =25.0;
			anguloProximais[i][j] = 10.0;
			anguloDistais[i][j] = 5.0;
		}

		//Seta angulos dos dedos.
		anguloMetacarpo[0][0] = -10.0;
		anguloProximais[0][0] = -8.0;
		anguloMedias[0][0] = -6.0;
		anguloDistais[0][0] = -5.0;

		anguloMetacarpo[0][1] = -5.0;
		anguloProximais[0][1] = -4.0;
		anguloMedias[0][1] = -4.0;
		anguloDistais[0][1] = -3.0;

		anguloMetacarpo[0][3] = 5.0;
		anguloProximais[0][3] = 4.0;
		anguloMedias[0][3] = 4.0;
		anguloDistais[0][3] = 3.0;
	}

	Carpo *getCarpo() const
	{
		return carpo;
	}

	void setCarpo(Carpo *carpo)
	{
		this->carpo = carpo;
	}

	MetaCarpo *getMetacarpo(short indice) const
	{
		return metacarpo[indice];
	}

	void setMetacarpo(MetaCarpo *metacarpo, short indice)
	{
		this->metacarpo[indice]= metacarpo;
	}

	Falange *getProximais(short indice) const
	{
		return proximais[indice];
	}

	void setProximais(Falange *proximais, short indice)
	{
		this->proximais[indice] = proximais;
	}

	Falange *getMedias(short indice) const
	{
		if (indice >= 4)
			throw ("Polegar não contem Falange Media");
		return medias[indice];
	}

	void setMedias(Falange *medias, short indice)
	{
		if (indice >= 4)
			throw ("Polegar não pode conter Falange Media");
		this->medias[indice] = medias;
	}

	Falange *getDistais(short indice) const
	{
		return distais[indice];
	}

	void setDistais(Falange *distais, short indice)
	{
		this->distais[indice] = distais;
	}

	void createDLs(){
		GLuint DL;
		unsigned int i;

		DL = glGenLists(1);
		// start list
		glNewList(DL,GL_COMPILE);
			this->carpo->draw();
		// endList
		glEndList();
		this->carpo_dl = DL;


		//MetaCarpo
		for (i = 0; i < 5; i++){
			DL = glGenLists(1);
			// start list
			glNewList(DL,GL_COMPILE);
			this->metacarpo[i]->draw();
			// endList
			glEndList();
			this->metacarpo_dl[i] = DL;
		}

		//Falanges Proximais
		for (i = 0; i < 5; i++){
			DL = glGenLists(1);
			// start list
			glNewList(DL,GL_COMPILE);
			this->proximais[i]->draw();
			// endList
			glEndList();
			this->proximais_dl[i] = DL;
		}

		//Falanges Medias
		for (i = 0; i < 4; i++){
			DL = glGenLists(1);
			// start list
			glNewList(DL,GL_COMPILE);
			this->medias[i]->draw();
			// endList
			glEndList();
			this->medias_dl[i] = DL;
		}

		//Falanges
		for (i = 0; i < 5; i++){
			DL = glGenLists(1);
			// start list
			glNewList(DL,GL_COMPILE);
			this->distais[i]->draw();
			// endList
			glEndList();
			this->distais_dl[i] = DL;
		}

	}


	void draw(){
		unsigned int i;
		float distMeta = this->carpo->getLargura()/4.0;
		float acumuladoZ[5] = {0.0, 0.0, 0.0, 0.0, 0.0};
		float acumuladoX[5];
		//Desenha o Carpo
		glColor3f(0.0, 0.0, 1.0);
		glCallList(carpo_dl);

		//Desenha os Metacarpos
		glColor3f(0.0, 1.0, 0.0);


		for (i = 0; i < 5; i++){
			acumuladoZ[i] += this->carpo->getComprimento();
			acumuladoX[i] = distMeta*i;
			//tranlates e Rotates
			glTranslatef(acumuladoX[i],0.0, acumuladoZ[i]);
			glRotatef(this->anguloMetacarpo[X][i], 0.0, 1.0, 0.0);
			glCallList(metacarpo_dl[i]);
			glRotatef(-this->anguloMetacarpo[X][i], 0.0, 1.0, 0.0);
			glTranslatef(-acumuladoX[i],0.0, -acumuladoZ[i]);
			acumuladoX[i] += sin(Mao::drg2rad(this->anguloMetacarpo[X][i]))*this->metacarpo[i]->getComprimento();;

		}
//		//Desenha as Proximais
//
		//glColor3f(1.0, 0.0, 0.0);
		for (i = 0; i < 5; i++){
			//tranlates e Rotates

			acumuladoZ[i] +=cos(Mao::drg2rad(this->anguloMetacarpo[X][i]))*this->metacarpo[i]->getComprimento();
			glTranslatef(acumuladoX[i],0.0, acumuladoZ[i]);
			glRotatef(this->anguloProximais[X][i], 0.0, 1.0, 0.0);
			glCallList(proximais_dl[i]);
			glRotatef(-this->anguloProximais[X][i], 0.0, 1.0, 0.0);
			glTranslatef(-acumuladoX[i],0.0, -acumuladoZ[i]);
			acumuladoX[i] += sin(Mao::drg2rad(this->anguloProximais[X][i]))*this->proximais[i]->getComprimento();;
		}
		//Desenha as medias
		//glColor3f(0.0, 1.0, 1.0);
		for (i = 0; i < 4; i++){
			//tranlates e Rotates
			acumuladoZ[i] += cos(Mao::drg2rad(this->anguloProximais[X][i]))*this->proximais[i]->getComprimento();
			glTranslatef(acumuladoX[i],0.0, acumuladoZ[i]);
			glRotatef(this->anguloMedias[X][i], 0.0, 1.0, 0.0);
			glCallList(medias_dl[i]);
			glRotatef(-this->anguloMedias[X][i], 0.0, 1.0, 0.0);
			glTranslatef(-acumuladoX[i],0.0, -acumuladoZ[i]);
			acumuladoX[i] += sin(Mao::drg2rad(this->anguloMedias[X][i]))*this->medias[i]->getComprimento();;

		}

		//Desenha as Distais
		//glColor3f(1.0, 1.0, 0.0);
		for (i = 0; i < 4; i++){
			//tranlates e Rotates
			acumuladoZ[i]+= cos(Mao::drg2rad(this->anguloMedias[X][i]))*this->medias[i]->getComprimento();
			glTranslatef(acumuladoX[i],0.0, acumuladoZ[i]);
			glRotatef(this->anguloDistais[X][i], 0.0, 1.0, 0.0);
			glCallList(distais_dl[i]);
			glRotatef(-this->anguloDistais[X][i], 0.0, 1.0, 0.0);
			glTranslatef(-acumuladoX[i],0.0, -acumuladoZ[i]);
		}
		//Desenha Polegar
		acumuladoZ[i] += cos(Mao::drg2rad(this->anguloProximais[X][i]))*this->proximais[i]->getComprimento();
		glTranslatef(acumuladoX[i],0.0, acumuladoZ[i]);
		glRotatef(this->anguloDistais[X][i], 0.0, 1.0, 0.0);
		glCallList(distais_dl[i]);
		glRotatef(-this->anguloDistais[X][i], 0.0, 1.0, 0.0);
		glTranslatef(-acumuladoX[i],0.0, -acumuladoZ[i]);

	}

	void addAnguloMetacarpo(short dedo, short eixo, float delta){
		this->anguloMetacarpo[eixo][dedo] += delta;
		this->anguloProximais[eixo][dedo] += delta;
		if (dedo < 4)
			this->anguloMedias[eixo][dedo] += delta;
		this->anguloDistais[eixo][dedo] += delta;
	}
	
	void addAnguloProximais(short dedo, short eixo, float delta){
		this->anguloProximais[eixo][dedo] += delta;
		if (dedo < 4)
			this->anguloMedias[eixo][dedo] += delta;
		this->anguloDistais[eixo][dedo] += delta;
	}
	void addAnguloMedias(short dedo, short eixo, float delta){
		if (dedo < 4){
			this->anguloMedias[eixo][dedo] += delta;
			this->anguloDistais[eixo][dedo] += delta;
		}
	}
	void addAnguloDistais(short dedo, short eixo, float delta){
		this->anguloDistais[eixo][dedo] += delta;
	}
};
