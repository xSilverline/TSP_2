//
// Created by Silver on 01.11.2024.
//

#ifndef TSP_2_TIMECOUNTER_H
#define TSP_2_TIMECOUNTER_H

#include <windows.h>
#include <iostream>


using namespace std;
static double freq;
static long long int counterStart;

static void startCounter() // FUNKCJA STARTUJĄCA LICZNIK DO POMIARU CZASU
{
    LARGE_INTEGER largeInteger;
    if(!QueryPerformanceFrequency(& largeInteger))
        cout<<"Blad zliczania czasu"<<endl;

    freq = double(largeInteger.QuadPart) / 1000.0;

    QueryPerformanceCounter(& largeInteger);
    counterStart = largeInteger.QuadPart;
}

static double getCounter() // FUNKCJA ZWRACAJĄCA OBECNY STAN LICZNIKA
{
    LARGE_INTEGER largeInteger;
    QueryPerformanceCounter(& largeInteger);
    return double(largeInteger.QuadPart-counterStart)/freq;
}


#endif //TSP_2_TIMECOUNTER_H
