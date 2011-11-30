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
#include <qapplication.h>
#include <qcursor.h>

#include <dcopclient.h>
#include <kapplication.h>
#include <kdebug.h>
#include <kdesktopfile.h>
#include <kglobal.h>
#include <kiconloader.h>
#include <kio/job.h>
#include <klocale.h>
#include <kpanelmenu.h>
#include <kprocess.h>
#include <krun.h>
#include <kservice.h>
#include <kservicegroup.h>
#include <kstandarddirs.h>
#include <ksycoca.h>
#include <ksycocaentry.h>
#include <kservice.h>
#include <kurl.h>
#include <kurldrag.h>
#include <kdeversion.h>

#if KDE_VERSION >= 350
#include <kglobalsettings.h>
#endif

#include "kicker_settings.h"
#include "menu_services.h"


const int idStart = 4242;

MenuServices::MenuServices(const QString & label, const QString & relPath,
                           QWidget * parent, const char * name)
    : KPanelMenu( label, parent, name )
    , m_relPath(relPath)
    , m_clearOnClose(false)
    , m_popupMenu(0)
{
    m_subMenus.setAutoDelete(true);

    m_excludeNoDisplay=true;

    connect( KSycoca::self(), SIGNAL(databaseChanged()),
             SLOT(slotClearOnClose()));
    connect(this, SIGNAL(aboutToHide()), this, SLOT(slotClose()));
}

MenuServices::~MenuServices()
{
    m_subMenus.clear();
}

void MenuServices::initialize()
{
    if (initialized())
    {
        return;
    }

    setInitialized(true);
    m_entryMap.clear();
    clear();
    m_subMenus.clear();

    createMenu();
}

void MenuServices::createMenu()
{
	kdDebug() << "  MenuServices::createMenu()" << endl;
	m_startPos = QPoint(-1,-1);

	// We ask KSycoca to give us all services (sorted).
	KServiceGroup::Ptr root = KServiceGroup::group(m_relPath);

	if (!root || !root->isValid())
	{
		kdDebug() << "  MenuServices::createMenu() !root" << endl;
		return;
	}

	KServiceGroup::List list = root->entries(true, m_excludeNoDisplay, true,
	  KickerSettings::menuEntryFormat() == KickerSettings::DescriptionAndName ||
	  KickerSettings::menuEntryFormat() == KickerSettings::DescriptionOnly);
	
	if (list.isEmpty())
	{
		setItemEnabled(insertItem(i18n("No Entries")), false);
		return;
	}
	
	int id = idStart;
	
	QStringList suppressGenericNames = root->suppressGenericNames();
	
	KServiceGroup::List::ConstIterator it = list.begin();
	
	for (; it != list.end(); ++it)
	{
		KSycocaEntry * e = *it;
	
		if (e->isType(KST_KServiceGroup))
		{
			KServiceGroup::Ptr g(static_cast<KServiceGroup *>(e));
			QString groupCaption = g->caption();
	
			// Avoid adding empty groups.
			KServiceGroup::Ptr subMenuRoot = KServiceGroup::group(g->relPath());
			if (subMenuRoot->childCount() == 0)
				continue;

			// Ignore dotfiles.
			if ((g->name().at(0) == '.'))
				continue;

			// Item names may contain ampersands. To avoid them being converted
			// to accelerators, replace them with two ampersands.
			groupCaption.replace("&", "&&");

			MenuServices * m =
			        newSubMenu(g->name(), g->relPath(), this, g->name().utf8());
			m->setCaption( groupCaption );

			QIconSet iconset;
	
			if (KickerSettings::menuEntryHeight() > 0)
			{
				iconset = KGlobal::instance()->iconLoader()->loadIconSet(
                                                                 g->icon(),
                                                                 KIcon::NoGroup,
                                              KickerSettings::menuEntryHeight()
                                             );
            }
            else if (KickerSettings::menuEntryHeight() == 0)
            {
                QPixmap normal = KGlobal::instance()->iconLoader()->loadIcon(
                                                            g->icon(),
                                                            KIcon::Small,
                                                            0,
                                                            KIcon::DefaultState,
                                                            0L,
                                                            true);

                QPixmap active = KGlobal::instance()->iconLoader()->loadIcon(
                                                            g->icon(),
                                                            KIcon::Small,
                                                            0,
                                                            KIcon::ActiveState,
                                                            0L,
                                                            true);

                // make sure they are not larger than 20x20
                if (normal.width() > 20 || normal.height() > 20)
                {
                    normal.convertFromImage(
                            normal.convertToImage().smoothScale(20,20));
                }
                if (active.width() > 20 || active.height() > 20)
                {
                    active.convertFromImage(
                            active.convertToImage().smoothScale(20,20));
                }


                iconset.setPixmap(normal, QIconSet::Small, QIconSet::Normal);
                iconset.setPixmap(active, QIconSet::Small, QIconSet::Active);
            }

            int newId = insertItem(iconset, groupCaption, m, id++);
            m_entryMap.insert(newId, static_cast<KSycocaEntry*>(g));
            // We have to delete the sub menu our selves! (See Qt docs.)
            m_subMenus.append(m);
        }
        else if (e->isType(KST_KService))
        {
            KService::Ptr s(static_cast<KService *>(e));
            insertMenuItem(s, id++, -1, &suppressGenericNames);
        }
        else if (e->isType(KST_KServiceSeparator))
        {
            insertSeparator();
        }
    } // end loop
}

void MenuServices::insertMenuItem(KService::Ptr& s, int nId, int nIndex,
                                  const QStringList *suppressGenericNames)
{
    QString serviceName = s->name();
    QString comment = s->genericName();


	if (!comment.isEmpty())
	{
		if (KickerSettings::menuEntryFormat() == KickerSettings::NameAndDescription)
		{
			if (!suppressGenericNames ||
				!suppressGenericNames->contains(s->untranslatedGenericName()))
			{
				serviceName = QString("%1 (%2)").arg(serviceName).arg(comment);
			}
		}
		else if (KickerSettings::menuEntryFormat() == KickerSettings::DescriptionAndName)
		{
			serviceName = QString("%1 (%2)").arg(comment).arg(serviceName);
		}
		else if (KickerSettings::menuEntryFormat() == KickerSettings::DescriptionOnly)
		{
			serviceName = comment;
		}
	}
    // restrict menu entries name length
    if (serviceName.length() > 60)
    {
        serviceName.truncate(57);
        serviceName += "...";
    }

    //Check for no Display
    if (s->noDisplay())
    {
        return;
    }

    // ignore dotfiles
    if ((serviceName.at(0) == '.'))
    {
        return;
    }

    // item names may contain ampersands. To avoid them being converted
    // to accelerators, replace them with two ampersands.
    serviceName.replace("&", "&&");

    QIconSet iconset;

    if (KickerSettings::menuEntryHeight() > 0)
    {
        iconset = KGlobal::iconLoader()->loadIconSet(
                                             s->icon(),
                                             KIcon::NoGroup,
                                             KickerSettings::menuEntryHeight());
    }
    else if (KickerSettings::menuEntryHeight() == 0)
    {
        QPixmap normal = KGlobal::iconLoader()->loadIcon( s->icon(),
                                                          KIcon::Small,
                                                          0,
                                                          KIcon::DefaultState,
                                                          0L,
                                                          true);

        QPixmap active = KGlobal::iconLoader()->loadIcon( s->icon(),
                                                          KIcon::Small,
                                                          0,
                                                          KIcon::ActiveState,
                                                          0L,
                                                          true);

        //make sure they are not larger than 20x20
        if (normal.width() > 20 || normal.height() > 20)
        {
            normal.convertFromImage(normal.convertToImage().smoothScale(20,20));
        }

        if (active.width() > 20 || active.height() > 20)
        {
            active.convertFromImage(active.convertToImage().smoothScale(20,20));
        }

        iconset.setPixmap(normal, QIconSet::Small, QIconSet::Normal);
        iconset.setPixmap(active, QIconSet::Small, QIconSet::Active);
    }

	int newId = insertItem(iconset, serviceName, nId, nIndex);
	m_entryMap.insert(newId, static_cast<KSycocaEntry*>(s));
}


MenuServices *MenuServices::newSubMenu(const QString & label,
                                       const QString & relPath,
                                       QWidget * parent, const char * name)
{
	return new MenuServices(label, relPath, parent, name);
}



void MenuServices::setExcludeNoDisplay( bool flag )
{
	m_excludeNoDisplay = flag;
}

void MenuServices::selectFirstItem()
{
	setActiveItem(indexOf(idStart));
}


void MenuServices::mousePressEvent(QMouseEvent * ev)
{
    m_startPos = ev->pos();
    KPanelMenu::mousePressEvent(ev);
}

void MenuServices::mouseReleaseEvent(QMouseEvent *ev)
{
    if (ev->button() == RightButton)
    {
        int id = idAt( ev->pos() );

        if (id < idStart)
        {
            return;
        }

        if (!m_entryMap.contains(id))
        {
            return;
        }

        m_contextKSycocaEntry = m_entryMap[id];

        delete m_popupMenu;
        m_popupMenu = new KPopupMenu(this);

        connect( m_popupMenu, SIGNAL(activated(int)),
                 SLOT(slotContextMenu(int)));

        switch (m_contextKSycocaEntry->sycocaType())
        {
            case KST_KService:
                if (kapp->authorize("editable_desktop_icons"))
                    m_popupMenu->insertItem( SmallIconSet("desktop"),
                                             i18n("Add Item to Desktop"),
                                             AddItemToDesktop);

                if (kapp->authorizeKAction("kicker_rmb"))
                    m_popupMenu->insertItem( SmallIconSet("kicker"),
                                             i18n("Add Item to Main Panel"),
                                             AddItemToPanel);

                if (kapp->authorizeKAction("menuedit"))
                    m_popupMenu->insertItem( SmallIconSet("kmenuedit"),
                                             i18n("Edit Menu Item"),
                                             EditItem);

                if (kapp->authorizeKAction("run_command"))
                    m_popupMenu->insertItem( SmallIconSet("run"),
                                             i18n("Put Into Run Dialog"),
                                             PutIntoRunDialog);
                break;

            case KST_KServiceGroup:
                if (kapp->authorize("editable_desktop_icons"))
                    m_popupMenu->insertItem( SmallIconSet("desktop"),
                                             i18n("Add Item to Desktop"),
                                             AddItemToDesktop);

                if (kapp->authorizeKAction("kicker_rmb"))
                    m_popupMenu->insertItem( SmallIconSet("kicker"),
                                             i18n("Add Item to Main Panel"),
                                             AddItemToPanel);

                if (kapp->authorizeKAction("menuedit"))
                    m_popupMenu->insertItem( SmallIconSet("kmenuedit"),
                                             i18n("Edit Menu"),
                                             this, SLOT( slotEditMenu() ));
                break;

            default:
                return;
                break;
        }

        m_popupMenu->popup( this->mapToGlobal( ev->pos() ));
        return;
    }

    delete m_popupMenu;
    m_popupMenu = 0;

    KPanelMenu::mouseReleaseEvent(ev);
}
void MenuServices::slotEditMenu()
{
	KProcess *proc;
	proc = new KProcess(this);
	*proc << KStandardDirs::findExe(QString::fromLatin1("kmenuedit"));
	proc->start();
}
void MenuServices::slotContextMenu(int selected)
{
    KProcess *proc;
    KService::Ptr service;
    KServiceGroup::Ptr g;
    QByteArray ba;
    QDataStream ds(ba, IO_WriteOnly);

    KURL src,dest;
    KIO::CopyJob *job;
    KDesktopFile *df;

    switch (selected)
    {
        case AddItemToDesktop:
            service = static_cast<KService *>(m_contextKSycocaEntry);

            src.setPath(KGlobal::dirs()->findResource("apps",
                                                  service->desktopEntryPath()));
            dest.setPath(KGlobalSettings::desktopPath());
            dest.setFileName(src.fileName());

            job = KIO::copyAs( src, dest );
            job->setDefaultPermissions(true);
            break;

        case AddItemToPanel:
            service = static_cast<KService *>(m_contextKSycocaEntry);

            kapp->dcopClient()->send("kicker", "Panel",
                                     "addServiceButton(QString)",
                                     service->desktopEntryPath());
            break;

        case EditItem:
            proc = new KProcess(this);
            *proc << KStandardDirs::findExe(QString::fromLatin1("kmenuedit"));
            *proc << "/"+m_relPath << static_cast<KService *>(m_contextKSycocaEntry)->menuId();
            proc->start();
            break;

        case PutIntoRunDialog:
            service = static_cast<KService *>(m_contextKSycocaEntry);
            kapp->dcopClient()->send("kdesktop", "default",
                                     "popupExecuteCommand(QString)",
                                     service->exec());
            break;

        case AddMenuToDesktop:
            g = static_cast<KServiceGroup *>(m_contextKSycocaEntry);
            dest.setPath(KGlobalSettings::desktopPath() );
            dest.setFileName(g->caption());

            df = new KDesktopFile(dest.path());
            df->writeEntry("Icon", g->icon());
            df->writePathEntry("URL", "programs:/"+g->name());
            df->writeEntry("Name", g->caption());
            df->writeEntry("Type", "Link");
            df->sync();
            delete df;
            break;

        case AddMenuToPanel:
            g = static_cast<KServiceGroup *>(m_contextKSycocaEntry);
            ds << "foo" << g->relPath();
            kapp->dcopClient()->send("kicker", "Panel",
                                     "addServiceMenuButton(QString,QString)",
                                     ba);
            break;

        case EditMenu:
            proc = new KProcess(this);
            *proc << KStandardDirs::findExe(QString::fromLatin1("kmenuedit"));
            *proc << "/"+static_cast<KServiceGroup *>(m_contextKSycocaEntry)->relPath();
            proc->start();
            break;

        default:
            break;
    } //end switch(selected)
}

void MenuServices::mouseMoveEvent(QMouseEvent *ev)
{
    KPanelMenu::mouseMoveEvent(ev);

    if ((ev->state() & LeftButton) != LeftButton)
    {
        return;
    }

    QPoint p = ev->pos() - m_startPos;

    if (p.manhattanLength() <= QApplication::startDragDistance() )
        return;

    int id = idAt(m_startPos);

    // Don't drag items we didn't create
    if (id < idStart)
    {
        return;
    }

    if (!m_entryMap.contains(id))
    {
        return;
    }

    KSycocaEntry * e = m_entryMap[id];

    QPixmap icon;
    KURL url;

    switch (e->sycocaType())
    {
        case KST_KService:
        {
            icon = static_cast<KService *>(e)->pixmap(KIcon::Small);
            QString filePath = static_cast<KService *>(e)->desktopEntryPath();
            if (filePath[0] != '/')
            {
                filePath = locate("apps", filePath);
            }

            url.setPath(filePath);
            break;
        }
        case KST_KServiceGroup:
        {
            icon = KGlobal::iconLoader()
                    ->loadIcon( static_cast<KServiceGroup *>(e)->icon(),
                                KIcon::Small);

            url = "programs:/"+static_cast<KServiceGroup *>(e)->relPath();
            break;
        }
        default:
        {
            return;
            break;
        }
    }

    // If the path to the desktop file is relative, try to get the full path
    KURLDrag *d = new KURLDrag(KURL::List(url), this);
    connect(d, SIGNAL(destroyed()), this, SLOT(slotDragObjectDestroyed()));
    d->setPixmap(icon);
    d->dragCopy();

    m_startPos = QPoint(-1,-1);
}

void MenuServices::dragEnterEvent(QDragEnterEvent *event)
{
    // Set the DragObject's target to this widget. This is needed because the
    // widget doesn't accept drops, but we want to determine if the drag object
    // is dropped on it. This avoids closing on accidental drags. If this
    // widget accepts drops in the future, these lines can be removed.
    if (event->source() == this)
    {
        KURLDrag::setTarget(this);
    }
    event->ignore();
}

void MenuServices::dragLeaveEvent(QDragLeaveEvent */*event*/)
{
    // see PanelServiceMenu::dragEnterEvent why this is nescessary
    if (!frameGeometry().contains(QCursor::pos()))
    {
        KURLDrag::setTarget(0);
    }
}

void MenuServices::slotClear()
{
    if( isVisible())
    {
        // QPopupMenu's aboutToHide() is emitted before the popup is really
        // hidden, and also before a click in the menu is handled, so do the
        // clearing only after that has been handled
        QTimer::singleShot( 100, this, SLOT( slotClear()));
        return;
    }
    m_entryMap.clear();
    KPanelMenu::slotClear();
    m_subMenus.clear();
}

void MenuServices::slotClearOnClose()
{
    if (!initialized())
    {
        return;
    }

    if ( !isVisible() )
    {
        m_clearOnClose = false;
        slotClear();
    }
    else
    {
        m_clearOnClose = true;
    }
}

void MenuServices::slotClose()
{
    if (m_clearOnClose)
    {
        m_clearOnClose = false;
        slotClear();
    }

    delete m_popupMenu;
    m_popupMenu = 0;
}

void MenuServices::slotDragObjectDestroyed()
{
    if (KURLDrag::target() != this)
    {
        close();
    }
}

void MenuServices::slotExec(int id)
{
    if (!m_entryMap.contains(id))
    {
        return;
    }

    KSycocaEntry * e = m_entryMap[id];

    kapp->propagateSessionManager();

    KService::Ptr service = static_cast<KService *>(e);
    KApplication::startServiceByDesktopPath( service->desktopEntryPath(),
                                             QStringList(), 0, 0, 0,"", true);
    m_startPos = QPoint(-1,-1);
}
