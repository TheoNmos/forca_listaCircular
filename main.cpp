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

        // Lê o arquivo linha por linha
        while (getline(arquivo, linha)) {
            insere(palavras,tamanho(palavras)+1,linha);
        }

        arquivo.close(); // Fecha o arquivo após a leitura
    } else {
        cout << "Não foi possível abrir o arquivo: " << nomeArq << std::endl;
    }

    mostraLista(palavras);

}
