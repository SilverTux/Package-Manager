#ifndef PKGPROPERTYWIDGET_H
#define PKGPROPERTYWIDGET_H

#include <QWidget>
#include <QTabWidget>
#include <QLabel>
#include <QTextBrowser>

class PkgPropertyWidget : public QWidget
{
public:
    PkgPropertyWidget(QWidget *parent=0);
    void setProperties(QStringList *desc);
    void setDependencyList(QStringList dep);

private:
    void setupUi();
    void resizeDependencyList();

    QWidget *m_description;
    QWidget *m_dependencyList;
    QTabWidget *m_tabWidget;

    QLabel *m_nameLabel;
    QLabel *m_sectionLabel;
    QLabel *m_originLabel;
    QLabel *m_installedSizeLabel;
    QLabel *m_maintainerLabel;
    QLabel *m_sourceLabel;
    QLabel *m_versionLabel;
    QLabel *m_packageSizeLabel;
    QLabel *m_shortDescriptionLabel;
    QLabel *m_homepage;
    QTextBrowser *m_dependencyBrowser;
};

#endif // PKGPROPERTYWIDGET_H
