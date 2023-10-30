#ifndef REDES_H
#define REDES_H

#include "enrutadores.h"
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <sstream>
#include <iomanip>

using namespace std;

class Redes
{
public:
    Redes();
    void Obtener_red();
    void Asignar_Nombre(string Nombre_Archivo);
    void RutaReducida(string origen, string destino);
    string caminoMasCorto();
    string crearCaminos(string origen,string destino);
    void anadirCamino(string way);
    bool validar(string response);
    map<char, int> costos(string Origen);
private:
    map<string, map<string, int>> Enlaces;
    enrutadores Enrutador;
    void imprimirMatrizAdyacente(map<string, map<string, int>> Enlaces);
    bool CaminoDirecto(string origen, string destino, map<string,map<string,int>>::iterator it1,map<string,int>::iterator it2);
    string Nombre_Archivo, camino;
    map<char, enrutadores>::iterator it;
    map<string,int> ways;
    map<string,int>::iterator itW;
    map<char,int> Conexiones;
};

#endif // REDES_H
