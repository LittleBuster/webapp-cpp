/* Webapp test application
 *
 * Copyright (C) 2016 Sergey Denisov.
 * Written by Sergey Denisov aka LittleBuster (DenisovS21@gmail.com)
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public Licence 3
 * as published by the Free Software Foundation; either version 3
 * of the Licence, or (at your option) any later version.
 */


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
