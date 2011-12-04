/****************************************************************************
** Meta object code from reading C++ file 'DebconfGui.h'
**
** Created: Wed Nov 9 01:48:33 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "DebconfGui.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'DebconfGui.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_DebconfKde__DebconfGui[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      24,   23,   23,   23, 0x05,
      36,   23,   23,   23, 0x05,

 // slots: signature, parameters, type, tag, flags
      62,   50,   23,   23, 0x0a,
      96,   90,   23,   23, 0x0a,
     118,   23,   23,   23, 0x08,
     138,   23,   23,   23, 0x08,
     158,   23,   23,   23, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_DebconfKde__DebconfGui[] = {
    "DebconfKde::DebconfGui\0\0activated()\0"
    "deactivated()\0title,input\0"
    "cmd_go(QString,QStringList)\0param\0"
    "cmd_progress(QString)\0on_nextPB_clicked()\0"
    "on_backPB_clicked()\0on_cancelPB_clicked()\0"
};

const QMetaObject DebconfKde::DebconfGui::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_DebconfKde__DebconfGui,
      qt_meta_data_DebconfKde__DebconfGui, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DebconfKde::DebconfGui::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DebconfKde::DebconfGui::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DebconfKde::DebconfGui::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DebconfKde__DebconfGui))
        return static_cast<void*>(const_cast< DebconfGui*>(this));
    return QWidget::qt_metacast(_clname);
}

int DebconfKde::DebconfGui::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: activated(); break;
        case 1: deactivated(); break;
        case 2: cmd_go((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QStringList(*)>(_a[2]))); break;
        case 3: cmd_progress((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: on_nextPB_clicked(); break;
        case 5: on_backPB_clicked(); break;
        case 6: on_cancelPB_clicked(); break;
        default: ;
        }
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void DebconfKde::DebconfGui::activated()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void DebconfKde::DebconfGui::deactivated()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
