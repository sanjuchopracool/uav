/****************************************************************************
** Meta object code from reading C++ file 'SerialApp.h'
**
** Created: Sat Nov 24 00:34:40 2012
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
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: signature, parameters, type, tag, flags
      11,   10,   10,   10, 0x05,
      34,   10,   10,   10, 0x05,
      55,   10,   10,   10, 0x05,

 // slots: signature, parameters, type, tag, flags
      73,   10,   10,   10, 0x0a,
      80,   10,   10,   10, 0x0a,
      88,   10,   10,   10, 0x0a,
     101,   95,   10,   10, 0x0a,
     126,   10,   10,   10, 0x0a,
     134,   10,   10,   10, 0x0a,
     151,   10,   10,   10, 0x0a,
     158,   10,   10,   10, 0x0a,
     183,   10,   10,   10, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_SerialApp[] = {
    "SerialApp\0\0showPlotButtonSignal()\0"
    "lineReceivedApp(int)\0closePortSignal()\0"
    "open()\0close()\0send()\0array\0"
    "dataReceived(QByteArray)\0clear()\0"
    "refreshDevices()\0save()\0"
    "closeEvent(QCloseEvent*)\0showPlotButtonSlot()\0"
};

void SerialApp::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        SerialApp *_t = static_cast<SerialApp *>(_o);
        switch (_id) {
        case 0: _t->showPlotButtonSignal(); break;
        case 1: _t->lineReceivedApp((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->closePortSignal(); break;
        case 3: _t->open(); break;
        case 4: _t->close(); break;
        case 5: _t->send(); break;
        case 6: _t->dataReceived((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 7: _t->clear(); break;
        case 8: _t->refreshDevices(); break;
        case 9: _t->save(); break;
        case 10: _t->closeEvent((*reinterpret_cast< QCloseEvent*(*)>(_a[1]))); break;
        case 11: _t->showPlotButtonSlot(); break;
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
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void SerialApp::showPlotButtonSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void SerialApp::lineReceivedApp(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void SerialApp::closePortSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}
QT_END_MOC_NAMESPACE
