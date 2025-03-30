#ifndef OBSERVER_H
#define OBSERVER_H

class Observer {
    public:
        virtual void notify(int position) = 0;
        virtual ~Observer() = default;
};

#endif