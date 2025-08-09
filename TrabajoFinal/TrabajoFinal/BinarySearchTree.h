#pragma once

//Mi compañero Cesar me ayudo a hacer el código de el ejercicio de BinarySearchTree

#include <iostream>
#include <stack> // necesario para DestroyIterative y PostOrderIterative
#include <utility> // para std::pair usado en PostOrderIterative
using namespace std;

#include <cmath> // Required for std::log

// Declaraciones únicamente. Las definiciones están en Utilities.cpp
double log_base_n(double x, double base);
int MinimaAlturaDeArbol(int numeroDeNodos, int maximoDeHijosPorNodo);

template <typename T>
class BinarySearchTree
{
	class TreeNode // se cambio el template de la Clase TreeNode para que sea el mismo de BinarySearchTree
    {
    public:
        TreeNode()
        {
            parent = leftChild = rightChild = nullptr;
            data = {};
        }

        TreeNode(T data)
        {
            parent = leftChild = rightChild = nullptr;
            // this se refiere a exactamente el objeto que está mandando a llamar la función. 
            this->data = data;
        }

        T data;
        // el padre de este nodo dentro del árbol. 
        // En otras palabras, this == parent.leftChild || this == parent.rightChild
        TreeNode* parent;

        // vector<TreeNode*> children; // si quisiéramos que tuviera la posibilidad de tener más de dos hijos cada nodo.
        TreeNode* leftChild;
        TreeNode* rightChild;
    };

public:
    BinarySearchTree()
    {
        root = nullptr;
        count = 0;
    }

    ~BinarySearchTree()
    {
        // destrucción segura sin recursión
        DestroyIterative();
    }

    void AddWithAddRecursive(T value)
    {
        // primero checamos si root es nullptr. 
        if (root == nullptr)
        {
            // si sí es nullptr, quiere decir que value es el primer valor en entrar, y por tanto se va a 
            // convertir en el nodo root.
            root = new TreeNode(value);
            count++;
            return; // nos salimos de la función.
        }

        TreeNode* currentNode = root;

        AddRecursive(value, currentNode);
    }

    void InsertarNode(TreeNode* currentNode, bool isLeftChild, T value)
    {
        // Crea un nuevo nodo con el valor dado y lo conecta como hijo izquierdo o derecho según isLeftChild
        TreeNode* newNode = new TreeNode(value);
        newNode->parent = currentNode;
        if (isLeftChild)
            currentNode->leftChild = newNode;
        else
            currentNode->rightChild = newNode;
        count++;
    }

    void AddRecursive(T value, TreeNode* currentNode)
    {
        // Inserta recursivamente el valor en la posición adecuada del árbol binario de búsqueda
        if (value > currentNode->data)
        {
            // Si el valor es mayor que el del nodo actual, se intenta insertar en el subárbol derecho
            if (currentNode->rightChild == nullptr)
            {
                InsertarNode(currentNode, false, value);
                return;
            }
            else
            {
                // Si ya hay hijo derecho, se continúa recursivamente hacia ese lado
                return AddRecursive(value, currentNode->rightChild);
            }
        }
        else // value <= currentNode->data, se inserta a la izquierda (incluye iguales)
        {
            // Si el valor es menor o igual, se intenta insertar en el subárbol izquierdo
            if (currentNode->leftChild == nullptr)
            {
                InsertarNode(currentNode, true, value);
                return;
            }
            else
            {
                // Si ya hay hijo izquierdo, se continúa recursivamente hacia ese lado
                return AddRecursive(value, currentNode->leftChild);
            }
        }
    }

    void Add(T value)
    {
        // Inserta el valor iterativamente en la posición correcta, sin usar recursión
        if (root == nullptr)
        {
            root = new TreeNode(value);
            count++;
            return;
        }

        TreeNode* currentNode = root;

        // Mientras no encontremos un lugar vacío para insertar el nuevo nodo
        while (currentNode != nullptr)
        {
            if (value > currentNode->data)
            {
                if (currentNode->rightChild == nullptr)
                {
                    InsertarNode(currentNode, false, value);
                    return;
                }
                else
                {
                    currentNode = currentNode->rightChild;
                }
            }
            else
            {
                if (currentNode->leftChild == nullptr)
                {
                    InsertarNode(currentNode, true, value);
                    return;
                }
                else
                {
                    currentNode = currentNode->leftChild;
                }
            }
        }
    }

    void InOrderWithRecursive()
    {
        // Imprime los valores del árbol en orden ascendente (izquierda, raíz, derecha)
        InOrderRecursive(root);
    }

    int MinimaAltura()
    {
        // Calcula la mínima altura teórica para un árbol con count nodos y máximo 2 hijos por nodo
        return MinimaAlturaDeArbol(count, 2);
    }

    // Es el nodo raíz desde el cual el árbol es capaz de llegar a cualquier otro nodo en el árbol.
    TreeNode* root;

    // cuántos nodos en total tiene el árbol.
    int count;

    // cuántos niveles de profundidad tiene el árbol.
    // int depth;

    // Versión recursiva de búsqueda
    bool SearchWithRecursive(T value)
    {
        TreeNode* resultNode = SearchRecursive(root, value);
        return resultNode != nullptr;
    }

    // IMPLEMENTACIÓN "Search" iterativa
    TreeNode* SearchIterative(T value)
    {
        TreeNode* current = root;
        // Recorremos repetitivamente el árbol buscando el valor deseado
        while (current != nullptr)
        {
            if (value == current->data)
                return current;
            else if (value < current->data)
                current = current->leftChild;
            else // value > current->data
                current = current->rightChild;
        }
        return nullptr; // No se encontró el valor
    }

    // Bool iterativo
    bool Search(T value)
    {
        // Retorna true si el valor existe en el árbol (usando búsqueda iterativa)
        return SearchIterative(value) != nullptr;
    }

    void Delete(T value)
    {
        // Corroboramos que existe un nodo con el value dado.
        TreeNode* nodeToDelete = SearchRecursive(root, value);

        if (nodeToDelete == nullptr)
        {
            cout << "no existe el valor value en este árbol." << endl;
            return;
        }

        // caso 1: el nodo no tiene hijos.
        if (nodeToDelete->leftChild == nullptr &&
            nodeToDelete->rightChild == nullptr)
        {
            // Nodo hoja, se desconecta de su padre o si es raíz, se limpia root
            if (nodeToDelete->parent)
            {
                if (nodeToDelete->parent->leftChild == nodeToDelete)
                    nodeToDelete->parent->leftChild = nullptr;
                else
                    nodeToDelete->parent->rightChild = nullptr;
            }
            else
            {
                root = nullptr;
            }

            count--;
            delete nodeToDelete;
            return;
        }

        // caso 2: tiene un solo hijo derecho.
        if (nodeToDelete->leftChild == nullptr && nodeToDelete->rightChild != nullptr)
        {
            // Reemplaza el nodo por su hijo derecho y actualiza los punteros padre-hijo
            if (nodeToDelete->parent)
            {
                if (nodeToDelete->parent->leftChild == nodeToDelete)
                    nodeToDelete->parent->leftChild = nodeToDelete->rightChild;
                else
                    nodeToDelete->parent->rightChild = nodeToDelete->rightChild;
            }
            else
            {
                root = nodeToDelete->rightChild;
            }

            nodeToDelete->rightChild->parent = nodeToDelete->parent;
            delete nodeToDelete;
            count--;
            return;
        }

        // caso 2: tiene un solo hijo izquierdo.
        if (nodeToDelete->leftChild != nullptr && nodeToDelete->rightChild == nullptr)
        {
            // Reemplaza el nodo por su hijo izquierdo y actualiza los punteros padre-hijo
            if (nodeToDelete->parent)
            {
                if (nodeToDelete->parent->leftChild == nodeToDelete)
                    nodeToDelete->parent->leftChild = nodeToDelete->leftChild;
                else
                    nodeToDelete->parent->rightChild = nodeToDelete->leftChild;
            }
            else
            {
                root = nodeToDelete->leftChild;
            }

            nodeToDelete->leftChild->parent = nodeToDelete->parent;
            delete nodeToDelete;
            count--;
            return;
        }

        // caso 3: tiene dos hijos
        // Buscamos el sucesor in-order para reemplazar el nodo a borrar
        TreeNode* successorNode = Successor(nodeToDelete);  // Nunca es nulo porque el nodo tiene dos hijos

        // Reubicamos el subárbol izquierdo al sucesor
        successorNode->leftChild = nodeToDelete->leftChild;
        if (nodeToDelete->leftChild)
            nodeToDelete->leftChild->parent = successorNode;

        // Reorganizamos la posición original del sucesor, desconectándolo de su padre
        if (successorNode->parent)
        {
            if (successorNode->parent->leftChild == successorNode)
                successorNode->parent->leftChild = successorNode->rightChild;
            else
                successorNode->parent->rightChild = successorNode->rightChild;
        }
        if (successorNode->rightChild)
            successorNode->rightChild->parent = successorNode->parent;

        // Reubicamos el subárbol derecho al sucesor
        successorNode->rightChild = nodeToDelete->rightChild;
        if (nodeToDelete->rightChild)
            nodeToDelete->rightChild->parent = successorNode;

        // Reconectamos el sucesor con el padre original del nodo a borrar
        successorNode->parent = nodeToDelete->parent;
        if (nodeToDelete->parent)
        {
            if (nodeToDelete->parent->leftChild == nodeToDelete)
                nodeToDelete->parent->leftChild = successorNode;
            else
                nodeToDelete->parent->rightChild = successorNode;
        }
        else
        {
            root = successorNode;
        }

        count--;
        delete nodeToDelete;
    }

    void PostOrderIterative()
    {
        if (root == nullptr)
            return;

        // Usamos dos pilas para simular recursión y obtener el recorrido postorden iterativo
        std::stack<TreeNode*> stack1;
        std::stack<TreeNode*> stack2;

        // Empezamos con la raíz
        stack1.push(root);

        // El primer stack sirve para recorrer nodos en orden raíz, derecha, izquierda (modificado)
        while (!stack1.empty())
        {
            TreeNode* node = stack1.top();
            stack1.pop();

            // Lo guardamos en el segundo stack; al final stack2 contendrá nodos en orden postorden real
            stack2.push(node);

            // Empujamos primero el hijo izquierdo, luego el derecho,
            // para que al invertir stack2 se mantenga el orden postorden: izquierda, derecha, raíz
            if (node->leftChild)
                stack1.push(node->leftChild);
            if (node->rightChild)
                stack1.push(node->rightChild);
        }

        // Finalmente vaciamos stack2 para imprimir el recorrido postorden
        while (!stack2.empty())
        {
            TreeNode* node = stack2.top();
            stack2.pop();
            cout << node->data << endl;
        }
    }

private:
    TreeNode* TreeMaximum()
    {
        // empezamos en la raíz y le pedimos el máximo desde ahí.
        return Maximum(root);
    }

    // Nos da el máximo a partir de node como raíz.
    TreeNode* Maximum(TreeNode* node)
    {
        TreeNode* maximum = node;
        // nos vamos todo a la derecha hasta que el hijo derecho sea nullptr.
        while (maximum->rightChild != nullptr)
            maximum = maximum->rightChild;

        return maximum;
    }

    // el mínimo valor T en todo el árbol.
    TreeNode* TreeMinimum()
    {
        return Minimum(root);
    }

    // Nos da el mínimo a partir de node como raíz.
    TreeNode* Minimum(TreeNode* node)
    {
        TreeNode* minimum = node;
        // nos vamos todo a la izquierda hasta que el hijo izquierdo sea nullptr.
        while (minimum->leftChild != nullptr)
            minimum = minimum->leftChild;

        return minimum;
    }

    TreeNode* MinimumWithRecursive()
    {
        return MinimumRecursive(root);
    }

    TreeNode* MinimumRecursive(TreeNode* currentNode)
    {
        if (currentNode->leftChild == nullptr)
            return currentNode;
        return MinimumRecursive(currentNode->leftChild);
    }

    TreeNode* Successor(TreeNode* node)
    {
        if (node->rightChild != nullptr)
            return Minimum(node->rightChild); // El sucesor es el mínimo del subárbol derecho

        TreeNode* ancestor = node->parent;
        // Subimos mientras el nodo sea hijo derecho, buscando el primer ancestro que sea padre izquierdo
        while (ancestor != nullptr && node == ancestor->rightChild)
        {
            node = ancestor;
            ancestor = node->parent;
        }
        return ancestor;
    }

    // lo mismo que Successor, pero invertimos Right por Left, y Minimum por maximum.
    TreeNode* Predecessor(TreeNode* node)
    {
        if (node->leftChild != nullptr)
            return Maximum(node->leftChild); // El predecesor es el máximo del subárbol izquierdo

        TreeNode* ancestor = node->parent;
        // Subimos mientras el nodo sea hijo izquierdo, buscando el primer ancestro que sea padre derecho
        while (ancestor != nullptr && node == ancestor->leftChild)
        {
            node = ancestor;
            ancestor = node->parent;
        }
        return ancestor;
    }

    TreeNode* SearchRecursive(TreeNode* currentNode, T value)
    {
        if (currentNode == nullptr)
            return nullptr;
        if (currentNode->data == value)
            return currentNode;

        if (value < currentNode->data)
            return SearchRecursive(currentNode->leftChild, value);

        return SearchRecursive(currentNode->rightChild, value);
    }

    void InOrderRecursive(TreeNode* node)
    {
        if (node != nullptr)
        {
            InOrderRecursive(node->leftChild);
            cout << node->data << endl;
            InOrderRecursive(node->rightChild);
        }
    }

    void PreOrderRecursive(TreeNode* node)
    {
        if (node != nullptr)
        {
            cout << node->data << endl;
            PreOrderRecursive(node->leftChild);
            PreOrderRecursive(node->rightChild);
        }
    }

    void PostOrderRecursive(TreeNode* node)
    {
        if (node != nullptr)
        {
            PostOrderRecursive(node->leftChild);
            PostOrderRecursive(node->rightChild);
            cout << node->data << endl;
        }
    }

    // Destruye el árbol de forma iterativa siguiendo post-order: izquierda, derecha, nodo.
    void DestroyIterative()
    {
        if (root == nullptr)
            return;

        stack<TreeNode*> st;
        st.push(root);

        while (!st.empty())
        {
            TreeNode* node = st.top();

            // Si es hoja (ambos hijos ya fueron procesados o nunca existieron), lo borramos.
            if (node->leftChild == nullptr && node->rightChild == nullptr)
            {
                st.pop();
                delete node;
            }
            else
            {
                // Si tiene hijo derecho, lo empujamos y lo desconectamos para que sea tratado luego como hoja.
                if (node->rightChild)
                {
                    st.push(node->rightChild);
                    node->rightChild = nullptr;
                }
                // Igual con el hijo izquierdo.
                if (node->leftChild)
                {
                    st.push(node->leftChild);
                    node->leftChild = nullptr;
                }
            }
        }

        root = nullptr;
        count = 0;
    }

};
