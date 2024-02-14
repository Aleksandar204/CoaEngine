#ifndef TIME_H
#define TIME_H
static double dt;
void setDeltaTime(double d)
{
    dt = d;
}
double getDeltaTime()
{
    return dt;
}
#endif