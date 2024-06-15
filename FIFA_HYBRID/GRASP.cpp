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

    cargarCopias(mediasPos, auxJugadores, auxJugadores.size(), posiciones);
    
    for(int i=0; i < ITERACIONES; i++){
        srand(time(NULL));
        fo_parcial = construccion(mediasPos, pob_parcial, n, presupuesto, posiciones, chem_pos);
        fo_parcial *= getChemistry(pob_parcial, jugadores, chem_pos);
        actualizarMejores(poblacion, pob_parcial, mejoresfo, fo_parcial, requerido);
        pob_parcial.clear();
    } 
}

void cargarCopias(map<string, vector<Jugador>> &mediasPos, vector<Jugador> &auxJugadores, int n, string *posiciones){
    //Para ordenar según la posición actual "RW" por ejemplo y lo guarda en un map para no ordenar todo el tiempo
    for(int i=1; i < N_PLAYERS; i++){
        pos_name = posiciones[i];
        sort(auxJugadores.begin(), auxJugadores.end(), comparar); 
        mediasPos[pos_name] = auxJugadores;
    }
    
    sort(auxJugadores.begin(), auxJugadores.end(), comparar_gk); 
    
    for(int i=0; i < n; i++){
        if(auxJugadores[i].GetPosicion().compare("GK") == 0) 
            mediasPos["GK"].push_back(auxJugadores[i]); //Guarda los arqueros tambien ya estan ordenados por media
    }
}

double construccion(map<string, vector<Jugador>> &mediasPos, vector<int> &candidato, int n, double presupuesto, string *posiciones, int chem_pos[][N_CHEM]){
    int beta, tau, maxrcl, indmax, inda, fitness=0;
    vector<int> borrados;
    
    //Análisis exclusivo de arqueros
    while(true){
        beta = mediasPos["GK"].size();
        tau = 0;
        maxrcl = beta - ALPHA*(beta-tau);
        indmax = beta-maxrcl;
        inda = (indmax>0)?rand()%indmax:0;
        inda += maxrcl;
        if(presupuesto >= mediasPos["GK"][inda].GetValor()){
            presupuesto -= mediasPos["GK"][inda].GetValor();
            candidato.push_back(mediasPos["GK"][inda].getId());
            fitness += mediasPos["GK"][inda].getFitness("GK");
            break;
        }
    }

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

bool sonIguales(vector<int> &pob, vector<int> &cand){
    for(int i=0; i < pob.size(); i++)
        if(pob[i] != cand[i]) return false;
    return true;
}

void actualizarMejores(vector<vector<int>> &poblacion, vector<int> &candidato, vector<double> &mejoresfo, double fo_parcial, int requerido){
    double peor=INTMAX_MAX;
    int peor_fo;
    
    if(poblacion.size() < requerido){
        for(int i=0; i < poblacion.size(); i++)
            if(sonIguales(poblacion[i], candidato)) return; //No necesito iguales
        poblacion.push_back(candidato);
        mejoresfo.push_back(fo_parcial);
    }
    else{
        for(int i=0; i < requerido; i++){
            if(sonIguales(poblacion[i], candidato)) return; //No necesito repetidos
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

double getChemistry(vector<int> &equipo, vector<Jugador> &jugadores, int chem_pos[][N_CHEM]){
    int cant_relaciones=0;
    double chem_parc=0;
    
    //Si no coinciden en nada +60, si coinciden en club o nacionalidad +150, si coinciden en los dos 200. Se divide entre el total de relaciones
    for(int i=0; i < N_CHEM; i++){
        for(int j=0; j < N_CHEM; j++){
            if(chem_pos[i][j] != -1){
                cant_relaciones++;
                if(jugadores[equipo[i]].GetNacionalidad().compare(jugadores[equipo[chem_pos[i][j]]].GetNacionalidad()) == 0 and
                   jugadores[equipo[i]].GetClub().compare(jugadores[equipo[chem_pos[i][j]]].GetClub()) == 0) chem_parc += 200;
                else if(jugadores[equipo[i]].GetNacionalidad().compare(jugadores[equipo[chem_pos[i][j]]].GetNacionalidad()) == 0 or
                        jugadores[equipo[i]].GetClub().compare(jugadores[equipo[chem_pos[i][j]]].GetClub()) == 0) chem_parc += 100;
                else chem_parc += 60;
            }else break;
        }
    }
    
    chem_parc /= (cant_relaciones*100);
    chem_parc = (chem_parc <= 1)?chem_parc:1; //Si supera el 100% se deja así
    
    return chem_parc;
}

bool comparar(Jugador &a, Jugador &b){
    double fo_a=(double)(a.getMediaPos(pos_name)*a.GetPotencial()*per_max)/
                (double)(a.GetValor()*a.GetEdad()*per_min);
    double fo_b=(double)(b.getMediaPos(pos_name)*b.GetPotencial()*per_max)/
                (double)(b.GetValor()*b.GetEdad()*per_min);
    return fo_a < fo_b;
}

bool comparar_gk(Jugador &a, Jugador &b){
    double fo_a=(double)(a.GetMedia()*a.GetPotencial()*per_max)/
                (double)(a.GetValor()*a.GetEdad()*per_min);
    double fo_b=(double)(b.GetMedia()*b.GetPotencial()*per_max)/
                (double)(b.GetValor()*b.GetEdad()*per_min);
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
