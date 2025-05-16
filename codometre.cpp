#include "codometre.h"

COdometre::COdometre()
{


    this->Kilometrage = 0.0;
    this->Temps_n_1 = 0.0;
    this->Vitesse_n_1 = 0.0;
/*    
    vn = 0;
    vn_1 = 0;
    tnStr = "";
    tn_1Str = "";
  
    tn = 0;
    tn_1 = 0;
*/
}


double COdometre::GetKilometrage()
{
    return this->Kilometrage;
}

void COdometre::RemiseAZero()
{
    this->Kilometrage = 0.0;
}

void COdometre::AjouterN_1(double TempsEnHeure, double VitesseKmhh)
{
    this->Temps_n_1 = TempsEnHeure;
    this->Vitesse_n_1 = VitesseKmhh;
}

double COdometre::AjouterNouveauPoint( double TempsHeureNouveauPoint, double VitesseKmhNouveauPoint )
{
double Distance;

    // Calcul de la distance entre le nouveau point et le point précédent
    Distance = ( ( VitesseKmhNouveauPoint + this->Vitesse_n_1 ) / 2 ) * ( TempsHeureNouveauPoint - this->Temps_n_1 );

    // Mise à jour du kilométrage cumulé
    this->Kilometrage = this->Kilometrage + Distance;

    // Mémorise le point présent qui devient le point précédent pour le prochain ajout
    this->Vitesse_n_1 = VitesseKmhNouveauPoint;
    this->Temps_n_1 = TempsHeureNouveauPoint;

    return this->Kilometrage;
}

double COdometre::GetVitesse_n_1()
{
    return Vitesse_n_1;
}

/*
// Fonction pour convertir une chaîne "HHMMSS" en heures
double COdometre::TempsToHeures(string Temps)
{
    double hours, minutes, seconds;
    hours = stoi(Temps.substr(0, 2));
    minutes = stoi(Temps.substr(2, 2));
    seconds = stoi(Temps.substr(4, 2));
    double tempoheure = hours * 3600 + minutes * 60 + seconds;
    return tempoheure / 3600.0;
}
*/
/*
double COdometre::calculKilometrage()
{
    // Convertir les temps en heures
    tn = TempsToHeures(tnStr);
    tn_1 = TempsToHeures(tn_1Str);
    //Calcul
    double deltatemps = tn - tn_1;
    double vntempo = vn_1 + vn;
    double distanceInKilometre = (vntempo / 2.0) * (deltatemps);
    Kilometrage = Kilometrage + distanceInKilometre;   //KILOMETRAGE DE DEPART A PRENDRE DANS LE FICHIER INI
    return Kilometrage;
}

double COdometre::Getvn_1()
{
    return vn_1;
}

double COdometre::GetKilometrage()
{
    return Kilometrage;
}

double COdometre::Getvn()
{
    return vn;
}

string COdometre::GettnStr()
{
    return tnStr;
}

void COdometre::SettnStr(string a)
{
    tnStr = a;
}

void COdometre::Settn_1Str(string a)
{
    tn_1Str = a;
}

void COdometre::Setvn(double a)
{
    vn = a;
}

void COdometre::Setvn_1(double a)
{
    vn_1 = a;
}

*/