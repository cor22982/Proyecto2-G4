// Librerias
#include <iostream>
#include <pthread.h>
#include <ctime>
#include <cmath>
#include <omp.h>
#include <unistd.h>
using namespace std;

// Cantidad de estaciones para pago por "COMPASS"
#define estaciones_compass 3
// Cantidad de estaciones para pago por "EFECTIVO"
#define estaciones_efectivo 3
// Cantidad de estaciones para pago por "COMPASS"
#define tiempo_compass 0
// Cantidad de estaciones para pago por "EFECTIVO"
#define tiempo_efectivo 2

// Cantidad de carros que usan el método de pago "COMPASS" y "EFECTIVO"
int carros_compass, carros_efectivo;
// Hilos encargados para simular el método de pago de los kioscos "COMPASS" y "EFECTIVO"
pthread_t hilo_compass, hilo_efectivo;

/**
 * Estructura Parametros
 * Estructura que sirve como parámetros para el funcionamiento de la función "atencion"
 * @param bandera, tiempo de tardanza según el tipo de kiosco (COMPASS o EFECTIVO)
 * @param cant_carros, cantidad de carros por atender
 * @param tiempo_promedio, tiempo promedio en atender cada kiosco al total de carros
 * @param tiempo_total, tiempo total de atención de toda la cantidad de carros
 * @param tiempo_individual, tiempo individual de cada carro
 */
struct Parametros
{
    bool bandera;
    int cant_carros;
    double tiempo_total;
    double tiempo_promedio;
    double tiempo_individual;

};

/**
 * Función atención
 * Se encarga de atender los carros
 */
void *atencion(void *arg)
{

    // Obtener parámetros de interes
    Parametros *params = (Parametros *)arg;
    bool usar_tiempo_rapido = params->bandera;
    int carros = params->cant_carros;

    clock_t start_time = clock(); // Marca de tiempo inicial

    // Simular el tiempo de procesamiento para cada carro dependiendo del kiosco
    int tiempo_espera;
    if (usar_tiempo_rapido)
    {
        // Tiempo de procesamiento rápido
        tiempo_espera = tiempo_compass; // Ajusta el tiempo según tus necesidades
    }
    else
    {
        // Tiempo de procesamiento lento
        tiempo_espera = tiempo_efectivo; // Ajusta el tiempo según tus necesidades
    }

    for (int i = 1; i <= carros; i++)
    {

        #pragma omp sections
        {

            #pragma omp section
            { 
                if(i <= carros){
                    cout<< "El carro "<<i<<" esta siendo atendido por el trabajador "<< omp_get_thread_num()<<endl; 
                }
                // Simular el tiempo de pago
                sleep(tiempo_espera);
            }

            #pragma omp section
            { 
                if(i <= carros){
                    cout<< "El carro "<<i+1<<" esta siendo atendido por el trabajador "<< omp_get_thread_num()<<endl; 
                }
                // Simular el tiempo de pago
                sleep(tiempo_espera);
            }

            #pragma omp section
            { 
                if(i <= carros){
                    cout<< "El carro "<<i+2<<" esta siendo atendido por el trabajador "<< omp_get_thread_num()<<endl; 
                }
                // Simular el tiempo de pago
                sleep(tiempo_espera);  
            }    
        }
        // Incrementar i después de ejecutar las tres secciones
    if (i <= carros - 2) {
        i += 2; // Incrementar en 2 si hay al menos 3 carros restantes por atender
    }   
    }
    // Calcular el tiempo de procesamiento de cada auto en cada kiosco.
    // Sumar los tiempos de procesamiento de cada auto para obtener el tiempo total que cada kiosco utilizó.
    // Mostrar el tiempo en que se atiende a cada carro individualmente.
    clock_t end_time = clock(); // Marca de tiempo final
    double tiempo_total_transcurrido = difftime(end_time, start_time) / CLOCKS_PER_SEC;
    double tiempo_hilo_promedio = tiempo_total_transcurrido/carros;

    params -> tiempo_total = tiempo_total_transcurrido;
    params -> tiempo_promedio = tiempo_hilo_promedio;

    return NULL;
}

int main()
{
    /**
     * ===========
     * PEDIR DATOS
     * ===========
     */
    cout << "Ingrese el numero de carros que usan compass: ";
    cin >> carros_compass;
    cout << "Ingrese el numero de carros que usan efectivo: ";
    cin >> carros_efectivo;

    Parametros params1 = {true, carros_compass,0,0,0};
    Parametros params2 = {false, carros_efectivo,0,0,0};

    int creacion_hcompass = pthread_create(&hilo_compass, NULL, atencion, &params1);
    int creacion_hefectivo = pthread_create(&hilo_efectivo, NULL, atencion, &params2);

    // Esperar a que los hilos terminen (pthread_join) o realizar otras operaciones aquí
    pthread_join(hilo_compass, NULL);
    pthread_join(hilo_efectivo, NULL);

    return 0;
}
