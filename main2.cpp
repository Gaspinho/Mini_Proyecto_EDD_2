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
    vector<int> numCities = {100000, 200000, 400000, 800000, 1600000, 3173648}; // Números de ciudades a probar
    int numExperiments = 20; // Número de experimentos por cada número de ciudades

    for (const auto& numLines : numCities) {
        double totalTime = 0;

        for (int experiment = 0; experiment < numExperiments; experiment++) {
            vector<Data> data = readDataBase(numLines);

            // Crear el quadtree
            QuadTree quadtree(Point(0, 0), Point(10000000, 10000000)); // Ajusta los límites superiores derecho según tus necesidades

            // Iniciar el conteo del tiempo
            auto startTime = chrono::high_resolution_clock::now();

            // Insertar las ciudades en el quadtree
            for (const auto& node : data) {
                quadtree.insert(Point(node.latitude, node.longitude), node.population);
            }

            // Finalizar el conteo del tiempo
            auto endTime = chrono::high_resolution_clock::now();

            // Calcular la duración de la inserción
            auto duration = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();

            totalTime += duration;
        }
        
        // Calcular el tiempo promedio
        double averageTime = totalTime / numExperiments;

        // Imprimir el resultado
        cout << "Tiempo promedio de inserción para " << numLines << " ciudades: " << averageTime << " ms" << endl;
    }

    return 0;
}
