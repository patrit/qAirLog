#ifndef TABLEVIEWWITHVALIDATOR_H
#define TABLEVIEWWITHVALIDATOR_H

#include "tableViewBase.h"


class QSqlValidatorDelegate : public QSqlRelationalDelegate
{
   public:
      QSqlValidatorDelegate(QDataWidgetMapper*m, 
                            QMap<int,QValidator *> const& validatorMap) :
         QSqlRelationalDelegate(m),
         _validatorMap(validatorMap)
      {}
      virtual ~QSqlValidatorDelegate();
//       virtual QWidget *createEditor(QWidget *parent,
//                             QStyleOptionViewItem const& option,
//                             QModelIndex const& index ) const; 

   private:
      typedef QMap<int,QValidator *> ValidatorMap;
      ValidatorMap const& _validatorMap;
};



class TableViewWithValidator : public TableViewBase
{
   public:
      TableViewWithValidator(LogSql &sql);
      virtual ~TableViewWithValidator();

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
      void addEntry( int entry,
                     QString const& name,
                     QVariant value,
                     bool visibleInTable,
                     QValidator *vtor,
                     QWidget *widget = NULL);
      void addEntry( int entry,
                     QString const& name,
                     QVariant value,
                     bool visibleInTable,
                     QString vtor,
                     QWidget *widget = NULL);
   protected:
      virtual QAbstractItemDelegate * getSqlRelationalDelegate();

   private:
      typedef QMap<int,QValidator *> ValidatorMap;
      ValidatorMap _validatorMap;
};


#endif
