//
// Created by mjrsk on 10/3/2021.
//

#ifndef TEENSY_SYNTH_NOTIFICATION_RECEIVER_H
#define TEENSY_SYNTH_NOTIFICATION_RECEIVER_H

class NotificationReceiver {
public:
    virtual void notify() = 0;
private:
    void (*_cb)();
};

#endif //TEENSY_SYNTH_NOTIFICATION_RECEIVER_H
