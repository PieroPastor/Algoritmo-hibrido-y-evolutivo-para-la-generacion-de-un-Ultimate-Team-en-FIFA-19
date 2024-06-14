/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.cc to edit this template
 */

#include <iostream>

#include "Genetico.h"

vector<Jugador> genetico(vector<Jugador> &jugadores, int n, double presupuesto, string *posiciones, int chem_pos[][N_CHEM]){
    int indRet;
    vector<vector<int>> poblacion, padres;
    vector<Jugador> equipo;
    
    //Llamará al GRASP para la poblacion inicial
    grasp(jugadores, poblacion, jugadores.size(), presupuesto, posiciones, chem_pos, POB_INICIAL);
    
    for(int i=0; i < 11; i++) cout << poblacion[0][i] << endl;
    
    for(int i=0; i < GENERACIONES; i++){ //Ejecuta por tantas generaciones
        seleccion(poblacion, padres, jugadores, n, posiciones, chem_pos);
        casamiento(poblacion, padres);
        mutacion(poblacion, padres, jugadores);
        eliminarAberraciones(poblacion, jugadores, presupuesto);
        eliminarClones(poblacion);
        disminuirPoblacion(poblacion, jugadores, n, posiciones, chem_pos);
        padres.clear(); //Limpia los padres previos
    }
    
    seleccion(poblacion, padres, jugadores, n, posiciones, chem_pos);
    indRet = rand()%padres.size();
    for(int i=0; i < N_PLAYERS; i++) equipo.push_back(jugadores[padres[indRet][i]]);
    return equipo; //Retorna un padre aleatorio y se supone que por seleccion ahí puede estar el mejor
}

double calcularFo(vector<int> &equipo, vector<Jugador> &jugadores, string *posiciones, int chem_pos[][N_CHEM]){
    double fo_max=jugadores[equipo[0]].GetMedia()*jugadores[equipo[0]].GetPotencial(), //El portero tiene una media estatica
           fo_min=jugadores[equipo[0]].GetValor()*jugadores[equipo[0]].GetEdad(),
           chem_parc=0, cant_relaciones=0;
    
    for(int i=1; i < N_PLAYERS; i++){
        fo_max += jugadores[equipo[i]].getMediaPos(posiciones[i])*jugadores[equipo[i]].GetPotencial(); //Para tener su media en su posicion que le toco
        fo_min += jugadores[equipo[i]].GetValor()*jugadores[equipo[i]].GetEdad();
    }
    //Si no coinciden en nada +60, si coinciden en club o nacionalidad +150, si coinciden en los dos 200. Se divide entre el total de relaciones
    for(int i=0; i < N_CHEM; i++){
        for(int j=0; j < N_CHEM; j++){
            if(chem_pos[i][j] != -1){
                cant_relaciones++;
                if(jugadores[equipo[i]].GetNacionalidad().compare(jugadores[chem_pos[i][j]].GetNacionalidad()) == 0 and
                   jugadores[equipo[i]].GetClub().compare(jugadores[chem_pos[i][j]].GetClub()) == 0) chem_parc += 200;
                else if(jugadores[equipo[i]].GetNacionalidad().compare(jugadores[chem_pos[i][j]].GetNacionalidad()) == 0 or
                        jugadores[equipo[i]].GetClub().compare(jugadores[chem_pos[i][j]].GetClub()) == 0) chem_parc += 100;
                else chem_parc += 60;
            }else break;
        }
    }
    
    chem_parc /= cant_relaciones;
    cant_relaciones = (cant_relaciones <= 100)?cant_relaciones:100; //Si supera el 100% se deja así
    
    return (fo_max*cant_relaciones)/fo_min;
}

bool esAberracion(const vector<int> &equipo, const vector<Jugador> &jugadores, double presupuesto){
    double suma=0;
    for(int i=0; i < N_PLAYERS; i++){
        suma += jugadores[equipo[i]].GetValor();
        if(jugadores[equipo[i]].GetPosicion().compare("GK") and i >= 1) return true; //No puede ser arquero los que van luego de 1
    }
    return suma > presupuesto or jugadores[equipo[0]].GetPosicion() != "GK"; //Si pasa el presupuesto o no hay arquero
}

void calculaSupervivencia(vector<vector<int>> &poblacion, vector<double> &supervivencia, vector<Jugador> &jugadores, int n, string *posiciones, int chem_pos[][N_CHEM], bool muerte){
    double sumafo=0;
    double fit;
    for(int i=0; i < poblacion.size(); i++) sumafo += calcularFo(poblacion[i], jugadores, posiciones, chem_pos);
    for(int i=0; i < poblacion.size(); i++){
        fit=round(100*calcularFo(poblacion[i], jugadores, posiciones, chem_pos)/sumafo); //Multiplica por 100 para ese porcentaje volverlo cantidad y se redondea
        if(!muerte) supervivencia.push_back(fit);
        else supervivencia.push_back(100-fit); //Para bajarme a los peores (lo opuesto)
    }
}

void cargaRuletas(vector<double> supervivencia, int *ruleta){
    int cont=0;
    for(int i=0; i < supervivencia.size(); i++){ 
        //Repite tantas veces como el fit sea para que el random de un índice y 
        //con ese se seleccione del arreglo ej: 
        //rand=5 -> [0, 0, 0, 0, 0,, 4, ,4, 4, 4, 4] -> selecciona el 0
        for(int j=0; j < supervivencia[i]; j++){
            ruleta[cont] = i;
            cont++;
        }
    }
}

void seleccion(vector<vector<int>> &poblacion, vector<vector<int>> &padres, vector<Jugador> &jugadores, int n, string *posiciones, int chem_pos[][N_CHEM]){
    int ruleta[100]{}, npadres, ind, cont=0;
    vector<double> supervivencia;
    calculaSupervivencia(poblacion, supervivencia, jugadores, n, posiciones, chem_pos); //Halla el porcentaje de supervivencia de cada individuo
    cargaRuletas(supervivencia, ruleta); //Consigue un arreglo para que el random tenga preferencia a elegir a los mejores que tienen mayor supervivencia
    npadres = round(poblacion.size()*Tcasamiento);
    while(true){
        ind=rand()%100; //Con esto se saca un índice de la ruleta
        padres.push_back(poblacion[ruleta[ind]]);
        cont++;
        if(cont >= npadres) break;
    }
}

void mutacion(vector<vector<int>> &poblacion, vector<vector<int>> &padres, vector<Jugador> &jugadores){
    int cont=0;
    int nmuta = round(padres[0].size() *Tmutacion); //Deben mutar la mitad
    for(int i=0; i < padres.size(); i++){
        cont = 0; //Para que siempre muten
        while(cont < nmuta){
            int ind=rand()%padres[0].size(); //Elige un bit aleatorio de todo el gen para que cambie
            padres[i][ind] = rand()%jugadores.size(); //Lo cambia por otro jugador al azar, el indice en su vector jugadores
            cont++;
        }
        poblacion.push_back(padres[i]); //Guardo los padres mutados
    }
}

void generaHijo(vector<int> &padre, vector<int> &madre, vector<int> &hijo){
    int pos=round(padre.size()*Pcasamiento); //Porcentaje de cuantos genes tendrá de cada padre
    for(int i=0; i < pos; i++) hijo.push_back(padre[i]); //Tendrá 40% del padre
    for(int i=pos; i < madre.size(); i++) hijo.push_back(madre[i]); //Tendrá el resto (60%) de la madre
}

void casamiento(vector<vector<int>> &poblacion, vector<vector<int>> &padres){
    for(int i=0; i < padres.size(); i++){
        for(int j=0; j < padres.size(); j++){
            if(i != j){ //Para que cruce todos con todos
                vector<int> cromo;
                generaHijo(padres[i], padres[j], cromo);
                poblacion.push_back(cromo);
            }
        }
    }
}

/* PARA ESTE CASO PARECE QUE NO REQUIERE INVERSIÓN
void inversion(vector<vector<Jugador>> &poblacion, vector<vector<Jugador>> &padres){
    for(int i=0; i < padres.size(); i++){
        for(int j=0; j < padres[i].size(); j++){
            if(padres[i][j] == 0) padres[i][j] = 1;
            else padres[i][j] = 0;
        }
        poblacion.push_back(padres[i]);
    }
}
*/

void eliminarAberraciones(vector<vector<int>> &poblacion, vector<Jugador> &jugadores, double presupuesto){
    for(int i=0; i < poblacion.size(); i++){
        if(esAberracion(poblacion[i], jugadores, presupuesto)){
            //poblacion.erase(poblacion.begin()+(i--));
            poblacion.erase(poblacion.begin()+i);
            i--;
        }
    }
}

void eliminarClones(vector<vector<int>> &poblacion){
    int n=poblacion.size();
    vector<vector<int>> unicos;
    
    for(int i=0; i < n; i++){
        if(esUnico(unicos, poblacion[i])) unicos.push_back(poblacion[i]);
        else{
            poblacion.erase(poblacion.begin()+i);
            i--;
        }
    }
}

bool esUnico(vector<vector<int>> &unicos, vector<int> &equipo){
    int n=unicos.size(), flag;
    
    for(int i=0; i < n; i++){
        flag = true;
        for(int j=0; j < N_PLAYERS; j++){
            if(equipo[j] != unicos[i][j]){
                flag = false;
                break;
            }
        }
        if(!flag) return false; //Es identico a uno anterior
    }
    return true; //Es unico
}

void disminuirPoblacion(vector<vector<int>> &poblacion, vector<Jugador> &jugadores, int n, string *posiciones, int chem_pos[][N_CHEM]){
    int ruleta[100]{}, nmuertos, ind, cont=0;
    vector<double> muerte;
    calculaSupervivencia(poblacion, muerte, jugadores, n, posiciones, chem_pos, true); //Halla el porcentaje de supervivencia de cada individuo
    cargaRuletas(muerte, ruleta); //Consigue un arreglo para que el random tenga preferencia a elegir a los mejores que tienen mayor supervivencia
    nmuertos = round(poblacion.size()*Tmuerte);
    while(true){
        ind=rand()%100; //Con esto se saca un índice de la ruleta
        poblacion.erase(poblacion.begin()+ind); //Se baja a ese gen
        cont++; //Lo agrega para contar los muertos
        if(cont >= nmuertos) break;
    }
}