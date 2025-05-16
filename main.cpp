#include "CTrameGPS.h"
#include "codometre.h"
#include "INIReader.h"
#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>
#include <iomanip>
#include <string>
#include <libserial/SerialStream.h>

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
    fstream PortSerie;
    string Trame;
    COdometre Odometre;
    double KilometrageTotal;

    CINIReader reader("projet_neis.ini");

    if (reader.ParseError() < 0) 
    {
        cout << "Can't load 'projet_neis.ini'\n";
        return 1;
    }

    cout << reader.GetInteger( "technicien", "kilometrage", 0 ) << endl;
        


    /*Fichier.open( "TramesGPS.nmea", fstream::in );
    if ( Fichier.is_open() == false )
    {
        cout << "Pb fichier" << endl;
        return 0;
    }
    while ( Fichier.eof() == false )
    {
        Fichier >> Trame;*/
    
    PortSerie.open("ttyACM0", ios_base::in);
    if(PortSerie.is_open() == false)
    {
        cout << "pb port serie" << endl;
        return 0;
    }
    while(PortSerie.eof() == false)
    {

    
        PortSerie >> Trame;

        TrameGPS = new CTrameGPS(Trame);
        if(TrameGPS->GetIdentifiant() == "GPRMC" || TrameGPS->GetIdentifiant() == "GPGGA")
        {
            if(TrameGPS->GetIdentifiant() == "GPRMC")
            {
                cout << Trame << endl;
                /*Odometre.Setvn(TrameGPS->GetVitesse());
                Odometre.SettnStr(TrameGPS->GetTemps());*/
                cout << TrameGPS->GetTempsHeure() << endl;
                cout << TrameGPS->GetVitesse() << endl;
                if(Odometre.GetVitesse_n_1() != 0)
                {
                    //Calcul ici
                    KilometrageTotal = Odometre.AjouterNouveauPoint(TrameGPS->GetTempsHeure(), TrameGPS->GetVitesse());
                    cout << "Kilometrage -> " << KilometrageTotal << endl;
                }
                else
                {
                    Odometre.AjouterN_1(TrameGPS->GetTempsHeure(), TrameGPS->GetVitesse());
                }

                this_thread::sleep_for( chrono::milliseconds( 1000 ) ); //vitesse a changer surement
            }
            if(TrameGPS->GetIdentifiant() == "GPGGA")
            {
                cout << Trame << endl;
                this_thread::sleep_for( chrono::milliseconds( 1000 ) );
            }

        }


    }
    //Fichier.close();

    return 0;
}


/*if(etat = arret)
{
    KilometrageTotal = KilometrageTotal + reader.GetInteger( "technicien", "kilometrage", 0 );
}*/