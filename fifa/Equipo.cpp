/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.cc to edit this template
 */

/* 
 * File:   Equipo.cpp
 * Author: GAMER
 * 
 * Created on 12 de junio de 2024, 05:52 PM
 */

#include "Equipo.h"

Equipo::Equipo() {
}

Equipo::Equipo(const Equipo& orig) {
}

Equipo::~Equipo() {
}

void Equipo::SetEdad(double edad) {
    this->edad = edad;
}

double Equipo::GetEdad() const {
    return edad;
}

void Equipo::SetQuimica(double quimica) {
    this->quimica = quimica;
}

double Equipo::GetQuimica() const {
    return quimica;
}

void Equipo::SetMedia(double media) {
    this->media = media;
}

double Equipo::GetMedia() const {
    return media;
}

void Equipo::SetCosto(double costo) {
    this->costo = costo;
}

double Equipo::GetCosto() const {
    return costo;
}

void Equipo::SetJugadores(vector<Jugador> jugadores) {
    this->jugadores = jugadores;
}

vector<Jugador> Equipo::GetJugadores() const {
    return jugadores;
}

