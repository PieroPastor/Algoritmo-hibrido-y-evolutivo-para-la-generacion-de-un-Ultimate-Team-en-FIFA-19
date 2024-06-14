/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.h to edit this template
 */

/* 
 * File:   Formaciones.h
 * Author: GAMER
 *
 * Created on 12 de junio de 2024, 06:03 PM
 */

#ifndef FORMACIONES_H
#define FORMACIONES_H

#include "Utils.h"

string f_4_3_3[11]={"GK", "RB", "CB", "CB", "LB", "CM", "CM", "CM", "RW", "ST", "LW"};
int chem_4_3_3[N_CHEM][N_CHEM]={ //Se tiene quimica 10x10 porque un jugador no juega consigo mismo
    {2, 3, -1, -1, -1, -1, -1, -1, -1, -1},
    {5, 2, -1, -1, -1, -1, -1, -1, -1, -1},
    {3, 6, -1, -1, -1, -1, -1, -1, -1, -1},
    {6, 4, -1, -1, -1, -1, -1, -1, -1, -1},
    {7, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {8, 6, -1, -1, -1, -1, -1, -1, -1, -1},
    {9, 7, -1, -1, -1, -1, -1, -1, -1, -1},
    {10, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {9, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {10, -1, -1, -1, -1, -1, -1, -1, -1, -1},
};

#endif /* FORMACIONES_H */

