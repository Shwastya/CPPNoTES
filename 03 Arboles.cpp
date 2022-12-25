#include "debugTools.h"

/*────────────────────── Concepto de Arbol binario ───────────────────────────-
* 
  Un árbol  consta de un conjunto finito  de elementos,  denominados nodos  y un 
  conjunto finito de líneas dirigidas, denominadas ramas, que conectan los nodos.
 
                              ┌────┬────────┬────┐
                              │ p* | Node A │ p* │--> Raiz 
                              └────┴────────┴────┘
                                /              \
                               /                \
                    ┌────┬────────┬────┐┌────┬────────┬────┐
                    │ p* | Node B │ p* ││ p* | Node C │ p* │--> Nodo hijo y padre
                    └────┴────────┴────┘└────┴────────┴────┘               
                      /                   /              \
                     /                   /                \
           ┌────┬────────┬────┐┌────┬────────┬────┐┌────┬────────┬────┐
           │ p* | Node D │ p* ││ p* | Node E │ p* ││ p* | Node F │ p* │--> Nodos hojas
           └────┴────────┴────┘└────┴────────┴────┘└────┴────────┴────┘               

  Arbol  binario  es una estructura recursiva, Se divide en tres subconjuntos:

          1. Nodo Raiz
          2. Subarbol izq.
          3. subarbol der.

  -> Arbol Binario de Busqueda (ABB):

     Es aquel  que dado un nodo,  todos los datos  del sub árbol izquierdo  son 
     menores,  mientras  que todos los datos del sub árbol derecho  son mayores.

*/
struct Node 
{
   int Data;
   Node* Left;
   Node* Right;
   Node* Parent;
};

Node* createNode(int node, Node* parent);
void pushNode(Node*& tree, int data, Node* parent);
void printTree(Node* tree, int count);
bool findData(Node* tree, int data);

// recorrido en profundiad Pre-Order
void preOrder(Node* tree);
// recorrido en profundiad In-Order
void inOrder(Node* tree);
// recorrido en profundiad Post-Order
void postOrder(Node* tree);

// eliminar un nodo
void deleteNode(Node* tree, int dato);

Node* Tree = nullptr;

int main()
{
   int data[11] { 10, 5, 3, 8, 6, 7, 9, 15, 12, 20, 30};

   for (int i = 0; i < 11; ++i) pushNode(Tree, data[i], nullptr);
   deleteNode(Tree, 5);
   deleteNode(Tree, 9);
   deleteNode(Tree, 20);
   deleteNode(Tree, 3);
   printTree(Tree, 0/* Contador a cero */);
   int n = 8;
   bool result = findData(Tree, n);

   if (result) std::cout << "\nSe ha encontrado " << n << "\n";
   else if (result) std::cout << "\nNO se ha encontrado " << n << "\n";

   std::cout << "\n\nRecorrido pre-order\n";
   preOrder(Tree);
   std::cout << "\n\nRecorrido in-order\n";
   inOrder(Tree);
   std::cout << "\n\nRecorrido post-order\n";
   postOrder(Tree);

   //std::cout << "\n\neliminamos 9\n";
   //deleteNode(Tree, 9);
   //printTree(Tree, 0/* Contador a cero */);
}

Node* createNode(int node, Node* parent)
{
   Node* newNode { new Node() };
   newNode->Data = node;
   newNode->Parent = parent;
   newNode->Left = nullptr;
   newNode->Right = nullptr;
   return newNode;
}

void pushNode(Node*& tree, int data, Node* parent)
{
   // cuando el arbol esta vacio, creamos un nuevo nodo
   if (tree == nullptr)
   {
      Node* newNode = createNode(data, parent);
      tree = newNode;
   }
   // si el arbol tiene un nodo o mas
   else 
   {
      int treeData { tree->Data }; // obtenemos el valor del dato de la raiz

      // si el elemento es mayor a la raiz, insertamos en izquierdo
      if (data < treeData) pushNode(tree->Left, data, tree);
      // si el elemento es menos a la raiz, insertamos en derecho
      else pushNode(tree->Right, data, tree);
   }
}

void printTree(Node* tree, int count)
{
   if (tree == nullptr) return;
   else 
   {
      printTree(tree->Right, count++);
      for (int i = 0; i < count; ++i)
      {
         std::cout << "   ";
      }
      std::cout << tree->Data << std::endl;
      printTree(tree->Left, count++);
   }  
}

bool findData(Node* tree, int data)
{
   if (tree == nullptr) return false;
   else if (tree->Data = data) return true;
   else if (data < tree->Data) return findData(tree->Left, data);
   else return findData(tree->Right, data);
}

void preOrder(Node* tree)
{   
   if (tree == nullptr) return;
   else 
   {
      std::cout << tree->Data << " - ";
      preOrder(tree->Left);
      preOrder(tree->Right);
   }
}

void inOrder(Node* tree)
{   
   if (tree == nullptr) return;
   else
   {
      inOrder(tree->Left);
      std::cout << tree->Data << " - ";      
      inOrder(tree->Right);
   }
}

void postOrder(Node* tree)
{
   if (tree == nullptr) return;
   else
   {
      postOrder(tree->Left);
      postOrder(tree->Right);
      std::cout << tree->Data << " - ";        
   }
}

// funcion para determinar el nodo mas izq posible
Node* minime(Node* tree)
{
   if (tree == nullptr) return nullptr;
   // si tiene hijo izq
   if (tree->Left) return minime(tree->Left);
   // si no tiene hijo izq, retornamos el mismo nodo
   else return tree;
}
void replace(Node* tree, Node* newNode)
{
   if (tree->Parent) // si el arbol tiene padre
   {
      // arbol->padre, hay que asignarle su nuevo hijo
      if (tree->Data == tree->Parent->Left->Data)
      {
         tree->Parent->Left = newNode;
      }
      else if (tree->Data == tree->Parent->Right->Data)
      {
         tree->Parent->Right = newNode;
      }
   }
   if (newNode) // si existe el nuevo nodo
   {
      // procedemos a asignarle su nuevo padre
      newNode->Parent = tree->Parent;
   }
}
void destroyNode(Node* node)
{
   node->Left = nullptr;
   node->Right = nullptr;
   delete node;
}
void deleteSelectedNode(Node* deletenode)
{
   if (deletenode->Left && deletenode->Right) // si tiene hijos izq y der
   {
      Node* menor = minime(deletenode->Right);
      deletenode->Data = menor->Data;
      deleteSelectedNode(menor);
   }
   else if (deletenode->Left) // si tiene hijo izq
   {
      replace(deletenode, deletenode->Left);
      destroyNode(deletenode);
   }
   else if (deletenode->Right)
   {
      replace(deletenode, deletenode->Right);
      destroyNode(deletenode);
   }
   else 
   { 
      replace(deletenode, nullptr);  
      destroyNode(deletenode); 
   }
}
void deleteNode(Node* tree, int dato)
{
   if (tree == nullptr) return; // si el valor esta vacio
   // si el valor es menor, busca por la izq
   else if (dato < tree->Data) deleteNode(tree->Left, dato);
   // si el valor es mayor, busca por la der
   else if (dato > tree->Data) deleteNode(tree->Right, dato);
   // si ya encontraste el valor
   else deleteSelectedNode(tree);
}
