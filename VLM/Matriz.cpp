/* This file is part of an educational VLM project which is released under GNU General Public License v3.0 license
	For full details, check https://github.com/Mudrost/VLM/blob/main/LICENSE
*/

// https://youtu.be/GKkUU4T6o08
// Eliminação Gaussiana -> Substituição Reversa -> Resultados


#include "Matriz.h"
#include <iostream>
using namespace std;


void Matriz::Mostrar() {
	cout << "[";
	for (size_t i = 0; i < linhas; i++) {

		for (size_t j = 0; j < colunas; j++) {
			cout << dados[i * colunas + j];
			if (j + 1 != colunas) {
				cout << ", ";
			}
		}
		if (i + 1 != linhas) {
			cout << ";\n";
		}
		
	}
	cout << "]" << endl;
}

int Matriz::EliminacaoGauss() {
	//https://www.codespeedy.com/gaussian-elimination-in-cpp/
	for (int i = 0; i < linhas; i++) {
		for (int j = i + 1; j < linhas; j++) {
			if (abs(dados[i * colunas + i]) < abs(dados[j * colunas + i])) {
				for (int k = 0; k < colunas; k++) {
					dados[i * colunas + k] = dados[i * colunas + k] + dados[j * colunas + k];
					dados[j * colunas + k] = dados[i * colunas + k] - dados[j * colunas + k];
					dados[i * colunas + k] = dados[i * colunas + k] - dados[j * colunas + k];
				}
			}
		}
	}
	for (int i = 0; i < linhas - 1; i++) {
		for (int j = i + 1; j < linhas; j++) {
			double fator = dados[j * colunas + i] / dados[i * colunas + i];
			for (int k = 0; k < colunas; k++) {
				dados[j * colunas + k] -= fator * dados[i * colunas + k];
			}
	
		}
	}
	return 1;
}


void Matriz::SubstituicaoReversa(double* resultados) {
	for (int i = linhas - 1; i >= 0; i--) {
		resultados[i] = dados[i * colunas + linhas];
		for (int j = i + 1; j < linhas; j++) {
			if (i != j) {
				resultados[i] -= dados[i * colunas + j] * resultados[j];
			}

		}
		resultados[i] = resultados[i] / dados[i * colunas + i];
	}
}