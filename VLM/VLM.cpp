/* This file is part of an educational VLM project which is released under GNU General Public License v3.0 license
	For full details, check https://github.com/Mudrost/VLM/blob/main/LICENSE
*/

#include "SistemasLineares.h"
#include "Vetores.h"
#include "VLM.h"
#include <math.h>
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <chrono>

constexpr double pi = 3.14159265358979323846;
using namespace std;

int main() {
	// Mapeando os paineis aos índices fornecidos
	map<int, Painel> Paineis;
	auto duracao = std::chrono::system_clock::now().time_since_epoch();
	auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(duracao).count();

	for (int i = 0; i < 8; i++) {
		CarregarDadosPainel(i, Paineis);
	}

	auto duracaocarregar = std::chrono::system_clock::now().time_since_epoch();
	auto millis2 = std::chrono::duration_cast<std::chrono::milliseconds>(duracaocarregar).count();

	cout << "Tempo para carregar dados: " << millis2 - millis << "ms" << endl;
	cout << "Dados dos painéis:\n";
	for (int i = 0; i < 8; i++) {
		cout << "Painel " << i + 1 << endl;
		cout << "Anel: " << endl;
		cout << Paineis[i].Vertice1Anel.x << ", " << Paineis[i].Vertice1Anel.y << ", " << Paineis[i].Vertice1Anel.z << endl;
		cout << Paineis[i].Vertice2Anel.x << ", " << Paineis[i].Vertice2Anel.y << ", " << Paineis[i].Vertice2Anel.z << endl;
		cout << Paineis[i].Vertice3Anel.x << ", " << Paineis[i].Vertice3Anel.y << ", " << Paineis[i].Vertice3Anel.z << endl;
		cout << Paineis[i].Vertice4Anel.x << ", " << Paineis[i].Vertice4Anel.y << ", " << Paineis[i].Vertice4Anel.z << endl;
		cout << "Ponto de controle: " << endl;
		cout << Paineis[i].PontoDeControle.x << ", " << Paineis[i].PontoDeControle.y << ", " << Paineis[i].PontoDeControle.z << endl;
		cout << "Vértices do painel: " << endl;
		cout << Paineis[i].Vertice1Painel.x << ", " << Paineis[i].Vertice1Painel.y << ", " << Paineis[i].Vertice1Painel.z << endl;
		cout << Paineis[i].Vertice2Painel.x << ", " << Paineis[i].Vertice2Painel.y << ", " << Paineis[i].Vertice2Painel.z << endl;
		cout << Paineis[i].Vertice3Painel.x << ", " << Paineis[i].Vertice3Painel.y << ", " << Paineis[i].Vertice3Painel.z << endl;
		cout << Paineis[i].Vertice4Painel.x << ", " << Paineis[i].Vertice4Painel.y << ", " << Paineis[i].Vertice4Painel.z << endl;
		cout << endl;
	}







}

void CarregarDadosPainel(int numeroPainel, map<int, Painel>& Paineis) {
	// Alimentação de dados dos painéis através dos arquivos .txt
	// Ordem: Vértices do anel 1,2,3,4, ponto de controle, e então vértices do painel 1, 2, 3 e 4
	ifstream arquivo("vertices_anel.txt");
	
	string ArquivoAnel;

	Vetor3D vecs[9];

	if (arquivo) {
		ostringstream ss;
		ss << arquivo.rdbuf();
		ArquivoAnel = ss.str();
		ArquivoAnel.erase(0, 433 + (99 *numeroPainel));
		size_t aux;
		for (int i = 0; i < 4; i++) {
			double x = stod(ArquivoAnel, &aux);
			ArquivoAnel.erase(0, aux);
			double y = stod(ArquivoAnel, &aux);
			ArquivoAnel.erase(0, aux);
			double z = stod(ArquivoAnel, &aux);
			ArquivoAnel.erase(0, aux);
			vecs[i] = Vetor3D(x, y, z);
		}
	}
	
	arquivo.close();
	arquivo.open("pontos_de_controle.txt");
	if (arquivo) {
		ostringstream ss;
		ss << arquivo.rdbuf();
		ArquivoAnel = ss.str();
		ArquivoAnel.erase(0, 67 + (27 *numeroPainel));
		size_t aux;
		double x = stod(ArquivoAnel, &aux);
		ArquivoAnel.erase(0, aux);
		double y = stod(ArquivoAnel, &aux);
		ArquivoAnel.erase(0, aux);
		double z = stod(ArquivoAnel, &aux);
		ArquivoAnel.erase(0, aux);
		vecs[4] = Vetor3D(x, y, z);
	}
	arquivo.close();
	arquivo.open("vertices_painel.txt");
	if (arquivo) {
		ostringstream ss;
		ss << arquivo.rdbuf();
		ArquivoAnel = ss.str();
		ArquivoAnel.erase(0, 451 + (99 *numeroPainel));
		size_t aux;
		for (int i = 5; i < 9; i++) {
			double x = stod(ArquivoAnel, &aux);
			ArquivoAnel.erase(0, aux);
			double y = stod(ArquivoAnel, &aux);
			ArquivoAnel.erase(0, aux);
			double z = stod(ArquivoAnel, &aux);
			ArquivoAnel.erase(0, aux);
			vecs[i] = Vetor3D(x, y, z);
		}
	}

	Paineis[numeroPainel] = Painel(vecs[0], vecs[1], vecs[2], vecs[3], vecs[4], vecs[5], vecs[6], vecs[7], vecs[8]);
}




Vetor3D InfluenciaAnel(Painel p1, Painel p2) {
	// Calcula o fator de influência de um painel qualquer p1 sobre o painel p2
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