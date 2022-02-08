struct vatrate {
    const char* country;
    const char* rate;
};

static struct vatrate rates[] = {
    {"AT", "20"},
    {"BE", "21"},
    {"BG", "20"},
    {"HR", "25"},
    {"CY", "19"},
    {"CZ", "21"},
    {"DK", "25"},
    {"EE", "20"},
    {"FI", "24"},
    {"FR", "20"},
    {"MO", "20"},
    {"DE", "19"},
    {"EL", "24"},
    {"HU", "27"},
    {"IE", "23"},
    {"IT", "22"},
    {"LV", "21"},
    {"LT", "21"},
    {"LU", "17"},
    {"MT", "18"},
    {"NL", "21"},
    {"PL", "23"},
    {"PT", "23"},
    {"RO", "19"},
    {"SK", "20"},
    {"SI", "22"},
    {"ES", "21"},
    {"SE", "25"},
    {"GB", "20"}
};
GtkCalendar     *input_date;
GtkEntry        *input_invoice_nr;
GtkComboBoxText *input_currency;
GtkEntry        *input_seller_name;
GtkEntry        *input_seller_business;
GtkEntry        *input_seller_address;
GtkEntry        *input_seller_zip;
GtkEntry        *input_seller_city;
GtkComboBoxText *input_seller_country;
GtkEntry        *input_seller_nip;
GtkEntry        *input_buyer_name;
GtkEntry        *input_buyer_business;
GtkEntry        *input_buyer_address;
GtkEntry        *input_buyer_zip;
GtkEntry        *input_buyer_city;
GtkComboBoxText *input_buyer_country;
GtkEntry        *input_buyer_nip;
GtkEntry        *input_product1_name;
GtkComboBoxText *input_product1_qty;
GtkEntry        *input_product1_net;
GtkEntry        *input_product1_netto;
GtkEntry        *input_product1_vat_rate;
GtkEntry        *input_product1_vat_value;
GtkEntry        *input_product1_brutto;
GtkEntry        *input_product2_name;
GtkComboBoxText *input_product2_qty;
GtkEntry        *input_product2_net;
GtkEntry        *input_product2_netto;
GtkEntry        *input_product2_vat_rate;
GtkEntry        *input_product2_vat_value;
GtkEntry        *input_product2_brutto;
GtkEntry        *input_total_netto;
GtkEntry        *input_total_vat_value;
GtkEntry        *input_total_brutto;
GtkEntry        *input_total;
GtkTextBuffer   *model_faktura;
float total_netto_1;
float total_netto_2;
float total_vat_1;
float total_vat_2;
float total_brutto_1;
float total_brutto_2;

static void destroy(GtkWidget *widget, gpointer data);
void on_input_product1_net_changed
    (GtkEditable *input_product1_net, GtkComboBoxText *input_product1_qty);
void on_input_product1_qty_changed
    (GtkComboBoxText *input_product1_qty, GtkEditable *input_product1_net);
void on_input_product1_netto_changed
    (GtkEditable *input_product1_netto, GtkEntry *input_product1_vat_rate);
void on_input_product1_vat_rate_changed
    (GtkEntry *input_product1_vat_rate, GtkEditable *input_product1_netto);
void on_input_product2_net_changed
    (GtkEditable *input_product2_net, GtkComboBoxText *input_product2_qty);
void on_input_product2_qty_changed
    (GtkComboBoxText *input_product2_qty, GtkEditable *input_product2_net);
void on_input_product2_netto_changed
    (GtkEditable *input_product2_netto, GtkEntry *input_product2_vat_rate);
void on_input_product2_vat_rate_changed
    (GtkEntry *input_product2_vat_rate, GtkEditable *input_product2_netto);
void on_input_buyer_country_changed
    (GtkComboBox *input_buyer_country, GtkEntry *input_product1_vat_rate);
void on_input_buyer_nip_changed
    (GtkEditable *input_buyer_nip, GtkComboBox *input_buyer_country);
void output_to_file(char* html);
char* read_template(char* location);
char* insert_date(char* html);
char* insert_total_netto(char* html);
char* insert_total_vat(char* html);
char* insert_total_brutto(char* html);
char* insert_total(char* html);
char* insert_currency(char* html);
char* replace_str(char* str, const char* orig, const char* rep);
char* insert_invoice_nr(char* html);
char* insert_product_1(char* html, char* html_part);
char* insert_product_2(char* html, char* html_part);
char* build_product_row(char* html_part, const char* name, const char* qty,
        const char* net, const char* netto, const char* vat_rate,
        const char* vat_value, const char* brutto);
char* insert_mentions(char* html, char* mentions);
void pdf_print();
char* insert_seller(char* html);
const char* build_seller();
char* insert_buyer(char* html);
const char* build_buyer();
const char* get_vat_rate(const char* code);
