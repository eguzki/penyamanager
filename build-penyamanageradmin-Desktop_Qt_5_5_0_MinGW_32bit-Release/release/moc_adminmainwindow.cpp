/****************************************************************************
** Meta object code from reading C++ file 'adminmainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../penyamanager/admin/adminmainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'adminmainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_PenyaManager__AdminMainWindow_t {
    QByteArrayData data[15];
    char stringdata0[495];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PenyaManager__AdminMainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PenyaManager__AdminMainWindow_t qt_meta_stringdata_PenyaManager__AdminMainWindow = {
    {
QT_MOC_LITERAL(0, 0, 29), // "PenyaManager::AdminMainWindow"
QT_MOC_LITERAL(1, 30, 24), // "on_exit_button_triggered"
QT_MOC_LITERAL(2, 55, 0), // ""
QT_MOC_LITERAL(3, 56, 31), // "on_slow_payers_button_triggered"
QT_MOC_LITERAL(4, 88, 32), // "on_invoice_list_button_triggered"
QT_MOC_LITERAL(5, 121, 36), // "on_manage_providers_button_tr..."
QT_MOC_LITERAL(6, 158, 32), // "on_manage_stock_button_triggered"
QT_MOC_LITERAL(7, 191, 39), // "on_manage_family_items_button..."
QT_MOC_LITERAL(8, 231, 36), // "on_product_expenses_button_tr..."
QT_MOC_LITERAL(9, 268, 36), // "on_provider_invoice_button_tr..."
QT_MOC_LITERAL(10, 305, 41), // "on_provider_invoice_list_butt..."
QT_MOC_LITERAL(11, 347, 32), // "on_deposit_list_button_triggered"
QT_MOC_LITERAL(12, 380, 40), // "on_account_balance_list_butto..."
QT_MOC_LITERAL(13, 421, 36), // "on_member_list_view_button_tr..."
QT_MOC_LITERAL(14, 458, 36) // "on_reservation_view_button_tr..."

    },
    "PenyaManager::AdminMainWindow\0"
    "on_exit_button_triggered\0\0"
    "on_slow_payers_button_triggered\0"
    "on_invoice_list_button_triggered\0"
    "on_manage_providers_button_triggered\0"
    "on_manage_stock_button_triggered\0"
    "on_manage_family_items_button_triggered\0"
    "on_product_expenses_button_triggered\0"
    "on_provider_invoice_button_triggered\0"
    "on_provider_invoice_list_button_triggered\0"
    "on_deposit_list_button_triggered\0"
    "on_account_balance_list_button_triggered\0"
    "on_member_list_view_button_triggered\0"
    "on_reservation_view_button_triggered"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PenyaManager__AdminMainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   79,    2, 0x08 /* Private */,
       3,    0,   80,    2, 0x08 /* Private */,
       4,    0,   81,    2, 0x08 /* Private */,
       5,    0,   82,    2, 0x08 /* Private */,
       6,    0,   83,    2, 0x08 /* Private */,
       7,    0,   84,    2, 0x08 /* Private */,
       8,    0,   85,    2, 0x08 /* Private */,
       9,    0,   86,    2, 0x08 /* Private */,
      10,    0,   87,    2, 0x08 /* Private */,
      11,    0,   88,    2, 0x08 /* Private */,
      12,    0,   89,    2, 0x08 /* Private */,
      13,    0,   90,    2, 0x08 /* Private */,
      14,    0,   91,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void PenyaManager::AdminMainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        AdminMainWindow *_t = static_cast<AdminMainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_exit_button_triggered(); break;
        case 1: _t->on_slow_payers_button_triggered(); break;
        case 2: _t->on_invoice_list_button_triggered(); break;
        case 3: _t->on_manage_providers_button_triggered(); break;
        case 4: _t->on_manage_stock_button_triggered(); break;
        case 5: _t->on_manage_family_items_button_triggered(); break;
        case 6: _t->on_product_expenses_button_triggered(); break;
        case 7: _t->on_provider_invoice_button_triggered(); break;
        case 8: _t->on_provider_invoice_list_button_triggered(); break;
        case 9: _t->on_deposit_list_button_triggered(); break;
        case 10: _t->on_account_balance_list_button_triggered(); break;
        case 11: _t->on_member_list_view_button_triggered(); break;
        case 12: _t->on_reservation_view_button_triggered(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject PenyaManager::AdminMainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_PenyaManager__AdminMainWindow.data,
      qt_meta_data_PenyaManager__AdminMainWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *PenyaManager::AdminMainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PenyaManager::AdminMainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_PenyaManager__AdminMainWindow.stringdata0))
        return static_cast<void*>(const_cast< AdminMainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int PenyaManager::AdminMainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
