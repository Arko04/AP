#include <iostream>
using namespace std;
int main()
{
    string name;
    cout << "Plaese enter your name: ";
    cin >> name;
    if (name == "Toby")
    {
        cerr << "You're a waste of life, and you should give up.\n";
        return 1;
    }
    cout << "Hello " << name << "\n";
    return 0;
}

/*In order to fix this problem, you will need to change the permissions of the .sh file. 
To do this, open Terminal and type in the following command:

chmod +x <filename>.sh

This will give the file executable permissions. You should now be able to run the .sh file in command line.
*/