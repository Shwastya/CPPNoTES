#include <iostream>
#include <cstdint>
/*--------------------- Colas FIFO (First In First Out) -----------------------

 Node (frente)  	Node	  	      Node		  		Node (final)		  
┌───────────-─┐    ┌───────────-─┐    ┌───────────-─┐   ┌───────────-─┐   
│ dato		  │    │ dato		 │    │ dato		│   │ dato		  │   
├────────────-┤	   ├────────────-┤	  ├────────────-┤	├────────────-┤	  
│ Node next*  ├-──>│ Node next*  ├-──>│ Node next*  ├-->│ Node next*  ├
└───────────-─┘	   └───────────-─┘	  └───────────-─┘	└───────────-─┘	   

Una cola en programación con C++ es una estructura de datos, caracterizada por 
ser una secuencia  de elementos  en la que la operación de inserción (push) se 
realiza por el final  y  la extracción (pop) por el frente. conocido como FIFO
(First In First Out) (primero en entrar primero en salir.

A diferencia de las pilas,  en las colas el primero en hacer push es el primero 
en ser atendido,se insertan por el final y se sacan por el frente, fin de cola.
*/

struct Node
{
	int	  Dato {};
	Node* Next { nullptr };
};


void pushCola(Node*& front, Node*& end, int dato); // PUSH DATOS A COLA
void popCola(Node*& front, Node*& end, int& dato);  // POP DATOS DE COLA (eliminar)

int main()
{
	Node* front = nullptr;
	Node* end   = nullptr;

	// PUSH DATOS TO COLA
	std::cout << "\n (push) elements to Cola(Queue)\n\n";
	for (uint8_t dato = 0; dato < 6; ++dato) pushCola(front, end, dato);

	// POP DATOS DE COLA
	std::cout << "\n (pOP) elements from Cola(Queue)\n\n";	
	while (front != nullptr)
	{
		int dato{};
		popCola(front, end, dato);
		std::cout << "\tCola(Queue) --> (pop) " << dato << " correctly \n";
	}	
}

void pushCola(Node*& front, Node*& end, int dato)	// PUSH DATO A COLA
{
	Node* newNodo = new Node();				// 1.  Crear espacio en memoria para almacenar un nodo.
	newNodo->Dato = dato;					// 2.  Asignar ese nuevo nodo al dato que queremos insertar.
	newNodo->Next = nullptr;				//	   Siguiente apuntará a NULL

	// si cola vacia						// 3.  Asignar a los punteros frente y fin hacia el nuevo nodo
	if (front == nullptr) front = newNodo;	//	   Si cola vacia, frente = nuevo nodo
	else end->Next = newNodo;				//	   Si cola NO vacia, ya hay un nodo en la cola end->Next = nuevo nodo

	end = newNodo;							//	   Ponemos en end el nuevo nodo

	std::cout << "\tCola(Queue) <-- (push) " << dato << " correctly\n";
}

void popCola(Node*& front, Node*& end, int& dato)	// POP DATOS A COLA : (sacar el dato de la pila, eliminar)
{
	dato = front->Dato;				// 1. Obtener el valor del nodo
	Node* auxNode = front;			// 2. Crear un nodo auxiliar y asignarle el frente de la cola
	
	if (front == end)				// 3. Eliminar el nodo del frente de la cola
	{								//    (caso en que solo hay un elemento) si front == end, solo hay un elemento 
		front = nullptr;			//	  poniendo front a nullptr
		end   = nullptr;			//	  y poniendo end a nullptr
	}
	else							//    (en caso de que haya mas de un nodo)
	{								
		front = front->Next;		//	  entonces front apunta a siguiente (Next)
	}				
	delete auxNode;					// 4. por ultimo podemos borrar del nodo (pop)				
}
