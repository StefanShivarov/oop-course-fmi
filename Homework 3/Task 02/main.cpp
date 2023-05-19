#include <iostream>
#include "PriorityQueue.hpp"

int main()
{
    
    PriorityQueue<char> pq(4);

    pq.push('A', 0);
    pq.push('B', 3);
    pq.push('C', 2);
    pq.push('D', 2);
    pq.push('E', 1);

    try {
        pq.push('F', 5); // error
    }
    catch (std::logic_error e) {
        std::cout << e.what() << std::endl;
    }

    std::cout << pq.peek() << std::endl; //B
    pq.pop();
    std::cout << pq.peek() << std::endl; //C
    pq.pop();
    std::cout << pq.peek() << std::endl; //D
    pq.pop();
    std::cout << pq.peek() << std::endl; //E
    pq.pop();
    std::cout << pq.peek() << std::endl; //A
    pq.pop();
}