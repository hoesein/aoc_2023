#include "common.h"

int main()
{
    std::priority_queue<int> pq;
    
    pq.push(30);
    pq.push(100);
    pq.push(25);
    pq.push(40);

    while(!pq.empty())
    {
        std::cout << pq.top() << std::endl;
        pq.pop();
    }
    
    std::cout << "---- Min Heap ----" << std::endl;

    std::priority_queue<int, std::vector<int>, std::greater<int>> min_pq;
    
    min_pq.push(30);
    min_pq.push(100);
    min_pq.push(25);
    min_pq.push(40);

    while(!min_pq.empty())
    {
        std::cout << min_pq.top() << std::endl;
        min_pq.pop();
    }

    std::cout << "---- Map with tuple key ----" << std::endl;

    std::map<std::tuple<int, int, int>, int> test_map_tuple;
    test_map_tuple[{1,2,3}] = 100;
    test_map_tuple[{4,5,6}] = 200;
    test_map_tuple[{1,2,4}] = 300;

    if(test_map_tuple.count({1,2,3}))
    {
        std::cout << test_map_tuple[{1,2,3}] << std::endl;
    }

    std::cout << "---- Vector with pair ----" << std::endl;
    std::vector<std::pair<int, int>> vec_pair = {{1,2}, {3,4}, {5,6}};
    std::cout << vec_pair[0].first << ", " << vec_pair[0].second << std::endl;
    
    return 0;
}