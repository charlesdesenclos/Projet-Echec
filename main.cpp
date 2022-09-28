#include <SFML/Graphics.hpp>
#include <iostream>
#include "Menu.h"
#include "AfficheNP.h"
#include "Instructions.h"
#include "Plateau.h"

#define LUNGIME 8
#define PionNEGRU 1
#define PionALB -1
#define TurnNEGRU 2
#define TurnALB -2
#define CalALB -3
#define CalNEGRU 3
#define NebunNEGRU 4
#define NebunALB -4
#define ReginaALB -5
#define ReginaNEGRU 5
#define RegeNEGRU 6
#define RegeALB -6

using namespace sf;

struct poz
{
	int x, y;
}oldPoz, regeleAlb, regeleNegru, transformA, transformN;

int  taille = 100, mouvement = 0, x, y;
int board[8][8] =
{ 2, 3, 4, 5, 6, 4, 3, 2,
  1, 1, 1, 1, 1, 1, 1, 1,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
 -1,-1,-1,-1,-1,-1,-1,-1,
 -2,-3,-4,-5,-6,-4,-3,-2, };

int turnAlbDreapta = 0, turnAlbStanga = 0, regeAlb = 0;
int turnNegruDreapta = 0, turnNegruStanga = 0, regeNegru = 0;

int mutare = 0; // 0 déplace le blanc, 1 déplace le noir

int sahAlb = 0, sahNegru = 0;

int transformareAlb = 0, transformareNegru = 0;


int PionA(int ox, int oy, int nx, int ny)
{
	if (oldPoz.y == 6)
	{
		if ((ny == oy - 1 && nx == ox && board[oy - 1][ox] == 0) || (ny == oy - 2 && nx == ox && board[oy - 1][ox] == 0 && board[oy - 2][ox] == 0))
		{
			return 1;
		}
	}
	else if (ny == oy - 1 && nx == ox && board[oy - 1][ox] == 0)
	{
		return 1;
	}
	if (board[oy - 1][ox - 1] > 0)
	{
		if (ny == oy - 1 && nx == ox - 1)
		{
			return 1;
		}
	}
	if (board[oy - 1][ox + 1] > 0)
	{
		if (ny == oy - 1 && nx == ox + 1)
		{
			return 1;
		}
	}
	return 0;
}

int PionN(int ox, int oy, int nx, int ny)
{
	if (oldPoz.y == 1)
	{
		if ((ny == oy + 1 && nx == ox && board[oy + 1][ox] == 0) || (ny == oy + 2 && nx == ox && board[oy + 1][ox] == 0 && board[oy + 2][ox] == 0))
		{
			return 1;
		}
	}
	else if (ny == oy + 1 && nx == ox && board[oy + 1][ox] == 0)
	{
		return 1;
	}
	if (board[oy + 1][ox - 1] < 0)
	{
		if (ny == oy + 1 && nx == ox - 1)
		{
			return 1;
		}
	}
	if (board[oy + 1][ox + 1] < 0)
	{
		if (ny == oy + 1 && nx == ox + 1)
		{
			return 1;
		}
	}
	return 0;
}

int TurnA(int ox, int oy, int nx, int ny)
{
	for (int i = ox - 1; i >= 0; i--) //À gauche
	{
		if (board[oy][i] >= 0 && (nx == i && ny == oy))
		{
			return 1;
		}
		else if (board[oy][i] != 0)
		{
			break;
		}
	}
	for (int i = oy - 1; i >= 0; i--) // en haut
	{
		if (board[i][ox] >= 0 && (ny == i && nx == ox))
		{
			return 1;
		}
		else if (board[i][ox] != 0)
		{
			break;
		}
	}
	for (int i = ox + 1; i <= 7; i++) // À droite
	{
		if (board[oy][i] >= 0 && (ny == oy && nx == i))
		{
			return 1;
		}
		else if (board[oy][i] != 0)
		{
			break;
		}
	}
	for (int i = oy + 1; i <= 7; i++) // jvers le bas
	{
		if (board[i][ox] >= 0 && (ny == i && nx == ox))
		{
			return 1;
		}
		else if (board[i][ox] != 0)
		{
			break;
		}
	}
	return 0;
}

int TurnN(int ox, int oy, int nx, int ny)
{
	for (int i = ox - 1; i >= 0; i--) // À gauche
	{
		if (board[oy][i] <= 0 && (nx == i && ny == oy))
		{
			return 1;
		}
		else if (board[oy][i] != 0)
		{
			break;
		}
	}
	for (int i = oy - 1; i >= 0; i--) // en haut
	{
		if (board[i][ox] <= 0 && (ny == i && nx == ox))
		{
			return 1;
		}
		else if (board[i][ox] != 0)
		{
			break;
		}
	}
	for (int i = ox + 1; i <= 7; i++) // À droite
	{
		if (board[oy][i] <= 0 && (ny == oy && nx == i))
		{
			return 1;
		}
		else if (board[oy][i] != 0)
		{
			break;
		}
	}
	for (int i = oy + 1; i <= 7; i++) // vers le bas
	{
		if (board[i][ox] <= 0 && (ny == i && nx == ox))
		{
			return 1;
		}
		else if (board[i][ox] != 0)
		{
			break;
		}
	}
	return 0;
}

int NebunA(int ox, int oy, int nx, int ny)
{
	int j = ox - 1;
	for (int i = oy - 1; i >= 0; i--) // en haut à gauche
	{
		if (board[i][j] >= 0 && (ny == i && nx == j))
		{
			return 1;
		}
		else if (board[i][j] != 0)
		{
			break;
		}
		j--;
	}
	j = ox + 1;
	for (int i = oy - 1; i >= 0; i--) // en haut à droite
	{
		if (board[i][j] >= 0 && (ny == i && nx == j))
		{
			return 1;
		}
		else if (board[i][j] != 0)
		{
			break;
		}
		j++;
	}
	j = ox - 1;
	for (int i = oy + 1; i <= 7; i++) // en bas à gauche
	{
		if (board[i][j] >= 0 && (ny == i && nx == j))
		{
			return 1;
		}
		else if (board[i][j] != 0)
		{
			break;
		}
		j--;
	}
	j = ox + 1;
	for (int i = oy + 1; i <= 7; i++)  // en bas à droite
	{
		if (board[i][j] >= 0 && (ny == i && nx == j))
		{
			return 1;
		}
		else if (board[i][j] != 0)
		{
			break;
		}
		j++;
	}
	return 0;
}

int NebunN(int ox, int oy, int nx, int ny)
{
	int j = ox - 1;
	for (int i = oy - 1; i >= 0; i--) // en haut à gauche
	{
		if (board[i][j] <= 0 && (ny == i && nx == j))
		{
			return 1;
		}
		else if (board[i][j] != 0)
		{
			break;
		}
		j--;
	}
	j = ox + 1;
	for (int i = oy - 1; i >= 0; i--) // en haut à droite
	{
		if (board[i][j] <= 0 && (ny == i && nx == j))
		{
			return 1;
		}
		else if (board[i][j] != 0)
		{
			break;
		}
		j++;
	}
	j = ox - 1;
	for (int i = oy + 1; i <= 7; i++) // en bas à gauche
	{
		if (board[i][j] <= 0 && (ny == i && nx == j))
		{
			return 1;
		}
		else if (board[i][j] != 0)
		{
			break;
		}
		j--;
	}
	j = ox + 1;
	for (int i = oy + 1; i <= 7; i++)  // en bas à droite
	{
		if (board[i][j] <= 0 && (ny == i && nx == j))
		{
			return 1;
		}
		else if (board[i][j] != 0)
		{
			break;
		}
		j++;
	}
	return 0;
}

int ReginaA(int ox, int oy, int nx, int ny)
{
	for (int i = ox - 1; i >= 0; i--) // À gauche
	{
		if (board[oy][i] >= 0 && (nx == i && ny == oy))
		{
			return 1;
		}
		else if (board[oy][i] != 0)
		{
			break;
		}
	}
	for (int i = oy - 1; i >= 0; i--) // en haut
	{
		if (board[i][ox] >= 0 && (ny == i && nx == ox))
		{
			return 1;
		}
		else if (board[i][ox] != 0)
		{
			break;
		}
	}
	for (int i = ox + 1; i <= 7; i++) // À droite
	{
		if (board[oy][i] >= 0 && (ny == oy && nx == i))
		{
			return 1;
		}
		else if (board[oy][i] != 0)
		{
			break;
		}
	}
	for (int i = oy + 1; i <= 7; i++) // vers le bas
	{
		if (board[i][ox] >= 0 && (ny == i && nx == ox))
		{
			return 1;
		}
		else if (board[i][ox] != 0)
		{
			break;
		}
	}
	int j = ox - 1;
	for (int i = oy - 1; i >= 0; i--) // en haut à gauche
	{
		if (board[i][j] >= 0 && (ny == i && nx == j))
		{
			return 1;
		}
		else if (board[i][j] != 0)
		{
			break;
		}
		j--;
	}
	j = ox + 1;
	for (int i = oy - 1; i >= 0; i--) // en haut à droite
	{
		if (board[i][j] >= 0 && (ny == i && nx == j))
		{
			return 1;
		}
		else if (board[i][j] != 0)
		{
			break;
		}
		j++;
	}
	j = ox - 1;
	for (int i = oy + 1; i <= 7; i++) // en bas à gauche
	{
		if (board[i][j] >= 0 && (ny == i && nx == j))
		{
			return 1;
		}
		else if (board[i][j] != 0)
		{
			break;
		}
		j--;
	}
	j = ox + 1;
	for (int i = oy + 1; i <= 7; i++)  // en bas à droite
	{
		if (board[i][j] >= 0 && (ny == i && nx == j))
		{
			return 1;
		}
		else if (board[i][j] != 0)
		{
			break;
		}
		j++;
	}
	return 0;
}

int ReginaN(int ox, int oy, int nx, int ny)
{
	for (int i = ox - 1; i >= 0; i--) // À gauche
	{
		if (board[oy][i] <= 0 && (nx == i && ny == oy))
		{
			return 1;
		}
		else if (board[oy][i] != 0)
		{
			break;
		}
	}
	for (int i = oy - 1; i >= 0; i--) // en haut
	{
		if (board[i][ox] <= 0 && (ny == i && nx == ox))
		{
			return 1;
		}
		else if (board[i][ox] != 0)
		{
			break;
		}
	}
	for (int i = ox + 1; i <= 7; i++) // À droite
	{
		if (board[oy][i] <= 0 && (ny == oy && nx == i))
		{
			return 1;
		}
		else if (board[oy][i] != 0)
		{
			break;
		}
	}
	for (int i = oy + 1; i <= 7; i++) // vers le bas
	{
		if (board[i][ox] <= 0 && (ny == i && nx == ox))
		{
			return 1;
		}
		else if (board[i][ox] != 0)
		{
			break;
		}
	}
	int j = ox - 1;
	for (int i = oy - 1; i >= 0; i--) // en haut à gauche
	{
		if (board[i][j] <= 0 && (ny == i && nx == j))
		{
			return 1;
		}
		else if (board[i][j] != 0)
		{
			break;
		}
		j--;
	}
	j = ox + 1;
	for (int i = oy - 1; i >= 0; i--) // en haut à droite
	{
		if (board[i][j] <= 0 && (ny == i && nx == j))
		{
			return 1;
		}
		else if (board[i][j] != 0)
		{
			break;
		}
		j++;
	}
	j = ox - 1;
	for (int i = oy + 1; i <= 7; i++) // en bas à gauche
	{
		if (board[i][j] <= 0 && (ny == i && nx == j))
		{
			return 1;
		}
		else if (board[i][j] != 0)
		{
			break;
		}
		j--;
	}
	j = ox + 1;
	for (int i = oy + 1; i <= 7; i++)  // en bas à droite
	{
		if (board[i][j] <= 0 && (ny == i && nx == j))
		{
			return 1;
		}
		else if (board[i][j] != 0)
		{
			break;
		}
		j++;
	}
	return 0;
}

int CalA(int ox, int oy, int nx, int ny)
{
	if (oy - 2 >= 0 && ox - 1 >= 0 && ny == oy - 2 && nx == ox - 1 && board[ny][nx] >= 0)
	{
		return 1; // en haut à gauche
	}
	if (oy - 2 >= 0 && ox + 1 < LUNGIME && ny == oy - 2 && nx == ox + 1 && board[ny][nx] >= 0)
	{
		return 1; // En haut à droite
	}
	if (oy - 1 >= 0 && ox + 2 < LUNGIME && ny == oy - 1 && nx == ox + 2 && board[ny][nx] >= 0)
	{
		return 1; // droite 1
	}
	if (oy + 1 >= 0 && ox + 2 < LUNGIME && ny == oy + 1 && nx == ox + 2 && board[ny][nx] >= 0)
	{
		return 1; // droite 2
	}
	if (oy + 2 < LUNGIME && ox + 1 < LUNGIME && ny == oy + 2 && nx == ox + 1 && board[ny][nx] >= 0)
	{
		return 1; // vers le bas 1
	}
	if (oy + 2 < LUNGIME && ox - 1 >= 0 && ny == oy + 2 && nx == ox - 1 && board[ny][nx] >= 0)
	{
		return 1; //vers le bas 2
	}
	if (oy + 1 < LUNGIME && ox - 2 >= 0 && ny == oy + 1 && nx == ox - 2 && board[ny][nx] >= 0)
	{
		return 1; // gauche 1
	}
	if (oy - 1 >= 0 && ox - 2 >= 0 && ny == oy - 1 && nx == ox - 2 && board[ny][nx] >= 0)
	{
		return 1;
	}
	return 0;
}

int CalN(int ox, int oy, int nx, int ny)
{
	if (oy - 2 >= 0 && ox - 1 >= 0 && ny == oy - 2 && nx == ox - 1 && board[ny][nx] <= 0)
	{
		return 1; // en haut à gauche
	}
	if (oy - 2 >= 0 && ox + 1 < LUNGIME && ny == oy - 2 && nx == ox + 1 && board[ny][nx] <= 0)
	{
		return 1; // En haut à droite
	}
	if (oy - 1 >= 0 && ox + 2 < LUNGIME && ny == oy - 1 && nx == ox + 2 && board[ny][nx] <= 0)
	{
		return 1; // droite 1
	}
	if (oy + 1 >= 0 && ox + 2 < LUNGIME && ny == oy + 1 && nx == ox + 2 && board[ny][nx] <= 0)
	{
		return 1; // droite 2
	}
	if (oy + 2 < LUNGIME && ox + 1 < LUNGIME && ny == oy + 2 && nx == ox + 1 && board[ny][nx] <= 0)
	{
		return 1; // vers le bas 1
	}
	if (oy + 2 < LUNGIME && ox - 1 >= 0 && ny == oy + 2 && nx == ox - 1 && board[ny][nx] <= 0)
	{
		return 1; //jos 2
	}
	if (oy + 1 < LUNGIME && ox - 2 >= 0 && ny == oy + 1 && nx == ox - 2 && board[ny][nx] <= 0)
	{
		return 1; // gauche 1
	}
	if (oy - 1 >= 0 && ox - 2 >= 0 && ny == oy - 1 && nx == ox - 2 && board[ny][nx] <= 0)
	{
		return 1;
	}
	return 0;
}


int PionASah(int posx, int posy, int regex, int regey)
{

	if (board[posy - 1][posx - 1] >= 0)
	{
		if (posy - 1 == regey && posx - 1 == regex)
		{
			return 1;
		}
	}
	if (board[posy - 1][posx + 1] >= 0)
	{

		if (posy - 1 == regey && posx + 1 == regex)
		{
			return 1;
		}
	}
	return 0;
}

int TurnASah(int ox, int oy, int regex, int regey)
{
	for (int i = ox - 1; i >= 0; i--) // À gauche
	{
		if (board[oy][i] >= 0 && (regex == i && regey == oy))
		{
			return 1;
		}
		else if (board[oy][i] != 0)
		{
			break;
		}
	}
	for (int i = oy - 1; i >= 0; i--) // en haut
	{
		if (board[i][ox] >= 0 && (regey == i && regex == ox))
		{
			return 1;
		}
		else if (board[i][ox] != 0)
		{
			break;
		}
	}
	for (int i = ox + 1; i < LUNGIME; i++) // À droite
	{
		if (board[oy][i] >= 0 && (regey == oy && regex == i))
		{
			return 1;
		}
		else if (board[oy][i] != 0)
		{
			break;
		}
	}
	for (int i = oy + 1; i < LUNGIME; i++) // vers le bas
	{
		if (board[i][ox] >= 0 && (regey == i && regex == ox))
		{
			return 1;
		}
		else if (board[i][ox] != 0)
		{
			break;
		}
	}
	return 0;
}

int NebunASah(int ox, int oy, int regex, int regey)
{
	int j = ox - 1;
	for (int i = oy - 1; i >= 0; i--) // en haut à gauche
	{
		if (board[i][j] >= 0 && (regey == i && regex == j))
		{
			return 1;
		}
		else if (board[i][j] != 0)
		{
			break;
		}
		j--;
	}
	j = ox + 1;
	for (int i = oy - 1; i >= 0; i--) // en haut à droite
	{
		if (board[i][j] >= 0 && (regey == i && regex == j))
		{
			return 1;
		}
		else if (board[i][j] != 0)
		{
			break;
		}
		j++;
	}
	j = ox - 1;
	for (int i = oy + 1; i <= 7; i++) // en bas à gauche
	{
		if (board[i][j] >= 0 && (regey == i && regex == j))
		{
			return 1;
		}
		else if (board[i][j] != 0)
		{
			break;
		}
		j--;
	}
	j = ox + 1;
	for (int i = oy + 1; i <= 7; i++)  // en bas à droite
	{
		if (board[i][j] >= 0 && (regey == i && regex == j))
		{
			return 1;
		}
		else if (board[i][j] != 0)
		{
			break;
		}
		j++;
	}
	return 0;
}

int ReginaASah(int ox, int oy, int regex, int regey)
{
	for (int i = ox - 1; i >= 0; i--) // À gauche
	{
		if (board[oy][i] >= 0 && (regex == i && regey == oy))
		{
			return 1;
		}
		else if (board[oy][i] != 0)
		{
			break;
		}
	}
	for (int i = oy - 1; i >= 0; i--) // en haut
	{
		if (board[i][ox] >= 0 && (regey == i && regex == ox))
		{
			return 1;
		}
		else if (board[i][ox] != 0)
		{
			break;
		}
	}
	for (int i = ox + 1; i < LUNGIME; i++) //À droite
	{
		if (board[oy][i] >= 0 && (regey == oy && regex == i))
		{
			return 1;
		}
		else if (board[oy][i] != 0)
		{
			break;
		}
	}
	for (int i = oy + 1; i < LUNGIME; i++) // vers le bas
	{
		if (board[i][ox] >= 0 && (regey == i && regex == ox))
		{
			return 1;
		}
		else if (board[i][ox] != 0)
		{
			break;
		}
	}
	int j = ox - 1;
	for (int i = oy - 1; i >= 0; i--) // en haut à gauche
	{
		if (board[i][j] >= 0 && (regey == i && regex == j))
		{
			return 1;
		}
		else if (board[i][j] != 0)
		{
			break;
		}
		j--;
	}
	j = ox + 1;
	for (int i = oy - 1; i >= 0; i--) // en haut à droite
	{
		if (board[i][j] >= 0 && (regey == i && regex == j))
		{
			return 1;
		}
		else if (board[i][j] != 0)
		{
			break;
		}
		j++;
	}
	j = ox - 1;
	for (int i = oy + 1; i <= 7; i++) // en bas à gauche
	{
		if (board[i][j] >= 0 && (regey == i && regex == j))
		{
			return 1;
		}
		else if (board[i][j] != 0)
		{
			break;
		}
		j--;
	}
	j = ox + 1;
	for (int i = oy + 1; i < LUNGIME; i++)  // en bas à droite
	{
		if (board[i][j] >= 0 && (regey == i && regex == j))
		{
			return 1;
		}
		else if (board[i][j] != 0)
		{
			break;
		}
		j++;
	}
	return 0;
}

int CalASah(int ox, int oy, int regex, int regey)
{
	if (oy - 2 >= 0 && ox - 1 >= 0 && regey == oy - 2 && regex == ox - 1 && board[regey][regex] >= 0)
	{
		return 1; // en haut à gauche
	}
	if (oy - 2 >= 0 && ox + 1 < LUNGIME && regey == oy - 2 && regex == ox + 1 && board[regey][regex] >= 0)
	{
		return 1; // En haut à droite
	}
	if (oy - 1 >= 0 && ox + 2 < LUNGIME && regey == oy - 1 && regex == ox + 2 && board[regey][regex] >= 0)
	{
		return 1; // droite 1
	}
	if (oy + 1 >= 0 && ox + 2 < LUNGIME && regey == oy + 1 && regex == ox + 2 && board[regey][regex] >= 0)
	{
		return 1; // droite 2
	}
	if (oy + 2 < LUNGIME && ox + 1 < LUNGIME && regey == oy + 2 && regex == ox + 1 && board[regey][regex] >= 0)
	{
		return 1; // vers le bas 1
	}
	if (oy + 2 < LUNGIME && ox - 1 >= 0 && regey == oy + 2 && regex == ox - 1 && board[regey][regex] >= 0)
	{
		return 1; //vers le bas 2
	}
	if (oy + 1 < LUNGIME && ox - 2 >= 0 && regey == oy + 1 && regex == ox - 2 && board[regey][regex] >= 0)
	{
		return 1; // gauche 1
	}
	if (oy - 1 >= 0 && ox - 2 >= 0 && regey == oy - 1 && regex == ox - 2 && board[regey][regex] >= 0)
	{
		return 1;
	}
	return 0;
}

int RegeASah(int ox, int oy, int regex, int regey)
{
	if (ox - 1 >= 0 && oy - 1 >= 0 && regey == oy - 1 && regex == ox - 1 && board[regey][regex] <= 0)
	{
		return 1;
	}
	if (oy - 1 >= 0 && regex == ox && regey == oy - 1 && board[regey][regex] <= 0)
	{
		return 1;
	}
	if (oy - 1 >= 0 && ox + 1 < LUNGIME && regex == ox + 1 && regey == oy - 1 && board[regey][regex] <= 0)
	{
		return 1;
	}
	if (ox + 1 < LUNGIME && regey == oy && regex == ox + 1 && board[regey][regex] <= 0)
	{
		return 1;
	}
	if (ox + 1 < LUNGIME && oy + 1 < LUNGIME && regey == oy + 1 && regex == ox + 1 && board[regey][regex] <= 0)
	{
		return 1;
	}
	if (oy + 1 < LUNGIME && regey == oy + 1 && regex == ox && board[regey][regex] <= 0)
	{
		return 1;
	}
	if (ox - 1 >= 0 && oy + 1 < LUNGIME && regex == ox - 1 && regey == oy + 1 && board[regey][regex] <= 0)
	{
		return 1;
	}
	if (ox - 1 >= 0 && regey == oy && regex == ox - 1 && board[regey][regex] <= 0)
	{
		return 1;
	}
	return 0;
}


int PionNSah(int ox, int oy, int regex, int regey)
{
	if (board[oy + 1][ox - 1] <= 0)
	{
		if (regey == oy + 1 && regex == ox - 1)
		{
			return 1;
		}
	}
	if (board[oy + 1][ox + 1] <= 0)
	{
		if (regey == oy + 1 && regex == ox + 1)
		{
			return 1;
		}
	}
	return 0;
}

int TurnNSah(int ox, int oy, int regex, int regey)
{
	for (int i = ox - 1; i >= 0; i--) // À gauche
	{
		if (board[oy][i] <= 0 && (regex == i && regey == oy))
		{
			return 1;
		}
		else if (board[oy][i] != 0)
		{
			break;
		}
	}
	for (int i = oy - 1; i >= 0; i--) // en haut
	{
		if (board[i][ox] <= 0 && (regey == i && regex == ox))
		{
			return 1;
		}
		else if (board[i][ox] != 0)
		{
			break;
		}
	}
	for (int i = ox + 1; i < LUNGIME; i++) // À droite
	{
		if (board[oy][i] <= 0 && (regey == oy && regex == i))
		{
			return 1;
		}
		else if (board[oy][i] != 0)
		{
			break;
		}
	}
	for (int i = oy + 1; i < LUNGIME; i++) // vers le bas
	{
		if (board[i][ox] <= 0 && (regey == i && regex == ox))
		{
			return 1;
		}
		else if (board[i][ox] != 0)
		{
			break;
		}
	}
	return 0;
}

int NebunNSah(int ox, int oy, int regex, int regey)
{
	int j = ox - 1;
	for (int i = oy - 1; i >= 0; i--) // en haut à gauche
	{
		if (board[i][j] <= 0 && (regey == i && regex == j))
		{
			return 1;
		}
		else if (board[i][j] != 0)
		{
			break;
		}
		j--;
	}
	j = ox + 1;
	for (int i = oy - 1; i >= 0; i--) // en haut à droite
	{
		if (board[i][j] <= 0 && (regey == i && regex == j))
		{
			return 1;
		}
		else if (board[i][j] != 0)
		{
			break;
		}
		j++;
	}
	j = ox - 1;
	for (int i = oy + 1; i <= 7; i++) // en bas à gauche
	{
		if (board[i][j] <= 0 && (regey == i && regex == j))
		{
			return 1;
		}
		else if (board[i][j] != 0)
		{
			break;
		}
		j--;
	}
	j = ox + 1;
	for (int i = oy + 1; i <= 7; i++)  // en bas à droite
	{
		if (board[i][j] <= 0 && (regey == i && regex == j))
		{
			return 1;
		}
		else if (board[i][j] != 0)
		{
			break;
		}
		j++;
	}
	return 0;
}

int ReginaNSah(int ox, int oy, int regex, int regey)
{
	for (int i = ox - 1; i >= 0; i--) // À gauche
	{
		if (board[oy][i] <= 0 && (regex == i && regey == oy))
		{
			return 1;
		}
		else if (board[oy][i] != 0)
		{
			break;
		}
	}
	for (int i = oy - 1; i >= 0; i--) // en haut
	{
		if (board[i][ox] <= 0 && (regey == i && regex == ox))
		{
			return 1;
		}
		else if (board[i][ox] != 0)
		{
			break;
		}
	}
	for (int i = ox + 1; i < LUNGIME; i++) //À droite
	{
		if (board[oy][i] <= 0 && (regey == oy && regex == i))
		{
			return 1;
		}
		else if (board[oy][i] != 0)
		{
			break;
		}
	}
	for (int i = oy + 1; i < LUNGIME; i++) // vers le bas
	{
		if (board[i][ox] <= 0 && (regey == i && regex == ox))
		{
			return 1;
		}
		else if (board[i][ox] != 0)
		{
			break;
		}
	}
	int j = ox - 1;
	for (int i = oy - 1; i >= 0; i--) //en haut à gauche
	{
		if (board[i][j] <= 0 && (regey == i && regex == j))
		{
			return 1;
		}
		else if (board[i][j] != 0)
		{
			break;
		}
		j--;
	}
	j = ox + 1;
	for (int i = oy - 1; i >= 0; i--) // en haut à droite
	{
		if (board[i][j] <= 0 && (regey == i && regex == j))
		{
			return 1;
		}
		else if (board[i][j] != 0)
		{
			break;
		}
		j++;
	}
	j = ox - 1;
	for (int i = oy + 1; i <= 7; i++) // en bas à gauche
	{
		if (board[i][j] <= 0 && (regey == i && regex == j))
		{
			return 1;
		}
		else if (board[i][j] != 0)
		{
			break;
		}
		j--;
	}
	j = ox + 1;
	for (int i = oy + 1; i < LUNGIME; i++)  //en bas à droite
	{
		if (board[i][j] <= 0 && (regey == i && regex == j))
		{
			return 1;
		}
		else if (board[i][j] != 0)
		{
			break;
		}
		j++;
	}
	return 0;
}

int CalNSah(int ox, int oy, int regex, int regey)
{
	if (oy - 2 >= 0 && ox - 1 >= 0 && regey == oy - 2 && regex == ox - 1 && board[regey][regex] <= 0)
	{
		return 1; // en haut à gauche
	}
	if (oy - 2 >= 0 && ox + 1 < LUNGIME && regey == oy - 2 && regex == ox + 1 && board[regey][regex] <= 0)
	{
		return 1; // En haut à droite
	}
	if (oy - 1 >= 0 && ox + 2 < LUNGIME && regey == oy - 1 && regex == ox + 2 && board[regey][regex] <= 0)
	{
		return 1; // droite 1
	}
	if (oy + 1 >= 0 && ox + 2 < LUNGIME && regey == oy + 1 && regex == ox + 2 && board[regey][regex] <= 0)
	{
		return 1; // droite 2
	}
	if (oy + 2 < LUNGIME && ox + 1 < LUNGIME && regey == oy + 2 && regex == ox + 1 && board[regey][regex] <= 0)
	{
		return 1; // vers le bas 1
	}
	if (oy + 2 < LUNGIME && ox - 1 >= 0 && regey == oy + 2 && regex == ox - 1 && board[regey][regex] <= 0)
	{
		return 1; //vers le bas 2
	}
	if (oy + 1 < LUNGIME && ox - 2 >= 0 && regey == oy + 1 && regex == ox - 2 && board[regey][regex] <= 0)
	{
		return 1; // gauche 1
	}
	if (oy - 1 >= 0 && ox - 2 >= 0 && regey == oy - 1 && regex == ox - 2 && board[regey][regex] <= 0)
	{
		return 1;
	}
	return 0;
}

int RegeNSah(int ox, int oy, int regex, int regey)
{
	if (ox - 1 >= 0 && oy - 1 >= 0 && regey == oy - 1 && regex == ox - 1 && board[regey][regex] >= 0)
	{
		return 1;
	}
	if (oy - 1 >= 0 && regex == ox && regey == oy - 1 && board[regey][regex] >= 0)
	{
		return 1;
	}
	if (oy - 1 >= 0 && ox + 1 < LUNGIME && regex == ox + 1 && regey == oy - 1 && board[regey][regex] >= 0)
	{
		return 1;
	}
	if (ox + 1 < LUNGIME && regey == oy && regex == ox + 1 && board[regey][regex] >= 0)
	{
		return 1;
	}
	if (ox + 1 < LUNGIME && oy + 1 < LUNGIME && regey == oy + 1 && regex == ox + 1 && board[regey][regex] >= 0)
	{
		return 1;
	}
	if (oy + 1 < LUNGIME && regey == oy + 1 && regex == ox && board[regey][regex] >= 0)
	{
		return 1;
	}
	if (ox - 1 >= 0 && oy + 1 < LUNGIME && regex == ox - 1 && regey == oy + 1 && board[regey][regex] >= 0)
	{
		return 1;
	}
	if (ox - 1 >= 0 && regey == oy && regex == ox - 1 && board[regey][regex] >= 0)
	{
		return 1;
	}
	return 0;
}



int RegeNegruSahCheck(int posRegex, int posRegey)
{
	int ok = 0;
	for (int i = 0; i < LUNGIME; i++)
	{
		for (int j = 0; j < LUNGIME; j++)
		{
			if (board[i][j] < 0)
			{
				if (board[i][j] == PionALB)
				{
					ok = PionASah(j, i, posRegex, posRegey);
				}
				if (board[i][j] == TurnALB)
				{
					ok = TurnASah(j, i, posRegex, posRegey);
				}
				if (board[i][j] == CalALB)
				{
					ok = CalASah(j, i, posRegex, posRegey);
				}
				if (board[i][j] == NebunALB)
				{
					ok = NebunASah(j, i, posRegex, posRegey);
				}
				if (board[i][j] == ReginaALB)
				{
					ok = ReginaASah(j, i, posRegex, posRegey);
				}
				if (board[i][j] == RegeALB)
				{
					ok = RegeASah(j, i, posRegex, posRegey);
				}
				if (ok == 1)
				{
					return 0;
				}
			}
		}
	}
	return 1;
}

int RegeN(int ox, int oy, int nx, int ny)
{
	if (ox - 1 >= 0 && oy - 1 >= 0 && ny == oy - 1 && nx == ox - 1 && board[ny][nx] <= 0)
	{
		int ok = RegeNegruSahCheck(ox - 1, oy - 1);
		if (ok == 1)
		{
			return 1;  // en haut à gauche
		}
	}
	if (oy - 1 >= 0 && nx == ox && ny == oy - 1 && board[ny][nx] <= 0)
	{
		int ok = RegeNegruSahCheck(ox, oy - 1);
		if (ok == 1)
		{
			return 1; // en haut
		}
	}
	if (oy - 1 >= 0 && ox + 1 < LUNGIME && nx == ox + 1 && ny == oy - 1 && board[ny][nx] <= 0)
	{
		int ok = RegeNegruSahCheck(ox + 1, oy - 1);
		if (ok == 1)
		{
			return 1; // En haut à droite
		}
	}
	if (ox + 1 < LUNGIME && ny == oy && nx == ox + 1 && board[ny][nx] <= 0)
	{
		int ok = RegeNegruSahCheck(ox + 1, oy);
		if (ok == 1)
		{
			return 1; // droit
		}
	}
	if (ox + 1 < LUNGIME && oy + 1 < LUNGIME && ny == oy + 1 && nx == ox + 1 && board[ny][nx] <= 0)
	{
		int ok = RegeNegruSahCheck(ox + 1, oy + 1);
		if (ok == 1)
		{
			return 1; // en bas à droite
		}
	}
	if (oy + 1 < LUNGIME && ny == oy + 1 && nx == ox && board[ny][nx] <= 0)
	{
		int ok = RegeNegruSahCheck(ox, oy + 1);
		if (ok == 1)
		{
			return 1; // vers le bas
		}
	}
	if (ox - 1 >= 0 && oy + 1 < LUNGIME && nx == ox - 1 && ny == oy + 1 && board[ny][nx] <= 0)
	{
		int ok = RegeNegruSahCheck(ox - 1, oy + 1);
		if (ok == 1)
		{
			return 1; //en bas à gauche
		}
	}
	if (ox - 1 >= 0 && ny == oy && nx == ox - 1 && board[ny][nx] <= 0)
	{
		int ok = RegeNegruSahCheck(ox - 1, oy);
		if (ok == 1)
		{
			return 1; // La gauche
		}
	}
	// point à droite
	if (turnNegruDreapta == 0 && regeNegru == 0 && board[0][5] == 0 && board[0][6] == 0 && ny == 0 && nx == 6)
	{
		int ok = RegeNegruSahCheck(4, 0);
		if (ok == 1)
		{
			ok = RegeNegruSahCheck(5, 0);
			if (ok == 1)
			{
				ok = RegeNegruSahCheck(6, 0);
				if (ok == 1)
				{
					regeNegru = 1;
					turnNegruDreapta = 1;
					board[0][7] = 0;
					board[0][5] = TurnNEGRU;
					return 1;
				}
			}
		}
	}
	if (turnNegruStanga == 0 && regeNegru == 0 && board[0][3] == 0 && board[0][2] == 0 && board[0][1] == 0 && ny == 0 && nx == 2)
	{
		int ok = RegeNegruSahCheck(4, 0);
		if (ok == 1)
		{
			ok = RegeNegruSahCheck(3, 0);
			if (ok == 1)
			{
				ok = RegeNegruSahCheck(2, 0);
				if (ok == 1)
				{
					ok = RegeNegruSahCheck(1, 0);
					if (ok == 1)
					{
						regeNegru = 1;
						turnNegruStanga = 1;
						board[0][0] = 0;
						board[0][3] = TurnNEGRU;
						return 1;
					}
				}
			}
		}
	}
	return 0;
}


int RegeAlbSahCheck(int posRegex, int posRegey)
{
	int ok = 0;
	for (int i = 0; i < LUNGIME; i++)
	{
		for (int j = 0; j < LUNGIME; j++)
		{
			if (board[i][j] > 0)
			{
				if (board[i][j] == PionNEGRU)
				{
					ok = PionNSah(j, i, posRegex, posRegey);
				}
				if (board[i][j] == TurnNEGRU)
				{
					ok = TurnNSah(j, i, posRegex, posRegey);
				}
				if (board[i][j] == CalNEGRU)
				{
					ok = CalNSah(j, i, posRegex, posRegey);
				}
				if (board[i][j] == NebunNEGRU)
				{
					ok = NebunNSah(j, i, posRegex, posRegey);
				}
				if (board[i][j] == ReginaNEGRU)
				{
					ok = ReginaNSah(j, i, posRegex, posRegey);
				}
				if (board[i][j] == RegeNEGRU)
				{
					ok = RegeNSah(j, i, posRegex, posRegey);
				}
				if (ok == 1)
				{

					return 0;
				}
			}
		}
	}
	return 1;
}

int RegeA(int ox, int oy, int nx, int ny)
{
	if (ox - 1 >= 0 && oy - 1 >= 0 && ny == oy - 1 && nx == ox - 1 && board[ny][nx] >= 0)
	{
		int ok = RegeAlbSahCheck(ox - 1, oy - 1);
		if (ok == 1)
		{
			return 1;  // en haut à gauche
		}
	}
	if (oy - 1 >= 0 && nx == ox && ny == oy - 1 && board[ny][nx] >= 0)
	{
		int ok = RegeAlbSahCheck(ox, oy - 1);
		if (ok == 1)
		{
			return 1; // en haut
		}
	}
	if (oy - 1 >= 0 && ox + 1 < LUNGIME && nx == ox + 1 && ny == oy - 1 && board[ny][nx] >= 0)
	{
		int ok = RegeAlbSahCheck(ox + 1, oy - 1);
		if (ok == 1)
		{
			return 1; // En haut à droite
		}
	}
	if (ox + 1 < LUNGIME && ny == oy && nx == ox + 1 && board[ny][nx] >= 0)
	{
		int ok = RegeAlbSahCheck(ox + 1, oy);
		if (ok == 1)
		{
			return 1; // droit
		}
	}
	if (ox + 1 < LUNGIME && oy + 1 < LUNGIME && ny == oy + 1 && nx == ox + 1 && board[ny][nx] >= 0)
	{
		int ok = RegeAlbSahCheck(ox + 1, oy + 1);
		if (ok == 1)
		{
			return 1; // en bas à droite
		}
	}
	if (oy + 1 < LUNGIME && ny == oy + 1 && nx == ox && board[ny][nx] >= 0)
	{
		int ok = RegeAlbSahCheck(ox, oy + 1);
		if (ok == 1)
		{
			return 1; // vers le bas
		}
	}
	if (ox - 1 >= 0 && oy + 1 < LUNGIME && nx == ox - 1 && ny == oy + 1 && board[ny][nx] >= 0)
	{
		int ok = RegeAlbSahCheck(ox - 1, oy + 1);
		if (ok == 1)
		{
			return 1; //en bas à gauche
		}
	}
	if (ox - 1 >= 0 && ny == oy && nx == ox - 1 && board[ny][nx] >= 0)
	{
		int ok = RegeAlbSahCheck(ox - 1, oy);
		if (ok == 1)
		{
			return 1; // La gauche
		}
	}
	// point à droite
	if (regeAlb == 0 && turnAlbDreapta == 0 && board[7][5] == 0 && board[7][6] == 0 && ny == 7 && nx == 6)
	{
		int ok = 1;
		ok = RegeAlbSahCheck(4, 7);
		if (ok == 1)
		{
			ok = RegeAlbSahCheck(5, 7);
			if (ok == 1)
			{
				ok = RegeAlbSahCheck(6, 7);
				if (ok == 1)
				{
					board[7][7] = 0;
					board[7][5] = TurnALB;
					regeAlb = 1;
					turnAlbDreapta = 1;
					return 1;
				}
			}
		}
	}
	//	point à droite
	if (regeAlb == 0 && turnAlbDreapta == 0 && board[7][3] == 0 && board[7][2] == 0 && board[7][1] == 0 && ny == 7 && nx == 2)
	{
		int ok = 1;
		ok = RegeAlbSahCheck(4, 7);
		if (ok == 1)
		{
			ok = RegeAlbSahCheck(3, 7);
			if (ok == 1)
			{
				ok = RegeAlbSahCheck(2, 7);
				if (ok == 1)
				{
					ok = RegeAlbSahCheck(1, 7);
					if (ok == 1)
					{
						board[7][0] = 0;
						board[7][3] = TurnALB;
						regeAlb = 1;
						turnAlbStanga = 1;
						return 1;
					}
				}
			}
		}
	}
	return 0;
}


void pozRegeAlb()
{
	for (int i = 0; i < LUNGIME; i++)
	{
		for (int j = 0; j < LUNGIME; j++)
		{
			if (board[i][j] == RegeALB)
			{
				regeleAlb.x = j;
				regeleAlb.y = i;
				break;
			}
		}
	}
}

void pozRegeNegru()
{
	for (int i = 0; i < LUNGIME; i++)
	{
		for (int j = 0; j < LUNGIME; j++)
		{
			if (board[i][j] == RegeNEGRU)
			{
				regeleNegru.y = i;
				regeleNegru.x = j;
				break;
			}
		}
	}
}

using namespace sf;

void main(int argc, char **argv)
{


	RenderWindow window(sf::VideoMode(960, 720), "Echecs", Style::Default);
	window.setFramerateLimit(60);

	Menu menu(window.getSize().x, window.getSize().y);

	
	// Affichage du thème à la page d'accueil

	RectangleShape background;
	background.setSize(Vector2f(960, 720));
	Texture texture;
	texture.loadFromFile("donnees/imagefond.jpg");
	background.setTexture(&texture);

	// Affichage du thème à la page du choix solo ou multi

	RectangleShape Pbackground;
	Pbackground.setSize(Vector2f(960, 720));
	Texture Play_texture;
	Play_texture.loadFromFile("donnees/imagefond.jpg");
	Pbackground.setTexture(&Play_texture);

	// Affichage du thème à la page d'Instructions

	RectangleShape Ibackground;
	Ibackground.setSize(Vector2f(960, 720));
	Texture Instructions_texture;
	Instructions_texture.loadFromFile("donnees/imagefond.jpg");
	Ibackground.setTexture(&Instructions_texture);

	// Affichage du thème à la page d'options

	RectangleShape Obackground;
	Obackground.setSize(Vector2f(960, 720));
	Texture Options_texture;
	Options_texture.loadFromFile("donnees/imagefond.jpg");
	Obackground.setTexture(&Options_texture);


	//Affichage général
	// on fait tourner le programme jusqu'à ce que la fenêtre soit fermée
	while (window.isOpen())
	{
		// on inspecte tous les évènements de la fenêtre qui ont été émis depuis la précédente itération
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
			}

			if (event.type == Event::KeyReleased)
			{
				if (event.key.code == Keyboard::Up)
				{
					menu.MoveUp();
					break;
				}
				if (event.key.code == Keyboard::Down)
				{
					menu.MoveDown();
					break;
				}

				if (event.key.code == Keyboard::Return)
				{
					RenderWindow Play(VideoMode(960, 720), "Echecs");
					Play.setFramerateLimit(60);

					AfficheNP AfficheNP(Play.getSize().x, Play.getSize().y);
					RenderWindow Instructions(VideoMode(960, 720), "Instructions");
					RenderWindow Options(VideoMode(960, 720), "Options");


					int x = menu.MenuPressed();
					if (x == 0)
					{
						while (Play.isOpen())
						{
							Event aevent;
							while (Play.pollEvent(aevent))
							{
								if (aevent.type == Event::Closed)
								{
									Play.close();

								}
								if (aevent.type == Event::KeyPressed)
								{
									if (aevent.key.code == Keyboard::Escape)
									{
										Play.close();
									}
								}
							}
							Instructions.close();
							Options.close();
							Play.clear();

							Play.draw(Pbackground);

							AfficheNP.draw(Play);

							Play.display();
						}

					}
					if (x == 1)
					{
						while (Instructions.isOpen())
						{
							Event aevent;
							while (Instructions.pollEvent(aevent))
							{
								if (aevent.type == Event::Closed)
								{
									Instructions.close();
								}
								if (aevent.type == Event::KeyPressed)
								{
									if (aevent.key.code == Keyboard::Escape)
									{
										Instructions.close();
									}
								}
							}
							Play.close();
							Instructions.clear();
							Options.close();

							Instructions.draw(Ibackground);

							Instructions.display();


						}
					}
					if (x == 2)
					{
						while (Options.isOpen())
						{
							Event aevent;
							while (Options.pollEvent(aevent))
							{
								if (aevent.type == Event::Closed)
								{
									Options.close();
								}
								if (aevent.type == Event::KeyPressed)
								{
									if (aevent.key.code == Keyboard::Escape)
									{
										Options.close();
									}
								}
							}
							Play.close();
							Instructions.clear();
							Options.clear();

							Options.draw(Obackground);

							Options.display();

						}
					}

					if (x == 3)
					{
						window.close();
						break;
					}

				}

			}
			else if (event.type == Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == Mouse::Left)
				{
					
					//printf("%d %d\n", event.mouseButton.x, event.mouseButton.y);
					
					if (event.mouseButton.x >= 337 && event.mouseButton.y >= 199)
					{
						if (event.mouseButton.x <= 750 && event.mouseButton.y <= 245)
						{
							window.close();
							RenderWindow Play(VideoMode(960, 720), "Echecs");
							Play.setFramerateLimit(60);

							AfficheNP AfficheNP(Play.getSize().x, Play.getSize().y);

							
							

							while (Play.isOpen())
							{
								
								Event aevent;
								while (Play.pollEvent(aevent))
								{
									if (aevent.type == Event::Closed)
									{
										Play.close();

									}

									if (aevent.type == Event::MouseButtonPressed)
									{
										
										if (aevent.mouseButton.button == Mouse::Left)
										{
											
											if (aevent.mouseButton.x >= 337 && aevent.mouseButton.y >= 199)
											{
												if (aevent.mouseButton.x <= 750 && aevent.mouseButton.y <= 245)
												{

													
													Play.close();
													RenderWindow Plateaux(VideoMode(800, 800), "Plateau");
													//Plateaux.setFramerateLimit(30);

													Texture t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15;

													t1.loadFromFile("images/board.png");
													t2.loadFromFile("images/PionNegru.png");
													t3.loadFromFile("images/PionAlb.png");
													t4.loadFromFile("images/TurnNegru.png");
													t5.loadFromFile("images/TurnAlb.png");
													t6.loadFromFile("images/CalAlb.png");
													t7.loadFromFile("images/CalNegru.png");
													t8.loadFromFile("images/NebunNegru.png");
													t9.loadFromFile("images/NebunAlb.png");
													t10.loadFromFile("images/ReginaAlb.png");
													t11.loadFromFile("images/ReginaNegru.png");
													t12.loadFromFile("images/RegeNegru.png");
													t13.loadFromFile("images/RegeAlb.png");
													t14.loadFromFile("images/TransformareAlb.png");
													t15.loadFromFile("images/TransformareNegru.png");

													Sprite tabla(t1);
													Sprite PionNegru(t2);
													Sprite PionAlb(t3);
													Sprite TurnNegru(t4);
													Sprite TurnAlb(t5);
													Sprite CalAlb(t6);
													Sprite CalNegru(t7);
													Sprite NebunNegru(t8);
													Sprite NebunAlb(t9);
													Sprite ReginaAlb(t10);
													Sprite ReginaNegru(t11);
													Sprite RegeNegru(t12);
													Sprite RegeAlb(t13);
													Sprite Mutare;
													Sprite TransformareALB(t14);
													Sprite TransformareNEGRU(t15);

													float dx = 0, dy = 0;
													int numarPiesaMutata = 0;
													

													
													
													
													while (Plateaux.isOpen())
													{
								
														Vector2i pos = Mouse::getPosition(Plateaux);
														x = pos.x / taille;
														y = pos.y / taille;
														
														Event saevent;
														while (Plateaux.pollEvent(saevent))
														{
															if (aevent.type == Event::Closed)
															{
																Plateaux.close();
															}
															if (saevent.type == Event::MouseButtonPressed)
															{

																if (saevent.mouseButton.button == Mouse::Left)
																{
																	if (transformareAlb == 1)
																	{
																		if (pos.y >= transformA.y * taille && pos.y <= (transformA.y + 1) * taille && pos.x >= transformA.x * taille && pos.x <= (transformA.x + 1) * taille)
																		{
																			int xx = pos.x % 100, yy = pos.y % 100;

																			if (xx < 50 && yy < 50 && xx > 0 && yy > 0)
																			{
																				board[transformA.y][transformA.x] = TurnALB;
																				transformareAlb = 0;
																			}
																			if (xx > 50 && xx < 100 && yy < 50 && yy > 0)
																			{
																				board[transformA.y][transformA.x] = ReginaALB;
																				transformareAlb = 0;
																			}
																			if (xx > 50 && xx < 100 && yy>50 && yy < 100)
																			{
																				board[transformA.y][transformA.x] = CalALB;
																				transformareAlb = 0;
																			}
																			if (xx < 50 && xx>0 && yy > 50 && y < 100)
																			{
																				board[transformA.y][transformA.x] = NebunALB;
																				transformareAlb = 0;
																			}
																			if (transformareAlb == 0)
																			{
																				pozRegeNegru();
																				int h = RegeNegruSahCheck(regeleNegru.x, regeleNegru.y);
																				if (h == 0)
																				{
																					sahNegru = 1;
																				}
																			}
																		}
																	}
																	if (transformareNegru == 1)
																	{
																		if (pos.y >= transformN.y * taille && pos.y <= (transformN.y + 1) * taille && pos.x >= transformN.x * taille && pos.x <= (transformN.x + 1) * taille)
																		{
																			int xx = pos.x % 100, yy = pos.y % 100;

																			if (xx < 50 && yy < 50 && xx > 0 && yy > 0)
																			{
																				board[transformN.y][transformN.x] = TurnNEGRU;
																				transformareNegru = 0;
																			}
																			if (xx > 50 && xx < 100 && yy < 50 && yy > 0)
																			{
																				board[transformN.y][transformN.x] = ReginaNEGRU;
																				transformareNegru = 0;
																			}
																			if (xx > 50 && xx < 100 && yy>50 && yy < 100)
																			{
																				board[transformN.y][transformN.x] = CalNEGRU;
																				transformareNegru = 0;
																			}
																			if (xx < 50 && xx>0 && yy > 50 && y < 100)
																			{
																				board[transformN.y][transformN.x] = NebunNEGRU;
																				transformareNegru = 0;
																			}
																			if (transformareNegru == 0)
																			{
																				pozRegeAlb();
																				int h = RegeAlbSahCheck(regeleAlb.x, regeleAlb.y);
																				if (h == 0)
																				{
																					sahAlb = 1;
																				}
																			}
																		}
																	}
																	if (board[y][x] != 0)
																	{
																		dx = pos.x - x * 100;
																		dy = pos.y - y * 100;
																		if (board[y][x] == PionNEGRU && mutare == 1)
																		{
																			numarPiesaMutata = PionNEGRU;
																			Mutare = PionNegru;
																			board[y][x] = 0;
																		}
																		if (board[y][x] == PionALB && mutare == 0)
																		{
																			numarPiesaMutata = PionALB;
																			Mutare = PionAlb;
																			board[y][x] = 0;
																		}
																		if (board[y][x] == TurnNEGRU && mutare == 1)
																		{
																			numarPiesaMutata = TurnNEGRU;
																			Mutare = TurnNegru;
																			board[y][x] = 0;

																		}
																		if (board[y][x] == TurnALB && mutare == 0)
																		{
																			numarPiesaMutata = TurnALB;
																			Mutare = TurnAlb;
																			board[y][x] = 0;

																		}
																		if (board[y][x] == CalALB && mutare == 0)
																		{
																			numarPiesaMutata = CalALB;
																			Mutare = CalAlb;
																			board[y][x] = 0;
																		}
																		if (board[y][x] == CalNEGRU && mutare == 1)
																		{
																			numarPiesaMutata = CalNEGRU;
																			Mutare = CalNegru;
																			board[y][x] = 0;
																		}
																		if (board[y][x] == NebunNEGRU && mutare == 1)
																		{
																			numarPiesaMutata = NebunNEGRU;
																			Mutare = NebunNegru;
																			board[y][x] = 0;
																		}
																		if (board[y][x] == NebunALB && mutare == 0)
																		{
																			numarPiesaMutata = NebunALB;
																			Mutare = NebunAlb;
																			board[y][x] = 0;
																		}
																		if (board[y][x] == ReginaALB && mutare == 0)
																		{
																			numarPiesaMutata = ReginaALB;
																			Mutare = ReginaAlb;
																			board[y][x] = 0;
																		}
																		if (board[y][x] == ReginaNEGRU && mutare == 1)
																		{
																			numarPiesaMutata = ReginaNEGRU;
																			Mutare = ReginaNegru;
																			board[y][x] = 0;
																		}
																		if (board[y][x] == RegeNEGRU && mutare == 1)
																		{
																			numarPiesaMutata = RegeNEGRU;
																			Mutare = RegeNegru;
																			board[y][x] = 0;
																		}
																		if (board[y][x] == RegeALB && mutare == 0)
																		{
																			numarPiesaMutata = RegeALB;
																			Mutare = RegeAlb;
																			board[y][x] = 0;
																		}
																		if (board[y][x] == 0)
																		{
																			mouvement = 1;
																			oldPoz.x = x;
																			oldPoz.y = y;
																		}
																	}
																}
															}

															if (saevent.type == Event::MouseButtonReleased)
															{
																if (saevent.key.code == Mouse::Left)
																{
																	int ok = 2;
																	if (numarPiesaMutata == PionALB && mouvement == 1)
																	{
																		ok = PionA(oldPoz.x, oldPoz.y, x, y);
																	}
																	if (numarPiesaMutata == PionNEGRU && mouvement == 1)
																	{
																		ok = PionN(oldPoz.x, oldPoz.y, x, y);
																	}
																	if (numarPiesaMutata == TurnALB && mouvement == 1)
																	{
																		ok = TurnA(oldPoz.x, oldPoz.y, x, y);
																		if (ok == 1 && turnAlbStanga == 0 && oldPoz.y == 7 && oldPoz.x == 0)
																		{
																			turnAlbStanga = 1;

																		}
																		if (ok == 1 && turnAlbDreapta == 0 && oldPoz.y == 7 && oldPoz.x == 7)
																		{
																			turnAlbDreapta = 1;

																		}
																	}
																	if (numarPiesaMutata == TurnNEGRU && mouvement == 1)
																	{
																		ok = TurnN(oldPoz.x, oldPoz.y, x, y);
																		if (ok == 1 && turnNegruDreapta == 0 && oldPoz.y == 0 && oldPoz.x == 7)
																		{
																			turnNegruDreapta = 1;

																		}
																		if (ok == 1 && turnNegruStanga == 0 && oldPoz.y == 0 && oldPoz.x == 0)
																		{
																			turnNegruStanga = 1;

																		}
																	}
																	if (numarPiesaMutata == NebunALB && mouvement == 1)
																	{
																		ok = NebunA(oldPoz.x, oldPoz.y, x, y);
																	}
																	if (numarPiesaMutata == NebunNEGRU && mouvement == 1)
																	{
																		ok = NebunN(oldPoz.x, oldPoz.y, x, y);
																	}
																	if (numarPiesaMutata == ReginaALB && mouvement == 1)
																	{
																		ok = ReginaA(oldPoz.x, oldPoz.y, x, y);
																	}
																	if (numarPiesaMutata == ReginaNEGRU && mouvement == 1)
																	{
																		ok = ReginaN(oldPoz.x, oldPoz.y, x, y);
																	}
																	if (numarPiesaMutata == CalALB && mouvement == 1)
																	{
																		ok = CalA(oldPoz.x, oldPoz.y, x, y);
																	}
																	if (numarPiesaMutata == CalNEGRU && mouvement == 1)
																	{
																		ok = CalN(oldPoz.x, oldPoz.y, x, y);
																	}
																	if (numarPiesaMutata == RegeNEGRU && mouvement == 1)
																	{
																		ok = RegeN(oldPoz.x, oldPoz.y, x, y);
																		if (ok == 1 && regeNegru == 0)
																		{
																			regeNegru = 1;

																		}
																	}
																	if (numarPiesaMutata == RegeALB && mouvement == 1)
																	{
																		ok = RegeA(oldPoz.x, oldPoz.y, x, y);
																		if (ok == 1 && regeAlb == 0)
																		{
																			regeAlb = 1;

																		}
																	}
																	if (ok == 1)
																	{
																		int nr = board[y][x];
																		board[y][x] = numarPiesaMutata;
																		if (y == 0 && numarPiesaMutata == PionALB)
																		{
																			transformareAlb = 1;
																			transformA.x = x;
																			transformA.y = y;
																			board[y][x] = 0;
																		}
																		if (y == 7 && numarPiesaMutata == PionNEGRU)
																		{
																			transformareNegru = 1;
																			transformN.x = x;
																			transformN.y = y;
																			board[y][x] = 0;
																		}
																		if (mutare == 0) // blanc a bougé et noir suit
																		{
																			if (sahAlb == 1)
																			{
																				pozRegeAlb();
																				int s = RegeAlbSahCheck(regeleAlb.x, regeleAlb.y);
																				if (s == 0)
																				{
																					board[oldPoz.y][oldPoz.x] = numarPiesaMutata;
																					board[y][x] = nr;
																				}
																				else
																				{
																					sahAlb = 0;
																					pozRegeNegru();
																					int sah = RegeNegruSahCheck(regeleNegru.x, regeleNegru.y);
																					if (sah == 0)
																					{
																						sahNegru = 1;
																					}
																					mutare = 1;
																				}
																			}
																			else
																			{
																				pozRegeAlb();
																				int sa = RegeAlbSahCheck(regeleAlb.x, regeleAlb.y);
																				if (sa == 0)
																				{
																					board[oldPoz.y][oldPoz.x] = numarPiesaMutata;
																					board[y][x] = nr;
																				}
																				else
																				{
																					pozRegeNegru();
																					int sah = RegeNegruSahCheck(regeleNegru.x, regeleNegru.y);
																					if (sah == 0)
																					{
																						sahNegru = 1;
																					}
																					mutare = 1;
																				}
																			}
																		}
																		else // le noir s'est déplacé et le blanc suit
																		{
																			if (sahNegru == 1)
																			{
																				pozRegeNegru();
																				int s = RegeNegruSahCheck(regeleNegru.x, regeleNegru.y);
																				if (s == 0)
																				{
																					board[oldPoz.y][oldPoz.x] = numarPiesaMutata;
																					board[y][x] = nr;
																				}
																				else
																				{
																					sahNegru = 0;
																					pozRegeAlb();
																					int sah = RegeAlbSahCheck(regeleAlb.x, regeleAlb.y);
																					if (sah == 0)
																					{
																						sahAlb = 1;
																					}
																					mutare = 0;
																				}
																			}
																			else
																			{
																				pozRegeNegru();
																				int sa = RegeNegruSahCheck(regeleNegru.x, regeleNegru.y);
																				if (sa == 0)
																				{
																					board[oldPoz.y][oldPoz.x] = numarPiesaMutata;
																					board[y][x] = nr;
																				}
																				else
																				{
																					pozRegeAlb();
																					int sah = RegeAlbSahCheck(regeleAlb.x, regeleAlb.y);
																					if (sah == 0)
																					{
																						sahAlb = 1;
																					}
																					mutare = 0;
																				}
																			}
																		}
																	}
																	else if (ok == 0)
																	{
																		board[oldPoz.y][oldPoz.x] = numarPiesaMutata;
																	}
																	mouvement = 0;
																}
															}

														}

														Plateaux.clear();

														Plateaux.draw(tabla);
														if (transformareAlb == 1)
														{
															TransformareALB.setPosition(transformA.x* taille, transformA.y* taille);
															Plateaux.draw(TransformareALB);
														}
														if (transformareNegru == 1)
														{
															TransformareNEGRU.setPosition(transformN.x* taille, transformN.y* taille);
															Plateaux.draw(TransformareNEGRU);
														}
														if (mouvement == 1)
														{
															Mutare.setPosition(pos.x - dx, pos.y - dy);
															Plateaux.draw(Mutare);
														}
														for (int i = 0; i < LUNGIME; i++)
														{
															for (int j = 0; j < LUNGIME; j++)
															{

																if (board[i][j] != 0)
																{
																	if (board[i][j] == PionNEGRU)
																	{
																		PionNegru.setPosition(j * taille, i * taille);
																		Plateaux.draw(PionNegru);
																	}
																	if (board[i][j] == PionALB)
																	{
																		PionAlb.setPosition(j * taille, i * taille);
																		Plateaux.draw(PionAlb);
																	}
																	if (board[i][j] == TurnNEGRU)
																	{
																		TurnNegru.setPosition(j * taille, i * taille);
																		Plateaux.draw(TurnNegru);

																	}
																	if (board[i][j] == TurnALB)
																	{
																		TurnAlb.setPosition(j * taille, i * taille);
																		Plateaux.draw(TurnAlb);

																	}
																	if (board[i][j] == CalALB)
																	{
																		CalAlb.setPosition(j * taille, i * taille);
																		Plateaux.draw(CalAlb);
																	}
																	if (board[i][j] == CalNEGRU)
																	{
																		CalNegru.setPosition(j * taille, i * taille);
																		Plateaux.draw(CalNegru);
																	}
																	if (board[i][j] == NebunNEGRU)
																	{
																		NebunNegru.setPosition(j * taille, i * taille);
																		Plateaux.draw(NebunNegru);
																	}
																	if (board[i][j] == NebunALB)
																	{
																		NebunAlb.setPosition(j * taille, i * taille);
																		Plateaux.draw(NebunAlb);
																	}
																	if (board[i][j] == ReginaALB)
																	{
																		ReginaAlb.setPosition(j * taille, i * taille);
																		Plateaux.draw(ReginaAlb);
																	}
																	if (board[i][j] == ReginaNEGRU)
																	{
																		ReginaNegru.setPosition(j * taille, i * taille);
																		Plateaux.draw(ReginaNegru);
																	}
																	if (board[i][j] == RegeNEGRU)
																	{
																		RegeNegru.setPosition(j * taille, i * taille);
																		Plateaux.draw(RegeNegru);
																	}
																	if (board[i][j] == RegeALB)
																	{
																		RegeAlb.setPosition(j * taille, i * taille);
																		Plateaux.draw(RegeAlb);
																	}
																}
															}
														}
														Plateaux.display();

														
													}
													
												}
											}
											if (aevent.mouseButton.x >= 343 && aevent.mouseButton.y >= 305)
											{
												if (aevent.mouseButton.x <= 623 && aevent.mouseButton.y <= 341)
												{
													Play.close();
													RenderWindow Multi(VideoMode(960, 720), "Multi");
													Multi.setFramerateLimit(30);

													// Affichage Plateau

													Texture image;

													image.loadFromFile("./donnees/board.png");

													Sprite sprite;
													image.setSmooth(true);
													sprite.setTexture(image);

													sprite.setScale(1.4f, 1.4f);

													//Affichage pion blanc

													//Affichage pion roi

													Texture image_roi;

													image_roi.loadFromFile("./donnees/king.png");

													Sprite sprite_roi;

													image_roi.setSmooth(true);

													sprite_roi.setTexture(image_roi);

													sprite_roi.setScale(0.6f, 0.6f);

													sprite_roi.setPosition(350, 580);

													//Affichage pion reine

													Texture image_reine;

													image_reine.loadFromFile("./donnees/queen.png");

													Sprite sprite_reine;

													image_reine.setSmooth(true);

													sprite_reine.setTexture(image_reine);

													sprite_reine.setScale(0.6f, 0.6f);

													sprite_reine.setPosition(270, 580);

													//Affichage des pions fou 

													Texture image_fou;

													image_fou.loadFromFile("./donnees/fou.png");

													Sprite sprite_fou;

													image_fou.setSmooth(true);

													sprite_fou.setTexture(image_fou);

													sprite_fou.setScale(0.6f, 0.6f);

													sprite_fou.setPosition(190, 580);

													Texture image_fou2;

													image_fou2.loadFromFile("./donnees/fou.png");

													Sprite sprite_fou2;

													image_fou.setSmooth(true);

													sprite_fou2.setTexture(image_fou2);

													sprite_fou2.setScale(0.6f, 0.6f);

													sprite_fou2.setPosition(425, 580);

													//Affichage des pions chevaliers

													Texture image_chavalier;

													image_chavalier.loadFromFile("./donnees/knight.png");

													Sprite sprite_chevalier;

													image_chavalier.setSmooth(true);

													sprite_chevalier.setTexture(image_chavalier);

													sprite_chevalier.setScale(0.6f, 0.6f);

													sprite_chevalier.setPosition(110, 580);

													Texture image_chevalier2;

													image_chevalier2.loadFromFile("./donnees/knight.png");

													Sprite sprite_chevalier2;

													image_chevalier2.setSmooth(true);

													sprite_chevalier2.setTexture(image_chevalier2);

													sprite_chevalier2.setScale(0.6f, 0.6f);

													sprite_chevalier2.setPosition(505, 580);

													//Affichage des pions tours

													Texture image_tour;

													image_tour.loadFromFile("./donnees/rook.png");

													Sprite sprite_tour;

													image_tour.setSmooth(true);

													sprite_tour.setTexture(image_tour);

													sprite_tour.setScale(0.6f, 0.6f);

													sprite_tour.setPosition(30, 580);

													Texture image_tour2;

													image_tour2.loadFromFile("./donnees/rook.png");

													Sprite sprite_tour2;

													image_tour2.setSmooth(true);

													sprite_tour2.setTexture(image_tour2);

													sprite_tour2.setScale(0.6f, 0.6f);

													sprite_tour2.setPosition(585, 580);

													//Affichage des pions 

													Texture image_pion;

													image_pion.loadFromFile("./donnees/pawn.png");

													Sprite sprite_pion;

													image_pion.setSmooth(true);

													sprite_pion.setTexture(image_pion);

													sprite_pion.setScale(0.6f, 0.6f);

													sprite_pion.setPosition(30, 500);

													Texture image_pion2;

													image_pion2.loadFromFile("./donnees/pawn.png");

													Sprite sprite_pion2;

													image_pion2.setSmooth(true);

													sprite_pion2.setTexture(image_pion2);

													sprite_pion2.setScale(0.6f, 0.6f);

													sprite_pion2.setPosition(110, 500);

													Texture image_pion3;

													image_pion3.loadFromFile("./donnees/pawn.png");

													Sprite sprite_pion3;

													image_pion3.setSmooth(true);

													sprite_pion3.setTexture(image_pion3);

													sprite_pion3.setScale(0.6f, 0.6f);

													sprite_pion3.setPosition(190, 500);

													Texture image_pion4;

													image_pion4.loadFromFile("./donnees/pawn.png");

													Sprite sprite_pion4;

													image_pion4.setSmooth(true);

													sprite_pion4.setTexture(image_pion4);

													sprite_pion4.setScale(0.6f, 0.6f);

													sprite_pion4.setPosition(270, 500);

													Texture image_pion5;

													image_pion5.loadFromFile("./donnees/pawn.png");

													Sprite sprite_pion5;

													image_pion5.setSmooth(true);

													sprite_pion5.setTexture(image_pion5);

													sprite_pion5.setScale(0.6f, 0.6f);

													sprite_pion5.setPosition(350, 500);

													Texture image_pion6;

													image_pion6.loadFromFile("./donnees/pawn.png");

													Sprite sprite_pion6;

													image_pion6.setSmooth(true);

													sprite_pion6.setTexture(image_pion6);

													sprite_pion6.setScale(0.6f, 0.6f);

													sprite_pion6.setPosition(425, 500);

													Texture image_pion7;

													image_pion7.loadFromFile("./donnees/pawn.png");

													Sprite sprite_pion7;

													image_pion7.setSmooth(true);

													sprite_pion7.setTexture(image_pion7);

													sprite_pion7.setScale(0.6f, 0.6f);

													sprite_pion7.setPosition(505, 500);

													Texture image_pion8;

													image_pion8.loadFromFile("./donnees/pawn.png");

													Sprite sprite_pion8;

													image_pion8.setSmooth(true);

													sprite_pion8.setTexture(image_pion8);

													sprite_pion8.setScale(0.6f, 0.6f);

													sprite_pion8.setPosition(585, 500);

													//Affichage pion noir

													//Affichage pion roi

													Texture image_roin;

													image_roin.loadFromFile("./donnees/king.png");

													Sprite sprite_roin;

													image_roin.setSmooth(true);

													sprite_roin.setTexture(image_roin);

													sprite_roin.setColor(Color::Black);

													sprite_roin.setScale(0.6f, 0.6f);

													sprite_roin.setPosition(350, 30);

													//Affichage pion reine

													Texture image_reinen;

													image_reinen.loadFromFile("./donnees/queen.png");

													Sprite sprite_reinen;

													image_reinen.setSmooth(true);

													sprite_reinen.setTexture(image_reinen);

													sprite_reinen.setColor(Color::Black);

													sprite_reinen.setScale(0.6f, 0.6f);

													sprite_reinen.setPosition(270, 30);

													//Affichage des pions fou 

													Texture image_foun;

													image_foun.loadFromFile("./donnees/fou.png");

													Sprite sprite_foun;

													image_foun.setSmooth(true);

													sprite_foun.setTexture(image_foun);

													sprite_foun.setColor(Color::Black);

													sprite_foun.setScale(0.6f, 0.6f);

													sprite_foun.setPosition(190, 30);

													Texture image_fou2n;

													image_fou2n.loadFromFile("./donnees/fou.png");

													Sprite sprite_fou2n;

													image_foun.setSmooth(true);

													sprite_fou2n.setTexture(image_fou2n);

													sprite_fou2n.setColor(Color::Black);

													sprite_fou2n.setScale(0.6f, 0.6f);

													sprite_fou2n.setPosition(425, 30);

													//Affichage des pions chevaliers

													Texture image_chavaliern;

													image_chavaliern.loadFromFile("./donnees/knight.png");

													Sprite sprite_chevaliern;

													image_chavaliern.setSmooth(true);

													sprite_chevaliern.setTexture(image_chavaliern);

													sprite_chevaliern.setColor(Color::Black);

													sprite_chevaliern.setScale(0.6f, 0.6f);

													sprite_chevaliern.setPosition(110, 30);

													Texture image_chevalier2n;

													image_chevalier2n.loadFromFile("./donnees/knight.png");

													Sprite sprite_chevalier2n;

													image_chevalier2n.setSmooth(true);

													sprite_chevalier2n.setTexture(image_chevalier2n);

													sprite_chevalier2n.setColor(Color::Black);

													sprite_chevalier2n.setScale(0.6f, 0.6f);

													sprite_chevalier2n.setPosition(505, 30);

													//Affichage des pions tours

													Texture image_tourn;

													image_tourn.loadFromFile("./donnees/rook.png");

													Sprite sprite_tourn;

													image_tourn.setSmooth(true);

													sprite_tourn.setTexture(image_tourn);

													sprite_tourn.setColor(Color::Black);

													sprite_tourn.setScale(0.6f, 0.6f);

													sprite_tourn.setPosition(30, 30);

													Texture image_tour2n;

													image_tour2n.loadFromFile("./donnees/rook.png");

													Sprite sprite_tour2n;

													image_tour2n.setSmooth(true);

													sprite_tour2n.setTexture(image_tour2n);

													sprite_tour2n.setColor(Color::Black);

													sprite_tour2n.setScale(0.6f, 0.6f);

													sprite_tour2n.setPosition(585, 30);

													//Affichage des pions 

													Texture image_pionn;

													image_pionn.loadFromFile("./donnees/pawn.png");

													Sprite sprite_pionn;

													image_pionn.setSmooth(true);

													sprite_pionn.setTexture(image_pionn);

													sprite_pionn.setColor(Color::Black);

													sprite_pionn.setScale(0.6f, 0.6f);

													sprite_pionn.setPosition(30, 110);

													Texture image_pion2n;

													image_pion2n.loadFromFile("./donnees/pawn.png");

													Sprite sprite_pion2n;

													image_pion2n.setSmooth(true);

													sprite_pion2n.setTexture(image_pion2n);

													sprite_pion2n.setColor(Color::Black);

													sprite_pion2n.setScale(0.6f, 0.6f);

													sprite_pion2n.setPosition(110, 110);

													Texture image_pion3n;

													image_pion3n.loadFromFile("./donnees/pawn.png");

													Sprite sprite_pion3n;

													image_pion3n.setSmooth(true);

													sprite_pion3n.setTexture(image_pion3n);

													sprite_pion3n.setColor(Color::Black);

													sprite_pion3n.setScale(0.6f, 0.6f);

													sprite_pion3n.setPosition(190, 110);

													Texture image_pion4n;

													image_pion4n.loadFromFile("./donnees/pawn.png");

													Sprite sprite_pion4n;

													image_pion4n.setSmooth(true);

													sprite_pion4n.setTexture(image_pion4n);

													sprite_pion4n.setColor(Color::Black);

													sprite_pion4n.setScale(0.6f, 0.6f);

													sprite_pion4n.setPosition(270, 110);

													Texture image_pion5n;

													image_pion5n.loadFromFile("./donnees/pawn.png");

													Sprite sprite_pion5n;

													image_pion5n.setSmooth(true);

													sprite_pion5n.setTexture(image_pion5n);

													sprite_pion5n.setColor(Color::Black);

													sprite_pion5n.setScale(0.6f, 0.6f);

													sprite_pion5n.setPosition(350, 110);

													Texture image_pion6n;

													image_pion6n.loadFromFile("./donnees/pawn.png");

													Sprite sprite_pion6n;

													image_pion6n.setSmooth(true);

													sprite_pion6n.setTexture(image_pion6n);

													sprite_pion6n.setColor(Color::Black);

													sprite_pion6n.setScale(0.6f, 0.6f);

													sprite_pion6n.setPosition(425, 110);

													Texture image_pion7n;

													image_pion7n.loadFromFile("./donnees/pawn.png");

													Sprite sprite_pion7n;

													image_pion7n.setSmooth(true);

													sprite_pion7n.setTexture(image_pion7n);

													sprite_pion7n.setColor(Color::Black);

													sprite_pion7n.setScale(0.6f, 0.6f);

													sprite_pion7n.setPosition(505, 110);

													Texture image_pion8n;

													image_pion8n.loadFromFile("./donnees/pawn.png");

													Sprite sprite_pion8n;

													image_pion8n.setSmooth(true);

													sprite_pion8n.setTexture(image_pion8n);

													sprite_pion8n.setColor(Color::Black);

													sprite_pion8n.setScale(0.6f, 0.6f);

													sprite_pion8n.setPosition(585, 110);

													while (Multi.isOpen())
													{
														Event aevent;
														while (Multi.pollEvent(aevent))
														{
															if (aevent.type == Event::Closed)
															{
																Multi.close();
															}

														}

														Multi.clear();


														Multi.draw(sprite);

														Multi.draw(sprite_roi);

														Multi.draw(sprite_reine);

														Multi.draw(sprite_fou);

														Multi.draw(sprite_fou2);

														Multi.draw(sprite_chevalier);

														Multi.draw(sprite_chevalier2);

														Multi.draw(sprite_tour);

														Multi.draw(sprite_tour2);

														Multi.draw(sprite_pion);

														Multi.draw(sprite_pion2);

														Multi.draw(sprite_pion3);

														Multi.draw(sprite_pion4);

														Multi.draw(sprite_pion5);

														Multi.draw(sprite_pion6);

														Multi.draw(sprite_pion7);

														Multi.draw(sprite_pion8);

														Multi.draw(sprite_roin);

														Multi.draw(sprite_reinen);

														Multi.draw(sprite_foun);

														Multi.draw(sprite_fou2n);

														Multi.draw(sprite_chevaliern);

														Multi.draw(sprite_chevalier2n);

														Multi.draw(sprite_tourn);

														Multi.draw(sprite_tour2n);

														Multi.draw(sprite_pionn);

														Multi.draw(sprite_pion2n);

														Multi.draw(sprite_pion3n);

														Multi.draw(sprite_pion4n);

														Multi.draw(sprite_pion5n);

														Multi.draw(sprite_pion6n);

														Multi.draw(sprite_pion7n);

														Multi.draw(sprite_pion8n);

														Multi.display();
													}
												}
											}
										}

									}

								}
								Play.clear();

								Play.draw(Pbackground);



								AfficheNP.draw(Play);

								Play.display();
							}
							
						}

					if (event.mouseButton.x >= 343 && event.mouseButton.y >= 305)
					{
						if (event.mouseButton.x <= 623 && event.mouseButton.y <= 341)
						{
							window.close();
							RenderWindow Instruction(VideoMode(960, 720), "Instructions");

							Instructions Instructions(Instruction.getSize().x, Instruction.getSize().y);

							while (Instruction.isOpen())
							{
								Event aevent;
								while (Instruction.pollEvent(aevent))
								{
									if (aevent.type == Event::Closed)
									{
										Instruction.close();
									}


										
								}
									
								Instruction.clear();
									

								Instruction.draw(Ibackground);

								Instructions.draw(Instruction);

								Instruction.display();
							}
						}
					}
					if (event.mouseButton.x >= 340 && event.mouseButton.y >= 400)
					{
						if (event.mouseButton.x <= 513 && event.mouseButton.y <= 443)
						{
							window.close();
							RenderWindow Options(VideoMode(960, 720), "Options");

							while (Options.isOpen())
							{
								Event aevent;
								while (Options.pollEvent(aevent))
								{
									if (aevent.type == Event::Closed)
									{
										Options.close();
									}
									
								}
								Options.clear();

								Options.draw(Obackground);

								Options.display();

							}
						}

					}

					if (event.mouseButton.x >= 342 && event.mouseButton.y >= 503)
					{
						if (event.mouseButton.x <= 524 && event.mouseButton.y <= 545)
						{
							window.close();
							break;
						}

					}
				}
					
					
			}
			}

			window.clear();
			window.draw(background);
			menu.draw(window);
			window.display();

			


		}





	}
}