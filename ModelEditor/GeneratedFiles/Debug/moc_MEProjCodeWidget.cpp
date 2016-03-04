/****************************************************************************
** Meta object code from reading C++ file 'MEProjCodeWidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../MEProjCodeWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MEProjCodeWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MEProjCodeWidget_t {
    QByteArrayData data[8];
    char stringdata[116];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_MEProjCodeWidget_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_MEProjCodeWidget_t qt_meta_stringdata_MEProjCodeWidget = {
    {
QT_MOC_LITERAL(0, 0, 16),
QT_MOC_LITERAL(1, 17, 25),
QT_MOC_LITERAL(2, 43, 0),
QT_MOC_LITERAL(3, 44, 14),
QT_MOC_LITERAL(4, 59, 20),
QT_MOC_LITERAL(5, 80, 20),
QT_MOC_LITERAL(6, 101, 5),
QT_MOC_LITERAL(7, 107, 7)
    },
    "MEProjCodeWidget\0UpdateLineNumberAreaWidth\0"
    "\0nNewBlockCount\0HighlightCurrentLine\0"
    "UpdateLineNumberArea\0qRect\0nDeltaY\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MEProjCodeWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x08,
       4,    0,   32,    2, 0x08,
       5,    2,   33,    2, 0x08,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QRect, QMetaType::Int,    6,    7,

       0        // eod
};

void MEProjCodeWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MEProjCodeWidget *_t = static_cast<MEProjCodeWidget *>(_o);
        switch (_id) {
        case 0: _t->UpdateLineNumberAreaWidth((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->HighlightCurrentLine(); break;
        case 2: _t->UpdateLineNumberArea((*reinterpret_cast< const QRect(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObject MEProjCodeWidget::staticMetaObject = {
    { &QPlainTextEdit::staticMetaObject, qt_meta_stringdata_MEProjCodeWidget.data,
      qt_meta_data_MEProjCodeWidget,  qt_static_metacall, 0, 0}
};


const QMetaObject *MEProjCodeWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MEProjCodeWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MEProjCodeWidget.stringdata))
        return static_cast<void*>(const_cast< MEProjCodeWidget*>(this));
    return QPlainTextEdit::qt_metacast(_clname);
}

int MEProjCodeWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QPlainTextEdit::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
