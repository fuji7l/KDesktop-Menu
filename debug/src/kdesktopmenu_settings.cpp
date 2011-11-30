// This file is generated by kconfig_compiler from kdesktopmenu_settings.kcfg.
// All changes you do to this file will be lost.

#include "kdesktopmenu_settings.h"

#include <kstaticdeleter.h>

KDesktopMenuSettings *KDesktopMenuSettings::mSelf = 0;
static KStaticDeleter<KDesktopMenuSettings> staticKDesktopMenuSettingsDeleter;

KDesktopMenuSettings *KDesktopMenuSettings::self()
{
  if ( !mSelf ) {
    staticKDesktopMenuSettingsDeleter.setObject( mSelf, new KDesktopMenuSettings() );
    mSelf->readConfig();
  }

  return mSelf;
}

KDesktopMenuSettings::KDesktopMenuSettings(  )
  : KConfigSkeleton( QString::fromLatin1( "kdesktop_menurc" ) )
{
  mSelf = this;
  setCurrentGroup( QString::fromLatin1( "General" ) );

  KConfigSkeleton::ItemFont  *itemMenuFont;
  itemMenuFont = new KConfigSkeleton::ItemFont( currentGroup(), QString::fromLatin1( "MenuFont" ), mMenuFont, KGlobalSettings::menuFont() );
  addItem( itemMenuFont, QString::fromLatin1( "MenuFont" ) );
  KConfigSkeleton::ItemColor  *itemMenuFontColour;
  itemMenuFontColour = new KConfigSkeleton::ItemColor( currentGroup(), QString::fromLatin1( "MenuFontColour" ), mMenuFontColour, QColor( 0,0,0 ) );
  addItem( itemMenuFontColour, QString::fromLatin1( "MenuFontColour" ) );
  KConfigSkeleton::ItemBool  *itemShowMenuIcon;
  itemShowMenuIcon = new KConfigSkeleton::ItemBool( currentGroup(), QString::fromLatin1( "ShowMenuIcon" ), mShowMenuIcon, true );
  addItem( itemShowMenuIcon, QString::fromLatin1( "ShowMenuIcon" ) );

  setCurrentGroup( QString::fromLatin1( "Root Menus" ) );

  KConfigSkeleton::ItemString  *itemProgramsName;
  itemProgramsName = new KConfigSkeleton::ItemString( currentGroup(), QString::fromLatin1( "ProgramsName" ), mProgramsName, QString::fromLatin1( "Programs" ) );
  addItem( itemProgramsName, QString::fromLatin1( "ProgramsName" ) );
  KConfigSkeleton::ItemString  *itemActionsName;
  itemActionsName = new KConfigSkeleton::ItemString( currentGroup(), QString::fromLatin1( "ActionsName" ), mActionsName, QString::fromLatin1( "Actions" ) );
  addItem( itemActionsName, QString::fromLatin1( "ActionsName" ) );
  KConfigSkeleton::ItemString  *itemDesktopName;
  itemDesktopName = new KConfigSkeleton::ItemString( currentGroup(), QString::fromLatin1( "DesktopName" ), mDesktopName, QString::fromLatin1( "Desktop" ) );
  addItem( itemDesktopName, QString::fromLatin1( "DesktopName" ) );
  KConfigSkeleton::ItemBool  *itemShowProgramsMenu;
  itemShowProgramsMenu = new KConfigSkeleton::ItemBool( currentGroup(), QString::fromLatin1( "ShowProgramsMenu" ), mShowProgramsMenu, true );
  addItem( itemShowProgramsMenu, QString::fromLatin1( "ShowProgramsMenu" ) );
  KConfigSkeleton::ItemBool  *itemShowActionsMenu;
  itemShowActionsMenu = new KConfigSkeleton::ItemBool( currentGroup(), QString::fromLatin1( "ShowActionsMenu" ), mShowActionsMenu, true );
  addItem( itemShowActionsMenu, QString::fromLatin1( "ShowActionsMenu" ) );
  KConfigSkeleton::ItemBool  *itemShowDesktopMenu;
  itemShowDesktopMenu = new KConfigSkeleton::ItemBool( currentGroup(), QString::fromLatin1( "ShowDesktopMenu" ), mShowDesktopMenu, true );
  addItem( itemShowDesktopMenu, QString::fromLatin1( "ShowDesktopMenu" ) );

  setCurrentGroup( QString::fromLatin1( "Menu Items" ) );

  KConfigSkeleton::ItemBool  *itemShowDefaultEmailClient;
  itemShowDefaultEmailClient = new KConfigSkeleton::ItemBool( currentGroup(), QString::fromLatin1( "ShowDefaultEmailClient" ), mShowDefaultEmailClient, true );
  addItem( itemShowDefaultEmailClient, QString::fromLatin1( "ShowDefaultEmailClient" ) );
  KConfigSkeleton::ItemBool  *itemUseCustomEmailClient;
  itemUseCustomEmailClient = new KConfigSkeleton::ItemBool( currentGroup(), QString::fromLatin1( "UseCustomEmailClient" ), mUseCustomEmailClient, false );
  addItem( itemUseCustomEmailClient, QString::fromLatin1( "UseCustomEmailClient" ) );
  KConfigSkeleton::ItemString  *itemCustomEmailClient;
  itemCustomEmailClient = new KConfigSkeleton::ItemString( currentGroup(), QString::fromLatin1( "CustomEmailClient" ), mCustomEmailClient );
  addItem( itemCustomEmailClient, QString::fromLatin1( "CustomEmailClient" ) );
  KConfigSkeleton::ItemBool  *itemUseTerminalCustomEmailClient;
  itemUseTerminalCustomEmailClient = new KConfigSkeleton::ItemBool( currentGroup(), QString::fromLatin1( "UseTerminalCustomEmailClient" ), mUseTerminalCustomEmailClient, false );
  addItem( itemUseTerminalCustomEmailClient, QString::fromLatin1( "UseTerminalCustomEmailClient" ) );
  KConfigSkeleton::ItemBool  *itemShowDefaultBrowser;
  itemShowDefaultBrowser = new KConfigSkeleton::ItemBool( currentGroup(), QString::fromLatin1( "ShowDefaultBrowser" ), mShowDefaultBrowser, true );
  addItem( itemShowDefaultBrowser, QString::fromLatin1( "ShowDefaultBrowser" ) );
  KConfigSkeleton::ItemBool  *itemUseCustomBrowser;
  itemUseCustomBrowser = new KConfigSkeleton::ItemBool( currentGroup(), QString::fromLatin1( "UseCustomBrowser" ), mUseCustomBrowser, false );
  addItem( itemUseCustomBrowser, QString::fromLatin1( "UseCustomBrowser" ) );
  KConfigSkeleton::ItemString  *itemCustomBrowser;
  itemCustomBrowser = new KConfigSkeleton::ItemString( currentGroup(), QString::fromLatin1( "CustomBrowser" ), mCustomBrowser );
  addItem( itemCustomBrowser, QString::fromLatin1( "CustomBrowser" ) );
}

KDesktopMenuSettings::~KDesktopMenuSettings()
{
  if ( mSelf == this )
    staticKDesktopMenuSettingsDeleter.setObject( mSelf, 0, false );
}
