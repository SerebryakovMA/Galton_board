#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <list>
#include <iterator>
#include <numeric>
#include "../matplotlib-cpp/matplotlibcpp.h"

namespace plt = matplotlibcpp;
using namespace std;

constexpr int num_rows = 150;
constexpr int num_cols = 150;
constexpr int central_col = (num_cols -1) / 2;

void update_beans_in_cell_forward_backward(list<double> (&counts)[num_rows][num_cols], int row_idx, int col_idx){
    auto& beans = counts[row_idx][col_idx];
    auto& next_row_beans = counts[row_idx+1][col_idx];
    auto& next_col_beans = counts[row_idx+1][min(col_idx+1, num_cols - 1)];
    auto& prev_col_beans = counts[row_idx+1][max(col_idx-1, 0)];
    const double coeff = 5. * 3. * 6.5821195144 * 1E-19;
    for (auto bean = begin(beans); bean != end(beans); ++bean){
        int r = rand() % 3;
        if (r == 0){
            next_row_beans.push_back(*bean * (1.0 - coeff * pow(fabs(col_idx - central_col), 2)));
        }
        else if (r == 1) {
            next_col_beans.push_back(*bean);
        }
        else if (r == 2) {
            prev_col_beans.push_back(*bean);
        }
        bean = prev(beans.erase(bean));
    }
}

int main() {
    srand(time(0));
    list<double> counts[num_rows][num_cols];

    const int beans = 1000000;
    const double mass = 1.0;

    counts[0][central_col].resize(beans, mass);
    const int Runs = 100;
    for (int run = 0; run < Runs; ++run){
        for (int row = 0; row < num_rows - 1; ++row) {
            for (int col = 0; col < num_cols; col++) {
                update_beans_in_cell_forward_backward(counts, row, col);
            }
        }
    }

    ofstream fout;
    fout.open("output.csv");
    int row = num_rows -1 ;
    for (int j = 0; j < num_cols; j++){
        fout << setprecision(3) << fixed << accumulate(counts[row][j].begin(), counts[row][j].end(), 0.0) << ",";
    }
    fout << endl;
    fout.close();

    vector<int> x(num_cols);
    iota(x.begin(), x.end(), 0);
    std::vector<double> mass_per_column;
    std::transform(std::begin(counts[num_rows-1]), std::end(counts[num_rows-1]), std::back_inserter(mass_per_column),
                   [](const list<double>& masses){ return std::accumulate(masses.begin(), masses.end(), 0.0);});

    for (int j = 0; j < num_cols; j++){
        std::cout << x[j] << " ";
        std::cout << setprecision(3) << fixed << mass_per_column[j] << ",";
    }
    plt::plot(x, mass_per_column, "b");
    plt::save("galton.png");
    // plt::
    return 0;
}