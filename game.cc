#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "game.h"
using namespace std;

Game(vector<Player> players, vector<shared_ptr<Player>> currPlayer) : players{players}, currPlayer{currPlayer} {}

Game::AddPlayer
