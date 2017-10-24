/****************************************************************************
** Meta object code from reading C++ file 'memberdashboardwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../penyamanager/user/memberdashboardwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'memberdashboardwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_PenyaManager__MemberDashboardWindow_t {
    QByteArrayData data[17];
    char stringdata0[371];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PenyaManager__MemberDashboardWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PenyaManager__MemberDashboardWindow_t qt_meta_stringdata_PenyaManager__MemberDashboardWindow = {
    {
QT_MOC_LITERAL(0, 0, 35), // "PenyaManager::MemberDashboard..."
QT_MOC_LITERAL(1, 36, 4), // "init"
QT_MOC_LITERAL(2, 41, 0), // ""
QT_MOC_LITERAL(3, 42, 29), // "on_invoiceCloseButton_clicked"
QT_MOC_LITERAL(4, 72, 29), // "on_invoiceResetButton_clicked"
QT_MOC_LITERAL(5, 102, 21), // "on_exitButton_clicked"
QT_MOC_LITERAL(6, 124, 25), // "on_depositsButton_clicked"
QT_MOC_LITERAL(7, 150, 33), // "on_invoiceTableWidget_cellCli..."
QT_MOC_LITERAL(8, 184, 3), // "row"
QT_MOC_LITERAL(9, 188, 6), // "column"
QT_MOC_LITERAL(10, 195, 24), // "on_accountButton_clicked"
QT_MOC_LITERAL(11, 220, 33), // "on_tableReservationButton_cli..."
QT_MOC_LITERAL(12, 254, 29), // "on_invoicesPushButton_clicked"
QT_MOC_LITERAL(13, 284, 31), // "on_familyListWidget_itemClicked"
QT_MOC_LITERAL(14, 316, 16), // "QListWidgetItem*"
QT_MOC_LITERAL(15, 333, 4), // "item"
QT_MOC_LITERAL(16, 338, 32) // "on_productListWidget_itemClicked"

    },
    "PenyaManager::MemberDashboardWindow\0"
    "init\0\0on_invoiceCloseButton_clicked\0"
    "on_invoiceResetButton_clicked\0"
    "on_exitButton_clicked\0on_depositsButton_clicked\0"
    "on_invoiceTableWidget_cellClicked\0row\0"
    "column\0on_accountButton_clicked\0"
    "on_tableReservationButton_clicked\0"
    "on_invoicesPushButton_clicked\0"
    "on_familyListWidget_itemClicked\0"
    "QListWidgetItem*\0item\0"
    "on_productListWidget_itemClicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PenyaManager__MemberDashboardWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   69,    2, 0x08 /* Private */,
       3,    0,   70,    2, 0x08 /* Private */,
       4,    0,   71,    2, 0x08 /* Private */,
       5,    0,   72,    2, 0x08 /* Private */,
       6,    0,   73,    2, 0x08 /* Private */,
       7,    2,   74,    2, 0x08 /* Private */,
      10,    0,   79,    2, 0x08 /* Private */,
      11,    0,   80,    2, 0x08 /* Private */,
      12,    0,   81,    2, 0x08 /* Private */,
      13,    1,   82,    2, 0x08 /* Private */,
      16,    1,   85,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    8,    9,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 14,   15,
    QMetaType::Void, 0x80000000 | 14,   15,

       0        // eod
};

void PenyaManager::MemberDashboardWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MemberDashboardWindow *_t = static_cast<MemberDashboardWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->init(); break;
        case 1: _t->on_invoiceCloseButton_clicked(); break;
        case 2: _t->on_invoiceResetButton_clicked(); break;
        case 3: _t->on_exitButton_clicked(); break;
        case 4: _t->on_depositsButton_clicked(); break;
        case 5: _t->on_invoiceTableWidget_cellClicked((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 6: _t->on_accountButton_clicked(); break;
        case 7: _t->on_tableReservationButton_clicked(); break;
        case 8: _t->on_invoicesPushButton_clicked(); break;
        case 9: _t->on_familyListWidget_itemClicked((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 10: _t->on_productListWidget_itemClicked((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject PenyaManager::MemberDashboardWindow::staticMetaObject = {
    { &IPartner::staticMetaObject, qt_meta_stringdata_PenyaManager__MemberDashboardWindow.data,
      qt_meta_data_PenyaManager__MemberDashboardWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *PenyaManager::MemberDashboardWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PenyaManager::MemberDashboardWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_PenyaManager__MemberDashboardWindow.stringdata0))
        return static_cast<void*>(const_cast< MemberDashboardWindow*>(this));
    return IPartner::qt_metacast(_clname);
}

int PenyaManager::MemberDashboardWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = IPartner::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
