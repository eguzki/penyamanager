/****************************************************************************
** Meta object code from reading C++ file 'memberview.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../penyamanager/admin/memberview.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'memberview.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_PenyaManager__MemberView_t {
    QByteArrayData data[5];
    char stringdata0[115];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PenyaManager__MemberView_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PenyaManager__MemberView_t qt_meta_stringdata_PenyaManager__MemberView = {
    {
QT_MOC_LITERAL(0, 0, 24), // "PenyaManager::MemberView"
QT_MOC_LITERAL(1, 25, 25), // "on_savePushButton_clicked"
QT_MOC_LITERAL(2, 51, 0), // ""
QT_MOC_LITERAL(3, 52, 26), // "on_imagePushButton_clicked"
QT_MOC_LITERAL(4, 79, 35) // "on_changePasswordPushButton_c..."

    },
    "PenyaManager::MemberView\0"
    "on_savePushButton_clicked\0\0"
    "on_imagePushButton_clicked\0"
    "on_changePasswordPushButton_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PenyaManager__MemberView[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   29,    2, 0x08 /* Private */,
       3,    0,   30,    2, 0x08 /* Private */,
       4,    0,   31,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void PenyaManager::MemberView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MemberView *_t = static_cast<MemberView *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_savePushButton_clicked(); break;
        case 1: _t->on_imagePushButton_clicked(); break;
        case 2: _t->on_changePasswordPushButton_clicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject PenyaManager::MemberView::staticMetaObject = {
    { &IPartner::staticMetaObject, qt_meta_stringdata_PenyaManager__MemberView.data,
      qt_meta_data_PenyaManager__MemberView,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *PenyaManager::MemberView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PenyaManager::MemberView::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_PenyaManager__MemberView.stringdata0))
        return static_cast<void*>(const_cast< MemberView*>(this));
    return IPartner::qt_metacast(_clname);
}

int PenyaManager::MemberView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = IPartner::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
