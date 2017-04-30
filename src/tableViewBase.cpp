#include "tableViewBase.h"

#include <QMessageBox>
#include <QRegExp>
#include <QRegExpValidator>

//
TableViewBase::TableViewBase(LogSql &sql) :
   _sql(sql),
   _tableView(NULL)
{
}
//

TableViewBase::~TableViewBase()
{
   _mapper.clearMapping();
   _model.clear();
}

void TableViewBase::setupView()
{
   // setup model
   _model.setTable(_tableName);
   _model.setSort(0, Qt::AscendingOrder);
   _model.setEditStrategy(QSqlTableModel::OnManualSubmit);
   _tableView->setModel(&_model);
   _tableView->setItemDelegate(getSqlRelationalDelegate());
   _mapper.setModel( &_model );
   _mapper.setItemDelegate(getSqlRelationalDelegate());
   _mapper.setSubmitPolicy(QDataWidgetMapper::AutoSubmit);

   for( cit = _viewMap.begin(); cit != _viewMap.end(); ++cit ) {
      _model.setHeaderData(cit.key(), Qt::Horizontal, cit.value().name);
      _tableView->setColumnHidden(cit.key(), !cit.value().visibleInTable);
      if( cit.value().relation != NULL )
         _model.setRelation(cit.key(), *cit.value().relation);
      if( cit.value().relation != NULL && cit.value().widget != NULL )
      {
         QComboBox* cb = qobject_cast<QComboBox*>(cit.value().widget);
         if( cb != NULL )
         {
            QSqlTableModel * m = _model.relationModel(cit.key());
            cb->setModel(m);
            cb->setModelColumn(m->fieldIndex(cit.value().relation->displayColumn()));
         }
      }
      if( cit.value().widget != NULL )
         _mapper.addMapping(cit.value().widget, cit.key());
   }
   _model.select();
   _mapper.toFirst();

   // connect table changes to detailed view updating
   // Note: this requires a common model!
   connect( _tableView->selectionModel(),
            SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
            &_mapper, SLOT(setCurrentModelIndex(QModelIndex)));
}

void TableViewBase::setupConnections( QPushButton *button_new,
                                          QPushButton *button_delete,
                                          QPushButton *button_revert,
                                          QPushButton *button_submit )
{
   if( button_new != NULL )
      connect( button_new,    SIGNAL(clicked()), this, SLOT(newRow()) );
   if( button_delete != NULL )
      connect( button_delete, SIGNAL(clicked()), this, SLOT(removeRow()) );
   if( button_revert != NULL )
      connect( button_revert, SIGNAL(clicked()), &_model, SLOT(revertAll()) );
   if( button_submit != NULL )
      connect( button_submit, SIGNAL(clicked()), this, SLOT(submit()) );
}

void TableViewBase::setTable(QString const& name, QTableView *table)
{
   _tableName = name;
   _tableView = table;
}

void TableViewBase::addEntry(int e, QString const& n, QVariant v,
                             bool vis, QWidget *w)
{
   _viewMap.insert(e, ViewMapEntry(n, v, vis, w, NULL));
}

void TableViewBase::addEntry(int e, QString const& n, QVariant v,
                             bool vis, QComboBox *w, QSqlRelation *r)
{
   _viewMap.insert(e, ViewMapEntry(n, v, vis, w, r));
}

      void addEntry( int entry,
                     QString const& name,
                     QVariant const& value,
                     bool visibleInTable,
                     QSqlRelation const& relation);

void TableViewBase::submit()
{
   QModelIndex const& index = _tableView->currentIndex();
   if( !_model.submitAll() )
   {
      QMessageBox::warning(NULL,
         tr("Failed writing to database"),
         tr("Error writing data to database:\%1").arg(_model.lastError().text()));
      _model.database().rollback();
   }
   _tableView->setCurrentIndex(index);
}

void TableViewBase::newRow()
{
   // get record template from table
   QSqlRecord r(_model.record());
   // initilize record with default values
   for( cit = _viewMap.begin(); cit != _viewMap.end(); ++cit )
      r.setValue(cit.key(), cit.value().defaultValue);
   _model.insertRecord(0, r);
   _tableView->selectRow(0);
}

void TableViewBase::removeRow()
{
   cit = _viewMap.begin();
   const int row = _tableView->currentIndex().row();
   QSqlRecord const& r = _model.record(row);
   QString const& name = cit.value().name;
   QString const& value = r.value(cit.key()).toString();
   QMessageBox msgBox( QMessageBox::Question,
      tr("Deleting database entry"),
      tr("Do you really want to delete the entry\n%1:  %2?").arg(name).arg(value));
   msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
   if( msgBox.exec() == QMessageBox::Yes )
   {
      _model.removeRow(row);
      submit();
   }
}


//Testing!!!
void TableViewBase::connectWidget(QString tableName, QString fieldIndex, QComboBox *widget)
{
    //_mapper = new QDataWidgetMapper(this);
    //_model = new QSqlRelationalTableModel(this);
    _model.setTable(tableName);
    _model.setSort(0, Qt::AscendingOrder);
    _mapper.setModel( &_model );
    //_mapper.setItemDelegate(getSqlRelationalDelegate());
    //_mapper.setSubmitPolicy(QDataWidgetMapper::AutoSubmit);
    _mapper.addMapping(widget, _model.fieldIndex(fieldIndex));
    widget->setModel(&_model);
    //widget->setItemDelegate(getSqlRelationalDelegate());
    _model.select();
    _mapper.toFirst();
}
