#include "client_selectWkWindow.h"

SelectWkWindow::SelectWkWindow(Morph &morph, std::vector<std::string> &workspaces, ProxyServer &proxyServer)
    : morph(morph),
      workspaces(workspaces),
      proxyServer(proxyServer) {
  refBuilder = Gtk::Builder::create();
  try {
    refBuilder->add_from_file("mainWindow.glade");
  } catch (...) {
    throw std::runtime_error("No se puede crear la ventana");
  }

  refBuilder->get_widget("windowWorkspace", pWindow);

  std::string cad = "";
  proxyServer.sendCmdMessage(AVAILABLE_WKS, cad);
  drawWorkspaces();

  addWidgets();
  configureTreeView();
  show_all_children();
}

Gtk::Window* SelectWkWindow::getWindow() {
  return pWindow;
}

void SelectWkWindow::addWidgets() {
  // Primera fila
  refBuilder->get_widget("btnRefreshWk", pBtnRefreshWk);
  refBuilder->get_widget("btnNewWk", pBtnNewWk);
  refBuilder->get_widget("txtNewWk", pTxtNewWk);

  // TreeView
  refBuilder->get_widget("treeViewWks", pTreeView);

  // Conecto los eventos
  if (pBtnRefreshWk) {
    pBtnRefreshWk->signal_clicked().connect(
        sigc::mem_fun(*this, &SelectWkWindow::btnRefreshWk_clicked));
  }

  if (pBtnNewWk) {
    pBtnNewWk->signal_clicked().connect(
        sigc::mem_fun(*this, &SelectWkWindow::btnNewWk_clicked));
  }

  if (pTreeView) {
    pTreeView->signal_row_activated().connect(
        sigc::mem_fun(*this, &SelectWkWindow::treeView_on_row_activated));
  }

}

void SelectWkWindow::configureTreeView() {
  m_refTreeModel = Gtk::TreeStore::create(m_Columns);
  pTreeView->set_model(m_refTreeModel);

  pTreeView->append_column_editable("[-]", m_Columns.m_col_delete);
  pTreeView->append_column("Workspace", m_Columns.m_col_wkName);

  // Conecto el evento para controlar el checkbox
  ((Gtk::CellRendererToggle*) pTreeView->get_column_cell_renderer(0))
      ->signal_toggled().connect(
      sigc::mem_fun(*this, &SelectWkWindow::treeView_toggled));
}

void SelectWkWindow::drawWorkspaces() {
	m_refTreeModel->clear();
	for(auto str : workspaces) {
		  Gtk::TreeModel::Row row = *(m_refTreeModel->append());
		  row[m_Columns.m_col_delete] = false;
		  row[m_Columns.m_col_wkName] = str;
	}
}

// Eventos
void SelectWkWindow::btnRefreshWk_clicked() {
	drawWorkspaces();
}
void SelectWkWindow::btnNewWk_clicked() {
	drawWorkspaces();
}

void SelectWkWindow::treeView_toggled(const Glib::ustring &path) {
  Gtk::TreeIter iter;
  std::cout << "toggled = " << path << std::endl;

  auto model = this->m_refTreeModel;
  if (model) {
    iter = model->get_iter(path);

    bool checked = iter->get_value(m_Columns.m_col_delete);
    /*proxyServer.sendCmdMessage(SWAP_MUTABILITY, text);
     while (proxyServer.getFlag()) {
     }
     if (proxyServer.areThereErrors()) {
     Gtk::MessageDialog dialog(*this, "Errores en la ejecución", false,
     Gtk::MESSAGE_ERROR, Gtk::BUTTONS_OK);
     dialog.set_secondary_text(proxyServer.getErrors());
     dialog.run();
     }*/
  }
}

void SelectWkWindow::treeView_on_row_activated(const Gtk::TreeModel::Path& path,
                                               Gtk::TreeViewColumn* column) {
  Gtk::TreeModel::iterator iter = m_refTreeModel->get_iter(path);
  if (iter) {
    Gtk::TreeModel::Row row = *iter;
    std::cout << "Row activated: Slot name=" << row[m_Columns.m_col_wkName] <<
    //", Name="
        /*  << row[m_Columns.m_col_name] << */std::endl;

    Glib::ustring text = row[m_Columns.m_col_wkName];

    MainWindow* _window = new MainWindow(morph, proxyServer);
    _window->getWindow()->show();

    /*std::string str(text.c_str());
     proxyServer.sendCmdMessage(GET_SLOT_OBJ, str);
     while (proxyServer.getFlag()) {
     }
     if (proxyServer.areThereErrors()) {
     Gtk::MessageDialog dialog(*this, "Errores en la ejecución", false,
     Gtk::MESSAGE_ERROR, Gtk::BUTTONS_OK);
     dialog.set_secondary_text(proxyServer.getErrors());
     dialog.run();
     }
     drawMorph();*/
  }
}

