#include<iostream>
#include<conio.h>
#include<iomanip>
#include<fstream>
#include<string>
#include <algorithm>// for find
#include <sstream>
#include <limits>
#include<cctype> // for tolower
#include <ctime>
#include<windows.h>

using namespace std;

fstream menu;
fstream cart;//cart file
fstream purchasehistory;
struct Flavor {
    string name;
    float price;
    Flavor* next;
};

struct AddOn {
    string name;
    float price;
    AddOn* next;
};

struct Node {
    string admin_id;
    string admin_name;
    string admin_hp;
    string admin_pw;
    Node* next;
};

struct Food{
	string foodName,name,username;
	float foodPrice,price,subtotal;
	int qty;
   Food* next;
}p[100];

struct Product {
    string name;
    float price;
    Product* next;
};

struct main_menu
{
	string name, id,num,password;

	float price, total;
	int quantity;
}x[100];
void viewmenu();
void addBurger();
void editBurger();
void deleteBurger();
void rootAdminFunctionality();
void viewhistory();
void sortmenu();
void sortbyname();
void sortbyprice();
void searchBurger();
void adminpage();
void adminlogin();
void adminmainpage();
void adminLoginPage();
void login();
void registration();
void forgot();
void userprofile();
void mainpage();
void LoginHome();
void deleteOrder();
void dl();
void sp();
void viewmenu();
void freeCart();
void searchproduct();
void sortPrice();
void sortmenu();
void viewhistory();
void viewhistorys();
void viewmenus();
void admin_customer();
string loggedInUsername = "";

bool compareAdminData(const Node& admin, const string& key) //To compare admin data 
{
    string lowerAdminID = admin.admin_id;
    transform(lowerAdminID.begin(), lowerAdminID.end(), lowerAdminID.begin(), ::tolower);
    string lowerAdminName = admin.admin_name;
    transform(lowerAdminName.begin(), lowerAdminName.end(), lowerAdminName.begin(), ::tolower);
    string lowerAdminContextNumber = admin.admin_hp;
    transform(lowerAdminContextNumber.begin(), lowerAdminContextNumber.end(), lowerAdminContextNumber.begin(), ::tolower);
    string lowerAdminPassword = admin.admin_pw;
    transform(lowerAdminPassword.begin(), lowerAdminPassword.end(), lowerAdminPassword.begin(), ::tolower);

    return lowerAdminID.find(key) != string::npos ||
           lowerAdminName.find(key) != string::npos ||
           lowerAdminContextNumber.find(key) != string::npos ||
           lowerAdminPassword.find(key) != string::npos;
}

class Receipt//for generate receipt
{
	public:
		
		~Receipt()
		{	cout<<"\n\t\t\t\t\t\t= End of Receipt ="<<endl;
		}
		void payment()//for admin to enter how much does the user pay
		{	int i=0;
			float customer_pay=0;
			float customer_changes=0;
			float grand_total=0;
			ifstream read;
			
			read.open("cart.txt");
			
			cout<<"\t\t\t\t\t\tMMU Fast-Food "<<endl;
			cout<<"\t\t\t\t\tJalan Ayer Keroh Lama, 75450 Bukit Beruang"<<endl;
			cout<<"\t\t\t\t\t\t Melaka , Malaysia"<<endl;
			cout<<"\t\t\t\t\t\tTEL : 019-7753357"<<endl;
			cout<<"\t---------------------------------------------------------------------------------------------------------"<<endl;
			cout<<"\t-\t\t\t\t\t\tReceipt\t\t\t\t\t\t\t-"<<endl;
			cout<<"\t---------------------------------------------------------------------------------------------------------"<<endl;
			cout<<"\tUsername : "<<loggedInUsername<<endl;
			cout<<"\t\tItem ID\t\tItem Name\t\t\tItem Price\tQuantity\tTotal Price"<<endl;
			while(!read.eof())
			{	read.ignore();
				getline(read,p[i].foodName)>>p[i].foodPrice;
				read>>p[i].qty;
				read>>p[i].subtotal;
				
				cout<<"\t\t"<<i+1;
				cout<<"\t\t"<<left<<setw(30)<<p[i].foodName;
				cout<<"RM "<<right<<setw(5)<<fixed<<setprecision(2)<<p[i].foodPrice<<"\t\t"<<p[i].qty<<"\t\t"<<p[i].subtotal<<endl;
				grand_total += p[i].subtotal;
				i++;
			}
			read.close();
			
			cout<<"\n\t---------------------------------------------------------------------------------------------------------"<<endl;
			cout<<"\t\t\t\t\tGrand Total              : RM "<<grand_total<<endl<<endl;
			cout<<"\t\t\t\t\tCustomer Pay             : RM ";
			cin>>customer_pay;
			fflush(stdin);
			cin.clear();
			
			while(customer_pay<grand_total)
			{	cout<<"\n\t\t\t\t\tIncorrect Amout. Reenter again"<<endl;
				cout<<"\t\t\t\t\tCustomer Pay             : RM ";
				cin>>customer_pay;
				fflush(stdin);
				cin.clear();
			}
			customer_changes=customer_pay-grand_total;
			cout<<"\n\t\t\t\t\tCustomer Changes         : RM "<<customer_changes<<endl;
			cout<<"\n\t---------------------------------------------------------------------------------------------------------"<<endl;
			cout<<("\n\t\t\t\t\tDear Customer, Have A Great Day !");
			cout<<("\n\t\t\t\t\t    Thank You for Choosing Us !");
			
			
			ofstream pur("purchase.txt");
			    
			    for (int k= 0; k < i; k++)
			    {
			    	
			        pur << "\n" << p[k].foodName;
			        pur << "\n"<< p[k].foodPrice;
			        pur << "\n" << p[k].qty;
					pur <<"\n"<< p[k].subtotal;
					
			    }
			
			    pur.close();
			    ofstream ord("order_details.txt", ios::app);
			    
			    for (int y= 0; y < i; y++)
			    {
			    	p[y].foodName.erase(remove_if(p[y].foodName.begin(), p[y].foodName.end(), ::isspace), p[y].foodName.end());
			    	ord<<"\n"<<loggedInUsername;
			        ord <<"\t"<< p[y].foodName;
			        ord <<"\t"<< p[y].foodPrice;
			        ord <<"\t"<< p[y].qty;
					ord <<"\t"<< p[y].subtotal;
					
			    }
			
			    ord.close();
			    
			    ofstream detail("purchasedetail.txt");
			    
			    detail<<loggedInUsername<<endl;
			    
			    detail<<customer_pay<<endl;
			    detail<<customer_changes;
			    detail.close();
			    
				
				ofstream clearCart("cart.txt", ios::trunc);
    			clearCart.close();
			    getche();
		}
};

class Menu:public Receipt{ 
	private:
		int item,qty,choice;
		Food* cartHead;
		string itemName;
    	float itemPrice;
	public:
		
		Menu() {
			cartHead = NULL; 
		}
		
		Menu(string name, float price) : itemName(name), itemPrice(price) {}

	    void displayItem() {
	        cout << "Item: " << itemName << ", Price: RM " << fixed << setprecision(2) << itemPrice << endl;
	    }
	
	    string getName() const {
	        return itemName;
	    }
	
	    float getPrice() const {
	        return itemPrice;
	    }
			
		void viewpurchase(){
			int i=0;
			float grand_total=0;
			string user_N,line;
			float customer_P,customer_C;
			bool found=false;
	
		    ifstream purchase("purchase.txt");
		      ifstream order("order_details.txt");
		    ifstream details("purchasedetail.txt");
		    
		    while(details){
            	getline(details,user_N);
            	details>>customer_P;
            	details>>customer_C;
			}
			details.close();

            cout<<"\t\t\t\t\t\tMMU Fast-Food"<<endl;
			cout<<"\t\t\t\t\t\tJalan Ayer Keroh Lama, 75450 Bukit Beruang"<<endl;
			cout<<"\t\t\t\t\t\t Melaka , Malaysia"<<endl;
			cout<<"\t\t\t\t\t\tTEL : 019-7753357"<<endl;
			cout<<"\t---------------------------------------------------------------------------------------------------------"<<endl;
			cout<<"\t-\t\t\t\t\t\tOrder History\t\t\t\t\t\t-"<<endl;
			cout<<"\t---------------------------------------------------------------------------------------------------------"<<endl;
				cout<<"\tUsername : "<<loggedInUsername<<endl;
			cout<<"\tItem ID\t\tItem Name\t\t\tItem Price\tQuantity\tTotal Price"<<endl;
            while (getline(order, line)) {
           istringstream iss(line);
            iss >> p[i].username>>p[i].foodName>>p[i].foodPrice >> p[i].qty >> p[i].subtotal;
        
             	if(p[i].username == loggedInUsername)
             	{
             	found = true;
             	cout << "\t" << i + 1;
        		cout << "\t\t" << left << setw(30) << p[i].foodName;
        		cout << "RM " << right << setw(5) << fixed << setprecision(2) << p[i].foodPrice << "\t\t" << p[i].qty << "\t\t" << p[i].subtotal << endl;
       			grand_total += p[i].subtotal;
       			i++;
				 }
			  }
	
			  order.close();
			    if (!found) {
        cout << "No orders found for username: " << loggedInUsername << endl;
    }
            
            cout<<"\t---------------------------------------------------------------------------------------------------------"<<endl;
			cout<<("\n\t\t\t\t\tDear Customer, Have A Great Day !");
			cout<<("\n\t\t\t\t\t    Thank You for Choosing Us !");
			
			cout<<"\n\nPress any key to continue"<<endl;
			getche();
		}
		
		void viewcart()//for user to check what they have select
		{	int i=0;
			cart.open("cart.txt",ios::in);
			cout<<"\t---------------------------------------------------------------------------------------------------------"<<endl;
			cout<<"\t-\t\t\t\t\t\tCart\t\t\t\t\t\t\t-"<<endl;
			cout<<"\t---------------------------------------------------------------------------------------------------------"<<endl;
			cout<<"\tItem No.\tFast-Food Name\t\tFast-Food Price\t\tQuantity\tTotal Price"<<endl;
			
			while (cart.peek() == '\n') {
			    cart.ignore();
			}
			
			
			while(!cart.eof())
			{	
				
				getline(cart,p[i].foodName)>>p[i].foodPrice;
				cart>>p[i].qty;
				cart>>p[i].subtotal;
				cart.ignore();

				cout<<"\t"<<i+1; 
				cout<<"\t\t"<<left<<setw(30)<<p[i].foodName;
				cout<<"RM "<<right<<setw(5)<<fixed<<setprecision(2)<<p[i].foodPrice<<"\t\t"<<p[i].qty<<"\t\t"<<p[i].subtotal<<endl;

				i++;
			}
			cart.close();
			cout<<"\n\n\n"<<endl;
			cout<<"Press any key to continue...";
			getche();
			confirmOrder();
		}
		
void deleteOrder()
		{
		    int i = 0;
		    cart.open("cart.txt", ios::in);
		
		    cout << "\t---------------------------------------------------------------------------------------------------------" << endl;
		    cout << "\t-\t\t\t\t\t\tCart\t\t\t\t\t\t\t-" << endl;
		    cout << "\t---------------------------------------------------------------------------------------------------------" << endl;
		    cout << "\tItem No.\tFast-Food Name\t\tFast-Food Price\t\tQuantity\tTotal Price" << endl;
		
		    // Clear the existing linked list
		    while (cartHead != NULL)
		    {
		        Food* current = cartHead;
		        cartHead = cartHead->next;
		        delete current;
		    }
		
		    while (!cart.eof())
		    {
		        Food* newFood = new Food;
		        cart.ignore();
		        getline(cart, newFood->foodName);
		        cart >> newFood->foodPrice;
		        cart >> newFood->qty;
		        cart >> newFood->subtotal;
		        newFood->next = NULL;
		
		        
		
		        if (cartHead == NULL)
		        {
		            cartHead = newFood;
		        }
		        else
		        {
		            Food* current = cartHead;
		            while (current->next != NULL)
		            {
		                current = current->next;
		            }
		            current->next = newFood;
		        }
		
		        cout << "\t" << i + 1;
		        cout << "\t\t" << left << setw(30) << newFood->foodName;
		        cout << "RM " << right << setw(5) << fixed << setprecision(2) << newFood->foodPrice << "\t\t" << newFood->qty << "\t\t" << newFood->subtotal << endl;
		
		        i++;
		    }
		    cart.close();
		
		    cout << "\n\n\t\t Enter the item you want to delete [0 return back]: ";
		    int del;
		    cin >> del;
		    fflush(stdin);
		    cin.clear();
		    
		    while(del < 0 || del >i){
		    	cout << "\n\n\t\t Item not found. Enter the item you want to delete: ";
		    	cin >> del;
			    fflush(stdin);
			    cin.clear();
			}
		
		    if (del == 0)
		    {
		    
		        system("CLS");
		        confirmOrder();
		    }
		    else
		    {
		        Food* current = cartHead;
		        Food* prev = NULL;
		        int count = 1;
		
		        // Traverse the linked list to find the item to delete
		        while (current != NULL && count < del)
		        {
		            prev = current;
		            current = current->next;
		            count++;
		        }
		
		        if (current != NULL)
		        {
		            if (prev != NULL)
		            {
		                prev->next = current->next;
		            }
		            else
		            {
		                cartHead = current->next;
		            }
		            delete current;
		        }
		
		        ofstream d_file("cart.txt");
		
		        current = cartHead;
		        i = 1;
		
		        // Rewrite the cart file after deleting the item
		        while (current != NULL)
		        {
		            d_file <<"\n"<< current->foodName << endl;
		            d_file << fixed << setprecision(2) << current->foodPrice << endl;
		            d_file << current->qty << endl;
		            d_file << fixed << setprecision(2)<< current->subtotal;
		
		            current = current->next;
		            i++;
		        }
		
		        d_file.close();
		        cout << "\n\n\n" << endl;
		        cout<<"delete successfully"<<endl;
		        cout<<"Press any keyword to continue......";
		        getche();
		        system("CLS");
		        deleteOrder();
		        
		        
		    }
		}
	
void freeCart(){
		    Food* current = cartHead;
		    while (current != NULL)
		    {
		        Food* temp = current;
		        current = current->next;
		        delete temp;
		    }
		    cartHead = NULL;
		}
		
void addToCart(const Food& food) {
			Food* newFood = new Food;
			newFood->foodName = food.foodName;
			newFood->foodPrice = food.foodPrice;
			newFood->subtotal = food.subtotal;
			newFood->qty = food.qty;
			newFood->next = NULL;
	
			if (cartHead == NULL) {
				cartHead = newFood;
			}
			else {
				Food* current = cartHead;
				while (current->next != NULL) {
					current = current->next;
				}
				current->next = newFood;
			}
		}
		
		void editOrder() {
		int i = 0, editNum, newQty;
		Food* head = NULL;
		Food* current = NULL;
	
		ifstream cart("cart.txt");
		if (!cart) {
			cout << "Error opening cart.txt file." << endl;
			return;
		}
		ifstream purchase("purchase.txt");
		if (!purchase) {
			cout << "Error opening cart.txt file." << endl;
			return;
		}
	
		cout << "\t---------------------------------------------------------------------------------------------------------" << endl;
		cout << "\t-\t\t\t\t\t\tCart\t\t\t\t\t\t\t-" << endl;
		cout << "\t---------------------------------------------------------------------------------------------------------" << endl;
		cout << "\tItem No.\tFast-Food Name\t\tFast-Food Price\t\tQuantity\tTotal Price" << endl;
	
		while (!cart.eof()) {
			Food* newNode = new Food();
			cart.ignore();
			getline(cart, newNode->foodName);
			cart >> newNode->foodPrice;
			cart >> newNode->qty;
			cart >> newNode->subtotal;
			
	
			newNode->next = NULL;
	
			if (head == NULL) {
				head = newNode;
				current = newNode;
			}
			else {
				current->next = newNode;
				current = newNode;
			}
	
			cout << "\t" << i + 1;
			cout << "\t\t" << left << setw(30) << current->foodName;
			cout << "RM " << right << setw(5) << fixed << setprecision(2) << current->foodPrice << "\t\t" << current->qty << "\t\t" << current->subtotal << endl;
	
			i++;
		}
	
		cart.close();
	
		cout << "\n\tEnter the Order No you want to edit: ";
		cin >> editNum;
		fflush(stdin);
		cin.clear();
	
		while (editNum < 1 || editNum > i) {
			cout << "\n\tOrder No not found.";
			getche();
			system("CLS"); 
			confirmOrder();
		
		}
	
		cout << "\n\tEnter the new quantity for the product: ";
		cin >> newQty;
		if(newQty<1)
		{
			cout<<"The Quantity can not less than 1. Enterthe new quantity for the product:";
				cin >> newQty;
			    fflush(stdin);
		}
	
		current = head;
		int count = 1;
		while (count < editNum) {
			current = current->next;
			count++;
		}
	
		current->qty = newQty;
	
		// Update the cart file with the new quantity
		ofstream updatedCart("cart.txt");
		if (!updatedCart) {
			cout << "Error opening cart.txt file for writing." << endl;
			return;
		}
		ofstream updatedPurchase("purchase.txt");
			if (!updatedPurchase) {
			cout << "Error opening cart.txt file for writing." << endl;
			return;
		}
	
		current = head;
		while (current != NULL) {
			current->subtotal=current->qty*current->foodPrice;
			updatedCart <<endl<< current->foodName << endl;
			updatedCart << current->foodPrice << endl;
			updatedCart << current->qty << endl;
			updatedCart << current->subtotal;
			updatedPurchase <<endl<< current->foodName << endl;
			updatedPurchase << current->foodPrice << endl;
			updatedPurchase << current->qty << endl;
			updatedPurchase << current->subtotal;
	
			Food* temp = current;
			current = current->next;
			delete temp;
		}
	
		updatedCart.close();
		updatedPurchase.close();
		cout << "\n\tEdit successful." << endl;
		cout << "Press any key to continue..." << endl;
		getche();
	}
		
		void confirmOrder()
		{
		    int choice;
		    
		    do {
		        system("CLS");
		        cout << "\t\t\t\t--------------------------------------------------" << endl;
		        cout << "\t\t\t\t\t\tConfirm Order" << endl;
		        cout << "\t\t\t\t--------------------------------------------------" << endl;
		        cout << "\t\t\t\t\t    No.  |  Selection" << endl;
		        cout << "\t\t\t\t--------------------------------------------------" << endl;
		        cout << "\t\t\t\t\t     1.  | View Cart" << endl;
		        cout << "\t\t\t\t\t     2.  | Delete Order" << endl;
		        cout << "\t\t\t\t\t     3.  | Edit Order"<<endl;
		        cout << "\t\t\t\t\t     4.  | Add More Order" << endl;
		        cout << "\t\t\t\t\t     5.  | Payment" << endl;
		
		        cout << "\n\t\t\t\tSelect your choice [ 1 - 5 ] : ";
		        cin >> choice;
		        fflush(stdin);
		        cin.clear();
		
		        while (choice < 1 || choice > 5)
		        {
		            cout << "\t\t\t\tInvalid code" << endl;
		            cout << "\t\t\t\tPlease Reenter the choice : ";
		            cin >> choice;
		            fflush(stdin);
		            cin.clear();
		        }
		
		        switch (choice)
		        {
			        case 1:
			            system("CLS");
			            viewcart();
			            break;
			        case 2:
			            system("CLS");
			            deleteOrder(); //delete record here
			            break;
			        case 3:
			        	 system("CLS");
			        	editOrder();
			        	break;
			        case 4:
			            system("CLS");
			            food(); // Call the food function to add another item
			            break;
			        case 5:
			            system("CLS");
			            payment();
			            remove("cart.txt");
			            system("CLS");
			            mainpage();
			            break;
		        }
		    } while (choice != 5); // Continue the loop until the user chooses to proceed with payment
		}
		
		void searchProduct()
		{
			string keyw;
		    cout << "\t\t\tEnter the keyword to search [0 to return back]: ";
		    getline(cin, keyw);
		
		    if (keyw == "0")
		    {
		        system("cls");
		       
		        return;
		    }
		
		    ifstream menu("menu.txt");
		    if (menu)
		    {
		        // Convert the keyword to lowercase for case-insensitive search
		        transform(keyw.begin(), keyw.end(), keyw.begin(), ::tolower);
		
		        string line;
		        int lineNum = 0; // Start from line 1
		
		        bool match = false; // Track if any matches are found
		
		
		        int left = 1;
		        int right = 0;
		        menu.seekg(0, ios::end);
		        right = menu.tellg();
		        menu.seekg(0, ios::beg);
		
		        while (left <= right)
		        {
		            int mid = left + (right - left) / 2;
		
		            getline(menu, line);
		
		            string lowercaseLine = line;
		            transform(lowercaseLine.begin(), lowercaseLine.end(), lowercaseLine.begin(), ::tolower);
		
		            if (lowercaseLine.find(keyw) != string::npos)
		            {
		                match = true;
		                cout << "No " << lineNum / 2 + 1 << ": " << line << endl;
		
		                if (getline(menu, line))
		                {
		                    lineNum++;
		                    stringstream ss(line);
		                    double price;
		                    if (ss >> price)
		                    {
		                        cout << "Price: " << price << endl;
		                    }
		                    else
		                    {
		                        cout << "Price information not found." << endl;
		                    }
		                }
		                else
		                {
		                    cout << "Price information not found." << endl;
		                }
		            }
		
		            if (lowercaseLine >= keyw)
		            {
		                right = mid - 1;
		            }
		            else
		            {
		                left = mid + 1;
		            }
		
		            lineNum += 1; 
		        }
		
		        // After binary search, continue searching forward to display all matches
		        menu.clear(); 
		    
		
		        while (getline(menu, line))
		        {
		            string lowercaseLine = line;
		            transform(lowercaseLine.begin(), lowercaseLine.end(), lowercaseLine.begin(), ::tolower);
		
		            if (lowercaseLine.find(keyw) != string::npos)
		            {
		                match = true;
		                cout << "No " << lineNum / 2+1 << ": " << line << endl;
		
		                // Check if there's a next line
		                if (getline(menu, line))
		                {
		                    lineNum++;
		                    stringstream ss(line);
		                    double price;
		                    if (ss >> price)
		                    {
		                        cout << "Price: " << price << endl;
		                    }
		                    else
		                    {
		                        cout << "Price information not found." << endl;
		                    }
		                }
		                else
		                {
		                    cout << "Price information not found." << endl;
		                }
		            }
		
		            lineNum++;
		        }
		
		        if (!match)
		        {
		            cout << "No matching products found." << endl;
		        }
		    }
		    else
		    {
		        cout << "Error opening menu file." << endl;
		    }
		
		    menu.close();
		    cout << "\nPress any key to continue...";
		    getche();
		}


// Merge function for merging two sorted subarrays
void merge(main_menu arr[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    // Create temporary arrays
    main_menu L[n1], R[n2];

    // Copy data to temporary arrays L[] and R[]
    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    // Merge the temporary arrays back into arr[l..r]
    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i].price <= R[j].price) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of L[], if there are any
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copy the remaining elements of R[], if there are any
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// Merge sort function yf done
void mergeSort(main_menu arr[], int l, int r) {
    if (l < r) {
        // Find the middle point
        int m = l + (r - l) / 2;

        // Sort first and second halves
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        // Merge the sorted halves
        merge(arr, l, m, r);
    }
}

// Modified sortPrice function using merge sort
void sortPrice() {
    main_menu x[100];
    int i = 0;

    // Open the file for reading
    ifstream menuFile("menu.txt");
    if (menuFile.is_open()) {
        // Read data into array x[]
        while (!menuFile.eof()) {
            menuFile.ignore();
            getline(menuFile, x[i].name);
            menuFile >> x[i].price;
            i++;
        }
        menuFile.close();

        // Perform merge sort on the array
        mergeSort(x, 0, i - 1);

        // Write sorted data back to the file
        ofstream me("menu.txt");
        for (int j = 0; j < i; j++) {
            me << "\n" << x[j].name;
            me << endl << x[j].price;
        }
        me.close();
    } else {
        cout << "File does not exist." << std::endl;
    }


    cout << "The price for the menu already sorted low to high!" << endl;
     getche();
    system("cls");
    food();
}

void sortAlphabet() {//selection sort
    int i = 0;
    main_menu x[100];

    ifstream menuFile("menu.txt"); // Open the file for reading

    if (menuFile.is_open()) {
        while (!menuFile.eof()) {
            menuFile.ignore();
            getline(menuFile, x[i].name);
            menuFile >> x[i].price;
            i++;
        }
        menuFile.close();

        // Use selection sort for alphabetical sorting
        for (int a = 0; a < i - 1; a++) {
            int minIndex = a;
            for (int j = a + 1; j < i; j++) {
                if (x[j].name < x[minIndex].name) {
                    minIndex = j;
                }
            }
            // Swap menu items
            if (minIndex != a) {
                main_menu temp = x[a];
                x[a] = x[minIndex];
                x[minIndex] = temp;
            }
        }

        ofstream me("menu.txt");
        for (int j = 0; j < i; j++) {
            me << "\n" << x[j].name;
            me << endl << x[j].price;
        }
        me.close();

        cout << "The alphabet for the menu has been sorted!" << endl; // Moved inside the successful sorting block
    } else {
        cout << "File does not exist." << endl;
    }
    getche();
    system("cls");
    food();
}

void sortmenu() {
    int sortchoice;

    cout << endl;
    cout << "\t\t\t 1. Sort by Alphabet" << endl;
    cout << "\t\t\t 2. Sort by Price" << endl;
    cout << "Enter your choice [0 return back]: ";
    cin >> sortchoice;

    if (sortchoice == 0) {
        system("cls");
        food();
        return; // Exit function if the user chooses to return
    }

    switch (sortchoice) {
        case 1:
            sortAlphabet();
            break;

        case 2:
            sortPrice();
            break;

        default:
            cout << "Invalid choice!" << endl;
            break;
    }
}
	
	void food() {
    int i = 0;
    int c = 0;
    ifstream menu("menu.txt");

    if (!menu) {
        cout << "\nFile does not exist." << endl;
    } else {
        cout << "No.\t\t\tFast-Food Menu\t\t\t\tPrice(RM)" << endl;

        while (!menu.eof()) {
            menu.ignore();
            getline(menu, p[i].foodName);
            menu >> p[i].foodPrice;

            if (p[i].foodName.empty()) // Skip empty lines
                continue;
            
            size_t found = p[i].foodName.find("appy");
    if (found != string::npos) {
        p[i].foodName.replace(found, 4, "Happy");
    }
    
            cout << i + 1 << "\t" << setw(30) << p[i].foodName << "\t\t" << setw(20) << fixed << setprecision(2) << p[i].foodPrice << endl;
            i++;
        }

        menu.close(); // Close the menu.txt file

        cout << "\n\t\t\t1.Searching Food" << endl;
        cout << "\n\t\t\t2.Sorting Food" << endl;
        cout << "\n\t\t\t3.Purchase Food" << endl;
        cout << "\n\t[0 return back to customer main page or 88 go to confirm order]";
        cout << "\n\t\t Enter your choice : ";
        cin >> c;
        fflush(stdin);
        cin.clear();

        if (c == 0) {
            system("cls");
            mainpage();
        } else if (c == 88) {
            confirmOrder();
        }

        while (c < 1 || c > 3) {
            cout << "\n\t\t\tChoice unavailable. Please Reenter your choice: ";
            cin >> c;
            fflush(stdin);
            cin.clear();
        }

        switch (c) {
            case 1:
                searchProduct();
                system("cls");
                food();
                break;
            case 2:
                sortmenu();
                break;
            case 3:

                cout << "\n\t\t\tEnter the Fast-Food No [0 return back]: ";
                cin >> item;
                fflush(stdin);
                cin.clear();

                if (item == 0) {
                    system("cls");
                    food();
                }

                while (item < 1 || item > i) {
                    cout << "\n\t\t\t\tItem Not Found!";
                    cout << "\n\t\t\t\tReenter the Item No: ";
                    cin >> item;
                    fflush(stdin);
                    cin.clear();
                }

                cout << "\t\t\tEnter the Quantity: ";
                cin >> qty;
                fflush(stdin);
                cin.clear();

                Food foodToAdd;
                foodToAdd.foodName = p[item - 1].foodName;
                foodToAdd.foodPrice = p[item - 1].foodPrice;
                foodToAdd.qty = qty;
                foodToAdd.subtotal = p[item - 1].foodPrice * qty;

                addToCart(foodToAdd);
                ofstream cart("cart.txt", ios::app);
                cart << "\n" <<foodToAdd.foodName << "\n" << fixed << setprecision(2) << foodToAdd.foodPrice << "\n" << qty << "\n" <<foodToAdd.subtotal;
                cart.close();
                break;
        }
        cout << "\n \t\t\t Added successfully....;";
        cout << "\n \t\t\t Press any key to continue...";
        getche();
        confirmOrder(); // Call confirmOrder to continue the order confirmation process
    }
}
};

// Class for user management
class User {
private:
    string username;
    string password;

public:
    User(string uname, string pwd) : username(uname), password(pwd) {}

    string getUsername() const {
        return username;
    }

    string getPassword() const {
        return password;
    }
};

// Admin inherits from User
class Admin : public User {
private:
    string adminID;

public:
    Admin(string uname, string pwd, string id) : User(uname, pwd), adminID(id) {}

    string getAdminID() const {
        return adminID;
    }
};

// Customer inherits from User
class Customer : public User {
private:
    string customerID;

public:
    Customer(string uname, string pwd, string id) : User(uname, pwd), customerID(id) {}

    string getCustomerID() const {
        return customerID;
    }
};

// Order inherits from Menu
class Order : public Menu {
private:
    int quantity;

public:
    Order(string name, float price, int qty) : Menu(name, price), quantity(qty) {}

    int getQuantity() const {
        return quantity;
    }

    float getTotalPrice() const {
        return getPrice() * quantity;
    }
};

// Friend function for comparing admin data
bool compareAdminData(const Admin& admin, const string& key) 
{
    return admin.getUsername() == key; // Compare based on username for simplicity
}

// Friend function
void friendFunction1(const User& user) 
{
    cout << "Friend Function 1 accessing User: " << user.getUsername() << endl;
}

// Friend function
void friendFunction2(const Menu& menu) 
{
    cout << "Friend Function 2 accessing Menu: " << menu.getName() << endl;
}

void dl()
{
	for(int i=1;i<100;i++)
	cout<<"=";
	cout<<endl;
}

void sp()
{
	cout<<endl;
}

void viewmenu()
{	
    dl();
	cout<<"                                           Fast-Food Menu"<<endl;
	dl();
	
	ifstream menu("menu.txt");
		
	cout<<"Id        \t\t\tName \t\t       \t\tPrice(RM)"<<endl;
	cout<<endl;
	int i=0;
	
	if(menu)
	{
		while(!menu.eof())
		{	
			menu.ignore();
			getline(menu,x[i].name)>>x[i].price;
						
			cout<<setw(2)<<i+1;
			cout<<setw(35)<<x[i].name;
			cout<<setw(32)<<fixed<<setprecision(2)<<x[i].price<<endl;
			i++;
		}
	}
	menu.close();
	sp();
}

void viewhistory()
{	int i=0;
			float grand_total=0;
			string userN;
			float customerP,customerC;
			 bool found = false;
			 string line;
	
		    ifstream purchase("purchase.txt");
		    ifstream order("order_details.txt");
		    ifstream details("purchasedetail.txt");

 while (getline(details, userN) >> customerP >> customerC) {
        // Process each line of purchasedetail.txt
    }
			details.close();

             cout << setw(50) << "MMU Fast-Food" << endl;
    cout << setw(50) << "Jalan Ayer Keroh Lama, 75450 Bukit Beruang" << endl;
    cout << setw(50) << "Melaka, Malaysia" << endl;
    cout << setw(50) << "TEL : 019-7753357" << endl;
    cout << "\t---------------------------------------------------------------------------------------------------------" << endl;
    cout << "\t-\t\t\t\t\t\tReceipt\t\t\t\t\t\t\t-" << endl;
    cout << "\t---------------------------------------------------------------------------------------------------------" << endl;
    cout << "\tUsername : " << userN << endl;
    cout << "\tItem ID\t\tItem Name\t\t\tItem Price\tQuantity\tTotal Price" << endl;
          
	   while (getline(order, line)) {
           istringstream iss(line);
            iss >> p[i].username>>p[i].foodName>>p[i].foodPrice >> p[i].qty >> p[i].subtotal;
        
             	if(p[i].username == loggedInUsername)
             	{
             	found = true;
             	cout << "\t" << i + 1;
        		cout << "\t\t" << left << setw(30) << p[i].foodName;
        		cout << "RM " << right << setw(5) << fixed << setprecision(2) << p[i].foodPrice << "\t\t" << p[i].qty << "\t\t" << p[i].subtotal << endl;
       			grand_total += p[i].subtotal;
       			i++;
				 }
			  }
	
			  order.close();
			    if (!found) {
        cout << "No orders found for username: " << loggedInUsername << endl;
    }
            
           
    cout << "\n\t---------------------------------------------------------------------------------------------------------" << endl;
    cout << "\n\t\t\t\t\tGrand Total = RM " << grand_total << endl;
    cout << "\n\t\t\t\t\tCustomer Pay = RM " << customerP << endl;
    cout << "\n\t\t\t\t\tCustomer Changes = RM " << customerC << endl;
    cout << "\n\t---------------------------------------------------------------------------------------------------------" << endl;
    cout << ("\n\t\t\t\t\tDear Customer, Have A Great Day !");
    cout << ("\n\t\t\t\t\t    Thank You for Choosing Us !");

    cout << "\n\nPress any key to continue" << endl;
    getche();
}

void LoginHome(){
	int c;
	cout<<"\t ________________________________________________________________\n";
	cout<<"\t|                                                                |\n";
	cout<<"\t|                    Welcome To MMU Fast-Food                    |\n";
	cout<<"\t|                         Customer Page                          |\n";
	cout<<"\t|________________________________________________________________|\n";
	cout<<"\t| 1. Login                                                       |\n";
	cout<<"\t| 2. Register                                                    |\n";
	cout<<"\t| 3. Forgot password                                             |\n";
	cout<<"\t| 4. Back to previous                                            |\n";
	cout<<"\t|________________________________________________________________|\n";
	
	cout<<"\n\t Enter your choice : ";
	cin>>c;
	fflush(stdin);
	cin.clear();

		
	while(c < 1 || c >4){
		cout<<"\n\tChoice unavailable. Please Reenter your choice : ";
		cin>>c;
		fflush(stdin);
	    cin.clear();
	}
	
	switch(c)
	{
		case 1:
			system("cls");
			login();
			break;
			
		case 2:
			system("cls");
			registration();
			break;
			
		case 3:
			system("cls");
			forgot();
			break;
		case 4:
			system("cls");
			admin_customer();
			break;
			
		
		
			
	}
}

void mainpage(){
	Menu m;
	
	int c;
	cout<<"\t ________________________________________________________________\n";
	cout<<"\t|                                                                |\n";
	cout<<"\t|                    Welcome to Customer Main Page               |\n";
	cout<<"\t|________________________________________________________________|\n";
	cout<<"\t| 1. Customer profile                                            |"<<endl;
	cout<<"\t| 2. Menu                                                        |"<<endl;
	cout<<"\t| 3. Purchase History                                            |"<<endl;
	cout<<"\t| 4. Logout                                                      |"<<endl;
	cout<<"\t| 5. Exit                                                        |"<<endl;
	cout<<"\t|________________________________________________________________|\n";
	
	
	cout<<endl;
	
	cout<<"\n\t Enter your choice : ";
	cin>>c;
	fflush(stdin);
	cin.clear();
	
	while(c<1||c>5){
		cout<<"\n\t Choice Unavailable. Please reenter your choice : ";
		cin>>c;
		fflush(stdin);
		cin.clear();
	}
	
	switch(c)
	{
		case 1:
			system("cls");
			userprofile();
			break;
		case 2:
			system("cls");
			m.food();
			break;
		case 3:
			system("cls");
			m.viewpurchase();
			system("cls");
			mainpage();
			break;
			
		case 4:
			system("cls");
			LoginHome();
			loggedInUsername ="";
			break;
		
		case 5:
			cout<<"\t\t\t Thank you !!! \n\n";
			exit(1);
			break;
	}
}

void login() {
    int attempts = 0;
    char option;
    string user_name, pass;
    string fileUsername, filePassword;

    cout << "\t _____________________________________________________________\n";
    cout << "\t|                                                             |\n";
    cout << "\t|                       Login page                            |\n";
    cout << "\t|_____________________________________________________________|\n\n";

    while (true) {
    	cout << "\n \t Enter [88] to back to main login page: ";
        cout << "\n \t Enter username: ";
        getline(cin, user_name);

        if (user_name == "88") {
            system("cls");
            LoginHome();
            return;
        } else {
            cout << "\t Enter password: ";
            getline(cin, pass);

            ifstream file("userprofile.txt");

            if (file.is_open()) {
                bool loginSuccessful = false;

                while (getline(file, fileUsername)) {
                    getline(file, filePassword);

                    if (user_name == fileUsername && pass == filePassword) {
                        loginSuccessful = true;
                        loggedInUsername = fileUsername;
                        break;
                    }
                }

                file.close();

                if (loginSuccessful) {
                    system("cls"); // or system("clear");
                    cout << "\t|                      Login Successfull                        |\n";
                    mainpage();
                    return;
                } else {
                    cout << "\n \t| Invalid username or password. |\n" << endl;
                    attempts++;

                    if (attempts >= 3) {
                        system("cls"); // or system("clear");
                        cout << "\n \t You are login too many time please try again later..." << endl;
                        LoginHome();
                        return;
                    }
                }
            } else {
                cout << "\t Unable to open file." << endl;
                return;
            }
        }
    }
}

void registration() {
    system("cls");

    string ruser_Id, r_password, confirm_password;
    cout << "\t ________________________________________________________________\n";
    cout << "\t|                                                                |\n";
    cout << "\t|                          Register page                         |\n";
    cout << "\t|________________________________________________________________|\n\n";

    while (true) {
        cout << "\n \t Enter [88] to go back to the main login page: ";
        cout << "\n \t Enter username: ";
        cin.ignore();
        getline(cin, ruser_Id);

        if (ruser_Id == "88") {
            system("cls");
            LoginHome();
            return;
        }

        ifstream f2("userprofile.txt");
        string line;
        bool UsernameExists = false; // Flag to check if username exists

        while (getline(f2, line)) {
            if (line == ruser_Id) {
                UsernameExists = true;
                cout << "\n \t | Username already exists. Please choose a different username. |\n";
                break;
            }
        }
        f2.close();

        if (!UsernameExists)
            break;
    }

    cout << "\n \t Enter password: ";
    getline(cin, r_password);

   
    while (true) {
        cout << "\n \t Confirm password: ";
        getline(cin, confirm_password);

        if (confirm_password == r_password) {
            break;
        } else {
            cout << "\n \t | Passwords do not match. Please try again. |\n";
        }
    }

    ofstream f1("userprofile.txt", ios::app);
    if (f1.is_open()) {
        f1 << ruser_Id << endl;
        f1 << r_password << endl;
        f1.close();
        system("cls");
        cout << "\n\t Registration is successful!\n";
        login();
    } else {
        cout << "\t Error opening file." << endl;
    }
}

void forgot() {
    cout << "\t ________________________________________________________________\n\n";
    cout << "\t|                                                                |\n";
    cout << "\t|                        Forgot Password                         |\n";
    cout << "\t|________________________________________________________________|\n\n";

    string User_name;
    bool profile_Found = false;
    string line; // Declare line variable here

    cout << "\n \t Enter [88] to go back to main login page: ";
    cout << "\n \t Enter the username you remember: ";
    getline(cin, User_name);

    // Check if the user wants to go back to main()
    if (User_name == "88") {
        system("cls");
        LoginHome();
        return; // Exit the forgot() function
    }

    ifstream inputFile("userprofile.txt"); // Declare inputFile here

    if (!inputFile) {
        cerr << "\t Error opening the file." << endl;
        return;
    }

    inputFile.clear();
    inputFile.seekg(0, ios::beg);

    string password;

    // Find the user's profile in the file
    while (getline(inputFile, line)) {
        string name = line;
        getline(inputFile, line);
        password = line;

        if (name == User_name) {
            profile_Found = true;
            break;
        }
    }

    inputFile.close();

    if (!profile_Found) {
        system("cls");
        cout << "\n \t Sorry! Your account is not found! \n";
        // Exit the forgot() function if the profile is not found
        forgot();
        return;
    }

    // If the profile is found, reset the password
    string new_Pass;
    string confirm_Pass;

    do {
        cout << "\n \t Enter your new password: ";
        getline(cin, new_Pass);

        cout << "\n \t Confirm your new password: ";
        getline(cin, confirm_Pass);

        if (new_Pass != confirm_Pass) {
            cout << "\n \t Passwords do not match. Please try again.\n";
        }
    } while (new_Pass != confirm_Pass);

    // Update the user's profile in the file with the new password
    ifstream inputFile2("userprofile.txt"); // Declare a new variable inputFile2

    ofstream outputFile("temp.txt");

    if (inputFile2 && outputFile) {
        while (getline(inputFile2, line)) {
            string name = line;
            getline(inputFile2, line);

            if (name == User_name) {
                outputFile << name << endl;
                outputFile << new_Pass << endl;
            } else {
                outputFile << name << endl;
                outputFile << line << endl;
            }
        }

        inputFile2.close();
        outputFile.close();

        // Rename temp.txt to userprofile.txt
        if (remove("userprofile.txt") != 0 || rename("temp.txt", "userprofile.txt") != 0) {
            cerr << "\n \t Error updating password." << endl;
            return;
        }

        system("cls");
        cout << "\n \t Password reset successful! \n";
        LoginHome(); // Navigate back to the login page
    } else {
        cerr << "\n \t Error opening the file for writing." << endl;
    }
}

void userprofile() {
    char num;

    ifstream inputFile("userprofile.txt");
    if (!inputFile) {
        cerr << "\t Error opening the file." << endl;
        return;
    }

    cout << "\t ________________________________________________________________\n";
    cout << "\t|                                                                |\n";
    cout << "\t|                        Customer Profile                        |\n";
    cout << "\t|________________________________________________________________|\n\n";

    // Use loggedInUsername here
    string u_name = loggedInUsername;

    // No need to ask for the username and password again
    cout << "\n \t Current Name: " << u_name << endl;
    cout << "\n \t Current Password: " << "********" << endl; // Mask the password for security

    inputFile.close();

    cout << "\n\n\t Enter 'y' to go back to main: ";
    cin >> num;

    while (num != 'y' && num != 'Y') {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\n\n\t Invalid input! Please try again.\n";
        cout << "\n\n\t Enter 'y' to go back to main: ";
        cin >> num;
    }
    system("cls");
    mainpage();
}

void loading()
{

	char a= 177,b=219;
	cout<<"\n\n\tLoading...";
    cout<<"\n\n\t";
    for(int i=0;i<=45;i++)
        	cout<<" " ;
    Sleep(70);
    cout<<"\r";
    cout<<"\t";
    for(int i=0;i<=40;i++)
    {
        cout<<b;
        Sleep(70);
    }
}

void display(){
cout<<"\n\t ===========================================================================================";
Sleep(450);
cout<<"\n\t -------------------------------------------------------------------------------------------";
cout<<"\n\t ===========================================================================================";
Sleep(450);
cout<<"\n\t ##########################################################################################";
Sleep(450);
cout<<"\n\t\t* ";
Sleep(250);
cout<<"   Fast-Food  ";
Sleep(250);
cout<<"Ordering ";
Sleep(250);
cout<<"System ";
Sleep(250);
cout<<"SYSTEM ";
Sleep(100);
cout<<"  *";
Sleep(100);
cout<<"\n\t\t------------------------------------------";
Sleep(100);
cout<<"\n\t\t   ------------------------------------";
Sleep(100);
cout<<"\n\t\t     ------------------------------";
Sleep(100);
cout<<"\n\t\t        -------------------------";
Sleep(600);
}

void addadmin()//Linked list
{
    Node* head = NULL; 
    Node* tail = NULL; 

    string admin_id, admin_hp, admin_name, admin_pw, confirm_pw;

    ofstream adminFile;
    adminFile.open("admin.txt", ios::app);

    bool exists;
    do {
        exists = false; 
        cout << "\nEnter new Admin ID [0 to return back ]: ";
        cin >> admin_id;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 

        if (admin_id == "0") {
            system("cls");
            return; 
        }

        while (admin_id.length() != 10) {
            cout << "Admin ID must be 10 digits: ";
            cin >> admin_id;
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        }

        
        ifstream inputFile("admin.txt");
        string line;
        while (getline(inputFile, line)) {
            if (!line.empty()) {
                string id = line;
                getline(inputFile, admin_name);
                getline(inputFile, admin_hp); 
                getline(inputFile, admin_pw); 
                if (id == admin_id) {
                    exists = true;
                    cout << "Admin ID already exists. Please try again." << endl;
                    break;
                }
            }
        }
        inputFile.close();

    } while (exists);

    do {
        cout << "Enter New Admin Contact number: ";
        getline(cin, admin_hp); 

  
        exists = false;

     
        ifstream inputFile("admin.txt");
        string line;
        while (getline(inputFile, line)) {
            if (!line.empty()) {
                string id = line;
                getline(inputFile, admin_name); 
                getline(inputFile, line); 
                string hp = line;
                getline(inputFile, admin_pw); 
                if (hp == admin_hp) {
                    exists = true;
                    cout << "Contact number already exists. Please try again." << endl;
                    break;
                }
            }
        }
        inputFile.close();

    } while (exists);

    cout << "Enter New Admin Name: ";
    getline(cin, admin_name);

    
    do {
        cout << "Enter New Admin password: ";
        cin >> admin_pw;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        cout << "Confirm New Admin password: ";
        cin >> confirm_pw;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        if (admin_pw != confirm_pw) {
            cout << "Passwords do not match. Please try again." << endl;
        }
    } while (admin_pw != confirm_pw);

  
    Node* newNode = new Node;
    newNode->admin_id = admin_id;
    newNode->admin_name = admin_name;
    newNode->admin_hp = admin_hp;
    newNode->admin_pw = admin_pw;
    newNode->next = NULL;

    if (head == NULL) {
        head = newNode;
        tail = newNode;
    } else {
        tail->next = newNode;
        tail = newNode;
    }

   
    adminFile << endl << admin_id;
    adminFile << endl << admin_name;
    adminFile << endl << admin_hp;
    adminFile << endl << admin_pw;

    adminFile.close();

    cout << "\n\nThe new admin has been added!" << endl;
    cout << "Press any key to continue...";
    getche();
    system("cls");
}

void showAdminList() //Display admin list
{
    ifstream adminFile("admin.txt");

    string admin_id, admin_name, admin_hp, admin_pw;
    int adminCount = 0;

    cout << "Admin List" << endl;

   
    adminFile.ignore(numeric_limits<streamsize>::max(), '\n');

    while (getline(adminFile, admin_id)) {
        getline(adminFile, admin_name);
        getline(adminFile, admin_hp);
        getline(adminFile, admin_pw);

        ++adminCount;

        cout << "Admin #" << adminCount << endl;
        cout << "ID: " << admin_id << endl;
        cout << "Name: " << admin_name << endl ;
        cout<<"Contact Number: "<<admin_hp<< endl<< endl;
      
    }

    if (adminCount == 0) {
        cout << "No admins found." << endl;
    }

    adminFile.close();
}

void editadmin() //Linked list traversal & linear search
{
    string edit_id, edit_password, new_value;
    int choice;
    bool found = false;

    ifstream admin("admin.txt");
    ofstream temp("temp.txt");

    cout << "\nEnter the Admin's ID you want to edit [0 to return back ]: ";
    cin >> edit_id;

    if (edit_id == "0")
    {
        system("cls");
        return;
    }

    cin.ignore();

    Node *head = NULL;
    Node *tail = NULL;

    while (admin.peek() == '\n')
    {
        admin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

   
    while (!admin.eof())
    {
        Node *newNode = new Node;

        getline(admin, newNode->admin_id);
        getline(admin, newNode->admin_name);
        getline(admin, newNode->admin_hp);
        getline(admin, newNode->admin_pw);

        newNode->next = NULL;

 
        if (head == NULL)
        {
            head = newNode;
            tail = newNode;
        }
        else
        {
            tail->next = newNode;
            tail = newNode;
        }
    }

    
    Node *current = head;
    while (current != NULL)
    {
        if (edit_id == current->admin_id)
        {
            found = true;
            cout << "Admin found. What do you want to edit?" << endl;
            cout << "1. Edit Name" << endl;
            cout << "2. Edit Contact Number" << endl;
            cout << "Enter your choice: ";
            cin >> choice;
            cin.ignore();

            switch (choice)
            {
            case 1:
                cout << "Enter the new name for Admin with ID " << current->admin_id << ": ";
                getline(cin, new_value);
                current->admin_name = new_value;
                break;
            case 2:
                
                do
                {
                    cout << "Enter the new contact number for Admin with ID " << current->admin_id << ": ";
                    getline(cin, new_value);

                    Node *check = head;
                    bool exists = false;
                    while (check != NULL)
                    {
                        if (check->admin_hp == new_value && check->admin_id != current->admin_id)
                        {
                            exists = true;
                            cout << "Contact number already exists. Please enter a different one." << endl;
                            break;
                        }
                        check = check->next;
                    }
                    if (!exists)
                    {
                        current->admin_hp = new_value;
                        break;
                    }
                } while (true);
                break;
            default:
                cout << "Invalid choice." << endl;
                break;
            }

            edit_password = current->admin_pw;
        }

       
        temp << endl
             << current->admin_id << endl;
        temp << current->admin_name << endl;
        temp << current->admin_hp << endl;
        temp << current->admin_pw;

        current = current->next;
    }

  
    current = head;
    while (current != NULL)
    {
        Node *nextNode = current->next;
        delete current;
        current = nextNode;
    }

    admin.close();
    temp.close();
    remove("admin.txt");
    rename("temp.txt", "admin.txt");

    if (found)
    {
        cout << "\n\nAdmin details updated successfully!" << endl;
    }
    else
    {
        cout << "Admin not found!" << endl;
    }

    cout << "Press any key to continue...";
    getche();
    system("cls");
}

void deleteadmin()
{
    string dlt_id;
    
    cout << "Enter the Admin's ID you want to delete [0 to return back]: ";
    cin >> dlt_id;

    if (dlt_id == "0")
    {
        system("cls");
      
        return; 
    }

    ifstream adminFile("admin.txt");
    ofstream tempFile("temp.txt");

    bool adminDeleted = false;

   
    if (!adminFile.is_open() || !tempFile.is_open()) {
        cout << "Error: Unable to open files." << endl;
        return;
    }

	while (!adminFile.eof())
	{
	    string line;
	    getline(adminFile, line);
	    if (line.empty()) continue; 
	
	    string admin_id = line;
	    string admin_name, admin_hp, admin_pw;
	
	    getline(adminFile, admin_name);
	    getline(adminFile, admin_hp);
	    getline(adminFile, admin_pw);
	
	    if (dlt_id != admin_id)
	    {
	       
	        tempFile<< endl << admin_id;
		    tempFile << endl << admin_name;
		    tempFile << endl << admin_hp;
		    tempFile << endl << admin_pw;
	      
	      
	    }
	    else
	    {
	        adminDeleted = true; 
	    }
	}

    adminFile.close();
    tempFile.close();


    remove("admin.txt");
    rename("temp.txt", "admin.txt");

    if (adminDeleted) { 
        cout << "\n\nAdmin Deleted Successfully." << endl;
    } else {
        cout << "\n\nAdmin Not Found." << endl;
    }

    cout << "Press any key to continue..." << endl;
    getche();
}

void sort_admin_by_ID() // Bubble sort
{
    int i = 0;
    Node x[100]; 

    ifstream adminFile("admin.txt"); 
    if (adminFile.is_open()) {
     
        string temp;
        getline(adminFile, temp);

 
        while (!adminFile.eof() && i < 100) {
            getline(adminFile, x[i].admin_id);
            getline(adminFile, x[i].admin_name);
            getline(adminFile, x[i].admin_hp);
            getline(adminFile, x[i].admin_pw);
            i++;
        }
        adminFile.close();

      
		  for (int a = 0; a < i; a++) {
		    for (int j = 0; j < i - a - 1; j++) {
		        if (x[j].admin_id > x[j + 1].admin_id) { 
		      
		            Node temp = x[j];
		            x[j] = x[j + 1];
		            x[j + 1] = temp;
		        }
		    }
		}

 
        cout << "No.\tID\t\tName\t\t\t\tContact Number" << endl;
        
        for (int j = 0; j < i; j++) {
            cout << j+1  << "\t" << setw(12) << left << x[j].admin_id << "\t" << setw(30) << left << x[j].admin_name << "\t" << x[j].admin_hp << endl;
        }
    } else {
        cout << "File does not exist." << endl;
    }

    system("pause");
    system("cls");
}

void sort_admin_by_name() // Bubble sort
{
    int i = 0;
    Node x[100]; 

    ifstream adminFile("admin.txt"); 
    if (adminFile.is_open()) {

        adminFile.ignore(numeric_limits<streamsize>::max(), '\n');

       
        while (!adminFile.eof() && i < 100) {
            getline(adminFile, x[i].admin_id);
            getline(adminFile, x[i].admin_name);
            getline(adminFile, x[i].admin_hp);
            getline(adminFile, x[i].admin_pw);
            i++;
        }
        adminFile.close();


        for (int a = 0; a < i - 1; a++) {
            for (int j = 0; j < i - a - 1; j++) {
                if (x[j].admin_name > x[j + 1].admin_name) {
           
                    Node temp = x[j];
                    x[j] = x[j + 1];
                    x[j + 1] = temp;
                }
            }
        }

      
        cout << "No.\tID\t\tName\t\t\t\tContact Number" << endl;

        for (int j = 0; j < i; j++) {
            cout << j+1 << "\t" << setw(12) << left << x[j].admin_id << "\t" << setw(30) << left << x[j].admin_name << "\t" << x[j].admin_hp << endl;
        }
    } else {
        cout << "File does not exist." << endl;
    }

    system("pause");
    system("cls");
}

void search_admin()//Linear search
{
    string search;
    cout << "Enter the keyword that you want to search [0 to return back]";
    getline(cin, search);

    if (search == "0")
    {
        system("cls");
        return;
    }

    ifstream adminFile("admin.txt");

    if (adminFile)
    {
        string line;
        int lineNum = 0; 
        int matchCount = 0; 
        
        while (getline(adminFile, line))
        {
            string lowercaseLine = line;
            transform(lowercaseLine.begin(), lowercaseLine.end(), lowercaseLine.begin(), ::tolower);

            if (lowercaseLine.find(search) != string::npos)
            {
                matchCount++; 
                cout << "\nNo " << (lineNum / 4) + 1 << ": " << line << endl; 
                if (getline(adminFile, line))
                {
                    lineNum++;
                    stringstream ss(line);
                    string admin_name;
                    if (ss >> admin_name)
                    {
                        cout << "Admin Name: " << admin_name << endl;
                    }
                    else
                    {
                        cout << "Admin information not found." << endl;
                    }
                }
                else
                {
                    cout << "Admin information not found." << endl;
                }
            }

            lineNum++; 
        }

        if (matchCount > 0)
        {
            cout << matchCount << " matching admins found." << endl;
        }
        else
        {
            cout << "No matching admins found." << endl;
        }
    }
    else
    {
        cout << "Error opening menu file." << endl;
    }

    adminFile.close();
    cout << "\nPress any key to continue...";
    getche();
}
	
void forgotPassword()
{
    string adminID;
    cout << "Enter your admin ID: ";
    cin >> adminID;

    ifstream adminFile("admin.txt");

    if (adminFile)
    {
        string line;
        bool found = false;

        while (getline(adminFile, line))
        {
            if (line == adminID)
            {
                found = true;
                string password;

              
                for (int i = 0; i < 3; ++i)
                {
                    if (!getline(adminFile, line))
                    {
                        cout << "Password not found." << endl;
                        return;
                    }
                }

                cout << "Your password is: " << line << endl;
				cout << "\nPress any key to continue...";
                getche();
                system("cls");
				adminLoginPage();
                break;
               
            }
        }

        if (!found)
        {
            cout << "Admin ID not found." << endl;
           	cout << "\nPress any key to continue...";
            getche();
            system("cls");
            adminLoginPage();
        }
    }
    else
    {
        cout << "Error opening admin file." << endl;
        	cout << "\nPress any key to continue...";
            getche();
            system("cls");
        adminLoginPage();
    }

    adminFile.close();
}
	
void adminLoginPage()
{
	int choice;
	cout<<"\t ________________________________________________________________\n";
	cout<<"\t|                                                                |\n";
	cout<<"\t|                Welcome to admin login page                     |\n";
	cout<<"\t|________________________________________________________________|\n";
	cout<<"\t| 1. Login                                                       |"<<endl;
	cout<<"\t| 2. Forgot password                                             |"<<endl;
	cout<<"\t| 3. Back to previous                                            |"<<endl;
	cout<<"\t|________________________________________________________________|\n";
	
	
	cout<<"\n\t Enter your choice : ";
	
	cin>>choice;
	fflush(stdin);
	cin.clear();
	
	
	while(choice < 1 || choice >3){
		cout<<"\n\tChoice unavailable. Please Re-enter your choice : ";
		cin>>choice;
		fflush(stdin);
		cin.clear();
	}
	
	switch(choice)
	{
		case 1:
			system("cls");
			adminlogin();
			break;
			
		case 2:
			system("cls");
			forgotPassword();
			break;
		case 3:
			system("cls");
			admin_customer();	
			
			
	}
}		

void adminlogin()
{
    char option;
    string id, password;
    string fileID, fileName, filePhoneNumber, filePassword;
    int attempts = 0;

    cout << "\t _____________________________________________________________\n";
    cout << "\t|                                                             |\n";
    cout << "\t|                      Admin Login page                       |\n";
    cout << "\t|_____________________________________________________________|\n\n";
    
    while (true) {
        cout << "\n \t Enter [0] to back to main login page";
        cout << "\n \t Enter ID: ";
        getline(cin, id);

        if (id == "0") {
            system("cls");
            adminLoginPage();
            return;
        } else {
            fflush(stdin);

            cout << "\t Enter password: ";
            getline(cin, password);

            if (id == "root" && password == "root") {
                system("cls");
                cout << "\n\n \t|                Login successful! Welcome, Root Admin!          | \n" << endl;
                rootAdminFunctionality(); 
                return;
            }

            ifstream file("admin.txt");
            while (file.peek() == '\n') {
                file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }

            if (file.is_open()) {
                bool loginSuccessful = false;

                while (!file.eof()) {
                    getline(file, fileID);
                    getline(file, fileName);
                    getline(file, filePhoneNumber);
                    getline(file, filePassword);

                    if (id == fileID && password == filePassword) {
                        loginSuccessful = true;
                        break;
                    }
                }

                file.close();

                if (loginSuccessful) { 
				 	loading();
                    system("cls");
                    cout << "\n\n \t|                Login successful!                        | \n" << endl;
					adminmainpage();
                    return;
                } else {
                    cout << "\n \t| Invalid ID or password. |\n" << endl;
                    attempts++;

                    if (attempts >= 3) {
                        system("cls"); 
                        cout << "\n \t You have exceeded the maximum number of login attempts. Please try again later." << endl;
                        adminLoginPage();
                        return;
                    }
                }
            } else {
                cout << "\t Unable to open file." << endl;
                return;
            }
        }
    }
}

void rootAdminFunctionality()
{
    int adminID, adminchoice, back, adc, c;
    int prochoice, adchoice;
    string adminid, adminnum, adminname;

    do
    {
        cout << "\t ________________________________________________________________\n";
        cout << "\t|                                                                |\n";
        cout << "\t|                    Welcome to Root Admin menu                  |\n";;
        cout << "\t|________________________________________________________________|\n";
        cout << "\t| 1. View Purchase History                                       |" << endl;
        cout << "\t| 2. View Menu                                                   |" << endl;
        cout << "\t| 3. View Admin                                                  |" << endl;
        cout << "\t| 4. Logout                                                      |" << endl;
        cout << "\t| 5. Exit                                                        |" << endl;
        cout << "\t|________________________________________________________________|\n";

        cout << endl;

        cout << "\n\n\t Enter your choice : ";
        cin >> c;
        fflush(stdin);
        cin.clear();
        cout << endl;

        while (c < 1 || c > 5)
        {
            cout << "\n\t Choice unavailable. Please Reenter with the correct choice : ";
            cin >> c;
            fflush(stdin);
            cin.clear();
        }

        system("cls");

        switch (c)
        {
        case 1:
            viewhistorys();
            break;
        case 2:
        order:
            viewmenus();
            cout << "1. Searching" << endl;
            cout << "2. Sorting" << endl;
            cout << "3. Add Product" << endl;
            cout << "4. Edit Product" << endl;
            cout << "5. Delete Product" << endl;
            cout << endl;
            cout << "Enter your choice [0 to return back admin main page] : ";
            cin >> prochoice;
            fflush(stdin);
            cin.clear();

            if (prochoice == 0)
            {
                system("cls");
            }

            while (prochoice < 1 || prochoice > 5)
            {
                cout << "Choice unavailable. Please Reenter your choice : ";
                cin >> prochoice;
                fflush(stdin);
                cin.clear();
            }

            switch (prochoice)
            {
            case 1:

                searchBurger();
                system("cls");

                goto order;
                break;

            case 2:

                sortmenu();
                system("cls");
                goto order;
                break;

            case 3:

                addBurger();
                system("cls");
                goto order;
                break;

            case 4:

                editBurger();
                system("cls");
                goto order;
                break;

            case 5:

                deleteBurger();
                system("cls");
                goto order;
                break;
            }
            break;

        case 3:
            do
            {
                showAdminList();
                cout << "1. Add Admin" << endl;
                cout << "2. Edit Admin Profile" << endl;
                cout << "3. Search Admin" << endl;
                cout << "4. Delete Admin" << endl;
                cout << "5. Sort Admin" << endl;
                cout << "Enter your choice [0 to return back to admin main page]: ";
                cin >> adminchoice;
                fflush(stdin);
                cin.clear();
                if (adminchoice == 0)
                {
                    system("cls");
                    break;
                }
                while (adminchoice < 0 || adminchoice > 5)
                {
                    cout << "Choice unavailable. Please Re-enter your choice : ";
                    cin >> adminchoice;
                    fflush(stdin);
                    cin.clear();
                }

                switch (adminchoice)
                {
                case 1:
                    addadmin();
                    break;
                case 2:
                    editadmin();
                    break;
                case 3:
                    search_admin();
                    break;
                case 4:
                    deleteadmin();
                    break;
                case 5:
                    cout << "\n1. Sort Admin By ID" << endl;
                    cout << "2. Sort Admin By Name" << endl;
                    cout << "Enter your choice [0 to return back]";
                    cin >> adc;
                    if (adc == 0)
                    {
                        system("cls");
                    }
                    if (adc == 1)
                    {
                        sort_admin_by_ID();
                    }
                    else if (adc == 2)
                    {
                        sort_admin_by_name();
                    }
                    break;
                }
             
                system("cls");
            } while (adminchoice != 0);
            break;

        case 4:
          adminLoginPage();
            break;

		case 5:
		exit(0);
        default:
            cout << "Invalid choice! Please try again.\n";
            break;
        }

        cout << "\nPress any key to continue...";

    } while (c != 5);
}	

void adminmainpage()
{
    int adminID, adminchoice, back, adc, c;
    int prochoice, adchoice;
    string adminid, adminnum, adminname;

    do
    {
        cout << "\t ________________________________________________________________\n";
        cout << "\t|                                                                |\n";
        cout << "\t|                    Welcome to Admin menu                       |\n";
        cout << "\t|________________________________________________________________|\n";
        cout << "\t| 1. View Purchase History                                       |" << endl;
        cout << "\t| 2. View Menu                                                   |" << endl;
        cout << "\t| 3. Logout                                                      |" << endl;
        cout << "\t| 4. Exit                                                        |" << endl;
        cout << "\t|________________________________________________________________|\n";

        cout << endl;

        cout << "\n\n\t Enter your choice : ";
        cin >> c;
        fflush(stdin);
        cin.clear();
        cout << endl;

        while (c < 1 || c > 5)
        {
            cout << "\n\t Choice unavailable. Please Reenter with the correct choice : ";
            cin >> c;
            fflush(stdin);
            cin.clear();
        }

        system("cls");

        switch (c)
        {
        case 1:
            viewhistorys();
            break;
        case 2:
        order:
            viewmenus();
            cout << "1. Searching" << endl;
            cout << "2. Sorting" << endl;
            cout << "3. Add Product" << endl;
            cout << "4. Edit Product" << endl;
            cout << "5. Delete Product" << endl;
            cout << endl;
            cout << "Enter your choice [0 to return back admin main page] : ";
            cin >> prochoice;
            fflush(stdin);
            cin.clear();

            if (prochoice == 0)
            {
                system("cls");
            }

            while (prochoice < 1 || prochoice > 5)
            {
                cout << "Choice unavailable. Please Reenter your choice : ";
                cin >> prochoice;
                fflush(stdin);
                cin.clear();
            }

            switch (prochoice)
            {
            case 1:

                searchBurger();
                system("cls");

                goto order;
                break;

            case 2:

                sortmenu();
                system("cls");
                goto order;
                break;

            case 3:

                addBurger();
                system("cls");
                goto order;
                break;

            case 4:

                editBurger();
                system("cls");
                goto order;
                break;

            case 5:

                deleteBurger();
                system("cls");
                goto order;
                break;
            }
            break;

        

        case 3:
          adminLoginPage();
            break;

		case 4:
		exit(0);
        default:
            cout << "Invalid choice! Please try again.\n";
            break;
        }

        cout << "\nPress any key to continue...";

    } while (c != 5);
}

void viewmenus()
{
 
    cout << "                        Fast-Food Menu" << endl;

    ifstream menu("menu.txt");

    cout << "Id        \t\t\tName \t\t       \t\tPrice(RM)" << endl;
    cout << endl;

   
    for (int i = 0; !menu.eof(); i++)
    {
        menu.ignore();
        getline(menu, x[i].name) >> x[i].price;

        cout << setw(2) << i + 1;
        cout << setw(40) << x[i].name;
        cout << setw(40) << fixed << setprecision(2) << x[i].price << endl;
    }

    menu.close();

    cout << "\nOptions:" << endl;
    cout << "1. Add Food" << endl;
    cout << "2. Delete Food" << endl;
    cout << "3. Edit Food" << endl;
    cout << "4. Sort" << endl;
    cout << "5. Search by name" << endl;

    int option;
    cout << "Enter your choice [0 to return back admin main page]: ";
    cin >> option;
	
	if(option==0)
	{
		system("cls");
		adminmainpage();
	}
    switch (option)
    {
        case 1:
            addBurger();
            system("cls");
            break;
        case 2:
            deleteBurger();
            system("cls");
            break;
        case 3:
            editBurger();
            system("cls");
            break;
        case 4:
            sortmenu();
            system("cls");
            break;
        case 5:
            searchBurger();
            break;
        default:
            cout << "Invalid option. Please select a valid option." << endl;
            break;
    }
}

void addBurger() {
    ofstream add;
    add.open("menu.txt", ios::app);

    if (!add.is_open()) {
        cout << "Error opening file!" << endl;
        return;
    }

    string newburgername;
    float newburgerprice;

    cout << "Enter Food name [0 to return back admin main page]:  ";
    fflush(stdin);
    getline(cin, newburgername);
    	cin.clear();
	     if (newburgername =="0")
        {	 system("cls");
        	adminmainpage();
           
          
        }

    cout << "Enter Food price: ";
    cin >> newburgerprice;
	cin.clear();
    while (newburgerprice < 5) {
        cout << "Price cannot be lower than 5. Please re-enter Food price: ";
        cin >> newburgerprice;
        	cin.clear();
    }

    add << endl<<newburgername << endl;
    add << newburgerprice;

    add.close();

    loading();
    cout << "\n\nAdded successfully." << endl;
    cout << "Press any key to continue..." << endl;
    getche();
    viewmenus();
}

void editBurger()
{
    int i = 0;
    int edit_choice;
    bool check = false;

    ifstream loop("menu.txt");
    ifstream menu("menu.txt");
    ofstream temp("temp.txt");

    while (!loop.eof())
    {
        loop.ignore();
        getline(loop, x[i].name) >> x[i].price;
        i++;
    }
    loop.close();

    do
    {
        cout << "Enter the number of the product you want to edit [0 to return back admin main page]: ";
        cin >> edit_choice;
        fflush(stdin);
        cin.clear();

        if (edit_choice == 0)
        {	 system("cls");
        	adminmainpage();
           
            break;
        }

        while (edit_choice< 1 || edit_choice > i)
        {
            cout << "Invalid number of the product. Please reenter the number of the product you want to edit: ";
            cin >>  edit_choice;
            fflush(stdin);
            cin.clear();
        }

        Food *head = NULL;
        Food *current = NULL;

        i = 0;
        while (!menu.eof())
        {
            Food *newNode = new Food();
            menu.ignore();
            getline(menu, newNode->name);
            menu >> newNode->price;
            newNode->next = NULL;

            if (i + 1 ==  edit_choice)
            {
                check = true;

                int choice;
                cout << "Select an option for Food " <<  edit_choice << ":" << endl;
                cout << "1. Edit Food name" << endl;
                cout << "2. Edit Food price" << endl;
                cout << "Enter your choice: ";
                cin >> choice;
                fflush(stdin);
                cin.clear();

                switch (choice)
                {
                case 1:
                    cout << "Enter the new name for Food " <<  edit_choice << ": ";
                    getline(cin, newNode->name);
                    break;
                case 2:
                    cout << "Enter the new price for Food " <<  edit_choice << ": ";
                    cin >> newNode->price;
                    fflush(stdin);
                    cin.clear();
                    while (newNode->price <= 0)
                    {
                        cout << "Price for Food cannot be lower than 0. Please enter the new price for product " <<  edit_choice << ": ";
                        cin >> newNode->price;
                    }
                    break;
                default:
                    cout << "Invalid choice. No changes will be made to Food " <<  edit_choice << "." << endl;
                    break;
                }

                int selection;
                cout << "Select an option for the edited Food:" << endl;
                cout << "1. Edit name again" << endl;
                cout << "2. Edit price again" << endl;
                cout << "3. Continue" << endl;
                cout << "Enter you choice:" ;

                cin >> selection;
                fflush(stdin);
                cin.clear();

                switch (selection)
                {
                case 1:
                    cout << "Enter the new name for Food " <<  edit_choice << ": ";
                    getline(cin, newNode->name);
                    break;
                case 2:
                    cout << "Enter the new price for Food " <<  edit_choice << ": ";
                    cin >> newNode->price;
                    fflush(stdin);
                    cin.clear();
                    while (newNode->price <= 5)
                    {
                        cout << "Price for Food cannot be lower than 5. Please enter the new price for Food " << edit_choice << ": ";
                        cin >> newNode->price;
                    }
                    break;
                default:
                    break;
                }
            }

            if (head == NULL)
            {
                head = newNode;
                current = newNode;
            }
            else
            {
                current->next = newNode;
                current = newNode;
            }

            i++;
        }

        menu.close();

        current = head;
        while (current != NULL)
        {
            temp << endl<< current->name << endl;
            temp << current->price;
            current = current->next;
        }

        temp.close();
        remove("menu.txt");
        rename("temp.txt", "menu.txt");

        if (check)
        {
             loading();
		cout << "\n\nedit successfully." << endl;
        cout << "Press any key to continue..." << endl;
        getche();
        viewmenus();
        }
    } while (true);
}

void deleteBurger()
{
    bool check = false;

    while (true) {
        int delete_id;
        ifstream menu("menu.txt");
        ofstream temp("temp.txt");

        cout << "Enter the number of the product you want to delete [0 to return back admin main page]: ";
        cin >> delete_id;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (delete_id == 0) {
            system("cls");
            adminmainpage();
        }

        Food* head = NULL;
        Food* current = NULL;

        while (!menu.eof()) {
            Food* newNode = new Food();
            newNode->next = NULL;
            menu.ignore();
            getline(menu, newNode->name);
            menu >> newNode->price;

            if (head == NULL) {
                head = newNode;
                current = newNode;
            } else {
                current->next = newNode;
                current = newNode;
            }
        }

        Food* prev = NULL;
        current = head;
        for (int j = 1; current != NULL; ++j) {
            if (j != delete_id) {
                if (prev == NULL) {
                    temp << endl << current->name << endl;
                    temp << current->price;
                } else {
                    temp << endl << current->name << endl;
                    temp << current->price;
                }
                prev = current;
                current = current->next;
            } else {
                check = true;
                Food* tempNode = current;
                current = current->next;
                delete tempNode;
                if (prev != NULL) {
                    prev->next = current;
                } else {
                    head = current;
                }
            }
        }
        menu.close();
        temp.close();
        remove("menu.txt");
        rename("temp.txt", "menu.txt");

        if (check) { 
            loading();
            cout << "\n\ndelete successfully." << endl;
            cout << "Press any key to continue..." << endl;
            getche();
            system("cls");
            viewmenus();
        } else {
            cout << "Food not found!" << endl;
            getche();
        }
    }
}

void sortmenu()
{
	int sortchoice;
	main_menu x[100];
	
	cout<<endl;
	cout<<"1. Sort by Name"<<endl;
	cout<<"2. Sort by Price"<<endl;
	cout<<"Enter your choice [0 to return back admin main page]: ";
	cin>>sortchoice;
	fflush(stdin);
	cin.clear();
	
	if(sortchoice == 0)
	{
		system("cls");
		adminmainpage(); 
		
	}
	
	
	while(sortchoice < 0 || sortchoice >2){
		cout<<"Choice unavailable. Please Reenter with the correct choice : ";
		cin>>sortchoice;
		fflush(stdin);
		cin.clear();
	}
	
	switch(sortchoice)
	{
		case 1:
				sortbyname();
				
			break;
			
		case 2:
				sortbyprice();
			break;	
	}
}

void sortbyname() {//selection sort
    int i = 0;
    main_menu x[100];

    ifstream menuFile("menu.txt");

    if (menuFile.is_open()) {
        while (!menuFile.eof()) {
            menuFile.ignore();
            getline(menuFile, x[i].name);
            menuFile >> x[i].price;
            i++;
        }
        menuFile.close();

      
        for (int a = 1; a < i - 1; a++) {
            int minIndex = a;
            for (int j = a + 1; j < i; j++) {
                if (x[j].name < x[minIndex].name) {
                    minIndex = j;
                }
            }
            
            if (minIndex != a) {
                main_menu temp = x[a];
                x[a] = x[minIndex];
                x[minIndex] = temp;
            }
        }

        ofstream me("menu.txt");
        for (int j = 0; j < i; j++) {
            me << "\n" << x[j].name;
            me << endl << x[j].price;
        }
        me.close();

        cout << "The Fast-Food's name has been sorted!" << endl; 
    } else {
        cout << "File does not exist." << endl;
    }

    system("cls");
       viewmenus(); 
 
}

void sortbyprice() {
    int i = 0;
    main_menu x[100];

    ifstream menuFile("menu.txt");

    if (menuFile.is_open()) {
        while (i < 100 && menuFile >> ws && getline(menuFile, x[i].name) && menuFile >> x[i].price) {
            i++;
        }
        menuFile.close();

        // Sort the menu items by price
        for (int a = 0; a < i - 1; a++) {
            for (int j = 0; j < i - a - 1; j++) {
                if (x[j].price > x[j + 1].price) {
                    main_menu temp = x[j];
                    x[j] = x[j + 1];
                    x[j + 1] = temp;
                }
            }
        }

        // Rewrite sorted menu to the file
        ofstream menuFile("menu.txt");
        for (int j = 0; j < i; j++) {
            menuFile << endl<< x[j].name ;
            menuFile  << endl<< x[j].price;
        }
        menuFile.close();

        cout << "The menu has been sorted by price." << endl;
    } else {
        cout << "File does not exist." << endl;
    }


    cout<<"The price for the menu already sorted low to hight!!"<<endl;
    system("cls");
    viewmenus();    
}
    
void searchBurger()
{
    string serachname;
    cout << "\t[0 to return back]*only can serach the name only*: ";
    getline(cin, serachname);

    if (serachname == "0")
    {
        system("cls");
        return;
    }

    while (serachname.empty())
    {
        cout << "\nPlease enter a valid keyword to search: ";
        getline(cin, serachname);
        if (serachname == "0")
        {
            system("cls");
            adminmainpage();
        }
    }

    ifstream menu("menu.txt");
    if (menu)
    {
        transform(serachname.begin(), serachname.end(), serachname.begin(), ::tolower);

        string line;
        int lineNum = 0; 

        bool match = false;
        int left = 1;
        int right = 0;
        menu.seekg(0, ios::end);
        right = menu.tellg();
        menu.seekg(0, ios::beg);

        while (left <= right)
        {
            int mid = left + (right - left) / 2;

            getline(menu, line);

            string lowercaseLine = line;
            transform(lowercaseLine.begin(), lowercaseLine.end(), lowercaseLine.begin(), ::tolower);

            if (lowercaseLine.find(serachname) != string::npos)
            {
                match = true;
                cout << "No " << lineNum / 2 + 1 << ": " << line << endl;

                if (getline(menu, line))
                {
                    lineNum++;
                    stringstream ss(line);
                    double price;
                    if (ss >> price)
                    {
                        cout << "Price: " << price << endl;
                    }
                    else
                    {
                        cout << "Price information not found." << endl;
                    }
                }
                else
                {
                    cout << "Price information not found." << endl;
                }
            }

            if (lowercaseLine >= serachname)
            {
                right = mid - 1;
            }
            else
            {
                left = mid + 1;
            }

            lineNum += 1; 
        }

        menu.clear(); 
        while (getline(menu, line))
        {
            string lowercaseLine = line;
            transform(lowercaseLine.begin(), lowercaseLine.end(), lowercaseLine.begin(), ::tolower);

            if (lowercaseLine.find(serachname) != string::npos)
            {
                match = true;
                cout << "No " << lineNum / 2+1 << ": " << line << endl;

                if (getline(menu, line))
                {
                    lineNum++;
                    stringstream ss(line);
                    double price;
                    if (ss >> price)
                    {
                        cout << "Price: " << price << endl;
                    }
                    else
                    {
                        cout << "Price information not found." << endl;
                    }
                }
                else
                {
                    cout << "Price information not found." << endl;
                }
            }

            lineNum++;
        }

        if (!match)
        {
            cout << "No matching products found." << endl;
        }
    }
    else
    {
        cout << "Error opening menu file." << endl;
    }

    menu.close();
    cout << "\nPress any key to continue...";
    
    getche();
	
	
	viewmenus();
}


void viewhistorys() {
    int i = 1;
    float total = 0,g_total=0;
    string userburger,line;
    float customerP,customerC;
    ifstream order("order_details.txt");
    ifstream details("purchasedetail.txt");

    if (!order.is_open() || !details.is_open()) {
        cout << "Error opening file!" << endl;
        return;
    }
		
		     while(details){
		     getline(details,userburger);
		     details>>customerP;
		     details>>customerC;
		        		}
			details.close();
  
			loading();
			system("cls");
			cout<<"\n\t ######################################################################################################"<<endl;
            cout<<"\n\t\t\t\t\t\t\tMMU Fast-Food "<<endl;
			cout<<"\t\t\t\t\t   Jalan Ayer Keroh Lama, 75450 Bukit Beruang"<<endl;
			cout<<"\t\t\t\t\t\tMelaka , Malaysia"<<endl;
			cout<<"\t\t\t\t\t\tTEL : 019-7753357"<<endl;
			cout<<"\t---------------------------------------------------------------------------------------------------------"<<endl;
			cout<<"\t-\t\t\t\t\t\tReceipt\t\t\t\t\t\t\t-"<<endl;
			cout<<"\t---------------------------------------------------------------------------------------------------------"<<endl;
		
          
            while (getline(order, line)) {
            	if (line.empty())
        		continue;   
           istringstream iss(line);
            iss >> p[i].username>>p[i].name>>p[i].price >> p[i].qty >> p[i].subtotal;
        
			cout<<"\tUsername : "<<	p[i].username<<endl;
            	cout<<"\tNo\t\tFast-Food Name\t\t\tItem Price\tQuantity\tTotal Price"<<endl;
                  cout<<"\t"<<i;
                cout<<"\t\t"<<left<<setw(30)<<p[i].name;
                cout<<"\tRM "<<right<<setw(5)<<fixed<<setprecision(2)<<p[i].price<<"\t"<<p[i].qty<<"\t\t"<<p[i].subtotal<<endl;
                total += p[i].subtotal;
                i++;
                  cout<<"\n\t---------------------------------------------------------------------------------------------------------"<<endl;
            }
            order.close();
            cout<<"                                                                                  Total Revenue - RM "<<total<<endl;
            cout<<"\n\t---------------------------------------------------------------------------------------------------------"<<endl;
			cout<<"\n\nPress any key to continue"<<endl;
	
			getche();
			system("cls");
			adminmainpage();
					
}

void admin_customer()
{
	 int choice;

    
    cout<<"\t ________________________________________________________________\n";
	cout<<"\t|                                                                |\n";
	cout<<"\t|                    Welcome to MMU Fast-Food                    |\n";
	cout<<"\t|________________________________________________________________|\n";
	cout<<"\t| 1. Customer                                                    |\n";
	cout<<"\t| 2. Admin                                                       |\n";
	cout<<"\t| 3. Exit Program                                                |\n";
	cout<<"\t|________________________________________________________________|\n";
        while (true) {
        cout << "\n\tEnter your choice: ";
        cin >> choice;

        switch(choice) {
            case 1:
            	system("cls");
                LoginHome();
                break;
            case 2:
            	system("cls");
                adminLoginPage();
                break;
            case 3:
            	system("cls");
                cout << "Exiting program..." << endl;
                exit(0);
                break;
            default:
                cout << "You have entered an invalid choice. Please re-enter." << endl;
        }
    }
}
int main() {
   
	admin_customer();
	
	// Creating instances of Admin and Menu
    Admin adminUser("admin1", "admin123", "A123");
    Menu menuItem("Burger", 10.50);
	
	// Testing friend functions
    friendFunction1(adminUser); // Accessing User details via friend function
    friendFunction2(menuItem); // Accessing Menu details via friend function
    return 0;
}
