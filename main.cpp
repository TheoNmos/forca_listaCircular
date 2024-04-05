#include <iostream>
#include "ListaCircular.h"
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cctype>


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

void insereLetras(ListaCircular<char>& lista, string palavra){
    for(int i = 1;i<=palavra.size();i++){
        insere(lista,i,palavra[i-1]);
    }
}

void mostraForca(ListaCircular<char>& lista, string tentativas, int numTentativas){
    cout<<"FORCA: ";
    for(int i = 1;i<=tamanho(lista);i++){
        cout<<"_ ";
    }
    cout<<endl;
    tentativas.size() > 0 ? cout<<"Voce ja tentou as letras: "<<tentativas<<endl : cout<<"Voce ainda nao tentou nenhuma letra!"<<endl;
    cout<<"Vidas: "<<5-numTentativas<<endl;
}

bool validaPalpite(string palpite,string tentativas){
    if (palpite.size() != 1 || !isalpha(palpite[0])) return false;

    for(int i = 0;i<tentativas.size();i++){
        if (palpite[0] == tentativas[i]){
            return false;
        }
    }
    return true;
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

    string tentativas = "";

    int numTentativas = 0;

    while(true){
        if (numTentativas == 6){
            cout<<"Voce perdeu! A palavra era : "<< palavra<<endl; // BOTAR PALAVRA AQUI
            break;
        }
        string palpite = "";
        mostraForca(letras,tentativas,numTentativas);

        cout<<"Faca sua tentativa: ";
        getline(cin,palpite);
        if (validaPalpite(palpite,tentativas)){ // validando para ver se realmente foi informada uma letra
            tentativas += palpite + ", ";
            numTentativas++;
        }
        else{
            cout<<"valor informado e invalido";
            continue;
        }

    }






    mostraLista(letras);



}
