#include "CTrameGPS.h"
#include "codometre.h"
//#include "INIReader.h"
#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>
#include <iomanip>
#include <string>
#include <libserial/SerialStream.h>
#include <mini/ini.h>

using namespace std;
using namespace LibSerial;
using namespace mINI;

#define Arret 0;
#define Marche 1;

int main(int argc, char** argv)
{
    if ( argc != 3 )
    {
        cout << "==================================================================" << endl;
        cout << "= Parametres insuffisants : port debit"<< endl;
        cout << "= Exemple : TestDebit /dev/ttyS0 9600"<< endl;
        cout << "==================================================================" << endl;

        return 0;
    }
    CTrameGPS* TrameGPS = new CTrameGPS("$GPRMC,091303.000,A,4341.4196,N,00104.2376,W,0.09,137.78,120809,,,A*78");
    /*cout << TrameGPS->GetIntegrite() << endl;
    cout << TrameGPS->GetTrame() << endl;
    cout << TrameGPS->GetDate() << endl;
    cout << TrameGPS->GetTemps() << endl;*/
    cout << TrameGPS->GetLongitude() << endl;
    cout << TrameGPS->GetLatitude() << endl;


    delete TrameGPS;


    fstream Fichier;
    fstream PortSerie;
    string Trame;
    COdometre Odometre;
    double KilometrageTotal;
    string strTrameDoublon;
    int CompteurArret = 0;
    int EtatVoiture;
    string ZoneA;
    string ZoneB;
    string strZoneALat;
    string strZoneALong;
    string strZoneBLat;
    string strZoneBLong;
    size_t PositionVirgule;


    INIFile Fichier("projet_neis")
    INIStructure    ini;
    string  strKilometrageTest = ini["technicien"]["kilometrage"];
    cout << strKilometrageTest << endl;
    double Test = stod(strKilometrageTest) + 2;
    ini["technicien"]["kilometrage"] = to_string(Test);

    /*CINIReader reader("projet_neis.ini");

    if (reader.ParseError() < 0) 
    {
        cout << "Can't load 'projet_neis.ini'\n";
        return 1;
    }

    cout << reader.GetInteger( "technicien", "kilometrage", 0 ) << endl;

    ZoneA = reader.GetString("technicien", zone_depotA);      //Extraction de la zone de depot dans le fichier ini
    PositionVirgule = ZoneA.find_first_of( ',' );
    strZoneALat = ZoneA.substr( 0, PositionVirgule - 2 );
    strZoneALong = ZoneA.substr( PositionVirgule - 2)
    ZoneB = reader.GetString("technicien", zone_depotB);
    PositionVirgule = ZoneB.find_first_of( ',' );
    strZoneBLat = ZoneB.substr( 0, PositionVirgule - 2 );
    strZoneBLong = ZoneB.substr( PositionVirgule - 2)*/
        


    /*Fichier.open( "TramesGPS.nmea", fstream::in );        //Lecture de fichier pour test
    if ( Fichier.is_open() == false )
    {
        cout << "Pb fichier" << endl;
        return 0;
    }
    while ( Fichier.eof() == false )
    {
        Fichier >> Trame;*/
    
    string Port = string(argv[1]);
    while("/dev/" == Port.substr(0,5))
    {
        //string strbaudrate = "BaudRate::BAUD_" + string(argv[2]);
        //BaudRate baudrate = argv[2];          //JE sais pas 

        SerialStream PortSerie( Port, BaudRate::BAUD_9600 );   // Correspond à la configuration 9600,

        for (;;)//int NombreTrames = 0; NombreTrames != 200; NombreTrames++ )
        {
            
            char Buffer[ 100 ];
            PortSerie.getline( Buffer, 1000 );
            string strTrame(Buffer);
            if(strTrame != strTrameDoublon)
            {

            
                string strTrameDoublon(Buffer);
                //cout << strTrame << endl;
                cout << "__________________________________________________________" << endl;
            

                TrameGPS = new CTrameGPS(strTrame);
                if(TrameGPS->GetIdentifiant() == "GPRMC" || TrameGPS->GetIdentifiant() == "GPGGA")
                {
                    if(TrameGPS->GetIdentifiant() == "GPRMC")
                    {
                        cout << strTrame << endl;
                        /*Odometre.Setvn(TrameGPS->GetVitesse());
                        Odometre.SettnStr(TrameGPS->GetTemps());*/
                        cout << TrameGPS->GetTempsHeure() << endl;
                        cout << TrameGPS->GetVitesse() << endl;
                        if(TrameGPS->GetVitesse() <= 1)
                        {
                            CompteurArret = CompteurArret + 1;
                        }
                        else
                        {
                            EtatVoiture = Marche;
                            CompteurArret = 0;
                        }
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

                        this_thread::sleep_for( chrono::milliseconds( 500 ) ); //vitesse a changer surement
                    }
                    if(TrameGPS->GetIdentifiant() == "GPGGA")
                    {
                        cout << strTrame << endl;
                        this_thread::sleep_for( chrono::milliseconds( 500 ) );
                    }
                    if(CompteurArret == 600)
                    {
                        EtatVoiture = Arret;
                        KilometrageTotal = KilometrageTotal + reader.GetInteger( "technicien", "kilometrage", 0 );
                        //Ecrire la valeur de KilometrageTotal dans le fichier ini
                    }  
                    
                    if(TrameGPS->GetLatitude() <= stof(strZoneALat) && TrameGPS->GetLongitude() <= stof(strZoneALat) && TrameGPS->GetLatitude() >= stof(strZoneBLat) && TrameGPS->GetLongitude() >= stof(strZoneBLong))
                    {
                        cout << "Est entrer dans la zone de depot" << endl;
                        //Envoyer information besoin
                    }  

                }
            }
        }
        PortSerie.Close();
        return 0;
    }
    
    //Fichier.close();

    return 0;
}


/*if(EtatVoiture = Arret)
{
    KilometrageTotal = KilometrageTotal + reader.GetInteger( "technicien", "kilometrage", 0 );
    //reader.WriteInteger("technicien", "kilometrage", KilometrageTotal);  j'imagine
}

*/