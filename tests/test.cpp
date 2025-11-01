#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
using namespace std;

// template<typename T> // This must be in the header file.
// T roll(T dice) {
//     int i = 0;
//     int total = 0;
//     int bag[] = { dice... };
//     for (int roll : bag) {
//         total += rand() % roll;
//         i ++;
//     }
//     return total/i;
// }



// int main() {
//     srand(static_cast<unsigned int>(time(0))); // Seed the random number generator
//     cout << "Hello World!\n";
//     int a = 20;
//     int b = 6;
//     int c = 12;
//     cout << roll(1) << endl;
// }



// template <typename... Dice>
// int roll(Dice... dice) {
//     int rolls[] = { dice... };
//     int total = 0;
//     int count = sizeof...(dice);

//     for (int sides : rolls) {
//         total += rand() % sides + 1; // +1 to simulate dice roll from 1 to sides
//     }

//     return total / count;
// }

// int main() {
//     srand(static_cast<unsigned int>(time(0)));

//     int a = 20;
//     int b = 6;
//     int c = 12;

//     cout << "Average roll: " << roll(a, b, c, b, a) << endl;
//     return 0;
// }



// template<typename T>
// T Sum(T arg){
//     return arg;
// }
// template<typename T,typename... Args>
// T Sum(T arg, Args... args){
//     return arg + Sum(args...);
// }

// int main(){
//     cout << Sum(1,2,3,4) << endl;
// }
int main(){
    std::vector<int> vec(5);
    vec.at(5) = 90;
    int i;
    for(i=0; i < vec.size(); i++){
        cout << vec.at(i) << endl;
    }
    
}
    