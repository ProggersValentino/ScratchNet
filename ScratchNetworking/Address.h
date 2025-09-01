#pragma once

/*all address related actions happen here from address creation to deletion*/
class Address
{
public:

    /*initialize with default callback address*/
    Address();

    Address(unsigned char a, 
                 unsigned char b, 
                 unsigned char c, 
                 unsigned char d, 
                 unsigned short p );

    Address(unsigned int address, 
                 unsigned short port );

    Address(unsigned short port);

    /*get individual address numbers*/
    unsigned char GetA() const;
    unsigned char GetB() const;
    unsigned char GetC() const;
    unsigned char GetD() const;

    unsigned int getAddress() const;
    
    /*get port*/
    unsigned short getPort() const;

    private:
    unsigned int address;
    unsigned short port;
};
