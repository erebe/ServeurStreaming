/****************************************************************************
** Meta object code from reading C++ file 'demandetcppull.h'
**
** Created: Sun Jan 22 22:02:20 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "Tcp_pull/demandetcppull.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'demandetcppull.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_DemandeTcpPull[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      16,   15,   15,   15, 0x05,
      34,   15,   15,   15, 0x05,

 // slots: signature, parameters, type, tag, flags
      68,   15,   15,   15, 0x09,
      82,   15,   15,   15, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_DemandeTcpPull[] = {
    "DemandeTcpPull\0\0requeteComplete()\0"
    "connexionTermine(DemandeTcpPull*)\0"
    "requeteRecu()\0traiterRequete()\0"
};

void DemandeTcpPull::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        DemandeTcpPull *_t = static_cast<DemandeTcpPull *>(_o);
        switch (_id) {
        case 0: _t->requeteComplete(); break;
        case 1: _t->connexionTermine((*reinterpret_cast< DemandeTcpPull*(*)>(_a[1]))); break;
        case 2: _t->requeteRecu(); break;
        case 3: _t->traiterRequete(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData DemandeTcpPull::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject DemandeTcpPull::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_DemandeTcpPull,
      qt_meta_data_DemandeTcpPull, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DemandeTcpPull::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DemandeTcpPull::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DemandeTcpPull::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DemandeTcpPull))
        return static_cast<void*>(const_cast< DemandeTcpPull*>(this));
    return QObject::qt_metacast(_clname);
}

int DemandeTcpPull::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void DemandeTcpPull::requeteComplete()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void DemandeTcpPull::connexionTermine(DemandeTcpPull * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
