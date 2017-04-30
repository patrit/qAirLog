#include "aircrafts.h"

#include <QSet>
#include <QMessageBox>
#include <QSqlRelationalDelegate>
#include <QFileDialog>


//
Aircrafts::Aircrafts(LogSql &sql) :
   _tvb(sql)
{
}
//

Aircrafts::~Aircrafts()
{
}

void Aircrafts::setupData()
{
   _tvb.setTable("aircraft", aircraftsTable);
   _tvb.addEntry(0, tr("Registration"), "", true, ragistration_lineEdit);
   _tvb.addEntry(1, tr("Model"), "", true, model_lineEdit);
   _tvb.addEntry(2, tr("Variant"), "", true, variant_lineEdit);
   _tvb.addEntry(3, tr("AC Function"), "", true, function_comboBox,
      new QSqlRelation("ac_func", "func", "description"));
   _tvb.addEntry(4, tr("Operation"), "", true, operation_comboBox,
      new QSqlRelation("ac_ops", "operation", "description"));
   _tvb.addEntry(5, tr("MSN"), 0, false, msn_spinBox);
   _tvb.addEntry(6, tr("DOM"), 0, false, dom_spinBox);
   _tvb.addEntry(7, tr("DOI"), 0, false, doi_spinBox);
   _tvb.addEntry(8, tr("MTOM"), 0, false, mtom_spinBox);
   _tvb.addEntry(9, tr("MLM"), 0, false, mlm_spinBox);
   _tvb.addEntry(10, tr("MZFM"), 0, false, mzfm_spinBox);
   _tvb.addEntry(11, tr("Max. Payload"), 0, false, payload_spinBox);
   _tvb.addEntry(12, tr("Max. Range"), 0, false, range_spinBox);
   _tvb.addEntry(13, tr("Manufacturer"), "", false,manufacturer_lineEdit);
   //todo, add blob picture type to set pixmap
   _tvb.addEntry(14, tr("Picture"), "", false,img_label);
   _tvb.setupConnections(pushButton_new,
                              pushButton_delete,
                              pushButton_revert,
                              pushButton_submit);
   _tvb.setupView();


   //SetupPicture
   connect(pic_pushButton,SIGNAL(clicked()), this, SLOT(uploadPicture()));

}
void Aircrafts::uploadPicture()
{
    QString fileName = QFileDialog::getOpenFileName(NULL,
         tr("Open Image"), "/home", tr("Image Files (*.png *.jpg *.bmp)"));
    QImage *img = new QImage(fileName);
    img_label->setPixmap(QPixmap::fromImage(*img));
    img_label->show();
    //TODO: QImage QImage::smoothScale ( int w, int h, ScaleMode mode = ScaleFree ) const
    //TODO: http://dev.mysql.com/doc/refman/5.0/en/blob.html

}

// CREATE TABLE aircraft   (registration   VARCHAR(5) PRIMARY KEY,
//                         model           VARCHAR(4) NOT NULL,
//                         variant         VARCHAR
//                         ac_func         VARCHAR(3) NOT NULL,
//                         operation       VARCHAR,
//                         msn             INTEGER,
//                         dom             INTEGER,
//                         doi             INTEGER,
//                         mtom            INTEGER,
//                         mlm             INTEGER,
//                         mzfm            INTEGER,
//                         max_payload     INTEGER,
//                         max_range       INTEGER, 
//                         manufacturer TEXT, 
//                         picture BLOB);
