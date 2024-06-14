/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/main.cc to edit this template
 */

/* 
 * File:   main.cpp
 * Author: piero
 *
 * Created on 12 de junio de 2024, 05:15 PM
 */

#include <cstdlib>
#include <iostream>

#include "Jugador.h"
#include "LecturaCSV.h"
#include "Formaciones.h"
#include "Genetico.h"

using namespace std;

//HAY UN SALTO EN 13284 PARA UN POSIBLE BORRADO

int main(int argc, char** argv) {
    vector<Jugador> jugadores, equipo;
    double presupuesto=500, fitness; //En millones de dolares
    
    leerJugadores("data_300.csv", jugadores, presupuesto);
    while(true) equipo = genetico(jugadores, jugadores.size(), presupuesto, f_4_3_3, chem_4_3_3, fitness);
    
    for(int i=0; i < N_PLAYERS; i++){
        cout << equipo[i].GetNombre() << " | ";
    }
    
    cout << endl << "Con Fitness: " << fitness;
    
    return 0;
}

