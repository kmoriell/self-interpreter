#include "client_mainWindow.h"

MainWindow::MainWindow(Morph &morph, ProxyServer &proxyServer)
    : morph(morph),
      proxyServer(proxyServer) {
  refBuilder = Gtk::Builder::create();
  try {
    refBuilder->add_from_file("mainWindow.glade");
  } catch (...) {
    throw std::runtime_error("No se puede crear la ventana");
  }

  refBuilder->get_widget("window", pWindow);

  addWidgets();
  configureTreeView();
  drawMorph();

  /*Gdk::Geometry geo;
  geo.screen_width(640);
  geo.screen_height(480);*/


  //pWindow->set_geometry_hints(nullptr, nullptr,Gdk::HINT_MAX_SIZE);

  pWindow->set_name("MyWindow");
  pTreeView->set_name("MyTreeView");
  //pGridSetObjName->set_name("GridSetObjName");

  //pTextView->set_name("MyTextView");
  pTxtObjName->set_name("txtObjName");
  Glib::RefPtr < Gtk::CssProvider > m_refCssProvider =
      Gtk::CssProvider::create();
  m_refCssProvider->load_from_path("custom_textView.css");
  auto refStyleContext = pWindow->get_style_context();
  //refStyleContext->add_class("txtCodeSegment");

  auto display = Gdk::Display::get_default();
  auto screen = display->get_default_screen();

  refStyleContext->add_provider_for_screen(
      screen, m_refCssProvider, GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
  //refStyleContext = pTreeView->get_style_context();
  //refStyleContext->add_provider(m_refCssProvider, GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

  show_all_children();
}

MainWindow::~MainWindow() {
  delete pWindow;
}

void MainWindow::addWidgets() {
  // Primera fila
  refBuilder->get_widget("btnLobby", pBtnLobby);
  refBuilder->get_widget("btnGoBack", pBtnGoBack);
  refBuilder->get_widget("btnRefresh", pBtnRefresh);
  refBuilder->get_widget("btnEnviar", pBtnEnviar);
  refBuilder->get_widget("txtEntrada", pTxtEntrada);

  // Segunda fila
  refBuilder->get_widget("btnApply", pBtnApply);
  refBuilder->get_widget("txtObjectName", pTxtObjName);

  refBuilder->get_widget("treeView", pTreeView);
  refBuilder->get_widget("btnSetSlot", pBtnSetSlot);
  refBuilder->get_widget("txtSlot", pTxtSlot);

  refBuilder->get_widget("btnSetCodeSegment", pBtnSetCodeSegment);
  refBuilder->get_widget("txtCodeSegment", pTxtCodeSegment);

  refBuilder->get_widget("m_Open", pMenuItemOpen);
  refBuilder->get_widget("m_CloseWorkspace", pMenuItemCloseWorkspace);

  //refBuilder->get_widget("boxObject", pBoxObject);

  //refBuilder->get_widget("menuButton", pMenuButton);

  if (pBtnLobby) {
    pBtnLobby->signal_clicked().connect(
        sigc::mem_fun(*this, &MainWindow::btnLobby_clicked));
  }

  if (pBtnGoBack) {
    pBtnGoBack->signal_clicked().connect(
        sigc::mem_fun(*this, &MainWindow::btnGoBack_clicked));
  }

  if (pBtnRefresh) {
    pBtnRefresh->signal_clicked().connect(
        sigc::mem_fun(*this, &MainWindow::btnRefresh_clicked));
  }

  if (pBtnEnviar) {
    pBtnEnviar->signal_clicked().connect(
        sigc::mem_fun(*this, &MainWindow::btnEnviar_clicked));
  }

  if (pBtnApply) {
    pBtnApply->signal_clicked().connect(
        sigc::mem_fun(*this, &MainWindow::btnApply_clicked));
  }

  if (pBtnSetSlot) {
    pBtnSetSlot->signal_clicked().connect(
        sigc::mem_fun(*this, &MainWindow::btnSetSlot_clicked));
  }

  if (pBtnSetCodeSegment) {
    pBtnSetCodeSegment->signal_clicked().connect(
        sigc::mem_fun(*this, &MainWindow::btnSetCodeSegment_clicked));
  }

  if (pTreeView) {
    pTreeView->signal_row_activated().connect(
        sigc::mem_fun(*this, &MainWindow::on_row_activated));
  }

  if (pMenuItemOpen) {
    pMenuItemOpen->signal_activate().connect(
        sigc::mem_fun(*this, &MainWindow::on_Open_selected));
  }

  if (pMenuItemCloseWorkspace) {
    pMenuItemCloseWorkspace->signal_activate().connect(
        sigc::mem_fun(*this, &MainWindow::on_CloseWorkspace_selected));
  }
}

void MainWindow::configureTreeView() {
  m_refTreeModel = Gtk::TreeStore::create(m_Columns);
  pTreeView->set_model(m_refTreeModel);

  pTreeView->append_column_editable("[ - ]", m_Columns.m_col_delete);
  pTreeView->append_column("Slot", m_Columns.m_col_slotName);
  pTreeView->append_column_editable("Mutable", m_Columns.m_col_mutable);
  pTreeView->append_column("Objeto", m_Columns.m_col_objType);
  pTreeView->append_column("Vista Previa", m_Columns.m_col_preview);

  ((Gtk::CellRendererToggle*) pTreeView->get_column_cell_renderer(0))
        ->signal_toggled().connect(
        sigc::mem_fun(*this, &MainWindow::cellDelete_toggled));

  ((Gtk::CellRendererToggle*) pTreeView->get_column_cell_renderer(2))
      ->signal_toggled().connect(
      sigc::mem_fun(*this, &MainWindow::cellMutable_toggled));
}

void MainWindow::drawMorph() {
  //pTxtObjName->set_use_markup(true);
  //pLabel->set_markup();
  pTxtObjName->set_text(morph.getObjName());
  //pLabel->set_text(morph.getObjName());
  m_refTreeModel->clear();
  Gtk::TreeModel::Row row;

  for (int i = 0; i < morph.getSlotsSize(); i++) {
    row = *(m_refTreeModel->append());
    std::string slotName;
    if (morph.isArgumentSlot(i))
      slotName = OP_ARG + morph.getSlotName(i);
    else if (morph.isParentSlot(i))
      slotName = morph.getSlotName(i) + OP_PARENT;
    else if (morph.isNativeMethodSlot(i))
      slotName = morph.getSlotName(i);
    else
      slotName = morph.getSlotName(i);

    row[m_Columns.m_col_slotName] = slotName;
    row[m_Columns.m_col_mutable] = morph.isMutableSlot(i);
    row[m_Columns.m_col_objType] = morph.getSlotObjName(i);
    row[m_Columns.m_col_preview] = morph.getSlotObjPreview(i);
  }
  auto pTextBuffer = Glib::RefPtr < Gtk::TextBuffer
      > ::cast_dynamic(refBuilder->get_object("textBufferCodeSegment"));
  pTextBuffer->set_text(morph.getCodeSegment());
}


Gtk::Window* MainWindow::getWindow() {
  return pWindow;
}

// Eventos

void MainWindow::btnEnviar_clicked() {
  if (pWindow) {
    auto pTextBuffer = Glib::RefPtr < Gtk::TextBuffer
        > ::cast_dynamic(refBuilder->get_object("txtBufferEntrada"));
    std::string text = pTextBuffer->get_text();
    proxyServer.sendCmdMessage(EXEC_LOBBY_CMD, text);
    while (proxyServer.getFlag()) {
    }
    if (proxyServer.areThereErrors()) {
      Gtk::MessageDialog dialog(*this, "Errores en la ejecución", false,
                                Gtk::MESSAGE_ERROR, Gtk::BUTTONS_OK);
      dialog.set_secondary_text(proxyServer.getErrors());
      dialog.run();
    }
    drawMorph();
  }
}

void MainWindow::btnLobby_clicked() {
  std::string empty;
  proxyServer.sendCmdMessage(SHOW_LOBBY, empty);
  while (proxyServer.getFlag()) {
  }
  if (proxyServer.areThereErrors()) {
    Gtk::MessageDialog dialog(*this, "Errores en la ejecución", false,
                              Gtk::MESSAGE_ERROR, Gtk::BUTTONS_OK);
    dialog.set_secondary_text(proxyServer.getErrors());
    dialog.run();
  }
  drawMorph();
}

void MainWindow::btnGoBack_clicked() {
  std::string empty;
  proxyServer.sendCmdMessage(GO_BACK, empty);
  while (proxyServer.getFlag()) {
  }
  if (proxyServer.areThereErrors()) {
    Gtk::MessageDialog dialog(*this, "Errores en la ejecución", false,
                              Gtk::MESSAGE_ERROR, Gtk::BUTTONS_OK);
    dialog.set_secondary_text(proxyServer.getErrors());
    dialog.run();
  }
  drawMorph();
}
void MainWindow::btnRefresh_clicked() {

}
void MainWindow::btnApply_clicked() {
  std::string text = pTxtObjName->get_text();

  proxyServer.sendCmdMessage(SET_OBJ_NAME, text);
  while (proxyServer.getFlag()) {
  }
  if (proxyServer.areThereErrors()) {
    Gtk::MessageDialog dialog(*this, "Errores en la ejecución", false,
                              Gtk::MESSAGE_ERROR, Gtk::BUTTONS_OK);
    dialog.set_secondary_text(proxyServer.getErrors());
    dialog.run();
  }
  drawMorph();
}
void MainWindow::btnSetSlot_clicked() {
  std::string text = pTxtSlot->get_text();

  proxyServer.sendCmdMessage(ADD_SLOT, text);
  while (proxyServer.getFlag()) {
  }
  if (proxyServer.areThereErrors()) {
    Gtk::MessageDialog dialog(*this, "Errores en la ejecución", false,
                              Gtk::MESSAGE_ERROR, Gtk::BUTTONS_OK);
    dialog.set_secondary_text(proxyServer.getErrors());
    dialog.run();
  }
  drawMorph();
}
void MainWindow::btnSetCodeSegment_clicked() {
  auto pTextBuffer = Glib::RefPtr < Gtk::TextBuffer
      > ::cast_dynamic(refBuilder->get_object("textBufferCodeSegment"));
  std::string text = pTextBuffer->get_text();

  proxyServer.sendCmdMessage(SET_CODESEGMENT, text);
  while (proxyServer.getFlag()) {
  }
  if (proxyServer.areThereErrors()) {
    Gtk::MessageDialog dialog(*this, "Errores en la ejecución", false,
                              Gtk::MESSAGE_ERROR, Gtk::BUTTONS_OK);
    dialog.set_secondary_text(proxyServer.getErrors());
    dialog.run();
  }
  drawMorph();
}

void MainWindow::on_row_activated(const Gtk::TreeModel::Path& path,
                                  Gtk::TreeViewColumn* column) {
  Gtk::TreeModel::iterator iter = m_refTreeModel->get_iter(path);
  if (iter) {
    Gtk::TreeModel::Row row = *iter;
    std::cout << "Row activated: Slot name=" << row[m_Columns.m_col_slotName] <<
    //", Name="
        /*  << row[m_Columns.m_col_name] << */std::endl;

    Glib::ustring text = row[m_Columns.m_col_slotName];

    std::string str(text.c_str());
    proxyServer.sendCmdMessage(GET_SLOT_OBJ, str);
    while (proxyServer.getFlag()) {
    }
    if (proxyServer.areThereErrors()) {
      Gtk::MessageDialog dialog(*this, "Errores en la ejecución", false,
                                Gtk::MESSAGE_ERROR, Gtk::BUTTONS_OK);
      dialog.set_secondary_text(proxyServer.getErrors());
      dialog.run();
    }
    drawMorph();
  }
}

void MainWindow::on_CloseWorkspace_selected() {
  Gtk::MessageDialog dialog(*this, "Errores en la ejecución", false,
                            Gtk::MESSAGE_QUESTION, Gtk::BUTTONS_YES_NO);
  dialog.set_secondary_text("¿Desea abandonar el Workspace?");
  Gtk::ResponseType resp = (Gtk::ResponseType) dialog.run();

  if (resp == Gtk::RESPONSE_NO) {
    return;
  }

  std::string emptyString = "";
  proxyServer.sendCmdMessage(CLOSE_WK, emptyString);
  while (proxyServer.getFlag()) {
  }
  this->getWindow()->close();
}

void MainWindow::on_Open_selected() {
  Gtk::FileChooserDialog dialog("Seleccionar un archivo para procesar",
                                Gtk::FILE_CHOOSER_ACTION_OPEN);
  dialog.set_transient_for(*pWindow);

  //Add response buttons the the dialog:
  dialog.add_button("_Cancelar", Gtk::RESPONSE_CANCEL);
  dialog.add_button("_Abrir", Gtk::RESPONSE_OK);

  auto filter_any = Gtk::FileFilter::create();
  filter_any->set_name("Archivos self");
  filter_any->add_pattern("*.self");
  dialog.add_filter(filter_any);

  //Show the dialog and wait for a user response:
  int result = dialog.run();

  //Handle the response:
  switch (result) {
    case (Gtk::RESPONSE_OK): {
      std::cout << "Open clicked." << std::endl;

      //Notice that this is a std::string, not a Glib::ustring.
      std::string filename = dialog.get_filename();
      std::ifstream file(filename);

      std::stringstream buffer;
      buffer << file.rdbuf();

      auto pTextBuffer = Glib::RefPtr < Gtk::TextBuffer
          > ::cast_dynamic(refBuilder->get_object("txtBufferEntrada"));
      pTextBuffer->set_text(buffer.str());
      break;
    }
    case (Gtk::RESPONSE_CANCEL): {
      std::cout << "Cancel clicked." << std::endl;
      break;
    }
    default: {
      std::cout << "Unexpected button clicked." << std::endl;
      break;
    }
  }
}

void MainWindow::cellMutable_toggled(const Glib::ustring &path) {
  Gtk::TreeIter iter;
  std::cout << "toggled = " << path << std::endl;

  auto model = this->m_refTreeModel;
  if (model) {
    iter = model->get_iter(path);

    bool checked = iter->get_value(m_Columns.m_col_mutable);
    std::string text = iter->get_value(m_Columns.m_col_slotName);
    proxyServer.sendCmdMessage(SWAP_MUTABILITY, text);
      while (proxyServer.getFlag()) {
      }
      if (proxyServer.areThereErrors()) {
        Gtk::MessageDialog dialog(*this, "Errores en la ejecución", false,
                                  Gtk::MESSAGE_ERROR, Gtk::BUTTONS_OK);
        dialog.set_secondary_text(proxyServer.getErrors());
        dialog.run();
        iter->set_value(m_Columns.m_col_mutable, checked);
      }
  }
}

void MainWindow::cellDelete_toggled(const Glib::ustring &path) {
  Gtk::TreeIter iter;
  auto model = this->m_refTreeModel;
  if (model) {
    iter = model->get_iter(path);

    std::string slotName = iter->get_value(m_Columns.m_col_slotName);
    Gtk::MessageDialog dialog(*this, "Confirmar", false,
                                  Gtk::MESSAGE_QUESTION, Gtk::BUTTONS_YES_NO);
        dialog.set_secondary_text("¿Desea borrar el slot " + slotName + "?");
        Gtk::ResponseType resp = (Gtk::ResponseType) dialog.run();

        if (resp == Gtk::RESPONSE_NO) {
          iter->set_value(m_Columns.m_col_delete, false);
          return;
        }
    proxyServer.sendCmdMessage(REMOVE_SLOT, slotName);
      while (proxyServer.getFlag()) {
      }
      if (proxyServer.areThereErrors()) {
        Gtk::MessageDialog dialog(*this, "Errores en la ejecución", false,
                                  Gtk::MESSAGE_ERROR, Gtk::BUTTONS_OK);
        dialog.set_secondary_text(proxyServer.getErrors());
        dialog.run();
        iter->set_value(m_Columns.m_col_delete, false);
      }
      drawMorph();
  }
}

