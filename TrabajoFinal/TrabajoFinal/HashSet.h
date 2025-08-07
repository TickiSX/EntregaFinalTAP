#pragma once

#include "HashTableChaining.h"
#include <iostream>
using namespace std;

/*
  HashSet<T> extiende HashTableChaining<T> para impedir elementos duplicados.
  - Aprovecha la estructura de encadenamiento de HashTableChaining.
  - Sobrescribe (override) el método Add para verificar duplicados antes de insertar.
  - Si el elemento ya existe (Contains devuelve true), no lo inserta.
  - Las demás funciones se heredan sin cambios.
*/

template <typename T>
class HashSet : public HashTableChaining<T>
{
public:
    // Constructor que simplemente llama al constructor de la clase base,
    // reservando el arreglo de listas enlazadas para la tabla hash.
    HashSet(unsigned int size)
        : HashTableChaining<T>(size)
    {
    }

    // Override del método Add para evitar insertar elementos duplicados.
    void Add(T element) override
    {
        // Solo agregamos el elemento si no existe ya en la tabla.
        if (!this->Contains(element))
        {
            // Invoca la implementación Add de la clase base para la inserción.
            HashTableChaining<T>::Add(element);
        }
        /*else
        {
          // Si el elemento ya está, no hacemos nada.
        }*/
    }
};
