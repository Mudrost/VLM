#pragma once
/* This file is part of an educational VLM project which is released under GNU General Public License v3.0 license
	For full details, check https://github.com/Mudrost/VLM/blob/main/LICENSE
*/
#include <map>


class Painel {
	// Classe "Painel" para fácil manipulação
public:

	Painel() {


	}


	Painel(Vetor3D vec1anel, Vetor3D vec2anel, Vetor3D vec3anel, Vetor3D vec4anel, Vetor3D pdc, Vetor3D vec1painel, Vetor3D vec2painel, Vetor3D vec3painel, Vetor3D vec4painel)
	{
		Vertice1Anel = vec1anel;
		Vertice2Anel = vec2anel;
		Vertice3Anel = vec3anel;
		Vertice4Anel = vec4anel;
		PontoDeControle = pdc;
		Vertice1Painel = vec1painel;
		Vertice2Painel = vec2painel;
		Vertice3Painel = vec3painel;
		Vertice4Painel = vec4painel;
	};

	~Painel() {};

	// Um painel é definido pelos seguintes vetores:
	Vetor3D Vertice1Anel;
	Vetor3D Vertice2Anel;
	Vetor3D Vertice3Anel;
	Vetor3D Vertice4Anel;
	Vetor3D PontoDeControle;
	Vetor3D Vertice1Painel;
	Vetor3D Vertice2Painel;
	Vetor3D Vertice3Painel;
	Vetor3D Vertice4Painel;

};


Vetor3D InfluenciaAnel(Painel p1, Painel p2);
void CarregarDadosPainel(std::map<int, Painel>& Paineis);
