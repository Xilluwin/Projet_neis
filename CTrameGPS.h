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
    float fNoeud;

    void TraiterTrame();
    unsigned char ASCIIHexToInt(char * pASCII);
    bool ControlerIntegrite();
    bool IdentifierTrame();
    string ExtraireChamp(unsigned char ucRangChamp);
    float NoeudToMetersPerSecond(float fNoeud);
    int TempsToSeconds(string Temps);

public:
    CTrameGPS( string );
    ~CTrameGPS();

    float calculDistanceKilometre(float vn_1, float vn, string tnStr, string tn_1Str);
    string GetHorodatageForDB();
    string  GetTrame();
    bool    GetIntegrite();
    float   GetVitesse();
    float   GetLatitude();
    float   GetLongitude();
    string  GetTemps();
    string  GetDate();
    string  GetIdentifiant();
    float   GetNoeud();

};

