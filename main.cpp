#include<bits/stdc++.h>
#include<string>
using namespace std;
#define MAX_BOOK  10000
#define MAX_PAGE  10000
bool isRunning = true;
string int_to_string(int number){
	std::ostringstream ss;
    ss <<number;
    return ss.str();
}
//string generator
string gen(int length) {
    char chars[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'k', 'A', 'B', 'C', 'D', 'G', 'H', 'I', 'K', 'Z', 'X',
                    'V', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0'};
    int size = sizeof(chars) / sizeof(char);
    string gen_str;
    for (int i = 0; i < length; i++) {
        gen_str += chars[rand() % size];
    }
    return gen_str;
}


int get_int_range(int start = 0,int end = 0,string content = ""){
    int number = 0;
    do {
        cout<<content<<endl;
        cin>>number;
    } while (number < start || number > end);
    return number;
}
tm *get_now(){
    time_t tt;
    tm *ti;
    time(&tt);
    ti = localtime(&tt);
    return ti;
}

struct Time {
    int minute;
    int hours;
    int day;
    int month;
    int year;

    void GetData() {
    	fflush(stdin);
        tm *now = get_now();
        this->day = get_int_range(1,30,"\tNhap Ngay: ");
        this->month = get_int_range(1,12,"\tNhap Thang: ");
        this->year = get_int_range(0,now->tm_year + 1990,"\tNhap Nam: ");
    }

    string get_publish_time() {
        return int_to_string(this->day) + "/" + int_to_string(this->month) + "/" +
               int_to_string(this->year);
    }
	

    string get_full_time() {
        return int_to_string(this->hours) + " : " + int_to_string(this->minute) + " " +
               int_to_string(this->day) + "/" + int_to_string(this->month) + "/" +
               int_to_string(this->year);
    }
};


struct Book {
    string ID;  // Ma Sach
    string book_name;  // Ten Sach
    string author;		// Tac gia	
    string publisher; // nha xuat ban;
    Time *date_publish;
    int count;

    void print() {
    	
        cout << endl;
        cout << "ID: " << this->ID;
        cout << "\t\nTen Sach: " << this->book_name ;
        cout << "\t\nTac Gia: " << this->author ;
        cout << "\t\nNha Xuat Ban: " << this->publisher ;
        cout << "\t\nNgay Nhap Sach: " << this->date_publish->get_publish_time();
        cout << endl;
    }

    void GetData() {
        fflush(stdin);
        cout << "\tNhap ID Sach: ";
        getline(std::cin, this->ID);
        cout << "\tNhap Ten Sach: ";
        getline(std::cin, this->book_name);
        cout << "\tNhap Tac Gia: ";
        getline(std::cin, this->author);
        cout << "\tNhap Nha Xuat Ban: ";
        getline(std::cin, this->publisher);
        cout << "--- Nhap Thoi Gian Xuat Ban--- " << endl;
        this->date_publish = new Time();
        this->date_publish->GetData();
        this->count =get_int_range(1,MAX_BOOK,"\tNhap Vao So Sach: ");
    }
};

//start
struct NodeBook {
    Book *book;
    NodeBook *p_next;
};

NodeBook *create_node_book(Book *data) {
    NodeBook *new_node = new NodeBook();
    new_node->p_next = NULL;
    new_node->book = data;
    return new_node;
}

struct ListBook {
    NodeBook *head;
    NodeBook *tail;

    int get_count() {
        NodeBook *start = this->head;
        int count = 0;
        while (start != NULL) {
            count++;
            start = start->p_next;
        }
        return count;
    }

    void show_list() {
    	system("cls");
        NodeBook *start = this->head;
        cout<<"\tHien Thi Tat Ca Sach Trong Kho"<<endl;
        while (start != NULL) {
            start->book->print();
            start = start->p_next;
        }
    }

    bool addToHead(NodeBook *new_node) {
        try {
            if (this->head == NULL) {
                this->head = new_node;
                this->tail = new_node;
            } else {
                NodeBook *temp = this->head;
                this->head = new_node;
                this->head->p_next = temp;
                delete temp;
            }
            return true;
        } catch (int err) {
            cout << "\tERROR!!!";
            return false;
        }
    }

    NodeBook *search_by_id(string book_id) {
        NodeBook *start = this->head;
        while (start != NULL) {
            if (start->book->ID == book_id) {
                return start;
            }
            start = start->p_next;
        }
        return NULL;
    }

    NodeBook *get_pre_node(string book_id) {
        NodeBook *start = this->head;
        NodeBook *pre = start;
        while (start != NULL) {
            if (start->book->ID == book_id) {
                return pre;
            }
            pre = start;
            start = start->p_next;
        }
        return NULL;
    }

    bool remove(string book_id) {
        try {
            NodeBook *remove_node = this->search_by_id(book_id);
            if (remove_node != NULL) {
                NodeBook *pre_node = this->get_pre_node(book_id);
                if (pre_node != NULL) {
                    pre_node->p_next = remove_node->p_next;
                    delete remove_node;
                } else {
                    this->head = remove_node->p_next;
                    delete remove_node;
                }
                return true;
            } else {
                cout << "\tKhong Tim Thay\n";
            }
            return false;
        } catch (int err) {
            cout << "\tERROR!!!" << endl;
        }

    }

    bool update(NodeBook *update_node, string ID) {
        try {
            if (update_node != NULL) {
                NodeBook *node = this->search_by_id(ID);
                if (node != NULL) {
                    node->book = update_node->book;
                    return true;
                }
            } else {
                cout << "\tKhong Tim Thay" << endl;
            }
            return false;
        } catch (int err) {
            cout << "\tERROR!!!" << endl;
        }
    }

    bool isExit(string book_id) {
        NodeBook *has = this->search_by_id(book_id);
        return has != NULL;
    }
};
// end


struct Bill {
    string ID;
    Book *book;
    Time *import_date;
    bool isSale;

    void create_bill_data(Book *book, bool isSale) {
        this->ID = gen(10);
        this->book = book;
        this->import_date = this->process_date();
        this->isSale = isSale;
    }

    void Print(){
        this->book->print();
        cout<<"\tNgay Nhap Sach: "<<this->import_date->get_full_time()<<endl;
        cout<<endl;
    }

    Time *process_date() {
        Time *t_time = new Time();

        tm *ti = get_now();
        t_time->day = ti->tm_mday;
        t_time->month = ti->tm_mon + 1;
        t_time->year = ti->tm_year + 1900;
        t_time->minute = ti->tm_min;
        t_time->hours = ti->tm_hour;
        return t_time;
    }

};

struct NodeBill {
    Bill *bill;
    NodeBill *p_next;
};

NodeBill *create_node_bill(Bill *bill) {
    NodeBill *new_node_bill = new NodeBill();
    new_node_bill->bill = bill;
    new_node_bill->p_next = NULL;
    return new_node_bill;
}

struct ListBill {
    NodeBill *head = NULL;
    NodeBill *tail = NULL;

    void show_list_import_bill() {
    	system("cls");
    	cout<<"\tHien Thi Tat Ca Sach Da Nhap ";
        NodeBill *start = this->head;
        while (start != NULL){
            if (start->bill->isSale == false){
                start->bill->Print();
            }
            start = start->p_next;
        }
    }

    bool AddToHead(NodeBill *new_bill) {
        if (this->head == NULL) {
            this->head = new_bill;
            this->tail = new_bill;
        } else {
            NodeBill *temp = this->head;
            this->head = new_bill;
            new_bill->p_next = temp;
            delete temp;
        }
    }
};


int main_menu() {
    int select = 0;
    do {
        try {
            cout << "==========================================" << endl;
            cout << "\t\tNha Sach ABCD" << endl;
            cout << "\t[1].Tat Ca Sach Con Trong Kho " << endl;
            cout << "\t[2].Thao Tac Voi Kho Sach " << endl;
            cout << "\t[3].Danh Sach Sach Da Ban " << endl;
            cout << "\t[4].Lich Su Nhap Sach " << endl;
            cout << "\t[0].EXIT " << endl;
            cout << "==========================================" << endl;
            cout << "\tNhap lua chon cua ban: ";
            cin >> select;
        } catch (int err) {
            std::cin.ignore(INT_MAX);
            cout << "\tNhap Dung Du Lieu Nao!" << endl;
        }
        if (select <= 0 || select > 5) {
            cout << "\tKhong Co Lua Chon Nao Nhu Vay!" << endl;
        }
    } while (select <= 0 || select > 5);
    return select;
}

int crud_menu() {
    int select = 0;
    do {
        try {
            cout << "==========================================" << endl;
            cout << "\t\tThao Tac Voi Kho Sach" << endl;
            cout << "\t[1].Nhap Sach" << endl;
            cout << "\t[2].Ban Sach" << endl;
            cout << "\t[3].Sua Thong Tin Sach" << endl;
            cout << "\t[4].Exit" << endl;
            cout << "==========================================" << endl;
            cout << "\tNhap Lua Chon Cua Ban: ";
            cin >> select;
        } catch (int err) {
            std::cin.ignore(INT_MAX);
            cout << "\tNhap Dung Du Lieu!" << endl;
        }
        if (select <= 0 || select > 4) {
            cout << "\tKhong Co Lua Chon Nao Nhu Vay!" << endl;
        }
    } while (select <= 0 || select > 4);
    return select;
}

void AddBook(ListBook *&list_book, ListBill *&list_bill) {
    cout << "----------------------Them Sach------------------\n";
    do {
        Book *new_book = new Book();
        new_book->GetData();
        if (!(list_book->isExit(new_book->ID))) {
            NodeBook *new_node_book = create_node_book(new_book);
            Bill *import_bill = new Bill();
            import_bill->create_bill_data(new_book, false);
            NodeBill *new_node_bill = create_node_bill(import_bill);
            list_bill->AddToHead(new_node_bill);
            if (list_book->addToHead(new_node_book)) {
                cout << "\tThem Thanh Cong" << endl;
                return;
            } else {
                cout << "\tThem That Bai" << endl;
                cout << "\tNhap Lai!" << endl;
            }
        } else {
            cout << "\tID Da Ton Tai!" << endl;
        }
    } while (true);
}

void switch_crud_menu(int chose, ListBook *&list_book, ListBill *&list_bill, bool &isCrud) {
    switch (chose) {
        case 1:
            AddBook(list_book, list_bill);
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            isCrud = false;
            break;
        default:
            cout << "\tKhong Co Lua Chon Nao Nhu Vay!";
            break;
    }
}

void run_crud(ListBook *&list_book, ListBill *&list_bill) {
    bool isCrud = true;
    while (isCrud) {
        int select_crud = crud_menu();
        switch_crud_menu(select_crud, list_book, list_bill, isCrud);
    }
}

void switch_main_menu(int chose, ListBook *&list_book, ListBill *&list_bill) {
    switch (chose) {
        case 1:
            if (list_book->get_count() > 0) {
                list_book->show_list();
            } else {
                cout << "\n\tKho rong!\n";
            }
            break;
        case 2:
            run_crud(list_book, list_bill);
            break;
        case 3:
			// Danh sách sách đã bán
            break;
        case 4:
                list_bill->show_list_import_bill();
            break;
        case 0:
            isRunning = false;
            break;
        default:
            cout << "\tKhong Co Lua Chon Nao Nhu Vay!";
            break;
    }
}

int run() {
    // init data;

    ListBook *list_book = new ListBook();
    ListBill *list_bill = new ListBill();

    while (isRunning) {
        int select = main_menu();
        switch_main_menu(select, list_book, list_bill);
    }
}

int main() {
    run();
}
