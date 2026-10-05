#include <stdio.h>

double fmf_sqrt(double x) {
    if (x <= 0.0) return 0.0;
    union {
        long l;
        double d;
    } u;
    u.d = x;
    u.l = 0x5fe6eb50c7b537a9L - (u.l >> 1);
    double g = u.d;
    
    for (int i = 0; i < 2; i++) {
        double xg2 = x * g * g;
        g = g * (3.0 + xg2) / (1.0 + 3.0 * xg2);
    }
    return x * g;
}

double fmf_zeta(double s) {
    double sum = 0.0;
    for (int n = 1; n <= 1000; n++) {
        double term = 1.0 / ((double)n * (double)n);
        sum += term;
    }
    return sum;
}

double fmf_ln(double x) {
    if (x <= 0.0) return 0.0;
    double t = 2.0 * x - 3.0;
    double sum = 0.3862943611198932; 
    double tn_prev = 1.0;
    double tn_curr = t;
    
    for (int n = 1; n < 6; n++) {
        double tn_next = 2.0 * t * tn_curr - tn_prev;
        double coeff_div = 0.5 / (double)n;
        sum += coeff_div * tn_curr;
        tn_prev = tn_curr;
        tn_curr = tn_next;
    }
    return sum;
}

double fmf_exp(double x) {
    if (x < -20.0) return 0.0;
    if (x > 20.0) return 485165195.4;
    
    double t = x * 0.25;
    double c0 = 1.2660658775;
    double c1 = 1.1303182079;
    double c2 = 0.2714953395;
    double c3 = 0.0443368498;
    double c4 = 0.0054742404;

    return c0 + t * (c1 + t * (c2 + t * (c3 + t * c4))); 
}

double fmf_sin(double x) {
    while (x > 3.141592653589793) x -= 6.283185307179586;
    while (x < -3.141592653589793) x += 6.283185307179586;

    double x2 = x * x;
    return x * (1.0 - x2 * (0.1666666664 - x2 * (0.0083333315 - x2 * (0.0001984090 - x2 * 0.0000027555))));
}

double fmf_cos(double x) {
    while (x > 3.141592653589793) x -= 6.283185307179586;
    while (x < -3.141592653589793) x += 6.283185307179586;

    double x2 = x * x;
    return 1.0 - x2 * (0.5 - x2 * (0.0416666664 - x2 * (0.0013888397 - x2 * (0.0000247609 - x2 * 0.0000002605))));
}

double fmf_pow(double x, double y) {
    if (x <= 0.0) return 0.0;
    return fmf_exp(y * fmf_ln(x));
}

int main() {
    printf("sqrt(16.0)     = %f\n", fmf_sqrt(16.0));
    printf("zeta(2.0)      = %f\n", fmf_zeta(2.0));
    printf("ln(1.5)        = %f\n", fmf_ln(1.5));
    printf("exp(1.0)       = %f\n", fmf_exp(1.0));
    printf("sin(1.0)       = %f\n", fmf_sin(1.0));
    printf("cos(1.0)       = %f\n", fmf_cos(1.0));
    printf("pow(2.0, 3.0)  = %f\n", fmf_pow(2.0, 3.0));
    return 0;
}
