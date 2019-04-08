/****************************************************************************
** Meta object code from reading C++ file 'chatSupervisor.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../ChatClient/head/chatSupervisor.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'chatSupervisor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ChatMainWindow_t {
    QByteArrayData data[57];
    char stringdata[629];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ChatMainWindow_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ChatMainWindow_t qt_meta_stringdata_ChatMainWindow = {
    {
QT_MOC_LITERAL(0, 0, 14), // "ChatMainWindow"
QT_MOC_LITERAL(1, 15, 15), // "nicknameChanged"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 19), // "changingUserChanged"
QT_MOC_LITERAL(4, 52, 17), // "popupTitleChanged"
QT_MOC_LITERAL(5, 70, 16), // "otherUserChanged"
QT_MOC_LITERAL(6, 87, 5), // "other"
QT_MOC_LITERAL(7, 93, 17), // "openPrivateWindow"
QT_MOC_LITERAL(8, 111, 13), // "focusPmWindow"
QT_MOC_LITERAL(9, 125, 13), // "pmSelfChanged"
QT_MOC_LITERAL(10, 139, 13), // "windowChanged"
QT_MOC_LITERAL(11, 153, 4), // "wind"
QT_MOC_LITERAL(12, 158, 16), // "mainWindowClosed"
QT_MOC_LITERAL(13, 175, 14), // "contentChanged"
QT_MOC_LITERAL(14, 190, 12), // "usersChanged"
QT_MOC_LITERAL(15, 203, 16), // "connectedChanged"
QT_MOC_LITERAL(16, 220, 17), // "textLengthChanged"
QT_MOC_LITERAL(17, 238, 11), // "setNickname"
QT_MOC_LITERAL(18, 250, 8), // "nickname"
QT_MOC_LITERAL(19, 259, 15), // "setChangingUser"
QT_MOC_LITERAL(20, 275, 5), // "state"
QT_MOC_LITERAL(21, 281, 13), // "setTextLength"
QT_MOC_LITERAL(22, 295, 3), // "len"
QT_MOC_LITERAL(23, 299, 13), // "setPopupTitle"
QT_MOC_LITERAL(24, 313, 5), // "title"
QT_MOC_LITERAL(25, 319, 12), // "setOtherUser"
QT_MOC_LITERAL(26, 332, 4), // "user"
QT_MOC_LITERAL(27, 337, 11), // "sendCommand"
QT_MOC_LITERAL(28, 349, 11), // "CommandType"
QT_MOC_LITERAL(29, 361, 4), // "code"
QT_MOC_LITERAL(30, 366, 4), // "text"
QT_MOC_LITERAL(31, 371, 9), // "readyRead"
QT_MOC_LITERAL(32, 381, 18), // "socketDisconnected"
QT_MOC_LITERAL(33, 400, 15), // "socketConnected"
QT_MOC_LITERAL(34, 416, 11), // "socketError"
QT_MOC_LITERAL(35, 428, 13), // "clientConnect"
QT_MOC_LITERAL(36, 442, 10), // "IP_address"
QT_MOC_LITERAL(37, 453, 4), // "port"
QT_MOC_LITERAL(38, 458, 9), // "reconnect"
QT_MOC_LITERAL(39, 468, 8), // "getModel"
QT_MOC_LITERAL(40, 477, 9), // "otherUser"
QT_MOC_LITERAL(41, 487, 10), // "popupTitle"
QT_MOC_LITERAL(42, 498, 9), // "connected"
QT_MOC_LITERAL(43, 508, 12), // "changingUser"
QT_MOC_LITERAL(44, 521, 6), // "pmSelf"
QT_MOC_LITERAL(45, 528, 10), // "textLength"
QT_MOC_LITERAL(46, 539, 7), // "content"
QT_MOC_LITERAL(47, 547, 5), // "users"
QT_MOC_LITERAL(48, 553, 3), // "Set"
QT_MOC_LITERAL(49, 557, 6), // "Change"
QT_MOC_LITERAL(50, 564, 9), // "CloseMain"
QT_MOC_LITERAL(51, 574, 8), // "Validate"
QT_MOC_LITERAL(52, 583, 7), // "Request"
QT_MOC_LITERAL(53, 591, 12), // "OpenPmWindow"
QT_MOC_LITERAL(54, 604, 2), // "PM"
QT_MOC_LITERAL(55, 607, 13), // "ClosePmWindow"
QT_MOC_LITERAL(56, 621, 7) // "Message"

    },
    "ChatMainWindow\0nicknameChanged\0\0"
    "changingUserChanged\0popupTitleChanged\0"
    "otherUserChanged\0other\0openPrivateWindow\0"
    "focusPmWindow\0pmSelfChanged\0windowChanged\0"
    "wind\0mainWindowClosed\0contentChanged\0"
    "usersChanged\0connectedChanged\0"
    "textLengthChanged\0setNickname\0nickname\0"
    "setChangingUser\0state\0setTextLength\0"
    "len\0setPopupTitle\0title\0setOtherUser\0"
    "user\0sendCommand\0CommandType\0code\0"
    "text\0readyRead\0socketDisconnected\0"
    "socketConnected\0socketError\0clientConnect\0"
    "IP_address\0port\0reconnect\0getModel\0"
    "otherUser\0popupTitle\0connected\0"
    "changingUser\0pmSelf\0textLength\0content\0"
    "users\0Set\0Change\0CloseMain\0Validate\0"
    "Request\0OpenPmWindow\0PM\0ClosePmWindow\0"
    "Message"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ChatMainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      26,   14, // methods
       9,  200, // properties
       1,  236, // enums/sets
       0,    0, // constructors
       0,       // flags
      13,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,  144,    2, 0x06 /* Public */,
       3,    0,  145,    2, 0x06 /* Public */,
       4,    0,  146,    2, 0x06 /* Public */,
       5,    1,  147,    2, 0x06 /* Public */,
       7,    1,  150,    2, 0x06 /* Public */,
       8,    1,  153,    2, 0x06 /* Public */,
       9,    1,  156,    2, 0x06 /* Public */,
      10,    1,  159,    2, 0x06 /* Public */,
      12,    0,  162,    2, 0x06 /* Public */,
      13,    0,  163,    2, 0x06 /* Public */,
      14,    0,  164,    2, 0x06 /* Public */,
      15,    0,  165,    2, 0x06 /* Public */,
      16,    0,  166,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      17,    1,  167,    2, 0x0a /* Public */,
      19,    1,  170,    2, 0x0a /* Public */,
      21,    1,  173,    2, 0x0a /* Public */,
      23,    1,  176,    2, 0x0a /* Public */,
      25,    1,  179,    2, 0x0a /* Public */,
      27,    2,  182,    2, 0x0a /* Public */,
      31,    0,  187,    2, 0x0a /* Public */,
      32,    0,  188,    2, 0x0a /* Public */,
      33,    0,  189,    2, 0x0a /* Public */,
      34,    0,  190,    2, 0x0a /* Public */,

 // methods: name, argc, parameters, tag, flags
      35,    2,  191,    2, 0x02 /* Public */,
      38,    0,  196,    2, 0x02 /* Public */,
      39,    1,  197,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void, QMetaType::Int,   11,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,   18,
    QMetaType::Void, QMetaType::Bool,   20,
    QMetaType::Void, QMetaType::Int,   22,
    QMetaType::Void, QMetaType::QString,   24,
    QMetaType::Void, QMetaType::QString,   26,
    QMetaType::Void, 0x80000000 | 28, QMetaType::QString,   29,   30,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // methods: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   36,   37,
    QMetaType::Void,
    QMetaType::QObjectStar, QMetaType::QString,   40,

 // properties: name, type, flags
      18, QMetaType::QString, 0x00495103,
      41, QMetaType::QString, 0x00495103,
      40, QMetaType::QString, 0x00495103,
      42, QMetaType::Bool, 0x00495001,
      43, QMetaType::Bool, 0x00495103,
      44, QMetaType::Bool, 0x00495001,
      45, QMetaType::Int, 0x00495103,
      46, QMetaType::QObjectStar, 0x00495001,
      47, QMetaType::QObjectStar, 0x00495001,

 // properties: notify_signal_id
       0,
       2,
       3,
      11,
       1,
       6,
      12,
       9,
      10,

 // enums: name, flags, count, data
      28, 0x0,    9,  240,

 // enum data: key, value
      48, uint(ChatMainWindow::Set),
      49, uint(ChatMainWindow::Change),
      50, uint(ChatMainWindow::CloseMain),
      51, uint(ChatMainWindow::Validate),
      52, uint(ChatMainWindow::Request),
      53, uint(ChatMainWindow::OpenPmWindow),
      54, uint(ChatMainWindow::PM),
      55, uint(ChatMainWindow::ClosePmWindow),
      56, uint(ChatMainWindow::Message),

       0        // eod
};

void ChatMainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ChatMainWindow *_t = static_cast<ChatMainWindow *>(_o);
        switch (_id) {
        case 0: _t->nicknameChanged(); break;
        case 1: _t->changingUserChanged(); break;
        case 2: _t->popupTitleChanged(); break;
        case 3: _t->otherUserChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->openPrivateWindow((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: _t->focusPmWindow((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: _t->pmSelfChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 7: _t->windowChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->mainWindowClosed(); break;
        case 9: _t->contentChanged(); break;
        case 10: _t->usersChanged(); break;
        case 11: _t->connectedChanged(); break;
        case 12: _t->textLengthChanged(); break;
        case 13: _t->setNickname((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 14: _t->setChangingUser((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 15: _t->setTextLength((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 16: _t->setPopupTitle((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 17: _t->setOtherUser((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 18: _t->sendCommand((*reinterpret_cast< CommandType(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 19: _t->readyRead(); break;
        case 20: _t->socketDisconnected(); break;
        case 21: _t->socketConnected(); break;
        case 22: _t->socketError(); break;
        case 23: _t->clientConnect((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 24: _t->reconnect(); break;
        case 25: { QObject* _r = _t->getModel((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QObject**>(_a[0]) = _r; }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (ChatMainWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ChatMainWindow::nicknameChanged)) {
                *result = 0;
            }
        }
        {
            typedef void (ChatMainWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ChatMainWindow::changingUserChanged)) {
                *result = 1;
            }
        }
        {
            typedef void (ChatMainWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ChatMainWindow::popupTitleChanged)) {
                *result = 2;
            }
        }
        {
            typedef void (ChatMainWindow::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ChatMainWindow::otherUserChanged)) {
                *result = 3;
            }
        }
        {
            typedef void (ChatMainWindow::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ChatMainWindow::openPrivateWindow)) {
                *result = 4;
            }
        }
        {
            typedef void (ChatMainWindow::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ChatMainWindow::focusPmWindow)) {
                *result = 5;
            }
        }
        {
            typedef void (ChatMainWindow::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ChatMainWindow::pmSelfChanged)) {
                *result = 6;
            }
        }
        {
            typedef void (ChatMainWindow::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ChatMainWindow::windowChanged)) {
                *result = 7;
            }
        }
        {
            typedef void (ChatMainWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ChatMainWindow::mainWindowClosed)) {
                *result = 8;
            }
        }
        {
            typedef void (ChatMainWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ChatMainWindow::contentChanged)) {
                *result = 9;
            }
        }
        {
            typedef void (ChatMainWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ChatMainWindow::usersChanged)) {
                *result = 10;
            }
        }
        {
            typedef void (ChatMainWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ChatMainWindow::connectedChanged)) {
                *result = 11;
            }
        }
        {
            typedef void (ChatMainWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ChatMainWindow::textLengthChanged)) {
                *result = 12;
            }
        }
    }
}

const QMetaObject ChatMainWindow::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ChatMainWindow.data,
      qt_meta_data_ChatMainWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ChatMainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ChatMainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ChatMainWindow.stringdata))
        return static_cast<void*>(const_cast< ChatMainWindow*>(this));
    return QObject::qt_metacast(_clname);
}

int ChatMainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 26)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 26;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 26)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 26;
    }
#ifndef QT_NO_PROPERTIES
      else if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QString*>(_v) = nickname(); break;
        case 1: *reinterpret_cast< QString*>(_v) = popupTitle(); break;
        case 2: *reinterpret_cast< QString*>(_v) = otherUser(); break;
        case 3: *reinterpret_cast< bool*>(_v) = connected(); break;
        case 4: *reinterpret_cast< bool*>(_v) = changingUser(); break;
        case 5: *reinterpret_cast< bool*>(_v) = pmSelf(); break;
        case 6: *reinterpret_cast< int*>(_v) = textLength(); break;
        case 7: *reinterpret_cast< QObject**>(_v) = content(); break;
        case 8: *reinterpret_cast< QObject**>(_v) = users(); break;
        default: break;
        }
        _id -= 9;
    } else if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: setNickname(*reinterpret_cast< QString*>(_v)); break;
        case 1: setPopupTitle(*reinterpret_cast< QString*>(_v)); break;
        case 2: setOtherUser(*reinterpret_cast< QString*>(_v)); break;
        case 4: setChangingUser(*reinterpret_cast< bool*>(_v)); break;
        case 6: setTextLength(*reinterpret_cast< int*>(_v)); break;
        default: break;
        }
        _id -= 9;
    } else if (_c == QMetaObject::ResetProperty) {
        _id -= 9;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 9;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 9;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 9;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 9;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 9;
    } else if (_c == QMetaObject::RegisterPropertyMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void ChatMainWindow::nicknameChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void ChatMainWindow::changingUserChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}

// SIGNAL 2
void ChatMainWindow::popupTitleChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, Q_NULLPTR);
}

// SIGNAL 3
void ChatMainWindow::otherUserChanged(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void ChatMainWindow::openPrivateWindow(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void ChatMainWindow::focusPmWindow(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void ChatMainWindow::pmSelfChanged(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void ChatMainWindow::windowChanged(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void ChatMainWindow::mainWindowClosed()
{
    QMetaObject::activate(this, &staticMetaObject, 8, Q_NULLPTR);
}

// SIGNAL 9
void ChatMainWindow::contentChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 9, Q_NULLPTR);
}

// SIGNAL 10
void ChatMainWindow::usersChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 10, Q_NULLPTR);
}

// SIGNAL 11
void ChatMainWindow::connectedChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 11, Q_NULLPTR);
}

// SIGNAL 12
void ChatMainWindow::textLengthChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 12, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
