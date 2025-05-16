#ifndef CODOMETRE_H
#define CODOMETRE_H

#include <string>
using namespace std;

class COdometre
{
private:

    double Kilometrage;
    double Vitesse_n_1;
    double Temps_n_1;


/*
    double TempsToHeures(string);
    double vn_1;
    string tn_1Str;
    double vn;
    double tn;
    double tn_1;
    string tnStr;
*/


public:
    COdometre();

    double  GetKilometrage();
    void    RemiseAZero();
    double  AjouterNouveauPoint( double TempsHeure, double VitesseKmh );
    void    AjouterN_1(double TempsHeure, double VitesseKmh);
    double  GetVitesse_n_1();                            

/*
    double calculKilometrage();
    
    double GetVitesse_n_1();
    double Getvn();
    string GettnStr();
    void Setvn(double);
    void SettnStr(string);
    void Setvn_1(double);
    void Settn_1Str(string);
*/

};

#endif // Codometre_H

