#include "dependencywidget.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>

DependencyWidget::DependencyWidget(QWidget *parent) : QDialog(parent)
{
  m_dependencyList = new QTextBrowser();
  m_headerLabel = new QLabel(trUtf8("<b>Módosítandó csomagok listája:</b>"));
  setWindowTitle(trUtf8("Változtatások alkalmazása"));

  QVBoxLayout *mainLayout = new QVBoxLayout();
  QHBoxLayout *buttonLayout = new QHBoxLayout();

  QPushButton *okButton = new QPushButton(trUtf8("Ok"));
  QPushButton *cancelButton = new QPushButton(trUtf8("Mégse"));
  connect(okButton, SIGNAL(clicked()), this, SLOT(accept()));
  connect(cancelButton, SIGNAL(clicked()), this, SLOT(reject()));

  buttonLayout->addWidget(okButton);
  buttonLayout->addWidget(cancelButton);

  mainLayout->addWidget(m_headerLabel);
  mainLayout->addWidget(m_dependencyList);
  mainLayout->addLayout(buttonLayout);

  setLayout(mainLayout);
  //Nem szerkeszthető a lista
  m_dependencyList->setReadOnly(true);
}

void DependencyWidget::setPkgs(QList<QString> *pkgsInstall, QList<QString> *pkgsRemove)
{
  QString text("");

  Q_FOREACH(QString name, *pkgsInstall)
  {
    if (text == "")
        text += trUtf8("<b>Telepítendő:</b> <br />") + name;       
    else
        text += " <br />" + name;
  }

  if (pkgsRemove->size() != 0)
      text += " <br />" + trUtf8("<b>Eltávolítandó:</b>");
 
  Q_FOREACH(QString name, *pkgsRemove)
  {
    text += " <br />" + name;
  }

  m_dependencyList->setText(text);
}

void DependencyWidget::clear()
{
  m_dependencyList->clear();
}
