/****************************************************************************
** Meta object code from reading C++ file 'tablereservationview.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../penyamanager/user/tablereservationview.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'tablereservationview.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_PenyaManager__TableReservationView_t {
    QByteArrayData data[14];
    char stringdata0[244];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PenyaManager__TableReservationView_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PenyaManager__TableReservationView_t qt_meta_stringdata_PenyaManager__TableReservationView = {
    {
QT_MOC_LITERAL(0, 0, 34), // "PenyaManager::TableReservatio..."
QT_MOC_LITERAL(1, 35, 21), // "on_backButton_clicked"
QT_MOC_LITERAL(2, 57, 0), // ""
QT_MOC_LITERAL(3, 58, 25), // "on_calendarWidget_clicked"
QT_MOC_LITERAL(4, 84, 4), // "date"
QT_MOC_LITERAL(5, 89, 25), // "on_reservedButton_clicked"
QT_MOC_LITERAL(6, 115, 6), // "itemId"
QT_MOC_LITERAL(7, 122, 19), // "ReservationItemType"
QT_MOC_LITERAL(8, 142, 8), // "itemType"
QT_MOC_LITERAL(9, 151, 23), // "on_cancelButton_clicked"
QT_MOC_LITERAL(10, 175, 13), // "reservationId"
QT_MOC_LITERAL(11, 189, 22), // "on_lunchButton_clicked"
QT_MOC_LITERAL(12, 212, 7), // "checked"
QT_MOC_LITERAL(13, 220, 23) // "on_dinnerButton_clicked"

    },
    "PenyaManager::TableReservationView\0"
    "on_backButton_clicked\0\0on_calendarWidget_clicked\0"
    "date\0on_reservedButton_clicked\0itemId\0"
    "ReservationItemType\0itemType\0"
    "on_cancelButton_clicked\0reservationId\0"
    "on_lunchButton_clicked\0checked\0"
    "on_dinnerButton_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PenyaManager__TableReservationView[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x08 /* Private */,
       3,    1,   45,    2, 0x08 /* Private */,
       5,    2,   48,    2, 0x08 /* Private */,
       9,    2,   53,    2, 0x08 /* Private */,
      11,    1,   58,    2, 0x08 /* Private */,
      13,    1,   61,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QDate,    4,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 7,    6,    8,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 7,   10,    8,
    QMetaType::Void, QMetaType::Bool,   12,
    QMetaType::Void, QMetaType::Bool,   12,

       0        // eod
};

void PenyaManager::TableReservationView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TableReservationView *_t = static_cast<TableReservationView *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_backButton_clicked(); break;
        case 1: _t->on_calendarWidget_clicked((*reinterpret_cast< const QDate(*)>(_a[1]))); break;
        case 2: _t->on_reservedButton_clicked((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< ReservationItemType(*)>(_a[2]))); break;
        case 3: _t->on_cancelButton_clicked((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< ReservationItemType(*)>(_a[2]))); break;
        case 4: _t->on_lunchButton_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->on_dinnerButton_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject PenyaManager::TableReservationView::staticMetaObject = {
    { &IPartner::staticMetaObject, qt_meta_stringdata_PenyaManager__TableReservationView.data,
      qt_meta_data_PenyaManager__TableReservationView,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *PenyaManager::TableReservationView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PenyaManager::TableReservationView::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_PenyaManager__TableReservationView.stringdata0))
        return static_cast<void*>(const_cast< TableReservationView*>(this));
    return IPartner::qt_metacast(_clname);
}

int PenyaManager::TableReservationView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = IPartner::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
