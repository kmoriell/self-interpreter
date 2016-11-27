#include <string>
#include <gtkmm-3.0/gtkmm.h>

class ColumnRecord: public Gtk::TreeModel::ColumnRecord {
public:
    ColumnRecord() {
        add(m_col_delete);
        add(m_col_slotName);
        add(m_col_mutable);
        add(m_col_objType);
        add(m_col_preview);
    }

    Gtk::TreeModelColumn<bool> m_col_delete;
    Gtk::TreeModelColumn<Glib::ustring> m_col_slotName;
    Gtk::TreeModelColumn<bool> m_col_mutable;
    Gtk::TreeModelColumn<Glib::ustring> m_col_objType;
    Gtk::TreeModelColumn<Glib::ustring> m_col_preview;
};
