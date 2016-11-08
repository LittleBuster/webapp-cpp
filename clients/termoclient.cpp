#include "termoclient.h"
#include <iostream>

using namespace std;


TermoClient::TermoClient()
{
}

void TermoClient::setMaxTemp(float temp)
{
    // Connecting to device
    // Setting max temp
    // Closing connection
    cout << "Termo (C): Temperature was setted." << endl;
}

float TermoClient::getMaxTemp()
{
    return 22.1f;
}
