#pragma once

#include <string>
using namespace std;

class CTrameGPS
{
private:
    string  Trame;

    bool    bIntegrite;
    size_t  TailleTrame;

    string  IdentifiantTrame;
    string  Horodatage;
    float   fVitesse;
    float   fLatitude;
    float   fLongitude;
    string  Date;
    string  Temps;

    void TraiterTrame();
    unsigned char ASCIIHexToInt(char * pASCII);
    bool ControlerIntegrite();
    bool IdentifierTrame();
    string ExtraireChamp(unsigned char ucRangChamp);

public:
    CTrameGPS( string );
    ~CTrameGPS();

    string GetHorodatageForDB();  // idk about that one boss
    string  GetTrame();
    bool    GetIntegrite();
    float   GetVitesse();
    float   GetLatitude();
    float   GetLongitude();
    string  GetTemps();
    double  GetTempsHeure();
    string  GetDate();
    string  GetIdentifiant();

};

