#include <QVBoxLayout>
#include <QtGui>

#include "pkgpropertywidget.h"

PkgPropertyWidget::PkgPropertyWidget(QWidget *parent) : QWidget(parent)
{
    setupUi();

    setWindowTitle(trUtf8("Tulajdonságok"));
}

void PkgPropertyWidget::setProperties(QStringList *desc)
{
    m_nameLabel->setText(desc->at(0));
    m_sectionLabel->setText(desc->at(1));
    m_originLabel->setText(desc->at(2));
    m_installedSizeLabel->setText(desc->at(3));
    m_maintainerLabel->setText(desc->at(4));
    m_sourceLabel->setText(desc->at(5));
    m_versionLabel->setText(desc->at(6));
    m_packageSizeLabel->setText(desc->at(7));
    m_shortDescriptionLabel->setText(desc->at(8));
    m_homepage->setText(desc->at(9));

    resizeDependencyList();
}

void PkgPropertyWidget::setDependencyList(QStringList dep)
{
    QString temp;

    Q_FOREACH (QString str, dep) {
        temp += str + "<br />";
    }

    m_dependencyBrowser->setHtml(temp);
}

void PkgPropertyWidget::setupUi()
{
    m_tabWidget = new QTabWidget(this);
    m_description = new QWidget();
    m_dependencyList = new QWidget();
    QVBoxLayout *dependencyListL = new QVBoxLayout();
    m_dependencyBrowser = new QTextBrowser(m_dependencyList);
    m_tabWidget->addTab(m_description,trUtf8("Tulajdonságok"));
    m_tabWidget->addTab(m_dependencyList,trUtf8("Függőségek"));

    QVBoxLayout *layout = new QVBoxLayout();
    QVBoxLayout *descLayout = new QVBoxLayout();

    layout->addWidget(m_tabWidget);

    setLayout(layout);

    m_nameLabel = new QLabel();
    m_sectionLabel = new QLabel();
    m_originLabel = new QLabel();
    m_installedSizeLabel = new QLabel();
    m_maintainerLabel = new QLabel();
    m_sourceLabel = new QLabel();
    m_versionLabel = new QLabel();
    m_packageSizeLabel = new QLabel();
    m_shortDescriptionLabel = new QLabel();
    m_homepage = new QLabel();

    descLayout->addWidget(m_nameLabel);
    descLayout->addWidget(m_sectionLabel);
    descLayout->addWidget(m_originLabel);
    descLayout->addWidget(m_installedSizeLabel);
    descLayout->addWidget(m_maintainerLabel);
    descLayout->addWidget(m_sourceLabel);
    descLayout->addWidget(m_versionLabel);
    descLayout->addWidget(m_packageSizeLabel);
    descLayout->addWidget(m_shortDescriptionLabel);
    descLayout->addWidget(m_homepage);

    dependencyListL->addWidget(m_dependencyBrowser);

    m_description->setLayout(descLayout);
    m_dependencyList->setLayout(dependencyListL);
}

void PkgPropertyWidget::resizeDependencyList()
{
    m_dependencyBrowser->setMaximumSize(width()*2,height()*2);
}
