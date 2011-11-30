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
#ifndef __MENU_ACTIONS_H__
#define __MENU_ACTIONS_H__

#include <kpanelmenu.h>
#include <qintdict.h>

class MenuClient;

typedef QPtrList<QPopupMenu> PopupMenuList;

class MenuActions : public KPanelMenu
{
    Q_OBJECT

public:
    MenuActions();
    ~MenuActions();


public slots:
    void initialize();

protected slots:
    void slotLock();
    void slotLogout();
    void slotPopulateSessions();
    void slotSessionActivated(int);
    void slotSaveSession();
    void slotExec(int) {}

protected:
    void insertDynamicMenu(const QString& menuFile);
    void doNewSession( bool lock );

private:
    QPopupMenu              *m_sessionsMenu;
    QIntDict<MenuClient>    clients;
    PopupMenuList           m_subMenus;
};

#endif
