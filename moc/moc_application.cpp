/****************************************************************************
** Meta object code from reading C++ file 'application.h'
**
** Created: Wed 8. Aug 21:11:59 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../application.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'application.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Application[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x05,

 // slots: signature, parameters, type, tag, flags
      27,   12,   12,   12, 0x0a,
      37,   12,   12,   12, 0x0a,
      56,   49,   12,   12, 0x0a,
      84,   78,   74,   12, 0x0a,
      99,   78,   12,   12, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Application[] = {
    "Application\0\0tooManyApps()\0Restart()\0"
    "LoadIcons()\0filter\0SortApps(QString)\0"
    "int\0index\0isChecked(int)\0changeSetting(int)\0"
};

const QMetaObject Application::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Application,
      qt_meta_data_Application, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Application::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Application::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Application::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Application))
        return static_cast<void*>(const_cast< Application*>(this));
    return QObject::qt_metacast(_clname);
}

int Application::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: tooManyApps(); break;
        case 1: Restart(); break;
        case 2: LoadIcons(); break;
        case 3: SortApps((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: { int _r = isChecked((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 5: changeSetting((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void Application::tooManyApps()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
