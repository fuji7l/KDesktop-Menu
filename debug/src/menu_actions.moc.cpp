/****************************************************************************
** MenuActions meta object code from reading C++ file 'menu_actions.h'
**
** Created: Sun Jul 9 18:21:01 2006
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.3.6   edited Mar 8 17:43 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "../../src/menu_actions.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *MenuActions::className() const
{
    return "MenuActions";
}

QMetaObject *MenuActions::metaObj = 0;
static QMetaObjectCleanUp cleanUp_MenuActions( "MenuActions", &MenuActions::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString MenuActions::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "MenuActions", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString MenuActions::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "MenuActions", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* MenuActions::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = KPanelMenu::staticMetaObject();
    static const QUMethod slot_0 = {"initialize", 0, 0 };
    static const QUMethod slot_1 = {"slotLock", 0, 0 };
    static const QUMethod slot_2 = {"slotLogout", 0, 0 };
    static const QUMethod slot_3 = {"slotPopulateSessions", 0, 0 };
    static const QUParameter param_slot_4[] = {
	{ 0, &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_4 = {"slotSessionActivated", 1, param_slot_4 };
    static const QUMethod slot_5 = {"slotSaveSession", 0, 0 };
    static const QUParameter param_slot_6[] = {
	{ 0, &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_6 = {"slotExec", 1, param_slot_6 };
    static const QMetaData slot_tbl[] = {
	{ "initialize()", &slot_0, QMetaData::Public },
	{ "slotLock()", &slot_1, QMetaData::Protected },
	{ "slotLogout()", &slot_2, QMetaData::Protected },
	{ "slotPopulateSessions()", &slot_3, QMetaData::Protected },
	{ "slotSessionActivated(int)", &slot_4, QMetaData::Protected },
	{ "slotSaveSession()", &slot_5, QMetaData::Protected },
	{ "slotExec(int)", &slot_6, QMetaData::Protected }
    };
    metaObj = QMetaObject::new_metaobject(
	"MenuActions", parentObject,
	slot_tbl, 7,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_MenuActions.setMetaObject( metaObj );
    return metaObj;
}

void* MenuActions::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "MenuActions" ) )
	return this;
    return KPanelMenu::qt_cast( clname );
}

bool MenuActions::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: initialize(); break;
    case 1: slotLock(); break;
    case 2: slotLogout(); break;
    case 3: slotPopulateSessions(); break;
    case 4: slotSessionActivated((int)static_QUType_int.get(_o+1)); break;
    case 5: slotSaveSession(); break;
    case 6: slotExec((int)static_QUType_int.get(_o+1)); break;
    default:
	return KPanelMenu::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool MenuActions::qt_emit( int _id, QUObject* _o )
{
    return KPanelMenu::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool MenuActions::qt_property( int id, int f, QVariant* v)
{
    return KPanelMenu::qt_property( id, f, v);
}

bool MenuActions::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
