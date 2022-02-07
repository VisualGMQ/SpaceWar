#include "game/quick_list.hpp"

int main() {
    QuickList<int> list;
    list.Add(1);
    list.Add(3);
    list.Add(2);
    list.Add(5);

    list.PrintAll();

    list.RemoveAll([](const int& elem){
            return elem < 3;
     });

    list.PrintAll();

    list.RemoveAll([](const int& elem){
            return elem < 10;
    });

    list.PrintAll();
}

