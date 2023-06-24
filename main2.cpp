#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Point.h"
#include "Node.h"
#include "QuadTree.h"
using namespace std;

struct Data {
    string city;
    int population;
    double latitude;
    double longitude;
};

vector<Data> readDataBase(int numLines) {
    ifstream myfile("worldcitiespop_fixed.csv");
    vector<Data> dataBase;

    if (!myfile.is_open()) {
        cout << "No se pudo abrir el archivo." << endl;
        return dataBase;
    }

    string line;
    getline(myfile, line);

    for (int i = 0; i < numLines; i++) {
        getline(myfile, line);

        istringstream aux(line); // Convierte el string obtenido en un stream

        string field;
        int currentField = 0;

        Data dataAux; // Creamos un data para agregar al vector

        while (getline(aux, field, ';')) { // Lee el string usando ";" como delimitador
            int commaPos = field.find(','); // La base de datos trae los decimales con comas, así que las convertimos en puntos
            if (commaPos != string::npos) {
                field[commaPos] = '.';
            }

            switch (currentField) {
                case 1: // City
                    dataAux.city = field;
                    break;
                case 4: // Population
                    dataAux.population = stoi(field);
                    break;
                case 5: // Latitude
                    dataAux.latitude = stod(field);
                    break;
                case 6: // Longitude
                    dataAux.longitude = stod(field);
                    break;
                default:
                    break;
            }

            currentField++;
        }

        dataBase.push_back(dataAux);
    }

    return dataBase;
}

int main() {
    int numLines = 10; // Número de líneas a leer

    vector<Data> data = readDataBase(numLines);

    for (const auto& node : data) {
        cout << "Ciudad: " << node.city << endl;
        cout << "Poblacion: " << node.population << endl;
        cout << "Latitud: " << node.latitude << endl;
        cout << "Longitud: " << node.longitude << endl;
        cout << endl;
    }

    return 0;
}
