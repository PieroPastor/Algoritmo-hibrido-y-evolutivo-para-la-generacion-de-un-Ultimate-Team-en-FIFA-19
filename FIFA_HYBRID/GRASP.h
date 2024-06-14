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

#define ITERACIONES 10000
#define ALPHA 0.3

void grasp(vector<Jugador> &jugadores, vector<vector<int>> &poblacion, int n, double presupuesto, string *posiciones, int chem_pos[][N_CHEM], int requerido);
double construccion(map<string, vector<Jugador>> &mediasPos, vector<int> &candidato, int n, double presupuesto, string *posiciones, int chem_pos[][N_CHEM]);
void actualizarMejores(vector<vector<int>> &poblacion, vector<int> &candidato, vector<double> &mejoresfo, double fo_parcial, int requerido);
bool comparar(Jugador &a, Jugador &b);
bool comparar_gk(Jugador &a, Jugador &b);
bool sonIguales(vector<int> &pob, vector<int> &cand);
int verifica(vector<Jugador> &jugadores, int rcl, string pos);
bool notSelected(int id, vector<int> &candidato, int n);

#endif /* GRASP_H */

