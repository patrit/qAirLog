#include "avastronomy.h"
#include <QDateTime>
#include <math.h>

avastronomy::avastronomy(QObject *parent) :
    QObject(parent)
{
    //lookup math.c for an equivalent...
    pi = 4 * atan(1);
}
//Negative is South, positive is North, Negative is West, positive is East.
double avastronomy::DDtoDMS(int deg, int min, int sec, QString dir)
{

    double dd = deg+((min + (sec / 60)) / 60);
    if((dir.operator ==("S")) || (dir.operator ==("W")))
    {
        dd=-dd;
        return dd;
    }
    else
    {
        return dd;
    }
}
/*void avastronomy::DMStoDD(double dd, QString dir)
{
    //pass dir either lat for latitude or lng of longitude
    bool neg(false) ;
        if (dd < 0.0)
        {
          neg = true ;
          dd = -dd ;
        }
    int deg = (int)dd ;
    double frac = dd - (double)deg ;
    frac *= 60.0 ;
    int min = (int)frac ;
    frac = frac - (double)min ;
    double sec = nearbyint(frac * 600000.0) ;
    sec /= 10000.0 ;
    if (sec >= 60.0)
        {
          min++ ;
          sec -= 60.0 ;
        }
}*/

void avastronomy::NightTime(QDate date, QTime depTime, QTime arrTime, float depLong, float depLat, float arrLong, float arrLat)
{
    NightTime(date, TimeToDecTime(depTime), TimeToDecTime(arrTime),depLong,depLat,arrLong,arrLat);
}

void avastronomy::NightTime(QDate date, float depTime, float arrTime, float depLong, float depLat, float arrLong, float arrLat)
{
    //http://www.teamsamas.com/
    float nitTime;
    float incTime = (1/60);
    float lopTime=depTime;
    int count=0; //LoopCounter=0;
    float gs = Groundspeed(depLong,depLat,arrLong,arrLat,(arrTime-depTime));
    while(lopTime>=arrTime)
    {
    //fix: returns integer part of number
    //check which functions require rad, input in deg!!!
    float gcDist = (gs*incTime*count)*pi/(180*60);
    float gcLat = asin(sin(DegToRad(depLat))*cos(gcDist)+cos(DegToRad(depLat))*sin(gcDist)*cos(TrueCourseRadiant(depLong,depLat,arrLong,arrLat)));
    float dLong = atan2((sin(TrueCourseRadiant(depLong,depLat,arrLong,arrLat))*sin(gcDist)*cos(DegToRad(depLat))),(cos(gcDist)-sin(DegToRad(depLat))*sin(gcLat)));
    float gcLong = (Modulus(((depLong*-1)-dLong+pi), (2*pi))-pi)*-1;
    float sunRise = SunRiseSet(date,gcLong,gcLat,0)-0.5; //aviation time remove 30'
    float sunSet = SunRiseSet(date,gcLong,gcLat,0)+0.5; //aviation time add 30'
    if ((sunRise>24) && (sunRise<98)){sunRise=sunRise-24;}
    else if ((sunRise<0) && (sunRise>-98)){sunRise=sunRise+24;}
    if ((sunSet>24) && (sunSet<98)){sunSet=sunSet-24;}
    else if ((sunSet<0) && (sunSet>-98)){sunSet=sunSet+24;}
    //unknown
    if((arrTime-lopTime)<incTime){incTime=arrTime-lopTime;}
    //debug!!!
    if(sunRise==99){/*return nitTime=nitTime+incTime;*/}
    else if (sunRise==-99){/*return 0;*/}
    if(sunSet==99){/*return nitTime=nitTime+incTime;*/}
    else if (sunSet==-99){/*return 0;*/}
    //
    if(sunRise<sunSet){
        if ((lopTime >= sunRise)&&(lopTime<sunSet)){}
        else{/*return nitTime=nitTime+incTime;*/}
    }
    if(sunRise>sunSet){
        if((lopTime>=sunRise)||(lopTime<sunSet)){}
        else{/*return nitTime=nitTime+incTime;*/}
    }
    count++;
    lopTime = lopTime + incTime;
    }
}


float avastronomy::SunRiseSet(QDate date, float longitude, float latitude, int r_s)
{
   /*                 zenith:      Sun's zenith for sunrise/sunset
                      offical      = 90 degrees 50'
                      civil        = 96 degrees
                      nautical     = 102 degrees
                      astronomical = 108 degrees
                      zenith=cos(90°50')
                      TODO: INSERT FUNCTION*/
    //SEE: http://williams.best.vwh.net/sunrise_sunset_example.htm
    //If r_s=0 returns sunrise times
    //If r_s=1 returns sunset times
    float zenith = -0.014543897651582;
    float t;
    float sunHour;
    if(r_s == 0){t=(int)date.dayOfYear()+((6-(longitude/15))/24);}
    else if(r_s == 1){t=(int)date.dayOfYear()+((18-(longitude/15))/24);}
    float sunLong =((0.9856*t)-3.289)+(1.916*sin(DegToRad(((0.9856*t)-3.289))))+(0.020*sin(DegToRad(2*((0.9856*t)-3.289))))+282.634;
    if(sunLong>360){sunLong=sunLong-360;}
    if(sunLong<0){sunLong=sunLong+360;}
    float sunRA = RadToDeg(atan(0.91764 *tan(DegToRad(sunLong))));
    sunRA = (sunRA+(((int(sunLong/90.0))*90)-((int(sunLong/90.0))*90.0)))/15;
    float sinDec = 0.39782*sin(DegToRad(sunLong));
    float cosDec = cos(asin(sinDec));
    //Poles
    if(latitude == 90){latitude=89.999999999;}
    if(latitude == -90){latitude=-89.999999999;}
    float sunAngle = zenith-(sinDec*sin(DegToRad(latitude)))/(cosDec*cos(DegToRad(latitude)));
    if (sunAngle >  1){return 99;} //  the sun never rises on this location
    if (sunAngle < -1){return -99;} // the sun never sets on this location
    if(r_s == 0){sunHour=(360-RadToDeg(acos(sunAngle)))/15;}
    if(r_s == 1){sunHour=(360-RadToDeg(acos(sunAngle)))/15;}
    float sunTimeUTC = (sunHour+sunRA-(0.06571*t)-6.622)-(longitude/15.0);
    if (sunTimeUTC<0){return (sunTimeUTC+24);}
    else if(sunTimeUTC){return (sunTimeUTC-24);}
    else{return sunTimeUTC;}
}

float avastronomy::TrueCourseRadiant(float depLong, float depLat, float arrLong, float arrLat)
{
    depLong=DegToRad(depLong);
    depLat=DegToRad(depLat);
    arrLong=DegToRad(arrLong);
    arrLat=DegToRad(arrLat);
    //At poles, exit as do not need to calculate initial true course
    if(depLat==(pi/2)){return pi;}
    else if(depLat==(-pi/2)){return 0;}
    float distRad = 2 * asin(sqrt(pow((sin((depLat-arrLat)/2)),2) + cos(depLat)*cos(arrLat)*pow((sin((depLong-arrLong)/2)),2)));
    float tcRad = ((sin(arrLat)-sin(depLat)*cos(distRad))/(sin(distRad)*cos(depLat)));
    //correct for double precision arithmetic errors
    if(tcRad>1){tcRad=1;}
    if(tcRad<-1){tcRad=-1;}
    //initial true course from dep point to arr point
    if((sin((arrLong*-1)-(depLong*-1)))<0){
        return acos(tcRad);}
    else{
        return 2*pi-acos(tcRad);}
}
float avastronomy::DistanceRadiant(float depLong, float depLat, float arrLong, float arrLat)
{
    depLong=DegToRad(depLong);
    depLat=DegToRad(depLat);
    arrLong=DegToRad(arrLong);
    arrLat=DegToRad(arrLat);
    return (acos(sin(depLat)*sin(arrLat)+cos(depLat)*cos(arrLat)*cos(depLong*-1-arrLong*-1)));
}
int avastronomy::Distance(float depLong, float depLat, float arrLong, float arrLat)
{
    return (int(DistanceRadiant(depLong,depLat,arrLong,arrLat)*180*60/pi));
}
int avastronomy::Groundspeed(float depLong, float depLat, float arrLong, float arrLat, float fltTime)
{
    return (int(Distance(depLong,depLat,arrLong,arrLat)/fltTime));
}

float avastronomy::DegToRad(float deg)
{
      return ((pi*deg)/180);
}
float avastronomy::RadToDeg(float rad)
{
      return ((rad*180)/pi);
}
float avastronomy::Modulus (float y, float x)
{
    // calculates the remainder of y/x
    if (y>=0)
    {
        return (y-x*(int(y/x)));
    }
    else
    {
        return (y+x*(int((-y/x)+1)));
    }
}
float avastronomy::TimeToDecTime(QTime time)
{
    return time.hour() + (time.minute()/60);
}
QTime avastronomy::DecTimeToTime(float time)
{
}
