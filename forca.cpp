#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <ctime>
#include <cstdlib>
using namespace std;

string secret_word;
map<char, bool> tried;
vector<char> failed_attempts;

bool letter_exists(char attempt) {
    for(char letter : secret_word) {
      if(attempt == letter) {
        return true;
      } 
    }
    return false;
}

bool not_hanged() {
    return failed_attempts.size() < 5;
}

bool not_r() {
    for(char letter : secret_word) {
      if(!tried[letter]) {
        return true;
      }
    }
    return false;
}

void header() {
    cout << "Jogo da Forca" << endl;
     cout << endl;
}

void errors() {
    cout << "Chutes errados: ";
    for(char letter : failed_attempts) {
        cout << letter << " ";
    }
    cout << endl;
}

void show_word() {
    for(char letter : secret_word) {
        if(tried[letter]) {
          cout << letter << " ";
      } 
      else {
        cout << "_ ";
      }
    }
    cout << endl;
}

void try_p() {
    cout << "Seu chute: " << endl;
    char attempt;
    cin >> attempt;

    tried[attempt] = true;

    if (letter_exists(attempt)) {
      cout << "Você acertou! Seu chute está na palavra." << endl;
    }
    else {
      cout << "Você errou! Seu chute não está na palavra." << endl;
      failed_attempts.push_back(attempt);
      if(!not_hanged()) {
        cout << "Fim de jogo!" << endl;
      }
    }
}

vector<string> read_file() {
    ifstream file;
    file.open("palavras.txt");

    if(file.is_open()) {
        int number_of_words;
        file >> number_of_words;

        vector<string> file_words;

        for(int i = 0; i < number_of_words; i++) {
            string read_word;
            file >> read_word;
            file_words.push_back(read_word);
        }
        file.close();
        return file_words;
    }
    else {
        cout << "Não foi possível acessar o banco de palavras." << endl;
        exit(0);
    }
}

void draw_word() {
    vector<string> words = read_file();

    srand(time(NULL));
    int index_drawn = rand() % words.size();

    secret_word = words[index_drawn];
}

void save_file(vector<string> new_list) {
    ofstream file;
    file.open("palavras.txt");
    if(file.is_open()) {
        file << new_list.size() << endl;

        for(string word : new_list) {
            file << word << endl;
        }
        file.close();
    }
    else {
      cout << "Não foi possível acessar o banco de palavras." << endl;
      exit(0);
    }                                          
}

void add_word() {
    cout << "Digite a nova palavra." << endl;
    string new_word;
    cin >> new_word;

    vector<string> list_words = read_file();
    list_words.push_back(new_word);

    save_file(list_words);
}

int main() {
    read_file();
    header();
    draw_word();

    while(not_r() && not_hanged()) {
        errors();
        show_word();
        try_p();
  
    }
      cout << endl;
      cout << "A palavra secreta era: " << secret_word << endl;
      if(not_r()) {
        cout << "Você perdeu! Tente novamente." << endl;
      }
      else {
        cout << "Você acertou a palavra secreta!" << endl;
        cout << "Você deseja adicionar uma nova palavra ao banco? (S/N) ";
        char response;
        cin >> response;
        if(response == 'S') {
            add_word();
        }
      }
}