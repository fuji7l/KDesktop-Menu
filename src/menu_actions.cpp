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

#include <qdir.h>
#include <qfile.h>
#include <dcopclient.h>
#include <kapplication.h>
#include <kiconloader.h>
#include <klocale.h>
#include <kmessagebox.h>

#include "dmctl.h"
#include "menu_actions.h"
#include "kicker_settings.h"
#include "menu_client.h"
#include "menuinfo.h"

MenuActions::MenuActions()
     : KPanelMenu( QString::null, 0, "Actions" )
     , m_sessionsMenu( 0 )
{
    disableAutoClear();
    setCaption(i18n("Actions Menu"));
}

MenuActions::~MenuActions()
{
    delete m_sessionsMenu;
    m_sessionsMenu = 0;
}

void MenuActions::initialize()
{
    bool need_separator = false;
    QStringList menu_ext = KickerSettings::menuExtensions();
    if (!menu_ext.isEmpty())
    {
        if (!menu_ext.grep("prefmenu.desktop").isEmpty())
        {
            //moves the Configuration menu to the top because that's where I
            //think it belongs.
            menu_ext.remove("prefmenu.desktop");
            insertDynamicMenu("prefmenu.desktop");
            insertSeparator();
        }

        if (!menu_ext.grep("remotemenu.desktop").isEmpty())
        {
            //removed here because we use it in menu_desktop.cpp
            menu_ext.remove("remotemenu.desktop");
        }

        for (QStringList::ConstIterator it=menu_ext.begin(); it!=menu_ext.end(); ++it)
        {
            insertDynamicMenu(*it);
            need_separator = true;
        }
    }

    if (need_separator)
        insertSeparator();

    // insert client menus, if any
    if (clients.count() > 0)
    {
        QIntDictIterator<MenuClient> it(clients);
        while (it)
        {
            if (it.current()->text.at(0) != '.')
                insertItem(
                    it.current()->icon,
                    it.current()->text,
                    it.current(),
                    it.currentKey()
                    );
            ++it;
        }
        insertSeparator();
    }

    if (DM().isSwitchable())
    {
        if (!need_separator)
            insertSeparator();

        m_sessionsMenu = new QPopupMenu(this);

        if (KickerSettings::menuEntryHeight() > -1)
        {

            QString faceIcon = QString("%1/.face.icon").arg(QDir::homeDirPath());
            if (QFile::exists(faceIcon) == true)
            {
                insertItem(SmallIconSet(faceIcon, KickerSettings::menuEntryHeight()),
                           i18n("Switch User"),
                           m_sessionsMenu);
            }
            else
            {
                insertItem(SmallIconSet("switchuser",
                           KickerSettings::menuEntryHeight()),
                           i18n("Switch User"),
                           m_sessionsMenu);
            }
        }
        else
        {
            insertItem(i18n("Switch User"), m_sessionsMenu);
        }

        connect( m_sessionsMenu, SIGNAL(aboutToShow()),
                 SLOT(slotPopulateSessions()) );
        connect( m_sessionsMenu, SIGNAL(activated(int)),
                 SLOT(slotSessionActivated(int)) );
    }

    insertSeparator();

    KConfig ksmserver("ksmserverrc", false, false);
    ksmserver.setGroup("General");

    if (ksmserver.readEntry("loginMode") == "restoreSavedSession")
    {
        if (KickerSettings::menuEntryHeight() > -1)
        {
            insertItem(SmallIconSet("filesave", KickerSettings::menuEntryHeight()),
                       i18n("Save Session"),
                       this,
                       SLOT(slotSaveSession())
                      );
        }
        else
        {
            insertItem(i18n("Save Session"), this, SLOT(slotSaveSession()));
        }
    }

    if (kapp->authorize("lock_session"))
    {
        if (KickerSettings::menuEntryHeight() > -1)
        {
            insertItem(SmallIconSet("lock", KickerSettings::menuEntryHeight()),
                       i18n("Lock Session"),
                       this,
                       SLOT(slotLock())
                      );
        }
        else
        {
            insertItem(i18n("Lock Session"), this, SLOT(slotLock()));
        }
    }

    if (kapp->authorize("logout"))
    {
        if (KickerSettings::menuEntryHeight() > -1)
        {
            insertItem(SmallIconSet("exit", KickerSettings::menuEntryHeight()),
                       i18n("Log Out..."),
                       this,
                       SLOT(slotLogout())
                      );
        }
        else
        {
            insertItem(i18n("Log Out..."), this, SLOT(slotLogout()));
        }
    }
    setInitialized( true );
}


void MenuActions::insertDynamicMenu(const QString& menuFile)
{
    MenuInfo info(menuFile);

    if (!info.isValid())
        return;

    KPanelMenu *menu = info.load();
    if (menu)
    {
        if (KickerSettings::menuEntryHeight() > -1)
        {
            insertItem(SmallIconSet(info.icon(),
                       KickerSettings::menuEntryHeight()),
                       info.name(),
                       menu
                      );
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
                insertItem(it.current()->icon, it.current()->text,
                           it.current(), it.currentKey());
            ++it;
        }
    }
}

void MenuActions::slotLock()
{
    QCString appname("kdesktop");
    kapp->dcopClient()->send(appname, "KScreensaverIface", "lock()", "");
}

void MenuActions::slotLogout()
{
    kapp->requestShutDown();
}

void MenuActions::slotPopulateSessions()
{
    int p = 0;
    DM dm;

    m_sessionsMenu->clear();

    if (kapp->authorize("start_new_session") && (p = dm.numReserve()) >= 0)
    {
        if (kapp->authorize("lock_screen"))
            m_sessionsMenu->insertItem( /*SmallIconSet("lockfork"),*/
                                      i18n("Lock Current && Start New Session"),
                                     100);

        m_sessionsMenu->insertItem( SmallIconSet("fork"),
                                  i18n("Start New Session"),
                                  101);

        if (!p)
        {
            m_sessionsMenu->setItemEnabled(100, false);
            m_sessionsMenu->setItemEnabled(101, false);
        }
        m_sessionsMenu->insertSeparator();
    }
    SessList sess;

    if (dm.localSessions(sess))
    {
        for (SessList::ConstIterator it = sess.begin(); it != sess.end(); ++it)
        {
            //int id = m_sessionsMenu->insertItem(DM::sess2Str(*it), (*it).vt);
            DM::sess2Str(*it);
            int id = m_sessionsMenu->insertItem(i18n("%1 - CTRL+ALT+%2").arg((*it).user).arg((*it).vt), (*it).vt);
            if (!(*it).vt)
                m_sessionsMenu->setItemEnabled(id,false);
            if (!(*it).self)
                m_sessionsMenu->setItemChecked(id,false);
        }
    }
}

void MenuActions::slotSessionActivated(int ent)
{
    if (ent == 100)
    {
        doNewSession(true);
    }
    else if (ent == 101)
    {
        doNewSession(false);
    }
    else if (!m_sessionsMenu->isItemChecked(ent))
    {
        DM().lockSwitchVT(ent);
    }
}

void MenuActions::doNewSession( bool lock )
{
    int result = KMessageBox::warningContinueCancel(
        kapp->desktop()->screen(kapp->desktop()->screenNumber(this)),
        i18n("<p>You have chosen to open another desktop session.<br>"
              "The current session will be hidden "
              "and a new login screen will be displayed.<br>"
              "An F-key is assigned to each session; "
              "F%1 is usually assigned to the first session, "
              "F%2 to the second session and so on. "
              "You can switch between sessions by pressing "
              "Ctrl, Alt and the appropriate F-key at the same time. "
              "Additionally, the KDE Panel and Desktop menus have "
              "actions for switching between sessions.</p>")
                          .arg(7).arg(8),
        i18n("Warning - New Session"),
        KGuiItem(i18n("&Start New Session"), "fork"),
                 ":confirmNewSession",
                 KMessageBox::PlainCaption | KMessageBox::Notify);

    if (result==KMessageBox::Cancel)
        return;

    if (lock)
        slotLock();

    DM().startReserve();
}

void MenuActions::slotSaveSession()
{
    QByteArray data;
    kapp->dcopClient()->send( "ksmserver", "default",
                              "saveCurrentSession()", data );
}
