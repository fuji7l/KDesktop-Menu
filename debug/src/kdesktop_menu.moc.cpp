/****************************************************************************
** KDesktopMenu meta object code from reading C++ file 'kdesktop_menu.h'
**
** Created: Sun Jul 9 18:20:52 2006
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.3.6   edited Mar 8 17:43 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "../../src/kdesktop_menu.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *KDesktopMenu::className() const
{
    return "KDesktopMenu";
}

QMetaObject *KDesktopMenu::metaObj = 0;
static QMetaObjectCleanUp cleanUp_KDesktopMenu( "KDesktopMenu", &KDesktopMenu::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString KDesktopMenu::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "KDesktopMenu", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString KDesktopMenu::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "KDesktopMenu", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* KDesktopMenu::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = KPanelApplet::staticMetaObject();
    static const QUParameter param_slot_0[] = {
	{ "selected", &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_0 = {"slotContextMenu", 1, param_slot_0 };
    static const QUMethod slot_1 = {"slotSettingsChanged", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "slotContextMenu(int)", &slot_0, QMetaData::Protected },
	{ "slotSettingsChanged()", &slot_1, QMetaData::Protected }
    };
    metaObj = QMetaObject::new_metaobject(
	"KDesktopMenu", parentObject,
	slot_tbl, 2,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_KDesktopMenu.setMetaObject( metaObj );
    return metaObj;
}

void* KDesktopMenu::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "KDesktopMenu" ) )
	return this;
    return KPanelApplet::qt_cast( clname );
}

bool KDesktopMenu::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: slotContextMenu((int)static_QUType_int.get(_o+1)); break;
    case 1: slotSettingsChanged(); break;
    default:
	return KPanelApplet::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool KDesktopMenu::qt_emit( int _id, QUObject* _o )
{
    return KPanelApplet::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool KDesktopMenu::qt_property( int id, int f, QVariant* v)
{
    return KPanelApplet::qt_property( id, f, v);
}

bool KDesktopMenu::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES


const char *KDesktopMenuBar::className() const
{
    return "KDesktopMenuBar";
}

QMetaObject *KDesktopMenuBar::metaObj = 0;
static QMetaObjectCleanUp cleanUp_KDesktopMenuBar( "KDesktopMenuBar", &KDesktopMenuBar::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString KDesktopMenuBar::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "KDesktopMenuBar", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString KDesktopMenuBar::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "KDesktopMenuBar", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* KDesktopMenuBar::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QMenuBar::staticMetaObject();
    metaObj = QMetaObject::new_metaobject(
	"KDesktopMenuBar", parentObject,
	0, 0,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_KDesktopMenuBar.setMetaObject( metaObj );
    return metaObj;
}

void* KDesktopMenuBar::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "KDesktopMenuBar" ) )
	return this;
    return QMenuBar::qt_cast( clname );
}

bool KDesktopMenuBar::qt_invoke( int _id, QUObject* _o )
{
    return QMenuBar::qt_invoke(_id,_o);
}

bool KDesktopMenuBar::qt_emit( int _id, QUObject* _o )
{
    return QMenuBar::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool KDesktopMenuBar::qt_property( int id, int f, QVariant* v)
{
    return QMenuBar::qt_property( id, f, v);
}

bool KDesktopMenuBar::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES


const char *KMenuButton::className() const
{
    return "KMenuButton";
}

QMetaObject *KMenuButton::metaObj = 0;
static QMetaObjectCleanUp cleanUp_KMenuButton( "KMenuButton", &KMenuButton::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString KMenuButton::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "KMenuButton", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString KMenuButton::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "KMenuButton", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* KMenuButton::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QButton::staticMetaObject();
    static const QUMethod slot_0 = {"slotIconChanged", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "slotIconChanged()", &slot_0, QMetaData::Protected }
    };
    metaObj = QMetaObject::new_metaobject(
	"KMenuButton", parentObject,
	slot_tbl, 1,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_KMenuButton.setMetaObject( metaObj );
    return metaObj;
}

void* KMenuButton::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "KMenuButton" ) )
	return this;
    return QButton::qt_cast( clname );
}

bool KMenuButton::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: slotIconChanged(); break;
    default:
	return QButton::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool KMenuButton::qt_emit( int _id, QUObject* _o )
{
    return QButton::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool KMenuButton::qt_property( int id, int f, QVariant* v)
{
    return QButton::qt_property( id, f, v);
}

bool KMenuButton::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
