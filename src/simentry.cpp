#include "simentry.h"
#include "logsql.h"

#include <QSet>
#include <QMessageBox>


//
simentry::simentry(LogSql &sql) : _simulators(sql), _simlog(sql)
{
}
//

simentry::~simentry()
{
}

void simentry::setupData()
{
    //setup GUI
    sim_dateEdit->setDateTime(QDateTime().currentDateTime());
    sim_timeEdit->setTime(QTime(0,0,0,0));
    pilotfunc();
    connect(sim_funcCombo,SIGNAL(currentIndexChanged(int)), this, SLOT(pilotfunc()));
    connect(sim_timeEdit,SIGNAL(timeChanged(QTime)), this, SLOT(pilotfunc()));

    //auth, type, level: Simulators Groupbox
    _simulators.setTable("sims", simulatorsTable);
    _simulators.addEntry(0, tr("id"),"",false);
    _simulators.addEntry(1, tr("Author Nr."),"",true, auth_lineEdit);
    _simulators.addEntry(2, tr("Type"),"",true, type_lineEdit);
    _simulators.addEntry(3, tr("Level"),"",true, level_lineEdit);
    _simulators.setupConnections(pushButton_new,
                                pushButton_delete,
                                pushButton_revert,
                                pushButton_submit);
    _simulators.setupView();
    //simulator log
    _simlog.setTable("simLog",sim_logView);
    _simlog.addEntry(0, tr("id_sim"),"",false);
    _simlog.addEntry(1, tr("Date"),"",true,sim_dateEdit);
    //TODO: Relationship betwenn sim_authorCombo and Type and Level (by the model???)
    _simlog.addEntry(2, tr("Type"),"",true);
    _simlog.addEntry(3, tr("Author Nr."),"",true,sim_authorCombo,
                     new QSqlRelation("sims","id","authno"));
    _simlog.addEntry(4, tr("Level"),"",true);
    //TODO: CONNECT WIDGET??? -> unable to fetch row
    _simlog.addEntry(5, tr("Trainee"),"",true,&t_trainee);
    _simlog.addEntry(6, tr("SFI/SFE"),"",true,&t_sfisfe);
    _simlog.addEntry(7, tr("Remarks"),"",true,sim_remarksText);
    _simlog.setupConnections(   pushButton_new_2,
                                pushButton_delete_2,
                                pushButton_revert_2,
                                pushButton_submit_2);
    //TODO: Custom Table
    _simlog.setupView();
}

void simentry::pilotfunc()
{
    if(sim_funcCombo->currentText().operator ==("TRAINEE"))
    {
        this->t_trainee.setTime(this->sim_timeEdit->time());
        this->t_sfisfe.setTime(QTime(0,0,0,0));
        //DEBUG a la Raphi :-)
        /*QMessageBox::critical(NULL,
           tr("Failed checking database tables"),
           this->t_trainee.time().toString());*/
    }
    else if(sim_funcCombo->currentText().operator ==("SFI"))
    {
        this->t_trainee.setTime(QTime(0,0,0,0));
        this->t_sfisfe.setTime(this->sim_timeEdit->time());
    }
    else if(sim_funcCombo->currentText().operator ==("SFE"))
    {
        this->t_trainee.setTime(QTime(0,0,0,0));
        this->t_sfisfe.setTime(this->sim_timeEdit->time());
    }

}
