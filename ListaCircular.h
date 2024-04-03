#ifndef LISTACIRCULAR_H_INCLUDED
#define LISTACIRCULAR_H_INCLUDED

#include <iostream>
using namespace std;

template <typename T> struct Nodo {
  T elemento;
  Nodo<T> *proximo;
  Nodo<T> *anterior;
};

template <typename T> struct ListaCircular { // A lista trabalha com posições lógicas, ou seja, o primeiro elemento está na posição 1 e assim por diante.
  int cardinalidade;
  Nodo<T> *inicio;
  Nodo<T> *fim;
};

template <typename T> void cria(ListaCircular<T> &lista) {
  lista.cardinalidade = 0;
  lista.inicio = NULL;
  lista.fim = NULL;
}

template <typename T> void destroi(ListaCircular<T> &lista) {
  while (lista.cardinalidade>0){
    retirar(lista,lista.inicio->elemento);// poderia ser feita de uma forma com melhor performance, mas na minha opinião dessa forma fica muito mais limpo
  }
  lista.cardinalidade = 0;
}

template <typename T> bool elemExiste(ListaCircular<T> lista, T elem) {
  Nodo<T>* p;
  p = lista.inicio;
  for(int i = 1; i <= lista.cardinalidade; i++){
    if (p->elemento == elem){
      return true;
    }
    p = p->proximo;
  }
  return false;
}

template <typename T> bool posValida(ListaCircular<T> lista, int posicao){
  return (posicao <= lista.cardinalidade+1 && posicao >= 1); // basicamente confere se se tem elemento na posição informada
}

template <typename T> int recPos(ListaCircular<T> lista, T elem) {
  Nodo<T>* p;
  p = lista.inicio;
  int pos = 1;
  while(pos<=lista.cardinalidade) {
    if (p->elemento == elem){
      return pos;
    }
    pos++;
    p = p->proximo;
  }
  throw "Erro na funcao recPos: Elemento nao esta na lista!";// caso não achar o elemento retorna -1, pois -1 não pode ser uma posição.
}

template <typename T> T recElem(ListaCircular<T> lista, int pos) {
  if (!posValida(lista,pos)) throw "Erro na funcao recElem: posicao invalida!";
  Nodo<T>* p;
  p = lista.inicio;
  int i=1;
  while(i != pos) {
    i++;
    p = p->proximo;
  }
  return p->elemento;
}

template <typename T> Nodo<T>* recRefPos(ListaCircular<T> lista, int pos) { // rec = recupera, Ref = referenia, Pos = por meiro da posição
  if (!posValida(lista,pos)) throw "Erro na funcao recRefPos: posicao invalida";
  Nodo<T>* p;
  p = lista.inicio;
  int i=1;
  while(i != pos) {
    i++;
    p = p->proximo;
  }
  return p;
} // ao inves de retornar o elemento ou a posição retorna direto a referencia do elemento. Essa função é uam função auxiliar, utilizada apenas dentro de outras funções

template <typename T> void mostraLista(ListaCircular<T> lista){
  int i =1;
  while(i<=lista.cardinalidade){
    cout<<"Elemento "<< i << "= " << recElem(lista,i) << endl; // numera os elementos e mostra eles na tela.
    i++;
  }
  if(i==1) cout<<"Essa lista está vazia"<<endl;
}

template<typename T> void insere(ListaCircular<T> &lista, int pos, T elem){ // TRATAR OVERFLOW

  if (!posValida(lista,pos)) throw "Erro na funcao insere: posicao invalida!";

  Nodo<T>* novo = new Nodo<T>; // cria o novo elemento e adiciona define o valor dele.
  novo->elemento = elem;

  if (lista.cardinalidade == 0){ // caso a lista esteja vazia o primeiro elemento aponta para ele mesmo em ambos os lados
    novo->proximo = novo;
    novo->anterior = novo;
    lista.inicio = novo;
    lista.fim = novo;
  }else if(pos == 1){ // tratando o caso de inserção no inicio
    novo->proximo = lista.inicio;
    novo->anterior = lista.fim;
    lista.fim->proximo = novo;
    lista.inicio->anterior = novo;
    lista.inicio = novo;
  }else if(pos == lista.cardinalidade+1){ // tratando o caso de inserção no final
    novo->proximo = lista.inicio;
    novo->anterior = lista.fim;
    lista.fim->proximo = novo;
    lista.fim = novo;
    lista.inicio->anterior = novo;
  }else{ // tratando demais casos, ou seja, inserção no meio.
    Nodo<T>* p;

    p = recRefPos(lista,pos-1);

    novo->proximo = p->proximo;
    novo->anterior = p;
    p->proximo->anterior = novo;
    p->proximo = novo;
  }
  lista.cardinalidade++;
}

template<typename T>
void retirar(ListaCircular<T> &lista, T elem){ // TRATAR UNDERFLOW
  int pos = recPos(lista, elem); // pegando a posição do elemento, posicao ja esta sendo validada dentro dessa funcao

  Nodo<T>* removido = recRefPos(lista, pos); // recuperando o endereço do Nodo que será removido com base na posição
  if(lista.cardinalidade == 1){ // tratando cada caso de retirada de elemento, procurei deixar a lógica bem explicita
    lista.inicio = NULL;
    lista.fim = NULL;
  }else if (pos == 1){
    lista.fim->proximo = removido->proximo;
    lista.inicio = removido->proximo;
    lista.inicio->anterior = lista.fim;
  } else if (pos == lista.cardinalidade){
    lista.fim = removido->anterior;
    lista.inicio->anterior = lista.fim;
    lista.fim->proximo = lista.inicio;
  }else{
    removido->anterior->proximo = removido->proximo;
    removido->proximo->anterior = removido->anterior;
  }
  delete removido;
  lista.cardinalidade--;
}


#endif // LISTACIRCULAR_H_INCLUDED
