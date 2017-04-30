#include "flightentry.h"
#include "ui_flightEntry.h"
#include "logsql.h"
#include <qt5/QtWidgets/QMessageBox>
#include <qt5/QtCore/qdatetime.h>

flightentry::flightentry(LogSql &sql): _tvb(sql)
{
}

flightentry::~flightentry()
{
}

void flightentry::calculateTimes()
{
    //TODO: Get rid of the declarations and integrate them into the class
    QTime depTime = dep_timeEdit->time();
    QTime arrTime = arr_timeEdit->time();
    QTime totTime;
    QTime rulesTime;
    //Calculate total time
    totTime = totTime.addSecs(depTime.secsTo(arrTime));
    tot_timeEdit->setTime(totTime);

    //Get the times for the Pilot function, static entry in ComboBox
    if(func_comboBox->currentText().operator ==("PIC"))
    {
        pic_timeEdit->setTime(totTime);
        copi_timeEdit->setTime(QTime(0,0,0,0));
        dual_timeEdit->setTime(QTime(0,0,0,0));
        instr_timeEdit->setTime(QTime(0,0,0,0));
        remarks_textEdit->setText("");
    }
    else if(func_comboBox->currentText().operator ==("COPI"))
    {
        pic_timeEdit->setTime(QTime(0,0,0,0));
        copi_timeEdit->setTime(totTime);
        dual_timeEdit->setTime(QTime(0,0,0,0));
        instr_timeEdit->setTime(QTime(0,0,0,0));
        remarks_textEdit->setText("");
    }
    else if(func_comboBox->currentText().operator ==("DUAL"))
    {
        pic_timeEdit->setTime(QTime(0,0,0,0));
        copi_timeEdit->setTime(QTime(0,0,0,0));
        dual_timeEdit->setTime(totTime);
        instr_timeEdit->setTime(QTime(0,0,0,0));
        remarks_textEdit->setText("");
    }
    else if(func_comboBox->currentText().operator ==("INSTR"))
    {
        pic_timeEdit->setTime(QTime(0,0,0,0));
        copi_timeEdit->setTime(QTime(0,0,0,0));
        dual_timeEdit->setTime(QTime(0,0,0,0));
        instr_timeEdit->setTime(totTime);
        remarks_textEdit->setText("");
    }
    else if(func_comboBox->currentText().operator ==("PICUS"))
    {
        pic_timeEdit->setTime(totTime);
        copi_timeEdit->setTime(QTime(0,0,0,0));
        dual_timeEdit->setTime(QTime(0,0,0,0));
        instr_timeEdit->setTime(QTime(0,0,0,0));
        remarks_textEdit->setText("PICUS");
    }

    //Get the times for the flight rules, static entry in ComboBox
    //assume VFR flight
    if(fr_timeEdit->time() < depTime)
    {
        fr_timeEdit->setTime(depTime);
    }
    else if(fr_timeEdit->time() > arrTime)
    {
        fr_timeEdit->setTime(depTime);
    }
    if(fr_comboBox->currentText().operator ==("IFR (I)"))
    {
        ifr_timeEdit->setTime(totTime);
        fr_timeEdit->setEnabled(false);
    }
    else if(fr_comboBox->currentText().operator ==("VFR (V)"))
    {
        ifr_timeEdit->setTime(QTime(0,0,0,0));
        fr_timeEdit->setEnabled(false);
    }
    else if(fr_comboBox->currentText().operator ==("LEAVE (Y)"))
    {

        rulesTime = rulesTime.addSecs(depTime.secsTo(fr_timeEdit->time()));
        ifr_timeEdit->setTime(rulesTime);
        fr_timeEdit->setEnabled(true);
    }
    else if(fr_comboBox->currentText().operator ==("JOIN (Z)"))
    {
        rulesTime = rulesTime.addSecs(fr_timeEdit->time().secsTo(arrTime));
        ifr_timeEdit->setTime(rulesTime);
        fr_timeEdit->setEnabled(true);
        QMessageBox::critical(NULL,
                              tr("Failed checking database tables"),
                              rulesTime.toString());
    }
}

void flightentry::setupData()
{

}

void flightentry::setupGui()
{
    //Set Fields
    flt_dateEdit->setDateTime(QDateTime().currentDateTime());
    dep_timeEdit->setTime(QTime(0,0,0,0));
    arr_timeEdit->setTime(QTime(0,0,0,0));
    dep_comboBox->setAutoCompletion(true);
    arr_comboBox->setAutoCompletion(true);
    ac_comboBox->setAutoCompletion(true);
    pic_comboBox->setAutoCompletion(true);
    //Connect Slots
    connect(func_comboBox,SIGNAL(currentIndexChanged(int)), this, SLOT(calculateTimes()));
    connect(fr_comboBox,SIGNAL(currentIndexChanged(int)), this, SLOT(calculateTimes()));
    connect(ac_comboBox,SIGNAL(currentIndexChanged(int)), this, SLOT(calculateTimes()));
    connect(arr_timeEdit,SIGNAL(timeChanged(QTime)), this, SLOT(calculateTimes()));
    connect(dep_timeEdit,SIGNAL(timeChanged(QTime)), this, SLOT(calculateTimes()));
    connect(fr_timeEdit,SIGNAL(timeChanged(QTime)), this, SLOT(calculateTimes()));
    //Connect Controls
    _tvb.connectWidget("airports","icao",dep_comboBox);
    _tvb.connectWidget("airports","icao",arr_comboBox);
    _tvb.connectWidget("aircraft","registration",ac_comboBox);
    _tvb.connectWidget("crew","id_crew",pic_comboBox);


}
