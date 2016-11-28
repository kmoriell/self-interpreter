#ifndef CLIENT_SELECTWKWINDOW_H_
#define CLIENT_SELECTWKWINDOW_H_

#include <gtkmm-3.0/gtkmm.h>
#include <gdkmm/color.h>
#include <iostream>
#include <mutex>
#include "client_columnRecordWk.h"
#include "client_morphWindow.h"

/** Se encarga de dibujar la ventana selectora de workspaces.
 *
 */
class SelectWkWindow: public Gtk::Window {
private:
    Morph &morph;
    std::vector<std::string> &workspaces;
    ProxyServer &proxyServer;
    std::mutex &m;

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

    /** Este metodo agrega los widgets a la ventana
     *
     */
    void addWidgets();

    /** Este metodo configura las columnas los eventos del TreeView.
     *
     */
    void configureTreeView();

    /** Este metodo dibuja los datos recibidos sobre los workspaces
     * provenientes del servidor en el TreeView.
     * Previamente hay que llamar al metodo updateList() para actualizar
     * los datos en memoria. Este metodo no los actualiza, solo dibuja lo que
     * esta cargado.
     *
     */
    void drawWorkspaces();

    /** Manda la solicitud al servidor para actualizar la lista
     * de workspaces disponibles que esta guardada en memoria.
     * Para redibujar la lista, llamar a drawWorkspaces().
     */
    void updateList();

public:
    /** Constructor de la clase
     * @param morph referencia al objeto Morph.
     * @param workspaces referencia al vector con los nombres de los workspaces
     * @param proxyServer referencia al proxy
     * @param m referencia al mutex
     */
    SelectWkWindow(Morph &morph, std::vector<std::string> &workspaces,
            ProxyServer &proxyServer, std::mutex &m);

    /** Devuelve un puntero al objeto Gtk::Window.
     *
     */
    Gtk::Window *getWindow();

    // Elimino los contructores por copia y moviemiento. Tambien los
    // operadores de asignacion
    SelectWkWindow(const SelectWkWindow&) = delete;
    SelectWkWindow(SelectWkWindow&&) = delete;
    SelectWkWindow& operator=(const SelectWkWindow&) = delete;
    SelectWkWindow& operator=(SelectWkWindow&&) = delete;
};

#endif /* CLIENT_SELECTWKWINDOW_H_ */
