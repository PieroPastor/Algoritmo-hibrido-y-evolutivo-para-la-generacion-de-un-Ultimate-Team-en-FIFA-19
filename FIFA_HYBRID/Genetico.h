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

#include "Utils.h"
#include "Jugador.h"
#include "GRASP.h"

#define Tcasamiento 0.5
#define Tmutacion 0.5
#define Tmuerte 0.4 //No debe haber mas muertes que nacimientos
#define Pcasamiento 0.5
#define IND 10
#define GENERACIONES 100
#define POB_INICIAL 50

vector<Jugador> genetico(vector<Jugador> &jugadores, int n, double presupuesto, string *posiciones, int chem_pos[][N_CHEM], double &fitness);
double calcularFo(vector<int> &equipo, vector<Jugador> &jugadores, string *posiciones, int chem_pos[][N_CHEM]);
double calcularOf(vector<int> &equipo, vector<Jugador> &jugadores, string *posiciones, int chem_pos[][N_CHEM]);
bool esAberracion(const vector<int> &equipo, const vector<Jugador> &jugadores, double presupuesto);
void calculaSupervivencia(vector<vector<int>> &poblacion, vector<double> &supervivencia, vector<Jugador> &jugadores, int n, string *posiciones, int chem_pos[][N_CHEM], double (*calcular)(vector<int> &, vector<Jugador> &, string *, int [][N_CHEM]));
void cargaRuletas(vector<double> supervivencia, vector<int> &ruleta);
void seleccion(vector<vector<int>> &poblacion, vector<vector<int>> &padres, vector<Jugador> &jugadores, int n, string *posiciones, int chem_pos[][N_CHEM]);
void mutacion(vector<vector<int>> &poblacion, vector<vector<int>> &padres, vector<Jugador> &jugadores);
void generaHijo(vector<int> &padre, vector<int> &madre, vector<int> &hijo);
void casamiento(vector<vector<int>> &poblacion, vector<vector<int>> &padres);
void eliminarAberraciones(vector<vector<int>> &poblacion, vector<Jugador> &jugadores, double presupuesto);
void eliminarClones(vector<vector<int>> &poblacion);
bool esUnico(vector<vector<int>> &unicos, vector<int> &equipo);
void disminuirPoblacion(vector<vector<int>> &poblacion, vector<Jugador> &jugadores, int n, string *posiciones, int chem_pos[][N_CHEM]);

#endif /* GENETICO_H */

