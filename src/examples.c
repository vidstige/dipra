#include "dipra.h"

int main(int argc, const char* argv[]) {
    const size_t N = 1024;
    double x[N], y[N], alpha[N];
    dipra_render(x, y, alpha, N);
    return 0;
}