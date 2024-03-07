#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

std::vector<char> read_source(std::string&& file_path)
{
    std::ifstream file(file_path);
    std::vector<char> source;
//enter then into a vector
    char c;
    while (file.get(c)) {
        source.push_back(c);
    }
    return source;
}
//remove the comments/useless charecters
void filter_chars(std::vector<char>& source)
{   
    auto new_end = std::remove_if(source.begin(), source.end(),[](char c) { return !std::strchr("<>+-[],.", c); });
    source.erase(new_end, source.end());
}

//to write
//actual funtion to interpret 
int main(int argc,char* argv[]){
     if (argc > 1) {
        std::vector<char> source = read_source(argv[1]);
        filter_chars(source);
        interpret(source);
        return 0;
    }
}

