/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.cc to edit this template
 */

#include <iostream>

#include "GRASP.h"

string pos_name;

void grasp(vector<Jugador> &jugadores, vector<vector<int>> &poblacion, int n, double presupuesto, string *posiciones, int chem_pos[][N_CHEM], int requerido){
    double fo_parcial;
    vector<double> mejoresfo;
    vector<int> pob_parcial;
    vector<Jugador> auxJugadores(jugadores);
    map<string, vector<Jugador>> mediasPos;
    
    for(int i=0; i < N_CHEM; i++){
        pos_name = posiciones[i];
        //Para ordenar según la posición actual "RW" por ejemplo y lo guarda en un map para no ordenar todo el tiempo
        sort(auxJugadores.begin(), auxJugadores.end(), comparar); 
        mediasPos[pos_name] = auxJugadores;
    }
    
    for(int i=0; i < ITERACIONES; i++){
        fo_parcial = construccion(mediasPos, pob_parcial, n, presupuesto, posiciones, chem_pos);
        actualizarMejores(poblacion, pob_parcial, mejoresfo, fo_parcial, requerido);
        pob_parcial.clear();
    }
}

double construccion(map<string, vector<Jugador>> &mediasPos, vector<int> &candidato, int n, double presupuesto, string *posiciones, int chem_pos[][N_CHEM]){
    int residual, beta, tau, maxrcl, indmax, inda;
    //Falta analizar arqueros
    for(int i=1; i < N_PLAYERS; i++){
        //Usara mediasPos[posiciones[i]; Esta ordenado segun la posicion
        beta = n; //Vamos a basarnos en indices
        tau = 0;
        maxrcl = beta - ALPHA*(beta-tau);
    }
}

void actualizarMejores(vector<vector<int>> &poblacion, vector<int> &candidato, vector<double> &mejoresfo, double fo_parcial, int requerido){
    //Aquí se tendrá en cuenta la química
}

bool comparar(Jugador &a, Jugador &b){
    double fo_a=(double)(a.getMediaPos(pos_name)*a.GetPotencial())/
                (double)(a.GetValor()*a.GetEdad());
    double fo_b=(double)(b.getMediaPos(pos_name)*b.GetPotencial())/
                (double)(b.GetValor()*b.GetEdad());
    return fo_a < fo_b;
}

