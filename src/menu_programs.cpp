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
#include <sys/types.h>
#include <unistd.h>
#include <qimage.h>
#include <qpainter.h>
#include <qstyle.h>
#include <qstring.h>
#include <qapplication.h>

#include <dcopclient.h>
#include <kapplication.h>
#include <kdebug.h>
#include <kdirwatch.h>
#include <kconfig.h>
#include <kglobal.h>
#include <kiconeffect.h>
#include <kiconloader.h>
#include <kipc.h>
#include <klocale.h>
#include <krun.h>
#include <kservice.h>
#include <kservicegroup.h>
#include <kshell.h>
#include <kstandarddirs.h>
#include <ksycoca.h>
#include <ksycocaentry.h>
#include <kurl.h>

#include "kdesktopmenu_settings.h"
#include "kicker_settings.h"
#include "menu_programs.h"
#include "menu_services.h"

const int idStart = 4242;

MenuPrograms::MenuPrograms( QMenuBar *parent)
    : MenuServices(QString::null, QString::null, 0, "KMenu")
    , m_parent( parent )
{
    // Don't automatically clear the main menu.
    disableAutoClear();
    setCaption(i18n("K Menu"));

    // Some Global Setting has changed
    kapp->addKipcEventMask(KIPC::SettingsChanged);
    connect( kapp, SIGNAL(settingsChanged(int)),
             this, SLOT(slotConfigChanged()) );

    QString emailDefaultsFile = locate( "config",
                                        QString::fromLatin1("emaildefaults"));
    if ( emailDefaultsFile.isEmpty() || emailDefaultsFile.isNull() )
    {
        kdDebug() << "Can't locate Email Defaults file for monitoring" << endl;
    }
    else
    {
        KDirWatch::self()->addFile( emailDefaultsFile );
        connect( KDirWatch::self(), SIGNAL( dirty( const QString& ) ),
                 this, SLOT( slotConfigChanged() ));
    }
}

MenuPrograms::~MenuPrograms()
{
    m_sidePixmap = QPixmap();
    m_sideTilePixmap = QPixmap();

    m_browserName = QString::null;
    m_browserIcon = QString::null;
    m_browserExec = QString::null;

    m_emailName   = QString::null;
    m_emailIcon   = QString::null;
    m_emailExec   = QString::null;
}

void MenuPrograms::colorize(QImage& image)
{
    KConfig *config = KGlobal::config();
    config->setGroup("WM");
    QColor color = QApplication::palette().active().highlight();
    QColor activeTitle = config->readColorEntry("activeBackground", &color);
    QColor inactiveTitle = config->readColorEntry("inactiveBackground", &color);

    // figure out which color is most suitable for recoloring to
    int h1, s1, v1, h2, s2, v2, h3, s3, v3;
    activeTitle.hsv(&h1, &s1, &v1);
    inactiveTitle.hsv(&h2, &s2, &v2);
    QApplication::palette().active().background().hsv(&h3, &s3, &v3);

    if ( (kAbs(h1-h3)+kAbs(s1-s3)+kAbs(v1-v3) <
          kAbs(h2-h3)+kAbs(s2-s3)+kAbs(v2-v3)) &&
       ( (kAbs(h1-h3)+kAbs(s1-s3)+kAbs(v1-v3) < 32) || (s1 < 32)) && (s2 > s1))
        color = inactiveTitle;
    else
        color = activeTitle;

    // limit max/min brightness
    int r, g, b;
    color.rgb(&r, &g, &b);
    int gray = qGray(r, g, b);
    if (gray > 180) {
        r = (r - (gray - 180) < 0 ? 0 : r - (gray - 180));
        g = (g - (gray - 180) < 0 ? 0 : g - (gray - 180));
        b = (b - (gray - 180) < 0 ? 0 : b - (gray - 180));
    } else if (gray < 76) {
        r = (r + (76 - gray) > 255 ? 255 : r + (76 - gray));
        g = (g + (76 - gray) > 255 ? 255 : g + (76 - gray));
        b = (b + (76 - gray) > 255 ? 255 : b + (76 - gray));
    }
    color.setRgb(r, g, b);
    KIconEffect::colorize(image, color, 1.0);
}

bool MenuPrograms::loadSidePixmap()
{
	if (!KickerSettings::useSidePixmap())
	{
		kdDebug() << "  useSidePixmap was false" <<endl;
		return false;
	}
	
	QString sideName = KickerSettings::sidePixmapName();
	QString sideTileName = KickerSettings::sideTileName();
	
	QImage image;
	image.load(locate("data", "kicker/pics/" + sideName));
	
	if (image.isNull())
	{
		kdDebug() << "Cannot load the Side Pixmap" << endl;
		return false;
	}
	
	colorize(image);
	m_sidePixmap.convertFromImage(image);
	
	image.load( locate( "data", "kicker/pics/" + sideTileName ) );
	
	if ( image.isNull() )
	{
		return false;
	}
	
	colorize( image );
	m_sideTilePixmap.convertFromImage( image );
	
	if (m_sidePixmap.width() != m_sideTilePixmap.width())
	{
		kdDebug() << "  Pixmaps have to be the same size" <<endl;
		return false;
	}
	
	// pretile the pixmap to a height of at least 100 pixels
	if (m_sideTilePixmap.height() < 100)
	{
		int tiles = (int)(100 / m_sideTilePixmap.height()) + 1;
		QPixmap preTiledPixmap( m_sideTilePixmap.width(),
		                        m_sideTilePixmap.height() * tiles );
		QPainter p( &preTiledPixmap );
		p.drawTiledPixmap( preTiledPixmap.rect(), m_sideTilePixmap );
		m_sideTilePixmap = preTiledPixmap;
	}
	return true;
}

void MenuPrograms::paletteChanged()
{
	if (!loadSidePixmap())
	{
		m_sidePixmap = m_sideTilePixmap = QPixmap();
		setMinimumSize( sizeHint() );
	}
}

QString MenuPrograms::stripCommandArgs( QString command )
{
	QStringList cmdTokens = KShell::splitArgs( command );
	return cmdTokens[0];
}

void MenuPrograms::getEmailClient()
{
	if (! KDesktopMenuSettings::useCustomEmailClient() )
	{
		getDefaultEmailClient();
		return;
	}

	QString eclient = KDesktopMenuSettings::customEmailClient();
	if ( eclient.isEmpty() || eclient.isNull() )
	{
		getDefaultEmailClient();
		return;
	}
	else
	{
		QString cmd = stripCommandArgs( eclient );

		KService::Ptr service = KService::serviceByDesktopName(
		                                      QString::fromLatin1( cmd ));
		if (!service)
		{
			m_emailName = cmd;
			m_emailIcon = "email";
			m_emailExec = eclient;
		}
		else
		{
			m_emailName = service->name();
			m_emailIcon = service->icon();
			m_emailExec = service->exec();
	
			if ( KDesktopMenuSettings::useTerminalCustomEmailClient() )
			{
				kdDebug() << "Terminal email clients... " << endl;
				KConfigGroup confGroup( KGlobal::config(), "General" );
				QString prefTerm = confGroup.readPathEntry(
				                           "TerminalApplication", "konsole" );
				m_emailExec = prefTerm + " -e " + service->exec();
			}
		}
	}
}

void MenuPrograms::getDefaultEmailClient()
{
	KConfig config("emaildefaults");
	config.setGroup("Defaults");
	QString group = config.readEntry("Profile", "Default");
	config.setGroup( QString("PROFILE_%1").arg(group) );

	QString command = config.readPathEntry("EmailClient");

	if ( command.isEmpty() || command == QString::fromLatin1("kmail") ||
	     command.endsWith("/kmail") )
	{
		KService::Ptr service = KService::serviceByDesktopName(
		                                   QString::fromLatin1("kmail"));
		if (service)
		{
			m_emailName = service->name();
			m_emailIcon = service->icon();
			m_emailExec = service->exec();
		}
		else
		{
			kdDebug() << "Can't find Kmail's desktop file." << endl;
		}
	}
	else
	{
		QString cmd = stripCommandArgs( command );
		KService::Ptr service = KService::serviceByDesktopName(
												QString::fromLatin1( cmd) );
		if (! service )
		{
			kdDebug() << cmd << " desktop file not found" << endl;
			m_emailName = cmd;
			m_emailIcon = "email";
			m_emailExec = command;
		}
		else
		{
			m_emailName = service->name();
			m_emailIcon = service->icon();
			m_emailExec = service->exec();
		}
	}
	
	if ( config.readBoolEntry( "TerminalClient", false ) )
	{
		kdDebug() << "Terminal email clients... " << endl;
		KConfigGroup confGroup( KGlobal::config(), "General" );
		QString prefTerm = confGroup.readPathEntry( "TerminalApplication",
		                                            "konsole" );
		m_emailExec = prefTerm + " -e " + command;
	}
}

void MenuPrograms::getBrowser()
{
	if (! KDesktopMenuSettings::useCustomBrowser() )
	{
		getDefaultBrowser();
		return;
	}

	QString browser = KDesktopMenuSettings::customBrowser();
	if ( browser.isEmpty() || browser.isNull() )
	{
		getDefaultBrowser();
	}
	else
	{
		QString cmd = stripCommandArgs( browser );
	
		KService::Ptr service = KService::serviceByDesktopName(
		                                             QString::fromLatin1( cmd));
		if (!service)
		{
			m_browserName = cmd;
			m_browserIcon = "internet";
			m_browserExec = browser;
		}
		else
		{
			m_browserName = service->name();
			m_browserIcon = service->icon();
			m_browserExec = service->exec();
		}
	}
}

void MenuPrograms::getDefaultBrowser()
{
	KConfigGroup confGroup( KGlobal::config(), "General" );
	QString exec = confGroup.readEntry("BrowserApplication");

	QString browserName = "";

	if ( exec.isEmpty() )
	{
		KService::Ptr service = KService::serviceByDesktopName(
		                                    QString::fromLatin1("konqbrowser"));
		if (service)
		{
			m_browserName = service->name();
			m_browserIcon = service->icon();
			m_browserExec = service->exec();
		}
		else
		{
			kdDebug() << "Konqueror is default, cannot find desktop file"<<endl;
		}
	}
	else
	{
		if (exec.startsWith("!"))
		{
			browserName = exec.mid(1);
	
			QString cmd = stripCommandArgs( browserName );
	
			KService::Ptr service = KService::serviceByDesktopName(
			                                          QString::fromLatin1(cmd));
			if (! service )
			{
				kdDebug() << "Could not locate df for "<< browserName << endl;
				//set up some default options but with the proper exec file
				m_browserName = cmd;
				m_browserIcon = "enhanced_browsing";
				m_browserExec = browserName;
			}
			else
			{
				m_browserName = service->name();
				m_browserIcon = service->icon();
				m_browserExec = service->exec();
			}
		}
		else
		{
			if (exec.endsWith(".desktop"))
			{
				exec = exec.replace(".desktop", QString(), false);
			}
			KService::Ptr service = KService::serviceByDesktopName(
			                                         QString::fromLatin1(exec));
			if (! service )
			{
				//shouldn't ever hit here unless somebody messed with kconfig
				// manually or...?
				kdDebug() << "Unusable default browser specified. Cannot find \
				              the desktop file" << endl;
			}
			else
			{
				m_browserName = service->name();
				m_browserIcon = service->icon();
				m_browserExec = service->exec();
			}
		}
	}
}

void MenuPrograms::initialize()
{
	if (initialized())
	{
		return;
	}
	
	if (loadSidePixmap())
	{
		// in case we've been through here before, let's disconnect
		disconnect( kapp, SIGNAL(kdisplayPaletteChanged()),
		            this, SLOT(paletteChanged()) );
		connect( kapp, SIGNAL(kdisplayPaletteChanged()),
		         this, SLOT(paletteChanged()) );
	}
	else
	{
		m_sidePixmap = m_sideTilePixmap = QPixmap();
	}

	MenuServices::initialize();

	int beginId = 0;

	if ( KDesktopMenuSettings::showDefaultEmailClient() )
	{
		kdDebug() << "getEmailClient()" << endl;
		getEmailClient();

		if (KickerSettings::menuEntryHeight() > -1)
		{
			insertItem( SmallIconSet( m_emailIcon,
			                          KickerSettings::menuEntryHeight()),
			            i18n("Email ( %1 )").arg( m_emailName ),
			            this, SLOT( slotLaunchEmailClient() ),
			            0, -1, beginId++);
		}
		else
		{
			insertItem( i18n("Email ( %1 )").arg( m_emailName ), this,
			            SLOT( slotLaunchEmailClient() ), 0, -1, beginId++);
		}
	}

	if ( KDesktopMenuSettings::showDefaultBrowser() )
	{
		kdDebug() << "getBrowser()" << endl;
		getBrowser();

		if (KickerSettings::menuEntryHeight() > -1)
		{
			insertItem( SmallIconSet( m_browserIcon,
			                          KickerSettings::menuEntryHeight()),
			            i18n("Web Browser ( %1 )").arg( m_browserName),
			            this, SLOT( slotLaunchBrowser() ),
			            0, -1, beginId++);
		}
		else
		{
			insertItem( i18n("Web Browser ( %1 )").arg( m_browserName),
			            this, SLOT( slotLaunchBrowser() ),
			            0, -1, beginId++);
		}
	}

	insertSeparator(beginId++);
	beginId = 0;

	if (kapp->authorize("run_command"))
	{
		insertSeparator();
		insertSeparator();
		if (KickerSettings::menuEntryHeight() > -1)
		{
			insertItem( SmallIconSet("run",
			                         KickerSettings::menuEntryHeight()),
			            i18n("Run Command..."),
			            this,
			            SLOT( slotRunCommand() ));
		}
		else
		{
			insertItem( i18n("Run Command..."), this, SLOT( slotRunCommand() ));
		}
	}
	setInitialized(true);
}


void MenuPrograms::resizeEvent(QResizeEvent * e)
{
	KPanelMenu::resizeEvent(e);

	setFrameRect( QStyle::visualRect( QRect( m_sidePixmap.width(), 0,
	              width() - m_sidePixmap.width(), height() ), this ) );
}
void MenuPrograms::resize(int width, int height)
{
	width = kMax(width, maximumSize().width());
	KPanelMenu::resize(width, height);
}

QSize MenuPrograms::sizeHint()
{
	QSize s = MenuServices::sizeHint();
	return s;
}

void MenuPrograms::paintEvent(QPaintEvent * e)
{
	if (m_sidePixmap.isNull())
	{
		MenuServices::paintEvent(e);
		return;
	}

	QPainter p(this);
	p.setClipRegion(e->region());

	style().drawPrimitive( QStyle::PE_PanelPopup, &p,
	                       QRect( 0, 0, width(), height() ),
	                       colorGroup(), QStyle::Style_Default,
	                       QStyleOption( frameWidth(), 0 ) );

	QRect r = sideImageRect();
	r.setBottom( r.bottom() - m_sidePixmap.height() );
	if ( r.intersects( e->rect() ) )
	{
		p.drawTiledPixmap( r, m_sideTilePixmap );
	}

	r = sideImageRect();
	r.setTop( r.bottom() - m_sidePixmap.height() );
	if ( r.intersects( e->rect() ) )
	{
		QRect drawRect = r.intersect( e->rect() );
		QRect pixRect  = drawRect;
		pixRect.moveBy( -r.left(), -r.top() );
		p.drawPixmap( drawRect.topLeft(), m_sidePixmap, pixRect );
	}

	drawContents( &p );
}

QRect MenuPrograms::sideImageRect()
{
	return QStyle::visualRect( QRect( frameWidth(), frameWidth(),
	                                  m_sidePixmap.width(),
	                                  height() - 2*frameWidth() ), this );
}


void MenuPrograms::setMinimumSize(const QSize & s)
{
	KPanelMenu::setMinimumSize(s.width() + m_sidePixmap.width(), s.height());
}

void MenuPrograms::setMaximumSize(const QSize & s)
{
	KPanelMenu::setMaximumSize(s.width() + m_sidePixmap.width(), s.height());
}

void MenuPrograms::setMinimumSize(int w, int h)
{
	KPanelMenu::setMinimumSize(w + m_sidePixmap.width(), h);
}

void MenuPrograms::setMaximumSize(int w, int h)
{
	KPanelMenu::setMaximumSize(w + m_sidePixmap.width(), h);
}

void MenuPrograms::slotConfigChanged()
{
	setInitialized( false );
}

void MenuPrograms::slotRunCommand()
{
	QByteArray data;
	QCString appname( "kdesktop" );

	kapp->updateRemoteUserTimestamp( appname );
	kapp->dcopClient()->send( appname, "KDesktopIface",
	                          "popupExecuteCommand()", data );
}

void MenuPrograms::slotLaunchEmailClient()
{
	KService service(m_emailName, m_emailExec, m_emailIcon);
	KRun::run(service, KURL::List::List(), false);
}

void MenuPrograms::slotLaunchBrowser()
{
	KService service(m_browserName, m_browserExec, m_browserIcon);
	KRun::run(service, KURL::List::List(), false);
}

QMouseEvent MenuPrograms::translateMouseEvent( QMouseEvent* e )
{
	QRect side = sideImageRect();

	if ( !side.contains( e->pos() ) )
		return *e;

	QPoint newpos( e->pos() );
	QApplication::reverseLayout()
	    ? newpos.setX( newpos.x() - side.width() )
	    : newpos.setX( newpos.x() + side.width() );
	QPoint newglobal( e->globalPos() );
	QApplication::reverseLayout()
	    ? newglobal.setX( newpos.x() - side.width() )
	    : newglobal.setX( newpos.x() + side.width() );

	return QMouseEvent( e->type(), newpos, newglobal, e->button(), e->state() );
}

void MenuPrograms::mousePressEvent(QMouseEvent * e)
{
	QMouseEvent newEvent = translateMouseEvent(e);
	MenuServices::mousePressEvent( &newEvent );
}

void MenuPrograms::mouseReleaseEvent(QMouseEvent *e)
{
	QMouseEvent newEvent = translateMouseEvent(e);
	MenuServices::mouseReleaseEvent( &newEvent );
}

void MenuPrograms::mouseMoveEvent(QMouseEvent *e)
{
	QMouseEvent newEvent = translateMouseEvent(e);
	MenuServices::mouseMoveEvent( &newEvent );
}
