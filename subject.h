#ifndef SUBJECT_H
#define SUBJECT_H
#include <vector>
#include "observer.h"
using namespace std;

class Subject {
    vector<Observer*> observers;

    public:
        Subject() = default;

        void attach(Observer *ob) {
            observers.emplace_back(ob);
        }

	    void detach(Observer *ob) {
            for (auto it = observers.begin(); it != observers.end(); ++it) {
                if (*it == ob) {
                    observers.erase(it);
                    break;
                }
            }
        }

	    void notifyObservers(int position, int temp) {
		    for (auto &ob: observers) {
                ob->notify(position, temp);
                cout << "notified" << endl;
            }
        }

	    virtual ~Subject() = default;
};

#endif