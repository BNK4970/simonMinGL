#include <iostream>
#include <iomanip>
#include "gridmanagement.h"

#include "type.h" //nos types


using namespace std;



void ClearScreen()
{
    cout << "\033[H\033[2J";
}// ClearScreen ()

void Color (const string & Col)
{
    cout << "\033[" << Col.c_str () <<"m";
} // Color ()


void DisplayGrid (const CMat & Mat)
{
    const unsigned KNbLine = Mat.size ();
    const unsigned KNbCol  = Mat[0].size ();
    cout << string (KNbCol + 2 , '-') << endl;
    for (unsigned i (0); i < KNbLine; ++i)
    {
        cout << '|';
        for (char c : Mat[i])
        {

            switch (c)
            {
            case KEmpty:
                cout << c;
                Color (KColor.find("KReset")->second);
                break;
            case 'X':
                Color (KColor.find("KBlue")->second);
                cout << c;
                Color (KColor.find("KReset")->second);
                break;
            case 'O':
                Color (KColor.find("KRed")->second);
                cout << c;
                Color (KColor.find("KReset")->second);
                break;

            }
        }
        cout << '|' << endl;
    }
    cout << string (KNbCol + 2 , '-') << endl;
}// ShowMatrix ()


void InitGrid (CMat & Mat, unsigned NbLine, unsigned NbColumn, CPosition & PosPlayer1, CPosition & PosPlayer2)
{
    Mat.resize (NbLine);
    const CVLine KLine (NbColumn, KEmpty);
    for (CVLine &ALine : Mat)
        ALine = KLine;

    PosPlayer1.first = 0;
    PosPlayer1.second = NbColumn - 1;
    Mat [PosPlayer1.first][PosPlayer1.second] = 'X';
    PosPlayer2.first = NbLine - 1;
    PosPlayer2.second =0;
    Mat [PosPlayer2.first][PosPlayer2.second]   = 'O';
}//InitMat ()

void InitGrid(CMat &Mat, const CMyParam &myParam) {
    auto it= myParam.MapParamUnsigned.find("NbColumn");
    if (it == myParam.MapParamUnsigned.end()) exit (EXIT_FAILURE);
    Mat.resize(it->second);
}
