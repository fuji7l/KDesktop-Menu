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
#include <qpixmap.h>

#include <kapplication.h>
#include <kdebug.h>
#include <dcopclient.h>

#include "menu_client.h"

MenuClient::MenuClient( QWidget * parent, const char *name )
    : QPopupMenu( parent, name), DCOPObject( name )
{
}

MenuClient::~MenuClient()
{
}

void MenuClient::clear()
{
    QPopupMenu::clear();
}

void MenuClient::insertItem( QPixmap icon, QString text, int id )
{
    int globalid = QPopupMenu::insertItem( icon, text, this,
                                           SLOT( slotActivated(int) ) );
    setItemParameter( globalid, id );
}

void MenuClient::insertItem( QString text, int id )
{
    int globalid = QPopupMenu::insertItem( text, this,
                                           SLOT( slotActivated(int) ) );
    setItemParameter( globalid, id );
}

QCString MenuClient::insertMenu( QPixmap icon, QString text, int id )
{
    QString subname("%1-submenu%2");
    QCString subid = subname.arg(objId()).arg(id).local8Bit();
    MenuClient *sub = new MenuClient(this, subid);
    int globalid = QPopupMenu::insertItem( icon, text, sub, id);
    setItemParameter( globalid, id );

    return subid;
}









































