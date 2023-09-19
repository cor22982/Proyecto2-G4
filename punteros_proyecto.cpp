/*
*------------------------------------------
* punteros_puntero.cpp
* -----------------------------------------
* UNIVERSIDAD DEL VALLE DE GUATEMALA
* FACULTAD DE INGENIERÍA
* DEPARTAMENTO DE CIENCIA DE LA COMPUTACIÓN

* CC3086 - Programacion de Microprocesadores
*
*------------------------------------------
* Descripción: ingreso de numeros para formar 
* lista y mostrar el tamaño del puntero.
*
*------------------------------------------
*/
#include <iostream>
using namespace std;

int *numeros;
int listSize;

int main(){
    cout << "Ingresar numero: "; //texto de prueba, cambiar despúes
    cin >> listSize; 
    numeros = new int[listSize];

    for (int i = 0; i<=listSize; i++){
           numeros[i] = i;
    }

    cout << "Lista de numeros del 0 al tamano de la lista:" << endl; //texto de prueba, cambiar despues
    for (int i = 0; i<=listSize; i++) {
        cout << numeros[i] << " ";
    }
    cout << "\nEl tamano del puntero es: " << *numeros << endl; //texto de prueba, cambiar despues

    delete[] numeros;
}