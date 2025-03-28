#ifndef SUBJECT_H
#define SUBJECT_H
#include <vector>
#include "observer.h"
using namespace std;

class Subject {
    vector<Observer*> observers;

    public:
        Subject();

        void attach(Observer *ob) {
            observers.emplace_back(ob);
        }

	    void detach(Observer *ob) {
            for (auto p : observers) {
                if (*p == ob) {
                    observers.erase(p);
                    break;
                }
            }
        }

	    void notifyObserver() {
		    for (auto &ob: observers) {
                ob->notify();
            }
        }

	    virtual ~Subject() = 0;
};

#endif