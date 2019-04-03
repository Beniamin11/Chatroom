/****************************************************************************
** Meta object code from reading C++ file 'pmModel.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../ChatClient/head/pmModel.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'pmModel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_pmModel_t {
    QByteArrayData data[8];
    char stringdata[70];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_pmModel_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_pmModel_t qt_meta_stringdata_pmModel = {
    {
QT_MOC_LITERAL(0, 0, 7), // "pmModel"
QT_MOC_LITERAL(1, 8, 16), // "otherUserChanged"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 5), // "other"
QT_MOC_LITERAL(4, 32, 13), // "appendChanged"
QT_MOC_LITERAL(5, 46, 8), // "getAlign"
QT_MOC_LITERAL(6, 55, 5), // "index"
QT_MOC_LITERAL(7, 61, 8) // "getColor"

    },
    "pmModel\0otherUserChanged\0\0other\0"
    "appendChanged\0getAlign\0index\0getColor"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_pmModel[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x06 /* Public */,
       4,    0,   37,    2, 0x06 /* Public */,

 // methods: name, argc, parameters, tag, flags
       5,    1,   38,    2, 0x02 /* Public */,
       7,    1,   41,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void,

 // methods: parameters
    QMetaType::Bool, QMetaType::Int,    6,
    QMetaType::QString, QMetaType::Int,    6,

       0        // eod
};

void pmModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        pmModel *_t = static_cast<pmModel *>(_o);
        switch (_id) {
        case 0: _t->otherUserChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->appendChanged(); break;
        case 2: { bool _r = _t->getAlign((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 3: { QString _r = _t->getColor((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (pmModel::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&pmModel::otherUserChanged)) {
                *result = 0;
            }
        }
        {
            typedef void (pmModel::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&pmModel::appendChanged)) {
                *result = 1;
            }
        }
    }
}

const QMetaObject pmModel::staticMetaObject = {
    { &QAbstractListModel::staticMetaObject, qt_meta_stringdata_pmModel.data,
      qt_meta_data_pmModel,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *pmModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *pmModel::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_pmModel.stringdata))
        return static_cast<void*>(const_cast< pmModel*>(this));
    return QAbstractListModel::qt_metacast(_clname);
}

int pmModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAbstractListModel::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void pmModel::otherUserChanged(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void pmModel::appendChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
