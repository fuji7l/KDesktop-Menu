/***************************************************************************
 *   Copyright (C) 2005 by Richard Fujimoto   *
 *   rfujimoto@imap.cc   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#include <stdlib.h>

#include <qdir.h>
#include <qimage.h>
#include <qpainter.h>
#include <qstyle.h>

#include <kconfig.h>
#include <kapplication.h>
#include <kbookmarkmenu.h>
#include <kglobalsettings.h>
#include <kiconloader.h>
#include <kipc.h>
#include <klocale.h>
#include <kdesktopfile.h>
#include <konqbookmarkmanager.h>
#include <krun.h>
#include <kservice.h>
#include <kstandarddirs.h>
#include <kurl.h>

#include "menu_desktop.h"
#include "menu_media.h"
#include "browser_mnu.h"
#include "kicker_settings.h"
#include "menu_client.h"
#include "menuinfo.h"

MenuDesktop::MenuDesktop()
     : KPanelMenu( QString::null, 0, "Desktop" )
     , bookmarkMenu(0)
     , bookmarkOwner(0)
{
	// Don't automatically clear the main menu.
	disableAutoClear();
	actionCollection = new KActionCollection(this);
	setCaption(i18n("Desktop Menu"));

	// Some Global Setting has changed
	kapp->addKipcEventMask(KIPC::SettingsChanged);
	connect( kapp, SIGNAL(settingsChanged(int)),
	         this, SLOT(slotConfigChanged()) );
}

MenuDesktop::~MenuDesktop()
{
	delete bookmarkMenu;
	bookmarkMenu = 0;
	delete bookmarkOwner;
	bookmarkOwner = 0;
}

void MenuDesktop::initialize()
{
	if (initialized())
		return;
	kdDebug() << "MenuDesktop::initialize(); " << endl;

	if (KickerSettings::menuEntryHeight() > -1)
	{
		insertItem( SmallIconSet( "folder_home",
		                           KickerSettings::menuEntryHeight() ),
		            i18n("Home Folder"), this, SLOT(slotOpenHomeFolder()) );

		insertItem( SmallIconSet( "folder_txt",
		                          KickerSettings::menuEntryHeight() ),
		            i18n("Documents"), this, SLOT(slotOpenDocsFolder()) );
	}
	else
	{
		insertItem( i18n("Home Folder"), this, SLOT(slotOpenHomeFolder()) );
		insertItem( i18n("Documents"), this, SLOT(slotOpenDocsFolder()) );
	}
	
	//BEGIN quickbrowser
	if (KickerSettings::useBrowser())
	{
		PanelQuickBrowser *browserMnu = new PanelQuickBrowser(this);
		browserMnu->initialize();
	
		if (KickerSettings::menuEntryHeight() > -1)
		{
			insertItem( SmallIconSet( "kdisknav",
			                          KickerSettings::menuEntryHeight()),
			            i18n("Quick Browser"), reduceMenu(browserMnu));
		}
		else
		{
			insertItem( i18n("Quick Browser"), reduceMenu( browserMnu ));
		}
	
		m_subMenus.append( browserMnu );
	}

    //BEGIN trash I/O slave menu item
//     QString kiotrash = locate("lib", QString::fromLatin1("kde3/kio_trash.la") );
//
//     if ( kiotrash.isNull() || kiotrash.isEmpty() )
//     {
//         kdDebug() << "Could not locate kio_trash, is it installed?" << endl;
//     }
//     else
//     {
//         if ( KickerSettings::menuEntryHeight() > -1 )
//         {
//             insertItem( SmallIconSet( "trashcan_empty",
//                                       KickerSettings::menuEntryHeight() ),
//                         i18n("Trash"), this, SLOT(slotOpenTrashSlave()) );
//         }
//         else
//         {
//             insertItem( i18n("Trash"), this, SLOT(slotOpenTrashSlave()) );
//         }
//     }

	//BEGIN media I/O slave menu item
	
	QString kiomedia = locate("lib", QString::fromLatin1("kde3/kio_media.la") );
	
	if ( kiomedia.isNull() || kiomedia.isEmpty() )
	{
		kdDebug() << "Could not locate kio_media, is it installed?" << endl;
	}
	else
	{
		insertSeparator();
		if (KickerSettings::menuEntryHeight() > -1)
		{
			insertItem(SmallIconSet("system",KickerSettings::menuEntryHeight()),
			           i18n("Storage Media"), new MenuMedia() );
		}
		else
		{
			insertItem( i18n("Storage Media"),new MenuMedia() );
		}
	}
	kiomedia = QString();

	insertSeparator();
	if (!KickerSettings::menuExtensions().grep("remotemenu.desktop").isEmpty())
	{
		insertDynamicMenu("remotemenu.desktop");
	}

	//BEGIN inserting bookmarks
	if (KickerSettings::useBookmarks() && kapp->authorizeKAction("bookmarks"))
	{
		// Need to create a new popup each time, deleted by subMenus.clear()
		KPopupMenu * bookmarkParent = new KPopupMenu( this, "bookmarks" );
		if(!bookmarkOwner)
			bookmarkOwner = new KBookmarkOwner;
		delete bookmarkMenu; // can't reuse old one, the popup has been deleted
		bookmarkMenu = new KBookmarkMenu( KonqBookmarkManager::self(),
		                                  bookmarkOwner,
		                                  bookmarkParent,
		                                  actionCollection, true, false );

		if (KickerSettings::menuEntryHeight() > -1)
		{
			insertItem( SmallIconSet("bookmark",
			            KickerSettings::menuEntryHeight()),
			            i18n("Bookmarks"), bookmarkParent );
		}
		else
		{
			insertItem( i18n("Bookmarks"), bookmarkParent);
		}
		m_subMenus.append(bookmarkParent);
	}

	setInitialized(true);
}

void MenuDesktop::insertDynamicMenu(const QString& menuFile)
{
	MenuInfo info(menuFile);

	if (!info.isValid())
		return;

	KPanelMenu *menu = info.load();
	if (menu)
	{
		if (KickerSettings::menuEntryHeight() > -1)
		{
			insertItem( SmallIconSet(info.icon(),
			            KickerSettings::menuEntryHeight()),info.name(), menu );
		}
		else
		{
			insertItem(info.name(), menu);
		}
		m_subMenus.append(menu);
	}

	if (clients.count() > 0)
	{
		QIntDictIterator<MenuClient> it(clients);
		while (it)
		{
			if (it.current()->text.at(0) != '.')
				insertItem(it.current()->icon, it.current()->text, it.current(),
				           it.currentKey());
			++it;
		}
	}
}

QPopupMenu *MenuDesktop::reduceMenu(QPopupMenu *menu)
{
	if (menu->count() != 1)
		return menu;

	QMenuItem *item = menu->findItem(menu->idAt(0));
	if (item->popup())
		return reduceMenu(item->popup());
	
	return menu;
}


void MenuDesktop::slotOpenTrashSlave()
{
	new KRun("trash:/");
}

void MenuDesktop::slotOpenDocsFolder()
{
	new KRun( KGlobalSettings::documentPath() );
}

void MenuDesktop::slotOpenHomeFolder()
{
	KService::Ptr service = KService::serviceByDesktopName(
	                                             QString::fromLatin1("Home") );
	if (! service)
	{
		new KRun( getenv("HOME") );
	}
	else
	{
		KApplication::startServiceByDesktopName( service->name(), QStringList(),
		                                         0, 0, 0, "", true );
	}
}

void MenuDesktop::slotConfigChanged()
{
	setInitialized( false );
}

PanelQuickBrowser::PanelQuickBrowser( QWidget *parent, const char *name )
    : KPanelMenu("", parent, name)
{
}

void PanelQuickBrowser::initialize()
{
	if(initialized())
	{
		return;
	}

	setInitialized(true);

	KURL url;

	url.setPath(QDir::homeDirPath());
	if (kapp->authorizeURLAction("list", KURL(), url))
	{
		insertItem( SmallIcon("kfm_home"), i18n("&Home Folder"),
					new PanelBrowserMenu(url.path(), this) );
	}

	url.setPath(QDir::rootDirPath());
	if (kapp->authorizeURLAction("list", KURL(), url))
	{
		insertItem( SmallIcon("folder_red"), i18n("&Root Folder"),
		            new PanelBrowserMenu(url.path(), this) );
	}

	url.setPath(QDir::rootDirPath() + "etc");
	if (kapp->authorizeURLAction("list", KURL(), url))
	{
		insertItem( SmallIcon("folder_yellow"), i18n("System &Configuration"),
		            new PanelBrowserMenu(url.path(), this) );
	}
}

