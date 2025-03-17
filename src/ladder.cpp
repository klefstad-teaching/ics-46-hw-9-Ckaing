#include "../src/ladder.h"
#include <stack>
#include <algorithm>


void error(string word1, string word2, string msg){
    cerr << "Error for words '" << word1 << "' to '" << word2 << "': " << msg << endl;
}

bool edit_distance_within(const std::string& str1, const std::string& str2, int d){
    size_t len1 = str1.length();
    size_t len2 = str2.length();

    if (str1 == str2) return true;

    if (abs(static_cast<int>(len1 - len2)) > 1) return false;

    if (len1 != len2){
        const string& shorter = (len1 < len2) ? str1 : str2;
        const string& longer = (len1 < len2) ? str2 : str1;
        size_t i = 0, j = 0;
        int differences = 0;
        while (i < shorter.length() && j < longer.length()){
            if (shorter[i] != longer[j]){
                if (++differences > 1) return false;
                j++;
            } else {
                i++;
                j++;
            }
        }
        if (j < longer.length()) differences += (longer.length() - j);
        return differences <= 1;
    }

    int differences = 0;
    for (size_t i = 0; i < len1; i++){
        if (str1[i] != str2[i]){
            if (++differences > 1) return false;
        }
    }
    return differences == 1;
}
bool is_adjacent(const string& word1, const string& word2){
    return edit_distance_within(word1, word2, 1);
}
vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list){
    string begin_lower = begin_word;
    string end_lower = end_word;
    transform(begin_lower.begin(), begin_lower.end(), begin_lower.begin(), ::tolower);
    transform(end_lower.begin(), end_lower.end(), end_lower.begin(), ::tolower);
    
    if (begin_word == end_word){
        error(begin_word, end_word, "Start and end words must be different");
        return vector<string>();
    }

    if (word_list.find(end_word) == word_list.end()){
        error(begin_word, end_word, "End word must be in dictionary");
        return vector<string>();
    }

    queue<vector<string>> ladder_queue;
    set<string> visited;

    ladder_queue.push({begin_word});
    visited.insert(begin_word);

    while (!ladder_queue.empty()) {
        vector<string> ladder = ladder_queue.front();
        ladder_queue.pop();

        string last_word = ladder.back();

        for (const string& word : word_list) {
            if (is_adjacent(last_word, word) && visited.find(word) == visited.end()) {
                visited.insert(word);
                vector<string> new_ladder = ladder;
                new_ladder.push_back(word);

                if (word == end_word) {
                    return new_ladder;
                }
                ladder_queue.push(new_ladder);
            }
        }
    }
    return vector<string>();

}
void load_words(set<string> & word_list, const string& file_name){
    ifstream file(file_name);
    if (!file){
        cerr << "Error: Could not open file " << file_name << endl;
        return;
    }
    string word;
    while (file >> word) {
        transform(word.begin(), word.end(), word.begin(), ::tolower);
        word_list.insert(word);
    }
    file.close();
}
void print_word_ladder(const vector<string>& ladder){
    if (ladder.empty()) {
        cout << "No ladder found.\n";
        return;
    }

    cout << "Word ladder found: ";
    for (size_t i = 0; i < ladder.size(); i++){
        cout << ladder[i];
        if (i < ladder.size() - 1) {
            cout << " ";
        }
    }
    cout << " \n";
}

void verify_word_ladder(){
    string begin_word, end_word;
    set<string> word_list;
    
    cout << "Enter start word: ";
    cin >> begin_word;
    cout << "Enter end word: ";
    cin >> end_word;
    
    load_words(word_list, "words.txt");
    vector<string> ladder = generate_word_ladder(begin_word, end_word, word_list);
    print_word_ladder(ladder);
}
