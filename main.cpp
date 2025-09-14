#include <iostream>
#include <cstdio>
#include <iomanip>
#include <vector>
#include <string>
#include <cstdlib>
#include <fstream>
using namespace std;

const string Fpath = "/storage/emulated/0/clientinfo1.txt" ;

const string User_path = "/storage/emulated/0/users.txt" ;

enum enMenu { display = 1 , add = 2 , deleted = 3 , update = 4 , Find = 5 , transaction = 6, manege = 7 ,Exit = 8 };

enum enActions { deposit = 1 , withdraw = 2 , total = 3 , backmenu = 4 } ;  

enum ePermission { show_user = 1 , add_user = 2 , del_user = 4 , update_user = 8 , Find_user = 16 , trans_user = 32 , manege_user = 64 };
 
 enum eManegeMenu { List = 1 , Add = 2 , Del = 3 , Update = 4 , mange_Find = 5 , Main_Menu = 6 } ; 
   
struct stClient {
    
    string AccountNum;
    string PinCode;
    string Name ;
    string Phone;
    string Balance ;
    bool IsMarked = false ;    
};

struct sUser {
     
     string name ; 
     string password ;
     long int perm = 0 ; 
     bool IsMarked = false ; 
 }; 


string ReadNum (string msg ){
    
    string n ;
    cout << msg ;
    getline(cin >> ws , n );
    
    return n ; 
}

vector<string> split (string str , string space = "#//#") {
   
    string sword ="";
    vector<string> strInfo ;
    short pos =0;
    
    // find the separator and save index in pos 
    while ((pos = str.find(space)) != std :: string ::npos){
        
    //  cut the word and save it in vector 
        sword = str.substr(0, pos);
        if (sword != ""){
            strInfo.push_back(sword) ;
        }
        str.erase(0 , pos + space.length());
        
    }
    
    // because the condition at while loop there a word well left in string str 
    if (str != "")
        strInfo.push_back(str) ;
        
    return strInfo ;
}

string JoinClient ( stClient strInfo , string space ="#//#"){
  
    string line ="";
    
    line += strInfo.AccountNum + space ;
    line += strInfo.PinCode + space ;
    line += strInfo.Name + space ;
    line += strInfo.Phone + space ;
    line += strInfo.Balance ;
    
    return line ;  
}

string JoinClient ( sUser strInfo , string space ="#//#"){
  
    string line ="";
    
    line += strInfo.name + space ;
    line += strInfo.password + space ;
    line += to_string(strInfo.perm );
    
    return line ;  
}

stClient ChangDateToStruct(vector<string>vstr){
        
    stClient Client ;
    
    if (vstr.size() >= 4){
        
        Client.AccountNum = vstr[0] ;
        Client.PinCode = vstr[1] ;
        Client.Name = vstr[2] ;
        Client.Phone = vstr[3] ;
  //      Client.Balance = stod(vstr[4]) ;    
        Client.Balance = vstr[4];
    }
    return Client ;          
}



sUser ChangDataUserToStruct(vector<string>vstr){
        
    sUser user ;
    
    if (vstr.size() >= 3){
        
        user.name = vstr[0] ; 
        user.password = vstr[1] ;
        user.perm = stoi(vstr[2] ) ; 
    }
    return user ;          
}

vector<stClient> LoadClientFromFile(  ){
    
    vector<stClient> vclients ;
    fstream myfile ;
    string line ;
    myfile.open(Fpath , ios :: in);

    if (myfile.is_open()){

        while (getline(myfile , line)){
            
            vclients.push_back(ChangDateToStruct(split(line)));                        
        } 
        myfile.close();              
    }  
    return  vclients ;  
}


void SaveClientsToFile(vector<stClient>& vClients){
    
    fstream myfile ;
    
    myfile.open(Fpath , ios :: out);
    
    if(myfile.is_open()){
        
        for (stClient& c : vClients ){
            
            if (c.IsMarked == false ){ 
                myfile << JoinClient(c) << endl ;
            }
            
        }        
    }
    myfile.close();        
}


void DisplayClients (vector<stClient>& vClients ){
    
    system("clear");
    
    cout << "                                   account Client(s) [ "<<vClients. size() <<" ]  \n";
    cout << "\n-------------------------------------------------------------------------------------------\n"; //80
    cout << left << setw(20) << "|Account number" ;
    cout << left << setw(15) << "|Pin code " ;
    cout << left << setw(20) << "|Name " ;
    cout << left << setw(20) << "|Phone ";
    cout << left << setw(15) << "|Balance ";
    cout <<"|";
    // a separator 
    cout<< endl <<setw(20) <<"|" << setw(15) <<"|"<< setw(20) <<"|" << setw(20) << "|" << setw(15) << "|" <<"|" ;//<<setw(15) << "|" ;
    
    cout << "\n|_________________________________________________________________________________________|\n"; //90_
    
    cout <<setw(20) <<"|" << setw(15) <<"|"<< setw(20) <<"|" << setw(20) << "|" << setw(15) << "|" <<"|\n";
    vClients= LoadClientFromFile() ;
    
    for(stClient& C :   vClients){
        // C meaning client

        cout <<"|" <<left<<setw(19)<< C.AccountNum;
        cout <<"|" <<left << setw(14)<<C.PinCode ;
        cout <<"|" <<left << setw(19)<<C.Name ;
        cout <<"|" <<left <<setw(19)<<C.Phone ;
        cout <<"|"<<left <<setw(14)<< C.Balance<<"|" ;
        cout <<endl ;
    }
    
    cout <<setw(20) <<"|" << setw(15) <<"|"<< setw(20) <<"|" << setw(20) << "|" << setw(15) << "|" <<"|\n";
    cout <<"|_________________________________________________________________________________________|\n";
    system ("pause");
}


void PrintStruct (stClient Client){
    
    cout<<endl << " client info : ";
    cout <<"\n_________________________________" ;
    cout <<"\n account number  : "<<Client.AccountNum << endl ;
    cout <<" pin code        : "<< Client.PinCode << endl ;
    cout <<" name            : "<<Client.Name<< endl ;
    cout <<" phone number    : " << Client.Phone << endl ;
    cout <<" account balance : "<< Client.Balance << endl ;    
    cout <<"\n_________________________________\n" ;
}


bool FindClient (string AccountNum, vector<stClient> vClients, stClient& client ){
    
    vClients= LoadClientFromFile() ;
    for (stClient & C : vClients){
        
        if (AccountNum == C.AccountNum){
            
            client = C ;
            return true ;
        }
    }    
    return false ;
}

void FindClientFunction(string AccountNum, vector<stClient> vClients , stClient client){
    
    system("clear");
    AccountNum= ReadNum (" enter the account number : ");
    
    if (FindClient(AccountNum, vClients, client)){
        
        PrintStruct(client);
    }
    else 
        cout << "\n client with number ( "<< AccountNum <<" ) not found \n" ;
        
     cout << endl ;
     system ("pause");   
}


void ReadClientData (stClient& c){
    
    cout <<" enter pin code  : ";
    getline(cin >> ws , c.PinCode);
    cout <<" enter the name : ";
    getline (cin , c.Name);
    cout <<" enter the phone number : ";
    getline (cin , c.Phone);
    cout <<" enter the balance : ";
    cin >> c. Balance;    
    
}


void AddClient (vector<stClient>& vClients, stClient& client){
    
    system("clear");
    cout <<"\n----------------------------------\n";
    cout << "            Add client (s)            ";
    cout << "\n----------------------------------\n" ;
    char answer ='n' ;
    do {
        
        string AccountNum= ReadNum("\n enter account number : ");
        
        if (!FindClient (AccountNum,vClients, client )){
            
            client.AccountNum = AccountNum ;
            ReadClientData(client);
            vClients.push_back(client ); 
            SaveClientsToFile(vClients);
            
            cout <<"\n client added successfully ";
        }
        else 
            cout <<"\n sorry account number is already taken! "; 
            
     cout <<"\n\n are you want to add more client ? (y/n)? ";
     cin >> answer ;       
             
    }while(tolower(answer) == 'y') ;
        
   cout <<endl ;
   system ("pause");
}

void MarketClientToDel( vector<stClient>& vClients , string AccountNum){
    
    for (stClient& c : vClients ){
        
        if (c.AccountNum == AccountNum ){
            c.IsMarked = true ;
        }
    }    
}

void DeleteClient(vector<stClient>& vClients  ){
    
    stClient client ;
    system ("clear");
    cout <<"\n----------------------------------\n";
    cout << "              delete menu         ";
    cout <<"\n----------------------------------\n";
    
    char accept ='n';
    string AccountNum= ReadNum("\n enter account number : ");
    
    if (FindClient (AccountNum,vClients, client )){
        
        PrintStruct (client );
        cout << " are you sure to delete account? (y/n)? ";
        cin >> accept ;
        if (tolower(accept) == 'y'){
            
            MarketClientToDel(vClients, AccountNum);
            SaveClientsToFile(vClients);
            
            cout <<"\n client deleted successfully ";
        }
    }
    else {
        cout << "\n client number is not exist !";
        
    }   
    cout << endl ; 
    system(" pause");
}

void CompleteUpdate (vector<stClient>& vClients , string AccountNum , stClient& client ){
    
    for (stClient& c : vClients ){
        
        if (AccountNum == c.AccountNum){
            
            client.AccountNum = AccountNum ;
            ReadClientData (client);            
            
            c.AccountNum = client.AccountNum ;
            c.PinCode = client.PinCode ;
            c.Name = client.Name ;
            c.Phone  = client.Phone ;
            c.Balance = client.Balance ; 
                        
            SaveClientsToFile(vClients);
            
            break ;
        }        
    }       
}

void UpdateClient (vector<stClient>& vClients ){
    
    stClient client ;
    system ("clear");
    cout <<"\n----------------------------------\n";
    cout << "              update menu         ";
    cout <<"\n----------------------------------\n";
    
    char accept ='n';
    string AccountNum= ReadNum("\n enter account number : ");
    
    if (FindClient (AccountNum,vClients, client )){
        
        PrintStruct (client );
        cout << " are you sure to update account? (y/n)? ";
        cin >> accept ;
        if (tolower(accept) == 'y'){
            
            CompleteUpdate(vClients, AccountNum, client); 

            PrintStruct (client );
        }        
    }
    
    else 
        cout <<"\n sorry there is no client with number ( "<< AccountNum<<" ) to update "; 
    
    
    cout << endl ;
    system("pause");
}


void PrintMenu (){
    system("clear");
    cout <<"\n----------------------------------\n";
    cout << "              Main menu               ";
    cout << "\n----------------------------------\n" ;
    cout << "\n    [1]. show all client " ;
    cout << "\n    [2]. add new client ";
    cout << "\n    [3]. delete old clint";
    cout << "\n    [4]. update old clint";
    cout << "\n    [5]. find client ";
    cout << "\n    [6]. transactions" ;
    cout << "\n    [7]. manege menu" ;
    cout << "\n    [8]. logout " ; 
    cout << "\n----------------------------------" << endl;         
}

void ShowActionsMenu (){
    
    system("clear");
    cout <<"\n----------------------------------\n";
    cout << "              Actions menu               ";
    cout << "\n----------------------------------\n" ;
    cout << "\n    [1]. deposit " ;
    cout << "\n    [2]. with draw ";
    cout << "\n    [3]. total balances";
    cout << "\n    [4]. back to main menu";
      cout << "\n----------------------------------" ;
    cout << endl ;    
}

short ReadChoice (){
    
    short n ; 
    cout << " enter a choice between (1-4) : ";
    cin >> n ;
    
    return n ; 
}

void DisplayTotalBalances( vector<stClient> vClients ){
    
    system("clear");
    
    cout << "              account Client(s) [ "<<vClients. size() <<" ]  \n";
    cout << "\n--------------------------------------------------------\n"; //80
    cout << left << setw(20) << "|Account number" ;

    cout << left << setw(20) << "|Name " ;

    cout << left << setw(15) << "|Balance ";
    cout <<"|";
    // a separator 
    cout<< endl <<setw(20) <<"|" << setw(20) <<  "|" << setw(15) << "|" <<"|" ;//<<setw(15) << "|" ;
   
    cout << "\n|______________________________________________________|\n"; //90_
    
    cout <<setw(20) <<"|"<< setw(20) << "|" << setw(15) << "|" <<"|\n";
    vClients= LoadClientFromFile() ;
    
    int TotalBalances =0;
    
    
    for(stClient& C :   vClients){
        // C meaning client

        cout <<"|" <<left<<setw(19)<< C.AccountNum;

        cout <<"|" <<left << setw(19)<<C.Name ;

        cout <<"|"<<left <<setw(14)<< C.Balance<<"|" ;
        cout <<endl ;
        
        TotalBalances += stod(C.Balance) ;
    }
    
    cout <<setw(20) <<"|"<< setw(20) << "|" << setw(15) << "|" <<"|\n";
    cout <<"|______________________________________________________|";
    cout <<" \t\t\t\t    total balances : $" << TotalBalances << endl ;
    system ("pause");
    
}

void DepositToClient (vector<stClient>& vClients , string AccountNum , double deposit){
           
    for (stClient& c : vClients){
        
        if (AccountNum == c.AccountNum ){
            
            c.Balance = to_string( stod(c.Balance) + deposit) ;
            SaveClientsToFile (vClients);
            break ;
        }        
    }
}

void ShowDepositTitle (){
    
     system("clear");
    cout <<"\n----------------------------------\n";
    cout << "              Deposit menu               ";
    cout << "\n----------------------------------\n" ;
    
} 

void DepositBalanceToClient (vector<stClient>& vClients ){
    
    string AccountNum= ReadNum (" enter the account number  : ");
    stClient client ;
    
        
    if (FindClient (AccountNum , vClients , client )){
        
        PrintStruct (client );
        
        double deposit=0;
    cout << "\n enter the amount to deposit : ";
    cin >> deposit ;
        DepositToClient(vClients, AccountNum, deposit );
        
        cout <<"\n amount deposited successfully ! ";
    }
    else {
        
        cout << "\n account number not found ! ";
    }
    
    cout << endl ;
    system ("pause");
    
}

void ShowWithDrawTitle (){
    
     system("clear");
    cout <<"\n----------------------------------\n";
    cout << "            Withdraw menu               ";
    cout << "\n----------------------------------\n" ;    
} 

void WithdrawFromClient (vector<stClient>&vClients , string AccountNum , double withdraw ){
        
    for (stClient& c : vClients){
        
        if (AccountNum == c.AccountNum ){
            
            c.Balance = to_string( stod(c.Balance) - withdraw ) ;
            SaveClientsToFile (vClients);
            break ;
        }        
    }    
}

void WithdrawBalaceFromClient(vector<stClient>& vClients){

    string AccountNum= ReadNum (" enter the account number  : ");
    stClient client ;
    
    char answer ; 
    double draw = 0 ;    
    
    if (FindClient (AccountNum , vClients , client )){
        
        if ( stod(client.Balance) >= draw){
            
            PrintStruct (client );
            
            cout << "\n enter the amount to draw : ";
    cin >> draw ;
    
            cout <<"\n are you sure to witdraw amount ? (y/n) ? ";
            cin >> answer ;
            if (tolower(answer) == 'y'){
                
                WithdrawFromClient(vClients, AccountNum , draw);
                
            }
            cout <<"\n amount drawed successfully ";            
        }
        else {
            cout <<"\n invlided process! the balance : "<<client.Balance <<" you can't draw amount "; 
        }                
    }
    else {
        cout << " the account number not found ! ";
    }
    
    cout << endl ;
    system("pause");
        
}

void ActionsMenu (vector<stClient>& vClients){
    
    short answer = 0 ;
    do {
        ShowActionsMenu();
        answer = ReadChoice () ;
        
        switch ((enActions )answer){
            
            case enActions :: deposit:{
                ShowDepositTitle();
                DepositBalanceToClient(vClients );
                break ;
            }
           case  enActions :: withdraw:{
                ShowWithDrawTitle();
                WithdrawBalaceFromClient(vClients );
                break ;
           }
           case  enActions :: total : {
                DisplayTotalBalances(vClients );
                break ;
           }
           case enActions :: backmenu:{                
                break ;
           }            
        }
                
    }while((enActions)answer != enActions :: backmenu );        
}


void EndScreen(){
    
    system("clear");
     cout <<"\n----------------------------------\n";
    cout << "          PROGRAM END               ";
    cout << "\n----------------------------------\n" ;        
}

void SaveUsersToFile(vector<sUser>& vUser){
    
    fstream myfile ;
    
    myfile.open(User_path  , ios :: out);
    
    if(myfile.is_open()){
        
        for (sUser& c : vUser ){
                
            if (c.IsMarked == false ){ 
                
                myfile << JoinClient(c) << endl ;     
        }        
    }
    myfile.close();        
}
}

vector<sUser> LoadUsersFromFile(  ){
    
    vector<sUser> vUsers ;
    fstream myfile ;
    string line ;
    myfile.open(User_path , ios :: in);

    if (myfile.is_open()){

        while (getline(myfile , line)){
            
            vUsers.push_back(ChangDataUserToStruct(split(line)));                        
        } 
        myfile.close();              
    }  
    return  vUsers ;  
}


bool FindUser (string name, string password,  sUser& user , vector<sUser> vUser ){
    
   // vector<sUser> vUser = LoadUsersFromFile() ;
    for (sUser & C : vUser){
        
        if ( C.name == name && C.password == password ){
            
            user = C ;
            return true ;
        }
    }    
    return false ;
}

bool FindUser (string name,  vector<sUser> vUser ){
    
   // vector<sUser> vUser = LoadUsersFromFile() ;
    for (sUser & C : vUser){
        
        if ( C.name == name ){
            
            return true ;
        }
    }    
    return false ;
}

void ShowListUser ( vector<sUser> vUser  ){
    
    system("clear");
 //   vector<sUser> vUser = LoadUsersFromFile() ; 
    cout << "              account User(s) [ "<<vUser.size() <<" ]  \n";
    cout << "\n--------------------------------------------------------\n"; //80
    cout << left << setw(20) << "|USER NAME " ;

    cout << left << setw(20) << "|PASSWORD " ;

    cout << left << setw(15) << "|PERMISSION ";
    cout <<"|";
    // a separator 
    cout<< endl <<setw(20) <<"|" << setw(20) <<  "|" << setw(15) << "|" <<"|" ;//<<setw(15) << "|" ;
   
    cout << "\n|______________________________________________________|\n"; //90_
    
    cout <<setw(20) <<"|"<< setw(20) << "|" << setw(15) << "|" <<"|\n";
  //  vUser= LoadUsersFromFile() ;
    

    for(sUser& C :   vUser){
        // C meaning client

        cout <<"|" <<left<<setw(19)<< C.name;

        cout <<"|" <<left << setw(19)<<C.password ;

        cout <<"|"<<left <<setw(14)<< C.perm <<"|" ;
        cout <<endl ;

    }
    
    cout <<setw(20) <<"|"<< setw(20) << "|" << setw(15) << "|" <<"|\n";
    cout <<"|______________________________________________________|\n";
    cout << endl ;
    system ("pause");
}

void InvalidAccess(){
    
    system("clear");
     cout <<"\n--------------------------------------------\n";
    cout << "       THE USER CAN'T ACCESS FOR THIS OPTION              ";
    cout << "\n--------------------------------------------\n" ;    
    
    cout << endl ; 
    system ("pause");
}
void LoginScreen(){
    
    system("clear");
     cout <<"\n----------------------------------\n";
    cout << "           LOGIN SCREEN               ";
    cout << "\n----------------------------------\n" ;     
}

void ReadUserInfo (string& name , string& password ){
    
    cout <<"\n enter user name : ";
    getline ( cin >> ws, name);
    cout << " enter user password : ";
    getline ( cin >> ws, password);    
}

sUser LoginMenu(vector<sUser>& vUser ){
    
    LoginScreen();
    string name , password ; 
    sUser user ; 
    //vector<sUser> vUser = LoadUsersFromFile (); 
        
    ReadUserInfo(name , password ); 
        
    while( ! FindUser(name , password , user , vUser ) ){
        LoginScreen(); 
        cout <<"\n falid password or user name  "; 
        ReadUserInfo(name , password ); 
    }
    
    return user ; 
}

void ManegeScreen(){
    
    system("clear");
     cout <<"\n------------------------------------------\n";
    cout << "           MANEGE Users Menue SCREEN               ";
    cout << "\n------------------------------------------\n" ;    
    
}

void AddUserScreen(){
    
    system("clear");
     cout <<"\n----------------------------------\n";
    cout << "           ADD USERS SCREEN               ";
    cout << "\n----------------------------------\n" ;     
}

sUser UserAccesInfo (sUser& user ){
     
      cout <<" do you want to give full access?(y/n)";
      char answer ;
      cin >> answer ;    
      if (answer == 'y' ){
        user.perm = -1;
      }
      else {
           user.perm = 0 ; 
           cout <<"\n give access for show client? " ; 
           cin >> answer ; 
           if ( answer == 'y' ) user.perm += show_user ;
           
           cout <<"\n give access for add client? " ; 
           cin >> answer ; 
           if ( answer == 'y' ) user.perm += add_user ;   
                   
           cout <<"\n give access for delete client? " ; 
           cin >> answer ; 
           if ( answer == 'y' ) user.perm += del_user ;    
           
           cout <<"\n give access for update client? " ; 
           cin >> answer ; 
           if ( answer == 'y' ) user.perm += update_user ; 
           
           cout <<"\n give access for find client? " ;
           cin >> answer ; 
           if ( answer == 'y' ) user.perm += Find_user ;
           
           cout <<"\n give access for trans client? " ;
           cin >> answer ; 
           if ( answer == 'y' ) user.perm += trans_user ;
           
           cout <<"\n give access for manege client?";
           cin >> answer ; 
           if ( answer == 'y' ) user.perm += manege_user ;
          
      }
      return user ;  
} 

bool AddNewUser (vector<sUser>& vUser ){
    
    sUser user  ;
    string name ;
    
    cout << "\n enter user name : ";
    getline (cin >> ws , name) ; 
    
    if ( FindUser( name , vUser ) ){
      
        return false ; 
    }
    user.name = name ; 
    cout <<"\n enter the password :";
    getline (cin >> ws , user.password) ;
    
    UserAccesInfo (user) ;  
    
    vUser.push_back(user);     
    SaveUsersToFile (vUser) ; 
    return true ;
}

void AddNewUsers (vector<sUser> vUser ){
    
    char answer = 'n';
    
    do { 
        AddUserScreen() ; 
        if(AddNewUser(vUser)){       
            cout <<"\n user added successfully... ";  
        }
        else {
            cout <<"\n user name already taken! \n\n";
        }               
        cout << "  added one more user ?(y/n) ";     
        cin >> answer ;     
    } while (tolower(answer) == 'y');
    
}

void ManegeMenu (){
    
    ManegeScreen(); 
    cout << "\n    [1]. List User " ;
    cout << "\n    [2]. Add New User  ";
    cout << "\n    [3]. Delete User ";
    cout << "\n    [4]. Update User ";
    cout << "\n    [5]. Find User ";
    cout << "\n    [6]. Main Menue"; 
     cout << "\n----------------------------------" ;
    cout << endl ;    
}

void DelUserScreen(){
    
    system("clear");
     cout <<"\n----------------------------------\n";
    cout << "          DELETE USERS SCREEN    ";
    cout << "\n----------------------------------\n" ;     
}

void MarketUserToDel( vector<sUser>& vUsers , string name ){
    
    for (sUser& c : vUsers ){
        
        if (c.name == name ){
            c.IsMarked = true ;
        }
    }    
}
void PrintUser (sUser user){
    
    cout <<"\n__________________\n";
    cout <<"\n name : "<< user.name ; 
    cout <<"\n password : "<< user.password ;
    cout <<"\n permissions : "<< user.perm ; 
    cout <<"\n__________________\n";
    
}
void PrintUsers (string name , vector<sUser> vuser){
    
    for (sUser& c : vuser){
        
        if (name == c.name ){
            
            PrintUser(c);
        }        
    } 
}

bool DeleteUser (vector<sUser>& vUser ){
    
    DelUserScreen() ; 
    string name ; 
    cout <<"\n enter the name of user to delete "; 
    getline(cin>> ws , name );
    
    if (name == "admin") {
        
        cout <<"\n admin can't deleted! \n" ; 
        return false ; 
    }
    if (FindUser(name , vUser ) && name != "admin"){
        
        char answer ='n' ; 
        PrintUsers(name , vUser ); 
        cout << "\n Are you sure to delete user [ "<< name <<" ] ?(y/n) " ;
        cin >> answer ; 
        
        if (answer == 'y'){
            MarketUserToDel(vUser , name ); 
            SaveUsersToFile (vUser) ; 
            return true ;
        }
    }
    else {
         cout <<"\n user name not found! \n\n";
     }  
    return false ; 
}

void DleteUsers (vector<sUser>& vUser ){
    
    char answer = 'n';
    
    do { 
        DelUserScreen() ; 
        if(DeleteUser(vUser)){       
            cout <<"\n user Deletd successfully... ";  
        }
                   
        cout << "  delete one more user ?(y/n) ";     
        cin >> answer ;     
    } while (tolower(answer) == 'y');
    
}

bool UpdateUser (string name , vector<sUser>& vUser){
    
    for (sUser& c : vUser){
        
        if (name == c.name ){
            string password=""; 
            cout <<"\n enter the password ";
            getline (cin>>ws , password); 
            c.password = password;         
            c = UserAccesInfo (c); 
            SaveUsersToFile (vUser) ; 
            return true ; 
        }
    } 
    return false ;    
}


void UpdateUserScreen(){
    
    system("clear");
     cout <<"\n----------------------------------\n";
    cout << "          UPDATE USERS SCREEN    ";
    cout << "\n----------------------------------\n" ;     
}

void UpdateUsersInfo (vector<sUser>& vUser ){
    
    UpdateUserScreen() ; 
    string name ; 
    cout <<"\n enter the name of user to update "; 
    getline(cin>> ws , name );
    
    if (name == "admin") {
        
        cout <<"\n admin can't updated ! \n" ; 
        
    }
    if (FindUser(name , vUser ) && name != "admin"){
        
        char answer ='n' ; 
        PrintUsers(name , vUser ); 
        cout << "\n Are you sure to update user [ "<< name <<" ] ?(y/n) " ;
        cin >> answer ; 
        
        if (answer == 'y'){
            UpdateUser( name , vUser );
            SaveUsersToFile (vUser) ;   // 

        }
    }
    else {
         cout <<"\n user name not found! \n\n";
     }  
     cout <<endl << endl ; 
     system ("pause"); 
}


void FindUserScreen(){
    
    system("clear");
     cout <<"\n----------------------------------\n";
    cout << "          FIND USERS SCREEN    ";
    cout << "\n----------------------------------\n" ;     
}

void FindUser ( vector<sUser> vUser ){
       
     FindUserScreen();
     string name ;  
     cout <<"\n enter the of user to find : "; 
     getline (cin >> ws , name );
     
     if (FindUser(name , vUser)){
         cout <<"\n USER  : ";
         PrintUsers (name , vUser);                   
     }
     else {
         cout <<"\n sorry user not found ";
     }
     cout << endl << endl ; 
     system ("pause"); 
}

void ManegeActions( short answer , vector<sUser>& vUser ){
    
     switch (answer ){
      
          case eManegeMenu :: List :{
              ShowListUser(vUser); 
              break ; 
          }
          case eManegeMenu :: Add :{
              AddNewUsers( vUser );
              break ; 
          }
          case eManegeMenu :: Del :{
              DleteUsers (vUser); 
              break ; 
          }
          case eManegeMenu :: Update :{
              UpdateUsersInfo (vUser); 
              break ; 
          }
          case eManegeMenu :: mange_Find :{
              FindUser(vUser);
              break ; 
          }            
     }      
} 

void ManegeUsers (){
    
    short answer =0;     
    vector<sUser> vUser ;  
    do{
        
        vUser = LoadUsersFromFile (); 
        ManegeMenu(); 
        cout <<"\n enter a choice between [1 - 6] " ;
        cin >> answer ; 
        
        if ( answer != 0  ){
            ManegeActions( answer , vUser ) ; 
        } 
        
        
    }while ( answer != Main_Menu ); 
    
}

bool IsUserAuthorizedToAcces( long int perm , short status ){
    
     return((perm & status ) == status || perm == -1); 
} 

void App_On(vector<stClient>& vClients , stClient& client , string AccountNum){
    
    short answer = 0 ;
    sUser user  ;
    vector<sUser> vUser = LoadUsersFromFile (); 
    user = LoginMenu(vUser);
    do{
        
        vUser = LoadUsersFromFile ();
        if (answer == Exit ){
            user = LoginMenu(vUser);
        }
        
        PrintMenu();
         
            cout <<" enter a choice between (1-8): ";
            cin >> answer ; 

        switch ((enMenu)answer){
            
            case display:{
                
                if ( IsUserAuthorizedToAcces(user.perm , show_user ) ){
                DisplayClients(vClients );
                }
                else  InvalidAccess(); 
                
                break;                
            }
            case add :{
                
                if ( IsUserAuthorizedToAcces(user.perm , add_user )){ 
                AddClient(vClients, client);
                }
                else  InvalidAccess(); 
                break ;
            }
            case update :{
                
                if ( IsUserAuthorizedToAcces(user.perm , update_user ) ){
                UpdateClient(vClients);
                }
                else  InvalidAccess(); 
                
                 break ;             
            }
           case deleted :{
                   if ( IsUserAuthorizedToAcces(user.perm , del_user) ){
                   DeleteClient(vClients);
                   }
                   else  InvalidAccess(); 
                   
                   break ;   
           }
           case Find :{
               
               if ( IsUserAuthorizedToAcces(user.perm , Find_user )){
               FindClientFunction(AccountNum, vClients, client ) ;
               }
               else  InvalidAccess(); 
               
               break ;
           }
           case transaction:{
               
               if ( IsUserAuthorizedToAcces(user.perm , trans_user) ){                   
               ActionsMenu(vClients);
               }
               else  InvalidAccess(); 
               
               break ;                              
           }
           case manege :{
               
               if ( IsUserAuthorizedToAcces(user.perm ,  manege_user )){
                    ManegeUsers (  ) ; 
               }
               else InvalidAccess(); 
               break ;                
           }
           case Exit :{               
               break ;
           }                     
        }                       
    }while( true );      
}


int main (){
    
    vector<stClient> vClients ;
    stClient client ; 
    string AccountNum ;
        
    vClients = LoadClientFromFile( );
    App_On(vClients , client , AccountNum);
    EndScreen();  
    
    return 0;
}
