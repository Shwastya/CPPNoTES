#include "debugTools.h"
/*----------------------------- Listas Enlazadas ------------------------------

Una lista enlazada consta  de un número de nodos con 2 (campos),  un enlace al 
siguiente nodo de la lista y un valor, que puede ser de cualquier tipo. pueden
Las listas enlazadas pueden dividirse en cuatro categorias:

    1. Listas Simplemente Enlazadas: (recorridos directos)
       "Cada nodo contiene un unico enlace que conecta ese nodo al siguiente"	

        ┌───────┬────-┐    ┌───────┬────-┐    ┌───────┬────-┐	 ┌───────┬────-┐
        │Dato 1 │  p* │-──>│Dato 2 │  p* │-──>│Dato 3 │  p* │-──>│Dato 4 │  p* │
        └───────┴───-─┘    └───────┴───-─┘    └───────┴───-─┘	 └───────┴───-─┘
        
    2. Listas Doblemente Enlazadas: (recorridos directos e inversos) 
       "Cada nodo contiene dos enlaces, uno al anterior y otro al posterior" 

        ┌───────┬────-┐───>┌───────┬────-┐-──>┌───────┬────-┐-──>┌───────┬────-┐
        │Dato 1 │  p* │    │Dato 2 │  p* │    │Dato 3 │  p* │    │Dato 4 │  p* │
        └───────┴───-─┘<───└───────┴───-─┘<───└───────┴───-─┘<───└───────┴───-─┘

    3. Lista Circular Simplemente Enlazada: (recorrido circular en anillo)
       "El ultimo elemento (cola) se enlaza al primero (cola)"       

        ┌───────┬────-┐    ┌───────┬────-┐    ┌───────┬────-┐	 ┌───────┬────-┐
     ┌─>│Dato 1 │  p* │-──>│Dato 2 │  p* │-──>│Dato 3 │  p* │-──>│Dato 4 │  p* │─┐
     │  └───────┴───-─┘    └───────┴───-─┘    └───────┴───-─┘	 └───────┴───-─┘ │
     └───────────────────────────────────────────────────────────────────────────┘ 

    4. Lista Circular Doblemente Enlazada: (recorrido en anillo directa e inversa)
       "El ultimo elemento (cola) se enlaza al primero (cola) y viceversa"

     ┌────────────────────────────────────────────────────────────────────────────┐
     └──┌───────┬────-┐───>┌───────┬────-┐-──>┌───────┬────-┐-──>┌───────┬────-┐<─┘
        │Dato 1 │  p* │    │Dato 2 │  p* │    │Dato 3 │  p* │    │Dato 4 │  p* │
     ┌─>└───────┴───-─┘<───└───────┴───-─┘<───└───────┴───-─┘<───└───────┴───-─┘──┐
     └────────────────────────────────────────────────────────────────────────────┘

     Hay 4 operaciones fundamentales en listas enlazadas:
      
       1. Insertar elementos
       2. Mostrar elementos
       3. Buscar un elemento
       4. Eliminar un elemento
*/
struct Node
{
   int Dato;
   Node* Next;
};

void pushIncreasingLista(Node*& lista, int dato);
void pushDecreasingLista(Node*& lista, int dato);

void printLista(Node*& lista);

int  findDatoLista  (Node*& lista, int dato);
void deleteDatoLista(Node*& lista, int dato);
void eliminarLista  (Node*& lista);

int main()
{    
   {
      Node* lista = nullptr;

      int dato[6]{ 5, 3, 6, 1, 3, 8 };

      // PUSH DATOS TO COLA
      std::cout << "\n (push) elements to Lista(List) ordenada\n\n";
      for (int i = 0; i < 6; ++i) pushIncreasingLista(lista, dato[i]);

      // Print
      printLista(lista);

      // ENCONTRAR DATO (caso True)
      int deleteDato = findDatoLista(lista, 6);

      // DELETE DATO
      deleteDatoLista(lista, deleteDato);
      // Print for delete check
      printLista(lista);

      // DELETE ALL LIST
      eliminarLista(lista);
   }
   MemoryUsage();
}

void pushIncreasingLista(Node*& lista, int dato)    // PUSH DATOS A PILA:
{
   Node* newNode = new Node();                  // 1. Crear un nuevo nodo
   newNode->Dato = dato;                        // 2. Asignar a un newNode->Dato el dato a hacer push
                                                // 3. Crear 2 nodos auxiliares
   Node* aux1 = lista;                          //    se asigna el Nodo lista al primero de ellos  
   Node* aux2 = nullptr; // temp                //    el otro se reserva
                                                
   while (aux1 != nullptr && aux1->Dato < dato) // 4. Insertar el elemento a la lista (de forma ordenada y ascendete)         
   {                                            //    tendremos 3 casos: 1. Lista->Null, 2. Lista->Nodo->Null, 3. Lista->Nodo->Nodo->Null   
      aux2 = aux1;                              //    para hacerlo mas facil, en esta funcion, cada vez que insertemos un nuevo elemento 
      aux1 = aux1->Next;                        //    este se hara de forma ordenada y ascendete,   
   }
                                                //    tendremos dos casos
   if (lista == aux1) lista = newNode;          //
   else aux2->Next = newNode;

   newNode->Next = aux1;

   std::cout << "\tLista(List) <-- (push)Increasing " << dato << " correctly\n";
}


void pushDecreasingLista(Node*& lista, int dato)
{
   Node* newNode = new Node();                  // 1. Crear un nuevo nodo
   newNode->Dato = dato;                        // 2. Asignar a un newNode->Dato el dato a hacer push
   // 3. Crear 2 nodos auxiliares
   Node* aux1 = lista;                          //    se asigna el Nodo lista al primero de ellos  
   Node* aux2 = nullptr; // temp                //    el otro se reserva

   while (aux1 != nullptr && aux1->Dato > dato) // 4. Insertar el elemento a la lista (de forma ordenada y ascendete)         
   {                                            //    tendremos 3 casos: 1. Lista->Null, 2. Lista->Nodo->Null, 3. Lista->Nodo->Nodo->Null   
      aux2 = aux1;                              //    para hacerlo mas facil, en esta funcion, cada vez que insertemos un nuevo elemento 
      aux1 = aux1->Next;                        //    este se hara de forma ordenada y ascendete,   
   }
   //    tendremos dos casos
   if (lista == aux1) lista = newNode;          
   else aux2->Next = newNode;

   newNode->Next = aux1;

   std::cout << "\tLista(List) <-- (push)Decreasing " << dato << " correctly\n";
}

void printLista(Node*& lista)
{
   Node* auxNod = lista;
   std::cout << "\n Print Lista(List) ordenada\n\n";
   while (lista != nullptr)
   {
      std::cout << "\tPrint:" << lista->Dato << "\n";
      lista = lista->Next;
   }
   lista = auxNod;
}

int findDatoLista(Node*& lista, int dato)
{
   Node* actual = lista;

   while (actual != nullptr && actual->Dato <= dato)
   {
      if (actual->Dato == dato)
      {            
         std::cout << "\nSe ha encontrado " << actual->Dato << " en lista\n";
         const int dataFound = actual->Dato;
         actual = lista;
         return dataFound;
      }
      actual = actual->Next;
   }
   actual = lista;
   std::cout << "\nNO Se ha encontrado " << dato << " en lista\n";
   return dato;
}

void deleteDatoLista(Node*& lista, int dato)
{
   if (lista != nullptr)
   {
      Node* auxDelete = nullptr;
      Node* previous  = nullptr;

      auxDelete = lista;

      // recorrer lista
      while (auxDelete != nullptr && auxDelete->Dato != dato)
      {
         previous = auxDelete;
         auxDelete = auxDelete->Next;
      }

      // el elemento no ha sido encontrado
      if (auxDelete == nullptr) std::cout << "No se ha encontrado el dato a borrar\n";

      // el primer dato es el que vamos a eliminar
      else if(previous == nullptr)   
      {
          std::cout << "\nSe ha borrado " << dato << "\n";
          lista = lista->Next;
          delete auxDelete;
      }
      // el elemento está en la lista pero no es el primer nodo
      else 
      {
          std::cout << "\nSe ha borrado " << dato << "\n";
          previous->Next = auxDelete->Next;
          delete auxDelete;
      }
   }
}

void eliminarLista(Node*& lista)
{
   

   while (lista != nullptr)
   {
      Node* aux = lista;
      lista = aux->Next;
      delete aux;
        
   }
}
