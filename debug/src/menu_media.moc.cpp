/****************************************************************************
** MenuMedia meta object code from reading C++ file 'menu_media.h'
**
** Created: Sun Jul 9 18:21:03 2006
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.3.6   edited Mar 8 17:43 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "../../src/menu_media.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *MenuMedia::className() const
{
    return "MenuMedia";
}

QMetaObject *MenuMedia::metaObj = 0;
static QMetaObjectCleanUp cleanUp_MenuMedia( "MenuMedia", &MenuMedia::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString MenuMedia::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "MenuMedia", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString MenuMedia::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "MenuMedia", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* MenuMedia::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = KPanelMenu::staticMetaObject();
    static const QUMethod slot_0 = {"initialize", 0, 0 };
    static const QUMethod slot_1 = {"slotOpenMediaSlave", 0, 0 };
    static const QUParameter param_slot_2[] = {
	{ "fileItem", &static_QUType_ptr, "KFileItem", QUParameter::InOut }
    };
    static const QUMethod slot_2 = {"slotOpen", 1, param_slot_2 };
    static const QUMethod slot_3 = {"slotClear", 0, 0 };
    static const QUParameter param_slot_4[] = {
	{ "url", &static_QUType_ptr, "KURL", QUParameter::In }
    };
    static const QUMethod slot_4 = {"slotStarted", 1, param_slot_4 };
    static const QUMethod slot_5 = {"slotCompleted", 0, 0 };
    static const QUParameter param_slot_6[] = {
	{ "entries", &static_QUType_ptr, "KFileItemList", QUParameter::In }
    };
    static const QUMethod slot_6 = {"slotNewItems", 1, param_slot_6 };
    static const QUParameter param_slot_7[] = {
	{ "fileItem", &static_QUType_ptr, "KFileItem", QUParameter::In }
    };
    static const QUMethod slot_7 = {"slotDeleteItem", 1, param_slot_7 };
    static const QUParameter param_slot_8[] = {
	{ "entries", &static_QUType_ptr, "KFileItemList", QUParameter::In }
    };
    static const QUMethod slot_8 = {"slotRefreshItems", 1, param_slot_8 };
    static const QUParameter param_slot_9[] = {
	{ "id", &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_9 = {"slotExec", 1, param_slot_9 };
    static const QMetaData slot_tbl[] = {
	{ "initialize()", &slot_0, QMetaData::Public },
	{ "slotOpenMediaSlave()", &slot_1, QMetaData::Protected },
	{ "slotOpen(KFileItem&)", &slot_2, QMetaData::Protected },
	{ "slotClear()", &slot_3, QMetaData::Protected },
	{ "slotStarted(const KURL&)", &slot_4, QMetaData::Protected },
	{ "slotCompleted()", &slot_5, QMetaData::Protected },
	{ "slotNewItems(const KFileItemList&)", &slot_6, QMetaData::Protected },
	{ "slotDeleteItem(KFileItem*)", &slot_7, QMetaData::Protected },
	{ "slotRefreshItems(const KFileItemList&)", &slot_8, QMetaData::Protected },
	{ "slotExec(int)", &slot_9, QMetaData::Protected }
    };
    metaObj = QMetaObject::new_metaobject(
	"MenuMedia", parentObject,
	slot_tbl, 10,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_MenuMedia.setMetaObject( metaObj );
    return metaObj;
}

void* MenuMedia::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "MenuMedia" ) )
	return this;
    return KPanelMenu::qt_cast( clname );
}

bool MenuMedia::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: initialize(); break;
    case 1: slotOpenMediaSlave(); break;
    case 2: slotOpen((KFileItem&)*((KFileItem*)static_QUType_ptr.get(_o+1))); break;
    case 3: slotClear(); break;
    case 4: slotStarted((const KURL&)*((const KURL*)static_QUType_ptr.get(_o+1))); break;
    case 5: slotCompleted(); break;
    case 6: slotNewItems((const KFileItemList&)*((const KFileItemList*)static_QUType_ptr.get(_o+1))); break;
    case 7: slotDeleteItem((KFileItem*)static_QUType_ptr.get(_o+1)); break;
    case 8: slotRefreshItems((const KFileItemList&)*((const KFileItemList*)static_QUType_ptr.get(_o+1))); break;
    case 9: slotExec((int)static_QUType_int.get(_o+1)); break;
    default:
	return KPanelMenu::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool MenuMedia::qt_emit( int _id, QUObject* _o )
{
    return KPanelMenu::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool MenuMedia::qt_property( int id, int f, QVariant* v)
{
    return KPanelMenu::qt_property( id, f, v);
}

bool MenuMedia::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
