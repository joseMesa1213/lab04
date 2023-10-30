#include "redes.h"

Redes::Redes()
{
    Nombre_Archivo = Enrutador.Obtener_Nombre_Archivo();
}

void Redes::Obtener_red()
{
    string aux, Origen, Destino;
    int Costo=0;
    Enlaces.clear();
    aux = Enrutador.Obtener_Enlaces(0,Nombre_Archivo);
    for (unsigned int i=1;!aux.empty();i++){
        stringstream Separate(aux);
        Separate >> Origen >> Destino >> Costo;
        Enlaces[Origen][Origen] = 0;
        Enlaces[Origen][Destino] = Costo;
        Enlaces[Destino][Origen] = Costo;
        Enlaces[Destino][Destino] = 0;
        aux = Enrutador.Obtener_Enlaces(i,Nombre_Archivo);
    }
    imprimirMatrizAdyacente(Enlaces);
}

void Redes::Asignar_Nombre(string Nombre_Archivo)
{
    this->Nombre_Archivo = Nombre_Archivo;
}

void Redes::imprimirMatrizAdyacente(map<string, map<string, int>> enlaces) {
    // Encontrar el tamaño máximo de cada celda de la matriz
    int max_length = 0;
    for (const auto& enrutador : enlaces) {
        for (const auto& enlace : enrutador.second) {
            max_length = max(max_length, static_cast<int>(to_string(enlace.second).size()));
        }
        max_length = max(max_length, static_cast<int>(enrutador.first.size()));
    }
    max_length += 1;

    // Imprimir encabezados de columna
    cout << setw(max_length+1) << ' ';
    for (const auto& enrutador : enlaces) {
        cout << setw(max_length) << enrutador.first << '|';
    }
    cout << '\n';

    // Imprimir separador horizontal
    for (unsigned int i = 0; i < (enlaces.size() + 1) * max_length + enlaces.size(); i++) {
        cout << '-';
    }
    cout << '\n';

    // Imprimir matriz de adyacencia
    for (const auto& enrutador1 : enlaces) {
        cout << setw(max_length) << enrutador1.first << '|';
        for (const auto& enrutador2 : enlaces) {
            if (enrutador1.second.count(enrutador2.first)) {
                cout << setw(max_length) << enrutador1.second.at(enrutador2.first) << '|';
            } else {
                cout << setw(max_length) << "-1" << '|';
            }
        }
        cout << '\n';

        // Imprimir separador horizontal
        if (&enrutador1.first != &enlaces.rbegin()->second.begin()->first) {
            for (unsigned int i = 0; i < (enlaces.size() + 1) * max_length + enlaces.size(); i++) {
                cout << '-';
            }
            cout << '\n';
        }
    }
}

void Redes::RutaReducida(string origen, string destino)
{
    ways.clear();
    int cont=0;
    string prueba;
    map<char,int>::iterator itC;
    map<char,int> conex = costos(origen);
    prueba = crearCaminos(origen,destino);
    if(validar(prueba))
        anadirCamino(prueba);
    for(itC=conex.begin();itC!=conex.end();itC++,cont++){
        string Char2string(1, itC->first);
        prueba = crearCaminos(Char2string,destino);
        prueba.append(origen);
        if(validar(prueba))
            anadirCamino(prueba);
    }
        cout<<"\nLa ruta mas eficiente es: "<<endl;
        prueba = caminoMasCorto();
        cout<<prueba<<" con un costo de "<<ways[prueba]<<endl;
}

string Redes::caminoMasCorto()
{
    int better=1000,cont=0;
    string chosen;
    bool flag =1;
    for(itW=ways.begin();itW!=ways.end();itW++,++cont){
        if(flag){
            cout<<"\nCamino "<<cont+1<<endl;
            cout<<itW->first<<" con un costo de "<<itW->second<<endl;
        }
        else {
            if(itW->second<better && itW->second>0){
                chosen = itW->first;
                better = itW->second;
            }
            else if(cont==0){
                chosen = itW->first;
                better = itW->second;
            }
        }
    }
    return chosen;
}

bool Redes::CaminoDirecto(string origen, string destino, map<string,map<string,int>>::iterator it1,map<string,int>::iterator it2){
    bool Hallado = false;
    it1 = Enlaces.find(origen);
    if (it1 != Enlaces.end()) {
        it2 = it1->second.find(destino);
        if (it2 != it1->second.end()) {
            camino.append(destino);
            camino.append(origen);
            Hallado=true;
        }
    }
    return Hallado;
}


string Redes::crearCaminos(string origen, string destino)
{
    map<string,map<string,int>>::iterator it1;
    map<string,int>::iterator it2;
    camino.clear();
    if(CaminoDirecto(origen,destino,it1,it2))
        return camino;
    if (empty(camino)) {
        for (it1 = Enlaces.begin(); it1 != Enlaces.end(); ++it1) {
            if (it1->first != origen) {
                if (CaminoDirecto(it1->first, destino, it1, it2)) {
                    if (camino.empty() || to_string(camino[0]) != origen) {
                        camino.append(origen);
                    }
                    break;
                }
            }
        }
    }
    return camino;
}

void Redes::anadirCamino(string camino){
    int costoTotal=0;
    for(unsigned int i=0; i<camino.length()-1; i++){
        string origen(1, camino[i]);
        string destino(1, camino[i+1]);
        int costo = Enlaces[origen][destino];
        costoTotal += costo;
    }
    ways.insert(pair<string,int>(camino,costoTotal));
}


bool Redes::validar(string camino)
{
    bool correcto = false;
    if(ways.find(camino)==ways.end()) correcto = true;
    return correcto;
}

map<char, int> Redes::costos(string Origen)
{
    for (auto it1 = Enlaces.begin(); it1 != Enlaces.end(); ++it1) {
        if (it1->first == Origen) {
            for (auto it2 = it1->second.begin(); it2 != it1->second.end(); ++it2) {
                if (it2->second==0)
                    continue;
                else
                    Conexiones[it2->first[0]] += it2->second;
            }
            break;
        }
    }
    return Conexiones;
}

