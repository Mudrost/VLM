#pragma once
/* This file is part of an educational VLM project which is released under GNU General Public License v3.0 license
	For full details, check https://github.com/Mudrost/VLM/blob/main/LICENSE
*/


class Matriz {
public:
	
	Matriz(size_t col, size_t lin) { 
		colunas = col;
		linhas = lin;
		tamanho = col * lin;
		dados = new double[tamanho]; 
	}
	~Matriz() {
		
	}
	int EliminacaoGauss();
	void SubstituicaoReversa(double* resultados);
	void Mostrar();
	size_t colunas;
	size_t linhas;
	size_t tamanho;
	double*	 dados;

};


