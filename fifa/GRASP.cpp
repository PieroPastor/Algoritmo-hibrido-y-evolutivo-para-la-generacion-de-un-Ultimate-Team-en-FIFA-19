/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.cc to edit this template
 */

#include "GRASP.h"

void grasp(vector<Jugador> &jugadores, vector<vector<int>> &poblacion, int n, double presupuesto, string *posiciones, int chem_pos[][N_CHEM], int requerido){
    double fo_parcial;
    vector<double> mejoresfo;
    vector<int> pob_parcial;
    
    for(int i=0; i < ITERACIONES; i++){
        fo_parcial = construccion(jugadores, pob_parcial, n, presupuesto, posiciones, chem_pos);
        actualizarMejores(poblacion, pob_parcial, mejoresfo, fo_parcial, requerido);
        pob_parcial.clear();
    }
}

double construccion(vector<Jugador> &jugadores, vector<int> &candidato, int n, double presupuesto, string *posiciones, int chem_pos[][N_CHEM]){
    int residual, beta, tau, maxrcl, indmax, inda;
}

void actualizarMejores(vector<vector<int>> &poblacion, vector<int> &candidato, vector<double> &mejoresfo, double fo_parcial, int requerido){
    
}