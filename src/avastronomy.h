#ifndef AVASTRONOMY_H
#define AVASTRONOMY_H

#include <QObject>
#include <QDateTime>

class avastronomy : public QObject
{
Q_OBJECT
public:
    explicit avastronomy(QObject *parent = 0);
    double DDtoDMS(int deg, int min, int sec, QString dir);
    void NightTime(QDate date, QTime depTime, QTime arrTime, float depLong, float depLat, float arrLong, float arrLat);
    void NightTime(QDate date, float depTime, float arrTime, float depLong, float depLat, float arrLong, float arrLat);
    float SunRiseSet(QDate date, float longitude, float latitude, int r_s);
    int Distance(float depLong, float depLat, float arrLong, float arrLat);
    int Groundspeed(float depLong, float depLat, float arrLong, float arrLat, float fltTime);

private:
    float pi;
    float DegToRad(float deg);
    float RadToDeg(float rad);
    float Modulus (float y, float x);
    float DistanceRadiant(float depLong, float depLat, float arrLong, float arrLat);
    float TrueCourseRadiant(float depLong, float depLat, float arrLong, float arrLat);
    float TimeToDecTime(QTime time);
    QTime DecTimeToTime(float time);
signals:

public slots:

};

#endif // AVASTRONOMY_H
