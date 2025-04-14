#ifndef CODOMETRE_H
#define CODOMETRE_H

#include <string>
using namespace std;

class COdometre
{
private:

    double TempsToHeures(string);
    double Kilometrage;
    double vn_1;
    string tn_1Str;
    double vn;
    double tn;
    double tn_1;
    string tnStr;



public:
    COdometre();

    double calculKilometrage();
    double GetKilometrage();
    double Getvn_1();
    double Getvn();
    string GettnStr();
    void Setvn(double);
    void SettnStr(string);
    void Setvn_1(double);
    void Settn_1Str(string);


};

#endif // Codometre_H
