#include <iostream>
#include <fstream>
#include <io.h>     // _pipe, _read, _write, _close
#include <fcntl.h>  // O_BINARY
#include <cmath>    // pow, fabs

using namespace std;

int main() {
    int fd[2]; // pipe: fd[0] - read, fd[1] - write
    if (_pipe(fd, 4096, O_BINARY) == -1) {
        cerr << "Pipe creation failed\n";
        return 1;
    }

    ifstream in("Input.txt");
    if (!in) {
        ofstream err("Error.txt");
        err << "Не удалось открыть Input.txt\n";
        return 1;
    }

    double x, e;
    in >> x >> e;
    if (!in || e <= 0.001 || e >= 0.01) {
        ofstream err("Error.txt");
        err << "Некорректные данные: x=" << x << ", e=" << e << endl;
        return 1;
    }

    int i = 0;
    while (true) {
        double fact = 1.0;
        for (int j = 1; j <= i; j++) fact *= j;
        double term = pow(x, i) / fact;

        if (fabs(term) < e) break;

        if (_write(fd[1], &term, sizeof(double)) == -1) {
            ofstream err("Error.txt");
            err << "Ошибка записи в pipe в процессе First\n";
            return 1;
        }
        i++;
    }
    _close(fd[1]);

    double sum = 0.0, value;
    while (_read(fd[0], &value, sizeof(double)) > 0) {
        sum += value;
    }
    _close(fd[0]);

    ofstream out("Output.txt");
    if (!out) {
        ofstream err("Error.txt");
        err << "Не удалось открыть Output.txt\n";
        return 1;
    }
    out << "Сумма последовательности: " << sum << endl;

    return 0;
}
