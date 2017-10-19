/****************************************************************************
** Meta object code from reading C++ file 'productexpensesview.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../penyamanager/admin/productexpensesview.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'productexpensesview.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_PenyaManager__ProductExpensesView_t {
    QByteArrayData data[7];
    char stringdata0[175];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PenyaManager__ProductExpensesView_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PenyaManager__ProductExpensesView_t qt_meta_stringdata_PenyaManager__ProductExpensesView = {
    {
QT_MOC_LITERAL(0, 0, 33), // "PenyaManager::ProductExpenses..."
QT_MOC_LITERAL(1, 34, 26), // "on_clearPushButton_clicked"
QT_MOC_LITERAL(2, 61, 0), // ""
QT_MOC_LITERAL(3, 62, 29), // "on_prevPagePushButton_clicked"
QT_MOC_LITERAL(4, 92, 29), // "on_nextPagePushButton_clicked"
QT_MOC_LITERAL(5, 122, 27), // "on_searchPushButton_clicked"
QT_MOC_LITERAL(6, 150, 24) // "on_csvPushButton_clicked"

    },
    "PenyaManager::ProductExpensesView\0"
    "on_clearPushButton_clicked\0\0"
    "on_prevPagePushButton_clicked\0"
    "on_nextPagePushButton_clicked\0"
    "on_searchPushButton_clicked\0"
    "on_csvPushButton_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PenyaManager__ProductExpensesView[] = {

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
       6,    0,   43,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void PenyaManager::ProductExpensesView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ProductExpensesView *_t = static_cast<ProductExpensesView *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_clearPushButton_clicked(); break;
        case 1: _t->on_prevPagePushButton_clicked(); break;
        case 2: _t->on_nextPagePushButton_clicked(); break;
        case 3: _t->on_searchPushButton_clicked(); break;
        case 4: _t->on_csvPushButton_clicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject PenyaManager::ProductExpensesView::staticMetaObject = {
    { &IPartner::staticMetaObject, qt_meta_stringdata_PenyaManager__ProductExpensesView.data,
      qt_meta_data_PenyaManager__ProductExpensesView,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *PenyaManager::ProductExpensesView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PenyaManager::ProductExpensesView::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_PenyaManager__ProductExpensesView.stringdata0))
        return static_cast<void*>(const_cast< ProductExpensesView*>(this));
    return IPartner::qt_metacast(_clname);
}

int PenyaManager::ProductExpensesView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
