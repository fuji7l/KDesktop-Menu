/***************************************************************************
 *   Copyright (c) 1996-2000 the kicker authors. See file AUTHORS.         *
 *   Copyright (C) 2005 by Richard Fujimoto                                *
 *   rfujimoto@imap.cc                                                     *
 *                                                                         *
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
#ifndef __MENU_SERVICES_H__
#define __MENU_SERVICES_H__

#include <qmap.h>
#include <qintdict.h>
#include <ksycocaentry.h>
#include <kservice.h>
#include <kpanelmenu.h>
//#include "menu_client.h"

typedef QMap<int, KSycocaEntry::Ptr> EntryMap;
typedef QPtrList<QPopupMenu> PopupMenuList;

//class MenuClient;
class QPoint;
class QString;

class  MenuServices : public KPanelMenu
{
    Q_OBJECT

public:
    /***
     * Constructor
     */
    MenuServices( const QString & label, const QString & relPath,
                  QWidget* parent  = 0, const char* name = 0 );
    ~MenuServices();

    QString relPath() { return m_relPath; }
    void setExcludeNoDisplay( bool flag );
    void selectFirstItem();
    void initialize();

private:
    void insertMenuItem(KService::Ptr & s, int nId, int nIndex = -1,
                        const QStringList *suppressGenericNames=0);

protected slots:
	void slotEditMenu();
    void slotContextMenu(int);
    virtual void slotExec(int id);
    virtual void slotClearOnClose();
    virtual void slotClear();
    virtual void slotClose();
    void slotDragObjectDestroyed();

protected:
    virtual MenuServices * newSubMenu( const QString & label,
                                        const QString & relPath,
                                        QWidget * parent, const char * name);

    virtual void mousePressEvent(QMouseEvent *);
    virtual void mouseReleaseEvent(QMouseEvent *);
    virtual void mouseMoveEvent(QMouseEvent *);
    virtual void dragEnterEvent(QDragEnterEvent *);
    virtual void dragLeaveEvent(QDragLeaveEvent *);
    void createMenu();

    QString        m_relPath;
    EntryMap       m_entryMap;
    bool           m_excludeNoDisplay;
    bool           m_clearOnClose;
    QPoint         m_startPos;
    PopupMenuList  m_subMenus;

private:
     enum        ContextMenuEntry { AddItemToPanel, EditItem, AddMenuToPanel,
                                    EditMenu, AddItemToDesktop, AddMenuToDesktop,
                                    PutIntoRunDialog };
    KPopupMenu*           m_popupMenu;
    KSycocaEntry*         m_contextKSycocaEntry;
//    QIntDict<MenuClient>  clients;
    int                   client_id;
};

#endif
