/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.cc to edit this template
 */

/* 
 * File:   Jugador.cpp
 * Author: GAMER
 * 
 * Created on 12 de junio de 2024, 05:30 PM
 */

#include "Jugador.h"

Jugador::Jugador() {
}

Jugador::Jugador(const Jugador& orig) {
}

Jugador::~Jugador() {
}

void Jugador::setId(int id){
    this->id = id;
}

int Jugador::getId(){
    return id;
}

void Jugador::SetValor(double valor) {
    this->valor = valor;
}

double Jugador::GetValor() const {
    return valor;
}

void Jugador::SetClub(string club) {
    this->club = club;
}

string Jugador::GetClub() const {
    return club;
}

void Jugador::SetPotencial(int potencial) {
    this->potencial = potencial;
}

int Jugador::GetPotencial() const {
    return potencial;
}

void Jugador::SetMedia(int media) {
    this->media = media;
}

int Jugador::GetMedia() const {
    return media;
}

void Jugador::SetPosicion(string posicion) {
    this->posicion = posicion;
}

string Jugador::GetPosicion() const {
    return posicion;
}

void Jugador::SetNacionalidad(string nacionalidad) {
    this->nacionalidad = nacionalidad;
}

string Jugador::GetNacionalidad() const {
    return nacionalidad;
}

void Jugador::SetEdad(int edad) {
    this->edad = edad;
}

int Jugador::GetEdad() const {
    return edad;
}

void Jugador::SetNombre(string nombre) {
    this->nombre = nombre;
}

string Jugador::GetNombre() const {
    return nombre;
}

void Jugador::setMediaPos(int media, string pos) {
    this->mediaPos[pos] = media;
}

int Jugador::getMediaPos(string pos) {
    return mediaPos[pos];
}

