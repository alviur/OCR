/****************************************************************************
** Meta object code from reading C++ file 'plotwidget.h'
**
** Created: Sat Feb 1 22:38:46 2014
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "plotwidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'plotwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_plotWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x05,
      19,   11,   11,   11, 0x05,
      33,   11,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
      47,   41,   11,   11, 0x08,
      77,   11,   11,   11, 0x08,
     101,   11,   11,   11, 0x08,
     126,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_plotWidget[] = {
    "plotWidget\0\0play()\0playsegment()\0"
    "sstop()\0event\0mousePressEvent(QMouseEvent*)\0"
    "on_playsignal_clicked()\0"
    "on_playsegment_clicked()\0on_stop_clicked()\0"
};

void plotWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        plotWidget *_t = static_cast<plotWidget *>(_o);
        switch (_id) {
        case 0: _t->play(); break;
        case 1: _t->playsegment(); break;
        case 2: _t->sstop(); break;
        case 3: _t->mousePressEvent((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 4: _t->on_playsignal_clicked(); break;
        case 5: _t->on_playsegment_clicked(); break;
        case 6: _t->on_stop_clicked(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData plotWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject plotWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_plotWidget,
      qt_meta_data_plotWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &plotWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *plotWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *plotWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_plotWidget))
        return static_cast<void*>(const_cast< plotWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int plotWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void plotWidget::play()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void plotWidget::playsegment()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void plotWidget::sstop()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}
QT_END_MOC_NAMESPACE
