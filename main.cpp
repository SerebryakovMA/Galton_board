#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
using namespace std;

int main() {
    srand(time(0));
    int* counts[10];

    for (int i = 0; i < 10; i++) {
        counts[i] = new int[i + 1];
        for (int j = 0; j <= i; j++) {
            counts[i][j] = 0;
        }
    }
const int Runs = 1000;

for (int run = 0; run < Runs; run++) {
    counts[0][0]++;
    int j = 0;
    for (int; i = 1; i < 10; i++) {
        int r = rand() % 2;
        if (r == 1){
            j++;
        }
        counts[i][j]++;
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