#ifndef ENRUTADORES_H
#define ENRUTADORES_H

#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <map>
#include <random>
#include <sstream>

using namespace std;

class enrutadores

{
public:
    enrutadores();
    string Obtener_Enrutadores(string Nombre_Archivo);
    void Asignar_Nombre(string Nombre_Archivo);
    string Obtener_Nombre_Archivo();
    void Generar_red_Aleatoria(unsigned int Num_Enrutadores, int Prob);
    void Agregar_Enrutador();
    void Eliminar_Enrutador();
    string Obtener_Enlaces(unsigned int row, string Nombre_Archivo);
    void Modificar_Costo();
private:
    void Leer_Archivo();
    void Escribir_Archivo(string Nombre_Archivo, string info);
    string Vector_a_String(vector<string> info);
    bool Nombre_enrutador_existe(char nombre);
    vector<string> split_string(string info, char delimitador);
    string Datos, Nombre_Archivo;
    char limit_append, limit_col;
};
#endif // ENRUTADOR_H
