/****************************************************************************
** Meta object code from reading C++ file 'familyitemmanagementwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../penyamanager/admin/familyitemmanagementwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'familyitemmanagementwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_PenyaManager__FamilyItemManagementWindow_t {
    QByteArrayData data[9];
    char stringdata0[193];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PenyaManager__FamilyItemManagementWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PenyaManager__FamilyItemManagementWindow_t qt_meta_stringdata_PenyaManager__FamilyItemManagementWindow = {
    {
QT_MOC_LITERAL(0, 0, 40), // "PenyaManager::FamilyItemManag..."
QT_MOC_LITERAL(1, 41, 28), // "on_newItemPushButton_clicked"
QT_MOC_LITERAL(2, 70, 0), // ""
QT_MOC_LITERAL(3, 71, 30), // "on_newFamilyPushButton_clicked"
QT_MOC_LITERAL(4, 102, 17), // "familyItemClicked"
QT_MOC_LITERAL(5, 120, 16), // "QListWidgetItem*"
QT_MOC_LITERAL(6, 137, 4), // "item"
QT_MOC_LITERAL(7, 142, 18), // "productItemClicked"
QT_MOC_LITERAL(8, 161, 31) // "on_editFamilyPushButton_clicked"

    },
    "PenyaManager::FamilyItemManagementWindow\0"
    "on_newItemPushButton_clicked\0\0"
    "on_newFamilyPushButton_clicked\0"
    "familyItemClicked\0QListWidgetItem*\0"
    "item\0productItemClicked\0"
    "on_editFamilyPushButton_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PenyaManager__FamilyItemManagementWindow[] = {

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
       4,    1,   41,    2, 0x08 /* Private */,
       7,    1,   44,    2, 0x08 /* Private */,
       8,    0,   47,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void,

       0        // eod
};

void PenyaManager::FamilyItemManagementWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        FamilyItemManagementWindow *_t = static_cast<FamilyItemManagementWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_newItemPushButton_clicked(); break;
        case 1: _t->on_newFamilyPushButton_clicked(); break;
        case 2: _t->familyItemClicked((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 3: _t->productItemClicked((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 4: _t->on_editFamilyPushButton_clicked(); break;
        default: ;
        }
    }
}

const QMetaObject PenyaManager::FamilyItemManagementWindow::staticMetaObject = {
    { &IPartner::staticMetaObject, qt_meta_stringdata_PenyaManager__FamilyItemManagementWindow.data,
      qt_meta_data_PenyaManager__FamilyItemManagementWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *PenyaManager::FamilyItemManagementWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PenyaManager::FamilyItemManagementWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_PenyaManager__FamilyItemManagementWindow.stringdata0))
        return static_cast<void*>(const_cast< FamilyItemManagementWindow*>(this));
    return IPartner::qt_metacast(_clname);
}

int PenyaManager::FamilyItemManagementWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
