/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.cc to edit this template
 */

#include <iostream>

#include "LecturaCSV.h"

string posiciones_meds[]={"LS","ST","RS","LW","LF","CF","RF","RW","LAM","CAM","RAM","LM","LCM",
              "CM","RCM","RM","LWB","LDM","CDM","RDM","RWB","LB","LCB","CB","RCB","RB"};

void leerJugadores(const char *narch, vector<Jugador> &jugadores, double presupuesto){
    ifstream arch (narch, ios::in);
    if(not arch.is_open()){exit(1);}
    Jugador jugador;
    int id, edad, media, potencial, aux;
    double valor, auxD;
    char car, *nomcad, *naciocad, *poscad, *clubcad;
    while(arch.get()!='\n'); //Limpia la cabecera
    for(;;){
        arch >> id;
        if(arch.eof()) break;
        arch.get();
        if(id >= 13284) id -= 48; //Para el salto que hubo en los ids de datos
        arch >> aux >> car;
        nomcad = leerCadena(arch, 500, ',');
        arch >> edad >> car;
        while(arch.get() != ',');
        naciocad = leerCadena(arch, 100, ',');
        while(arch.get() != ',');
        arch >> media >> car >> potencial >> car;
        clubcad = leerCadena(arch, 100, ',');
        while(arch.get() != ','); arch.get();
        arch >> valor >> car;
        if(car == 'K') valor = valor/1000; //Si está en K y no M
        arch >> car >> car >> auxD >> car >> car >> aux >> car;
        while(arch.get() != ',');
        arch >> aux >> car >> aux >> car >> aux >> car;
        while(arch.get() != ','); while(arch.get() != ','); while(arch.get() != ',');
        poscad = leerCadena(arch, 5, ',');        
        if(strcmp(poscad, "GK") != 0)leerMediasPosicion(jugador, arch);
        else while(arch.get() != '\n'); //Salta al siguiente jugador
        cargarInformacion(jugador, nomcad, naciocad, poscad, clubcad, valor, id, edad, media, potencial);
        if(jugador.GetValor() < presupuesto)jugadores.push_back(jugador); //Solo guarda si será útil
    }
}

char* leerCadena(ifstream &arch, int max, char tope){
    char buff[500], *cad;
    arch.get(buff, max, tope);
    arch.get();
    cad = new char[strlen(buff)+1];
    strcpy(cad, buff);
    return cad;
}

void leerMediasPosicion(Jugador &jugador, ifstream &arch){
    int med, med_2;
    char car;
    while(arch.get() != 'l');//Por el lbs
    if(arch.get() != 'b') {leerMediasPosicion(jugador, arch); return;}
    if(arch.get() != 's') {leerMediasPosicion(jugador, arch); return;}
    arch.get();
    for(int i=0; i < N_POS; i++){
        arch >> med >> car >> med_2 >> car;
        jugador.setMediaPos(med+med_2, posiciones_meds[i]);
    }
    while(arch.get() != '\n'); //Salta al siguiente jugador
}

void cargarInformacion(Jugador &jugador, char *nomcad, char *naciocad, char *poscad, 
                       char *clubcad, double valor, int id, int edad, int media, int potencial){
    jugador.SetNombre(nomcad);
    jugador.SetNacionalidad(naciocad);
    jugador.SetPosicion(poscad);
    jugador.SetClub(clubcad);
    jugador.SetValor(valor);
    jugador.setId(id);
    jugador.SetEdad(edad);
    jugador.SetMedia(media);
    jugador.SetPotencial(potencial);
}