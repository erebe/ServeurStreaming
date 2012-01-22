/****************************************************************************
** Meta object code from reading C++ file 'serveurUdpPull.h'
**
** Created: Sun Jan 22 22:02:22 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "Udp_pull/serveurUdpPull.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'serveurUdpPull.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ServeurUdpPull[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      16,   15,   15,   15, 0x09,
      32,   15,   15,   15, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_ServeurUdpPull[] = {
    "ServeurUdpPull\0\0lecturePaquet()\0"
    "deleteSock(ClientUdpPull*)\0"
};

void ServeurUdpPull::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ServeurUdpPull *_t = static_cast<ServeurUdpPull *>(_o);
        switch (_id) {
        case 0: _t->lecturePaquet(); break;
        case 1: _t->deleteSock((*reinterpret_cast< ClientUdpPull*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ServeurUdpPull::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ServeurUdpPull::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ServeurUdpPull,
      qt_meta_data_ServeurUdpPull, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ServeurUdpPull::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ServeurUdpPull::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ServeurUdpPull::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ServeurUdpPull))
        return static_cast<void*>(const_cast< ServeurUdpPull*>(this));
    return QObject::qt_metacast(_clname);
}

int ServeurUdpPull::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
