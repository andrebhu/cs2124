//Andre Hu abh471@nyu.edu
//hw01 for CS2124
//Decrypts encrypted caesar cipher

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

char caesar_shift_char(char, int);
void caesar_shift_string(string&, int);

int main(){
    //open encrypted.txt
    ifstream encrypted("encrypted.txt");
    if (!encrypted){
        cerr << "failed to open encrypted.txt";
        exit(1);
    }

    //read first int
    int shift;
    encrypted >> shift;
    shift *= -1; //decrypting

    //read file lines into vector lines
    string line;
    vector<string> lines;
    while (getline(encrypted, line)){
        lines.push_back(line);
    }
    encrypted.close();

    //modify lines and print backwards
    for (size_t i = lines.size() - 1; i > 0; --i){
        caesar_shift_string(lines[i], shift);
        cout << lines[i] << endl;
    }
    return 0;
}


//applies caesar cipher to char
char caesar_shift_char(char c, int shift){

    //checks if lowercase letter, if not returns input char
    int ascii_c = int(c);
    if (ascii_c < 97 || ascii_c > 122){
        return c;
    }

    //calculates ascii value
    int calculated_value = ascii_c + shift;

    //applies shift if goes past 122 'z' or behind 97 'a'
    if (calculated_value > 122){
        calculated_value -= 26;
    }
    else if (calculated_value < 97){
        calculated_value += 26;
    }
    
    //converts int to char
    char r = calculated_value;
    return r;
}

//applies caesar cipher to string
void caesar_shift_string(string& str, int shift){

    //loops through string and modifies char
    for(size_t i = 0; i < str.size(); i++){
        str[i] = caesar_shift_char(str[i], shift);
    }
}