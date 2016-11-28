#ifndef MORPHWINDOW_H_
#define MORPHWINDOW_H_

#include <gtkmm-3.0/gtkmm.h>
#include <gdkmm/color.h>
#include <iostream>
#include <fstream>
#include "client_columnRecord.h"
#include "client_morph.h"
#include "client_proxyServer.h"

#define COL_DELETE 0
#define COL_MUTABLE 2
#define MAX_PREVIEW_LEN 20

class MorphWindow: public Gtk::Window {
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

    Gtk::TreeView *pTreeView = nullptr;
    //Gtk::MenuButton *pMenuButton = nullptr;
    Glib::RefPtr<Gtk::TreeStore> m_refTreeModel;
    ColumnRecord m_Columns;
    //Gtk::Menu m_Menu_Popup;

    // Menu
    Gtk::MenuItem *pMenuItemOpen = nullptr;
    Gtk::MenuItem *pMenuItemCloseWorkspace = nullptr;

    void addWidgets();
    void configureTreeView();
    void drawMorph();
    void generatePopup();

    void doAction(char action, std::string text);

    // Eventos
    void btnLobby_clicked();
    void btnGoBack_clicked();
    void btnRefresh_clicked();
    void btnEnviar_clicked();
    void btnApply_clicked();
    void btnSetSlot_clicked();
    void btnSetCodeSegment_clicked();
    bool window_deleted(GdkEventAny* any_event);

    void on_row_activated(const Gtk::TreeModel::Path& path,
            Gtk::TreeViewColumn* column);
    void on_Open_selected();
    void on_CloseWorkspace_selected();
    void cellMutable_toggled(const Glib::ustring &path);
    void cellDelete_toggled(const Glib::ustring &path);

    Morph &morph;
    ProxyServer &proxyServer;
    std::mutex &m;

public:
    MorphWindow(Morph &morph, ProxyServer &proxyServer, std::mutex &m);
    ~MorphWindow();
    Gtk::Window *getWindow();

    // Elimino constructores y operadores de asignacion
    MorphWindow(MorphWindow&&) = delete;
    MorphWindow(const MorphWindow&) = delete;

    MorphWindow& operator=(MorphWindow&&) = delete;
    MorphWindow& operator=(const MorphWindow&) = delete;
};

#endif /* MORPHWINDOW_H_ */
