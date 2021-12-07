#include <iostream>
#include <fstream>
#include<ctime>
#include<vector>
#include<string>
#include <string.h>
using namespace std;
int show_menu();
void run_game(string str);
class Words{
    int minlen;
    int maxlen;
    int count;
    string *choices;
    int count_candidates();
    void load_words();
    public:
    Words(int min,int max){
        minlen=min;
        maxlen=max;
        count = count_candidates();
        load_words();
    }
    ~Words(){
        delete [] choices;
    }
    string pick_word();
    void reset(int min, int max);
    
};
void Words::reset(int min, int max){
    minlen=min;
    maxlen=max;
    if(choices!=NULL){
        delete [] choices;
    }
    count=count_candidates();
    load_words();
}
string Words::pick_word(){
    if(count==0){
        return "";
    }else{
        int random = rand() % count + 0;
        return choices[random];
    }
}
void Words::load_words(){
    choices=new string[count];
    int i=0;
    fstream newfile;
   newfile.open("enable1.txt",ios::in); 
   if (newfile.is_open()){ 
      string tp;
      while(getline(newfile, tp)){ 
        int len =tp.length();
        if(len>minlen && len<maxlen){
            choices[i++]=tp;
        }
      }
      newfile.close();
   }

}
int Words::count_candidates(){
    vector <string> v;
    int count=0;
    fstream newfile;
   newfile.open("enable1.txt",ios::in); 
   if (newfile.is_open()){ 
      string tp;
      while(getline(newfile, tp)){ 
        int len =tp.length();
        if(len>minlen && len<maxlen){
            count++;
        }
      }
      newfile.close();
   }
    return count;
}

class Hangman{
    char word[40], progress[40];
    int word_length;
    void clear_progress(int length);
    protected:
    int matches,wrong_guesses,remaining;
    char last_guess;
    string chars_guessed;
    bool check(char user_guess);
    public:
    void initialize(string start);
    Hangman(string str){
        initialize(str);
    }
    char * get_progress();
    char * get_word();
    int get_remaining();
    bool is_word_complete();
};
bool Hangman::check(char user_guess){
    int i;
    int count=0;
    for(i=0;i<word_length;i++){
        if(word[i]==user_guess){
            progress[i]=user_guess;
            matches++;
            count++;
        }
    }
    
    if(count>0) return true;
    if(chars_guessed.find(user_guess)<chars_guessed.length()){ 
        //found
    } else {
        wrong_guesses+=1;
        remaining-=1;
        chars_guessed+=user_guess;
    }
    return false;
};
bool Hangman::is_word_complete(){
    int val = strcmp(progress,word);
    if(val==0){
        return true;
    }
    return false;
}
char * Hangman::get_progress(){
    return progress;
}
char * Hangman::get_word(){
    return word;
}
int Hangman::get_remaining(){
    return remaining;
}
void Hangman::initialize(string start){
    chars_guessed="";
    wrong_guesses=0;
    matches=0;
    remaining=6;
    strcpy(word,start.c_str());
    word_length=start.length();
    clear_progress(start.length());
}   
void Hangman::clear_progress(int length){
    int i;
    for(i=0;i<length;i++){
        progress[i]='-';
    }
    progress[i]='\0';
}

class HangmanConsole : public Hangman{
    string start;
    public:
    HangmanConsole(string start): Hangman(start){
    }
    void show_status(int stage);
    void show_info();
    friend void operator>>(istream& is, HangmanConsole& hc)
    {
        char c;
        is>> c;
        hc.check(c);
    }
};
void HangmanConsole::show_info(){
    char * prog = get_progress();
    int ct=0;
    while(*prog!='\0'){
        if(*prog!='-') ct++;
        prog++;
    }
    show_status(ct);
    cout<<"Matches last guessed: "<<matches<<endl;
    cout<<"Wrong Guesses: "<<wrong_guesses<<endl;
    cout<<"Attempt remaining: "<<remaining<<endl;
    cout<<"Letters Guessed: "<<chars_guessed<<endl;
}
void HangmanConsole::show_status(int stage){
    switch (stage){
    case 0:
        cout << " +-----\n";
        cout << " |     \n";
        cout << " |     \n";
        cout << " |     \n";
        cout << " |     \n";
        cout << " ----- \n";
        break;
    case 1:
        cout << " +-----\n";
        cout << " |  O  \n";
        cout << " |     \n";
        cout << " |     \n";
        cout << " |     \n";
        cout << " ----- \n";
        break;
    case 2:
        cout << " +-----\n";
        cout << " |  O  \n";
        cout << " |  |  \n";
        cout << " |     \n";
        cout << " |     \n";
        cout << " ----- \n";
        break;
    case 3:
        cout << " +-----\n";
        cout << " |  O  \n";
        cout << " | /|\\\n";
        cout << " |     \n";
        cout << " |     \n";
        cout << " ----- \n";
        break;
    case 4:
        cout << " +-----\n";
        cout << " |  O  \n";
        cout << " | /|\\\n";
        cout << " |  |  \n";
        cout << " |     \n";
        cout << " ----- \n";
        break;
    case 5:
        cout << " +-----\n";
        cout << " |  O  \n";
        cout << " | /|\\\n";
        cout << " |  |  \n";
        cout << " | /   \n";
        cout << " ----- \n";
        break;
    case 6: 
        cout << " +-----\n"; 
        cout << " |  O  \n"; 
        cout << " | /|\\ \n";
        cout << " |  |   \n"; 
        cout << " | / \\ \n"; 
        cout << " ----- \n"; 
        break; 
    }

}
int show_menu(){
    int n;
    cout<<"1. Play the computer (auto select random range)"<<endl;
    cout<<"2. Play the computer (min: 7, max: 12)"<<endl;
    cout<<"3. Play the computer (user selects/changes range)"<<endl;
    cout<<"4. Play the computer (use same range stored in 3)"<<endl;
    cout<<"5. Two player mode (user1 enters the word, user2 guesses)"<<endl;
    cout<<"6. Quit"<<endl;
    cout<<"Enter choice: ";
    cin>>n;
    return n;
}
void get_range_num(string prompt, int min, int max, int & number){
    int num;
    cout<<prompt<<endl;
    cin>>num;
    while(num<min || num>max){
        cout<<prompt<<endl;
        cin>>num;
    }
    number=num;

}

int main(){
    srand(time(NULL)); 
    Words word(3, 13);
    string str;
    int flag=0;
    int num=1,min,max;
    while(num){
        num=show_menu();
        switch (num)
        {
        case 1:
            min = rand() % (40 - 2 + 1) + 2;
            max = rand() % (40 - 2 + 1) + 2;
            while(max<min){
                min = rand() % (40 - 2 + 1) + 2;
                max = rand() % (40 - 2 + 1) + 2;
            }
            word.reset(min,max);
            cout << word.pick_word() << endl;
            break;
        case 2:
            min=7,max=12;
            word.reset(min,max);
            cout << word.pick_word() << endl;
            break;
        case 3:
            get_range_num("Enter min: ", 2, 40, min);
            get_range_num("Enter max: ", min, 40, max);
            flag=1;
            word.reset(min,max);
            cout << word.pick_word() << endl;
            break;
        case 4:
            if(flag==1)cout<<word.pick_word() << endl;
            else {
                get_range_num("Enter min: ", 2, 40, min);
                get_range_num("Enter max: ", min, 40, max);
                word.reset(min,max);
                cout << word.pick_word() << endl;
            }
            break;
        case 5:
            cout<<"Player 1 Enter the Word: ";
            cin>>str;
            system("clear");
            run_game(str);
            break;
        case 6:
            exit(0);
            break;
        default:
            cout<<"Enter Valid Input"<<endl;
            break;
        }
    }
    return 0;
}

void run_game(string str){
    HangmanConsole game(str);
    cout << "HANGMAN" << endl << "-------" << endl << endl;
    cout << "Your word is: " << game.get_progress() << endl;

    while (!game.is_word_complete() && game.get_remaining() > 0)
    {
    cout << endl;
    cout << "Enter your guess: ";
    cin >> game;    

    system("clear");
    game.show_info();
    }
}

// int main()
// {
//     srand(time(NULL)); 
//     Words words(7,10); 
  
//     HangmanConsole game(words.pick_word());  

//     cout << "HANGMAN" << endl << "-------" << endl << endl;
//     cout << "Your word is: " << game.get_progress() << endl;

//     while (!game.is_word_complete() && game.get_remaining() > 0)
//     {
//        cout << endl;
//        cout << "Enter your guess: ";
//        cin >> game;    

//        system("clear");
//        game.show_info();
//     }

//     return 0;
// }






// int main(){
//     srand(time(NULL)); 
//     int min, max;

//     cout << "Enter min: ";
//     cin >> min;

//     cout << "Enter max; ";
//     cin >> max;

//     Words words(min, max);

//     cout << words.pick_word() << endl;
//     return 0;
// }