/****************************************************************************
** Meta object code from reading C++ file 'adminreservationswindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../penyamanager/admin/adminreservationswindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'adminreservationswindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_PenyaManager__AdminReservationsWindow_t {
    QByteArrayData data[18];
    char stringdata0[454];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PenyaManager__AdminReservationsWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PenyaManager__AdminReservationsWindow_t qt_meta_stringdata_PenyaManager__AdminReservationsWindow = {
    {
QT_MOC_LITERAL(0, 0, 37), // "PenyaManager::AdminReservatio..."
QT_MOC_LITERAL(1, 38, 25), // "on_calendarWidget_clicked"
QT_MOC_LITERAL(2, 64, 0), // ""
QT_MOC_LITERAL(3, 65, 4), // "date"
QT_MOC_LITERAL(4, 70, 39), // "on_new_table_reservation_butt..."
QT_MOC_LITERAL(5, 110, 6), // "itemId"
QT_MOC_LITERAL(6, 117, 42), // "on_update_table_reservation_b..."
QT_MOC_LITERAL(7, 160, 38), // "on_new_oven_reservation_butto..."
QT_MOC_LITERAL(8, 199, 41), // "on_update_oven_reservation_bu..."
QT_MOC_LITERAL(9, 241, 43), // "on_new_fireplace_reservation_..."
QT_MOC_LITERAL(10, 285, 46), // "on_update_fireplace_reservati..."
QT_MOC_LITERAL(11, 332, 23), // "on_cancelButton_clicked"
QT_MOC_LITERAL(12, 356, 13), // "reservationId"
QT_MOC_LITERAL(13, 370, 19), // "ReservationItemType"
QT_MOC_LITERAL(14, 390, 8), // "itemType"
QT_MOC_LITERAL(15, 399, 22), // "on_lunchButton_clicked"
QT_MOC_LITERAL(16, 422, 7), // "checked"
QT_MOC_LITERAL(17, 430, 23) // "on_dinnerButton_clicked"

    },
    "PenyaManager::AdminReservationsWindow\0"
    "on_calendarWidget_clicked\0\0date\0"
    "on_new_table_reservation_button_clicked\0"
    "itemId\0on_update_table_reservation_button_clicked\0"
    "on_new_oven_reservation_button_clicked\0"
    "on_update_oven_reservation_button_clicked\0"
    "on_new_fireplace_reservation_button_clicked\0"
    "on_update_fireplace_reservation_button_clicked\0"
    "on_cancelButton_clicked\0reservationId\0"
    "ReservationItemType\0itemType\0"
    "on_lunchButton_clicked\0checked\0"
    "on_dinnerButton_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PenyaManager__AdminReservationsWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   64,    2, 0x08 /* Private */,
       4,    1,   67,    2, 0x08 /* Private */,
       6,    1,   70,    2, 0x08 /* Private */,
       7,    1,   73,    2, 0x08 /* Private */,
       8,    1,   76,    2, 0x08 /* Private */,
       9,    1,   79,    2, 0x08 /* Private */,
      10,    1,   82,    2, 0x08 /* Private */,
      11,    2,   85,    2, 0x08 /* Private */,
      15,    1,   90,    2, 0x08 /* Private */,
      17,    1,   93,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::QDate,    3,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 13,   12,   14,
    QMetaType::Void, QMetaType::Bool,   16,
    QMetaType::Void, QMetaType::Bool,   16,

       0        // eod
};

void PenyaManager::AdminReservationsWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        AdminReservationsWindow *_t = static_cast<AdminReservationsWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_calendarWidget_clicked((*reinterpret_cast< const QDate(*)>(_a[1]))); break;
        case 1: _t->on_new_table_reservation_button_clicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->on_update_table_reservation_button_clicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->on_new_oven_reservation_button_clicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->on_update_oven_reservation_button_clicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->on_new_fireplace_reservation_button_clicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->on_update_fireplace_reservation_button_clicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->on_cancelButton_clicked((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< ReservationItemType(*)>(_a[2]))); break;
        case 8: _t->on_lunchButton_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 9: _t->on_dinnerButton_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject PenyaManager::AdminReservationsWindow::staticMetaObject = {
    { &IPartner::staticMetaObject, qt_meta_stringdata_PenyaManager__AdminReservationsWindow.data,
      qt_meta_data_PenyaManager__AdminReservationsWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *PenyaManager::AdminReservationsWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PenyaManager::AdminReservationsWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_PenyaManager__AdminReservationsWindow.stringdata0))
        return static_cast<void*>(const_cast< AdminReservationsWindow*>(this));
    return IPartner::qt_metacast(_clname);
}

int PenyaManager::AdminReservationsWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = IPartner::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
