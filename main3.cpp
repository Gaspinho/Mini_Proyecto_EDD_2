#include <bits/stdc++.h>
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

        istringstream aux(line);

        string field;
        int currentField = 0;

        Data dataAux;

        while (getline(aux, field, ';')) { // La database usa ";" en vez de "," para separar los datos.
            int commaPos = field.find(',');
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
    int numCities = 3173648;
    int numExperiments = 20; 
    vector<int> distances = {100, 500, 1000, 10000, 100000};

    vector<Data> data = readDataBase(numCities);

    // Crear el quadtree
    QuadTree quadtree(Point(0, 0), Point(10000000, 10000000));

    // Inserción de las ciudades
    for (const auto& node : data) {
        quadtree.insert(Point(node.latitude, node.longitude), node.population);
    }

    for (const auto& distance : distances) {
        double totalTimeAggregate = 0;
        double totalTimeCount = 0;

        for (int experiment = 0; experiment < numExperiments; experiment++) {
            // Punto de referencia para las operaciones
            Point referencePoint(0, 0);

            auto startTimeAggregate = chrono::high_resolution_clock::now();

            int aggregateResult = quadtree.agreggateRegion(referencePoint, distance);

            auto endTimeAggregate = chrono::high_resolution_clock::now();

            auto durationAggregate = chrono::duration_cast<chrono::nanoseconds>(endTimeAggregate - startTimeAggregate).count();

            totalTimeAggregate += durationAggregate;

            auto startTimeCount = chrono::high_resolution_clock::now();

            int countResult = quadtree.countRegion(referencePoint, distance);

            auto endTimeCount = chrono::high_resolution_clock::now();

            auto durationCount = chrono::duration_cast<chrono::nanoseconds>(endTimeCount - startTimeCount).count();

            totalTimeCount += durationCount;
        }

        double averageTimeAggregate = totalTimeAggregate / numExperiments / 1000000.0;
        double averageTimeCount = totalTimeCount / numExperiments / 1000000.0;

        cout << "Tiempo promedio de agreggateRegion para distancia " << distance << ": " << averageTimeAggregate << " ms" << endl;
        cout << "Tiempo promedio de countRegion para distancia " << distance << ": " << averageTimeCount << " ms" << endl;
    }

    return 0;
}