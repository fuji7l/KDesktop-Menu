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
#ifndef __MENU_DESKTOP_H__
#define __MENU_DESKTOP_H__

#include <kpanelmenu.h>

#include <qintdict.h>
class MenuClient;
class KBookmarkMenu;
class KActionCollection;
class KBookmarkOwner;
typedef QPtrList<QPopupMenu> PopupMenuList;
class MenuDesktop : public KPanelMenu
{
	Q_OBJECT

public:
	MenuDesktop();
	~MenuDesktop();
	static QPopupMenu *reduceMenu(QPopupMenu *);

public slots:
	void initialize();

protected slots:
	void slotOpenHomeFolder();
	void slotOpenDocsFolder();
	void slotOpenTrashSlave();
	void slotConfigChanged();
	void slotExec(int) {}
private:
	void insertDynamicMenu(const QString& menuFile);

	KBookmarkMenu           *bookmarkMenu;
	KActionCollection       *actionCollection;
	KBookmarkOwner          *bookmarkOwner;
	PopupMenuList  m_subMenus;
	QIntDict<MenuClient>  clients;
};


class PanelQuickBrowser : public KPanelMenu
{
	Q_OBJECT

public:
	PanelQuickBrowser(QWidget *parent=0, const char *name=0);

public slots:
	void initialize();

protected slots:
	void slotExec(int) {}
};
#endif
