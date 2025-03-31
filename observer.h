#ifndef OBSERVER_H
#define OBSERVER_H

class Observer {
    public:
        virtual void notify(int position, int temp, int a, int b, char c) = 0;
        virtual ~Observer() = default;
};

#endif
