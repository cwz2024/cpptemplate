int zeller(int year, int mon, int day)
{
    if (mon <= 2)
    {
        mon += 12;
        year--;
    }
    int c = year / 100;
    year %= 100;
    int w = (year + year / 4 + c / 4 - 2 * c + 13 * (mon + 1) / 5 + day - 1) % 7;
    if (w < 0)
        w += 7;
    return w;
}
int isleapyear(int n)
{
    return (n % 400 == 0 || (n % 100 != 0 && n % 4 == 0));
}