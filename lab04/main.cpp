#include "enrutadores.h"
#include "redes.h"

using namespace std;

void menu1(enrutadores enrutador, Redes red, string Archivo);
void menu2(enrutadores enrutador, Redes red, string Archivo);

int main()
{
    int opc=0;
    string Archivo, nombre2;
    enrutadores enrutador;
    Redes red;
    cout << "\t\tRED DE REDES" << endl;
    cout << "BIENVENIDO AL PROGRAMA DE ENRUTADORES, QUE DESEAS HACER" << endl;
    cout << "1. Cargar una red" << endl;
    cout << "2. Crear una red aleatoria"<< endl;
    cout << "Escoja una opcion: ";
    cin>>opc;

    switch (opc) {

    case 1:
        cout<<"Ingrese el nombre del Archivo donde se encuentra la Red: ";
        cin >> Archivo;
        menu1(enrutador, red, Archivo);
        break;

    case 2:
        menu2(enrutador, red, Archivo);
        break;
    }
    return 0;
}

void menu1(enrutadores enrutador, Redes red, string Archivo)
{
    int opcion = 0;
    string nombre, nombre2;
    enrutador.Obtener_Enrutadores(Archivo);
    system("cls");
    cout << "La matriz de adyacencia obtenida es:" << endl;
    red.Asignar_Nombre(Archivo);
    red.Obtener_red();
    cout << "Ahora podras hacer una de las siguientes opciones:" << endl;

    while (opcion != 6) {
        cout << "1. Agregar enrutador" << endl;
        cout << "2. Eliminar enrutador" << endl;
        cout << "3. Modificar un enrutador existente" << endl;
        cout << "4. Imprimir la matriz de adyacencia" << endl;
        cout << "5. Calcular el camino mas corto" << endl;
        cout << "6. Salir del programa" << endl;
        cout << "Selecciona una opcion:" << endl;
        cin >> opcion;
        system ("cls");

        switch (opcion) {
            case 1:
                enrutador.Agregar_Enrutador();
                system("pause");
                system ("cls");
                break;
            case 2:
                enrutador.Eliminar_Enrutador();
                cout << "Enrutador eliminado exitosamente" << endl;
                system("pause");
                system ("cls");
                break;
            case 3:
                enrutador.Modificar_Costo();
                cout << "Se ha modificado el costo de dos enrutadores exitosamente" << endl;
                system("pause");
                system ("cls");
                break;
            case 4:
                red.Asignar_Nombre(Archivo);
                red.Obtener_red();
                break;
            case 5:
                cout<<"Ingrese el nombre Origen:";
                cin>>nombre;
                cout<<"Ingrese el nombre Destino:";
                cin>>nombre2;
                red.RutaReducida(nombre,nombre2);
                system("pause");
                system ("cls");
                break;
            case 6:
                cout << "Saliendo del programa..." << endl;
                break;
            default:
                cout << "Opcion no valida. Por favor intente de nuevo." << endl;
                break;
        }
    }
}


void menu2(enrutadores enrutador, Redes red, string Archivo)
{
    int Num_Enrutadores, Prob;
    cout << "Ingrese el numero de enrutadores que deseas en tu red: ";
    cin >> Num_Enrutadores;
    cout << "Ingrese la probabilidad de exito que tendra un enlace: ";
    cin >> Prob;
    enrutador.Generar_red_Aleatoria(Num_Enrutadores, Prob);
    Archivo=enrutador.Obtener_Nombre_Archivo();
    cout << "La red se ha generado satisfactoriamente." << endl;
    system ("pause");
    system ("cls");
    int opcion = 0;
    string nombre, nombre2;
    enrutador.Obtener_Enrutadores(Archivo);
    system("cls");
    cout << "La matriz de adyacencia obtenida es:" << endl;
    red.Asignar_Nombre(Archivo);
    red.Obtener_red();
    cout << "Ahora podras hacer una de las siguientes opciones:" << endl;

    while (opcion != 6) {
        cout << "1. Agregar enrutador" << endl;
        cout << "2. Eliminar enrutador" << endl;
        cout << "3. Modificar un enrutador existente" << endl;
        cout << "4. Imprimir la matriz de adyacencia" << endl;
        cout << "5. Calcular el camino mas corto" << endl;
        cout << "6. Salir del programa" << endl;
        cout << "Selecciona una opcion:";
        cin >> opcion;
        system ("cls");

        switch (opcion) {
            case 1:
                enrutador.Agregar_Enrutador();
                system("pause");
                system ("cls");
                break;
            case 2:
                enrutador.Eliminar_Enrutador();
                cout << "Enrutador eliminado exitosamente" << endl;
                system("pause");
                system ("cls");
                break;
            case 3:
                enrutador.Modificar_Costo();
                cout << "Se ha modificado el costo de dos enrutadores exitosamente" << endl;
                system("pause");
                system ("cls");
                break;
            case 4:
                red.Asignar_Nombre(Archivo);
                red.Obtener_red();
                break;
            case 5:
                cout<<"Ingrese el nombre Origen:";
                cin>>nombre;
                cout<<"Ingrese el nombre Destino:";
                cin>>nombre2;
                red.RutaReducida(nombre,nombre2);
                system("pause");
                system ("cls");
                break;
            case 6:
                cout << "Saliendo del programa..." << endl;
                break;
            default:
                cout << "Opcion no valida. Por favor intente de nuevo." << endl;
                break;
        }
    }
}
