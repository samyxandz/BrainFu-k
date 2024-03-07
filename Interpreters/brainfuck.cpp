#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
 using namespace std;



vector<char> read_source( string&& file_path)
{
     ifstream file(file_path);
     vector<char> source;
//enter then into a vector
    char c;
    while (file.get(c)) {
        source.push_back(c);
    }
    return source;
}
//remove the comments/useless charecters
void filter_chars( vector<char>& source)
{   
    auto new_end =  remove_if(source.begin(), source.end(),[](char c) { return ! strchr("<>+-[],.", c); });
    source.erase(new_end, source.end());
}

//to write
//actual funtion to interpret 
void interpret( vector<char>& source){
    //memory
    vector<unsigned char> tape(30000, 0);
    int h = 0;  // the tape head

    int brace_count = 0;  // keeps track of nested braces

    int i = 0; 
    while (i < source.size()) {
        switch (source[i]) {
            case '<':
                --h;
                break;
            case '>':
                ++h;
                break;
            case '+':
                ++tape[h];
                break;
            case '-':
                --tape[h];
                break;
            case '.':
                cout << tape[h] <<flush;
                break;
            case ',':
               cin >> tape[h];
                break;

            case '[':

                if (tape[h] == 0) {
                    ++brace_count;
                    while (source[i] != ']' || brace_count != 0) {
                        ++i;
                        if (source[i] == '[') {
                            ++brace_count;
                        }
                        else if (source[i] == ']') {
                            --brace_count;
                        }
                    }
                }
                break;

            case ']':
                if (tape[h] != 0) {
                    ++brace_count;
                    while (source[i] != '[' || brace_count != 0) {
                        --i;
                        if (source[i] == ']') {
                            ++brace_count;
                        }
                        else if (source[i] == '[') {
                            --brace_count;
                        }
                    }
                }
                break;

        }
        ++i;
    }
}

int main(int argc,char* argv[]){

    if (argc != 1) {
        cout << "Expected a brainfuck source file as a command line argument.\n";
        cout << "Terminating the program." << endl;
        return 1;
    }

    // Normal operations.
    vector<char> source = read_source(argv[1]);
    filter_chars(source);
    interpret(source);
    return 0;
}

