#include <iostream>
#include "ListaCircular.h"
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime> // para usar no rand()
#include <cctype>


using namespace std;

void verificaAcertos(ListaCircular<char> palavra, char palpite, ListaCircular<char> &acertos, int &contAcertos){
    bool achou = false;                         // Se o palpite está na palavra e se
    for(int i = 1; i<=tamanho(palavra); i++){
        if(recElem(palavra, i)==tolower(palpite)){

            try{
            palpite = tolower(palpite);
            retirar(acertos, i);
            insere(acertos, i, palpite);
            achou = true;
            }catch(const char* erro){
                cout<<erro<<endl;
            }
        }
    }
    if(achou){contAcertos++;}
}


void preencherAcertos(ListaCircular<char> &acertos, ListaCircular<char> palavra){ // Preenche a lista de acertos com uma underline para cada letra na palavra.
    for(int i = 1; i<=tamanho(palavra);i++){
        insere(acertos, 1, '_');
    }
}


string selecionaPalavra(string nomeArq) { // Pega a palavra aleatóriamente do arquivo de texto informado

    ListaCircular<string> palavras;

    cria(palavras);

    ifstream arquivo(nomeArq);

    if (arquivo.is_open()) {
        string linha;

        while (getline(arquivo, linha)) {
            insere(palavras,tamanho(palavras)+1,linha);
        }

        arquivo.close();
    } else {
        throw "Erro na funcao selecionaPalavra: Nao foi possivel ler o arquivo ou ele nao foi encontrado";
    }

    srand(time(NULL));

    int linha = rand()% (tamanho(palavras))+1;

    string palavra = recElem(palavras,linha);

    destroi(palavras);

    return palavra;
}


void insereLetras(ListaCircular<char>& lista, string palavra){ // Insere as letras da palavra em uma lista de chars.
    for(int i = 1;i<=palavra.size();i++){
        insere(lista,i,palavra[i-1]);
    }
}


void desenha_boneco(int vidas) { // Desenha o boneco levando em conta 5 vidas. nao precisava mas fica mais legal com.
    cout << "  +---+" << endl;
    cout << "  |   |" << endl;
    if (vidas <= 5) cout << "  O   |" << endl;
    else cout << "      |" << endl;

    if (vidas <= 3) cout << " /|\\  |" << endl;
    else if (vidas == 4) cout << " /|   |"<<endl;
    else if (vidas == 5) cout << "  |   |" << endl;
    else cout << "      |" << endl;

    if (vidas <= 1) cout << " / \\  |" << endl;
    else if (vidas == 2) cout << " /    |" << endl;
    else cout << "      |" << endl;

    cout << "      |" << endl;
    cout << "=========" << endl;
}


void mostraForca(ListaCircular<char> acertos, string tentativas, int numTentativas,int contAcertos){ // Mostra como está o estado do jogo.
    cout<<"FORCA: ";
    mostraListaLinear(acertos);

    cout<<endl;
    tentativas.size() > 0 ? cout<<"Voce ja tentou as letras: "<<tentativas<<endl : cout<<"Voce ainda nao tentou nenhuma letra!"<<endl;
    cout<<"Jogador: "<<endl;
    desenha_boneco(6-numTentativas+contAcertos);
    cout<<"Vidas: "<<5-numTentativas+contAcertos<<endl;
}


bool validaPalpite(string palpite,string tentativas){ // Valida se o palpite realmente tem apenas uma letra.
    if (palpite.size() != 1 || !isalpha(palpite[0])) return false;

    for(int i = 0;i<tentativas.size();i++){
        if (tolower(palpite[0]) == tentativas[i]){
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
    while(true){
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
        int contAcertos = 0;
        ListaCircular<char> acertos;

        cria(acertos);
        preencherAcertos(acertos, letras);

        while(true){
            if (!elemExiste(acertos,'_')){
                cout<<"Parabens! Voce acertou a palavra: "<< palavra << endl;
                destroi(letras);
                destroi(acertos);
                break;
            }else if(numTentativas-contAcertos==5){
                desenha_boneco(5-numTentativas+contAcertos);
                cout<<"Voce perdeu! A palavra era : "<< palavra <<endl;
                destroi(letras);
                destroi(acertos);
                break;
            }
            string palpite = "";

            mostraForca(acertos,tentativas,numTentativas,contAcertos);

            cout<<"Faca sua tentativa: ";
            getline(cin,palpite);

            if (validaPalpite(palpite,tentativas)){
                tentativas += palpite + ", ";
                numTentativas++;
                verificaAcertos(letras, palpite[0], acertos, contAcertos);
            }
            else{
                cout<<"Valor informado e invalido ou ja foi informado!"<<endl;
                continue;
            }

        }
        char jogar;
        cout << "digite S se deseja jogar novamente. ";
        cin.get(jogar);
        cin.ignore();
        if(toupper(jogar)!='S'){
            break;
        }

    }

}
