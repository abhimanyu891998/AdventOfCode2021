#include<bits/stdc++.h>

using namespace std;

#define DELIM '-'

#define SOLVE_PART_2 true

vector < string > split(const string & str, char delim) {
  vector < string > elems;
  stringstream s(str);
  string parts;
  while (getline(s, parts, delim)) {
    if (parts == "")
      continue;

    elems.emplace_back(parts);
  }

  return elems;
}

bool smallHasBeenVisitedTwice = fal se;
string smallVisitedTwice = "";

void addEdge(map < string, vector < string >> & graph,
  const string & u,
    const string & v) {
  graph[u].push_back(v);
  graph[v].push_back(u);
}

void dfs(map < string, vector < string >> & graph,
  const string & s, map < string, bool > visited, int & ctr,
    const bool & part2) {
  if (s == "end") {
    ctr++;
    return;
  } else {
    if (!part2) {
      if (visited[s])
        return;
      if (islower(s[0]))
        visited[s] = true;
    } else {
      if (visited[s] && s == "start")
        return;

      if (visited[s] && smallHasBeenVisitedTwice && s != "start")
        return;

      if (visited[s] && s != "start") {
        smallHasBeenVisitedTwice = true;
        smallVisitedTwice = s;
      } else if (islower(s[0]))
        visited[s] = true;
    }

    vector < string > neighbors = graph[s];

    for (auto & n: neighbors) {
      dfs(graph, n, visited, ctr, part2);
    }

    if (!part2) {
      if (islower(s[0]) && s != "start")
        visited[s] = false;
    } else {
      if (s == smallVisitedTwice) {
        smallVisitedTwice = "";
        smallHasBeenVisitedTwice = false;
        visited[s] = false;
      } else {
        if (islower(s[0]) && s != "start")
          visited[s] = false;
      }
    }

  }
}

int main() {
  fstream f("./input.txt");
  string s;
  map < string, vector < string >> graph;
  while (getline(f, s)) {
    vector < string > elems = split(s, DELIM);
    addEdge(graph, elems[0], elems[1]);
  }

  int ctr = 0;

  map < string, bool > visited;

  for (auto & [key, value]: graph) {
    visited[key] = false;
  }

  dfs(graph, "start", visited, ctr, SOLVE_PART_2);

  if (SOLVE_PART_2)
    cout << "PART 2: ";
  else
    cout << "PART 1: ";

  cout << ctr << endl;

  return 0;
}