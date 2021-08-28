//PR2PO Application
//Command driven procurement Application
//Create a purchase requisition
//View purchase details
//convert purchase requisition into purchase order

#include <iostream>
#include <string>
#include <ncurses.h>
#include <stdlib.h>
#include <fstream>
#include <ctime>
using namespace std;
/*Function definition for setting cursor position in the console window*/
float price_list[20] = {865, 2.25, 44, 10, 20, 7710, 33.33, 48.97, 8, 0.5, 0.01, 88, 999, 25000, 87, 4, 22, 200, 20, 150};

class po;
//class definition
class requisition
{
    static int req_no;
    int item_code;
    int qty;
    string delivery_date;

public:
    //class function declaration
    void get_data();
    void display();
    friend void generate(requisition, po); //friend fn declaration
};
//fn definition for receiving requisition details

void requisition ::get_data()
{
    system("cls");
    req_no++;
    cout << "Product Item code";
    cin >> item_code;
    cout << "Quantity: ";
    cin >> qty;
    cout << "Delivery date : ";
    cin >> delivery_date;
    cin.clear();
    cin.ignore(1000, '\n');
    getline(cin, delivery_date);
}
// definition of the static data member
int requisition ::req_no;

// funtion for displaying requisition details
void requisition ::display()
{
    system("cls");
    cout << "Requisition No: " << req_no;
    cout << "/nProduct Item Code : " << item_code;
    cout << "/nDelivery date: " << delivery_date;
}

class po
{
    static int po_no;

public:
    //constructor is used for incrementing the static variable po_no
    po()
    {
        po_no++;
    }

    friend void generate(requisition, po); //friend function
};

//defining static variable po_no
int po::po_no;

//defining friend function generate
void generate(requisition r, po p)
{
    ofstream fout;
    //retriving system data and time
    time_t current = time(0);
    char *dt = ctime(&current);
    //Opening  the current_PO.txt file in which PO details are stored
    fout.open("Current_PO.txt");
    //generating the PO and storing it in  the Current_PO.txt file in the formatted manner
    fout << "\t\t\t  Purchase Order# : " << p.po_no << "/n";
    fout << "\t\t\t______________________/n/n";
    fout << "Requisition#: " << r.req_no << "\t\t\t\tIssue Date :" << dt << "/n/n";

    if (r.item_code >= 1 && r.item_code <= 10)
        fout << "Supplier : "
             << "SKS INC/n/n";
    else if (r.item_code >= 11 && r.item_code <= 20)
        fout << "Supplier : "
             << "KC spare parts Ldt./n/n";
    else
        fout << "Suppiler : "
             << "Other(_______________)/n/n";
    fout << "Delivery Date: " << r.delivery_date << "/n/n";
    fout << "------------------------------------------------------------------------------/n";
    fout << "                      ** Line Items ** /n";
    fout << "------------------------------------------------------------------------------/n";
    fout << "Item_code\t\tQuantiy\t\tPrice\t\tTotal\n";
    fout << "_________\t\t_______\t\t_____\t\t_____\n\n";
    fout << " " << r.item_code << "\t\t\t" << r.qty << "\t\t\t";
    if (r.item_code >= 1 && r.item_code <= 20)
    {
        fout << " " << price_list[r.item_code - 1] << "\t\t\t" << price_list[r.item_code - 1] * r.qty << "\n\n\n\n\n";
    }
    else
        fout << "_ _ _ \t\t\t _ _ _\n\n\n\n";
    ifstream fin;
    char line[80];
    //opening the terms.txt file from where standard terms and conditions are copied into the po
    fin.open("terms.txt");
    while (fin)
    {
        fin.getline(line, 80);
        fout << line << "\n";
    }
    fin.close();
    fout << "\n\n\\n\n Authorized signature: \t\t\t\t\t\\t Total: _ _ _ ";
    fout.close();
}

void main()
{

    requisition r;
    char flag = 'f';
    char ch;
    //Displaying a menu to accept user commands
    while (1)
    {
        system("cls");
        cout << "PR2PO";
        cout << "______";
        cout << "1- Create New Requisition";
        cout << "2- Display Requisition";
        cout << "3- Generate PO";
        cout << "4- Exit";
        cout << "Select an option by typing the numerical code:";
        cin >> ch;
        switch (ch)

        {
        case ('1'):
            r.get_data();
            flag = 't'; /* code */
            break;
        case ('2'):
            if (flag = 'f')
            {
                cout << "Requisition details not yet entered! Press any key to continue"; /* code */
            }
            else
                r.display();
            break;
        case ('3'):
            po p;
            generate(r, p);
            cout << "PR has been converted into a PO. You can view the Current_PO.txt file to view the generated PQ and take its print out"; /* code */

            break;
        case ('4'):
            exit(1);
            /* code */
            break;

        default:
            cout << "Invalid Choice! Press any key to continue..";

            break;
        }
    }
}
