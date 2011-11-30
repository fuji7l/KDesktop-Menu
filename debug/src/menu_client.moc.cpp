/****************************************************************************
** MenuClient meta object code from reading C++ file 'menu_client.h'
**
** Created: Sun Jul 9 18:20:59 2006
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.3.6   edited Mar 8 17:43 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "../../src/menu_client.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *MenuClient::className() const
{
    return "MenuClient";
}

QMetaObject *MenuClient::metaObj = 0;
static QMetaObjectCleanUp cleanUp_MenuClient( "MenuClient", &MenuClient::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString MenuClient::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "MenuClient", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString MenuClient::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "MenuClient", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* MenuClient::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QPopupMenu::staticMetaObject();
    metaObj = QMetaObject::new_metaobject(
	"MenuClient", parentObject,
	0, 0,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_MenuClient.setMetaObject( metaObj );
    return metaObj;
}

void* MenuClient::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "MenuClient" ) )
	return this;
    if ( !qstrcmp( clname, "DCOPObject" ) )
	return (DCOPObject*)this;
    return QPopupMenu::qt_cast( clname );
}

bool MenuClient::qt_invoke( int _id, QUObject* _o )
{
    return QPopupMenu::qt_invoke(_id,_o);
}

bool MenuClient::qt_emit( int _id, QUObject* _o )
{
    return QPopupMenu::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool MenuClient::qt_property( int id, int f, QVariant* v)
{
    return QPopupMenu::qt_property( id, f, v);
}

bool MenuClient::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
