/* This file is part of an educational VLM project which is released under GNU General Public License v3.0 license
	For full details, check https://github.com/Mudrost/VLM/blob/main/LICENSE
*/

#include "Matriz.h"
#include "Vetores.h"
#include "VLM.h"
#include <math.h>
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>

constexpr double pi = 3.14159265358979323846;
using namespace std;

int main() {
	// Mapeando os paineis aos índices fornecidos
	map<int, Painel>		Paineis;
	map<string, Vetor3D>	InfluenciasA;
	CarregarDadosPainel(Paineis);
	
	for (int i = 1; i <= 8; i++) {
		cout << "Influencia do painel " << i << " sobre os demais: " << endl;
		for (int j = 1; j <= 8; j++) {
			char buf[5];
			cout << "C" << i << "," << j << endl;
			sprintf_s(buf, sizeof(buf),"C%d,%d", i, j);		// Ex: C1,7
			InfluenciasA[buf] = InfluenciaAnel(Paineis[i-1], Paineis[j-1]);
			InfluenciasA[buf].Mostrar();
		}
		cout << endl;
	}

	Matriz matriz(4, 3);
	matriz.dados[0] = 1;
	matriz.dados[1] = 3;
	matriz.dados[2] = -1;
	matriz.dados[3] = 13;
	matriz.dados[4] = 4;
	matriz.dados[5] = -1;
	matriz.dados[6] = 1;
	matriz.dados[7] = 9;
	matriz.dados[8] = 2;
	matriz.dados[9] = 4;
	matriz.dados[10] = 3;
	matriz.dados[11] = -6;
	matriz.Mostrar();
	matriz.EliminacaoGauss();
	matriz.Mostrar();
	Matriz resultados(1, 4);
	matriz.SubstituicaoReversa(resultados.dados);
	resultados.Mostrar();

}







void CarregarDadosPainel(map<int, Painel>& Paineis) {
	// Alimentação de dados dos painéis através dos arquivos .txt
	// Ordem: Vértices do anel 1,2,3,4, ponto de controle, e então vértices do painel 1, 2, 3 e 4
	ifstream arquivoAnel("vertices_anel.txt");
	ifstream arquivoPonto("pontos_de_controle.txt");
	ifstream arquivoPainel("vertices_painel.txt");
	Vetor3D vecs[9];
	if (arquivoAnel && arquivoPonto && arquivoPainel) {
		ostringstream ss1, ss2, ss3;
		string ArquivoAnel, ArquivoPonto, ArquivoPainel;
		ss1 << arquivoAnel.rdbuf();
		ArquivoAnel = ss1.str();
		ArquivoAnel.erase(0, 433);
		ss2 << arquivoPonto.rdbuf();
		ArquivoPonto = ss2.str();
		ArquivoPonto.erase(0, 67);
		ss3 << arquivoPainel.rdbuf();
		ArquivoPainel = ss3.str();
		ArquivoPainel.erase(0, 451);
		for (int nPainel = 0; nPainel < 8; nPainel++) {
			size_t aux;
			for (int i = 0; i < 4; i++) {
				double x = stod(ArquivoAnel, &aux);
				ArquivoAnel.erase(0, aux);
				double y = stod(ArquivoAnel, &aux);
				ArquivoAnel.erase(0, aux);
				double z = stod(ArquivoAnel, &aux);
				ArquivoAnel.erase(0, aux);
				if (i == 3 && nPainel != 7) {
					stod(ArquivoAnel, &aux);
					ArquivoAnel.erase(0, aux);
				}
				vecs[i] = Vetor3D(x, y, z);
			}
			double xP = stod(ArquivoPonto, &aux);
			ArquivoPonto.erase(0, aux);
			double yP = stod(ArquivoPonto, &aux);
			ArquivoPonto.erase(0, aux);
			double zP = stod(ArquivoPonto, &aux);
			ArquivoPonto.erase(0, aux);
			if (nPainel != 7) {
				stod(ArquivoPonto, &aux);
				ArquivoPonto.erase(0, aux);
			}
			vecs[4] = Vetor3D(xP, yP, zP);
			for (int i = 5; i < 9; i++) {
				double x = stod(ArquivoPainel, &aux);
				ArquivoPainel.erase(0, aux);
				double y = stod(ArquivoPainel, &aux);
				ArquivoPainel.erase(0, aux);
				double z = stod(ArquivoPainel, &aux);
				ArquivoPainel.erase(0, aux);
				if (i == 8 && nPainel != 7) {
					stod(ArquivoPainel, &aux);
					ArquivoPainel.erase(0, aux);
				}
				vecs[i] = Vetor3D(x, y, z);
			}
			Paineis[nPainel] = Painel(vecs[0], vecs[1], vecs[2], vecs[3], vecs[4], vecs[5], vecs[6], vecs[7], vecs[8]);
		}
	}
}

Vetor3D VetorNormal(Painel p) {
	// Retorna o vetor normal ao painel fornecido
	Vetor3D aux = (p.Vertice3Painel - p.Vertice1Painel) * (p.Vertice2Painel - p.Vertice4Painel);
	return (aux / aux.mod());
}

Vetor3D InfluenciaFerradura(Painel p1, Painel p2, double alpharad) {
	// Calcula o fator de influência do vórtice ferradura na esteira de um painel qualquer p1 sobre o ponto de controle de um painel qualquer p2
	Vetor3D e(cos(alpharad), 0, sin(alpharad));
	Vetor3D r1 = p1.PontoDeControle - p2.Vertice1Anel;
	Vetor3D r2 = p1.PontoDeControle - p2.Vertice2Anel;
	Vetor3D r12 = (r2 - r1) * (-1);
	Vetor3D influencia1 = (e * r2) * ((r2.dot(e) / r2.mod()) + 1) / (4 * pi * ((e * r2).mod() * (e * r2).mod()));
	Vetor3D influencia2 = (e * r1) * ((r1.dot(e) / r1.mod()) + 1) / (4 * pi * ((e * r1).mod() * (e * r1).mod()));
	Vetor3D influencia3 = ((r1 * r2) / (4 * pi * ((r1 * r2).mod() * (r1 * r2).mod()))) * ((r12.dot(r1) / r1.mod()) - (r12.dot(r2) / r2.mod()));
	return influencia1 - influencia2 + influencia3;
}

Vetor3D InfluenciaAnel(Painel p1, Painel p2) {
	// Calcula o fator de influência do vórtice anel de um painel qualquer p1 sobre o ponto de controle de um painel qualquer p2
	Vetor3D r1 = p1.PontoDeControle - p2.Vertice1Anel;
	Vetor3D r2 = p1.PontoDeControle - p2.Vertice2Anel;
	Vetor3D r3 = p1.PontoDeControle - p2.Vertice3Anel;
	Vetor3D r4 = p1.PontoDeControle - p2.Vertice4Anel;
	Vetor3D r12 = (r2 - r1) * (-1);
	Vetor3D r23 = (r3 - r2) * (-1);
	Vetor3D r34 = (r4 - r3) * (-1);
	Vetor3D r41 = (r1 - r4) * (-1);
	Vetor3D influencia1 = ((r1 * r2) / (4 * pi * ((r1 * r2).mod() * (r1 * r2).mod()))) * ((r12.dot(r1) / r1.mod()) - (r12.dot(r2) / r2.mod()));
	Vetor3D influencia2 = ((r2 * r3) / (4 * pi * ((r2 * r3).mod() * (r2 * r3).mod()))) * ((r23.dot(r2) / r2.mod()) - (r23.dot(r3) / r3.mod()));
	Vetor3D influencia3 = ((r3 * r4) / (4 * pi * ((r3 * r4).mod() * (r3 * r4).mod()))) * ((r34.dot(r3) / r3.mod()) - (r34.dot(r4) / r4.mod()));
	Vetor3D influencia4 = ((r4 * r1) / (4 * pi * ((r4 * r1).mod() * (r4 * r1).mod()))) * ((r41.dot(r4) / r4.mod()) - (r41.dot(r1) / r1.mod()));
	return influencia1+influencia2+influencia3+influencia4;
}


void EliminacaoGaussiana(double* matriz, size_t tamanho) {

	


}
