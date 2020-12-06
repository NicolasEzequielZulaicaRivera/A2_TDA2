#include "abb.h"
#include "pa2m.h"
#include <stdio.h>
#include <string.h>

typedef struct cosa{
    int clave;
    char contenido[10];
}cosa;

cosa* crear_cosa(int clave){

    //static int count = 0;
    char aux [50];
    sprintf(aux,"CONT %i",clave);
    cosa* c = (cosa*)malloc(sizeof(cosa));
    if(c){
        c->clave = clave;
        strcpy( c->contenido , aux );
    }
    return c;
}

void destruir_cosa(cosa* c){
    free(c);
}
int comparar_cosas(void* elemento1, void* elemento2){
    if(!elemento1 || !elemento2)
        return 0;

    if(((cosa*)elemento1)->clave>((cosa*)elemento2)->clave)
        return 10;
    if(((cosa*)elemento1)->clave<((cosa*)elemento2)->clave)
        return -10;
    return 0;
}
void destructor_de_cosas(void* elemento){
    if(!elemento)
        return;
    destruir_cosa((cosa*)elemento);
}

bool mostrar_elemento(void* elemento, void* extra){
    extra=extra; //para que no se queje el compilador, gracias -Werror -Wall
    if(elemento)
        printf("%i ", ((cosa*)elemento)->clave);
    return false;
}
bool mostrar_hasta_5(void* elemento, void* extra){
    extra=extra; //para que no se queje el compilador, gracias -Werror -Wall
    if(elemento){
        printf("%i ", ((cosa*)elemento)->clave);
        if(((cosa*)elemento)->clave == 5)
            return true;
    }
    return false;
}
bool mostrar_acumulado(void* elemento, void* extra){
    if(elemento && extra){
        *(int*)extra += ((cosa*)elemento)->clave;
        printf("%i ", *(int*)extra);
    }
    return false;
}
void mini_pruebas_originales(){

  abb_t* arbol = arbol_crear(comparar_cosas, destructor_de_cosas);

  cosa* c1= crear_cosa(1);
  cosa* c2= crear_cosa(2);
  cosa* c3= crear_cosa(3);
  cosa* c4= crear_cosa(4);
  cosa* c5= crear_cosa(5);
  cosa* c6= crear_cosa(6);
  cosa* c7= crear_cosa(7);
  cosa* auxiliar = crear_cosa(0);

  arbol_insertar(arbol, c4);
  arbol_insertar(arbol, c2);
  arbol_insertar(arbol, c6);
  arbol_insertar(arbol, c1);
  arbol_insertar(arbol, c3);
  arbol_insertar(arbol, c5);
  arbol_insertar(arbol, c7);

  printf("El nodo raiz deberia ser 4: %s\n", ((cosa*)arbol_raiz(arbol))->clave==4?"SI":"NO");

  auxiliar->clave = 5;
  printf("Busco el elemento 5: %s\n", ((cosa*)arbol_buscar(arbol, auxiliar))->clave==5?"SI":"NO");

  auxiliar->clave = 7;
  printf("Borro nodo hoja (7): %s\n", (arbol_borrar(arbol, auxiliar))==0?"SI":"NO");

  auxiliar->clave = 6;
  printf("Borro nodo con un hijo (6): %s\n", (arbol_borrar(arbol, auxiliar))==0?"SI":"NO");

  auxiliar->clave = 2;
  printf("Borro nodo con dos hijos (2): %s\n", (arbol_borrar(arbol, auxiliar))==0?"SI":"NO");

  auxiliar->clave = 4;
  printf("Borro la raiz (4): %s\n", (arbol_borrar(arbol, auxiliar))==0?"SI":"NO");

  auxiliar->clave = 3;
  printf("Busco el elemento (3): %s\n", ((cosa*)arbol_buscar(arbol, auxiliar))->clave==3?"SI":"NO");

  cosa* elementos[10];

  printf("Recorrido inorden (deberian salir en orden 1 3 5): ");
  size_t cantidad = arbol_recorrido_inorden(arbol, (void**)elementos, 10);
  for(size_t i=0;i<cantidad;i++)
      printf("%i ", elementos[i]->clave);
  printf("\n");

  printf("\n\nInserto mas valores y pruebo el iterador interno\n\n");
  arbol_insertar(arbol, crear_cosa(15));
  arbol_insertar(arbol, crear_cosa(0));
  arbol_insertar(arbol, crear_cosa(9));
  arbol_insertar(arbol, crear_cosa(7));
  arbol_insertar(arbol, crear_cosa(4));


  printf("Recorrido inorden iterador interno: ");
  abb_con_cada_elemento(arbol, ABB_RECORRER_INORDEN, mostrar_elemento, NULL);
  printf("\n");

  printf("Recorrido preorden iterador interno: ");
  abb_con_cada_elemento(arbol, ABB_RECORRER_PREORDEN, mostrar_elemento, NULL);
  printf("\n");

  printf("Recorrido postorden iterador interno: ");
  abb_con_cada_elemento(arbol, ABB_RECORRER_POSTORDEN, mostrar_elemento, NULL);
  printf("\n");

  printf("\nRecorrido inorden hasta encontrar el 5: ");
  abb_con_cada_elemento(arbol, ABB_RECORRER_INORDEN, mostrar_hasta_5, NULL);
  printf("\n");

  printf("Recorrido preorden hasta encontrar el 5: ");
  abb_con_cada_elemento(arbol, ABB_RECORRER_PREORDEN, mostrar_hasta_5, NULL);
  printf("\n");

  printf("Recorrido postorden hasta encontrar el 5: ");
  abb_con_cada_elemento(arbol, ABB_RECORRER_POSTORDEN, mostrar_hasta_5, NULL);
  printf("\n");

  int acumulador=0;
  printf("\nRecorrido inorden acumulando los valores: ");
  abb_con_cada_elemento(arbol, ABB_RECORRER_INORDEN, mostrar_acumulado, &acumulador);
  printf("\n");

  acumulador=0;
  printf("Recorrido preorden acumulando los valores: ");
  abb_con_cada_elemento(arbol, ABB_RECORRER_PREORDEN, mostrar_acumulado, &acumulador);
  printf("\n");

  acumulador=0;
  printf("Recorrido postorden acumulando los valores: ");
  abb_con_cada_elemento(arbol, ABB_RECORRER_POSTORDEN, mostrar_acumulado, &acumulador);
  printf("\n");

  free(auxiliar);
  arbol_destruir(arbol);

  return;
}

int comparar_int(void* elemento1, void* elemento2){

  if( *(int*)elemento1 > *(int*)elemento2 )
    return 1;
  if( *(int*)elemento1 < *(int*)elemento2 )
    return -1;
  return 0;
}
bool acumular_int(void* num, void* extra ){
  *(int*)extra += *(int*)num;
  return 0;
}

void mostrar_cosas_inorder( nodo_abb_t* nodo ){

  if(!nodo) return;
  mostrar_cosas_inorder( nodo->izquierda );
  printf("%i\n", ((cosa*)(nodo->elemento))->clave );
  mostrar_cosas_inorder( nodo->derecha );
}

void mostrar_int_inorder( nodo_abb_t* nodo ){

  if(!nodo) return;
  mostrar_int_inorder( nodo->izquierda );
  printf("%i ",  *(int*)(nodo->elemento) );
  mostrar_int_inorder( nodo->derecha );
}

void pruebas_caja_blanca(){

  abb_t* abb = arbol_crear(comparar_int, NULL);

  int num[10];
  for(int i=0;i<10;i++) num[i]=i;

  arbol_insertar( abb, &num[4] );//      4      |
  arbol_insertar( abb, &num[2] );//    /  \     |
  arbol_insertar( abb, &num[6] );//   2   6     |
  arbol_insertar( abb, &num[1] );//  /\  /\     |
  arbol_insertar( abb, &num[3] );// 1 3 5 7     |
  arbol_insertar( abb, &num[5] );
  arbol_insertar( abb, &num[7] );

  pa2m_afirmar(
    *(int*)abb->nodo_raiz->elemento  == 4 &&
    *(int*)abb->nodo_raiz->izquierda->elemento  == 2 &&
    *(int*)abb->nodo_raiz->derecha->elemento  == 6 &&
    *(int*)abb->nodo_raiz->izquierda->izquierda->elemento  == 1 &&
    *(int*)abb->nodo_raiz->izquierda->derecha->elemento  == 3 &&
    *(int*)abb->nodo_raiz->derecha->izquierda->elemento  == 5 &&
    *(int*)abb->nodo_raiz->derecha->derecha->elemento  == 7
  ,"arbol_insertar");



  arbol_borrar( abb, &num[4] );//         3     |
  arbol_borrar( abb, &num[2] );//       /  \    |
  arbol_borrar( abb, &num[7] );//      1   6    |
  arbol_borrar( abb, &num[0] );//      \  /     |
  arbol_insertar( abb, &num[2] );//    2 5      |

  pa2m_afirmar(
    *(int*)abb->nodo_raiz->elemento  == 3 &&
    *(int*)abb->nodo_raiz->izquierda->elemento  == 1 &&
    *(int*)abb->nodo_raiz->derecha->elemento  == 6 &&
    *(int*)abb->nodo_raiz->izquierda->derecha->elemento  == 2 &&
    *(int*)abb->nodo_raiz->derecha->izquierda->elemento  == 5
  ,"arbol_borrar");

  arbol_destruir( abb );
}

void pruebas_funcionamiento(){

  abb_t* abb = arbol_crear(comparar_int, NULL);

  pa2m_afirmar(arbol_vacio(abb),"arbol_vacio (vacio)");

  int num[15];
  for(int i=0;i<15;i++) num[i]=i;

  arbol_insertar( abb, &num[4] );//      4      |
  arbol_insertar( abb, &num[2] );//    /  \     |
  arbol_insertar( abb, &num[6] );//   2   6     |
  arbol_insertar( abb, &num[1] );//  /\  /\     |
  arbol_insertar( abb, &num[3] );// 1 3 5 7     |
  arbol_insertar( abb, &num[5] );
  arbol_insertar( abb, &num[7] );

  pa2m_afirmar(!arbol_vacio(abb),"arbol_vacio (no vacio)");
  pa2m_afirmar( arbol_raiz(abb)==&num[4] ,"arbol_raiz");

  bool correcto = true;
  nodo_abb_t* aux;

  // elementos que deben estar
  for(int i=1;i<=7;i++){
    aux = arbol_buscar( abb, &num[i] );
    if( aux ) correcto = correcto && !abb->comparador( aux, &num[i] );
    else correcto = false;
  }
  // elementos que no deben estar
  for(int i=8;i<10;i++){
    aux = arbol_buscar( abb, &num[i] );
    if( aux ) correcto = false;
  }
  aux = arbol_buscar( abb, &num[0] );
  if( aux ) correcto = false;

  pa2m_afirmar(correcto,"buscar elementos tras insertar");


  arbol_borrar( abb, &num[4] );//         3     |
  arbol_borrar( abb, &num[2] );//       /  \    |
  arbol_borrar( abb, &num[7] );//      1   6    |
  arbol_borrar( abb, &num[0] );//      \  /     |
  arbol_insertar( abb, &num[2] );//    2 5      |

  // elementos que deben estar
  for(int i=1;i<=3;i++){
    aux = arbol_buscar( abb, &num[i] );
    if( aux ) correcto = correcto && !abb->comparador( aux, &num[i] );
    else correcto = false;
  }
  for(int i=5;i<=6;i++){
    aux = arbol_buscar( abb, &num[i] );
    if( aux ) correcto = correcto && !abb->comparador( aux, &num[i] );
    else correcto = false;
  }
  // elementos que no deben estar
  for(int i=7;i<10;i++){
    aux = arbol_buscar( abb, &num[i] );
    if( aux ) correcto = false;
  }
  aux = arbol_buscar( abb, &num[0] );
  if( aux ) correcto = false;
  aux = arbol_buscar( abb, &num[4] );
  if( aux ) correcto = false;


  pa2m_afirmar(correcto,"buscar elementos tras borrar");

  //arbol_borrar( abb, &num[4] );           3         |
  //arbol_borrar( abb, &num[2] );         /  \        |
  //arbol_borrar( abb, &num[7] );        1   6        |
  //arbol_borrar( abb, &num[0] );       /\  / \       |
  //arbol_insertar( abb, &num[2] );    0 2 5   8      |
  arbol_insertar( abb, &num[8] );//       \   / \     |
  arbol_insertar( abb, &num[7] );//        4 7  10    |
  arbol_insertar( abb, &num[10] );//           /      |
  arbol_insertar( abb, &num[9] );//           9       |
  arbol_insertar( abb, &num[4] );//                   |
  arbol_insertar( abb, &num[0] );//                   |

  // elementos que deben estar
  for(int i=10;i>=0;i--){
    aux = arbol_buscar( abb, &num[i] );
    if( aux ) correcto = correcto && !abb->comparador( aux, &num[i] );
    else correcto = false;
    arbol_borrar( abb, aux );
  }
  correcto = correcto && arbol_vacio(abb);

  pa2m_afirmar(correcto,"buscar elementos (extra)");

  arbol_destruir( abb );
}

void pruebas_recorrido(){

  abb_t* abb = arbol_crear(comparar_int, NULL);

  int num[10];
  for(int i=0;i<10;i++) num[i]=i;

  arbol_insertar( abb, &num[4] );//      4      |
  arbol_insertar( abb, &num[2] );//    /  \     |
  arbol_insertar( abb, &num[6] );//   2   6     |
  arbol_insertar( abb, &num[1] );//  /\  /\     |
  arbol_insertar( abb, &num[3] );// 1 3 5 7     |
  arbol_insertar( abb, &num[5] );
  arbol_insertar( abb, &num[7] );

  bool correcto = true;
  size_t tamanio;

  int* array[10];
  for( int i=0; i<10; i++ ) array[i] = &num[0];

  tamanio = arbol_recorrido_inorden( abb , (void**)array, 10);

  for( int i=0; i<7; i++ )
    correcto = correcto && ( *array[i] == i+1 );
  for( int i=7; i<10; i++ )
    correcto = correcto && ( *array[i] == 0 );

  correcto = correcto && tamanio==7;

  pa2m_afirmar(correcto,"Recorrido Inorden");

  for( int i=0; i<10; i++ ) array[i] = &num[0];

  tamanio = arbol_recorrido_inorden( abb , (void**)array, 4);

  for( int i=0; i<4; i++ )
    correcto = correcto && ( *array[i] == i+1 );
  for( int i=4; i<10; i++ )
    correcto = correcto && ( *array[i] == 0 );

  correcto = correcto && tamanio==4;

  pa2m_afirmar(correcto,"Recorrido Inorden ( Array Insuficiente ) ");


  for( int i=0; i<10; i++ ) array[i] = &num[0];

  tamanio = arbol_recorrido_preorden( abb , (void**)array, 10);

  pa2m_afirmar(
      *array[0]==4 &&
      *array[1]==2 &&
      *array[2]==1 &&
      *array[3]==3 &&
      *array[4]==6 &&
      *array[5]==5 &&
      *array[6]==7 &&
      *array[7]==0 &&
      *array[8]==0 &&
      *array[9]==0
  ,"Recorrido Preorden ");

  for( int i=0; i<10; i++ ) array[i] = &num[0];

  tamanio = arbol_recorrido_preorden( abb , (void**)array, 4);

  pa2m_afirmar(
      *array[0]==4 &&
      *array[1]==2 &&
      *array[2]==1 &&
      *array[3]==3 &&
      *array[4]==0 &&
      *array[5]==0 &&
      *array[6]==0 &&
      *array[7]==0 &&
      *array[8]==0 &&
      *array[9]==0
  ,"Recorrido Preorden ( Array Insuficiente ) ");

  for( int i=0; i<10; i++ ) array[i] = &num[0];

  tamanio = arbol_recorrido_postorden( abb , (void**)array, 10);

  pa2m_afirmar(
      *array[0]==1 &&
      *array[1]==3 &&
      *array[2]==2 &&
      *array[3]==5 &&
      *array[4]==7 &&
      *array[5]==6 &&
      *array[6]==4 &&
      *array[7]==0 &&
      *array[8]==0 &&
      *array[9]==0
  ,"Recorrido Postorden ");

  for( int i=0; i<10; i++ ) array[i] = &num[0];

  tamanio = arbol_recorrido_postorden( abb , (void**)array, 4);

  pa2m_afirmar(
      *array[0]==1 &&
      *array[1]==3 &&
      *array[2]==2 &&
      *array[3]==5 &&
      *array[4]==0 &&
      *array[5]==0 &&
      *array[6]==0 &&
      *array[7]==0 &&
      *array[8]==0 &&
      *array[9]==0
  ,"Recorrido Postorden ( Array Insuficiente ) ");

  int n1=0,n2=0,n3=0;
  size_t m1=0,m2=0,m3=0;

  m1 = abb_con_cada_elemento( abb, ABB_RECORRER_INORDEN , acumular_int , &n1 );
  m2 = abb_con_cada_elemento( abb, ABB_RECORRER_PREORDEN , acumular_int , &n2 );
  m3 = abb_con_cada_elemento( abb, ABB_RECORRER_POSTORDEN , acumular_int , &n3 );

  pa2m_afirmar(
      m1==m2 && m2==m3 && m3==7 &&
      n1==n2 && n2==n3 && n3==1+2+3+4+5+6+7
  ,"abb_con_cada_elemento");

  arbol_destruir( abb );
}

void pruebas_arbol_vacio(){
  abb_t* abb = arbol_crear(comparar_int, NULL);

  int num = 0;

  pa2m_afirmar(
    arbol_borrar( abb, &num ) == -1 &&
    !arbol_buscar( abb, &num ) &&
    !arbol_raiz( abb ) &&
    arbol_vacio( abb )
  ,"operaciones basicas");

  int* vec[10];
  pa2m_afirmar(
    !arbol_recorrido_inorden(abb,(void**)vec,10) &&
    !arbol_recorrido_preorden(abb,(void**)vec,10) &&
    !arbol_recorrido_postorden(abb,(void**)vec,10) &&
    !abb_con_cada_elemento( abb, ABB_RECORRER_INORDEN , acumular_int , &num ) &&
    !abb_con_cada_elemento( abb, ABB_RECORRER_PREORDEN , acumular_int , &num ) &&
    !abb_con_cada_elemento( abb, ABB_RECORRER_POSTORDEN , acumular_int , &num )
  ,"operaciones de recorrido");

  arbol_destruir( abb );
}

void pruebas_busqueda(){
  abb_t* abb = arbol_crear(comparar_cosas, destructor_de_cosas);

  cosa* elem[100];
  for( int i = 0; i<100 ; i++ ) elem[i]=crear_cosa(i);

  for( int i = 0; i<5 ; i++ )
    arbol_insertar(abb, crear_cosa(5) );
  for( int i = 0; i<5 ; i++ )
    arbol_insertar(abb, crear_cosa(10) );
  for( int i = 0; i<5 ; i++ )
    arbol_insertar(abb, crear_cosa(0) );

  arbol_insertar(abb, crear_cosa(50) );
  arbol_insertar(abb, crear_cosa(0) );
  arbol_insertar(abb, crear_cosa(40) );
  arbol_insertar(abb, crear_cosa(1) );
  arbol_insertar(abb, crear_cosa(30) );
  arbol_insertar(abb, crear_cosa(2) );
  arbol_insertar(abb, crear_cosa(20) );

  for( int i = 0; i<100 ; i=i+5 )
    arbol_insertar(abb, crear_cosa(i) );
  for( int i = 0; i<100 ; i=i+3 )
    arbol_insertar(abb, crear_cosa(i) );
  for( int i = 0; i<100 ; i=i+2 )
    arbol_insertar(abb, crear_cosa(i) );

  for( int i = 0; i<100 ; i++ ){

    if( arbol_buscar(abb,elem[i]) ){
      if( comparar_cosas( elem[i], arbol_buscar(abb,elem[i]) ) ){
        printf("UF [- %i -]\n",i);
      }else{
        printf("%s - %s \t ", elem[i]->contenido, ((cosa*)arbol_buscar(abb,elem[i]))->contenido );
      }
    }
  }


  for( int i = 0; i<100 ; i++ ) destruir_cosa(elem[i]);

  arbol_destruir(abb);
}

void pruebas_NULL(){
  abb_t* abb = arbol_crear(comparar_int, NULL);

  int num = 0;

  arbol_destruir(NULL);

  pa2m_afirmar(
    arbol_borrar( abb, NULL ) == -1 &&
    !arbol_buscar( abb, NULL ) &&
    arbol_borrar( NULL, &num ) == -1 &&
    !arbol_buscar( NULL, &num ) &&
    !arbol_raiz( NULL ) &&
    arbol_vacio( NULL )
  ,"operaciones basicas");

  int* vec[10];
  pa2m_afirmar(
    !arbol_recorrido_inorden(abb,(void**)vec,0) &&
    !arbol_recorrido_preorden(abb,(void**)vec,0) &&
    !arbol_recorrido_postorden(abb,(void**)vec,0) &&
    !arbol_recorrido_inorden(abb,NULL,10) &&
    !arbol_recorrido_preorden(abb,NULL,10) &&
    !arbol_recorrido_postorden(abb,NULL,10) &&
    !arbol_recorrido_inorden(NULL,(void**)vec,10) &&
    !arbol_recorrido_preorden(NULL,(void**)vec,10) &&
    !arbol_recorrido_postorden(NULL,(void**)vec,10) &&
    !abb_con_cada_elemento( abb, ABB_RECORRER_INORDEN , NULL , &num ) &&
    !abb_con_cada_elemento( abb, ABB_RECORRER_PREORDEN , NULL , &num ) &&
    !abb_con_cada_elemento( abb, ABB_RECORRER_POSTORDEN , NULL , &num ) &&
    !abb_con_cada_elemento( NULL, ABB_RECORRER_INORDEN , acumular_int , &num ) &&
    !abb_con_cada_elemento( NULL, ABB_RECORRER_PREORDEN , acumular_int , &num ) &&
    !abb_con_cada_elemento( NULL, ABB_RECORRER_POSTORDEN , acumular_int , &num )
  ,"operaciones de recorrido");

  arbol_destruir( abb );
}

int main(int argc, char const *argv[]){

  if( argc == 2 && !strcmp( argv[1], "minipruebas" ) ){
    mini_pruebas_originales();
  } else {

    pa2m_nuevo_grupo("PRUEBAS DE CAJA BLANCA");
    pruebas_caja_blanca();

    pa2m_nuevo_grupo("PRUEBAS DE FUNCIONAMIENTO");
    pruebas_funcionamiento();

    pa2m_nuevo_grupo("PRUEBAS DE RECORRIDO");
    pruebas_recorrido();

    pa2m_nuevo_grupo("PRUEBAS DE ARBOL VACIO");
    pruebas_arbol_vacio();

    pa2m_nuevo_grupo("PRUEBAS DE NULL");
    pruebas_NULL();

    //pa2m_nuevo_grupo("PRUEBAS DE BUSQUEDA");
    //pruebas_busqueda();
  }
  printf("\n");
  return 0;
}
