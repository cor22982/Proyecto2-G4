/*
*----------------------------------------
* PROYECTO 2 GRUPO 4
* ---------------------------------------
* UNIVERSIDAD DEL VALLE DE GUATEMALA
* CC3086 - Programacion de Microprocesadores
* Temario: 4 - Estudio de tiempos y movimientos de ventanillas de LA VAS
* ---------------------------------------
*
* Mathew Cordero 22982
* Josue Say 22801
* Abby Donis 22440
* Carlos Valladares 221164
*----------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <iostream>
using namespace std;
#define tiempo_compass 5 //5 mintuos compass.
#define tiempo_efectivo 10 //10 minutos efectivo. 
int *compass, *efectivo;
int carros_compass;
int carros_efectivo;
int *tiempos_efectivo, *tiempos_compass;
int tiempoTotal;
int Ttiempo;

//void atencion_efectivo();
void atencion(int carros,int *array,string tipo,int *tiempos,int tipo_tiempo);
void sumaTiempos();
void llenartiempos();
int main (){
    //Pedimos los datos que necesitamos. 
    cout << "Ingrese el numero de carros que usan compass: ";
    cin >> carros_compass;
    cout << "Ingrese el numero de carros que usan efectivo: ";
    cin >> carros_efectivo;

    // procedemos a declararlos.
    compass = new int[carros_compass];
    efectivo = new int[carros_efectivo];
    tiempos_efectivo = new int[3];
    tiempos_compass = new int[3];

    llenartiempos();
    atencion(carros_compass, compass, "compass", tiempos_compass, tiempo_compass);
    atencion(carros_efectivo, efectivo, "efectivo", tiempos_efectivo, tiempo_efectivo);
    sumaTiempos();
    
    
}

/// @brief funcion que atiende a los carros. 
/// @param carros 
/// @param array 
/// @param tipo 
/// @param tiempos 
/// @param tipo_tiempo 
void atencion(int carros,int *array,string tipo,int *tiempos,int tipo_tiempo){
    int n = carros;
    tiempos[0]=0;
    tiempos[1]=0;
    tiempos[2]=0;

    // ---------------- PARALLEL FOR LOGICA DE IMPRESION DE LOS KIOSKOS.
    // n es el numero de carros ya sea de tipo compass o efectivo. 
    #pragma omp parallel for
    for (int i = 0; i < n; i++) {
        int kisko = i % 3;
        kisko +=1;
        #pragma omp critical
        {
            cout << "\nEl carro: " << array[i]+1 << " es atendido en el kisko " << kisko << " de tipo " << tipo << " SOY EL HILO " << omp_get_thread_num() << endl;
        }
    }
    
}

/// @brief funcion que suma todos los tiempos e imprime el tiempo total 
void sumaTiempos(){
    int suma = 0;
    #pragma omp parallel for reduction(+:suma)
    for (int i = 0; i < 3; i++) {
        suma += tiempos_efectivo [i]+tiempos_compass[i];
    } 
    cout <<"\nEl tiempo en total para atender a "<<carros_compass<< " carros compass y "<<carros_efectivo<<" carros efectivo es de: "<<suma<< endl;
}

void llenartiempos(){
    // llenando de los punteros.
    #pragma omp parallel for 
    for (int i =0;i<carros_compass;i++){
        compass[i] = i;
    }

    #pragma omp parallel for
    for (int i =0;i<carros_efectivo;i++){
        efectivo[i] = i;
    }
}