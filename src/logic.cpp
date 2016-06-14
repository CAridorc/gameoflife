#include "logic.h"

#include <cstdio>
#include <unordered_map>

Gamestate::Gamestate() :
	paused(true),
	generation(0) {}

void Gamestate::update() {
	if (paused) {
		return;
	}
	std::unordered_map<Cell, int, Hash> num_neighbours;
	// Count neighbours of each cell
	for (Cell c : board) {
		for (Cell n : c.get_neighbours()) {
			if (!num_neighbours.count(n)) {
				num_neighbours.emplace(n, 0);
			}
			++num_neighbours[n];    // Note each cell counts itself as a neighbour
		}
	}
	// Apply the iteration rule
	for (auto pair : num_neighbours) {
		Cell c;
		int n;
		std::tie(c, n) = pair;
		if (n == 3) {    // i.e. c is live and has 2 neighbours or is dead and has 3
			board.insert(c);
		} else if (board.count(c) and n != 4) {
			board.erase(c);
		}
	}
	++generation;
	printf("Generation: %d, Total cells: %lu\n", generation, board.size());
}

bool Cell::operator==(const Cell& other) const {
	return (x == other.x) and (y == other.y);
}

std::vector<Cell> Cell::get_neighbours() const {
	std::vector<Cell> neighbours;
	for (int dx = -1; dx <= 1; ++dx) {
		for (int dy = -1; dy <= 1; ++dy) {
			neighbours.push_back({x + dx, y + dy});
		}
	}
	return neighbours;
}

std::size_t Hash::operator()(const Cell& c) const {
	return c.x * 31 + c.y;
}
