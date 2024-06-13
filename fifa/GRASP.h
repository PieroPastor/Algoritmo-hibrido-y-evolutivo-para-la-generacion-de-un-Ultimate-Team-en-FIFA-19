/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.h to edit this template
 */

/* 
 * File:   GRASP.h
 * Author: GAMER
 *
 * Created on 13 de junio de 2024, 10:16 AM
 */

#ifndef GRASP_H
#define GRASP_H

#include "Utils.h"
#include "Jugador.h"

#define ITERACIONES 100000
#define ALPHA 0.3

void grasp(vector<Jugador> &jugadores, vector<vector<int>> &poblacion, int n, double presupuesto, string *posiciones, int chem_pos[][N_CHEM], int requerido);
double construccion(vector<Jugador> &jugadores, vector<int> &candidato, int n, double presupuesto, string *posiciones, int chem_pos[][N_CHEM]);
void actualizarMejores(vector<vector<int>> &poblacion, vector<int> &candidato, vector<double> &mejoresfo, double fo_parcial, int requerido);

#endif /* GRASP_H */

