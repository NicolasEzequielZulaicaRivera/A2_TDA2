# Arbol Binario de Busqueda

## Funcionamiento

Se crea la libreria **abb.h** con el objetivo de implementar el tipo de dato abstracto **Arbol Binario de Busqueda**

 Se define la estructura `abb_t` que actuara en conjunto con los metodos definidos en la libreria para implementar las funcionalidades esperadas de dicho TDA
 
 **Importante :** Las funciones implementadas reservan *memoria dinamica* para la utilizacion de las estructuras, por lo que es imperativo que esta se libere antes de finalizar el programa.
  Esto se realiza mediante el uso de la funcion `arbol_destruir` para cualquier arbol creado y mediante la correcta definicion del destructor de elementos.

  Se añade el archivo **minipruebas.c** como ejemplo de implementacion de la libreria tanto como para verificar su correcto funcionamiento.


## Compilacion y Ejecution

  Habiendo incluido la libreria en su programa o descargado el main.c proveido, puede compilarlo con la siguiente linea en la terminal :

  ` gcc *.c -Wall -Werror -Wconversion -std=c99 -o nombre_programa `
  > usaremos el compilador gcc nativo a cualquier distribucion linux para compilar todos los archivos c (\*.c)
    en el directorio, empleando diversos *flags* para prevenir errores,
    queda a discrecion del usuario elegir el nombre del programa

  Luego puede ejecutar el programa con la siguiente linea:

  `./nombre_programa`

  Cabe aclarar que la terminal debe encontrarse en el directorio donde se encuentran los archivos del programa para poder llevar su compilacion y ejecucion a cabo.

  Se recomienda  emplear un **makefile** para agilizar estas tareas.
  Se añade en los archivos un makefile que nos permitira usar la linea `make run` que compilara (de ser necesario) y ejecutara el programa.

---

## Explicar qué es un ABB y cómo se diferencia de un Árbol Binario.

Un arbol binario es una esctructura de datos donde cada elemento tendra una refereencia a hasta otros dos elementos ( izquierda y derecha ), que seran llamados sus hijos.
Un ABB ( Arbol Binario de Busqueda ) es un tipo de arbol binario que cumple la condicion de estar ordenado, 
de manera que todos los nodos a la derecha de un nodo cumpliran cierta condicion al compararlos ( eg. ser mayores ) y los que no iran a la izquierda. 

## Explicar cuál es el objetivo de tener una función de destrucción en el TDA y qué implicaría para el usuario no tenerla.

El objetivo de la funcion de destruccion es facilitar la liberacion de memoria dinamica que el usuario debe hacer. 
Sin ella el usuario deberia buscar el elemento que quiera eliminar, guardar una referencia, eliminarlo del arbol y luego liberar la referencia.
Implementando la funcion de destruccion, el usuario solo necesita eliminarlo del arbol y la funcion liberara la memoria, simplificando el proceso.

## ¿Cuál es la complejidad de las diferentes operaciones del ABB? Justifique.

`arbol_crear`: **O(1)**, la funcion reservara memoria para el arbol, independiente del tamaño del arbol

`arbol_insertar`: **O(N)**, el peor caso sera cuando el arbol se degenere como una lista y halla que intertar un elemento al final, por lo que habra que recorrer todos los elementos.
para un arbol balanceado la complejidad es O(logN)

`arbol_borrar`: **O(N)**, el peor caso sera cuando el arbol se degenere como una lista y halla que eliminar un elemento al final, por lo que habra que recorrer todos los elementos.
para un arbol balanceado la complejidad es O(logN)

`arbol_buscar`: **O(N)**, el peor caso sera cuando el arbol se degenere como una lista y halla que buscar un elemento al final, por lo que habra que recorrer todos los elementos.
para un arbol balanceado la complejidad es O(logN)

`arbol_raiz`: **O(1)**, devuelve el primer elemento, al que accede de manera directa, independiente del tamaño del arbol

`arbol_vacio`: **O(1)**, comprueba que exista el primer elemnto, al que accede de manera directa, independiente del tamaño del arbol 

_recorrer arbol_: **O(N)**, para recorrer el arbol debe pasar por cada uno de sus elementos

