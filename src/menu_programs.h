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

#ifndef __MENU_PROGRAMS_H__
#define __MENU_PROGRAMS_H__

#include <qmenubar.h>
#include "menu_services.h"

class MenuPrograms : public MenuServices
{
	Q_OBJECT

public:
	MenuPrograms( QMenuBar *parent);
	~MenuPrograms();

	QSize sizeHint();
	void setMinimumSize(const QSize &);
	void setMaximumSize(const QSize &);
	void setMinimumSize(int, int);
	void setMaximumSize(int, int);
	QString relPath() { return m_relPath; }

public slots:
	void initialize();

	//### KDE4: workaround for Qt bug, remove later
	void resize (int width, int height);

protected slots:
	void slotConfigChanged();
	void slotRunCommand();
	void paletteChanged();
	void slotLaunchEmailClient();
	void slotLaunchBrowser();

protected:
	QRect sideImageRect();
	QMouseEvent translateMouseEvent( QMouseEvent* e);
	void resizeEvent(QResizeEvent *e);
	void paintEvent(QPaintEvent *);
	void mousePressEvent(QMouseEvent *e);
	void mouseReleaseEvent(QMouseEvent *e);
	void mouseMoveEvent(QMouseEvent *e);
	bool loadSidePixmap();
	void colorize(QImage& image);
	void getBrowser();
	void getDefaultBrowser();
	void getEmailClient();
	QString stripCommandArgs( QString command );
	void getDefaultEmailClient();
	void initPopup();
private:
	QMenuBar* m_parent;
	QPixmap            m_sidePixmap;
	QPixmap            m_sideTilePixmap;

	QString            m_browserName;
	QString            m_browserIcon;
	QString            m_browserExec;

	QString            m_emailName;
	QString            m_emailIcon;
	QString            m_emailExec;

};

#endif
