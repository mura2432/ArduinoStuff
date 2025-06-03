#include<bits/stdc++.h>
uint64_t map_[] = {0};

// Get the xth bit in the yth index of the array
bool getBit(unsigned x, unsigned y){
    return !!(map_[y] & ((uint64_t) 1 << x));
}

// Set the xth bit in the yth index of the array to v
void setBit(unsigned x, unsigned y, bool v){
    uint64_t r = map_[y];
    r &= ~((uint64_t) 1 << x);

    r |= v << x;

    map_[y] = r;
}

void printBitVersion(){
    for(int i = 63; i >= 0; i--){
        std::cout<<(getBit(i, 0) ? '1' : '0');
    }
    std::cout<<('\n');
}

int main(){
    printBitVersion();
    std::cout<<(unsigned int) map_[0]<<'\n';
    setBit(0, 0, true);
    printBitVersion();
    std::cout<<(unsigned int) map_[0]<<'\n';
}