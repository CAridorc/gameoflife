#ifndef _logic_h_included_
#define _logic_h_included_

#include <unordered_set>
#include <vector>

struct Cell {
	int x, y;

	bool operator==(const Cell&) const;
	std::vector<Cell> get_neighbours() const;
};

struct Hash {
	std::size_t operator()(const Cell&) const;
};

class Gamestate {
public:
	Gamestate();

	std::unordered_set<Cell, Hash> board;    // The set of live cells
	bool paused;
	int generation;

	void update();
};

#endif
