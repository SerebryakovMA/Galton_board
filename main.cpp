#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <cmath>
using namespace std;

int main() {
    srand(time(0));
    double* counts[10];

    for (int i = 0; i < 10; i++) {
        counts[i] = new double[i + 1];
        for (int j = 0; j <= i; j++) {
            counts[i][j] = 0;
        }
    }
const int Runs = 1000;
const double coeff = 5 * 3 * 6.5821195144 * pow(10, -19);

for (int run = 0; run < Runs; run++) {
    counts[0][0]++;
    int j = 0;
    for (int i = 1; i < 10; i++) {
        int r = rand() % 2;
        if (r == 1){
            j++;
        }
        counts[i][j] += (1 - coeff * j * j);
}
}

ofstream fout;
fout.open("output.csv");
for (int i = 0; i < 10; i++){
    for (int j = 0; j <= i; j++){
        fout << setw(4) << counts[i][j] << ",";
    }
    fout << endl;
}
fout.close();

for (int i = 0; i < 10; i++){
    delete[] counts[i];
}

return 0;
}