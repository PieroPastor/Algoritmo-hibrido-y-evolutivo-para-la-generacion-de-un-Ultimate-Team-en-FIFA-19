/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.cc to edit this template
 */

#include "Genetico.h"

vector<Jugador> genetico(vector<Jugador> &jugadores, double presupuesto, string *posiciones){
    int indRet;
    vector<vector<Jugador>> poblacion;
    vector<vector<Jugador>> padres;
    
    //Llamará al GRASP para la poblacion inicial
    
    for(int i=0; i < IND; i++){ //Ejecuta por tantas generaciones
        seleccion(poblacion, padres, posiciones);
        casamiento(poblacion, padres);
        mutacion(poblacion, padres, jugadores);
        eliminarAberraciones(poblacion, presupuesto);
        eliminarClones(poblacion);
        padres.clear(); //Limpia los padres previos
    }
    
    seleccion(poblacion, padres, posiciones);
    indRet = rand()%padres.size();
    return padres[indRet]; //Retorna un padrea aleatorio
}

double calcularFo(vector<Jugador> &equipo, string *posiciones){
    double fo_max=equipo[0].GetMedia()*equipo[0].GetPotencial(), //El portero tiene una media estatica
           fo_min=equipo[0].GetValor()*equipo[0].GetEdad();
    
    for(int i=1; i < N_PLAYERS; i++){
        fo_max += equipo[i].getMediaPos(posiciones[i])*equipo[i].GetPotencial(); //Para tener su media en su posicion que le toco
        fo_min += equipo[i].GetValor()*equipo[i].GetEdad();
    }
    
    //Falta analizar la quimica en base a los equipos y paises
    
    return fo_max/fo_min;
}

bool esAberracion(const vector<Jugador> &jugadores, double presupuesto){
    double suma=0;
    for(int i=0; i < N_PLAYERS; i++){
        suma += jugadores[i].GetValor();
    }
    return suma > presupuesto or jugadores[0].GetPosicion() == "GK"; //Si pasa el presupuesto o no hay arquero
}

void calculaSupervivencia(vector<vector<Jugador>> &poblacion, vector<double> &supervivencia, string *posiciones){
    int sumafo=0;
    double fit;
    for(int i=0; i < poblacion.size(); i++) sumafo += calcularFo(poblacion[i], posiciones);
    for(int i=0; i < poblacion.size(); i++){
        fit=round(100*calcularFo(poblacion[i], posiciones)/sumafo); //Multiplica por 100 para ese porcentaje volverlo cantidad y se redondea
        supervivencia.push_back(fit);
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

void seleccion(vector<vector<Jugador>> &poblacion, vector<vector<Jugador>> &padres, string *posiciones){
    int ruleta[100]{}, npadres, ind, cont=0;
    vector<double> supervivencia;
    calculaSupervivencia(poblacion, supervivencia, posiciones); //Halla el porcentaje de supervivencia de cada individuo
    cargaRuletas(supervivencia, ruleta); //Consigue un arreglo para que el random tenga preferencia a elegir a los mejores que tienen mayor supervivencia
    npadres = round(poblacion.size()*Tcasamiento);
    while(true){
        ind=rand()%100; //Con esto se saca un índice de la ruleta
        padres.push_back(poblacion[ruleta[ind]]);
        cont++;
        if(cont >= npadres) break;
    }
}

void mutacion(vector<vector<Jugador>> &poblacion, vector<vector<Jugador>> &padres, vector<Jugador> &jugadores){
    int cont=0;
    int nmuta = round(padres[0].size() *Tmutacion); //Deben mutar la mitad
    for(int i=0; i < padres.size(); i++){
        cont = 0; //Para que siempre muten
        while(cont < nmuta){
            int ind=rand()%padres[0].size(); //Elige un bit aleatorio de todo el gen para que cambie
            padres[i][ind] = jugadores[rand()%jugadores.size()]; //Lo cambia por otro jugador al azar
            cont++;
        }
        poblacion.push_back(padres[i]); //Guardo los padres mutados
    }
}

void generaHijo(vector<Jugador> &padre, vector<Jugador> &madre, vector<Jugador> &hijo){
    int pos=round(padre.size()*Pcasamiento); //Porcentaje de cuantos genes tendrá de cada padre
    for(int i=0; i < pos; i++) hijo.push_back(padre[i]); //Tendrá 40% del padre
    for(int i=pos; i < madre.size(); i++) hijo.push_back(madre[i]); //Tendrá el resto (60%) de la madre
}

void casamiento(vector<vector<Jugador>> &poblacion, vector<vector<Jugador>> &padres){
    for(int i=0; i < padres.size(); i++){
        for(int j=0; j < padres.size(); j++){
            if(i != j){ //Para que cruce todos con todos
                vector<Jugador> cromo;
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

void eliminarAberraciones(vector<vector<Jugador>> &poblacion, double presupuesto){
    for(int i=0; i < poblacion.size(); i++){
        if(esAberracion(poblacion[i], presupuesto)){
            //poblacion.erase(poblacion.begin()+(i--));
            poblacion.erase(poblacion.begin()+i);
            i--;
        }
    }
}

void eliminarClones(vector<vector<Jugador>> &poblacion){
    int n=poblacion.size();
    vector<vector<Jugador>> unicos;
    
    for(int i=0; i < n; i++){
        if(esUnico(unicos, poblacion[i])) unicos.push_back(poblacion[i]);
        else{
            poblacion.erase(poblacion.begin()+i);
            i--;
        }
    }
}

bool esUnico(vector<vector<Jugador>> &unicos, vector<Jugador> &equipo){
    int n=unicos.size(), flag;
    
    for(int i=0; i < n; i++){
        flag = true;
        for(int j=0; j < N_PLAYERS; j++){
            if(equipo[j].getId() != unicos[i][j].getId()){
                flag = false;
                break;
            }
        }
        if(!flag) return false; //Es identico a uno anterior
    }
    return true; //Es unico
}