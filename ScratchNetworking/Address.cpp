#include "Address.h"

Address::Address()
{
    
    unsigned char a = 127;
    unsigned char b = 0;
    unsigned char c = 0;
    unsigned char d = 1;
    
    unsigned int callbackAddress = (a << 24) | (b << 16) | (c << 8) | d; /*creating an unsigned 32 bit int which is the format of the address*/

    address = callbackAddress;

    port = 30000;
}

Address::Address(unsigned char a, unsigned char b, unsigned char c, unsigned char d, unsigned short p)
{
    unsigned int addressConverted = (a << 24) | (b << 16) | (c << 8) | d; /*creating an unsigned 32 bit int which is the format of the address*/

    address = addressConverted;
    port = p;
}

Address::Address(unsigned int address, unsigned short port)
{
    this->address = address;
    this->port = port;
}

Address::Address(unsigned short port)
{
    unsigned char a = 127;
    unsigned char b = 0;
    unsigned char c = 0;
    unsigned char d = 1;
    
    unsigned int callbackAddress = (a << 24) | (b << 16) | (c << 8) | d; /*creating an unsigned 32 bit int which is the format of the address*/

    address = callbackAddress;

    this->port = port; 
}

unsigned int Address::getAddress() const
{
    return address;
}

unsigned char Address::GetA() const
{
    return address >> 24 & 0xFF; /*shifts the data by 24 bits and isolates the result*/
}

unsigned char Address::GetB() const
{
    return address >> 16 & 0xFF;
}

unsigned char Address::GetC() const
{
    return address >> 8 & 0xFF;
}

unsigned char Address::GetD() const
{
    return address & 0xFF;
}

unsigned short Address::getPort() const
{
    return port;
}
