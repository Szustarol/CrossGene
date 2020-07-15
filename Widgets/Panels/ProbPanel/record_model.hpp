#ifndef RECORD_MODEL
#define RECORD_MODEL

#include <memory>
#include <vector>
#include <utility>
#include <any>
#include <gtkmm.h>

class record_model : public Gtk::TreeModel::ColumnRecord{
    std::vector<std::any> columns;
    std::vector<std::string> names;
    std::vector<char> tps;

    Glib::RefPtr<Gtk::ListStore> list_store;



    unsigned n_columns;

    template <typename T>
    void extract_record_data(std::string col_name){
        n_columns += 1;

        columns.emplace_back(Gtk::TreeModelColumn<T>());
        names.emplace_back(col_name);

        auto & toadd = std::any_cast<Gtk::TreeModelColumn<T>&>(columns.back());

        add(toadd);
    }

    template <typename T>
    void append_to_view(unsigned vect_iter, Gtk::TreeView & tv){
        auto & toadd = std::any_cast<Gtk::TreeModelColumn<T>&>(columns.at(vect_iter));

        tv.append_column(names.at(vect_iter), toadd);
    }

    public:

    template <typename ... Ts>
    void set_records_and_install(std::vector<std::string> column_names, Gtk::TreeView & tv){
        n_columns = 0;

        columns.clear();
        names.clear();

        auto name_iter = column_names.begin();

        (extract_record_data<Ts>(*(name_iter++)), ...);

        list_store = Gtk::ListStore::create(*this);

        tv.set_model(list_store);

        unsigned vct_idx = 0;

        (append_to_view<Ts>(vct_idx++, tv), ...);
    }

    unsigned num_columns();

    std::any & get_column(unsigned index);
    const std::string & get_column_name(unsigned index);

    const std::vector<std::string> & get_names();

    void add_row(char letter, int dtype, std::string description);

    void remove_row_by_iterator(Gtk::TreeModel::iterator it);

    unsigned n_rows();

    void install_in_treeview(Gtk::TreeView & tv);
};

#endif