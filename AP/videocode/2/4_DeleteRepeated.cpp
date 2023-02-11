#include <iostream>
#include <string>
using namespace std;
int main()
{
    string previous = "";
    string current;
    while (cin >> current)
    {
        if (previous == current)
            cout << "repeated word: " << current << '\n';
        previous = current;
    }
    cerr << "some errors!\n";
}

// ./a.out < input.txt > output.txt 2>errors.txt
// cerr is for errors.txt and shows the error massages

// ./a.out < input.txt | sort
// used for sorting the output

// press control + d to terminate