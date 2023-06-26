#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "Point.h"
#include "Node.h"
#include "QuadTree.h"
#include <chrono>

using namespace std::chrono;
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
    int numCities = 3173647; // Número de ciudades constante
    int numExperiments = 20; // Número de experimentos por cada distancia
    vector<int> distances = {100, 500, 1000, 10000, 100000}; // Distancias a probar

    vector<Data> data = readDataBase(numCities);

    // Crear el quadtree
    QuadTree quadtree(Point(0, 0), Point(10000000, 10000000)); // Ajusta los límites superiores derecho según tus necesidades

    // Insertar las ciudades en el quadtree
    for (const auto& node : data) {
        quadtree.insert(Point(node.latitude, node.longitude), node.population);
    }

    for (const auto& distance : distances) {
        double totalTimeAggregate = 0;
        double totalTimeCount = 0;

        for (int experiment = 0; experiment < numExperiments; experiment++) {
            // Punto de referencia para las operaciones
            Point referencePoint(0, 0); // Ajusta el punto de referencia según tus necesidades

            // Iniciar el conteo del tiempo de agregación
            auto startTimeAggregate = chrono::high_resolution_clock::now();

            // Realizar la operación de agregación
            int aggregateResult = quadtree.aggregateRegion(referencePoint, distance);

            // Finalizar el conteo del tiempo de agregación
            auto endTimeAggregate = chrono::high_resolution_clock::now();

            // Calcular la duración de la operación de agregación en nanosegundos
            auto durationAggregate = chrono::duration_cast<chrono::nanoseconds>(endTimeAggregate - startTimeAggregate).count();

            // Sumar el tiempo de agregación al total
            totalTimeAggregate += durationAggregate;

            // Iniciar el conteo del tiempo de conteo
            auto startTimeCount = chrono::high_resolution_clock::now();

            // Realizar la operación de conteo
            int countResult = quadtree.countRegion(referencePoint, distance);

            // Finalizar el conteo del tiempo de conteo
            auto endTimeCount = chrono::high_resolution_clock::now();

            // Calcular la duración de la operación de conteo en nanosegundos
            auto durationCount = chrono::duration_cast<chrono::nanoseconds>(endTimeCount - startTimeCount).count();

            // Sumar el tiempo de conteo al total
            totalTimeCount += durationCount;
        }

        // Calcular los tiempos promedio en milisegundos
        double averageTimeAggregate = totalTimeAggregate / numExperiments / 1000000.0;
        double averageTimeCount = totalTimeCount / numExperiments / 1000000.0;

        // Imprimir los resultados
        cout << "Tiempo promedio de aggregateRegion para distancia " << distance << ": " << averageTimeAggregate << " ms" << endl;
        cout << "Tiempo promedio de countRegion para distancia " << distance << ": " << averageTimeCount << " ms" << endl;
    }

    return 0;
}