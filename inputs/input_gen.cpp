#include <iostream>
#include <algorithm>
#include <chrono>
#include <random>
#include <fstream>

using namespace std;

int main(int argc, char *argv[]) {
    int n = atoi(argv[1]);
    int m = atoi(argv[2]);

    //ofstream inputFile;
    //inputFile.open("input.txt");
    cout << n << " " << m << endl;

    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    default_random_engine generator (seed);

    // Definindo distribuição normal com média de 3 e desvio padrão de 1
    normal_distribution<double> distribution_dif(3, 1.0);

    uniform_int_distribution<int> distribution_hr(0, 23);
    uniform_int_distribution<int> distribution_cat(1, m);

    vector<int> maxFilmes(m); // Vetor para armazenar o máximo de filmes por categoria
    for (int i = 0; i < m; i++) {
        maxFilmes[i] = distribution_cat(generator); // Gerando o máximo de filmes para cada categoria
        cout << maxFilmes[i] << " "; // Escrevendo o valor no arquivo de entrada
    }
    cout << endl;

    for (int i = 0; i < n; i++) {
        int hora_inicio = distribution_hr(generator);
        double dif_media = distribution_dif(generator);
        int hora_fim = ((int)hora_inicio + (int)round(dif_media)) % 24;
        int categoria = distribution_cat(generator);

        cout << hora_inicio << " " << hora_fim << " " << categoria << endl;
    }


    //inputFile.close();
    return 0;
}

//g++ -std=c++11 -I /usr/local/include <seu_programa>.cpp -o <seu_programa> -L/usr/local/lib -lboost_system -lboost_filesystem
//g++ -I /opt/homebrew/Cellar/boost/1.81.0_1/include -L /opt/homebrew/Cellar/boost/1.81.0_1/lib -lboost_random input_gen.cpp -o input_gen