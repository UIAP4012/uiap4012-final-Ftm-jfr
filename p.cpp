#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
using namespace std;

void login_manager();
void login();
int main();

class currency{
public:
    double dollor;
    double euro;

    currency(){
        ifstream file("currency.txt");
        string line;
        getline(file,line);
        dollor=stod(line);
        getline(file,line);
        euro= stod(line);
    }

    void Edit(){
        cout<<"$ :";
        cin>>dollor;
        cout<<"€ :";
        cin>>euro;
        ofstream currency("currency.txt");
        currency<<dollor<<endl<<euro;
    }

    double exchangetodollor(double toman){
        double priceindollor;
        priceindollor=toman/dollor;
        return priceindollor;
    }

    double exchangetoeuro(double toman){
        double priceineuro;
        priceineuro=toman/euro;
        return priceineuro;
    }
};

class product{
public:
    string Product_ID,Expiration_date;
    string name;
    string price,number;
    void add_product()
    {
        cout<<"name :";
        cin>> this->name;
        cout<<"quantity :";
        cin>>this->number;
        cout<<"ID :";
        cin>>this->Product_ID;
        cout<<"price :";
        cin>>this->price;
        cout<<"exp date :";
        cin>>this->Expiration_date;
        ofstream product(name + ".txt",ios_base::app);
        product<<this->name<<endl<<this->number<<endl<<this->Product_ID<<endl<<this->price<<endl<<this->Expiration_date<<endl;
        product.close();
        ofstream products("products.txt",ios_base::app);
        products<< this->name<<endl<< this->Product_ID<<endl;
        products.close();
    }

    void updatequantity(int newnum,const string& namee)
    {
        ifstream product((namee + ".txt"));
        ofstream temp("temp.txt",ios_base::app);

        string line;
        getline(product,line);
        temp<<line<<endl;
        getline(product,line);
        temp<<stoi(line)-newnum<<endl;
        getline(product,line);
        temp<<line<<endl;
        getline(product,line);
        temp<<line<<endl;
        getline(product,line);
        temp<<line;
        product.close();
        temp.close();

        remove((namee + ".txt").c_str());
        rename("temp.txt",(namee + ".txt").c_str());
    }
    void deleteproduct()
    {
        cout<<"Enter the product name :";
        cin>>name;
        remove((name+(".txt")).c_str());
        ofstream temp("temp.txt");
        ifstream product("products.txt");
        string line;
        while (getline(product,line)){
            if(line!=name)
            {
                temp<<line<<endl;
                getline(product,line);
                temp<<line<<endl;
            }
            else
                getline(product,line);
        }
        product.close();
        temp.close();

        remove("products.txt");
        rename("temp.txt","products.txt");
    }
    void editproduct()
    {
        cout<<"Name :";
        cin>>name;
        string N=name;
        remove((name + ".txt").c_str());
        ofstream temp(("temp.txt"));
        cout<<"New Name :";
        cin>>name;
        temp<<name<<endl;
        cout<<"New Number :";
        cin>>number;
        temp<<number<<endl;
        cout<<"New Product ID :";
        cin>>Product_ID;
        temp<<Product_ID<<endl;
        cout<<"New Price :";
        cin>>price;
        temp<<price<<endl;
        cout<<"New Exp date :";
        cin>>Expiration_date;
        temp<<Expiration_date<<endl;
        temp.close();
        rename("temp.txt",(name + ".txt").c_str());

        ofstream temp2("temp.txt");
        ifstream p("products.txt");
        string line;
        while(getline(p,line))
        {
            if(line!=N)
            {
                temp2<<line<<endl;
                getline(p,line);
                temp2<<line<<endl;
            }
            else
            {
                ifstream edif(name+".txt");
                getline(edif,line);
                temp2<<line<<endl;
                getline(edif,line);
                getline(edif,line);
                temp2<<line<<endl;
                edif.close();
                getline(p,line);
            }

        }p.close();
        temp2.close();

        remove("products.txt");
        rename("temp.txt","products.txt");
    }
    void show_product(){
        ifstream products("products.txt");
        string line;
        cout<<"Name--------Qantity\n";
        while (getline(products,line))
        {
            if(!line.empty())
                cout<<line<<"----------";
            ifstream quantity(line+".txt");
            getline(quantity,line);
            getline(quantity,line);
            if(!line.empty())
                cout<<line<<endl;
            quantity.close();
            getline(products,line);
        }products.close();
    }
};

class employee :public product{
    friend class manager;
private:
    string name,employee_iD,email,password;
public:
    void add_factor()
    {
        ifstream factornum("factornumber.txt");
        string line_num;
        getline(factornum,line_num);
        factornum.close();
        line_num= to_string(stoi(line_num)+1);
        ofstream factnum("factornumber.txt");
        factnum<<line_num;
        factnum.close();
        long int sum=0;
        ofstream factor("factor"+ line_num+".csv");
        factor<<"Name,Number,Id,Price\n";
        cout<<"Enter zero ID to finish\n";
        while(true)
        {
            cout<<"ID :";
            string line_name,line_id;
            cin>>Product_ID;
            ifstream file("products.txt");
            if(Product_ID=="0")
            {
                file.close();
                break;
            }
            while(getline(file,line_name))
            {
                getline(file,line_id);
                if(line_id==Product_ID)
                {
                    ifstream product(line_name+".txt");
                    string line;
                    getline(product,line);//name
                    factor<<line<<",";
                    cout<<"number :";
                    getline(product,line);//num


                    product.close();
                    string lp;
                    cin>>lp;//quantity
                    factor<<lp<<",";
                    updatequantity(stoi(lp),line_name);
                    ifstream product2(line_name+".txt");
                    getline(product2,line);
                    getline(product2,line);


                    getline(product2,line);//id
                    factor<<line<<",";
                    getline(product2,line);//price
                    sum+=stoi(line)* stoi(lp);
                    factor<<line<<",\n";
                    product2.close();
                    break;
                }
            }
        }
        currency a;
        factor<<"Total price :,"<<sum<<","<<a.exchangetodollor(sum)<<" $,"<<a.exchangetoeuro(sum)<<" €,\n";
        time_t t;
        struct tm* tim;
        time(&t);
        tim = localtime(&t);
        factor << asctime(tim)<<",\n";
        factor.close();
    }
};

class manager :employee ,currency {
private:
    string name="_MANAGER_";
    string email="MAnageSTore@gmail.com";
    string password="FTYHb345vgjkd254";
public:
    void add(){
        cout<<"Name :";
        cin>> this->name;
        cout<<"Employee Id :";
        cin>> this->employee_iD;
        cout<<"Email :";
        cin>> this->email;
        cout<<"Password :";
        cin>> this->password;

        hash<string> hash_pass;
        size_t hash_value = hash_pass(password);

        ofstream employee(this->employee_iD+".txt",ios_base::app);
        ofstream employees("empinfo.txt",ios_base::app);
        employee<< this->name<<endl<< this->employee_iD<<endl<< this->email<<endl<< hash_value<<endl;
        employees<< this->name<<endl<< this->employee_iD<<endl<< this->email<<endl<< hash_value<<endl;
        employee.close();
        employees.close();
    }

    void print_employee_info() {
        ifstream employees("empinfo.txt");
        string line;
        while (getline(employees, line)) {
            cout << line << endl;
        }
        employees.close();
    }

};

void options(bool flag)
{
    if(!flag)
        cout<<"1.Add new product\n2.Edite products\n3.Delete product\n4.Show all products\n5.Add factor\n6.Log out\n";
    if(flag)
        cout<<"1.Add new product\n2.Edite products\n3.Delete product\n4.Show all products\n5.Add factor\n6.Add new employee\n7.Employees info\n8.Edit exchange rate\n9.Log out\n";
    int order=0;
    employee a;
    cin>>order;
    if(order==1)
        a.add_product();
    else if(order==5)
        a.add_factor();
    else if(order==2)
        a.editproduct();
    else if(order==3)
        a.deleteproduct();
    else if(order==4)
        a.show_product();
    if(flag)
    {
        manager x;
        currency y;
        if(order==6)
            x.add();
        else if(order==7)
            x.print_employee_info();
        else if(order==8)
            y.Edit();
        else if(order==9)
            return;
        if(order!=9)
            options(flag);
    }
    else if(order==6)
        return;
    if(order!=6)
        options(flag);
}

void login_manager()
{
    string name,email,password;
    cout<<"Name :";
    cin>>name;
    cout<<"Email :";
    cin>>email;
    cout<<"Password :";
    cin>>password;
    if(name=="_MANAGER_")
    {
        if(email=="MAnageSTore@gmail.com")
        {
            if(password=="FTYHb345vgjkd254")
                options(true);
        }
    }
}

bool check_password(const string& password,unsigned long long int line)
{
    hash<string> hash_pass;
    unsigned long long  int hash_value = hash_pass(password);
    if(hash_value==(line))
        return true;
    else
        return false;
}

void login()
{
    string name,employee_iD,email,password;
    cout<<"Name :";
    cin>>name;
    cout<<"Employee Id :";
    cin>>employee_iD;
    cout<<"Email :";
    cin>>email;
    cout<<"Password :";
    cin>>password;
    ifstream file(employee_iD+".txt");
    if(!file.is_open())
        cout<<"No such employee was found\n";
    else
    {
        string line;
        getline(file,line);//name
        if(line==name)
        {
            getline(file,line);//id
            if(line==employee_iD)
            {
                getline(file,line);//email
                if(line==email)
                {
                    getline(file,line);//password
                    unsigned long long int l= stoull(line);
                    if(check_password(password, l))
                    {
                        options(false);
                    }

                }
            }
        }
    }
}

int main()
{
    cout<<"Who are you ?\n1.Employee\t\t2.Manager\nPress 3 if you want to exit\n";
    string order="0";
    cin>>order;
    while (order!="3")
    {
        if(order=="1")
            login();
        else if(order=="2")
            login_manager();
        cout<<"Who are you ?\n1.Employee\t\t2.Manager\nPress 3 if you want to exit\n";
        cin>>order;
    }
    return 0;
}
