/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.h to edit this template
 */

/* 
 * File:   Genetico.h
 * Author: GAMER
 *
 * Created on 12 de junio de 2024, 08:01 PM
 */

#ifndef GENETICO_H
#define GENETICO_H

#include "Jugador.h"

#define Tcasamiento 0.5
#define Tmutacion 0.5
#define Pcasamiento 0.4
#define IND 10

vector<Jugador> genetico(vector<Jugador> &jugadores, double presupuesto, string *posiciones);
double calcularFo(vector<Jugador> &equipo, string *posiciones);
bool esAberracion(const vector<Jugador> &jugadores, double presupuesto);
void calculaSupervivencia(vector<vector<Jugador>> &poblacion, vector<double> &supervivencia, string *posiciones);
void cargaRuletas(vector<double> supervivencia, int *ruleta);
void seleccion(vector<vector<Jugador>> &poblacion, vector<vector<Jugador>> &padres, string *posiciones);
void mutacion(vector<vector<Jugador>> &poblacion, vector<vector<Jugador>> &padres, vector<Jugador> &jugadores);
void generaHijo(vector<Jugador> &padre, vector<Jugador> &madre, vector<Jugador> &hijo);
void casamiento(vector<vector<Jugador>> &poblacion, vector<vector<Jugador>> &padres);
void eliminarAberraciones(vector<vector<Jugador>> &poblacion, double presupuesto);
void eliminarClones(vector<vector<Jugador>> &poblacion);
bool esUnico(vector<vector<Jugador>> &unicos, vector<Jugador> &equipo);

#endif /* GENETICO_H */

