/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.h to edit this template
 */

/* 
 * File:   Equipo.h
 * Author: GAMER
 *
 * Created on 12 de junio de 2024, 05:52 PM
 */

#ifndef EQUIPO_H
#define EQUIPO_H

#include "Jugador.h"

class Equipo {
public:
    Equipo();
    Equipo(const Equipo& orig);
    virtual ~Equipo();
    void SetEdad(double edad);
    double GetEdad() const;
    void SetQuimica(double quimica);
    double GetQuimica() const;
    void SetMedia(double media);
    double GetMedia() const;
    void SetCosto(double costo);
    double GetCosto() const;
    void SetJugadores(vector<Jugador> jugadores);
    vector<Jugador> GetJugadores() const;
private:
    vector<Jugador> jugadores;
    double costo;
    double media;
    double quimica;
    double edad;
};

#endif /* EQUIPO_H */

