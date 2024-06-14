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

    //Para ordenar según la posición actual "RW" por ejemplo y lo guarda en un map para no ordenar todo el tiempo
    for(int i=0; i < N_PLAYERS; i++){
        pos_name = posiciones[i];
        sort(auxJugadores.begin(), auxJugadores.end(), comparar); 
        mediasPos[pos_name] = auxJugadores;
    }
    
    for(int i=0; i < ITERACIONES; i++){
        srand(time(NULL));
        fo_parcial = construccion(mediasPos, pob_parcial, n, presupuesto, posiciones, chem_pos);
        actualizarMejores(poblacion, pob_parcial, mejoresfo, fo_parcial, requerido);
        pob_parcial.clear();
    }
}

double construccion(map<string, vector<Jugador>> &mediasPos, vector<int> &candidato, int n, double presupuesto, string *posiciones, int chem_pos[][N_CHEM]){
    int beta, tau, maxrcl, indmax, inda, fitness=0;
    vector<int> borrados;
    //Falta analizar arqueros
    candidato.push_back(57); presupuesto -= 41.5;
    for(int i=1; i < N_PLAYERS; i++){
        //Usara mediasPos[posiciones[i]; Esta ordenado segun la posicion
        beta = mediasPos[posiciones[i]].size(); //Vamos a basarnos en indices
        tau = 0;
        maxrcl = beta - ALPHA*(beta-tau);
        indmax = beta-maxrcl;
        inda = (indmax > 0)?rand()%indmax:0; //Si sale el indice 0 solo toma eso
        inda += maxrcl;
        if(presupuesto >= mediasPos[posiciones[i]][inda].GetValor() and 
           notSelected(mediasPos[posiciones[i]][inda].getId(), borrados, borrados.size()) and
           mediasPos[posiciones[i]][inda].GetPosicion().compare("GK") != 0){
            presupuesto -= mediasPos[posiciones[i]][inda].GetValor();
            candidato.push_back(mediasPos[posiciones[i]][inda].getId());
            fitness += mediasPos[posiciones[i]][inda].getFitness(posiciones[i]);
        }
        else i--; //Tiene que volver a analizar la posicion
        borrados.push_back(mediasPos[posiciones[i]][inda].getId()); //Lo borra pero para evitar mandar copias y mandar la direccion se usará un vector auxiliar
    }
    
    return fitness;
}

void actualizarMejores(vector<vector<int>> &poblacion, vector<int> &candidato, vector<double> &mejoresfo, double fo_parcial, int requerido){
    double peor=INTMAX_MAX;
    int peor_fo;
    
    if(poblacion.size() < requerido){
        poblacion.push_back(candidato);
        mejoresfo.push_back(fo_parcial);
    }
    else{
        for(int i=0; i < requerido; i++){
            if(mejoresfo[i] < peor){
                peor = mejoresfo[i];
                peor_fo = i;
            }
        }
        if(fo_parcial > peor){
            mejoresfo[peor_fo] = fo_parcial;
            poblacion[peor_fo] = candidato;
        }
    }
}

bool comparar(Jugador &a, Jugador &b){
    double fo_a=(double)(a.getMediaPos(pos_name)*a.GetPotencial())/
                (double)(a.GetValor()*a.GetEdad());
    double fo_b=(double)(b.getMediaPos(pos_name)*b.GetPotencial())/
                (double)(b.GetValor()*b.GetEdad());
    return fo_a < fo_b;
}

int verifica(vector<Jugador> &jugadores, int rcl, string pos){
    int cont=0, n=jugadores.size();
    for(int i=0; i < n; i++){
        if(jugadores[i].getFitness(pos) >= rcl) cont++;
        else return cont;
    }
}

bool notSelected(int id, vector<int> &borrados, int n){
    for(int i=0; i < n; i++)
        if(id == borrados[i]) return false;
    return true;
}