//
//  main.cpp
//  CS32 Polymorphism Challenge
//
//  Created by Lucas Xia on 1/30/19.
//  Copyright © 2019 Lucas Xia. All rights reserved.
//

#include <iostream>
#include <string>
using namespace std;

class Diary {
public:
    Diary(string name) {
        this->name = name;
        this->entry = "";
    }
    virtual ~Diary() {
        
    }
    string getTitle() {
        return name;
    }
    void writeEntry(string entry) {
        this->entry += entry;
    }
    string read() {
        return entry;
    }
private:
    string name, entry;
};

class SecretDiary: public Diary {
public:
    SecretDiary(): Diary("TOP-SECRET") {
        
    }
    virtual ~SecretDiary() {
        
    }
    
};

int main() {

    return 0;
}
