#include <QCheckBox>
#include <QApplication>
#include <QStyleOptionViewItemV4>
#include <QRect>

#include "installeddelegate.h"

InstalledDelegate::InstalledDelegate(QObject *parent) : QItemDelegate(parent)
{
}

void InstalledDelegate::paint(QPainter *painter,const QStyleOptionViewItem &option, const QModelIndex &index) const
{
  bool temp = index.model()->data(index).toBool();

  QStyleOptionViewItem myoption = option;
  myoption.displayAlignment = Qt::AlignHCenter | Qt::AlignVCenter;
  drawCheck(painter,myoption,myoption.rect,
            temp ? Qt::Checked : Qt::Unchecked);
  drawFocus(painter,myoption,myoption.rect);

}

/*QWidget* InstalledDelegate::createEditor(QWidget *parent,const QStyleOptionViewItem &option, const QModelIndex &index) const
{
//  QMessageBox::warning(0,"",QString::number(index.row()));
  QCheckBox *cEdit = new QCheckBox(parent);
  cEdit->setEnabled(true);
  cEdit->setMaximumWidth(20);
  cEdit->setMaximumHeight(20);

  return cEdit;

}

void InstalledDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
  bool i = index.model()->data(index).toBool();

  QCheckBox *cEdit = qobject_cast<QCheckBox*>(editor);
  if (i)
    cEdit->setChecked(true);
  else
    cEdit->setChecked(false);
}

void InstalledDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,const QModelIndex &index) const
{
  QCheckBox *cEdit = qobject_cast<QCheckBox*>(editor);

  model->setData(index, QVariant(cEdit->isChecked()));
}*/

void InstalledDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
  if (index.isValid() && index.column() == 0) {
      editor->setGeometry(option.rect);
  }
  else
      QItemDelegate::updateEditorGeometry(editor, option, index);
}

