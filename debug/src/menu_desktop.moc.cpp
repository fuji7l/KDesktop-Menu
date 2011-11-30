/****************************************************************************
** MenuDesktop meta object code from reading C++ file 'menu_desktop.h'
**
** Created: Sun Jul 9 18:20:57 2006
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.3.6   edited Mar 8 17:43 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "../../src/menu_desktop.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *MenuDesktop::className() const
{
    return "MenuDesktop";
}

QMetaObject *MenuDesktop::metaObj = 0;
static QMetaObjectCleanUp cleanUp_MenuDesktop( "MenuDesktop", &MenuDesktop::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString MenuDesktop::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "MenuDesktop", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString MenuDesktop::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "MenuDesktop", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* MenuDesktop::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = KPanelMenu::staticMetaObject();
    static const QUMethod slot_0 = {"initialize", 0, 0 };
    static const QUMethod slot_1 = {"slotOpenHomeFolder", 0, 0 };
    static const QUMethod slot_2 = {"slotOpenDocsFolder", 0, 0 };
    static const QUMethod slot_3 = {"slotOpenTrashSlave", 0, 0 };
    static const QUMethod slot_4 = {"slotConfigChanged", 0, 0 };
    static const QUParameter param_slot_5[] = {
	{ 0, &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_5 = {"slotExec", 1, param_slot_5 };
    static const QMetaData slot_tbl[] = {
	{ "initialize()", &slot_0, QMetaData::Public },
	{ "slotOpenHomeFolder()", &slot_1, QMetaData::Protected },
	{ "slotOpenDocsFolder()", &slot_2, QMetaData::Protected },
	{ "slotOpenTrashSlave()", &slot_3, QMetaData::Protected },
	{ "slotConfigChanged()", &slot_4, QMetaData::Protected },
	{ "slotExec(int)", &slot_5, QMetaData::Protected }
    };
    metaObj = QMetaObject::new_metaobject(
	"MenuDesktop", parentObject,
	slot_tbl, 6,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_MenuDesktop.setMetaObject( metaObj );
    return metaObj;
}

void* MenuDesktop::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "MenuDesktop" ) )
	return this;
    return KPanelMenu::qt_cast( clname );
}

bool MenuDesktop::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: initialize(); break;
    case 1: slotOpenHomeFolder(); break;
    case 2: slotOpenDocsFolder(); break;
    case 3: slotOpenTrashSlave(); break;
    case 4: slotConfigChanged(); break;
    case 5: slotExec((int)static_QUType_int.get(_o+1)); break;
    default:
	return KPanelMenu::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool MenuDesktop::qt_emit( int _id, QUObject* _o )
{
    return KPanelMenu::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool MenuDesktop::qt_property( int id, int f, QVariant* v)
{
    return KPanelMenu::qt_property( id, f, v);
}

bool MenuDesktop::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES


const char *PanelQuickBrowser::className() const
{
    return "PanelQuickBrowser";
}

QMetaObject *PanelQuickBrowser::metaObj = 0;
static QMetaObjectCleanUp cleanUp_PanelQuickBrowser( "PanelQuickBrowser", &PanelQuickBrowser::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString PanelQuickBrowser::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "PanelQuickBrowser", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString PanelQuickBrowser::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "PanelQuickBrowser", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* PanelQuickBrowser::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = KPanelMenu::staticMetaObject();
    static const QUMethod slot_0 = {"initialize", 0, 0 };
    static const QUParameter param_slot_1[] = {
	{ 0, &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_1 = {"slotExec", 1, param_slot_1 };
    static const QMetaData slot_tbl[] = {
	{ "initialize()", &slot_0, QMetaData::Public },
	{ "slotExec(int)", &slot_1, QMetaData::Protected }
    };
    metaObj = QMetaObject::new_metaobject(
	"PanelQuickBrowser", parentObject,
	slot_tbl, 2,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_PanelQuickBrowser.setMetaObject( metaObj );
    return metaObj;
}

void* PanelQuickBrowser::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "PanelQuickBrowser" ) )
	return this;
    return KPanelMenu::qt_cast( clname );
}

bool PanelQuickBrowser::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: initialize(); break;
    case 1: slotExec((int)static_QUType_int.get(_o+1)); break;
    default:
	return KPanelMenu::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool PanelQuickBrowser::qt_emit( int _id, QUObject* _o )
{
    return KPanelMenu::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool PanelQuickBrowser::qt_property( int id, int f, QVariant* v)
{
    return KPanelMenu::qt_property( id, f, v);
}

bool PanelQuickBrowser::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
