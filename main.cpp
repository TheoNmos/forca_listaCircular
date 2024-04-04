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

        // Lê o arquivo linha por linha
        while (getline(arquivo, linha)) {
            insere(palavras,tamanho(palavras)+1,linha);
        }

        arquivo.close(); // Fecha o arquivo após a leitura
    } else {
        throw "Erro na funcao selecionaPalavra: Nao foi possivel ler o arquivo ou ele nao foi encontrado";
    }

    srand(time(NULL));

    int linha = rand()% (tamanho(palavras))+1; // para que não caia na posição 0 e nem em uma posição maior que o tamanho da lista.

    string palavra = recElem(palavras,linha);

    destroi(palavras);

    return palavra;
}

template <typename T>
void insereLetras(ListaCircular<T>& lista, string palavra){
    for(int i = 1;i<=palavra.size();i++){
        insere(lista,i,palavra[i-1]);
    }
}

int main() {

    string nomeArq;
    cout<<"Digite o caminho completo do arquivo .txt contendo as palavras: ";
    getline(cin,nomeArq);

    string palavra = "";

    try{
        palavra = selecionaPalavra(nomeArq);
    }catch(const char* erro){
        cout<<erro<<endl;
    }

    ListaCircular<char> letras;

    cria(letras);

    insereLetras(letras,palavra);

    mostraLista(letras);



}
