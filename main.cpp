#include <iostream>
#include "ListaCircular.h"
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>


using namespace std;

int main() {
    string nomeArq;
    cout<<"Digite o caminho completo do arquivo .txt contendo as palavras: ";
    getline(cin,nomeArq);

    srand(time(NULL));

    int linha = rand()% 3;

    ListaCircular<string> palavras;

    ifstream arquivo(nomeArq);

    if (arquivo.is_open()) {
        string linha;

        // L� o arquivo linha por linha
        while (getline(arquivo, linha)) {
            insere(palavras,tamanho(palavras)+1,linha);
        }

        arquivo.close(); // Fecha o arquivo ap�s a leitura
    } else {
        cout << "N�o foi poss�vel abrir o arquivo: " << nomeArq << std::endl;
    }

    mostraLista(palavras);

}
