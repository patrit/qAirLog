#ifndef TABLEVIEWBASE_H
#define TABLEVIEWBASE_H
//
#include "logsql.h"

#include <QObject>
#include <QtSql>
#include <QMap>
#include <QString>
#include <QPushButton>
#include <QTableView>
#include <QDataWidgetMapper>
#include <QValidator>
//


class TableViewBase : public QObject
{
   Q_OBJECT

   public:
      TableViewBase(LogSql &sql);
      ~TableViewBase();

      /**
       * setupView must only be called after the whole table is set up
       * using setTable(...) and addEntry(...)
       */
      virtual void setupView();
      void setupConnections( QPushButton *button_new,
                             QPushButton *button_delete,
                             QPushButton *button_revert,
                             QPushButton *button_submit);
      void setTable( QString const& name, QTableView *table );
      void addEntry( int entry,
                     QString const& name,
                     QVariant value,
                     bool visibleInTable,
                     QWidget *widget = NULL);
      void addEntry( int entry,
                     QString const& name,
                     QVariant value,
                     bool visibleInTable,
                     QComboBox *widget,
                     QSqlRelation *relation);
      void connectWidget(QString tableName, QString fieldIndex, QComboBox *widget);
   public slots:
      virtual void submit();
      virtual void newRow();
      virtual void removeRow();

   protected:
      virtual QAbstractItemDelegate * getSqlRelationalDelegate()
      {
         return new QSqlRelationalDelegate(&_mapper);
      }
      QSqlRelationalTableModel _model;
      QDataWidgetMapper        _mapper;
   private:
      LogSql &_sql;

      QString _tableName;
      QTableView *_tableView;

      struct ViewMapEntry {
         QString name;
         QVariant defaultValue;
         bool visibleInTable;
         QWidget *widget;
         QSqlRelation *relation;
         ViewMapEntry(QString const& n, QVariant const& v,
                      bool vis, QWidget *w, QSqlRelation *r) :
            name(n), defaultValue(v), visibleInTable(vis), widget(w), relation(r)
         {}
      };
      typedef QMap<int,ViewMapEntry> ViewMap;
      ViewMap _viewMap;
      ViewMap::const_iterator cit;
      
};

#endif
