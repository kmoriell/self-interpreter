#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include <gtkmm.h>
#include <gdkmm/color.h>
#include <iostream>
#include <unistd.h>
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
	Glib::RefPtr<Gtk::ListStore> m_refTreeModel;
	ColumnRecord m_Columns;

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
	void populateTreeView();
        void on_button_clicked();
	Morph &morph;
	ProxyServer &proxyServer;
public:
	MainWindow(Morph &morph, ProxyServer &proxyServer);
	~MainWindow();
	Gtk::Window *getWindow();
};

#endif /* MAINWINDOW_H_ */
