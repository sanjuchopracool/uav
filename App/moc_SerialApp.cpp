/****************************************************************************
** Meta object code from reading C++ file 'SerialApp.h'
**
** Created: Wed Nov 21 23:52:13 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "SerialApp.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SerialApp.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SerialApp[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      11,   10,   10,   10, 0x0a,
      18,   10,   10,   10, 0x0a,
      26,   10,   10,   10, 0x0a,
      39,   33,   10,   10, 0x0a,
      64,   10,   10,   10, 0x0a,
      72,   10,   10,   10, 0x0a,
      89,   10,   10,   10, 0x0a,
      96,   10,   10,   10, 0x0a,
     121,   10,   10,   10, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_SerialApp[] = {
    "SerialApp\0\0open()\0close()\0send()\0array\0"
    "dataReceived(QByteArray)\0clear()\0"
    "refreshDevices()\0save()\0"
    "closeEvent(QCloseEvent*)\0gridButtonSlot()\0"
};

void SerialApp::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        SerialApp *_t = static_cast<SerialApp *>(_o);
        switch (_id) {
        case 0: _t->open(); break;
        case 1: _t->close(); break;
        case 2: _t->send(); break;
        case 3: _t->dataReceived((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 4: _t->clear(); break;
        case 5: _t->refreshDevices(); break;
        case 6: _t->save(); break;
        case 7: _t->closeEvent((*reinterpret_cast< QCloseEvent*(*)>(_a[1]))); break;
        case 8: _t->gridButtonSlot(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData SerialApp::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject SerialApp::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_SerialApp,
      qt_meta_data_SerialApp, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SerialApp::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SerialApp::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SerialApp::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SerialApp))
        return static_cast<void*>(const_cast< SerialApp*>(this));
    return QWidget::qt_metacast(_clname);
}

int SerialApp::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
