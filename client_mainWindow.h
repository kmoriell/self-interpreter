#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include <gtkmm-3.0/gtkmm.h>
#include <gdkmm/color.h>
#include <iostream>
#include <fstream>
#include "client_columnRecord.h"
#include "client_morph.h"
#include "client_proxyServer.h"

class MainWindow : public Gtk::Window {
 private:
  Glib::RefPtr<Gtk::Builder> refBuilder;

  Gtk::Window *pWindow = nullptr;

  // Botones
  Gtk::Button *pBtnLobby = nullptr;
  Gtk::Button *pBtnGoBack = nullptr;
  Gtk::Button *pBtnRefresh = nullptr;
  Gtk::Button *pBtnEnviar = nullptr;
  Gtk::Button *pBtnApply = nullptr;
  Gtk::Button *pBtnSetSlot = nullptr;
  Gtk::Button *pBtnSetCodeSegment = nullptr;

  // Cajas de texto
  Gtk::TextView *pTxtEntrada = nullptr;
  Gtk::TextView *pTxtCodeSegment = nullptr;
  Gtk::Entry *pTxtObjName = nullptr;
  Gtk::Entry *pTxtSlot = nullptr;

  //Boxes
  //Gtk::Box *pBoxObject = nullptr;

  Gtk::TreeView *pTreeView = nullptr;
  //Gtk::MenuButton *pMenuButton = nullptr;
  Glib::RefPtr<Gtk::ListStore> m_refTreeModel;
  ColumnRecord m_Columns;
  //Gtk::Menu m_Menu_Popup;

  // Menu
  Gtk::MenuItem *pMenuItemOpen = nullptr;
  //Gtk::MenuItem *pMenuItemExit = nullptr;

  // Cuadro de dialogo abrir

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

  // Eventos
  void btnLobby_clicked();
  void btnGoBack_clicked();
  void btnRefresh_clicked();
  void btnEnviar_clicked();
  void btnApply_clicked();
  void btnSetSlot_clicked();
  void btnSetCodeSegment_clicked();

  void on_menu_file_popup_generic();
  bool on_button_press_event(GdkEventButton* button_event);
  void on_row_activated(const Gtk::TreeModel::Path& path,
                        Gtk::TreeViewColumn* column);
  void on_Open_selected();
  Morph &morph;
  ProxyServer &proxyServer;
 public:
  MainWindow(Morph &morph, ProxyServer &proxyServer);
  ~MainWindow();
  Gtk::Window *getWindow();
};

#endif /* MAINWINDOW_H_ */
