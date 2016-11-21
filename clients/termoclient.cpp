#include "termoclient.h"
#include <iostream>

using namespace std;


void TermoClient::connect(const string &ip, unsigned port)
{
    TcpClient::connect(ip, port);
}

void TermoClient::setMaxTemp(float temp)
{
    // Connecting to device
    // Setting max temp
    // Closing connection
    cout << "Termo (C): Temperature was setted." << endl;
}

float TermoClient::getMaxTemp() const
{
    return 22.1f;
}

void TermoClient::close() const
{
    TcpClient::close();
}
