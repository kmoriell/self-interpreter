#ifndef CLIENT_SELECTWKWINDOW_H_
#define CLIENT_SELECTWKWINDOW_H_

#include <gtkmm-3.0/gtkmm.h>
#include <gdkmm/color.h>
#include <iostream>
#include "client_columnRecordWk.h"
#include "client_mainWindow.h"

class SelectWkWindow : public Gtk::Window {
 private:
  Morph &morph;
  std::vector<std::string> &workspaces;
  ProxyServer &proxyServer;

   Glib::RefPtr<Gtk::Builder> refBuilder;

   Gtk::Window *pWindow = nullptr;

   // Botones
   Gtk::Button *pBtnRefreshWk = nullptr;
   Gtk::Button *pBtnNewWk = nullptr;

   // Cajas de texto
   Gtk::Entry *pTxtNewWk = nullptr;

   // TreeView
   Gtk::TreeView *pTreeView = nullptr;
   Glib::RefPtr<Gtk::TreeStore> m_refTreeModel;
   ColumnRecordWk m_Columns;

 private:
   //Eventos
   void btnRefreshWk_clicked();
   void btnNewWk_clicked();
   void treeView_toggled(const Glib::ustring &path);
   void treeView_on_row_activated(const Gtk::TreeModel::Path& path,
                         Gtk::TreeViewColumn* column);

   void addWidgets();
   void configureTreeView();
   void drawWorkspaces();

 public:
   SelectWkWindow(Morph &morph, std::vector<std::string> &workspaces, ProxyServer &proxyServer);
   Gtk::Window *getWindow();

};



#endif /* CLIENT_SELECTWKWINDOW_H_ */
