#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include<vector>
#include<algorithm>

using namespace std;

int main() {
    ifstream file("sample.txt");
    if (!file) {
        cout << "File not found!" << endl;
        return 0;
    }

    unordered_map<string, int> wordCount;
    unordered_map<string, vector<int>> wordLines;

    string line;
    int lineNumber = 0;


    // 1. Process the file (Keep this outside the loop)
    while (getline(file, line)) {
    lineNumber++;   // ✅ line count starts from 1

    for (char &c : line) c = tolower(c);
    for (char &c : line)
        if (!isalpha(c) && c != ' ')
            c = ' ';

    stringstream ss(line);
    string word;

    while (ss >> word) {
        wordCount[word]++;
        wordLines[word].push_back(lineNumber); // ✅ correct place
    }
}

    file.close();
    // 2. The Loop
    int choice;
           string query;

do {
        cout << "1. Search a word\n";
        cout << "2. Show all word frequencies\n";
        cout << "3. Show top 5 frequent words\n";
        cout << "4. Exit\n";

    cout << "Enter your choice: ";
    cin >> choice;

    switch(choice)
    {
    case 1:
 
        cout << "Enter word to search: ";
        cin >> query;

        for (char &c : query)
            c = tolower(c);

       if (wordCount.find(query) != wordCount.end()) {
    cout << query << " appears "
         << wordCount[query] << " times.\n";

    cout << "Found in lines: ";
    for (int ln : wordLines[query]) {
        cout << ln << " ";
    }
    cout << endl;
} else {
    cout << query << " does not appear in the text.\n";
}

        break;
     case 2:
        cout << "\nWord Frequencies:\n";
        for (auto &p : wordCount) {
            cout << p.first << " : " << p.second << endl;
        }
    
      break;
   
      case 3: {
    vector<pair<string, int>> freqList(wordCount.begin(), wordCount.end());

    sort(freqList.begin(), freqList.end(),
         [](const pair<string,int>& a, const pair<string,int>& b) {
             return a.second > b.second;  // descending order
         });

    cout << "\nTop 5 most frequent words:\n";
    for (int i = 0; i < 5 && i < freqList.size(); i++) {
        cout << freqList[i].first << " : " << freqList[i].second << endl;
    }
    break;
}

      case 4:
      cout<<"the program is terminated\n";
      break;
     default: 
        cout << "Invalid choice! Try again.\n";
    }

} while (choice != 4);
    return 0;
}

