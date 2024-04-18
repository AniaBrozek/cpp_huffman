#include <string>
#include <iostream>
#include <vector>
#include <fstream>
using namespace std;
struct tab_vector{
    vector<char> chars;
    vector<unsigned int> numbers;
    vector<unsigned int> czy_pierwsza;
};
tab_vector erase_from_tab_vector (tab_vector a, unsigned int first){
    a.chars.erase(a.chars.begin()+first);
    a.numbers.erase(a.numbers.begin()+first);
    a.czy_pierwsza.erase(a.czy_pierwsza.begin()+first);
    return a;
}
tab_vector erase_from_tab_vector (tab_vector a, unsigned int first,unsigned int last){
    a.chars.erase(a.chars.begin()+first,a.chars.begin()+last);
    a.numbers.erase(a.numbers.begin()+first,a.numbers.begin()+last);
    a.czy_pierwsza.erase(a.czy_pierwsza.begin()+first,a.czy_pierwsza.begin()+last);
    return a;
}
tab_vector push_back_from_tab_vector (tab_vector a,char ch, unsigned int number,unsigned int czy){
    a.chars.push_back(ch);
    a.numbers.push_back(number);
    a.czy_pierwsza.push_back(czy);
    return a;
}
int main() {
    string sentence_copy_without_repetitions = "a";
    char choice;
    cout << "This is a program to coding sentences to Huffman's code" << endl;
    cout << "Do you want pull the sentence from the file or enter your own sentence?" << endl;
    cout << "If you want pull the sentence from the file enter P" << endl;
    cout << "If you want enter your own sentence enter E" << endl;
    cout << "->";
    cin >> choice;
    while (choice != 'p' && choice != 'P' && choice != 'e' && choice != 'E') {
        cout << "Your choice isn't P or E" << endl;
        cout << "If you want pull the sentence from the file enter P" << endl;
        cout << "If you want enter your own sentence enter E" << endl;
        cout << "->";
        cin >> choice;
    }
    if (choice == 'e' || choice == 'E') {
        cin.ignore();
        cout << "Now enter your own sentence:" << endl;
        cout << "->";
        getline(cin, sentence_copy_without_repetitions);
    }
    if (choice == 'P' || choice == 'p') {
        ifstream inFile("huffman_code_file.txt");
        getline(inFile, sentence_copy_without_repetitions);
    }
    const string sentence = sentence_copy_without_repetitions;
    for (unsigned int i = 0; i < sentence_copy_without_repetitions.size() - 1; i++) {
        for (unsigned int k = i + 1; k < sentence_copy_without_repetitions.size();) {
            if (sentence_copy_without_repetitions.at(k) == sentence_copy_without_repetitions.at(i)) {
                sentence_copy_without_repetitions.erase(sentence_copy_without_repetitions.begin() + k);
            } else { k++; }
        }
    }
    unsigned int b = 0;
    vector<unsigned int> frequency_tab;
    for (unsigned int i = 0; i < sentence_copy_without_repetitions.size(); i++) {
        for (unsigned int j = i; j < sentence.size(); j++) {
            if (sentence_copy_without_repetitions.at(i) == sentence.at(j)) {
                b++;
            }
        }
        frequency_tab.push_back(b);
        b = 0;
        // i przyporządkowała im liczbę występowania w zdaniu.
    }
    tab_vector chars_and_29;
    for (unsigned int i = sentence.size(); i > 0; --i) {
        for (unsigned int j = 0; j < sentence_copy_without_repetitions.size(); ++j) {
            if (i == frequency_tab[j]) {
                chars_and_29.numbers.push_back(frequency_tab.at(j));
                chars_and_29.chars.push_back(sentence_copy_without_repetitions.at(j));
            }
        }
    }
    for (unsigned int i = sentence_copy_without_repetitions.size(); i > 0; --i) {
        chars_and_29.czy_pierwsza.push_back(i);
    }
    unsigned int half_tree;
    vector<vector<bool>> huffman_code_key;
    for (int i = 0; i < sentence_copy_without_repetitions.size(); ++i) {
        huffman_code_key.push_back(vector<bool>{});
    }
    while (!chars_and_29.numbers.empty()) {
        unsigned int pierwsza=chars_and_29.czy_pierwsza.at(0);
        unsigned int counter_29=0;
        unsigned int counter = 0;
        int j=0;
        do {
            tab_vector vector1;
            bool prawa_lewa=true;
            if (chars_and_29.chars.size()==2){
                chars_and_29.chars.insert(chars_and_29.chars.begin()+1,29);
                chars_and_29.numbers.insert(chars_and_29.numbers.begin()+1,0);
                chars_and_29.czy_pierwsza.insert(chars_and_29.czy_pierwsza.begin()+1, 0);
            }
            else{
                if (chars_and_29.numbers.at(0) != 0) {
                    vector1= push_back_from_tab_vector(vector1,29,0,0);
                    counter=0;
                    j=0;
                }
                half_tree=0;
                for (int i = 0; i < chars_and_29.numbers.size(); ++i) {
                    if (chars_and_29.numbers.at(i)!=0){half_tree+=chars_and_29.numbers.at(i);}
                    else{break;}
                }
                if(half_tree%2){half_tree = (half_tree / 2)+1;} else{half_tree = (half_tree / 2);}
                if (chars_and_29.numbers.at(0) == 0) {
                    chars_and_29= erase_from_tab_vector(chars_and_29,0);}
                for (unsigned int i = 0; i < chars_and_29.numbers.size();i++) {
                    if (chars_and_29.numbers.at(i) == 0) { break; }
                    if (counter==0){
                        counter += chars_and_29.numbers.at(i);
                        vector1= push_back_from_tab_vector(vector1,chars_and_29.chars.at(i),chars_and_29.numbers.at(i),chars_and_29.czy_pierwsza.at(i));
                        chars_and_29= erase_from_tab_vector(chars_and_29,i-j);
                        i--;
                    }
                    else if ((counter + chars_and_29.numbers.at(i) <= half_tree)) {
                        counter += chars_and_29.numbers.at(i);
                        vector1= push_back_from_tab_vector(vector1,chars_and_29.chars.at(i),chars_and_29.numbers.at(i),chars_and_29.czy_pierwsza.at(i));
                        chars_and_29= erase_from_tab_vector(chars_and_29,i-j);
                        i--;
                    }
                    if (counter==half_tree){break;}
                }
                for (int i = 0; i < vector1.numbers.size(); ++i) {
                    chars_and_29= push_back_from_tab_vector(chars_and_29,vector1.chars.at(i),vector1.numbers.at(i),vector1.czy_pierwsza.at(i));
                    (!prawa_lewa) ? prawa_lewa = true : prawa_lewa = false;
                }
                while(chars_and_29.numbers.at(0)==0){
                    chars_and_29= erase_from_tab_vector(chars_and_29,0);
                }
                unsigned int licznik_pozostalych=0;
                for (int i = 0; i < chars_and_29.czy_pierwsza.size(); ++i) {
                    if(!chars_and_29.czy_pierwsza.at(i)){
                        licznik_pozostalych+=chars_and_29.numbers.at(i);
                    }else{break;}
                }
                if (licznik_pozostalych<=half_tree){
                    unsigned int licznik=0;
                    chars_and_29= push_back_from_tab_vector(chars_and_29,29,0,0);
                    while (chars_and_29.numbers.at(licznik)!=0){licznik++;}
                    for (int i = 0; i < licznik; ++i) {
                        chars_and_29= push_back_from_tab_vector(chars_and_29,chars_and_29.chars.at(0),chars_and_29.numbers.at(0),chars_and_29.czy_pierwsza.at(0));
                        chars_and_29= erase_from_tab_vector(chars_and_29,0);
                    }
                    chars_and_29= erase_from_tab_vector(chars_and_29,0);
                }
            }
        }while (chars_and_29.czy_pierwsza.at(0)!=pierwsza);
        bool zero_one = false;
        for (int i = 0; i < chars_and_29.numbers.size(); i++) {
            if (chars_and_29.chars.at(i) == 29) {
                (!zero_one) ? zero_one = true : zero_one = false;
                counter_29++;
            } else {
                for (int k = 0; k < sentence_copy_without_repetitions.size(); ++k) {
                    if (sentence_copy_without_repetitions.at(k) == chars_and_29.chars.at(i))
                        huffman_code_key.at(k).push_back(zero_one);
                }

            }
        }

        for (int i = 0; i < chars_and_29.numbers.size()-1;) {
            if (chars_and_29.chars.size() == 1) {
                chars_and_29.chars.clear();
                chars_and_29.numbers.clear();
                chars_and_29.czy_pierwsza.clear();
            }
            else if (chars_and_29.chars.at(chars_and_29.chars.size() - 2) == 29) {
                chars_and_29.chars.pop_back();
                chars_and_29.chars.pop_back();
                chars_and_29.numbers.pop_back();
                chars_and_29.numbers.pop_back();
                chars_and_29.czy_pierwsza.pop_back();
                chars_and_29.czy_pierwsza.pop_back();
                i=0;

            }
            else if (i == 0 && chars_and_29.chars.at(i + 1) == 29) {
                chars_and_29= erase_from_tab_vector(chars_and_29,i,i+2);}
            else if (chars_and_29.chars.at(i + 1) == 29 && chars_and_29.chars.at(i - 1) == 29) {
                chars_and_29= erase_from_tab_vector(chars_and_29,i-1,i+1);
                i--;
            } else { i++; }
        }
        if (chars_and_29.chars.size() == 1) {
            chars_and_29.chars.clear();
            chars_and_29.numbers.clear();
            chars_and_29.czy_pierwsza.clear();
        }
    }
/*for (int i = 0; i < huffman_code_key.size(); ++i) {
        cout<<sentence_copy_without_repetitions.at(i)<<": ";
        for (int k = 0; k < huffman_code_key.at(i).size(); ++k) {
            cout<<huffman_code_key.at(i).at(k);
        }cout<<endl;
    }// wyświetla po kolei kod huffmana*/
    vector<bool> huffman_code_sentence;
    for (char i : sentence) {
        for (int j = 0; j < sentence_copy_without_repetitions.size(); ++j) {
            if(i==sentence_copy_without_repetitions.at(j)){
                for (auto && k : huffman_code_key.at(j)) {
                    huffman_code_sentence.push_back(k);
                }

            }
        }
    }
    cout<<"Huffman's code:";
    for (auto && i : huffman_code_sentence) {
        cout<<(int)i;
    }
    long double compression_rate=(long double)huffman_code_sentence.size()/(sentence.size()*8);
    cout<<endl<<"Your compression rate is: "<<compression_rate*100<<"%"<<endl;
    cout<<"Koniec programu";
    cout<<"Do you want save yours Huffman's code?"<<endl;
    cout<<"WARNING! If you choose to save to file, everything that was in the file will be delate!"<<endl;
    cout<<"Enter y or n:"<<endl;
    cout<<"->";
    cin>>choice;
    while (choice!='y'&&choice!='Y'&&choice!='N'&&choice!='n'){
        system("cls");
        cout << "This isn't Y or N. Enter again" << endl;
        cout<<"Do you want save yours Huffman's code?"<<endl;
        cout<<"WARNING! If you choose to save to file, everything that was in the file will be delate!"<<endl;
        cout<<"Enter y or n:"<<endl;
        cout << "->";
        cin>>choice;
    }
    if (choice=='y'||choice=='Y') {
        fstream plik("huffman_code_exit.txt");
        plik.open("huffman_code_exit.txt", ios::out | ios::trunc);// plik zostanie wyczyszczony i wpisane zostaną nowe dane
        for (auto && i : huffman_code_sentence) {
            plik<<(int)i;
        }
    }

    return 0;

}