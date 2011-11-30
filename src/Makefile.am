INCLUDES= $(all_includes)
METASOURCES = AUTO

lib_LTLIBRARIES = kdesktop_menu_panelapplet.la

kdesktop_menu_panelapplet_la_SOURCES = kdesktop_menu.cpp menu_programs.cpp \
		kicker_settings.cpp menu_actions.cpp menu_desktop.cpp menu_services.cpp 	menu_client.cpp \
	menuinfo.cpp dmctl.cpp settings_ui.ui browser_mnu.cpp 	kdesktopmenu_settings.kcfgc \
	settingswidgetimp.cpp menu_media.cpp
kdesktop_menu_panelapplet_la_LDFLAGS = -module -avoid-version $(all_libraries)
kdesktop_menu_panelapplet_la_LIBADD = $(LIB_KDEUI) 

kdesktop_menu_DATA = kdesktop_menu.desktop
kdesktop_menudir = $(kde_datadir)/kicker/applets

messages: rc.cpp
	$(EXTRACTRC) `find . -name \*.ui -o -name \*.rc` > rc.cpp
	$(XGETTEXT) *.cpp -o $(podir)/kdesktop_menu.pot
noinst_HEADERS = menu_programs.h menu_services.h kicker_settings.h \
		menu_actions.h menu_desktop.h menu_client.h menuinfo.h dmctl.h 	browser_mnu.h \
	settingswidgetimp.h menu_media.h

kde_kcfg_DATA = kdesktopmenu_settings.kcfg
