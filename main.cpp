#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <cmath>
using namespace std;

int main() {
    srand(time(0));
    constexpr int num_rows = 11;
    struct gap {
        int num;
        double mass;
    };
    gap* counts[num_rows];

    for (int i = 0; i < num_rows; i++) {
        counts[i] = new gap[num_rows];
        for (int j = 0; j <= i; j++) {
            counts[i][j].mass = 0;
            counts[i][j].num = 0;
        }
    }
    const int Runs = 100;
    const double coeff = 5 * 3 * 6.5821195144 * pow(10, -19);

    for (int run = 0; run < Runs; run++) {
        counts[(num_rows -1) / 2][0].num++;
        int j = 0;
        for (int i = 1; i < num_rows-1; i++) {
            int r = rand() % 3;
            if (r == 0){
                counts[i][j].num--;
                counts[i][j-1].num++;
                counts[i][j-1].mass += 1;
            }
            if (r == 1) {
                counts[i][j].num--;
                counts[i+1][j].num++;
                counts[i+1][j].mass += 1;
            }
            if (r == 2) {
                counts[i][j].num--;
                counts[i][j+1].num++;
                counts[i][j+1].mass += 1;
            }
        }
    }

    ofstream fout;
    fout.open("output.csv");
    for (int i = 0; i < num_rows; i++){
        for (int j = 0; j <= i; j++){
            fout << setw(4) << counts[i][j].num << ",";
        }
        fout << endl;
}
fout.close();

for (int i = 0; i < num_rows; i++){
    delete[] counts[i];
}

return 0;
}