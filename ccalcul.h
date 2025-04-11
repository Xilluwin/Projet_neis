#ifndef CCALCUL_H
#define CCALCUL_H

#include <string>
using namespace std;

class CCalcul
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
    CCalcul();

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

#endif // CCALCUL_H
