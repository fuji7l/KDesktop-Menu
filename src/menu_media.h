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
#ifndef __MENU_MEDIA_H__
#define __MENU_MEDIA_H__

#include <kpanelmenu.h>
#include <kdirlister.h>
#include <kurl.h>
#include <qmap.h>

typedef QMap<int, QString>  MenuItemMap;

class MenuMedia : public KPanelMenu
{
	Q_OBJECT

	public:
		MenuMedia();
		~MenuMedia();
		int mMenuId;

	public slots:
		void initialize();

	protected:
		void mediaInsertItem(KFileItem *fileitem);

	protected slots:
		void slotOpenMediaSlave();
		void slotOpen(KFileItem &fileItem);
		void slotClear();
		void slotStarted(const KURL &url);
		void slotCompleted();
		void slotNewItems(const KFileItemList &entries);
		void slotDeleteItem(KFileItem *fileItem);
		void slotRefreshItems(const KFileItemList &entries);
		void slotExec(int id);

	private:
		KDirLister	          *m_DirLister;
		QStringList            m_ExcludedTypesList;
		MenuItemMap            m_MenuItemMap;
};

#endif
