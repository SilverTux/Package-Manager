/****************************************************************************
** Meta object code from reading C++ file 'DebconfString.h'
**
** Created: Wed Nov 9 01:48:46 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "DebconfString.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'DebconfString.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_DebconfKde__DebconfString[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

static const char qt_meta_stringdata_DebconfKde__DebconfString[] = {
    "DebconfKde::DebconfString\0"
};

const QMetaObject DebconfKde::DebconfString::staticMetaObject = {
    { &DebconfElement::staticMetaObject, qt_meta_stringdata_DebconfKde__DebconfString,
      qt_meta_data_DebconfKde__DebconfString, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DebconfKde::DebconfString::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DebconfKde::DebconfString::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DebconfKde::DebconfString::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DebconfKde__DebconfString))
        return static_cast<void*>(const_cast< DebconfString*>(this));
    if (!strcmp(_clname, "Ui::DebconfString"))
        return static_cast< Ui::DebconfString*>(const_cast< DebconfString*>(this));
    return DebconfElement::qt_metacast(_clname);
}

int DebconfKde::DebconfString::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = DebconfElement::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
QT_END_MOC_NAMESPACE