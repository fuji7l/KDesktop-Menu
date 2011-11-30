#include <kdialog.h>
#include <klocale.h>
/****************************************************************************
** Form implementation generated from reading ui file '/home/fuji/src/kdesktop_menu/src/settings_ui.ui'
**
** Created: Sun Jul 9 18:20:47 2006
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.6   edited Aug 31 2005 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "settings_ui.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qtabwidget.h>
#include <qgroupbox.h>
#include <kcolorbutton.h>
#include <qlabel.h>
#include <kfontrequester.h>
#include <qcombobox.h>
#include <qlineedit.h>
#include <qcheckbox.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>

/*
 *  Constructs a SettingsWidget as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
SettingsWidget::SettingsWidget( QWidget* parent, const char* name, WFlags fl )
    : QWidget( parent, name, fl )
{
    if ( !name )
	setName( "SettingsWidget" );
    SettingsWidgetLayout = new QHBoxLayout( this, 0, KDialog::spacingHint(), "SettingsWidgetLayout"); 

    tabs = new QTabWidget( this, "tabs" );

    tab = new QWidget( tabs, "tab" );
    tabLayout = new QVBoxLayout( tab, KDialog::marginHint(), KDialog::spacingHint(), "tabLayout"); 

    groupBox1 = new QGroupBox( tab, "groupBox1" );
    groupBox1->setColumnLayout(0, Qt::Vertical );
    groupBox1->layout()->setSpacing( KDialog::spacingHint() );
    groupBox1->layout()->setMargin( KDialog::marginHint() );
    groupBox1Layout = new QGridLayout( groupBox1->layout() );
    groupBox1Layout->setAlignment( Qt::AlignTop );

    kcfg_MenuFontColour = new KColorButton( groupBox1, "kcfg_MenuFontColour" );

    groupBox1Layout->addWidget( kcfg_MenuFontColour, 0, 1 );
    spacer7 = new QSpacerItem( 300, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    groupBox1Layout->addItem( spacer7, 0, 2 );

    textLabel1 = new QLabel( groupBox1, "textLabel1" );

    groupBox1Layout->addWidget( textLabel1, 0, 0 );

    textLabel5 = new QLabel( groupBox1, "textLabel5" );

    groupBox1Layout->addWidget( textLabel5, 2, 0 );

    kcfg_MenuFont = new KFontRequester( groupBox1, "kcfg_MenuFont" );

    groupBox1Layout->addMultiCellWidget( kcfg_MenuFont, 2, 2, 1, 2 );
    spacer6_2_3 = new QSpacerItem( 20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed );
    groupBox1Layout->addItem( spacer6_2_3, 1, 1 );
    tabLayout->addWidget( groupBox1 );
    spacer8_2_2_3_2 = new QSpacerItem( 16, 16, QSizePolicy::Minimum, QSizePolicy::Fixed );
    tabLayout->addItem( spacer8_2_2_3_2 );

    groupBox2 = new QGroupBox( tab, "groupBox2" );
    groupBox2->setColumnLayout(0, Qt::Vertical );
    groupBox2->layout()->setSpacing( KDialog::spacingHint() );
    groupBox2->layout()->setMargin( KDialog::marginHint() );
    groupBox2Layout = new QGridLayout( groupBox2->layout() );
    groupBox2Layout->setAlignment( Qt::AlignTop );

    textlabel2 = new QLabel( groupBox2, "textlabel2" );

    groupBox2Layout->addWidget( textlabel2, 0, 0 );

    textLabel4 = new QLabel( groupBox2, "textLabel4" );

    groupBox2Layout->addWidget( textLabel4, 4, 0 );

    textLabel3 = new QLabel( groupBox2, "textLabel3" );

    groupBox2Layout->addWidget( textLabel3, 2, 0 );
    spacer6_2 = new QSpacerItem( 20, 16, QSizePolicy::Minimum, QSizePolicy::Fixed );
    groupBox2Layout->addItem( spacer6_2, 1, 2 );

    kcfg_ShowActionsMenu = new QComboBox( FALSE, groupBox2, "kcfg_ShowActionsMenu" );

    groupBox2Layout->addWidget( kcfg_ShowActionsMenu, 2, 3 );

    kcfg_ShowProgramsMenu = new QComboBox( FALSE, groupBox2, "kcfg_ShowProgramsMenu" );

    groupBox2Layout->addWidget( kcfg_ShowProgramsMenu, 0, 3 );

    kcfg_ProgramsName = new QLineEdit( groupBox2, "kcfg_ProgramsName" );

    groupBox2Layout->addMultiCellWidget( kcfg_ProgramsName, 0, 0, 1, 2 );

    kcfg_ActionsName = new QLineEdit( groupBox2, "kcfg_ActionsName" );

    groupBox2Layout->addMultiCellWidget( kcfg_ActionsName, 2, 2, 1, 2 );

    kcfg_DesktopName = new QLineEdit( groupBox2, "kcfg_DesktopName" );

    groupBox2Layout->addMultiCellWidget( kcfg_DesktopName, 4, 4, 1, 2 );

    kcfg_ShowDesktopMenu = new QComboBox( FALSE, groupBox2, "kcfg_ShowDesktopMenu" );

    groupBox2Layout->addWidget( kcfg_ShowDesktopMenu, 4, 3 );
    spacer6_2_2 = new QSpacerItem( 20, 16, QSizePolicy::Minimum, QSizePolicy::Fixed );
    groupBox2Layout->addItem( spacer6_2_2, 3, 2 );
    spacer6_2_2_2 = new QSpacerItem( 20, 16, QSizePolicy::Minimum, QSizePolicy::Fixed );
    groupBox2Layout->addItem( spacer6_2_2_2, 5, 1 );

    kcfg_ShowMenuIcon = new QCheckBox( groupBox2, "kcfg_ShowMenuIcon" );

    groupBox2Layout->addMultiCellWidget( kcfg_ShowMenuIcon, 6, 6, 0, 2 );
    tabLayout->addWidget( groupBox2 );
    spacer8 = new QSpacerItem( 20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding );
    tabLayout->addItem( spacer8 );
    tabs->insertTab( tab, QString::fromLatin1("") );

    tab_2 = new QWidget( tabs, "tab_2" );
    tabLayout_2 = new QGridLayout( tab_2, 1, 1, KDialog::marginHint(), KDialog::spacingHint(), "tabLayout_2"); 
    spacer8_2 = new QSpacerItem( 20, 300, QSizePolicy::Minimum, QSizePolicy::Expanding );
    tabLayout_2->addItem( spacer8_2, 3, 1 );
    spacer8_2_2_3 = new QSpacerItem( 20, 16, QSizePolicy::Minimum, QSizePolicy::Fixed );
    tabLayout_2->addItem( spacer8_2_2_3, 1, 0 );

    groupBox3 = new QGroupBox( tab_2, "groupBox3" );
    groupBox3->setColumnLayout(0, Qt::Vertical );
    groupBox3->layout()->setSpacing( KDialog::spacingHint() );
    groupBox3->layout()->setMargin( KDialog::marginHint() );
    groupBox3Layout = new QGridLayout( groupBox3->layout() );
    groupBox3Layout->setAlignment( Qt::AlignTop );
    spacer8_2_2_2 = new QSpacerItem( 20, 16, QSizePolicy::Minimum, QSizePolicy::Fixed );
    groupBox3Layout->addItem( spacer8_2_2_2, 1, 1 );

    kcfg_UseCustomEmailClient = new QCheckBox( groupBox3, "kcfg_UseCustomEmailClient" );

    groupBox3Layout->addMultiCellWidget( kcfg_UseCustomEmailClient, 2, 2, 0, 1 );

    chooseCustomEmailClient = new QPushButton( groupBox3, "chooseCustomEmailClient" );
    chooseCustomEmailClient->setEnabled( FALSE );

    groupBox3Layout->addWidget( chooseCustomEmailClient, 3, 2 );

    kcfg_CustomEmailClient = new QLineEdit( groupBox3, "kcfg_CustomEmailClient" );
    kcfg_CustomEmailClient->setEnabled( FALSE );

    groupBox3Layout->addWidget( kcfg_CustomEmailClient, 3, 1 );
    spacer8_2_2_3_3_3 = new QSpacerItem( 25, 16, QSizePolicy::Fixed, QSizePolicy::Minimum );
    groupBox3Layout->addItem( spacer8_2_2_3_3_3, 4, 0 );
    spacer8_2_2_3_3 = new QSpacerItem( 25, 16, QSizePolicy::Fixed, QSizePolicy::Minimum );
    groupBox3Layout->addItem( spacer8_2_2_3_3, 3, 0 );

    kcfg_ShowDefaultEmailClient = new QComboBox( FALSE, groupBox3, "kcfg_ShowDefaultEmailClient" );

    groupBox3Layout->addWidget( kcfg_ShowDefaultEmailClient, 0, 2 );

    textLabel1_2 = new QLabel( groupBox3, "textLabel1_2" );

    groupBox3Layout->addMultiCellWidget( textLabel1_2, 0, 0, 0, 1 );

    kcfg_UseTerminalCustomEmailClient = new QCheckBox( groupBox3, "kcfg_UseTerminalCustomEmailClient" );
    kcfg_UseTerminalCustomEmailClient->setEnabled( FALSE );

    groupBox3Layout->addMultiCellWidget( kcfg_UseTerminalCustomEmailClient, 4, 4, 1, 2 );

    tabLayout_2->addMultiCellWidget( groupBox3, 0, 0, 0, 1 );

    groupBox4 = new QGroupBox( tab_2, "groupBox4" );
    groupBox4->setColumnLayout(0, Qt::Vertical );
    groupBox4->layout()->setSpacing( KDialog::spacingHint() );
    groupBox4->layout()->setMargin( KDialog::marginHint() );
    groupBox4Layout = new QGridLayout( groupBox4->layout() );
    groupBox4Layout->setAlignment( Qt::AlignTop );

    textLabel1_2_2 = new QLabel( groupBox4, "textLabel1_2_2" );

    groupBox4Layout->addMultiCellWidget( textLabel1_2_2, 0, 0, 0, 1 );
    spacer8_2_2 = new QSpacerItem( 20, 16, QSizePolicy::Minimum, QSizePolicy::Fixed );
    groupBox4Layout->addItem( spacer8_2_2, 1, 1 );

    kcfg_UseCustomBrowser = new QCheckBox( groupBox4, "kcfg_UseCustomBrowser" );

    groupBox4Layout->addMultiCellWidget( kcfg_UseCustomBrowser, 2, 2, 0, 2 );

    chooseCustomBrowser = new QPushButton( groupBox4, "chooseCustomBrowser" );
    chooseCustomBrowser->setEnabled( FALSE );

    groupBox4Layout->addWidget( chooseCustomBrowser, 3, 2 );

    kcfg_ShowDefaultBrowser = new QComboBox( FALSE, groupBox4, "kcfg_ShowDefaultBrowser" );

    groupBox4Layout->addWidget( kcfg_ShowDefaultBrowser, 0, 2 );
    spacer8_2_2_3_3_2 = new QSpacerItem( 25, 16, QSizePolicy::Fixed, QSizePolicy::Minimum );
    groupBox4Layout->addItem( spacer8_2_2_3_3_2, 3, 0 );

    kcfg_CustomBrowser = new QLineEdit( groupBox4, "kcfg_CustomBrowser" );
    kcfg_CustomBrowser->setEnabled( FALSE );

    groupBox4Layout->addWidget( kcfg_CustomBrowser, 3, 1 );

    tabLayout_2->addMultiCellWidget( groupBox4, 2, 2, 0, 1 );
    tabs->insertTab( tab_2, QString::fromLatin1("") );
    SettingsWidgetLayout->addWidget( tabs );
    languageChange();
    resize( QSize(335, 478).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );

    // signals and slots connections
    connect( chooseCustomEmailClient, SIGNAL( clicked() ), this, SLOT( chooseCustomEmailClient_clicked() ) );
    connect( chooseCustomBrowser, SIGNAL( clicked() ), this, SLOT( chooseCustomBrowser_clicked() ) );
    connect( kcfg_UseCustomBrowser, SIGNAL( toggled(bool) ), this, SLOT( useCustomBrowser_toggled(bool) ) );
    connect( kcfg_UseCustomEmailClient, SIGNAL( toggled(bool) ), this, SLOT( useCustomEmailClient_toggled(bool) ) );

    // tab order
    setTabOrder( tabs, kcfg_MenuFontColour );
    setTabOrder( kcfg_MenuFontColour, kcfg_MenuFont );
    setTabOrder( kcfg_MenuFont, kcfg_ProgramsName );
    setTabOrder( kcfg_ProgramsName, kcfg_ShowProgramsMenu );
    setTabOrder( kcfg_ShowProgramsMenu, kcfg_ActionsName );
    setTabOrder( kcfg_ActionsName, kcfg_ShowActionsMenu );
    setTabOrder( kcfg_ShowActionsMenu, kcfg_DesktopName );
    setTabOrder( kcfg_DesktopName, kcfg_ShowDesktopMenu );
    setTabOrder( kcfg_ShowDesktopMenu, kcfg_ShowMenuIcon );
    setTabOrder( kcfg_ShowMenuIcon, kcfg_ShowDefaultEmailClient );
    setTabOrder( kcfg_ShowDefaultEmailClient, kcfg_UseCustomEmailClient );
    setTabOrder( kcfg_UseCustomEmailClient, kcfg_CustomEmailClient );
    setTabOrder( kcfg_CustomEmailClient, chooseCustomEmailClient );
    setTabOrder( chooseCustomEmailClient, kcfg_UseTerminalCustomEmailClient );
    setTabOrder( kcfg_UseTerminalCustomEmailClient, kcfg_ShowDefaultBrowser );
    setTabOrder( kcfg_ShowDefaultBrowser, kcfg_UseCustomBrowser );
    setTabOrder( kcfg_UseCustomBrowser, kcfg_CustomBrowser );
    setTabOrder( kcfg_CustomBrowser, chooseCustomBrowser );
}

/*
 *  Destroys the object and frees any allocated resources
 */
SettingsWidget::~SettingsWidget()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void SettingsWidget::languageChange()
{
    setCaption( tr2i18n( "SettingsWidget" ) );
    groupBox1->setTitle( tr2i18n( "Menu Font" ) );
    QWhatsThis::add( groupBox1, tr2i18n( "These options allow you to change the default font options used to display the main menus." ) );
    kcfg_MenuFontColour->setText( QString::null );
    textLabel1->setText( tr2i18n( "Color:" ) );
    QToolTip::add( textLabel1, tr2i18n( "The colour used for the menu's text." ) );
    textLabel5->setText( tr2i18n( "Font:" ) );
    QToolTip::add( textLabel5, tr2i18n( "Choose the font settings to be used for  the menu" ) );
    groupBox2->setTitle( tr2i18n( "Main Menus" ) );
    QWhatsThis::add( groupBox2, tr2i18n( "These text boxes allow you to change the default text for the main menu headings into something more personal." ) );
    textlabel2->setText( tr2i18n( "Programs:" ) );
    QToolTip::add( textlabel2, tr2i18n( "You may enter a new name to be used for the \"Programs\" menu.  You may also disable this menu so that it does not appear." ) );
    textLabel4->setText( tr2i18n( "Desktop:" ) );
    QToolTip::add( textLabel4, tr2i18n( "You may enter a new name for the \"Desktop\" menu.  You may also disable this menu so that it does not appear." ) );
    textLabel3->setText( tr2i18n( "Actions:" ) );
    QToolTip::add( textLabel3, tr2i18n( "You may enter a new name for the \"Actions\" menu.  You may also disable this menu so that it does not appear." ) );
    kcfg_ShowActionsMenu->clear();
    kcfg_ShowActionsMenu->insertItem( tr2i18n( "Disabled" ) );
    kcfg_ShowActionsMenu->insertItem( tr2i18n( "Enabled" ) );
    kcfg_ShowProgramsMenu->clear();
    kcfg_ShowProgramsMenu->insertItem( tr2i18n( "Disabled" ) );
    kcfg_ShowProgramsMenu->insertItem( tr2i18n( "Enabled" ) );
    kcfg_ShowDesktopMenu->clear();
    kcfg_ShowDesktopMenu->insertItem( tr2i18n( "Disabled" ) );
    kcfg_ShowDesktopMenu->insertItem( tr2i18n( "Enabled" ) );
    kcfg_ShowMenuIcon->setText( tr2i18n( "Enable &KMenu Icon" ) );
    kcfg_ShowMenuIcon->setAccel( QKeySequence( tr2i18n( "Alt+K" ) ) );
    QToolTip::add( kcfg_ShowMenuIcon, tr2i18n( "Disables the KMenu Icon" ) );
    QWhatsThis::add( kcfg_ShowMenuIcon, tr2i18n( "If you place your menu in the left corner, the KMenu Icon will not allow you to just throw your mouse into the corner to access the Programs menu.  By disabling or hiding the menu, you will be able to do this." ) );
    tabs->changeTab( tab, tr2i18n( "&Appearance" ) );
    groupBox3->setTitle( tr2i18n( "Email &Client" ) );
    kcfg_UseCustomEmailClient->setText( tr2i18n( "Use custom &email application" ) );
    kcfg_UseCustomEmailClient->setAccel( QKeySequence( tr2i18n( "Alt+E" ) ) );
    QToolTip::add( kcfg_UseCustomEmailClient, tr2i18n( "This allows you to choose an email \\n application to be associated with the email menu item but does not change your default email client settings.  This would be useful if you use Kontact." ) );
    QWhatsThis::add( kcfg_UseCustomEmailClient, tr2i18n( "This allows you to choose a different email client to be associated with the email menu item in the Programs menu.  Unlike the component chooser in Kcontrol, this option does <b>not</b> change your system wide default email client.\n"
"\n"
"This option would be useful if you use Kontact." ) );
    chooseCustomEmailClient->setText( tr2i18n( "Choose..." ) );
    chooseCustomEmailClient->setAccel( QKeySequence( QString::null ) );
    kcfg_ShowDefaultEmailClient->clear();
    kcfg_ShowDefaultEmailClient->insertItem( tr2i18n( "Disabled" ) );
    kcfg_ShowDefaultEmailClient->insertItem( tr2i18n( "Enabled" ) );
    textLabel1_2->setText( tr2i18n( "Dynamic email menu item:" ) );
    QToolTip::add( textLabel1_2, tr2i18n( "Enables a special menu item that dynamically points to your KDE system's default email client." ) );
    QWhatsThis::add( textLabel1_2, tr2i18n( "Enables a special menu item that dynamically points to your KDE system's default email client." ) );
    kcfg_UseTerminalCustomEmailClient->setText( tr2i18n( "Run in terminal" ) );
    kcfg_UseTerminalCustomEmailClient->setAccel( QKeySequence( QString::null ) );
    QToolTip::add( kcfg_UseTerminalCustomEmailClient, tr2i18n( "Run the selected email client in a terminal." ) );
    groupBox4->setTitle( tr2i18n( "&Web Browser" ) );
    textLabel1_2_2->setText( tr2i18n( "Dynamic browser menu item:" ) );
    QToolTip::add( textLabel1_2_2, tr2i18n( "Enables a special menu item that dynamically points to your KDE system's default web browser." ) );
    QWhatsThis::add( textLabel1_2_2, tr2i18n( "Enables a special menu item that dynamically points to your KDE system's default web browser." ) );
    kcfg_UseCustomBrowser->setText( tr2i18n( "Use custom &browser application" ) );
    kcfg_UseCustomBrowser->setAccel( QKeySequence( tr2i18n( "Alt+B" ) ) );
    QToolTip::add( kcfg_UseCustomBrowser, tr2i18n( "This allows you to choose a web browser to be associated with the browser menu item but does not change your default web browser." ) );
    QWhatsThis::add( kcfg_UseCustomBrowser, tr2i18n( "This allows you to choose a different web browser to be associated with the browser menu item in the Programs menu.  Unlike the component chooser in Kcontrol, this option does <b>not</b> change your system wide default web browser." ) );
    chooseCustomBrowser->setText( tr2i18n( "Choose..." ) );
    chooseCustomBrowser->setAccel( QKeySequence( QString::null ) );
    kcfg_ShowDefaultBrowser->clear();
    kcfg_ShowDefaultBrowser->insertItem( tr2i18n( "Disabled" ) );
    kcfg_ShowDefaultBrowser->insertItem( tr2i18n( "Enabled" ) );
    tabs->changeTab( tab_2, tr2i18n( "Default Pro&grams" ) );
}

void SettingsWidget::chooseCustomEmailClient_clicked()
{
    qWarning( "SettingsWidget::chooseCustomEmailClient_clicked(): Not implemented yet" );
}

void SettingsWidget::chooseCustomBrowser_clicked()
{
    qWarning( "SettingsWidget::chooseCustomBrowser_clicked(): Not implemented yet" );
}

void SettingsWidget::useCustomBrowser_toggled(bool)
{
    qWarning( "SettingsWidget::useCustomBrowser_toggled(bool): Not implemented yet" );
}

void SettingsWidget::useCustomEmailClient_toggled(bool)
{
    qWarning( "SettingsWidget::useCustomEmailClient_toggled(bool): Not implemented yet" );
}

void SettingsWidget::showProgramsMenu_activated(int)
{
    qWarning( "SettingsWidget::showProgramsMenu_activated(int): Not implemented yet" );
}

void SettingsWidget::showActionsMenu_activated(int)
{
    qWarning( "SettingsWidget::showActionsMenu_activated(int): Not implemented yet" );
}

void SettingsWidget::showDesktopMenu_activated(int)
{
    qWarning( "SettingsWidget::showDesktopMenu_activated(int): Not implemented yet" );
}

void SettingsWidget::showDefaultEmailClient_activated(int)
{
    qWarning( "SettingsWidget::showDefaultEmailClient_activated(int): Not implemented yet" );
}

void SettingsWidget::showDefaultBrowser_activated(int)
{
    qWarning( "SettingsWidget::showDefaultBrowser_activated(int): Not implemented yet" );
}

#include "settings_ui.moc"
