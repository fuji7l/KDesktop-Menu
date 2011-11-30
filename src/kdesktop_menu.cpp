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
#include <stdlib.h>

#include <qfont.h>
#include <qfontmetrics.h>
#include <qpainter.h>
#include <qstyle.h>

#include <kdirwatch.h>
#include <kglobal.h>
#include <klocale.h>
#include <kconfig.h>
#include <kapplication.h>
#include <kaboutapplication.h>
#include <kdebug.h>
#include <kipc.h>
#include <kmessagebox.h>
#include <kiconloader.h>
#include <kiconeffect.h>
#include <kprocess.h>
#include <kstandarddirs.h>
#include <kconfigdialog.h>
#include <kaboutdata.h>

#include "settingswidgetimp.h"
#include "kdesktopmenu_settings.h"
#include "kicker_settings.h"
#include "kdesktop_menu.h"
#include "menu_programs.h"
#include "menu_actions.h"
#include "menu_desktop.h"
#include "menu_services.h"

KDesktopMenu::KDesktopMenu(const QString& configFile, Type type, int actions,
                           QWidget *parent, const char *name)
    : KPanelApplet(configFile, type, actions, parent, name)
    , m_menuBar( 0 )
    , m_icon( 0 )
    , m_popupMenu( 0 )
{
	setMargin( 0 );
	setLineWidth( 0 );
	setMidLineWidth( 0 );
	setFrameStyle( QFrame::NoFrame );

	QString kickerConfFile = locate("config", QString::fromLatin1("kickerrc"));
	if ( kickerConfFile.isEmpty() || kickerConfFile.isNull() )
	{
		kdDebug() << "Can't locate kicker's config file for monitoring" << endl;
	}
	else
	{
		KDirWatch::self()->addFile( kickerConfFile );
		connect( KDirWatch::self(), SIGNAL( dirty( const QString& ) ),
		         this, SLOT( slotSettingsChanged() ));
	}
	reconfigure();
}

KDesktopMenu::~KDesktopMenu()
{
	if (m_menuBar)
	{
		delete m_menuBar;
		m_menuBar = 0;
	}

	if (m_icon)
	{
		delete m_icon;
		m_icon = 0;
	}
	m_menuId    = 0;
	m_menuText  = QString();
	KGlobal::locale()->removeCatalogue( "KDesktopMenu" );
}
#include <qbitmap.h>
#include <qtoolbutton.h>
void KDesktopMenu::createMenu()
{
	m_menuId   = 0;
	m_menuText = "";
	
	if ( KDesktopMenuSettings::showProgramsMenu() )
	{
		QString strPrograms = KDesktopMenuSettings::programsName();
		m_menuBar->insertItem( strPrograms, new MenuPrograms(m_menuBar), m_menuId++ );
		m_menuText += strPrograms;
		//TODO figure out how to make QMenuBar draw both the text and icon...
		//
// 		QPainter p;
// 		QPixmap pix(80,25);
// 		QBitmap map(80,25);
// 		pix.setMask(map);
// 		p.begin(&pix);
// 		p.setBackgroundMode (Qt::TransparentMode);
// 
// 		p.setRasterOp(Qt::XorROP);
// 
// 		p.drawPixmap( 2, 2, kmenu2);
// 
//  		p.setFont(	KDesktopMenuSettings::menuFont() );
//  		p.setPen( KDesktopMenuSettings::menuFontColour() );
//  		p.drawText( 25, 0, "Programs");
// 		p.end();
// 		m_menuBar->insertItem(pix, new MenuPrograms(m_menuBar), m_menuId++);
// 		m_menuText += strPrograms;
		
//         QPainter p;
// 		QPixmap pix(80,20);
// 		QBitmap map(80,20);
// //		pix.setMask(map);
// 		p.begin(&pix);
// 		p.drawPixmap(2,2,KGlobal::iconLoader()->loadIcon( "kmenu",KIcon::Small));
// 		p.drawText(22, 10, "Programs");
// 		p.end();

//         QPixmap pix = QPixmap(100,20);
//         QPainter p(&pix);
//         QPixmap ddd = QPixmap(KGlobal::iconLoader()->loadIcon( "kmenu",
//                                                             KIcon::Small ));
// 
//         p.drawPixmap(0,0,ddd);
//         p.drawText(ddd.width(),ddd.height(),"asdfadf");
//        m_menuBar->insertItem(pix, new MenuPrograms(m_menuBar), asdf );

//		m_menuBar->insertItem(strPrograms, this, SLOT(slotShowKmenu()), m_menuId++);
//		QIconSet pix;
	//	pix = KGlobal::iconLoader()->loadIcon( "kmenu",KIcon::Small);
		//if (pix.isNull()) { kdDebug() << "pix is null" << endl;}
//  		m_menuBar->insertItem(SmallIconSet("home", 20),strPrograms, new MenuPrograms(m_menuBar), m_menuId++);
//  		m_menuText += strPrograms;
	}

	if ( KDesktopMenuSettings::showActionsMenu() )
	{
		QString strActions = KDesktopMenuSettings::actionsName();
		m_menuBar->insertItem( strActions, new MenuActions(), m_menuId++ );
		m_menuText += strActions;
	}

	if ( KDesktopMenuSettings::showDesktopMenu() )
	{
		QString strDesktop = KDesktopMenuSettings::desktopName();
		m_menuBar->insertItem( strDesktop, new MenuDesktop(), m_menuId++ );
		m_menuText += strDesktop;
	}
}

void KDesktopMenu::about()
{
	KAboutData *about = new KAboutData( "kdesktop_menu",
	                                    I18N_NOOP("KDesktop Menu"),
	                                    "v0.3",
	                                    I18N_NOOP("A replacement for KMenu"),
	                                    KAboutData::License_GPL_V2,
	                                    "(c) 2005 Richard Fujimoto",0,0,
	                                    "rfujimoto [AT] imap [DOT] cc" );
	about->addAuthor( "Richard Fujimoto", I18N_NOOP("Original Author"),
	                  "rfujimoto [AT] imap [DOT] cc" );
	KAboutApplication dlg( about );
	dlg.exec();
	delete about;
	about = 0;
}

void KDesktopMenu::help()
{
	KMessageBox::information(0, i18n("Unimplemented Help System. Coming Eventually"));
}

void KDesktopMenu::preferences()
{
	if ( KConfigDialog::showDialog("settings") )
	{
		return;
	}

	KConfigDialog * dialog = new KConfigDialog( this, "settings",
	                                            KDesktopMenuSettings::self(),
	                                            KDialogBase::Swallow,
	                                KDialogBase::Default | KDialogBase::Ok |
	                                KDialogBase::Apply | KDialogBase::Cancel,
	                                KDialogBase::Ok, false);
	SettingsWidgetImp * confWdg = new SettingsWidgetImp( 0, "Settings" );

	dialog->addPage( confWdg, KDesktopMenuSettings::self(), i18n("Settings"),
	                 QString::fromLatin1("kmenu"));

	connect( dialog, SIGNAL(settingsChanged()),
	         this, SLOT(slotSettingsChanged()) );

	dialog->setCaption( i18n("Configure - KDesktop Menu") );
	dialog->show();
}


int KDesktopMenu::widthForHeight(int ) const
{
	return width();
}

int KDesktopMenu::heightForWidth( int ) const
{
	return height();
}

void KDesktopMenu::reconfigure()
{
	kdDebug() << "    KDesktopMenu::reconfigure()" << endl;
	int menuLength = 0;
	int wOffset    = 0;
	int vOffset    = 0;
	int newHeight  = 0;

	if (m_menuBar)
		delete m_menuBar;

	m_menuBar = new KDesktopMenuBar(this, "menuBar");
	if (KDesktopMenuSettings::showMenuIcon())
	{
		if (m_icon)
			delete m_icon;

		m_icon = new KMenuButton( this, m_menuBar, "m_icon" );
		m_icon->setPixmap( KGlobal::iconLoader()->loadIcon( "kmenu",
		                                                    KIcon::NoGroup ) );


		kapp->removeKipcEventMask( KIPC::IconChanged );
		disconnect( kapp, SIGNAL( iconChanged(int) ),
		            m_icon, SLOT( slotIconChanged() ));

		// User has changed their icon theme, redraw the KDE Menu Icon.
		kapp->addKipcEventMask( KIPC::IconChanged );
		connect( kapp, SIGNAL( iconChanged(int) ),
		         m_icon, SLOT( slotIconChanged()) );
	}
	else
	{
		delete m_icon;
		m_icon = 0;
	}
	QFont daFont( KDesktopMenuSettings::menuFont() );
	m_menuBar->setFont( daFont );

	createMenu();

	if ( orientation() != Horizontal )
	{
		kdDebug() << "This menu will not work properly..."<<endl;
	}
	m_menuBar->reparent( this, QPoint( 0, 0 ), true );

	if (height() >= m_menuBar->sizeHint().height())
	{
		vOffset   = height() - m_menuBar->sizeHint().height() + 1;
		newHeight = m_menuBar->sizeHint().height();
	}
	else
	{
		newHeight = m_menuBar->sizeHint().height();
		if (newHeight > height())
		{
			newHeight = height();
		}
		vOffset   = (height() - newHeight) / 2;
	}

	if ( position() == KPanelApplet::pBottom )
	{
		vOffset = 0;
		m_menuBar->setDefaultUp(true);
	}


	QFontMetrics fontSize(daFont);
	menuLength = (m_menuId)*15 + fontSize.width(m_menuText);

	if (m_icon)
	{
		m_icon->setGeometry( 0, vOffset, newHeight, newHeight );
		wOffset = m_icon->width();
		m_icon->show();
	}

	m_menuBar->setGeometry( wOffset, vOffset, menuLength + 40, newHeight );
	this->setFixedWidth( menuLength + wOffset );
}

void KDesktopMenu::resizeEvent( QResizeEvent * )
{
	reconfigure();
}

void KDesktopMenu::rightMouseButtonEvent( QMouseEvent *ev )
{
	if (ev->button() == RightButton)
	{
		if (m_popupMenu)
			delete m_popupMenu;

		m_popupMenu = new QPopupMenu(this);

		connect(m_popupMenu, SIGNAL(activated(int)), SLOT(slotContextMenu(int)));

		if (kapp->authorize("menuedit"))
		{
			m_popupMenu->insertItem( SmallIconSet("kmenuedit"),
			                         i18n("Edit Menu"), EditMenu );
			m_popupMenu->insertSeparator();
		}

		m_popupMenu->insertItem( i18n("About..."), ShowAbout );
		m_popupMenu->insertItem( SmallIconSet("help"), i18n("Help"), ShowHelp );
		m_popupMenu->insertItem( SmallIconSet("reload"),
		                         i18n("Reload Configuration"), DoReload );
		m_popupMenu->insertSeparator();
		m_popupMenu->insertItem( SmallIconSet("configure"),
		                         i18n("Configure KDesktop Menu..."), ConfMenu );

		m_popupMenu->popup( this->mapToGlobal( ev->pos() ));
		return;
	}

	delete m_popupMenu;
	m_popupMenu = 0;
}

void KDesktopMenu::mouseReleaseEvent(QMouseEvent *ev)
{
	rightMouseButtonEvent( ev );
	KPanelApplet::mouseReleaseEvent(ev);
}


void KDesktopMenu::slotContextMenu(int selected)
{
	KProcess *proc;

	switch (selected)
	{
		case ConfMenu:
			this->preferences();
			break;
		case DoReload:
			this->reconfigure();
			break;
		case ShowHelp:
			this->help();
			break;
		case ShowAbout:
			this->about();
			break;
		case EditMenu:
			proc = new KProcess( this );
			*proc << KGlobal::dirs()->findExe(QString::fromLatin1("kmenuedit"));
			proc->start();
			break;
		default:
			break;
	} //end switch(selected)
}

void KDesktopMenu::slotSettingsChanged()
{
	reconfigure();
}

extern "C"
{
	KPanelApplet* init( QWidget *parent, const QString& configFile )
	{
		KGlobal::locale()->insertCatalogue("KDesktopMenu");
		return new KDesktopMenu( configFile, KPanelApplet::Normal,
		                         KPanelApplet::About | KPanelApplet::Help |
		                         KPanelApplet::Preferences,
		                         parent, "KDesktopMenu" );
	}
}


//
//-----------------------------------------------------------------------------
//

KMenuButton::KMenuButton( KDesktopMenu *parent, QMenuBar * menuBar, const char *name )
    : QButton( parent, name)
    , m_parent(parent)
    , m_menuBar(menuBar)
{
	setBackgroundOrigin( AncestorOrigin );
	setText("Programs");
}

KMenuButton::~KMenuButton()
{
	m_image = QPixmap();
}

void KMenuButton::drawButton( QPainter *p )
{
	drawButtonLabel( p );
}

void KMenuButton::drawButtonLabel( QPainter *p )
{
	if ( pixmap() )
	{
		p->drawPixmap( pixmapOrigin(), m_image);
	}
	//p->drawText(25,10,"Programs");
}

void KMenuButton::generateIcons()
{
	if (! pixmap() )
	{
		kdDebug() << "No pixmap for KDesktopMenu's kmenu button" << endl;
		return;
	}

	QImage image = pixmap()->convertToImage();
	image = image.smoothScale( pixmapSize(), QImage::ScaleMin );
	KIconEffect effect;
	m_image = effect.apply( image, KIcon::NoGroup, KIcon::LastState );
}

void KMenuButton::setPixmap( const QPixmap &pix )
{
	QButton::setPixmap( pix );
	generateIcons();
}

QPoint KMenuButton::pixmapOrigin() const
{
	QSize point = margin() / 2;
	QPoint origin( point.width(), point.height() );
	return origin;
}

void KMenuButton::resizeEvent( QResizeEvent * )
{
	generateIcons();
}
void KMenuButton::mouseReleaseEvent( QMouseEvent *ev )
{
	if (ev->button() == RightButton)
	{
		m_parent->rightMouseButtonEvent( ev );
	}
	QButton::mouseReleaseEvent( ev );
}

void KMenuButton::mousePressEvent(QMouseEvent *ev)
{
	if (ev->button() == RightButton)
	{
		// overwrite the RMB event or we get too many menus
		return;
	}
	QButton::mousePressEvent( ev );
}

void KMenuButton::slotIconChanged()
{
	m_image = QImage();
	setPixmap( KGlobal::instance()->iconLoader()->loadIcon( "kmenu", KIcon::NoGroup ) );
	generateIcons();
}

//
//-----------------------------------------------------------------------------
//

KDesktopMenuBar::KDesktopMenuBar( KDesktopMenu *parent, const char *name )
    : QMenuBar( parent, name )
    , m_parent( parent )
{
	setLineWidth( 0 );
	setMargin( 0 );
	setMidLineWidth( 0 );
	setFrameStyle( QFrame::NoFrame );
	menuId = 0;


}

KDesktopMenuBar::~KDesktopMenuBar()
{
}

void KDesktopMenuBar::drawContents( QPainter *p )
{
	bool up_enabled = isUpdatesEnabled();
	BackgroundMode bg_mode = backgroundMode();
	BackgroundOrigin bg_origin = backgroundOrigin();

	setUpdatesEnabled(false);
	setBackgroundMode(X11ParentRelative);
	setBackgroundOrigin(WindowOrigin);

	p->eraseRect( rect() );
	erase();

	QColorGroup g = colorGroup();
	bool e;

	for ( int i=0; i<(int)count(); i++ )
	{
		QMenuItem *mi = findItem( idAt( i ) );
		if ( !mi->text().isNull() || mi->pixmap() )
		{
			
			QRect r = itemRect(i);
			if(r.isEmpty() || !mi->isVisible())
				continue;

			e = mi->isEnabledAndVisible();
			if ( e )
				g = isEnabled() ? ( isActiveWindow()
				                                    ? palette().active()
				                                    : palette().inactive() )
				                : palette().disabled();
			else
				g = palette().disabled();
	
			bool item_active = ( actItem ==  i );
	
			p->setClipRect(r);

			// Sets the font colour for our menu
			g.setColor( QColorGroup::Foreground,
						KDesktopMenuSettings::menuFontColour() );

			if( item_active )
			{
				QStyle::SFlags flags = QStyle::Style_Default;
	
				if (isEnabled() && e)
					flags |= QStyle::Style_Enabled;
	
				if ( item_active )
					flags |= QStyle::Style_Active;
	
				if ( item_active && actItemDown )
					flags |= QStyle::Style_Down;
	
				flags |= QStyle::Style_HasFocus;
				style().drawControl(QStyle::CE_MenuBarItem, p, this,
				                    r, g, flags, QStyleOption(mi));
			}
			else
			{
				style().drawItem( p, r, AlignCenter | AlignVCenter | ShowPrefix,
				                  g, e, mi->pixmap(), mi->text());
			}
		}
	}

	setBackgroundOrigin(bg_origin);
	setBackgroundMode(bg_mode);
	setUpdatesEnabled(up_enabled);
}
int KDesktopMenuBar::getMenuId() { return menuId; }
void KDesktopMenuBar::setMenuId( int id) { menuId = id; }
void KDesktopMenuBar::mouseReleaseEvent(QMouseEvent *ev)
{
	if (ev->button() == RightButton)
	{
		m_parent->rightMouseButtonEvent( ev );
	}
	else
	{
		QMenuBar::mouseReleaseEvent( ev );
	}
}


