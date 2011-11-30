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


#ifndef __KDESKTOP_MENU_H__
#define __KDESKTOP_MENU_H__

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <kpanelapplet.h>
#include <qbutton.h>
#include <kconfig.h>
#include <kmenubar.h>
#include <dcopclient.h>
#include <dcopobject.h>
class QPixmap;
class KDesktopMenuBar;

class KDesktopMenu : public KPanelApplet
{
    Q_OBJECT

public:


    /**
     * Construct a @ref KPanelApplet just like any other widget.
     *
     * @param configFile The configFile handed over in the factory function.
     * @param Type The applet @ref type().
     * @param actions Standard RMB menu actions supported by the applet (see @ref action() ).
     * @param parent The pointer to the parent widget handed over in the factory function.
     * @param name A Qt object name for your applet.
     **/
    KDesktopMenu(const QString& configFile, Type t = Normal, int actions = 0,
        QWidget *parent = 0, const char *name = 0);
    /** destructor */
    ~KDesktopMenu();
    /**
     * Retrieve a suggested width for a given height.
     *
     * Every applet should reimplement this function.
     *
     * Depending on the panel orientation the height (horizontal panel) or the
     * width (vertical panel) of the applets is fixed.
     * The exact values of the fixed size component depend on the panel size.
     *
     * On a horizontal panel the applet height is fixed, the panel will
     * call @ref widthForHeight(int height) with @p height
     * equal to 'the fixed applet height'
     * when laying out the applets.
     *
     * The applet can now choose the other size component (width)
     * based on the given height.
     *
     * The width you return is granted.
     **/
    virtual int widthForHeight(int height) const;
    /**
     * @return A suggested height for a given width.
     *
     * Every applet should reimplement this function.
     *
     * Depending on the panel orientation the height (horizontal panel) or the
     * width (vertical panel) of the applets is fixed.
     * The exact values of the fixed size component depend on the panel size.
     *
     * On a vertical panel the applet width is fixed, the panel will
     * call @ref heightForWidth(int width) with @p width
     * equal to 'the fixed applet width'
     * when laying out the applets.
     *
     * The applet can now choose the other size component (height)
     * based on the given width.
     *
     * The height you return is granted.
     **/
    virtual int heightForWidth(int width) const;
    /**
     * Is called when the user selects "About" from the applets RMB menu.
     * Reimplement this function to launch a about dialog.
     *
     * Note that this is called only when your applet supports the About action.
     * See @ref Action and @ref KPanelApplet().
     **/
    virtual void about();
    /**
     * Is called when the user selects "Help" from the applets RMB menu.
     * Reimplement this function to launch a manual or help page.
     *
     * Note that this is called only when your applet supports the Help action.
     * See @ref Action and @ref KPanelApplet().
     **/
    virtual void help();
    /**
     * Is called when the user selects "Preferences" from the applets RMB menu.
     * Reimplement this function to launch a preferences dialog or kcontrol module.
     *
     * Note that this is called only when your applet supports the preferences action.
     * See @ref Action and @ref KPanelApplet().
     **/
	virtual void preferences();
	void rightMouseButtonEvent( QMouseEvent *ev );
protected slots:
	void slotContextMenu(int selected);
	void slotSettingsChanged();


protected:
	void resizeEvent(QResizeEvent *);
	void mouseReleaseEvent( QMouseEvent *ev );
	void reconfigure();
	void createMenu();


private:
	enum          ContextMenu { EditMenu, ShowAbout, ShowHelp,
								DoReload, ConfMenu };
	KDesktopMenuBar           *m_menuBar;
	QButton            *m_icon;
	QPopupMenu         *m_popupMenu;
	QPopupMenu         *m_popupProgMenu;
	QPoint              m_ProgPoint;
	QString             m_menuText;
	int                 m_menuId;
	int                 m_ProgId;
};


class KDesktopMenuBar : public QMenuBar
{
	Q_OBJECT

	public:
		KDesktopMenuBar( KDesktopMenu *parent, const char *name );
		~KDesktopMenuBar();
		int getMenuId();
		void setMenuId( int id);

	protected:
		void mouseReleaseEvent( QMouseEvent *ev );
		void drawContents( QPainter *p );
	private:
		KDesktopMenu *m_parent;
		int menuId;
};


class KMenuButton : public QButton
{
	Q_OBJECT

	public:
		KMenuButton( KDesktopMenu *parent, QMenuBar * menuBar, const char *name );
	//    KMenuButton( KDesktopMenu *parent, const char *name );
		~KMenuButton();
		void setPixmap( const QPixmap &pix );
	protected slots:
		void slotIconChanged();
	protected:
		void drawButton( QPainter *p );
		void drawButtonLabel( QPainter *p );
		QPoint pixmapOrigin() const;
		QSize margin() const { return QSize(5, 5); }
		QSize pixmapSize() const { return size() - margin(); }
		void generateIcons();
		void resizeEvent( QResizeEvent *e );
		void mouseReleaseEvent( QMouseEvent *ev );
		void mousePressEvent( QMouseEvent * );
	private:
		KDesktopMenu *m_parent;
		QMenuBar *m_menuBar;
		QPixmap m_image;
};


#endif
