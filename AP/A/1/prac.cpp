// #include <iostream>
// #include <string>
// #include <vector>
// #include <regex>
// using namespace std;
// int main()
// {
//     // vector<string> note;
//     // printf("%lu\n",sizeof "a");
//     // printf("%lu\n",strlen("a"));

//     // vector <string> names;
//     // names.push_back("ali");
//     // names.push_back("a");
//     // names.push_back("kakakakaak");
//     // names.push_back("reza");
//     // string line;
//     // while (getline(cin, line))
//     // {
//     //     if (line.find(" start_day ")!= string::npos)
//     //     {
//     //     }
//     //     else
//     //     {
//     //         note.push_back(line);
//     //     }
//     // }

//     // for (string x : note)
//     // {
//     //     cout << x << '\n';
//     // }



//     // string note;
//     // string word;
//     // cin >> note;
//     // char c = getchar();
//     // note+=c;
//     // cin >> word;
//     // note+=word;
//     // c = getchar();
//     // note+=c;
//     // cin>>word;
//     // note+=word;
//     // cout<<note;

//     if ('/' - '0' >'/' - '0'){
//         int c = '2' - '0';
//         cout <<c;
//     }
//     string name = "i am one_hundred_percent un happy c ";
//     char b = '\b';
//     string n = "\b";
//     n+= "happy";
//     n+=b;
//     if(name.find("\\bhappy\\b")!= string::npos){
//         cout << "yes";
//     }
//     else{
//         cout <<"no";
//     }
    
//     string text = "This is a sample string";
//     regex word_regex("\\bsample\\b"); // \b is used as a boundary to match the exact word "sample" 

//     return 0;
// }

#include <iostream>
#include <regex>
#include<string>
 using namespace std;
 int countMatchInRegex(std::string s, std::string re);
int main()
{
    string text = "i am one_hundred percent happy unharppy happy happyi";
    string note = "\\b";
    note+= "happy";
    note+="\\b";

    //regex word_regex(note); // \b is used as a boundary to match the exact word "sample" 
    // if (text.find(note.text)!= string :: npos) {
    //     cout << "found\n";
    // } else {
    //     cout << "not found\n";
    // }
    // cout << text;
    regex word_regex(note); // \b is used as a boundary to match the exact word "sample" 
    // int cnt = len(re.findall(note,text));
    int cnt = countMatchInRegex(text,note);
    cout << cnt << '\n';
    if (regex_search(text, word_regex)) {
        cout << "found\n";
    } else {
        cout << "not found\n";
    }
    cout << text;
return 0;
}
    int countMatchInRegex(string s, string re)
{
    regex words_regex(re);
    auto words_begin = sregex_iterator(s.begin(), s.end(), words_regex);
    auto words_end = sregex_iterator();

    return distance(words_begin, words_end);
}
int count_positive_words(string line, vector <string> positive_words){
    int cnt_pwords = 0;
    for(string word: positive_words){
        cnt_pwords += countMatchInRegex(line, word);
    }
    return cnt_pwords;
}

