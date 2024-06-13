/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.h to edit this template
 */

/* 
 * File:   LecturaCSV.h
 * Author: GAMER
 *
 * Created on 12 de junio de 2024, 06:20 PM
 */

#ifndef LECTURACSV_H
#define LECTURACSV_H

#include "Jugador.h"

void leerJugadores(const char *nombre, vector<Jugador> &jugadores, double presupuesto);
char* leerCadena(ifstream &arch, int max, char tope);
void leerMediasPosicion(Jugador &jugador, ifstream &arch);
void cargarInformacion(Jugador &jugador, char *nomcad, char *naciocad, char *poscad, 
                       char *clubcad, double valor, int id, int edad, int media, int potencial);

#endif /* LECTURACSV_H */

