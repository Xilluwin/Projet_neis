#include "CTrameGPS.h"
#include "ccalcul.h"
#include "INIReader.h"
#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>
#include <iomanip>
#include <string>

using namespace std;



int main()
{
    CTrameGPS* TrameGPS = new CTrameGPS("$GPRMC,091303.000,A,4341.4196,N,00104.2376,W,0.09,137.78,120809,,,A*78");
    /*cout << TrameGPS->GetIntegrite() << endl;
    cout << TrameGPS->GetTrame() << endl;
    cout << TrameGPS->GetDate() << endl;
    cout << TrameGPS->GetTemps() << endl;
    cout << TrameGPS->GetLongitude() << endl;
    cout << TrameGPS->GetLatitude() << endl;*/


    delete TrameGPS;


    fstream Fichier;
    string Trame;
    CCalcul Calcul;
    double KilometrageTotal;

    CINIReader reader("projet_neis.ini");

    if (reader.ParseError() < 0) 
    {
        cout << "Can't load 'projet_neis.ini'\n";
        return 1;
    }

    cout << reader.GetInteger( "technicien", "kilometrage", 0 ) << endl;
        


    Fichier.open( "TramesGPS.nmea", fstream::in );
    if ( Fichier.is_open() == false )
    {
        cout << "Pb fichier" << endl;
        return 0;
    }
    while ( Fichier.eof() == false )
    {
        Fichier >> Trame;
        TrameGPS = new CTrameGPS(Trame);
        if(TrameGPS->GetIdentifiant() == "GPRMC" || TrameGPS->GetIdentifiant() == "GPGGA")
        {
            if(TrameGPS->GetIdentifiant() == "GPRMC")
            {
                cout << Trame << endl;
                Calcul.Setvn(TrameGPS->GetVitesse());
                Calcul.SettnStr(TrameGPS->GetTemps());
                if(Calcul.Getvn_1() != 0)
                {
                    //Calcul ici
                    KilometrageTotal = Calcul.calculKilometrage();
                    cout << "Kilometrage -> " << KilometrageTotal << endl;
                }
                else
                {
                    Calcul.Setvn_1(Calcul.Getvn());
                    Calcul.Settn_1Str(Calcul.GettnStr());
                }

                this_thread::sleep_for( chrono::milliseconds( 1000 ) );
            }
            if(TrameGPS->GetIdentifiant() == "GPGGA")
            {
                cout << Trame << endl;
                this_thread::sleep_for( chrono::milliseconds( 1000 ) );
            }

        }


    }
    Fichier.close();

    return 0;
}


/*if(etat = arret)
{
    KilometrageTotal = KilometrageTotal + reader.GetInteger( "technicien", "kilometrage", 0 );
}*/