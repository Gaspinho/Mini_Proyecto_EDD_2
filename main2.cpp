#include <bits/stdc++.h>
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
                case 1:
                    dataAux.city = field;
                    break;
                case 4:
                    dataAux.population = stoi(field);
                    break;
                case 5:
                    dataAux.latitude = stod(field);
                    break;
                case 6:
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
    vector<int> numCities = {100000, 200000, 400000, 800000, 1600000, 3173648};
    int numExperiments = 20;

    for (const auto& numLines : numCities) {
        double totalTime = 0;

        for (int experiment = 0; experiment < numExperiments; experiment++) {
            vector<Data> data = readDataBase(numLines);

            
            QuadTree quadtree(Point(0, 0), Point(10000000, 10000000));

            auto startTime = chrono::high_resolution_clock::now();

            // Inserción de las ciudades.
            for (const auto& node : data) {
                quadtree.insert(Point(node.latitude, node.longitude), node.population);
            }

            auto endTime = chrono::high_resolution_clock::now();

            auto duration = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();

            totalTime += duration;
        }

        double averageTime = totalTime / numExperiments;

        cout << "Tiempo promedio de inserción para " << numLines << " ciudades: " << averageTime << " ms" << endl;
    }

    return 0;
}