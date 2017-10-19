/****************************************************************************
** Meta object code from reading C++ file 'accountbalanceview.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../penyamanager/admin/accountbalanceview.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'accountbalanceview.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_PenyaManager__AccountBalanceView_t {
    QByteArrayData data[6];
    char stringdata0[149];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PenyaManager__AccountBalanceView_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PenyaManager__AccountBalanceView_t qt_meta_stringdata_PenyaManager__AccountBalanceView = {
    {
QT_MOC_LITERAL(0, 0, 32), // "PenyaManager::AccountBalanceView"
QT_MOC_LITERAL(1, 33, 27), // "on_searchPushButton_clicked"
QT_MOC_LITERAL(2, 61, 0), // ""
QT_MOC_LITERAL(3, 62, 29), // "on_prevPagePushButton_clicked"
QT_MOC_LITERAL(4, 92, 29), // "on_nextPagePushButton_clicked"
QT_MOC_LITERAL(5, 122, 26) // "on_clearPushButton_clicked"

    },
    "PenyaManager::AccountBalanceView\0"
    "on_searchPushButton_clicked\0\0"
    "on_prevPagePushButton_clicked\0"
    "on_nextPagePushButton_clicked\0"
    "on_clearPushButton_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PenyaManager__AccountBalanceView[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x08 /* Private */,
       3,    0,   35,    2, 0x08 /* Private */,
       4,    0,   36,    2, 0x08 /* Private */,
       5,    0,   37,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void PenyaManager::AccountBalanceView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        AccountBalanceView *_t = static_cast<AccountBalanceView *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_searchPushButton_clicked(); break;
        case 1: _t->on_prevPagePushButton_clicked(); break;
        case 2: _t->on_nextPagePushButton_clicked(); break;
        case 3: _t->on_clearPushButton_clicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject PenyaManager::AccountBalanceView::staticMetaObject = {
    { &IPartner::staticMetaObject, qt_meta_stringdata_PenyaManager__AccountBalanceView.data,
      qt_meta_data_PenyaManager__AccountBalanceView,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *PenyaManager::AccountBalanceView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PenyaManager::AccountBalanceView::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_PenyaManager__AccountBalanceView.stringdata0))
        return static_cast<void*>(const_cast< AccountBalanceView*>(this));
    return IPartner::qt_metacast(_clname);
}

int PenyaManager::AccountBalanceView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = IPartner::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
