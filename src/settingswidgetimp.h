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

#ifndef __SETTINGSWIDGETIMP_H__
#define __SETTINGSWIDGETIMP_H__

#include "settings_ui.h"

class QCheckBox;
class QLineEdit;
class QPushButton;

class SettingsWidgetImp : public SettingsWidget
{
  Q_OBJECT

public:
  SettingsWidgetImp( QWidget* parent = 0, const char* name = 0, WFlags fl = 0 );
  ~SettingsWidgetImp();

public slots:
  virtual void          showDefaultBrowser_activated( int );
  virtual void          showDefaultEmailClient_activated( int );
  virtual void          showDesktopMenu_activated( int );
  virtual void          showActionsMenu_activated( int );
  virtual void          showProgramsMenu_activated( int );
  virtual void          useCustomEmailClient_toggled( bool );
  virtual void          useCustomBrowser_toggled( bool );
  virtual void          chooseCustomBrowser_clicked();
  virtual void          chooseCustomEmailClient_clicked();
};

#endif

