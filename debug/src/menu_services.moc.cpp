/****************************************************************************
** MenuServices meta object code from reading C++ file 'menu_services.h'
**
** Created: Sun Jul 9 18:20:54 2006
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.3.6   edited Mar 8 17:43 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "../../src/menu_services.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *MenuServices::className() const
{
    return "MenuServices";
}

QMetaObject *MenuServices::metaObj = 0;
static QMetaObjectCleanUp cleanUp_MenuServices( "MenuServices", &MenuServices::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString MenuServices::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "MenuServices", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString MenuServices::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "MenuServices", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* MenuServices::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = KPanelMenu::staticMetaObject();
    static const QUMethod slot_0 = {"slotEditMenu", 0, 0 };
    static const QUParameter param_slot_1[] = {
	{ 0, &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_1 = {"slotContextMenu", 1, param_slot_1 };
    static const QUParameter param_slot_2[] = {
	{ "id", &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_2 = {"slotExec", 1, param_slot_2 };
    static const QUMethod slot_3 = {"slotClearOnClose", 0, 0 };
    static const QUMethod slot_4 = {"slotClear", 0, 0 };
    static const QUMethod slot_5 = {"slotClose", 0, 0 };
    static const QUMethod slot_6 = {"slotDragObjectDestroyed", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "slotEditMenu()", &slot_0, QMetaData::Protected },
	{ "slotContextMenu(int)", &slot_1, QMetaData::Protected },
	{ "slotExec(int)", &slot_2, QMetaData::Protected },
	{ "slotClearOnClose()", &slot_3, QMetaData::Protected },
	{ "slotClear()", &slot_4, QMetaData::Protected },
	{ "slotClose()", &slot_5, QMetaData::Protected },
	{ "slotDragObjectDestroyed()", &slot_6, QMetaData::Protected }
    };
    metaObj = QMetaObject::new_metaobject(
	"MenuServices", parentObject,
	slot_tbl, 7,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_MenuServices.setMetaObject( metaObj );
    return metaObj;
}

void* MenuServices::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "MenuServices" ) )
	return this;
    return KPanelMenu::qt_cast( clname );
}

bool MenuServices::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: slotEditMenu(); break;
    case 1: slotContextMenu((int)static_QUType_int.get(_o+1)); break;
    case 2: slotExec((int)static_QUType_int.get(_o+1)); break;
    case 3: slotClearOnClose(); break;
    case 4: slotClear(); break;
    case 5: slotClose(); break;
    case 6: slotDragObjectDestroyed(); break;
    default:
	return KPanelMenu::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool MenuServices::qt_emit( int _id, QUObject* _o )
{
    return KPanelMenu::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool MenuServices::qt_property( int id, int f, QVariant* v)
{
    return KPanelMenu::qt_property( id, f, v);
}

bool MenuServices::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
