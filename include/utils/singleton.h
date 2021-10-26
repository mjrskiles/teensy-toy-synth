//
// Created by mjrsk on 10/25/2021.
//

#ifndef TEENSY_SYNTH_SINGLETON_H
#define TEENSY_SYNTH_SINGLETON_H

class Singleton {
public:
    static Singleton& getInstance() {
        static Singleton instance;
        return instance;
    }
private:
    Singleton() {}
    Singleton(Singleton const&); // Don't Implement.
    void operator=(Singleton const&); // Don't implement
};

#endif //TEENSY_SYNTH_SINGLETON_H
