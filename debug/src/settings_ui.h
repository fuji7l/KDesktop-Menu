/****************************************************************************
** Form interface generated from reading ui file '/home/fuji/src/kdesktop_menu/src/settings_ui.ui'
**
** Created: Sun Jul 9 18:18:34 2006
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.6   edited Aug 31 2005 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef SETTINGSWIDGET_H
#define SETTINGSWIDGET_H

#include <qvariant.h>
#include <qwidget.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QTabWidget;
class QGroupBox;
class KColorButton;
class QLabel;
class KFontRequester;
class QComboBox;
class QLineEdit;
class QCheckBox;
class QPushButton;

class SettingsWidget : public QWidget
{
    Q_OBJECT

public:
    SettingsWidget( QWidget* parent = 0, const char* name = 0, WFlags fl = 0 );
    ~SettingsWidget();

    QTabWidget* tabs;
    QWidget* tab;
    QGroupBox* groupBox1;
    KColorButton* kcfg_MenuFontColour;
    QLabel* textLabel1;
    QLabel* textLabel5;
    KFontRequester* kcfg_MenuFont;
    QGroupBox* groupBox2;
    QLabel* textlabel2;
    QLabel* textLabel4;
    QLabel* textLabel3;
    QComboBox* kcfg_ShowActionsMenu;
    QComboBox* kcfg_ShowProgramsMenu;
    QLineEdit* kcfg_ProgramsName;
    QLineEdit* kcfg_ActionsName;
    QLineEdit* kcfg_DesktopName;
    QComboBox* kcfg_ShowDesktopMenu;
    QCheckBox* kcfg_ShowMenuIcon;
    QWidget* tab_2;
    QGroupBox* groupBox3;
    QCheckBox* kcfg_UseCustomEmailClient;
    QPushButton* chooseCustomEmailClient;
    QLineEdit* kcfg_CustomEmailClient;
    QComboBox* kcfg_ShowDefaultEmailClient;
    QLabel* textLabel1_2;
    QCheckBox* kcfg_UseTerminalCustomEmailClient;
    QGroupBox* groupBox4;
    QLabel* textLabel1_2_2;
    QCheckBox* kcfg_UseCustomBrowser;
    QPushButton* chooseCustomBrowser;
    QComboBox* kcfg_ShowDefaultBrowser;
    QLineEdit* kcfg_CustomBrowser;

public slots:
    virtual void chooseCustomEmailClient_clicked();
    virtual void chooseCustomBrowser_clicked();
    virtual void useCustomBrowser_toggled(bool);
    virtual void useCustomEmailClient_toggled(bool);
    virtual void showProgramsMenu_activated(int);
    virtual void showActionsMenu_activated(int);
    virtual void showDesktopMenu_activated(int);
    virtual void showDefaultEmailClient_activated(int);
    virtual void showDefaultBrowser_activated(int);

protected:
    QHBoxLayout* SettingsWidgetLayout;
    QVBoxLayout* tabLayout;
    QSpacerItem* spacer8_2_2_3_2;
    QSpacerItem* spacer8;
    QGridLayout* groupBox1Layout;
    QSpacerItem* spacer7;
    QSpacerItem* spacer6_2_3;
    QGridLayout* groupBox2Layout;
    QSpacerItem* spacer6_2;
    QSpacerItem* spacer6_2_2;
    QSpacerItem* spacer6_2_2_2;
    QGridLayout* tabLayout_2;
    QSpacerItem* spacer8_2;
    QSpacerItem* spacer8_2_2_3;
    QGridLayout* groupBox3Layout;
    QSpacerItem* spacer8_2_2_2;
    QSpacerItem* spacer8_2_2_3_3_3;
    QSpacerItem* spacer8_2_2_3_3;
    QGridLayout* groupBox4Layout;
    QSpacerItem* spacer8_2_2;
    QSpacerItem* spacer8_2_2_3_3_2;

protected slots:
    virtual void languageChange();

};

#endif // SETTINGSWIDGET_H
