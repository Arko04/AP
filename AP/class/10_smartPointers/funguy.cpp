#include <iostream>
#include <string>
#include <memory>
using namespace std;

class FunGuy {
public:
    FunGuy(string name_) : name(name_) {
        cout << "Hi " << name << endl;
    }
    ~FunGuy() {
        cout << "Bye " << name << endl;
    }
    void introduce_youself() {
        cout << "I'm " << name << ", the fun guy!" << endl;
    }
private:
    string name;
};

void make_fun_0() {
    FunGuy* bob = new FunGuy("Bob");

    bob->introduce_youself();

//    if (something_happens)
//        return;     // memory leak

    delete bob;
}








void make_fun_1() {
    unique_ptr<FunGuy> bob(new FunGuy("Bob"));

    bob->introduce_youself();

    // No need to delete
}

void make_fun_2() {

    unique_ptr<FunGuy> bob = make_unique<FunGuy>("Bob");


    // no need to delete
}











void make_fun_3() {
    unique_ptr<FunGuy> bob = make_unique<FunGuy>("Bob");
    bob->introduce_youself();


   // unique_ptr<FunGuy> another_bob = bob;   // compile error: unique pointers cannot be copied


}








void make_fun_4() {
    unique_ptr<FunGuy> bob = make_unique<FunGuy>("Bob");
    {
        bob->introduce_youself();
        unique_ptr<FunGuy> another_bob;
        another_bob = std::move(bob);
    }   // another_bob goes outside scope
    bob->introduce_youself();
    cout << "The end!" << endl;
}






unique_ptr<FunGuy> make_fun_guy(string name) {
    unique_ptr<FunGuy> p = make_unique<FunGuy>(name);
    p->introduce_youself();
    return p;
}





void make_fun_5() {
    shared_ptr<FunGuy> another_bob;
    {
        shared_ptr<FunGuy> bob = make_shared<FunGuy>("Bob");
        bob->introduce_youself();
        another_bob = bob;
        bob->introduce_youself();
    }   // bob will go outside scope
    another_bob->introduce_youself();
}

int main() {
    make_fun_4();
}
