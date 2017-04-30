#include "tableViewWithValidator.h"

#include <QMessageBox>
#include <QRegExp>
#include <QRegExpValidator>
#include <QPainter>


QSqlValidatorDelegate::~QSqlValidatorDelegate()
{}

// QWidget *QSqlValidatorDelegate::createEditor(QWidget *parent,
//       QStyleOptionViewItem const& option, QModelIndex const& index) const
// {
//    qDebug() << "createEditor " << index.row() << endl;
//    QWidget *w = static_cast<QSqlRelationalDelegate const*>(this)->createEditor(parent, option, index);
//    qDebug() << "createEditor w=" << w << endl;
//    if( _validatorMap.find(index.row()) != _validatorMap.end() )
//    {
//       QValidator *vtor = _validatorMap[index.row()];
//       QLineEdit *le = qobject_cast<QLineEdit*>(w);
//       qDebug() << "createEditor vtor= " << vtor << ", le = " << le << endl;
//       if( le and vtor )
//          le->setValidator(vtor);
//    }
//    return w;
// }
      
// void QSqlValidatorDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, 
//          const QModelIndex & index ) const  
// {
//    if(index.row() == 0 ) {
//       QRect r;
//       painter->drawText(option.rect,Qt::TextSingleLine, "Item ",
//                         &r);
//       painter->setPen(Qt::red);
//       QRect modOptRect = option.rect;
//       modOptRect.setLeft(option.rect.left() + r.width());
//       painter->drawText(modOptRect, "1");
//    } else {
//       QItemDelegate::paint(painter, option, index);
//    }
// }






//
TableViewWithValidator::TableViewWithValidator(LogSql &sql) :
   TableViewBase(sql)
{
}
//

TableViewWithValidator::~TableViewWithValidator()
{
//    _mapper.clearMapping();
//    _model.clear();
}

QAbstractItemDelegate * TableViewWithValidator::getSqlRelationalDelegate()
{
   return new QSqlValidatorDelegate(&_mapper, _validatorMap);
}



void TableViewWithValidator::addEntry(int e, QString const& n, QVariant v,
                             bool vis, QWidget *w)
{
   qobject_cast<TableViewBase*>(this)->addEntry(e, n, v, vis, w);
}

void TableViewWithValidator::addEntry(int e, QString const& n, QVariant v,
                             bool vis, QComboBox *w, QSqlRelation *r)
{
   qobject_cast<TableViewBase*>(this)->addEntry(e, n, v, vis, w, r);
}

void TableViewWithValidator::addEntry(int e, QString const& n, QVariant v,
                             bool vis, QValidator *vtor, QWidget *w)
{
   qobject_cast<TableViewBase*>(this)->addEntry(e, n, v, vis, w);
   _validatorMap.insert(e, vtor);
}

void TableViewWithValidator::addEntry(int e, QString const& n, QVariant v,
                             bool vis, QString vtor, QWidget *w)
{
   qobject_cast<TableViewBase*>(this)->addEntry(e, n, v, vis, w);
   _validatorMap.insert(e, new QRegExpValidator(QRegExp(vtor), this));
}


