#include <gtk/gtk.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "main.h"

int main(int argc, char *argv[])
{
    GtkBuilder      *builder;
    GtkWidget       *window;

    gtk_init(&argc, &argv);

    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "design.glade", NULL);

    window = GTK_WIDGET(gtk_builder_get_object(builder, "shams"));
    gtk_builder_connect_signals(builder, NULL);

    input_seller_name =
        GTK_ENTRY(gtk_builder_get_object(builder, "input_seller_name"));
    input_buyer_name =
        GTK_ENTRY(gtk_builder_get_object(builder, "input_buyer_name"));
    input_seller_business =
        GTK_ENTRY(gtk_builder_get_object(builder, "input_seller_business"));
    input_buyer_business =
        GTK_ENTRY(gtk_builder_get_object(builder, "input_buyer_business"));
    input_seller_address =
        GTK_ENTRY(gtk_builder_get_object(builder, "input_seller_address"));
    input_buyer_address =
        GTK_ENTRY(gtk_builder_get_object(builder, "input_buyer_address"));
    input_seller_zip =
        GTK_ENTRY(gtk_builder_get_object(builder, "input_seller_zip"));
    input_buyer_zip =
        GTK_ENTRY(gtk_builder_get_object(builder, "input_buyer_zip"));
    input_seller_city =
        GTK_ENTRY(gtk_builder_get_object(builder, "input_seller_city"));
    input_buyer_city =
        GTK_ENTRY(gtk_builder_get_object(builder, "input_buyer_city"));
    input_seller_nip =
        GTK_ENTRY(gtk_builder_get_object(builder, "input_seller_nip"));
    input_buyer_nip =
        GTK_ENTRY(gtk_builder_get_object(builder, "input_buyer_nip"));
    input_seller_country =
        GTK_COMBO_BOX_TEXT(gtk_builder_get_object(builder, "input_seller_country"));
    input_buyer_country =
        GTK_COMBO_BOX_TEXT(gtk_builder_get_object(builder, "input_buyer_country"));
    input_product1_name =
        GTK_ENTRY(gtk_builder_get_object(builder, "input_product1_name"));
    input_product1_net =
        GTK_ENTRY(gtk_builder_get_object(builder, "input_product1_net"));
    input_product1_netto =
        GTK_ENTRY(gtk_builder_get_object(builder, "input_product1_netto"));
    input_product1_vat_rate =
        GTK_ENTRY(gtk_builder_get_object(builder, "input_product1_vat_rate"));
    input_product1_vat_value =
        GTK_ENTRY(gtk_builder_get_object(builder, "input_product1_vat_value"));
    input_product1_brutto =
        GTK_ENTRY(gtk_builder_get_object(builder, "input_product1_brutto"));
    input_product1_qty =
        GTK_COMBO_BOX_TEXT(gtk_builder_get_object(builder, "input_product1_qty"));
    input_product2_name =
        GTK_ENTRY(gtk_builder_get_object(builder, "input_product2_name"));
    input_product2_net =
        GTK_ENTRY(gtk_builder_get_object(builder, "input_product2_net"));
    input_product2_netto =
        GTK_ENTRY(gtk_builder_get_object(builder, "input_product2_netto"));
    input_product2_vat_rate =
        GTK_ENTRY(gtk_builder_get_object(builder, "input_product2_vat_rate"));
    input_product2_vat_value =
        GTK_ENTRY(gtk_builder_get_object(builder, "input_product2_vat_value"));
    input_product2_brutto =
        GTK_ENTRY(gtk_builder_get_object(builder, "input_product2_brutto"));
    input_product2_qty =
        GTK_COMBO_BOX_TEXT(gtk_builder_get_object(builder, "input_product2_qty"));
    input_total_netto =
        GTK_ENTRY(gtk_builder_get_object(builder, "input_total_netto"));
    input_total_vat_value =
        GTK_ENTRY(gtk_builder_get_object(builder, "input_total_vat_value"));
    input_total_brutto =
        GTK_ENTRY(gtk_builder_get_object(builder, "input_total_brutto"));
    input_total =
        GTK_ENTRY(gtk_builder_get_object(builder, "input_total"));
    model_faktura =
        GTK_TEXT_BUFFER(gtk_builder_get_object(builder, "model_faktura"));
    input_date =
        GTK_CALENDAR(gtk_builder_get_object(builder, "input_date"));
   input_invoice_nr =
        GTK_ENTRY(gtk_builder_get_object(builder, "input_invoice_nr"));
   input_currency =
        GTK_COMBO_BOX_TEXT(gtk_builder_get_object(builder, "input_currency"));

     g_signal_connect (window, "destroy",
                  G_CALLBACK (destroy), NULL);

    g_object_unref(builder);
    gtk_widget_show(window);
    gtk_main();

    return 0;
}

static void destroy(GtkWidget *widget, gpointer data)
{
    gtk_main_quit();
}

// PRODUCT 1 CHANGES
void on_input_product1_net_changed
    (GtkEditable *input_product1_net, GtkComboBoxText *input_product1_qty)
{
    char* pnet;
    char* pqt;
    char totals[50];
    float netto, qty, total;
    pnet = gtk_editable_get_chars(input_product1_net, 0, -1);
    netto = atof(pnet);
    pqt = gtk_combo_box_text_get_active_text(input_product1_qty);
    qty = atof(pqt);
    total = netto * qty;
    snprintf(totals,sizeof(totals), "%.2f", total);
    gtk_entry_set_text(input_product1_netto, totals);
    //free(pnet);free(pqt);
}

void on_input_product1_qty_changed
    (GtkComboBoxText *input_product1_qty, GtkEditable *input_product1_net)
{
    on_input_product1_net_changed(input_product1_net, input_product1_qty);
}

void on_input_product1_netto_changed
    (GtkEditable *input_product1_netto, GtkEntry *input_product1_vat_rate)
{
    const char* vat_rate;
    const char* netto;
    float vat_rate_float, total_float, vat_float, netto_float;
    char total[50];
    char vat[50];
    char total_netto[50];
    char total_vat_value[50];
    char total_brutto[50];

    vat_rate = gtk_entry_get_text(input_product1_vat_rate);
    netto = gtk_editable_get_chars(input_product1_netto, 0, -1);

    if (strcmp(vat_rate, "-") == 0) {
        vat_rate = "0";
    }

    vat_rate_float = atof(vat_rate);
    netto_float = atof(netto);
    total_netto_1 = netto_float;
    vat_float = netto_float * vat_rate_float / 100;
    total_vat_1 = vat_float;
    total_float = netto_float + vat_float;
    total_brutto_1 = total_float;
    snprintf(vat, sizeof(total), "%.2f", vat_float);
    snprintf(total, sizeof(total), "%.2f", total_float);
    snprintf(total_netto, sizeof(total_netto), "%.2f", total_netto_1 + total_netto_2);
    snprintf(total_vat_value, sizeof(total_vat_value), "%.2f", total_vat_1 + total_vat_2);
    snprintf(total_brutto, sizeof(total_brutto), "%.2f", total_brutto_1 + total_brutto_2);
    gtk_entry_set_text(input_product1_vat_value, vat);
    gtk_entry_set_text(input_product1_brutto, total);
    gtk_entry_set_text(input_total_netto, total_netto);
    gtk_entry_set_text(input_total_vat_value, total_vat_value);
    gtk_entry_set_text(input_total_brutto, total_brutto);
    gtk_entry_set_text(input_total, total_brutto);
}

void on_input_product1_vat_rate_changed
    (GtkEntry *input_product1_vat_rate, GtkEditable *input_product1_netto)
{
    on_input_product1_netto_changed(input_product1_netto, input_product1_vat_rate);
}
// PRODUCT1 CHANGES

// PRODUCT 2 CHANGES
void on_input_product2_net_changed
    (GtkEditable *input_product2_net, GtkComboBoxText *input_product2_qty)
{
    char* pnet;
    char* pqt;
    char totals[50];
    float netto, qty, total;
    pnet = gtk_editable_get_chars(input_product2_net, 0, -1);
    netto = atof(pnet);
    pqt = gtk_combo_box_text_get_active_text(input_product2_qty);
    qty = atof(pqt);
    total = netto * qty;
    snprintf(totals,sizeof(totals), "%.2f", total);
    gtk_entry_set_text(input_product2_netto, totals);
}

void on_input_product2_qty_changed
    (GtkComboBoxText *input_product2_qty, GtkEditable *input_product2_net)
{
    on_input_product2_net_changed(input_product2_net, input_product2_qty);
}

void on_input_product2_netto_changed
    (GtkEditable *input_product2_netto, GtkEntry *input_product2_vat_rate)
{
    const char* vat_rate;
    const char* netto;
    float vat_rate_float, total_float, vat_float, netto_float;
    char total[50];
    char vat[50];
    char total_netto[50];
    char total_vat_value[50];
    char total_brutto[50];

    vat_rate = gtk_entry_get_text(input_product2_vat_rate);
    netto = gtk_editable_get_chars(input_product2_netto, 0, -1);

    if (strcmp(vat_rate, "-") == 0) {
        vat_rate = "0";
    }

    vat_rate_float = atof(vat_rate);
    netto_float = atof(netto);
    total_netto_2 = netto_float;
    vat_float = netto_float * vat_rate_float / 100;
    total_vat_2 = vat_float;
    total_float = netto_float + vat_float;
    total_brutto_2 = total_float;
    snprintf(vat, sizeof(total), "%.2f", vat_float);
    snprintf(total, sizeof(total), "%.2f", total_float);
    snprintf(total_netto, sizeof(total_netto), "%.2f", total_netto_1 + total_netto_2);
    snprintf(total_vat_value, sizeof(total_vat_value), "%.2f", total_vat_1 + total_vat_2);
    snprintf(total_brutto, sizeof(total_brutto), "%.2f", total_brutto_1 + total_brutto_2);
    gtk_entry_set_text(input_product2_vat_value, vat);
    gtk_entry_set_text(input_product2_brutto, total);
    gtk_entry_set_text(input_total_netto, total_netto);
    gtk_entry_set_text(input_total_vat_value, total_vat_value);
    gtk_entry_set_text(input_total_brutto, total_brutto);
    gtk_entry_set_text(input_total, total_brutto);
}

void on_input_product2_vat_rate_changed
    (GtkEntry *input_product2_vat_rate, GtkEditable *input_product2_netto)
{
    on_input_product2_netto_changed(input_product2_netto, input_product2_vat_rate);
}
// PRODUCT2 CHANGES

void on_input_buyer_country_changed
    (GtkComboBox *input_buyer_country, GtkEntry *input_product1_vat_rate )
{
    const char* code;
    const char* vat;

    code = gtk_combo_box_get_active_id(input_buyer_country);
    vat  = get_vat_rate(code);
    gtk_entry_set_text(input_product1_vat_rate, vat);
}

const char* get_vat_rate(const char* code)
{
    size_t length = sizeof(rates)/sizeof(rates[0]);
    int i;

    for (i = 0 ; i<length; i++) {
        if (strstr(rates[i].country, code) != NULL) {
            return rates[i].rate;
        }
    }

    return "-";
}

void on_input_buyer_nip_changed
    (GtkEditable *input_buyer_nip, GtkComboBox *input_buyer_country)
{
    const char* code;
    code = gtk_combo_box_get_active_id(input_buyer_country);

    // if it's not from poland and if it has a vat rate, means that from EU
    if (strstr(code, "PL") == NULL && strstr(get_vat_rate(code), "-") == NULL) {
        gtk_entry_set_text(input_product1_vat_rate, "0");
    }
}

void on_btn_print_clicked()
{
    char* html;
    char* html_part;
    const char* vat_rate1;
    int vat;
    vat_rate1 = gtk_entry_get_text(input_product1_vat_rate);
    vat = atoi(vat_rate1);

    html = read_template("templates/shams.txt");
    html_part = read_template("templates/shams-loop.txt");
    html = insert_invoice_nr(html);
    html = insert_date(html);
    html = insert_seller(html);
    html = insert_buyer(html);
    html = insert_total_netto(html);
    html = insert_total_vat(html);
    html = insert_total_brutto(html);
    html = insert_total(html);
    html = insert_currency(html);
    html = insert_product_1(html, html_part);
    html = insert_product_2(html, html_part);

    if(strstr(vat_rate1, "0") != NULL && vat == 0) {
        html = insert_mentions(html, "Odwrotne obciążenie / Reverse charge");
    } else {
        html = insert_mentions(html, " ");
    }

    output_to_file(html);
    pdf_print();
    free(html);
}

void pdf_print()
{
    char path[100];
    char command[100];
    char fullpath[100];
    getcwd(path, sizeof(path));
    strcpy(command,"chromium --headless --disable-gpu --print-to-pdf ");
    strcpy(fullpath, path);
    strcat(fullpath, "/shams.html");
    strcat(command, fullpath);
    system(command);
}

char* insert_seller(char* html)
{
    const char* seller;
    char* buffer = malloc(5000*sizeof(char));
    seller = build_seller();
    buffer = replace_str(html, "%seller%", seller);
    return buffer;
}

const char* build_seller()
{
    char seller[1000] = {"\0"};
    const char* buffer;
    const char* name;
    const char* business;
    const char* address;
    const char* zip;
    const char* city;
    char* country;
    const char* nip;

    name = gtk_entry_get_text(input_seller_name);
    business = gtk_entry_get_text(input_seller_business);
    address = gtk_entry_get_text(input_seller_address);
    zip = gtk_entry_get_text(input_seller_zip);
    city = gtk_entry_get_text(input_seller_city);
    nip = gtk_entry_get_text(input_seller_nip);
    country = gtk_combo_box_text_get_active_text(input_seller_country);

    if (strlen(name) != 0)
    {

        strcat(seller, "<span class='name'>");
        strcat(seller, name);
        if (strlen(business) != 0)
        {
            strcat(seller, "<br/>");
            strcat(seller, business);
        }
        strcat(seller, "</span>");
    }

    if (strlen(address) != 0)
    {
        strcat(seller, address);
        strcat(seller, "<br/>");
    }

    if (strlen(city) != 0)
    {
        if (strlen(zip) != 0) {
            strcat(seller, zip);
            strcat(seller, ", ");
        }
        strcat(seller, city);
        strcat(seller, "<br/>");
    }

    if (country != NULL)
    {
        strcat(seller, country);
        strcat(seller, "<br/>");
    }

    if (strlen(nip) != 0)
    {
        strcat(seller, "<span class='nip'>");
        strcat(seller, "NIP ");
        strcat(seller, nip);
        strcat(seller, "</span>");
    }
    buffer = seller;
    return buffer;
}

char* insert_buyer(char* html)
{
    const char* buyer;
    char* buffer = malloc(5000*sizeof(char));
    buyer = build_buyer();
    buffer = replace_str(html, "%buyer%", buyer);
    return buffer;
}

const char* build_buyer()
{
    char buyer[1000] = {"\0"};
    const char* buffer;
    const char* name;
    const char* business;
    const char* address;
    const char* zip;
    const char* city;
    char* country;
    const char* nip;

    name = gtk_entry_get_text(input_buyer_name);
    business = gtk_entry_get_text(input_buyer_business);
    address = gtk_entry_get_text(input_buyer_address);
    zip = gtk_entry_get_text(input_buyer_zip);
    city = gtk_entry_get_text(input_buyer_city);
    nip = gtk_entry_get_text(input_buyer_nip);
    country = gtk_combo_box_text_get_active_text(input_buyer_country);

    if (strlen(name) != 0)
    {
        strcat(buyer, "<span class='name'>");
        strcat(buyer, name);
        if (strlen(business) != 0)
        {
            strcat(buyer, "<br/>");
            strcat(buyer, business);
        }
        strcat(buyer, "</span>");
    }

    if (strlen(address) != 0)
    {
        strcat(buyer, address);
        strcat(buyer, "<br/>");
    }

    if (strlen(city) != 0)
    {
        if (strlen(zip) != 0) {
            strcat(buyer, zip);
            strcat(buyer, ", ");
        }
        strcat(buyer, city);
        strcat(buyer, "<br/>");
    }

    if (country != NULL)
    {
        strcat(buyer, country);
        strcat(buyer, "<br/>");
    }

    if (strlen(nip) != 0)
    {
        strcat(buyer, "<span class='nip'>");
        strcat(buyer, nip);
        strcat(buyer, "</span>");
    }
    buffer = buyer;
    return buffer;
}

char* insert_invoice_nr(char* html)
{
    const char* invoice_nr;
    char* buffer = malloc(5000*sizeof(char));
    invoice_nr = gtk_entry_get_text(input_invoice_nr);
    buffer = replace_str(html, "%shamsnr%", invoice_nr);
    return buffer;
}

char* insert_date(char* html)
{
    GDate date;
    guint year, month, day;
    gsize buff_len = 11;
    char* buffer = malloc(5000*sizeof(char));
    char* datestr = malloc(11*sizeof(char));
    gtk_calendar_get_date(input_date, &year, &month, &day);
    g_date_set_dmy(&date, day, month + 1, year);
    g_date_strftime(datestr, buff_len, "%d.%m.%Y", &date);
    buffer = replace_str(html, "%shamsdate%", datestr);
    return buffer;
}

char* insert_total_netto(char* html)
{
    const char* total_netto;
    char* buffer = malloc(5000*sizeof(char));
    total_netto = gtk_entry_get_text(input_total_netto);
    buffer = replace_str(html, "%total_netto%", total_netto);
    return buffer;
}

char* insert_total_vat(char* html)
{
    const char* total_vat;
    char* buffer = malloc(5000*sizeof(char));
    total_vat = gtk_entry_get_text(input_total_vat_value);
    buffer = replace_str(html, "%total_vat%", total_vat);
    return buffer;
}

char* insert_total_brutto(char* html)
{
    const char* total_brutto;
    char* buffer = malloc(5000*sizeof(char));
    total_brutto = gtk_entry_get_text(input_total_brutto);
    buffer = replace_str(html, "%total_brutto%", total_brutto);
    return buffer;
}

char* insert_total(char* html)
{
    const char* total;
    char* buffer = malloc(5000*sizeof(char));
    total = gtk_entry_get_text(input_total);
    buffer = replace_str(html, "%total%", total);
    return buffer;
}

char* insert_currency(char* html)
{
    const char* currency;
    char* buffer = malloc(5000*sizeof(char));
    currency = gtk_combo_box_text_get_active_text(input_currency);
    buffer = replace_str(html, "%currency%", currency);
    buffer = replace_str(buffer, "%currency0%", currency);
    buffer = replace_str(buffer, "%currency1%", currency);
    buffer = replace_str(buffer, "%currency2%", currency);
    buffer = replace_str(buffer, "%currency3%", currency);
    return buffer;
}

char* insert_product_1(char* html, char* html_part)
{
    const char* name;
    const char* qty;
    const char* net;
    const char* netto;
    const char* vat_rate;
    const char* vat_value;
    const char* brutto;
    char* partial;
    char* tmp = malloc(5000*sizeof(char));

    name = gtk_entry_get_text(input_product1_name);
    qty = gtk_combo_box_text_get_active_text(input_product1_qty);
    net = gtk_entry_get_text(input_product1_net);
    netto = gtk_entry_get_text(input_product1_netto);
    vat_rate = gtk_entry_get_text(input_product1_vat_rate);
    vat_value = gtk_entry_get_text(input_product1_vat_value);
    brutto = gtk_entry_get_text(input_product1_brutto);

    if (strlen(name) != 0)
    {
        partial = build_product_row(html_part, name, qty, net, netto, vat_rate,
                vat_value, brutto);
        tmp = replace_str(html, "%product1%", partial);
        free(partial);
    }
    else
    {
        tmp = replace_str(html, "%product1%", "");
    }
    return tmp;
}

char* insert_product_2(char* html, char* html_part)
{
    const char* name;
    const char* qty;
    const char* net;
    const char* netto;
    const char* vat_rate;
    const char* vat_value;
    const char* brutto;
    char* partial;
    char* tmp = malloc(5000*sizeof(char));

    name = gtk_entry_get_text(input_product2_name);
    qty = gtk_combo_box_text_get_active_text(input_product2_qty);
    net = gtk_entry_get_text(input_product2_net);
    netto = gtk_entry_get_text(input_product2_netto);
    vat_rate = gtk_entry_get_text(input_product2_vat_rate);
    vat_value = gtk_entry_get_text(input_product2_vat_value);
    brutto = gtk_entry_get_text(input_product2_brutto);

    if (strlen(name) != 0)
    {
        partial = build_product_row(html_part, name, qty, net, netto, vat_rate,
                vat_value, brutto);
        tmp = replace_str(html, "%product2%", partial);
        free(partial);
    }
    else
    {
        tmp = replace_str(html, "%product2%", "");
    }
    return tmp;
}

char* build_product_row(char* html_part, const char* name, const char* qty,
        const char* net, const char* netto, const char* vat_rate,
        const char* vat_value, const char* brutto)
{
    char* partial = malloc(5000*sizeof(char));
    partial = replace_str(html_part, "%product_name%", name);
    partial = replace_str(partial, "%product_qty%", qty);
    partial = replace_str(partial, "%product_net%", net);
    partial = replace_str(partial, "%product_netto%", netto);
    partial = replace_str(partial, "%product_vat_rate%", vat_rate);
    partial = replace_str(partial, "%product_vat_value%", vat_value);
    partial = replace_str(partial, "%product_brutto%", brutto);
    return partial;
}

char* insert_mentions(char* html, char* mentions)
{
    char* buffer = malloc(5000*sizeof(char));
    buffer = replace_str(html, "%mentions%", mentions);
    return buffer;
}

void output_to_file(char* html)
{
    FILE* out = fopen("shams.html", "w+");
    if (out) {
        fprintf(out, "%s", html);
    }
    fclose(out);
}

char* read_template(char* location)
{
    FILE *f = fopen(location, "rb");
    fseek(f, 0, SEEK_END);
    long fsize = ftell(f);
    fseek(f, 0, SEEK_SET);

    char *string = malloc(fsize + 1);
    fread(string, fsize, 1, f);
    fclose(f);

    string[fsize] = 0;

    return string;
}

char* replace_str(char* str, const char* orig, const char* rep)
{
  static char temp[5000];
  static char buffer[5000];
  char* ret = malloc(5000*sizeof(char));
  char *p;

  strcpy(temp, str);

  if(!(p = strstr(temp, orig)))
    return temp;

  strncpy(buffer, temp, p-temp);
  buffer[p-temp] = '\0';

  sprintf(buffer + (p - temp), "%s%s", rep, p + strlen(orig));
  sprintf(ret, "%s", buffer);

  return ret;
}
