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
#include <qlineedit.h>
#include <qcheckbox.h>
#include <qpushbutton.h>
#include <kdebug.h>
#include <kglobal.h>
#include <kurl.h>
#include <kopenwith.h>
#include <klocale.h>

#include "kicker_settings.h"
#include "settingswidgetimp.h"

SettingsWidgetImp::SettingsWidgetImp(QWidget* parent, const char* name, WFlags fl)
: SettingsWidget(parent,name,fl)
{
    if ( kcfg_UseCustomEmailClient->isChecked())
    {
        chooseCustomEmailClient->setEnabled( true );
        kcfg_CustomEmailClient->setEnabled( true );
        kcfg_UseTerminalCustomEmailClient->setEnabled( true );
    }

    if ( kcfg_UseCustomBrowser->isChecked() )
    {
        chooseCustomBrowser->setEnabled( true );
        kcfg_CustomBrowser->setEnabled( true );
    }
}

SettingsWidgetImp::~SettingsWidgetImp()
{
}

void SettingsWidgetImp::chooseCustomEmailClient_clicked()
{
    KURL::List urlList;
    KOpenWithDlg dlg( urlList, i18n("Select preferred email client:"),
                      QString::null, this );
    // hide "Do not &close when command exits" here, we don't need it for a mail client
    dlg.hideNoCloseOnExit();
    if (dlg.exec() != QDialog::Accepted)
    {
        return;
    }

    QString client = dlg.text();

    // handle a custom terminal application.
    KConfigGroup confGroup( KGlobal::config(), QString::fromLatin1("General") );
    QString preferredTerminal = confGroup.readPathEntry("TerminalApplication",
                                                QString::fromLatin1("konsole"));
    preferredTerminal += QString::fromLatin1(" -e ");
    int len = preferredTerminal.length();

    bool b = client.left(len) == preferredTerminal;
    if (b)
    {
        client = client.mid(len);
    }

    if ( !client.isEmpty() )
    {
        kcfg_UseTerminalCustomEmailClient->setChecked( b );
        kcfg_CustomEmailClient->setText( client );
    }
}

void SettingsWidgetImp::chooseCustomBrowser_clicked()
{
    KURL::List urlList;
    KOpenWithDlg dlg(urlList, i18n("Select preferred web browser:"), QString::null, this);

    dlg.hideRunInTerminal();
    dlg.hideNoCloseOnExit();
    if (dlg.exec() != QDialog::Accepted)
    {
        return;
    }

    QString client = dlg.text();
    kcfg_CustomBrowser->setText( client );
}

void SettingsWidgetImp::useCustomBrowser_toggled(bool checked)
{
    chooseCustomBrowser->setEnabled( checked );
    kcfg_CustomBrowser->setEnabled( checked );
}

void SettingsWidgetImp::useCustomEmailClient_toggled(bool checked)
{
    chooseCustomEmailClient->setEnabled( checked );
    kcfg_CustomEmailClient->setEnabled( checked );
    kcfg_UseTerminalCustomEmailClient->setEnabled( checked );
}

void SettingsWidgetImp::showProgramsMenu_activated(int enabled)
{
    if (enabled == 0)
    {
        kcfg_ProgramsName->setDisabled( true );
    }
    else
    {
        kcfg_ProgramsName->setDisabled( false );
    }
}

void SettingsWidgetImp::showActionsMenu_activated(int enabled)
{
    if (enabled == 0)
    {
        kcfg_ActionsName->setDisabled( true );
    }
    else
    {
        kcfg_ActionsName->setDisabled( false );
    }
}

void SettingsWidgetImp::showDesktopMenu_activated(int enabled)
{
    if (enabled == 0)
    {
        kcfg_DesktopName->setDisabled( true );
    }
    else
    {
        kcfg_DesktopName->setDisabled( false );
    }
}

void SettingsWidgetImp::showDefaultEmailClient_activated(int enabled)
{
    if (enabled == 0)
    {
        kcfg_UseCustomEmailClient->setDisabled( true );
    }
    else
    {
        kcfg_UseCustomEmailClient->setDisabled( false );
    }
}

void SettingsWidgetImp::showDefaultBrowser_activated(int enabled)
{
    if (enabled == 0)
    {
        kcfg_UseCustomBrowser->setDisabled( true );
    }
    else
    {
        kcfg_UseCustomBrowser->setDisabled( false );
    }
}

#include "settingswidgetimp.moc"
