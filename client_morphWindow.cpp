#include "client_morphWindow.h"

MorphWindow::MorphWindow(Morph &morph, ProxyServer &proxyServer, std::mutex &m) :
        morph(morph), proxyServer(proxyServer), m(m) {
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
    pWindow->signal_delete_event().connect(
            sigc::mem_fun(*this, &MorphWindow::window_deleted));
    show_all_children();
}

MorphWindow::~MorphWindow() {
    delete pWindow;
}

void MorphWindow::addWidgets() {
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

    if (pBtnLobby) {
        pBtnLobby->signal_clicked().connect(
                sigc::mem_fun(*this, &MorphWindow::btnLobby_clicked));
    }

    if (pBtnGoBack) {
        pBtnGoBack->signal_clicked().connect(
                sigc::mem_fun(*this, &MorphWindow::btnGoBack_clicked));
    }

    if (pBtnRefresh) {
        pBtnRefresh->signal_clicked().connect(
                sigc::mem_fun(*this, &MorphWindow::btnRefresh_clicked));
    }

    if (pBtnEnviar) {
        pBtnEnviar->signal_clicked().connect(
                sigc::mem_fun(*this, &MorphWindow::btnEnviar_clicked));
    }

    if (pBtnApply) {
        pBtnApply->signal_clicked().connect(
                sigc::mem_fun(*this, &MorphWindow::btnApply_clicked));
    }

    if (pBtnSetSlot) {
        pBtnSetSlot->signal_clicked().connect(
                sigc::mem_fun(*this, &MorphWindow::btnSetSlot_clicked));
    }

    if (pBtnSetCodeSegment) {
        pBtnSetCodeSegment->signal_clicked().connect(
                sigc::mem_fun(*this, &MorphWindow::btnSetCodeSegment_clicked));
    }

    if (pTreeView) {
        pTreeView->signal_row_activated().connect(
                sigc::mem_fun(*this, &MorphWindow::on_row_activated));
    }

    if (pMenuItemOpen) {
        pMenuItemOpen->signal_activate().connect(
                sigc::mem_fun(*this, &MorphWindow::on_Open_selected));
    }

    if (pMenuItemCloseWorkspace) {
        pMenuItemCloseWorkspace->signal_activate().connect(
                sigc::mem_fun(*this, &MorphWindow::on_CloseWorkspace_selected));
    }
}

void MorphWindow::configureTreeView() {
    m_refTreeModel = Gtk::TreeStore::create(m_Columns);
    pTreeView->set_model(m_refTreeModel);

    // Creo las columnas del TreeView
    pTreeView->append_column_editable("[ - ]", m_Columns.m_col_delete);
    pTreeView->append_column("Slot", m_Columns.m_col_slotName);
    pTreeView->append_column_editable("Mutable", m_Columns.m_col_mutable);
    pTreeView->append_column("Objeto", m_Columns.m_col_objType);
    pTreeView->append_column("Vista Previa", m_Columns.m_col_preview);

    // Le asigno el evento toggle a las columnas que tienen un checkbox
    ((Gtk::CellRendererToggle*) pTreeView->get_column_cell_renderer(COL_DELETE))->signal_toggled().connect(
            sigc::mem_fun(*this, &MorphWindow::cellDelete_toggled));

    ((Gtk::CellRendererToggle*) pTreeView->get_column_cell_renderer(COL_MUTABLE))->signal_toggled().connect(
            sigc::mem_fun(*this, &MorphWindow::cellMutable_toggled));
}

void MorphWindow::drawMorph() {
    m.lock();
    pTxtObjName->set_text(morph.getObjName());

    m_refTreeModel->clear();
    Gtk::TreeModel::Row row;

    for (int i = 0; i < morph.getSlotsSize(); i++) {
        row = *(m_refTreeModel->append());
        std::string slotName;
        if (morph.isArgumentSlot(i))
            slotName = OP_ARG + morph.getSlotName(i);
        else if (morph.isParentSlot(i))
            slotName = morph.getSlotName(i) + OP_PARENT;
        else
            slotName = morph.getSlotName(i);

        std::string preview = morph.getSlotObjPreview(i);

        if (preview.size() > MAX_PREVIEW_LEN)
            preview = preview.substr(0, MAX_PREVIEW_LEN);

        row[m_Columns.m_col_slotName] = slotName;
        row[m_Columns.m_col_mutable] = morph.isMutableSlot(i);
        row[m_Columns.m_col_objType] = morph.getSlotObjName(i);
        row[m_Columns.m_col_preview] = preview;
    }
    auto pTextBuffer = Glib::RefPtr < Gtk::TextBuffer
            > ::cast_dynamic(refBuilder->get_object("textBufferCodeSegment"));
    pTextBuffer->set_text(morph.getCodeSegment());
    m.unlock();
}

Gtk::Window* MorphWindow::getWindow() {
    return pWindow;
}

void MorphWindow::doAction(char action, std::string text) {
    proxyServer.sendCmdMessage(action, text);
    while (proxyServer.getFlag()) {
    }
    if (proxyServer.areThereErrors()) {
        Gtk::MessageDialog dialog(*this, "Errores en la ejecución", false,
                Gtk::MESSAGE_ERROR, Gtk::BUTTONS_OK);
        dialog.set_secondary_text(proxyServer.getErrors());
        dialog.run();
    } else {
        drawMorph();
    }
}

// Eventos
bool MorphWindow::window_deleted(GdkEventAny* any_event) {
    std::string empty = "";
    proxyServer.sendCmdMessage(CLOSE_WK, empty);
    while (proxyServer.getFlag()) {
    }

    return false;
}

void MorphWindow::btnEnviar_clicked() {
    if (pWindow) {
        auto pTextBuffer = Glib::RefPtr < Gtk::TextBuffer
                > ::cast_dynamic(refBuilder->get_object("txtBufferEntrada"));
        std::string text = pTextBuffer->get_text();
        doAction(EXEC_LOBBY_CMD, text);
    }
}

void MorphWindow::btnLobby_clicked() {
    std::string empty;
    doAction(SHOW_LOBBY, empty);
}

void MorphWindow::btnGoBack_clicked() {
    std::string empty;
    doAction(GO_BACK, empty);
}
void MorphWindow::btnRefresh_clicked() {
    std::string empty;
    doAction(EXEC_REFRESH, empty);
}

void MorphWindow::btnApply_clicked() {
    std::string text = pTxtObjName->get_text();
    doAction(SET_OBJ_NAME, text);
}

void MorphWindow::btnSetSlot_clicked() {
    std::string text = pTxtSlot->get_text();
    doAction(ADD_SLOT, text);
}

void MorphWindow::btnSetCodeSegment_clicked() {
    auto pTextBuffer = Glib::RefPtr < Gtk::TextBuffer
            > ::cast_dynamic(refBuilder->get_object("textBufferCodeSegment"));
    std::string text = pTextBuffer->get_text();

    doAction(SET_CODESEGMENT, text);
}

void MorphWindow::on_row_activated(const Gtk::TreeModel::Path& path,
        Gtk::TreeViewColumn* column) {
    Gtk::TreeModel::iterator iter = m_refTreeModel->get_iter(path);
    if (iter) {
        int rowId = path[0];

        Glib::ustring text = morph.getSlotName(rowId);
        std::string str(text.c_str());

        if (morph.isNativeMethodSlot(rowId)) {
            return;
        }

        doAction(GET_SLOT_OBJ, str);
    }
}

void MorphWindow::on_CloseWorkspace_selected() {
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

void MorphWindow::on_Open_selected() {
    Gtk::FileChooserDialog dialog("Seleccionar un archivo para procesar",
            Gtk::FILE_CHOOSER_ACTION_OPEN);
    dialog.set_transient_for(*pWindow);

    // Le agrego los botones de Abrir y Cancelar al cuadro de dialogo
    dialog.add_button("_Cancelar", Gtk::RESPONSE_CANCEL);
    dialog.add_button("_Abrir", Gtk::RESPONSE_OK);

    auto filter_any = Gtk::FileFilter::create();
    filter_any->set_name("Archivos self");
    filter_any->add_pattern("*.self");
    dialog.add_filter(filter_any);

    int result = dialog.run();

    switch (result) {
    case (Gtk::RESPONSE_OK): {

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
        break;
    }
    default:
        break;
    }
}

void MorphWindow::cellMutable_toggled(const Glib::ustring &path) {
    Gtk::TreeIter iter;
    auto model = this->m_refTreeModel;
    if (model) {
        iter = model->get_iter(path);

        bool checked = iter->get_value(m_Columns.m_col_mutable);
        std::string text = iter->get_value(m_Columns.m_col_slotName);

        int rowId = atoi(path.c_str());
        // Antes de enviar el comando al servidor, verifico que sea objeto nativo
        if (morph.isNativeMethodSlot(rowId)) {
            iter->set_value(m_Columns.m_col_mutable, false);
            return;
        }

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

void MorphWindow::cellDelete_toggled(const Glib::ustring &path) {
    Gtk::TreeIter iter;
    auto model = this->m_refTreeModel;
    if (model) {
        iter = model->get_iter(path);
        int rowId = atoi(path.c_str());

        std::string slotName = morph.getSlotName(rowId);

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
        } else {
            drawMorph();
        }
    }
}
