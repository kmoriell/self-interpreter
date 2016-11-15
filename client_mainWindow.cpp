#include "client_mainWindow.h"

MainWindow::MainWindow(Morph &morph, ProxyServer &proxyServer) : morph(morph), proxyServer(proxyServer) {
  refBuilder = Gtk::Builder::create();
  try {
    refBuilder->add_from_file("mainWindow.glade");
  }
  catch(...) {
    throw "No se puede crear la ventana";
  }
  refBuilder->get_widget("window", pWindow);
  addWidgets();
  configureTreeView();
  populateTreeView();
  show_all_children();
}

MainWindow::~MainWindow() {
  delete pWindow;
}

void MainWindow::addWidgets() {
  refBuilder->get_widget("btnEnviar", pButton);
  refBuilder->get_widget("txtEntrada", pText);
  refBuilder->get_widget("treeView", pTreeView);
  refBuilder->get_widget("txtCodeSegment", pTextView);
  if(pButton) {
    pButton->signal_clicked().connect( sigc::mem_fun(*this,
              &MainWindow::on_button_clicked) );
  }
}

void MainWindow::configureTreeView() {
  colSlotName.set_title("Slot");
  colMutable.set_title("Mutable");
  colObjName.set_title("Objeto");
  colPreview.set_title("Previsualizacion");

  colMutableCell.set_activatable(true);

  colSlotName.pack_start(colSlotNameCell, true);
  colMutable.pack_start(colMutableCell, true);
  colPreview.pack_start(colPreviewCell, true);
  colObjName.pack_start(colObjNameCell, true);

  pTreeView->append_column(colSlotName);
  pTreeView->append_column(colMutable);
  pTreeView->append_column(colObjName);
  pTreeView->append_column(colPreview);

  colSlotName.add_attribute(colSlotNameCell, "text", 0);
  colMutable.add_attribute(colMutableCell, "activatable", 1);
  colObjName.add_attribute(colObjNameCell, "text", 2);
  colPreview.add_attribute(colPreviewCell, "text", 3);

  
  m_refTreeModel = Gtk::ListStore::create(m_Columns);
  pTreeView->set_model(m_refTreeModel);
}

void MainWindow::populateTreeView() {
  m_refTreeModel->clear();
  Gtk::TreeModel::Row row;
  //colMutableCell.set_active(false);
  for (int i = 0; i < morph.getSlotsSize(); i++) {
    row = *(m_refTreeModel->append());
    std::string slotName;
    if (morph.isArgumentSlot(i))
        slotName = ":" + morph.getSlotName(i);
    else if (morph.isParentSlot(i))
        slotName = morph.getSlotName(i) + "+";
    /*else if (morph.isNativeMethodSlot(i)) {
//	Gdk::Color col("red");
	colSlotNameCell.property_foreground("red");
    }
    else if (morph.isMutableSlot(i))
	colMutableCell.set_active(true);*/
    else
        slotName = morph.getSlotName(i);

    row[m_Columns.m_col_slotName] = slotName;
    row[m_Columns.m_col_mutable] = morph.isMutableSlot(i);
    row[m_Columns.m_col_objType] = morph.getSlotObjName(i);
    row[m_Columns.m_col_preview] = morph.getSlotObjPreview(i);
  }  
  auto pTextBuffer = Glib::RefPtr<Gtk::TextBuffer>::cast_dynamic(
    refBuilder->get_object("textbuffer1"));
  pTextBuffer->set_text(morph.getCodeSegment());
}

void MainWindow::on_button_clicked() {
  if(pWindow && pText) {
    std::string text = pText->get_text();
    proxyServer.sendCmdMessage(EXEC_LOBBY_CMD, text);
    std::cout << "antes while" << std::endl;
    while(proxyServer.getFlag()) {
	std::cout << "flag = " << proxyServer.getFlag() << std::endl;
    }
    std::cout << "despues while" << std::endl;
    populateTreeView();
  }
}

Gtk::Window* MainWindow::getWindow() {
  return pWindow;
}


