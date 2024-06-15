/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.cc to edit this template
 */

#include "Funciones.h"

void imprimirResultado(vector<Jugador> &equipo, double fitness, string *formacion){
    cout << equipo[0].GetNombre() << " - " << equipo[0].GetMedia()
         << " - " << equipo[0].GetNacionalidad() << " | ";
    
    for(int i=1; i < N_PLAYERS; i++){
        cout << equipo[i].GetNombre() << " - " << equipo[i].getMediaPos(formacion[i]) 
             << " - " << equipo[i].GetNacionalidad() << " | ";
    }

    cout << endl << "Con Fitness: " << fitness;
}