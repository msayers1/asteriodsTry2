#include <iostream>
#include <stdio.h>
#include <cmath>


int main(){
    float speed = 2;
    float angle = 0;

    float vx_ = speed * cosf(angle);
    float vy_ = speed * sinf(angle);
    std::cout << speed << " | " << angle << " | " << cosf(angle) << " | " << sinf(angle) << " | " << vx_ << " | " << vy_ << std::endl;
    printf("Here\n");
    for(int i = 0;  i < 8; i++){
        printf("Here\n");
        angle = angle + (M_PI/4);
        vx_ = speed * cosf(angle);
        vy_ = speed * sinf(angle);
        std::cout << speed << " | " << (angle * 180/M_PI) << " | " << angle << " | " << cosf(angle) << " | " << sinf(angle) << " | " << vx_ << " | " << vy_ << std::endl;
    }
    
    std::list<int> myList = {1};

    for(auto num : myList) {
        
    }


    return 0;   
}
