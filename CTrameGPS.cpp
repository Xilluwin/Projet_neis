#include "CTrameGPS.h"

CTrameGPS::CTrameGPS( string Trame )
{
    // Sauvegarde de la trame a traiter
    this -> Trame = Trame;
    //initialisation des valeur par default
    this -> bIntegrite = false;
    this -> TailleTrame = this -> Trame.length();
    this -> IdentifiantTrame = "";
    this -> fVitesse = -1.0f;
    this -> fLatitude = -200.0f;
    this -> fLongitude = -200.0f;
    this -> Date = "";
    this -> Temps = "";

    TailleTrame = Trame.length();

    TraiterTrame();


    // Lance l'analyse et l'extraction des champs
    TraiterTrame();
}

CTrameGPS::~CTrameGPS()
{
}

//get get
string  CTrameGPS::GetTrame()
{
    return Trame;
}
bool CTrameGPS::GetIntegrite()
{
    return bIntegrite;
}

float   CTrameGPS::GetLatitude()
{
    return fLatitude;
}

float   CTrameGPS::GetLongitude()
{
    return fLongitude;
}

string  CTrameGPS::GetTemps()
{
    return Temps;
}

float   CTrameGPS::GetVitesse()
{
    return fVitesse;
}

string CTrameGPS::GetDate()
{
    return Date;
}

string CTrameGPS::GetIdentifiant()
{
    return IdentifiantTrame;
}

float CTrameGPS::GetNoeud()
{
    return fNoeud;
}



void CTrameGPS::TraiterTrame()
{
    bIntegrite = CTrameGPS::ControlerIntegrite();
    if(bIntegrite == false)
    {
        return;
    }

    IdentifierTrame();

    string Angle;
    size_t PositionPoint;
    string Degres, Minutes;
    if(this -> IdentifiantTrame == "GPGGA")
    {
        Angle = ExtraireChamp(2);
        this -> Temps = ExtraireChamp(1).substr(0,6);
        PositionPoint = Angle.find_first_of( '.' );
        Degres = Angle.substr( 0, PositionPoint - 2 ); //ExtraireChamp(2).substr(0,2);
        Minutes = Angle.substr( PositionPoint - 2 ); //ExtraireChamp(2).substr(2);
        fLatitude = stof(Degres) + stof(Minutes)/60.0f;

        //Degres = ExtraireChamp(4).substr(0,3);
        //Minutes = ExtraireChamp(4).substr(3);
        Angle = ExtraireChamp(4);
        PositionPoint = Angle.find_first_of( '.' );
        Degres = Angle.substr( 0, PositionPoint - 2 );
        Minutes = Angle.substr( PositionPoint - 2 );
        fLongitude = stof(Degres) + stof(Minutes)/60.0f;

        if(ExtraireChamp(3) != "N") fLatitude *= -1.0f;
        if(ExtraireChamp(5) != "W") fLongitude *= -1.0f;

        Temps = ExtraireChamp(1);

        /*faltitude = stof(ExtraireChamp(9));   Don't need???*/
    }

    if(this -> IdentifiantTrame == "GPRMC")
    {
        Angle = ExtraireChamp(3);
        Degres = Angle.substr(0,2);
        Minutes = Angle.substr(2);
        fLatitude = stof(Degres) + stof(Minutes)/60.0f;

        Angle = ExtraireChamp(5);
        Degres = Angle.substr(0,3);
        Minutes = Angle.substr(3);
        fLongitude = stof(Degres) + stof(Minutes)/60.0f;

        if(ExtraireChamp(4) != "N") fLatitude *= -1.0f;
        if(ExtraireChamp(6) != "W") fLongitude *= -1.0f;

        fNoeud = stof(ExtraireChamp(7));
        fVitesse = stof(ExtraireChamp(7)) * 1.852f;
        Date = ExtraireChamp(9);
        Temps = ExtraireChamp(1);
    }
}

unsigned char CTrameGPS::ASCIIHexToInt(char * pASCIIHex )
{
    unsigned char ucMSB, ucLSB;
    unsigned char* pASCII = reinterpret_cast<unsigned char*>(pASCIIHex);

    // 1er digit Hex ASCII
    if (*pASCII < 'A')
        ucMSB = *pASCII - '0';
    else
        ucMSB = *pASCII - 'A' + 10;

    // 2eme digit Hex ASCII
    pASCII++;
    if (*pASCII < 'A')
        ucLSB = *pASCII - '0';
    else
        ucLSB = *pASCII - 'A' + 10;

    return (ucMSB << 4 | ucLSB);

}


bool CTrameGPS::ControlerIntegrite()
{
    // Controle integrite des donnees
    this->bIntegrite = false;

    // Test presence $
    if ( this->Trame[ 0 ] != '$' ) return false;

    // Test presence *
    size_t IndiceEtoile;
    IndiceEtoile = this->Trame.find( '*', 1 );
    if ( IndiceEtoile == string::npos ) return false;

    // Calcul checksum local
    unsigned char Indice;
    unsigned char ChecksumLocal;

    ChecksumLocal = 0;
    for ( Indice = 1; Indice != IndiceEtoile; Indice++ )
        ChecksumLocal = ChecksumLocal ^ this->Trame[ Indice ];

    // Extraction du Checksum recu
    unsigned char ChecksumRecu;
    ChecksumRecu = ASCIIHexToInt( &this->Trame[ IndiceEtoile + 1 ] );

    // Comparaison du checksum local et du checksum recu
    if ( ChecksumLocal != ChecksumRecu ) return false;

    this->bIntegrite = true;

    return true;

}


bool CTrameGPS::IdentifierTrame()
{
    if ( this->bIntegrite == false ) return false;

    IdentifiantTrame = Trame.substr(1,5);

    // L'attribut IdentifiantTrame recoit le NOM de la trame GPS


    return true;
}

string CTrameGPS::ExtraireChamp(unsigned char ucRangChamp)
{
    /*
    unsigned char   ucIndice;
    unsigned char   ucRang;
    string          ChampExtrait;
    */

    string Champ;
    size_t IndiceVirguleDebut, IndiceVirguleFin;

    // Si la trame n'est pas integre, on ne traite rien.
    if ( this->bIntegrite == false ) return "";

    // Cas particulier : rang 0
    if ( ucRangChamp == 0 ) return this->IdentifiantTrame;

    // Recherche du rang ==================================================

    // Recherche DEBUT de la chaine
    IndiceVirguleDebut = 0;
    do
    {
        IndiceVirguleDebut = Trame.find( ',', IndiceVirguleDebut + 1 );

        if ( IndiceVirguleDebut == string::npos ) return "";

        ucRangChamp--;

    }
    while ( ucRangChamp != 0 );

    // Recherche fin champ
    IndiceVirguleFin = Trame.find( ',', IndiceVirguleDebut + 1 );
    if ( IndiceVirguleFin == string::npos )
    {
        IndiceVirguleFin = Trame.find( '*', IndiceVirguleDebut + 1 );
        if ( IndiceVirguleFin == string::npos ) return "";		// BUG :manque l'etoile !!!
    }

    // Extraction champ ====================================================
    Champ = Trame.substr( IndiceVirguleDebut + 1, IndiceVirguleFin - IndiceVirguleDebut - 1 );

    return Champ;

}

/*string CTrameGPS::GetHorodatageInDatetime()
{
    Horodatage = "20" + Date.substr(4) + "-" + Date.substr(2,4) + "-" + Date.substr(0,2) + " " + Temps.substr(0,2) + ":" + Temps.substr(2,4) + ":" + Temps.substr(4,6);
    const char* cHorodatage = Horodatage.c_str();
    return cHorodatage;
}*/
