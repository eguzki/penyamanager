/****************************************************************************
** Meta object code from reading C++ file 'memberlistview.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../penyamanager/admin/memberlistview.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'memberlistview.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_PenyaManager__MemberListView_t {
    QByteArrayData data[11];
    char stringdata0[273];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PenyaManager__MemberListView_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PenyaManager__MemberListView_t qt_meta_stringdata_PenyaManager__MemberListView = {
    {
QT_MOC_LITERAL(0, 0, 28), // "PenyaManager::MemberListView"
QT_MOC_LITERAL(1, 29, 30), // "on_newMemberPushButton_clicked"
QT_MOC_LITERAL(2, 60, 0), // ""
QT_MOC_LITERAL(3, 61, 29), // "on_prevPagePushButton_clicked"
QT_MOC_LITERAL(4, 91, 29), // "on_nextPagePushButton_clicked"
QT_MOC_LITERAL(5, 121, 38), // "on_memberTableWidget_cellDoub..."
QT_MOC_LITERAL(6, 160, 3), // "row"
QT_MOC_LITERAL(7, 164, 6), // "column"
QT_MOC_LITERAL(8, 171, 24), // "on_csvPushButton_clicked"
QT_MOC_LITERAL(9, 196, 36), // "on_filterPostalUsersCheckBox_..."
QT_MOC_LITERAL(10, 233, 39) // "on_printPostalMembersPushButt..."

    },
    "PenyaManager::MemberListView\0"
    "on_newMemberPushButton_clicked\0\0"
    "on_prevPagePushButton_clicked\0"
    "on_nextPagePushButton_clicked\0"
    "on_memberTableWidget_cellDoubleClicked\0"
    "row\0column\0on_csvPushButton_clicked\0"
    "on_filterPostalUsersCheckBox_clicked\0"
    "on_printPostalMembersPushButton_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PenyaManager__MemberListView[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x08 /* Private */,
       3,    0,   50,    2, 0x08 /* Private */,
       4,    0,   51,    2, 0x08 /* Private */,
       5,    2,   52,    2, 0x08 /* Private */,
       8,    0,   57,    2, 0x08 /* Private */,
       9,    0,   58,    2, 0x08 /* Private */,
      10,    0,   59,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    6,    7,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void PenyaManager::MemberListView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MemberListView *_t = static_cast<MemberListView *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_newMemberPushButton_clicked(); break;
        case 1: _t->on_prevPagePushButton_clicked(); break;
        case 2: _t->on_nextPagePushButton_clicked(); break;
        case 3: _t->on_memberTableWidget_cellDoubleClicked((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 4: _t->on_csvPushButton_clicked(); break;
        case 5: _t->on_filterPostalUsersCheckBox_clicked(); break;
        case 6: _t->on_printPostalMembersPushButton_clicked(); break;
        default: ;
        }
    }
}

const QMetaObject PenyaManager::MemberListView::staticMetaObject = {
    { &IPartner::staticMetaObject, qt_meta_stringdata_PenyaManager__MemberListView.data,
      qt_meta_data_PenyaManager__MemberListView,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *PenyaManager::MemberListView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PenyaManager::MemberListView::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_PenyaManager__MemberListView.stringdata0))
        return static_cast<void*>(const_cast< MemberListView*>(this));
    return IPartner::qt_metacast(_clname);
}

int PenyaManager::MemberListView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = IPartner::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
