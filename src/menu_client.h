/***************************************************************************
 *   Copyright (c) 1996-2000 the kicker authors. See file AUTHORS.         *
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
#ifndef __MENU_CLIENT_H__
#define __MENU_CLIENT_H__

#include <qstringlist.h>
#include <qpopupmenu.h>

#include <dcopobject.h>


class MenuActions;
class MenuDesktop;

// Classes to handle client application menus. Used by PanelKButton, which
// also manages the toplevel K Button Menu.

/**
 * Small additions to QPopupMenu to contain data we need for DCop handling
 */
class MenuClient : public QPopupMenu, DCOPObject
{
    Q_OBJECT
public:
    MenuClient( QWidget *parent=0, const char *name=0);
    ~MenuClient();

    // dcop exported
    void clear();
    void insertItem( QPixmap icon, QString text, int id );
    void insertItem( QString text, int id );

    QCString insertMenu( QPixmap icon, QString test, int id );  

    QString text;
    QPixmap icon;
};

#endif
