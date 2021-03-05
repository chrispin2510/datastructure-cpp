#include "priority_queue.h"
#include <iostream>

int main()
{
    int prios[] = {19, 55, 44, 98, 67, 48, 95, 66, 70, 69, 30, 24, 99, 82};
    int num_prios = sizeof(prios) / sizeof(prios[0]);
    PriorityQueue<int> pq(num_prios + 1);
    for (int i = 0; i < num_prios; i++)
        pq.insert(prios[i]);
    for (int i = 1; i < pq.get_capacity(); i++) {
        int value = pq.delete_minimum();
        std::cout << value << std:: endl;
    }
    return 0;
}
