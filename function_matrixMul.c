void matMul(const double *a, const double *b, double *c, int m, int p, int n)
{
    int i, j, k;
    for (i = 0; i < m; i++)
    {
        for (j = 0; j < n; j++)
        {
            double sum = 0;
            for (k = 0; k < p; k++)
            {
                sum += a[i * p + k] * b[k * n + j];
            }
            c[i * n + j] = sum;
        }
    }
}