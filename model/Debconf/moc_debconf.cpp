/****************************************************************************
** Meta object code from reading C++ file 'debconf.h'
**
** Created: Wed Nov 9 01:48:24 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "debconf.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'debconf.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_DebconfKde__DebconfFrontend[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       2,   49, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: signature, parameters, type, tag, flags
      41,   29,   28,   28, 0x05,
      71,   65,   28,   28, 0x05,
      89,   28,   28,   28, 0x05,
     108,  100,   28,   28, 0x05,

 // slots: signature, parameters, type, tag, flags
     126,   28,  121,   28, 0x08,
     136,   28,   28,   28, 0x08,
     152,   28,   28,   28, 0x08,

 // enums: name, flags, count, data
     167, 0x0,    5,   57,
     179, 0x0,   11,   67,

 // enum data: key, value
     187, uint(DebconfKde::DebconfFrontend::Choices),
     195, uint(DebconfKde::DebconfFrontend::Description),
     207, uint(DebconfKde::DebconfFrontend::ExtendedDescription),
     227, uint(DebconfKde::DebconfFrontend::Type),
     232, uint(DebconfKde::DebconfFrontend::UnknownPropertyKey),
     251, uint(DebconfKde::DebconfFrontend::String),
     258, uint(DebconfKde::DebconfFrontend::Password),
     267, uint(DebconfKde::DebconfFrontend::Progress),
     276, uint(DebconfKde::DebconfFrontend::Boolean),
     284, uint(DebconfKde::DebconfFrontend::Select),
     291, uint(DebconfKde::DebconfFrontend::Multiselect),
     303, uint(DebconfKde::DebconfFrontend::Note),
     308, uint(DebconfKde::DebconfFrontend::Error),
     314, uint(DebconfKde::DebconfFrontend::Title),
     320, uint(DebconfKde::DebconfFrontend::Text),
     325, uint(DebconfKde::DebconfFrontend::UnknownTypeKey),

       0        // eod
};

static const char qt_meta_stringdata_DebconfKde__DebconfFrontend[] = {
    "DebconfKde::DebconfFrontend\0\0title,input\0"
    "go(QString,QStringList)\0param\0"
    "progress(QString)\0finished()\0capable\0"
    "backup(bool)\0bool\0process()\0newConnection()\0"
    "disconnected()\0PropertyKey\0TypeKey\0"
    "Choices\0Description\0ExtendedDescription\0"
    "Type\0UnknownPropertyKey\0String\0Password\0"
    "Progress\0Boolean\0Select\0Multiselect\0"
    "Note\0Error\0Title\0Text\0UnknownTypeKey\0"
};

const QMetaObject DebconfKde::DebconfFrontend::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_DebconfKde__DebconfFrontend,
      qt_meta_data_DebconfKde__DebconfFrontend, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DebconfKde::DebconfFrontend::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DebconfKde::DebconfFrontend::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DebconfKde::DebconfFrontend::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DebconfKde__DebconfFrontend))
        return static_cast<void*>(const_cast< DebconfFrontend*>(this));
    return QObject::qt_metacast(_clname);
}

int DebconfKde::DebconfFrontend::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: go((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QStringList(*)>(_a[2]))); break;
        case 1: progress((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: finished(); break;
        case 3: backup((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: { bool _r = process();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 5: newConnection(); break;
        case 6: disconnected(); break;
        default: ;
        }
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void DebconfKde::DebconfFrontend::go(const QString & _t1, const QStringList & _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void DebconfKde::DebconfFrontend::progress(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void DebconfKde::DebconfFrontend::finished()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void DebconfKde::DebconfFrontend::backup(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_END_MOC_NAMESPACE
