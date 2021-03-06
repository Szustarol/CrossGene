#ifndef RECORD_MODEL
#define RECORD_MODEL

#include <memory>
#include <vector>
#include <utility>
#include <any>
#include <gtkmm.h>
#include "../../../Translations/strings.hpp"
#include "../../../program_data.hpp"

class record_model : public Gtk::TreeModel::ColumnRecord{
    std::vector<std::any> columns;
    std::vector<std::string> names;
    std::vector<char> tps;

    Glib::RefPtr<Gtk::ListStore> list_store;

    GENE_DATA * parent_gene_data;    

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

    void update_data_package();

    Gtk::Label * result_label = nullptr;

    template <typename ... Ts>
    void set_records_and_install(std::vector<std::string> column_names, GENE_DATA * gd, Gtk::TreeView & tv, bool include_selection = true){
        n_columns = 0;

        parent_gene_data = gd;

        columns.clear();
        names.clear();

        Gtk::TreeModelColumn<std::string> domtype1;
        Gtk::TreeModelColumn<std::string> domtype2;

        Gtk::TreeModelColumn<std::string> domtype1_2;
        Gtk::TreeModelColumn<std::string> domtype2_2;

        auto name_iter = column_names.begin();

        (extract_record_data<Ts>(*(name_iter++)), ...);

        if(include_selection){
            add(domtype1);
            add(domtype2);
            add(domtype1_2);
            add(domtype2_2);
        }

        list_store = Gtk::ListStore::create(*this);

        tv.set_model(list_store);

        unsigned vct_idx = 0;

        (append_to_view<Ts>(vct_idx++, tv), ...);

        if(include_selection){
            tv.append_column(STRINGS[STRING_G1_TYPE], domtype1);
            tv.append_column(STRINGS[STRING_G2_TYPE], domtype2);
            tv.append_column(STRINGS[STRING_G1_TYPE_2], domtype1_2);
            tv.append_column(STRINGS[STRING_G2_TYPE_2], domtype2_2);
        }
        tv.signal_row_activated().connect(sigc::mem_fun(this, &record_model::row_double_click));

        for(unsigned column_idx; column_idx<tv.get_n_columns(); column_idx++){
            tv.get_column(column_idx)->set_sizing(Gtk::TreeViewColumnSizing::TREE_VIEW_COLUMN_AUTOSIZE);
            tv.get_column(column_idx)->set_resizable(true);
            tv.get_column(column_idx)->set_title("CHUJ");
        }
    }

    unsigned num_columns();

    std::any & get_column(unsigned index);
    const std::string & get_column_name(unsigned index);

    const std::vector<std::string> & get_names();

    void add_row(char letter, int dtype, std::string description, int n_codom);

    void remove_row_by_iterator(Gtk::TreeModel::iterator it);

    unsigned n_rows();

    void row_double_click(const Gtk::TreeModel::Path& path, Gtk::TreeViewColumn* column);

    void install_in_treeview(Gtk::TreeView & tv);
};

#endif