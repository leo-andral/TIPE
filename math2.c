float smoothstep(float x) {
    if (x <= 0) return 0.0;
    if (1 <= x) return 1.0;
    return x*x * (3.0 - 2.0 * x);
}

float smootherstep(float x) {
    if (x <= 0) return 0.0;
    if (1 <= x) return 1.0;
    return x * x * x * (x * (6.0 * x - 15.0) + 10.0);
}