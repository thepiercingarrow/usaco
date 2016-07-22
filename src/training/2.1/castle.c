/*
ID: thepier1
LANG: C
TASK: castle
*/
#include <stdio.h>
#include <string.h>

#define MAX_S 50

typedef char bool;
typedef char smallint;

struct Block {
  int room;
  bool w, n, e, s;
};

struct Wall {
  char dir;
  smallint i, j;
};

struct Room {
  int size, degree;
  int neighbors[MAX_S * MAX_S / 2];
};

void assign(int i, int j, int room);
int trumps(struct Wall wall); // "wall" made me think of Trump

int M, N, wall_num = 0, room_num = 0;
struct Block castle[MAX_S][MAX_S];
struct Wall walls[2 * (MAX_S * MAX_S + 2 * MAX_S)];
struct Room rooms[MAX_S * MAX_S + 1];
int maxroom = 0;
int maxi = 250, maxj = 250;
char maxdir = 'E';

int main() {
  FILE *fio;
  fio = fopen("castle.in", "r");
  fscanf(fio, "%d %d\n", &M, &N);
  memset(castle, 0, sizeof castle);
  memset(walls, 0, sizeof walls);
  int i, j;
  for (j = 0; j < N; ++j)
    for (i = 0; i < M; ++i) {
      int tmp;
      fscanf(fio, "%d", &tmp);
      if (tmp & 0x8) // south wall
	castle[i][j].s = 1;
      if (tmp & 0x4) { // east wall
	castle[i][j].e = 1;
	if (i != M - 1) {
	  walls[wall_num].dir = 'E';
	  walls[wall_num].i = i;
	  walls[wall_num].j = j;
	  ++wall_num;
	}
      }
      if (tmp & 0x2) { // north wall
	castle[i][j].n = 1;
	if (j > 0) {
	  walls[wall_num].dir = 'N';
	  walls[wall_num].i = i;
	  walls[wall_num].j = j;
	  ++wall_num;
	}
      }
      if (tmp & 0x1) // west wall
	castle[i][j].w = 1;
    }
  fclose(fio);
  for (i = 0; i < M; ++i)
    for (j = 0; j < N; ++j)
      if (!castle[i][j].room) {
	++room_num;
	rooms[room_num].size = 0;
	assign(i, j, room_num); // assign room numbers
      }
  fio = fopen("castle.out", "w");
  fprintf(fio, "%d\n", room_num);
  for (i = 0; i < room_num; ++i)
    if (rooms[i].size > maxroom)
      maxroom = rooms[i].size; // find biggest room
  fprintf(fio, "%d\n", maxroom);
  // cycle through optimal wall removals
  for (i = 0; i < wall_num; ++i) {
    // remove wall
    int tmp;
    if ((tmp = trumps(walls[i]))) {
      maxroom = tmp;
      maxi = walls[i].i;
      maxj = walls[i].j;
      maxdir = walls[i].dir;
    }
  }
  fprintf(fio, "%d\n%d %d %c\n", maxroom, maxj + 1, maxi + 1, maxdir);
}

void assign(int i, int j, int room) {
  if (castle[i][j].room)
    return;
  ++rooms[room_num].size;
  castle[i][j].room = room;
  if (!castle[i][j].n)
    assign(i, j - 1, room);
  if (!castle[i][j].s)
    assign(i, j + 1, room);
  if (!castle[i][j].e)
    assign(i + 1, j, room);
  if (!castle[i][j].w)
    assign(i - 1, j, room);
}

int trumps(struct Wall wall) {
  if (wall.dir == 'E') {
#define a castle[wall.i][wall.j]
#define b castle[wall.i+1][wall.j]
#define newsize rooms[a.room].size + rooms[b.room].size
    if (a.room == b.room)
      return 0;
    if (newsize > maxroom) {
	  return newsize;
    }
    else if (newsize == maxroom) {
      if (wall.i < maxi)
	return newsize;
      else if (wall.i == maxi && wall.j > maxj)
	return newsize;
    }
    return 0;
#undef a
#undef b
  }
  else { // 'N'
#define a castle[wall.i][wall.j]
#define b castle[wall.i][wall.j-1]
#define newsize rooms[a.room].size + rooms[b.room].size
    if (a.room == b.room)
      return 0;
    if (newsize > maxroom) {
      return newsize;
    }
    else if (newsize == maxroom) {
      if (wall.i < maxi)
	return newsize;
      else if (wall.i == maxi && wall.j >= maxj)
	return newsize;
    }
    return 0;
#undef a
#undef b
  }
}
