/****************************************************************************
** Meta object code from reading C++ file 'procesamiento.h'
**
** Created: Sat Feb 1 22:38:48 2014
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "procesamiento.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'procesamiento.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Procesamiento[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      15,   14,   14,   14, 0x05,
      30,   26,   14,   14, 0x05,

 // slots: signature, parameters, type, tag, flags
      54,   45,   14,   14, 0x0a,
      72,   14,   14,   14, 0x0a,
      85,   14,   14,   14, 0x0a,
      97,   14,   14,   14, 0x0a,
     111,   14,   14,   14, 0x0a,
     130,   14,   14,   14, 0x0a,
     142,   14,   14,   14, 0x0a,
     170,  149,   14,   14, 0x0a,
     212,   14,  196,   14, 0x0a,
     224,   14,  196,   14, 0x0a,
     240,   14,  235,   14, 0x0a,
     266,  248,   14,   14, 0x0a,
     297,  292,   14,   14, 0x0a,
     339,  316,   14,   14, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Procesamiento[] = {
    "Procesamiento\0\0finished()\0err\0"
    "error(QString)\0fileName\0openSignal(char*)\0"
    "playSignal()\0playClean()\0playSegment()\0"
    "playCleanSegment()\0playEnded()\0stop()\0"
    "cleanMod,thrMod,type\0cleanSignal(int,int,char)\0"
    "QVector<double>\0getSignal()\0getClean()\0"
    "long\0getFs()\0n_iRatio,n_fRatio\0"
    "setSegment(double,double)\0Name\0"
    "saveClean(QString)\0n_iRatio,n_fRatio,Name\0"
    "saveSegment(double,double,QString)\0"
};

void Procesamiento::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Procesamiento *_t = static_cast<Procesamiento *>(_o);
        switch (_id) {
        case 0: _t->finished(); break;
        case 1: _t->error((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->openSignal((*reinterpret_cast< char*(*)>(_a[1]))); break;
        case 3: _t->playSignal(); break;
        case 4: _t->playClean(); break;
        case 5: _t->playSegment(); break;
        case 6: _t->playCleanSegment(); break;
        case 7: _t->playEnded(); break;
        case 8: _t->stop(); break;
        case 9: _t->cleanSignal((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< char(*)>(_a[3]))); break;
        case 10: { QVector<double> _r = _t->getSignal();
            if (_a[0]) *reinterpret_cast< QVector<double>*>(_a[0]) = _r; }  break;
        case 11: { QVector<double> _r = _t->getClean();
            if (_a[0]) *reinterpret_cast< QVector<double>*>(_a[0]) = _r; }  break;
        case 12: { long _r = _t->getFs();
            if (_a[0]) *reinterpret_cast< long*>(_a[0]) = _r; }  break;
        case 13: _t->setSegment((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 14: _t->saveClean((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 15: _t->saveSegment((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Procesamiento::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Procesamiento::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Procesamiento,
      qt_meta_data_Procesamiento, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Procesamiento::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Procesamiento::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Procesamiento::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Procesamiento))
        return static_cast<void*>(const_cast< Procesamiento*>(this));
    return QObject::qt_metacast(_clname);
}

int Procesamiento::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    }
    return _id;
}

// SIGNAL 0
void Procesamiento::finished()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void Procesamiento::error(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
