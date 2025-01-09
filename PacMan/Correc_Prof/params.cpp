#include <string>
#include "params.h"
#include "game.h"
using namespace std;


void initParams (CMyParam & Param)
{
    //Move Keys
    Param.MapParamChar["KeyUp"] = 'z';
    Param.MapParamChar["KeyDown"] = 's';

    Param.MapParamChar["TokenP1"] = 'A';
    Param.MapParamChar["TokenP2"] = 'X';

    //Size of grid — suppose to be a rectangle
    Param.MapParamUnsigned["NbColumn"] = 10;

    //Display Colors
    Param.MapParamString["ColorP1"] = KColor.find("KRed")->second ;

}

void initParams (CMyParamV2 & Param)
{
    //Move Keys
    Param.KeyUp = 'z';
    Param.KeyDown = 's';

    Param.tokenP1 = 'A';
    Param.tokenP2 = 'X';

    //Size of grid — suppose to be a rectangle
    Param.NbColumn = 10;

    //Display Colors
    Param.ColorP1 = KColor.find("KRed")->second ;

}
