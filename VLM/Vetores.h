#pragma once
/* This file is part of an educational VLM project which is released under GNU General Public License v3.0 license
	For full details, check https://github.com/Mudrost/VLM/blob/main/LICENSE
*/


class Vetor3D {
	// Classe para vetores 3D
public:
	// Construtores
	Vetor3D() { x = y = z = 0; }
	Vetor3D(double x0, double y0, double z0) { x = x0; y = y0; z = z0; }

	void Mostrar();
	// Destrutores
	~Vetor3D() {};
	// Dados
	double x;
	double y;
	double z;

	// Operações
	Vetor3D operator+(const Vetor3D& vec);
	Vetor3D operator-(const Vetor3D& vec);
	Vetor3D operator*(const Vetor3D& vec);			// Multiplicação vetorial
	Vetor3D operator*(const double value);			// Multiplicação escalar
	Vetor3D operator/(const double value);			// Divisão escalar

	double mod();									// Módulo do vetor
	double square();								// Quadrado do vetor 
	double dot(Vetor3D vec);									// Multiplicação escalar com outro vetor
};