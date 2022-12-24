#include <iostream>
#include <cstdint>
/*------------------------- Pilas LIFO (Last In Firts Out) ----------------------

 Node (cima)	  Una pila  (stack en inglés)  es una lista ordenada o estructura 
┌─────────────┐   de datos en la que el modo de acceso a sus elementos es de tipo 
│ dato        │   LIFO (Last In First Out,último en entrar, primero en salir) que 
├─────────────┤	  permite almacenar y recuperar datos.  Esta estructura se aplica 
│ Node next*  │	  en multitud de ocasiones en el área de  informática debido a su 
└──────┬──────┘	  simplicidad y  ordenación  implícita  de  la propia estructura.
 Node  |
┌─────────────┐   Las operaciones habituales son push and pop,  se puede ver como
│ dato        │   un pila de platos, en el que el primer elemento es el plato que
├─────────────┤   que esta abajo (push), y el ultimo elemento, y  primero  en ser
│ Node next*  │   quitado (ultimo puesto en la pila) es el plato de arriba (pop).
└──────┬──────┘
 Node  |
┌─────────────┐
│ dato        │
├─────────────┤
│ Node next*  │
└─────────────┘
*/

struct Node
{
   int   Dato {};
   Node* Next { nullptr };
};

void pushPila	(Node*& pila, int  dato);	// PUSH DATOS A PILA
void popPila	(Node*& pila, int& dato);	// POP DATOS DE PILA (eliminar dato)
void printPila  (Node*& pila);

int main()
{
   Node* pila = nullptr;

   // PUSH DATOS TO PILA	
   std::cout << "\n (push) elements to Pila(Stack)\n\n";
   for (int dato = 1; dato < 6; ++dato) pushPila(pila, dato);		
	
   // Print
   printPila(pila);

   // POP DATOS FROM PILA (and delete Node)
   std::cout << "\n (pop) elements from Pila(Stack)\n\n";
   while (pila != nullptr)
    {
       int popDato{};
       popPila(pila, popDato);		
    }
   std::cout << "\n";
   return 0;
}

void pushPila(Node*& pila, int dato)	// PUSH DATOS A PILA :
{
	
   Node* newNode = new Node();		// 1. Reservar espacio en memoria para almacenar un nodo.
   newNode->Dato = dato;			// 2. Cargar el valor dentro del nodo(dato).
   newNode->Next = pila;			// 3. Cargar el puntero pila dentro del nodo siguiente.
   pila = newNode;                  // 4. Asignar el nuevo nodo a pila.

   std::cout << "\tPila(Stack) <-- (push) " << dato << " correctly\n";
}

void popPila(Node*& pila, int& dato)	// TAKE DATOS A PILA : (sacar el dato de la pila, eliminar)
{
	
   Node* auxNode = pila;			// 1. Crear una variable auxiliar de tipo nodo e igualarlo a pila.
   dato = auxNode->Dato;			// 2. n debe ser igual al dato de el auxiliar que coge por ref.
   pila = auxNode->Next;			// 3. como n se va a eliminar hay que indivar que pila apunte al siguiente
   delete auxNode;                  // 4. por ultimo podemos borrar del nodo

   std::cout << "\tPila(Stack) --> (pop) " << dato << " correctly \n";
}

void printPila(Node*& pila)
{
	Node* auxNod = pila;
	std::cout << "\n Print Pila(Stack)\n\n";
	while (pila != nullptr)
	{
		std::cout << "\tPrint:" << pila->Dato << "\n";
		pila = pila->Next;
	}
	pila = auxNod;
}