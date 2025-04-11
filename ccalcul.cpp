#include "ccalcul.h"

CCalcul::CCalcul()
{
    vn = 0;
    vn_1 = 0;
    tnStr = "";
    tn_1Str = "";
    Kilometrage = 0;
    tn = 0;
    tn_1 = 0;

}


// Fonction pour convertir une chaîne "HHMMSS" en heures
double CCalcul::TempsToHeures(string Temps)
{
    double hours, minutes, seconds;
    hours = stoi(Temps.substr(0, 2));
    minutes = stoi(Temps.substr(2, 2));
    seconds = stoi(Temps.substr(4, 2));
    double tempoheure = hours * 3600 + minutes * 60 + seconds;
    return tempoheure / 3600.0;
}

double CCalcul::calculKilometrage()
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

double CCalcul::Getvn_1()
{
    return vn_1;
}

double CCalcul::GetKilometrage()
{
    return Kilometrage;
}

double CCalcul::Getvn()
{
    return vn;
}

string CCalcul::GettnStr()
{
    return tnStr;
}

void CCalcul::SettnStr(string a)
{
    tnStr = a;
}

void CCalcul::Settn_1Str(string a)
{
    tn_1Str = a;
}

void CCalcul::Setvn(double a)
{
    vn = a;
}

void CCalcul::Setvn_1(double a)
{
    vn_1 = a;
}

