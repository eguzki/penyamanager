/****************************************************************************
** Meta object code from reading C++ file 'loginwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../penyamanager/user/loginwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'loginwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_PenyaManager__LoginWindow_t {
    QByteArrayData data[13];
    char stringdata0[223];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PenyaManager__LoginWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PenyaManager__LoginWindow_t qt_meta_stringdata_PenyaManager__LoginWindow = {
    {
QT_MOC_LITERAL(0, 0, 25), // "PenyaManager::LoginWindow"
QT_MOC_LITERAL(1, 26, 4), // "init"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 14), // "translateTable"
QT_MOC_LITERAL(4, 47, 15), // "initializeTable"
QT_MOC_LITERAL(5, 63, 24), // "fillLastInvoiceOwnerInfo"
QT_MOC_LITERAL(6, 88, 9), // "MemberPtr"
QT_MOC_LITERAL(7, 98, 20), // "pLastInvoiceOwnerPtr"
QT_MOC_LITERAL(8, 119, 19), // "fillLastInvoiceInfo"
QT_MOC_LITERAL(9, 139, 10), // "InvoicePtr"
QT_MOC_LITERAL(10, 150, 15), // "pLastInvoicePtr"
QT_MOC_LITERAL(11, 166, 26), // "on_loginPushButton_clicked"
QT_MOC_LITERAL(12, 193, 29) // "on_languagePushButton_clicked"

    },
    "PenyaManager::LoginWindow\0init\0\0"
    "translateTable\0initializeTable\0"
    "fillLastInvoiceOwnerInfo\0MemberPtr\0"
    "pLastInvoiceOwnerPtr\0fillLastInvoiceInfo\0"
    "InvoicePtr\0pLastInvoicePtr\0"
    "on_loginPushButton_clicked\0"
    "on_languagePushButton_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PenyaManager__LoginWindow[] = {

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
       5,    1,   52,    2, 0x08 /* Private */,
       8,    1,   55,    2, 0x08 /* Private */,
      11,    0,   58,    2, 0x08 /* Private */,
      12,    0,   59,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, 0x80000000 | 9,   10,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void PenyaManager::LoginWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        LoginWindow *_t = static_cast<LoginWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->init(); break;
        case 1: _t->translateTable(); break;
        case 2: _t->initializeTable(); break;
        case 3: _t->fillLastInvoiceOwnerInfo((*reinterpret_cast< const MemberPtr(*)>(_a[1]))); break;
        case 4: _t->fillLastInvoiceInfo((*reinterpret_cast< const InvoicePtr(*)>(_a[1]))); break;
        case 5: _t->on_loginPushButton_clicked(); break;
        case 6: _t->on_languagePushButton_clicked(); break;
        default: ;
        }
    }
}

const QMetaObject PenyaManager::LoginWindow::staticMetaObject = {
    { &IPartner::staticMetaObject, qt_meta_stringdata_PenyaManager__LoginWindow.data,
      qt_meta_data_PenyaManager__LoginWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *PenyaManager::LoginWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PenyaManager::LoginWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_PenyaManager__LoginWindow.stringdata0))
        return static_cast<void*>(const_cast< LoginWindow*>(this));
    return IPartner::qt_metacast(_clname);
}

int PenyaManager::LoginWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
