/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.cc to edit this template
 */

#include "Funciones.h"

void imprimirResultado(vector<Jugador> &equipo, double fitness, string *formacion, int chem_pos[][N_CHEM]){
    cout << equipo[0].GetNombre() << " - " << equipo[0].GetMedia()
         << " - " << equipo[0].GetNacionalidad() << " - " << equipo[0].GetClub()
         << " - " <<  equipo[0].GetPosicion() <<" | ";
    
    for(int i=1; i < N_PLAYERS; i++){
        cout << equipo[i].GetNombre() << " - " << equipo[i].getMediaPos(formacion[i]) 
             << " - " << equipo[i].GetNacionalidad() << " - " << equipo[i].GetClub() 
             << " - " <<  equipo[i].GetPosicion() <<" | ";
    }

    cout << endl << "Con Fitness: " << fitness;
    cout << endl << "Con Quimica: " << getChemistry(equipo, chem_pos);
}

double getChemistry(vector<Jugador> &equipo, int chem_pos[][N_CHEM]){
    int cant_relaciones=0;
    double chem_parc=0;
    
    //Si no coinciden en nada +60, si coinciden en club o nacionalidad +150, si coinciden en los dos 200. Se divide entre el total de relaciones
    for(int i=0; i < N_CHEM; i++){
        for(int j=0; j < N_CHEM; j++){
            if(chem_pos[i][j] != -1){
                cant_relaciones++;
                if(equipo[i].GetNacionalidad().compare(equipo[chem_pos[i][j]].GetNacionalidad()) == 0 and
                   equipo[i].GetClub().compare(equipo[chem_pos[i][j]].GetClub()) == 0) chem_parc += 200;
                else if(equipo[i].GetNacionalidad().compare(equipo[chem_pos[i][j]].GetNacionalidad()) == 0 or
                        equipo[i].GetClub().compare(equipo[chem_pos[i][j]].GetClub()) == 0) chem_parc += 100;
                else chem_parc += 60;
            }else break;
        }
    }
    
    chem_parc /= (cant_relaciones*100);
    chem_parc = (chem_parc <= 100)?chem_parc:100; //Si supera el 100% se deja así
    
    return chem_parc;
}

double hallarPromedio(vector<double> &resultados){
    double sum=0;
    for(int i=0; i < resultados.size(); i++) sum += resultados[i];
    return sum/resultados.size();
}