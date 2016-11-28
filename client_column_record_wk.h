#ifndef CLIENT_COLUMNRECORDWK_H_
#define CLIENT_COLUMNRECORDWK_H_

#include <string>
#include <gtkmm-3.0/gtkmm.h>

/** Esta clase represanta el modelo de columnas que se va
 * a utilizar en el TreeView que enumera los Workspaces.
 *
 */
class ColumnRecordWk: public Gtk::TreeModel::ColumnRecord {
public:
    ColumnRecordWk() {
        add(m_col_delete);
        add(m_col_wkName);
    }

    Gtk::TreeModelColumn<bool> m_col_delete;
    Gtk::TreeModelColumn<Glib::ustring> m_col_wkName;
};

#endif /* CLIENT_COLUMNRECORDWK_H_ */
