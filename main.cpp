#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    int x, k, p;
    std::cin >> x >> k >> p;
    
    // Create a vector to track seat usage for each segment
    std::vector<int> seats(x, 0);
    
    for (int i = 0; i < p; i++) {
        int u, v, n;
        std::cin >> u >> v >> n;
        
        // Convert to 0-based indexing
        u--; v--;
        
        // Check if we can allocate n seats for this journey
        bool can_allocate = true;
        for (int j = u; j < v; j++) {
            if (seats[j] + n > k) {
                can_allocate = false;
                break;
            }
        }
        
        // If we can allocate, update the seat counts
        if (can_allocate) {
            for (int j = u; j < v; j++) {
                seats[j] += n;
            }
            std::cout << "T\n";
        } else {
            std::cout << "N\n";
        }
    }
    
    return 0;
}