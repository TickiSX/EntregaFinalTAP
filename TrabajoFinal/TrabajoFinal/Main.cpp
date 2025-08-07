#include <iostream>
#include "HashTableChaining.h"
#include "HashSet.h"  // Asumiendo que guardaste el HashSet en este archivo

using namespace std;

void HashTableChainingExample()
{
    cout << "Ejemplo con HashTableChaining<int>" << endl;

    HashTableChaining<int> table(10);

    // Insertar algunos elementos
    table.Add(15);
    table.Add(25);
    table.Add(35);
    table.Add(5);
    table.Add(15); // Duplicado permitido en HashTableChaining

    cout << "Contenido de la tabla:" << endl;
    table.Print();

    // Buscar un elemento
    cout << "Contiene 25? " << (table.Contains(25) ? "Si" : "No") << endl;
    cout << "Contiene 50? " << (table.Contains(50) ? "Si" : "No") << endl;

    // Eliminar un elemento
    cout << "Eliminando 25..." << endl;
    table.Remove(25);
    cout << "Contiene 25? " << (table.Contains(25) ? "Si" : "No") << endl;

    cout << "Contenido de la tabla tras eliminacion:" << endl;
    table.Print();
}

void HashSetExample()
{
    cout << "\nEjemplo con HashSet<int>" << endl;

    HashSet<int> set(10);

    // Insertar elementos
    set.Add(15);
    set.Add(25);
    set.Add(35);
    set.Add(5);
    set.Add(15); // Intento de duplicado que debe ser ignorado

    cout << "Contenido del HashSet:" << endl;
    set.Print();

    // Buscar elementos
    cout << "Contiene 15? " << (set.Contains(15) ? "Si" : "No") << endl;
    cout << "Contiene 50? " << (set.Contains(50) ? "Si" : "No") << endl;

    // Eliminar un elemento
    cout << "Eliminando 5..." << endl;
    set.Remove(5);
    cout << "Contiene 5? " << (set.Contains(5) ? "Si" : "No") << endl;

    cout << "Contenido del HashSet tras eliminacion:" << endl;
    set.Print();
}

int main()
{
    HashTableChainingExample();
    HashSetExample();

    return 0;
}
