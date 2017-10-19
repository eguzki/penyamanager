/****************************************************************************
** Meta object code from reading C++ file 'invoicelistwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../penyamanager/user/invoicelistwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'invoicelistwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_PenyaManager__InvoiceListWindow_t {
    QByteArrayData data[9];
    char stringdata0[199];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PenyaManager__InvoiceListWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PenyaManager__InvoiceListWindow_t qt_meta_stringdata_PenyaManager__InvoiceListWindow = {
    {
QT_MOC_LITERAL(0, 0, 31), // "PenyaManager::InvoiceListWindow"
QT_MOC_LITERAL(1, 32, 27), // "on_searchPushButton_clicked"
QT_MOC_LITERAL(2, 60, 0), // ""
QT_MOC_LITERAL(3, 61, 25), // "on_backPushButton_clicked"
QT_MOC_LITERAL(4, 87, 29), // "on_prevPagePushButton_clicked"
QT_MOC_LITERAL(5, 117, 29), // "on_nextPagePushButton_clicked"
QT_MOC_LITERAL(6, 147, 40), // "on_invoicesTableWidget_cellDo..."
QT_MOC_LITERAL(7, 188, 3), // "row"
QT_MOC_LITERAL(8, 192, 6) // "column"

    },
    "PenyaManager::InvoiceListWindow\0"
    "on_searchPushButton_clicked\0\0"
    "on_backPushButton_clicked\0"
    "on_prevPagePushButton_clicked\0"
    "on_nextPagePushButton_clicked\0"
    "on_invoicesTableWidget_cellDoubleClicked\0"
    "row\0column"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PenyaManager__InvoiceListWindow[] = {

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
       4,    0,   41,    2, 0x08 /* Private */,
       5,    0,   42,    2, 0x08 /* Private */,
       6,    2,   43,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    7,    8,

       0        // eod
};

void PenyaManager::InvoiceListWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        InvoiceListWindow *_t = static_cast<InvoiceListWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_searchPushButton_clicked(); break;
        case 1: _t->on_backPushButton_clicked(); break;
        case 2: _t->on_prevPagePushButton_clicked(); break;
        case 3: _t->on_nextPagePushButton_clicked(); break;
        case 4: _t->on_invoicesTableWidget_cellDoubleClicked((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObject PenyaManager::InvoiceListWindow::staticMetaObject = {
    { &IPartner::staticMetaObject, qt_meta_stringdata_PenyaManager__InvoiceListWindow.data,
      qt_meta_data_PenyaManager__InvoiceListWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *PenyaManager::InvoiceListWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PenyaManager::InvoiceListWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_PenyaManager__InvoiceListWindow.stringdata0))
        return static_cast<void*>(const_cast< InvoiceListWindow*>(this));
    return IPartner::qt_metacast(_clname);
}

int PenyaManager::InvoiceListWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
