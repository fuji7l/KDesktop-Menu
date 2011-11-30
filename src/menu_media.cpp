/***************************************************************************
 *   Copyright (C) 2005 by Richard Fujimoto                                *
 *   rfujimoto@imap.cc                                                     *
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

#include <kdebug.h>
#include <kdirlister.h>
#include <kfileitem.h>
#include <kiconloader.h>
#include <klocale.h>
#include <krun.h>
#include <kurl.h>

#include "kicker_settings.h"
#include "menu_media.h"
MenuMedia::MenuMedia()
    : KPanelMenu( QString::null, 0, "Media" ),
    mMenuId(0)
{
	disableAutoClear();
	setCaption(i18n("Media Menu"));

	m_DirLister = new KDirLister();
	connect( m_DirLister, SIGNAL( clear() ), this, SLOT( slotClear() ) );
	connect( m_DirLister, SIGNAL( started(const KURL&) ),
	         this, SLOT( slotStarted(const KURL&) ) );
	connect( m_DirLister, SIGNAL( completed() ),
	         this, SLOT( slotCompleted() ) );
	connect( m_DirLister, SIGNAL( newItems( const KFileItemList & ) ),
	         this, SLOT( slotNewItems( const KFileItemList & ) ) );
	connect( m_DirLister, SIGNAL( deleteItem( KFileItem * ) ),
	         this, SLOT( slotDeleteItem( KFileItem * ) ) );
	connect( m_DirLister, SIGNAL( refreshItems( const KFileItemList & ) ),
	         this, SLOT( slotRefreshItems( const KFileItemList & ) ) );

	m_ExcludedTypesList.clear();
	m_ExcludedTypesList << "media/hdd_mounted";
	m_ExcludedTypesList << "media/hdd_unmounted";
	m_ExcludedTypesList << "media/nfs_mounted";
	m_ExcludedTypesList << "media/nfs_unmounted";
	m_ExcludedTypesList << "media/smb_mounted";
	m_ExcludedTypesList << "media/smb_unmounted";
}

MenuMedia::~MenuMedia()
{
	if (m_DirLister)
	{
		delete m_DirLister;
		m_DirLister = 0;
	}
}

void MenuMedia::initialize()
{
	if(initialized())
	{
		return;
	}
	if (KickerSettings::menuEntryHeight() > -1)
	{
		insertItem(SmallIconSet("system",KickerSettings::menuEntryHeight()),
		           i18n("Storage Media"), this, SLOT(slotOpenMediaSlave() ));
	}
	else
	{
		insertItem( i18n("Storage Media"), this, SLOT(slotOpenMediaSlave() ));
	}

	insertSeparator();


	m_DirLister->stop();
	m_DirLister->clearMimeFilter();
	m_DirLister->setMimeExcludeFilter(m_ExcludedTypesList);
	m_DirLister->openURL(KURL("media:/"));

	setInitialized( true );
}


void MenuMedia::slotClear()
{
}

void MenuMedia::slotCompleted()
{
	setInitialized( true );
}

void MenuMedia::mediaInsertItem(KFileItem *fileItem)
{
	// reset the mMenuId Int after 100 because I don't want to see what happens
	// when the int gets too big
	if (mMenuId > 100)
		mMenuId = 0;

	//find a valid mMenuId first
	int count = 0;
	while ((m_MenuItemMap.contains(mMenuId) == true))
	{
		if (count >= 500)
		{
			kdFatal() << "Infinite Loop found, report this please" << endl;
		}
		count++;
		mMenuId++;
	}

	if (KickerSettings::menuEntryHeight() > -1)
	{
		insertItem( SmallIconSet( fileItem->iconName(),
		                          KickerSettings::menuEntryHeight()),
		            fileItem->name(),
		            mMenuId);
	}
	else
	{
		insertItem(fileItem->name(), mMenuId);
	}
	m_MenuItemMap[mMenuId] = QString(fileItem->url().url());
	mMenuId++;
}

void MenuMedia::slotExec(int id)
{
	new KRun(m_MenuItemMap[id]);
}

void MenuMedia::slotOpenMediaSlave()
{
	new KRun("media:/");
}

void MenuMedia::slotOpen(KFileItem &fileItem)
{
	fileItem.run();
}

void MenuMedia::slotNewItems(const KFileItemList &entries)
{
	for (KFileItemListIterator it(entries); it.current(); ++it)
	{
		bool found = false;

		MenuItemMap::iterator mapit;
		for (mapit = m_MenuItemMap.begin(); mapit != m_MenuItemMap.end(); ++mapit)
		{
			if (mapit.data() == (*it.current()).url().url())
			{
				// Don't insert duplicates
				found = true;
				break;
			}
		}

		if(!found)
		{
			mediaInsertItem(it.current());
			kdDebug() << "New Media item: " << it.current()->url() << endl;
		}
	}
}
void MenuMedia::slotStarted(const KURL &/*url*/)
{

}
void MenuMedia::slotDeleteItem(KFileItem *fileItem)
{
	kdDebug()<<"MenuMedia::slotDeleteItem: "<< fileItem->url() << endl;

	MenuItemMap::iterator it;
	for (it=m_MenuItemMap.begin(); it != m_MenuItemMap.end(); ++it)
	{
		if (it.data() == fileItem->url().url())
		{
			kdDebug()<<"MenuMedia::removeItem("<< it.key() << ")"<< endl;
			m_MenuItemMap.remove(it.key());
			removeItem(it.key());
			break;
		}
	}
}

void MenuMedia::slotRefreshItems(const KFileItemList &entries)
{
	for(KFileItemListIterator it(entries); it.current(); ++it)
	{
		QString mimetype = (*it.current()).mimetype();
		bool found = false;

		MenuItemMap::iterator mapit;
		for (mapit = m_MenuItemMap.begin(); mapit != m_MenuItemMap.end(); ++mapit)
		{
			if (mapit.data().latin1() == (*it.current()).url().url())
			{
				removeItem(mapit.key());
				if (!m_ExcludedTypesList.contains(mimetype))
				{
					mediaInsertItem(it.current());
					found = true;
					break;
				}
					
			}
		}

		if(!found && !m_ExcludedTypesList.contains(mimetype))
		{
			mediaInsertItem(it.current());
		}
	}
}

