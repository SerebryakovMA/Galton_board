#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <list>
#include <iterator>
#include <numeric>
using namespace std;

constexpr int num_rows = 15;
constexpr int num_cols = 150;
constexpr int central_col = (num_cols -1) / 2;

void update_beans_in_cell_forward_backward(list<double> (&counts)[num_rows][num_cols], int row_idx, int col_idx){
    auto& beans = counts[row_idx][col_idx];
    auto& next_row_beans = counts[row_idx+1][col_idx];
    auto& next_col_beans = counts[row_idx][min(col_idx+1, num_cols - 1)];
    auto& prev_col_beans = counts[row_idx][max(col_idx-1, 0)];
    const double coeff = 5 * 3 * 6.5821195144 * 1E-19;
    for (auto bean = begin(beans); bean != end(beans); ++bean){
        int r = rand() % 3;
        if (r == 0){
            next_row_beans.push_back(*bean * (1.0 - coeff * double((col_idx - central_col) * (col_idx - central_col))));
        }
        else if (r == 1) {
            next_col_beans.push_back(*bean);
        }
        else if (r == 2) {
            prev_col_beans.push_back(*bean);
        }
        bean = prev(beans.erase(bean));
    }
    for (auto bean = prev(end(beans)); bean != prev(begin(beans)); --bean){
        int r = rand() % 3;
        if (r == 0){
            next_row_beans.push_back(*bean);
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

    const int beans = 1000;
    const double mass = 1.0;

    counts[0][central_col].resize(beans, mass);
    const int Runs = 1000;
    for (int run = 0; run < Runs; ++run){
        for (int row = num_rows - 2; row >= 0; --row) {
            for (int col = 0; col < num_cols; col++) {
                update_beans_in_cell_forward_backward(counts, row, col);
            }
        }
    }

    ofstream fout;
    fout.open("output.csv");
    // for (int row = 0; row < num_rows; row++){
        int row = num_rows -1 ;
        for (int j = 0; j < num_cols; j++){
            fout << setprecision(5) << setw(7) << accumulate(counts[row][j].begin(), counts[row][j].end(), 0.0) << ",";
        }
        fout << endl;
    // }
    fout.close();


return 0;
}