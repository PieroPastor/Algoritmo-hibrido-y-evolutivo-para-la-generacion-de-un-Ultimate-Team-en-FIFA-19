/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.h to edit this template
 */

/* 
 * File:   Funciones.h
 * Author: GAMER
 *
 * Created on 14 de junio de 2024, 10:28 PM
 */

#ifndef FUNCIONES_H
#define FUNCIONES_H

#include "Utils.h"
#include "Jugador.h"

void imprimirResultado(vector<Jugador> &equipo, double fitness, string *formacion, int chem_pos[][N_CHEM]);
double getChemistry(vector<Jugador> &equipo, int chem_pos[][N_CHEM]);
double hallarPromedio(vector<double> &resultados);

#endif /* FUNCIONES_H */

