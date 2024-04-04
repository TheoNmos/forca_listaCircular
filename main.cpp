#include <iostream>
#include "ListaCircular.h"
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>


using namespace std;

string selecionaPalavra(string nomeArq) {

    ListaCircular<string> palavras;

    cria(palavras);

    ifstream arquivo(nomeArq);

    if (arquivo.is_open()) {
        string linha;

        // L� o arquivo linha por linha
        while (getline(arquivo, linha)) {
            insere(palavras,tamanho(palavras)+1,linha);
        }

        arquivo.close(); // Fecha o arquivo ap�s a leitura
    } else {
        throw "Erro na funcao selecionaPalavra: Nao foi possivel ler o arquivo";
    }

    srand(time(NULL));

    int linha = rand()% (tamanho(palavras))+1; // para que n�o caia na posi��o 0 e nem em uma posi��o maior que o tamanho da lista.

    string palavra = recElem(palavras,linha);

    destroi(palavras);

    return palavra;
}

int main() {

    string nomeArq;
    cout<<"Digite o caminho completo do arquivo .txt contendo as palavras: ";
    getline(cin,nomeArq);

    try{
        cout<<selecionaPalavra(nomeArq);
    }catch(const char* erro){
        cout<<erro<<endl;
    }


}
