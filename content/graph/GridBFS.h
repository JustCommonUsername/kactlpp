/**
 * Author: folklore, written for readability
 * Date: 2026-11-17
 * License: CC0
 * Source: folklore
 * Description: BFS on a grid of characters, \texttt{'\#'} = wall.
 * For multi-source BFS push all sources with distance 0 (e.g. "distance to the
 * nearest fire"). For diagonal moves use all 8 directions. Counting
 * components (flood fill): run it from every unvisited free cell.
 * Usage: auto d = grid_bfs(grid, {{sr, sc}}); // d[r][c] = -1 if unreachable
 * Time: O(R C)
 */
#pragma once

const ll dr[] = {-1, 1, 0, 0}, dc[] = {0, 0, -1, 1}; // up down left right

vector<vi> grid_bfs(vector<string>& grid, vector<ii> sources) {
	ll R = SZ(grid), C = SZ(grid[0]);
	vector<vi> dist(R, vi(C, -1));
	queue<ii> q;
	for (auto [r, c] : sources) dist[r][c] = 0, q.push({r, c});
	while (!q.empty()) {
		auto [r, c] = q.front();
		q.pop();
		fore(k, 0, 4) {
			ll nr = r + dr[k], nc = c + dc[k];
			if (nr < 0 || nr >= R || nc < 0 || nc >= C) continue;
			if (grid[nr][nc] == '#' || dist[nr][nc] != -1) continue;
			dist[nr][nc] = dist[r][c] + 1;
			q.push({nr, nc});
		}
	}
	return dist;
}
