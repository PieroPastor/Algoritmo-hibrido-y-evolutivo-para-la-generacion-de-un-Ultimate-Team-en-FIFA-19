/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.h to edit this template
 */

/* 
 * File:   Jugador.h
 * Author: GAMER
 *
 * Created on 12 de junio de 2024, 05:30 PM
 */

#ifndef JUGADOR_H
#define JUGADOR_H

#include "Utils.h"

class Jugador {
public:
    Jugador();
    Jugador(const Jugador& orig);
    virtual ~Jugador();
    void setId(int id);
    int getId();
    void SetValor(double valor);
    double GetValor() const;
    void SetClub(string club);
    string GetClub() const;
    void SetPotencial(int potencial);
    int GetPotencial() const;
    void SetMedia(int media);
    int GetMedia() const;
    void SetPosicion(string posicion);
    string GetPosicion() const;
    void SetNacionalidad(string nacionalidad);
    string GetNacionalidad() const;
    void SetEdad(int edad);
    int GetEdad() const;
    void SetNombre(string nombre);
    string GetNombre() const;
    void setMediaPos(int media, string pos);
    int getMediaPos(string pos);
private:
    int id;
    string nombre;
    int edad;
    string nacionalidad;
    string posicion;
    int media;
    int potencial;
    string club;
    double valor;
    map<string, int> mediaPos;//Ya que tiene una media según la pocisión
};

#endif /* JUGADOR_H */

