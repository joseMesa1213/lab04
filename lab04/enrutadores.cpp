#include "enrutadores.h"

enrutadores::enrutadores()
{
    limit_append = '\n';
    Nombre_Archivo=Obtener_Nombre_Archivo();
    limit_col = ' ';
}

string enrutadores::Obtener_Enrutadores(string Nombre_Archivo)
{
    Asignar_Nombre(Nombre_Archivo);
    Leer_Archivo();
    return Datos;
}

void enrutadores::Asignar_Nombre(string Nombre_Archivo)
{
    this->Nombre_Archivo = Nombre_Archivo;
}

string enrutadores::Obtener_Nombre_Archivo()
{
    return Nombre_Archivo;
}

void enrutadores::Generar_red_Aleatoria(unsigned int Num_Enrutadores, int Prob)
{
    Nombre_Archivo = "rand_network.txt";
    srand(time(NULL));
    int Max_Costo=500;
    vector<string> info;
    string letras_generadas;
    for (unsigned int i=0;i < Num_Enrutadores;i++) {
        char letra = rand() % 26 + 'A';
        if (letras_generadas.find(letra) == string::npos) {
            letras_generadas.push_back(letra);
        }
        else
            i--;
    }
    for (unsigned int i = 0; i < Num_Enrutadores - 1; i++) {
        for (unsigned int j = i + 1; j < Num_Enrutadores; j++) {
            char origen = letras_generadas[i], destino = letras_generadas[j];
            if (origen > destino) {
                // Si las letras no están en orden, intercambiarlas
                char temp = origen;
                origen = destino;
                destino = temp;
            }
            // Calcular si debe establecerse un costo
            if (rand() % 100 + 1 <= Prob) {
                int costo = rand() % Max_Costo + 1;
                info.push_back(string(1, origen) + " " + string(1, destino) + " " + to_string(costo));
            }
            else
                info.push_back(string(1, origen) + " " + string(1, destino) + " " + to_string(-1));
        }
    }
    Escribir_Archivo(Nombre_Archivo,Vector_a_String(info));
}

void enrutadores::Leer_Archivo()
{
    fstream file;
    file.open(Nombre_Archivo, ios_base::in);
    Datos="";
    while (!file.eof() && file.is_open()) {
        Datos.push_back(file.get());
    }
    Datos.pop_back();
    file.close();
}

void enrutadores::Agregar_Enrutador()
{
    char nombre, destino;
    int costo;
    ostringstream os;
    cout << "Ingrese el nombre del nuevo enrutador: ";
    cin >> nombre;
    if (Nombre_enrutador_existe(nombre)){
       cout << "El enrutador a agregar ya existe en la matriz de adyacencia\n";
       return;
    }
    cout << "Ingrese el nombre del enrutador de destino: ";
    cin >> destino;
    if (!Nombre_enrutador_existe(destino)){
       cout << "El enrutador de destino no existe";
       return;
    }
    cout << "Ingrese el costo asociado: ";
    cin >> costo;
    os << nombre << " " << destino << " " << costo;
    string data = os.str();
    vector<string> info = split_string(Datos,'\n');
    info.push_back(data);
    Escribir_Archivo(Nombre_Archivo, Vector_a_String(info));
    cout << "Enrutador agregado exitosamente" << endl;
}

void enrutadores::Eliminar_Enrutador()
{
    char nombre;
    cout << "Ingrese el nombre del enrutador a eliminar: ";
    cin >> nombre;
    if (!Nombre_enrutador_existe(nombre)) {
        cout << "Error: el enrutador '" << nombre << "' no existe." << endl;
        return;
    }
    vector<string> info = split_string(Datos, '\n');
    for (unsigned int i=0;i<info.size();i++){
        if (info[i].find(nombre) != string::npos){
            info.erase(info.begin() + i);
            i--;
        }
    }
    Escribir_Archivo(Nombre_Archivo, Vector_a_String(info));
}

string enrutadores::Obtener_Enlaces(unsigned int row, string Nombre_Archivo)
{
    vector<string> info;
    Asignar_Nombre(Nombre_Archivo);
    Leer_Archivo();
    info = split_string(Datos,'\n');
    if (row>=info.size())
        return "";
    return info[row];
}

void enrutadores::Modificar_Costo()
{
    char origen, destino;
    int Nuevo_costo=0;
    cout << "A continuacion ingrese los enrutadores a los cuales quieres cambiarles el costo" << endl;
    cout << "Ingrese el enrutador de origen: ";
    cin >> origen;
    cout << "Ingrese el enrutador de destino: ";
    cin >> destino;
    if (Nombre_enrutador_existe(origen) && Nombre_enrutador_existe(destino)){
        cout << "Ingrese el nuevo costo que tendra la conexion: ";
        cin >> Nuevo_costo;
    }
    vector<string> info = split_string(Datos,'\n');
    for (unsigned int i=0;i<info.size();i++){
        if (info[i].find(origen) != string::npos && info[i].find(destino) != string::npos){
            istringstream is(info[i]);
            string enrutador1, enrutador2;
            int costo;
            is >> enrutador1 >> enrutador2 >> costo;
            costo = Nuevo_costo;
            info[i] = enrutador1 + " " + enrutador2 + " " + to_string(costo);
            break; // salir del ciclo
        }
        else{
            ostringstream os;
            os << origen << " " << destino << " " << Nuevo_costo;
            string data = os.str();
            info.push_back(data);
        }
    }
    Escribir_Archivo(Nombre_Archivo, Vector_a_String(info));
}


void enrutadores::Escribir_Archivo(string Nombre_Archivo, string info)
{
    fstream file;
    file.open(Nombre_Archivo, ios_base::out);
    file << info;
    file.close();
}

vector<string> enrutadores::split_string(string info, char delimitador)
{
    int pos = 0, char_pos;
    vector<string> aux;

    char_pos = info.find(delimitador,pos);

    while (char_pos != -1) {
        aux.push_back(info.substr(pos,char_pos-pos));
        pos = char_pos +1;
        char_pos = info.find(delimitador,pos);
    }
    aux.push_back(info.substr(pos,info.size()-pos));

    return  aux;
}

string enrutadores::Vector_a_String(vector<string> info)
{
    string aux;
    for(unsigned long long i=0; i < info.size(); i++){
        aux += info[i];
        if (i+1==info.size())
            aux.push_back('\0');
        else
            aux.push_back('\n');
    }

    return aux;
}

bool enrutadores::Nombre_enrutador_existe(char nombre)
{
    Obtener_Enrutadores(Nombre_Archivo);
    return Datos.find(nombre) != string::npos;
}
