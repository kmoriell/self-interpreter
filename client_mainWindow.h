#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include <gtkmm-3.0/gtkmm.h>
#include <iostream>
#include "client_columnRecord.h"
#include "client_morph.h"
#include "client_proxyServer.h"

class MainWindow : public Gtk::Window {
private:
	Glib::RefPtr<Gtk::Builder> refBuilder;
	Gtk::Window *pWindow = nullptr;
	Gtk::Entry *pText = nullptr;
	Gtk::Button *pButton = nullptr;
  	Gtk::TreeView *pTreeView = nullptr;
	Gtk::TextView *pTextView = nullptr;
	Gtk::Label *pLabel = nullptr;
	Glib::RefPtr<Gtk::ListStore> m_refTreeModel;
	ColumnRecord m_Columns;
	Gtk::Menu m_Menu_Popup;

	// Columnas y celdas
	Gtk::TreeViewColumn colSlotName;
	Gtk::TreeViewColumn colMutable;
	Gtk::TreeViewColumn colObjName;
	Gtk::TreeViewColumn colPreview;
	
	Gtk::CellRendererText colSlotNameCell;
	Gtk::CellRendererToggle colMutableCell;
	Gtk::CellRendererText colPreviewCell;
	Gtk::CellRendererText colObjNameCell;

	void addWidgets();
	void configureTreeView();
	void drawMorph();
	void generatePopup();
        void on_button_clicked();
	void on_menu_file_popup_generic();
	bool on_button_press_event(GdkEventButton* button_event);
	void on_row_activated(const Gtk::TreeModel::Path& path, Gtk::TreeViewColumn* column);
	Morph &morph;
	ProxyServer &proxyServer;
public:
	MainWindow(Morph &morph, ProxyServer &proxyServer);
	~MainWindow();
	Gtk::Window *getWindow();
};

#endif /* MAINWINDOW_H_ */
