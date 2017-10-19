/****************************************************************************
** Meta object code from reading C++ file 'depositwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../penyamanager/user/depositwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'depositwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_PenyaManager__DepositWindow_t {
    QByteArrayData data[9];
    char stringdata0[167];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PenyaManager__DepositWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PenyaManager__DepositWindow_t qt_meta_stringdata_PenyaManager__DepositWindow = {
    {
QT_MOC_LITERAL(0, 0, 27), // "PenyaManager::DepositWindow"
QT_MOC_LITERAL(1, 28, 21), // "on_backButton_clicked"
QT_MOC_LITERAL(2, 50, 0), // ""
QT_MOC_LITERAL(3, 51, 24), // "on_confirmButton_clicked"
QT_MOC_LITERAL(4, 76, 28), // "on_pushButton_number_clicked"
QT_MOC_LITERAL(5, 105, 6), // "Uint32"
QT_MOC_LITERAL(6, 112, 3), // "num"
QT_MOC_LITERAL(7, 116, 26), // "on_pushButton_coma_clicked"
QT_MOC_LITERAL(8, 143, 23) // "on_pushButton_C_clicked"

    },
    "PenyaManager::DepositWindow\0"
    "on_backButton_clicked\0\0on_confirmButton_clicked\0"
    "on_pushButton_number_clicked\0Uint32\0"
    "num\0on_pushButton_coma_clicked\0"
    "on_pushButton_C_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PenyaManager__DepositWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x08 /* Private */,
       3,    0,   40,    2, 0x08 /* Private */,
       4,    1,   41,    2, 0x08 /* Private */,
       7,    0,   44,    2, 0x08 /* Private */,
       8,    0,   45,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void PenyaManager::DepositWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        DepositWindow *_t = static_cast<DepositWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_backButton_clicked(); break;
        case 1: _t->on_confirmButton_clicked(); break;
        case 2: _t->on_pushButton_number_clicked((*reinterpret_cast< Uint32(*)>(_a[1]))); break;
        case 3: _t->on_pushButton_coma_clicked(); break;
        case 4: _t->on_pushButton_C_clicked(); break;
        default: ;
        }
    }
}

const QMetaObject PenyaManager::DepositWindow::staticMetaObject = {
    { &IPartner::staticMetaObject, qt_meta_stringdata_PenyaManager__DepositWindow.data,
      qt_meta_data_PenyaManager__DepositWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *PenyaManager::DepositWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PenyaManager::DepositWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_PenyaManager__DepositWindow.stringdata0))
        return static_cast<void*>(const_cast< DepositWindow*>(this));
    return IPartner::qt_metacast(_clname);
}

int PenyaManager::DepositWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = IPartner::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
