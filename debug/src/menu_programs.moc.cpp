/****************************************************************************
** MenuPrograms meta object code from reading C++ file 'menu_programs.h'
**
** Created: Sun Jul 9 18:20:55 2006
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.3.6   edited Mar 8 17:43 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "../../src/menu_programs.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *MenuPrograms::className() const
{
    return "MenuPrograms";
}

QMetaObject *MenuPrograms::metaObj = 0;
static QMetaObjectCleanUp cleanUp_MenuPrograms( "MenuPrograms", &MenuPrograms::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString MenuPrograms::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "MenuPrograms", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString MenuPrograms::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "MenuPrograms", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* MenuPrograms::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = MenuServices::staticMetaObject();
    static const QUMethod slot_0 = {"initialize", 0, 0 };
    static const QUParameter param_slot_1[] = {
	{ "width", &static_QUType_int, 0, QUParameter::In },
	{ "height", &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_1 = {"resize", 2, param_slot_1 };
    static const QUMethod slot_2 = {"slotConfigChanged", 0, 0 };
    static const QUMethod slot_3 = {"slotRunCommand", 0, 0 };
    static const QUMethod slot_4 = {"paletteChanged", 0, 0 };
    static const QUMethod slot_5 = {"slotLaunchEmailClient", 0, 0 };
    static const QUMethod slot_6 = {"slotLaunchBrowser", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "initialize()", &slot_0, QMetaData::Public },
	{ "resize(int,int)", &slot_1, QMetaData::Public },
	{ "slotConfigChanged()", &slot_2, QMetaData::Protected },
	{ "slotRunCommand()", &slot_3, QMetaData::Protected },
	{ "paletteChanged()", &slot_4, QMetaData::Protected },
	{ "slotLaunchEmailClient()", &slot_5, QMetaData::Protected },
	{ "slotLaunchBrowser()", &slot_6, QMetaData::Protected }
    };
    metaObj = QMetaObject::new_metaobject(
	"MenuPrograms", parentObject,
	slot_tbl, 7,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_MenuPrograms.setMetaObject( metaObj );
    return metaObj;
}

void* MenuPrograms::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "MenuPrograms" ) )
	return this;
    return MenuServices::qt_cast( clname );
}

bool MenuPrograms::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: initialize(); break;
    case 1: resize((int)static_QUType_int.get(_o+1),(int)static_QUType_int.get(_o+2)); break;
    case 2: slotConfigChanged(); break;
    case 3: slotRunCommand(); break;
    case 4: paletteChanged(); break;
    case 5: slotLaunchEmailClient(); break;
    case 6: slotLaunchBrowser(); break;
    default:
	return MenuServices::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool MenuPrograms::qt_emit( int _id, QUObject* _o )
{
    return MenuServices::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool MenuPrograms::qt_property( int id, int f, QVariant* v)
{
    return MenuServices::qt_property( id, f, v);
}

bool MenuPrograms::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
