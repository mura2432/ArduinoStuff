#include<bits/stdc++.h>
uint64_t map_[] = {0};

// Get the xth bit in the yth index of the array
bool getBit(unsigned x, unsigned y){
    return !!(map_[y] & (1 << x));
}

// Set the xth bit in the yth index of the array to v
void setBit(unsigned x, unsigned y, bool v){
    uint64_t r = map_[y];
    r &= ~(1 << x);

    r |= v << x;

    map_[y] = r;
}

int main(){
    std::cout<<(unsigned int)map_[0]<<'\n';
    setBit(16, 0, true);
    std::cout<<(unsigned int)map_[0]<<'\n';
}