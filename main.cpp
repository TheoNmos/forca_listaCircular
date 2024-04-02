#include <iostream>
#include "ListaCircular.h"

using namespace std;

int main() {
  // só pra testar as funções básicas da lista.
  ListaCircular<int> lista1;
  ListaCircular<char> lista2;

  cria(lista1);
  cria(lista2);

try{
  insere(lista1,1,9);
  insere(lista1, 1, 10);
  insere(lista1, 3, 11);
  insere(lista1, 2, 88);
  insere(lista1, 3, 77);
  insere(lista1, 1, 99);
  insere(lista1, 4, 55555);

}catch(const char* erro){ // só pra ilustrar como tratar os 'throw' usados na implementação da lista.
    cout<<erro<< endl;
}

  mostraLista(lista1);
  cout<<endl;

  retirar(lista1, 77);

  mostraLista(lista1);
  retirar(lista1, 99);
  retirar(lista1, 11);
  cout<<endl;
  mostraLista(lista1);

  cout<<endl;
  insere(lista2, 1, 'a');
  mostraLista(lista2);

  destroi(lista1);
  destroi(lista2);
}
