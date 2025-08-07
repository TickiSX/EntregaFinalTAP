#pragma once

#include <iostream>
#include <forward_list> 
#include <string>
using namespace std;

template <typename T>
class HashTableChaining
{
    // un lugar donde almacenar los datos
    // un arreglo de N forward_lists, donde cada una corresponde a un índice de la hash table.
    forward_list<T>* data;
    unsigned int arraySize;
    // unsigned = SIN signo, es decir, no puede ser negativo.

    // size_t // es solamente un int de 64 bits unsigned (no-negativo).
    // originalmente, se supone que es el tamaño estándar de las variables (direcciones de memoria) que maneja en el sistema operativo.

public:

    HashTableChaining(unsigned int size)
    {
        // pedimos memoria para nuestras N listas.
        data = new forward_list<T>[size];
        arraySize = size;
    }

    virtual ~HashTableChaining()
    {
        // liberamos la memoria pedida para el arreglo de listas enlazadas para evitar leaks
        delete[] data;
    }

    // necesitan una función hash, que es la que mapea desde una llave hacia un índice
    // es una función que toma un valor del tipo T y lo convierte en un entero
    int HashFunction(T key)
    {
        // usamos módulo con el tamaño del arreglo para asegurar que el índice esté dentro del rango válido
        return key % arraySize;
    }

    // métodos de insertar, quitar, buscar e iterar.
    // Se declara como virtual para permitir que clases derivadas, como HashSet, puedan sobrescribir este método y personalizar su comportamiento
    virtual void Add(T element)
    {
        int index = HashFunction(element);
        // agregamos el elemento al inicio de la lista en la posición 'index'
        // push_front es eficiente, O(1), sin importar el tamaño de la lista
        data[index].push_front(element);

        // arraySize = 10
        // element = 39
        // int index = HashFunction(element); nos da 9
        // data[index] = element; nos daría que data[9] = 39
    }

    // aquí, remove SÍ es lineal en el aspecto de que crece conforme crece la cantidad de elementos guardados,
    // pero no es directamente 'n', si no que es "n/arraySize" (en el caso promedio), lo cual la hace un poco mejor.
    void Remove(T element)
    {
        int index = HashFunction(element);
        forward_list<T>& listAtIndex = data[index];
        // recorremos la lista enlazada del índice correspondiente buscando el elemento
        for (auto i : listAtIndex) // esto es básicamente un foreach
        {
            if (i == element)
            {
                // quitamos este elemento y salimos de la función.
                // la función remove de forward_list elimina todas las apariciones iguales, aquí solo queremos la primera que encontramos.
                listAtIndex.remove(i);
                return;
            }
        }
        // si no se encontró el elemento, lanzamos una excepción para notificar error
        throw runtime_error("no element " + to_string(element) + " in this hash table.");

        //var myVar = 3.1415f;
        //var myVar2 = "hola ,mundo";
        //var myHashTable = HastTableChaining();
    }

    // contains es la función de búsqueda.
    bool Contains(T element)
    {
        int index = HashFunction(element);
        forward_list<T>& listAtIndex = data[index];
        // recorremos la lista en el índice y verificamos si contiene el elemento
        for (auto i : listAtIndex) // esto es básicamente un foreach
        {
            if (i == element)
            {
                // encontramos el elemento y salimos de la función con true
                return true;
            }
        }
        // si no se encontró el elemento en la lista, regresamos false
        return false;
    }

    void Print()
    {
        // vamos a iterar por cada uno de los índices
        for (int i = 0; i < arraySize; i++)
        {
            cout << "lista del índice: " << std::to_string(i) << ": ";
            // en cada índice hay una lista, entonces iteramos en toda la lista.
            for (auto j : data[i]) // recuerden, este for con auto nos itera la lista de inicio a fin.
                cout << j << ", ";

            cout << endl;
        }
    }

    //void Print()
    //{

    //}
};

void HashTableChainingExample();
