#include <SFML/Graphics.hpp>
#include <iostream>
#include "Menu.h"
#include "AfficheNP.h"
#include "Instructions.h"
#include "Plateau.h"
#include "Option.h"
#include "ServeurJeuxEchecs.h"
#include "main.h"

#define LONGUEUR 8
#define PionNOIR 1
#define PionBLANC -1
#define TourNOIR 2
#define TourBlanche -2
#define ChevalierBlanc -3
#define ChevalierNoir 3
#define FouNOIR 4
#define FouBLANC -4
#define ReineBLANCHE -5
#define ReineNOIRE 5
#define RoiNOIRE 6
#define RoiBLANC -6

using namespace sf;

using namespace std;

struct poz
{
	int x, y;
}ancienPos, roiBlanc, roiNoir, transformA, transformN;

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

int tourBlancDroit = 0, tourBlancGauche = 0, roiBLC = 0;
int tourNoirDroit = 0, tourNoirGauche = 0, roiNR = 0;

int mutare = 0; // 0 déplace le blanc, 1 déplace le noir

int numarPiesaMutataMultiJugador = 0;

int EchecsBLANC = 0, sahNegru = 0;

int transformationBlanc = 0, transformationNoir = 0;


int PionB(int ox, int oy, int nx, int ny)
{
	if (ancienPos.y == 6)
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
	if (ancienPos.y == 1)
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

int TourB(int ox, int oy, int nx, int ny)
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

int TourN(int ox, int oy, int nx, int ny)
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

int FouB(int ox, int oy, int nx, int ny)
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

int FouN(int ox, int oy, int nx, int ny)
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

int ReineB(int ox, int oy, int nx, int ny)
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

int ReineN(int ox, int oy, int nx, int ny)
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

int ChevalB(int ox, int oy, int nx, int ny)
{
	if (oy - 2 >= 0 && ox - 1 >= 0 && ny == oy - 2 && nx == ox - 1 && board[ny][nx] >= 0)
	{
		return 1; // en haut à gauche
	}
	if (oy - 2 >= 0 && ox + 1 < LONGUEUR && ny == oy - 2 && nx == ox + 1 && board[ny][nx] >= 0)
	{
		return 1; // En haut à droite
	}
	if (oy - 1 >= 0 && ox + 2 < LONGUEUR && ny == oy - 1 && nx == ox + 2 && board[ny][nx] >= 0)
	{
		return 1; // droite 1
	}
	if (oy + 1 >= 0 && ox + 2 < LONGUEUR && ny == oy + 1 && nx == ox + 2 && board[ny][nx] >= 0)
	{
		return 1; // droite 2
	}
	if (oy + 2 < LONGUEUR && ox + 1 < LONGUEUR && ny == oy + 2 && nx == ox + 1 && board[ny][nx] >= 0)
	{
		return 1; // vers le bas 1
	}
	if (oy + 2 < LONGUEUR && ox - 1 >= 0 && ny == oy + 2 && nx == ox - 1 && board[ny][nx] >= 0)
	{
		return 1; //vers le bas 2
	}
	if (oy + 1 < LONGUEUR && ox - 2 >= 0 && ny == oy + 1 && nx == ox - 2 && board[ny][nx] >= 0)
	{
		return 1; // gauche 1
	}
	if (oy - 1 >= 0 && ox - 2 >= 0 && ny == oy - 1 && nx == ox - 2 && board[ny][nx] >= 0)
	{
		return 1;
	}
	return 0;
}

int ChevalN(int ox, int oy, int nx, int ny)
{
	if (oy - 2 >= 0 && ox - 1 >= 0 && ny == oy - 2 && nx == ox - 1 && board[ny][nx] <= 0)
	{
		return 1; // en haut à gauche
	}
	if (oy - 2 >= 0 && ox + 1 < LONGUEUR && ny == oy - 2 && nx == ox + 1 && board[ny][nx] <= 0)
	{
		return 1; // En haut à droite
	}
	if (oy - 1 >= 0 && ox + 2 < LONGUEUR && ny == oy - 1 && nx == ox + 2 && board[ny][nx] <= 0)
	{
		return 1; // droite 1
	}
	if (oy + 1 >= 0 && ox + 2 < LONGUEUR && ny == oy + 1 && nx == ox + 2 && board[ny][nx] <= 0)
	{
		return 1; // droite 2
	}
	if (oy + 2 < LONGUEUR && ox + 1 < LONGUEUR && ny == oy + 2 && nx == ox + 1 && board[ny][nx] <= 0)
	{
		return 1; // vers le bas 1
	}
	if (oy + 2 < LONGUEUR && ox - 1 >= 0 && ny == oy + 2 && nx == ox - 1 && board[ny][nx] <= 0)
	{
		return 1; //jos 2
	}
	if (oy + 1 < LONGUEUR && ox - 2 >= 0 && ny == oy + 1 && nx == ox - 2 && board[ny][nx] <= 0)
	{
		return 1; // gauche 1
	}
	if (oy - 1 >= 0 && ox - 2 >= 0 && ny == oy - 1 && nx == ox - 2 && board[ny][nx] <= 0)
	{
		return 1;
	}
	return 0;
}


int PionBJeuxEchecs(int posx, int posy, int roix, int roiy)
{

	if (board[posy - 1][posx - 1] >= 0)
	{
		if (posy - 1 == roiy && posx - 1 == roix)
		{
			return 1;
		}
	}
	if (board[posy - 1][posx + 1] >= 0)
	{

		if (posy - 1 == roiy && posx + 1 == roix)
		{
			return 1;
		}
	}
	return 0;
}

int TourBJeuxEchecs(int ox, int oy, int roix, int roiy)
{
	for (int i = ox - 1; i >= 0; i--) // À gauche
	{
		if (board[oy][i] >= 0 && (roix == i && roiy == oy))
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
		if (board[i][ox] >= 0 && (roiy == i && roix == ox))
		{
			return 1;
		}
		else if (board[i][ox] != 0)
		{
			break;
		}
	}
	for (int i = ox + 1; i < LONGUEUR; i++) // À droite
	{
		if (board[oy][i] >= 0 && (roiy == oy && roix == i))
		{
			return 1;
		}
		else if (board[oy][i] != 0)
		{
			break;
		}
	}
	for (int i = oy + 1; i < LONGUEUR; i++) // vers le bas
	{
		if (board[i][ox] >= 0 && (roiy == i && roix == ox))
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

int FouBJeuxEchecs(int ox, int oy, int roix, int roiy)
{
	int j = ox - 1;
	for (int i = oy - 1; i >= 0; i--) // en haut à gauche
	{
		if (board[i][j] >= 0 && (roiy == i && roix == j))
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
		if (board[i][j] >= 0 && (roiy == i && roix == j))
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
		if (board[i][j] >= 0 && (roiy == i && roix == j))
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
		if (board[i][j] >= 0 && (roiy == i && roix == j))
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

int ReinneBJeuxEchecs(int ox, int oy, int roix, int roiy)
{
	for (int i = ox - 1; i >= 0; i--) // À gauche
	{
		if (board[oy][i] >= 0 && (roix == i && roiy == oy))
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
		if (board[i][ox] >= 0 && (roiy == i && roix == ox))
		{
			return 1;
		}
		else if (board[i][ox] != 0)
		{
			break;
		}
	}
	for (int i = ox + 1; i < LONGUEUR; i++) //À droite
	{
		if (board[oy][i] >= 0 && (roiy == oy && roix == i))
		{
			return 1;
		}
		else if (board[oy][i] != 0)
		{
			break;
		}
	}
	for (int i = oy + 1; i < LONGUEUR; i++) // vers le bas
	{
		if (board[i][ox] >= 0 && (roiy == i && roix == ox))
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
		if (board[i][j] >= 0 && (roiy == i && roix == j))
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
		if (board[i][j] >= 0 && (roiy == i && roix == j))
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
		if (board[i][j] >= 0 && (roiy == i && roix == j))
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
	for (int i = oy + 1; i < LONGUEUR; i++)  // en bas à droite
	{
		if (board[i][j] >= 0 && (roiy == i && roix == j))
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

int ChevalBJeuxEchecs(int ox, int oy, int roix, int roiy)
{
	if (oy - 2 >= 0 && ox - 1 >= 0 && roiy == oy - 2 && roix == ox - 1 && board[roiy][roix] >= 0)
	{
		return 1; // en haut à gauche
	}
	if (oy - 2 >= 0 && ox + 1 < LONGUEUR && roiy == oy - 2 && roix == ox + 1 && board[roiy][roix] >= 0)
	{
		return 1; // En haut à droite
	}
	if (oy - 1 >= 0 && ox + 2 < LONGUEUR && roiy == oy - 1 && roix == ox + 2 && board[roiy][roix] >= 0)
	{
		return 1; // droite 1
	}
	if (oy + 1 >= 0 && ox + 2 < LONGUEUR && roiy == oy + 1 && roix == ox + 2 && board[roiy][roix] >= 0)
	{
		return 1; // droite 2
	}
	if (oy + 2 < LONGUEUR && ox + 1 < LONGUEUR && roiy == oy + 2 && roix == ox + 1 && board[roiy][roix] >= 0)
	{
		return 1; // vers le bas 1
	}
	if (oy + 2 < LONGUEUR && ox - 1 >= 0 && roiy == oy + 2 && roix == ox - 1 && board[roiy][roix] >= 0)
	{
		return 1; //vers le bas 2
	}
	if (oy + 1 < LONGUEUR && ox - 2 >= 0 && roiy == oy + 1 && roix == ox - 2 && board[roiy][roix] >= 0)
	{
		return 1; // gauche 1
	}
	if (oy - 1 >= 0 && ox - 2 >= 0 && roiy == oy - 1 && roix == ox - 2 && board[roiy][roix] >= 0)
	{
		return 1;
	}
	return 0;
}

int RoiBJeuxEchecs(int ox, int oy, int roix, int roiy)
{
	if (ox - 1 >= 0 && oy - 1 >= 0 && roiy == oy - 1 && roix == ox - 1 && board[roiy][roix] <= 0)
	{
		return 1;
	}
	if (oy - 1 >= 0 && roix == ox && roiy == oy - 1 && board[roiy][roix] <= 0)
	{
		return 1;
	}
	if (oy - 1 >= 0 && ox + 1 < LONGUEUR && roix == ox + 1 && roiy == oy - 1 && board[roiy][roix] <= 0)
	{
		return 1;
	}
	if (ox + 1 < LONGUEUR && roiy == oy && roix == ox + 1 && board[roiy][roix] <= 0)
	{
		return 1;
	}
	if (ox + 1 < LONGUEUR && oy + 1 < LONGUEUR && roiy == oy + 1 && roix == ox + 1 && board[roiy][roix] <= 0)
	{
		return 1;
	}
	if (oy + 1 < LONGUEUR && roiy == oy + 1 && roix == ox && board[roiy][roix] <= 0)
	{
		return 1;
	}
	if (ox - 1 >= 0 && oy + 1 < LONGUEUR && roix == ox - 1 && roiy == oy + 1 && board[roiy][roix] <= 0)
	{
		return 1;
	}
	if (ox - 1 >= 0 && roiy == oy && roix == ox - 1 && board[roiy][roix] <= 0)
	{
		return 1;
	}
	return 0;
}


int PionNJeuxEchecs(int ox, int oy, int roix, int roiy)
{
	if (board[oy + 1][ox - 1] <= 0)
	{
		if (roiy == oy + 1 && roix == ox - 1)
		{
			return 1;
		}
	}
	if (board[oy + 1][ox + 1] <= 0)
	{
		if (roiy == oy + 1 && roix == ox + 1)
		{
			return 1;
		}
	}
	return 0;
}

int TourNJeuxEchecs(int ox, int oy, int roix, int roiy)
{
	for (int i = ox - 1; i >= 0; i--) // À gauche
	{
		if (board[oy][i] <= 0 && (roix == i && roiy == oy))
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
		if (board[i][ox] <= 0 && (roiy == i && roix == ox))
		{
			return 1;
		}
		else if (board[i][ox] != 0)
		{
			break;
		}
	}
	for (int i = ox + 1; i < LONGUEUR; i++) // À droite
	{
		if (board[oy][i] <= 0 && (roiy == oy && roix == i))
		{
			return 1;
		}
		else if (board[oy][i] != 0)
		{
			break;
		}
	}
	for (int i = oy + 1; i < LONGUEUR; i++) // vers le bas
	{
		if (board[i][ox] <= 0 && (roiy == i && roix == ox))
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

int FouNJeuxEchecs(int ox, int oy, int roix, int roiy)
{
	int j = ox - 1;
	for (int i = oy - 1; i >= 0; i--) // en haut à gauche
	{
		if (board[i][j] <= 0 && (roiy == i && roix == j))
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
		if (board[i][j] <= 0 && (roiy == i && roix == j))
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
		if (board[i][j] <= 0 && (roiy == i && roix == j))
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
		if (board[i][j] <= 0 && (roiy == i && roix == j))
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

int ReinneNJeuxEchecs(int ox, int oy, int roix, int roiy)
{
	for (int i = ox - 1; i >= 0; i--) // À gauche
	{
		if (board[oy][i] <= 0 && (roix == i && roiy == oy))
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
		if (board[i][ox] <= 0 && (roiy == i && roix == ox))
		{
			return 1;
		}
		else if (board[i][ox] != 0)
		{
			break;
		}
	}
	for (int i = ox + 1; i < LONGUEUR; i++) //À droite
	{
		if (board[oy][i] <= 0 && (roiy == oy && roix == i))
		{
			return 1;
		}
		else if (board[oy][i] != 0)
		{
			break;
		}
	}
	for (int i = oy + 1; i < LONGUEUR; i++) // vers le bas
	{
		if (board[i][ox] <= 0 && (roiy == i && roix == ox))
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
		if (board[i][j] <= 0 && (roiy == i && roix == j))
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
		if (board[i][j] <= 0 && (roiy == i && roix == j))
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
		if (board[i][j] <= 0 && (roiy == i && roix == j))
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
	for (int i = oy + 1; i < LONGUEUR; i++)  //en bas à droite
	{
		if (board[i][j] <= 0 && (roiy == i && roix == j))
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

int ChevalNJeuxEchecs(int ox, int oy, int roix, int roiy)
{
	if (oy - 2 >= 0 && ox - 1 >= 0 && roiy == oy - 2 && roix == ox - 1 && board[roiy][roix] <= 0)
	{
		return 1; // en haut à gauche
	}
	if (oy - 2 >= 0 && ox + 1 < LONGUEUR && roiy == oy - 2 && roix == ox + 1 && board[roiy][roix] <= 0)
	{
		return 1; // En haut à droite
	}
	if (oy - 1 >= 0 && ox + 2 < LONGUEUR && roiy == oy - 1 && roix == ox + 2 && board[roiy][roix] <= 0)
	{
		return 1; // droite 1
	}
	if (oy + 1 >= 0 && ox + 2 < LONGUEUR && roiy == oy + 1 && roix == ox + 2 && board[roiy][roix] <= 0)
	{
		return 1; // droite 2
	}
	if (oy + 2 < LONGUEUR && ox + 1 < LONGUEUR && roiy == oy + 2 && roix == ox + 1 && board[roiy][roix] <= 0)
	{
		return 1; // vers le bas 1
	}
	if (oy + 2 < LONGUEUR && ox - 1 >= 0 && roiy == oy + 2 && roix == ox - 1 && board[roiy][roix] <= 0)
	{
		return 1; //vers le bas 2
	}
	if (oy + 1 < LONGUEUR && ox - 2 >= 0 && roiy == oy + 1 && roix == ox - 2 && board[roiy][roix] <= 0)
	{
		return 1; // gauche 1
	}
	if (oy - 1 >= 0 && ox - 2 >= 0 && roiy == oy - 1 && roix == ox - 2 && board[roiy][roix] <= 0)
	{
		return 1;
	}
	return 0;
}

int RoiNJeuxEchecs(int ox, int oy, int roix, int roiy)
{
	if (ox - 1 >= 0 && oy - 1 >= 0 && roiy == oy - 1 && roix == ox - 1 && board[roiy][roix] >= 0)
	{
		return 1;
	}
	if (oy - 1 >= 0 && roix == ox && roiy == oy - 1 && board[roiy][roix] >= 0)
	{
		return 1;
	}
	if (oy - 1 >= 0 && ox + 1 < LONGUEUR && roix == ox + 1 && roiy == oy - 1 && board[roiy][roix] >= 0)
	{
		return 1;
	}
	if (ox + 1 < LONGUEUR && roiy == oy && roix == ox + 1 && board[roiy][roix] >= 0)
	{
		return 1;
	}
	if (ox + 1 < LONGUEUR && oy + 1 < LONGUEUR && roiy == oy + 1 && roix == ox + 1 && board[roiy][roix] >= 0)
	{
		return 1;
	}
	if (oy + 1 < LONGUEUR && roiy == oy + 1 && roix == ox && board[roiy][roix] >= 0)
	{
		return 1;
	}
	if (ox - 1 >= 0 && oy + 1 < LONGUEUR && roix == ox - 1 && roiy == oy + 1 && board[roiy][roix] >= 0)
	{
		return 1;
	}
	if (ox - 1 >= 0 && roiy == oy && roix == ox - 1 && board[roiy][roix] >= 0)
	{
		return 1;
	}
	return 0;
}



int RoiNoirJeuxEchecsVerif(int posRoix, int posRoiy)
{
	int ok = 0;
	for (int i = 0; i < LONGUEUR; i++)
	{
		for (int j = 0; j < LONGUEUR; j++)
		{
			if (board[i][j] < 0)
			{
				if (board[i][j] == PionBLANC)
				{
					ok = PionBJeuxEchecs(j, i, posRoix, posRoiy);
				}
				if (board[i][j] == TourBlanche)
				{
					ok = TourBJeuxEchecs(j, i, posRoix, posRoiy);
				}
				if (board[i][j] == ChevalierBlanc)
				{
					ok = ChevalBJeuxEchecs(j, i, posRoix, posRoiy);
				}
				if (board[i][j] == FouBLANC)
				{
					ok = FouBJeuxEchecs(j, i, posRoix, posRoiy);
				}
				if (board[i][j] == ReineBLANCHE)
				{
					ok = ReinneBJeuxEchecs(j, i, posRoix, posRoiy);
				}
				if (board[i][j] == RoiBLANC)
				{
					ok = RoiBJeuxEchecs(j, i, posRoix, posRoiy);
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

int RoiN(int ox, int oy, int nx, int ny)
{
	if (ox - 1 >= 0 && oy - 1 >= 0 && ny == oy - 1 && nx == ox - 1 && board[ny][nx] <= 0)
	{
		int ok = RoiNoirJeuxEchecsVerif(ox - 1, oy - 1);
		if (ok == 1)
		{
			return 1;  // en haut à gauche
		}
	}
	if (oy - 1 >= 0 && nx == ox && ny == oy - 1 && board[ny][nx] <= 0)
	{
		int ok = RoiNoirJeuxEchecsVerif(ox, oy - 1);
		if (ok == 1)
		{
			return 1; // en haut
		}
	}
	if (oy - 1 >= 0 && ox + 1 < LONGUEUR && nx == ox + 1 && ny == oy - 1 && board[ny][nx] <= 0)
	{
		int ok = RoiNoirJeuxEchecsVerif(ox + 1, oy - 1);
		if (ok == 1)
		{
			return 1; // En haut à droite
		}
	}
	if (ox + 1 < LONGUEUR && ny == oy && nx == ox + 1 && board[ny][nx] <= 0)
	{
		int ok = RoiNoirJeuxEchecsVerif(ox + 1, oy);
		if (ok == 1)
		{
			return 1; // droit
		}
	}
	if (ox + 1 < LONGUEUR && oy + 1 < LONGUEUR && ny == oy + 1 && nx == ox + 1 && board[ny][nx] <= 0)
	{
		int ok = RoiNoirJeuxEchecsVerif(ox + 1, oy + 1);
		if (ok == 1)
		{
			return 1; // en bas à droite
		}
	}
	if (oy + 1 < LONGUEUR && ny == oy + 1 && nx == ox && board[ny][nx] <= 0)
	{
		int ok = RoiNoirJeuxEchecsVerif(ox, oy + 1);
		if (ok == 1)
		{
			return 1; // vers le bas
		}
	}
	if (ox - 1 >= 0 && oy + 1 < LONGUEUR && nx == ox - 1 && ny == oy + 1 && board[ny][nx] <= 0)
	{
		int ok = RoiNoirJeuxEchecsVerif(ox - 1, oy + 1);
		if (ok == 1)
		{
			return 1; //en bas à gauche
		}
	}
	if (ox - 1 >= 0 && ny == oy && nx == ox - 1 && board[ny][nx] <= 0)
	{
		int ok = RoiNoirJeuxEchecsVerif(ox - 1, oy);
		if (ok == 1)
		{
			return 1; // La gauche
		}
	}
	// point à droite
	if (tourNoirDroit == 0 && roiNR == 0 && board[0][5] == 0 && board[0][6] == 0 && ny == 0 && nx == 6)
	{
		int ok = RoiNoirJeuxEchecsVerif(4, 0);
		if (ok == 1)
		{
			ok = RoiNoirJeuxEchecsVerif(5, 0);
			if (ok == 1)
			{
				ok = RoiNoirJeuxEchecsVerif(6, 0);
				if (ok == 1)
				{
					roiNR = 1;
					tourNoirDroit = 1;
					board[0][7] = 0;
					board[0][5] = TourNOIR;
					return 1;
				}
			}
		}
	}
	if (tourNoirGauche == 0 && roiNR == 0 && board[0][3] == 0 && board[0][2] == 0 && board[0][1] == 0 && ny == 0 && nx == 2)
	{
		int ok = RoiNoirJeuxEchecsVerif(4, 0);
		if (ok == 1)
		{
			ok = RoiNoirJeuxEchecsVerif(3, 0);
			if (ok == 1)
			{
				ok = RoiNoirJeuxEchecsVerif(2, 0);
				if (ok == 1)
				{
					ok = RoiNoirJeuxEchecsVerif(1, 0);
					if (ok == 1)
					{
						roiNR = 1;
						tourNoirGauche = 1;
						board[0][0] = 0;
						board[0][3] = TourNOIR;
						return 1;
					}
				}
			}
		}
	}
	return 0;
}


int RoiBlancJeuxEchecsVerif(int posRoix, int posRoiy)
{
	int ok = 0;
	for (int i = 0; i < LONGUEUR; i++)
	{
		for (int j = 0; j < LONGUEUR; j++)
		{
			if (board[i][j] > 0)
			{
				if (board[i][j] == PionNOIR)
				{
					ok = PionNJeuxEchecs(j, i, posRoix, posRoiy);
				}
				if (board[i][j] == TourNOIR)
				{
					ok = TourNJeuxEchecs(j, i, posRoix, posRoiy);
				}
				if (board[i][j] == ChevalierNoir)
				{
					ok = ChevalNJeuxEchecs(j, i, posRoix, posRoiy);
				}
				if (board[i][j] == FouNOIR)
				{
					ok = FouNJeuxEchecs(j, i, posRoix, posRoiy);
				}
				if (board[i][j] == ReineNOIRE)
				{
					ok = ReinneNJeuxEchecs(j, i, posRoix, posRoiy);
				}
				if (board[i][j] == RoiNOIRE)
				{
					ok = RoiNJeuxEchecs(j, i, posRoix, posRoiy);
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

int RoiB(int ox, int oy, int nx, int ny)
{
	if (ox - 1 >= 0 && oy - 1 >= 0 && ny == oy - 1 && nx == ox - 1 && board[ny][nx] >= 0)
	{
		int ok = RoiBlancJeuxEchecsVerif(ox - 1, oy - 1);
		if (ok == 1)
		{
			return 1;  // en haut à gauche
		}
	}
	if (oy - 1 >= 0 && nx == ox && ny == oy - 1 && board[ny][nx] >= 0)
	{
		int ok = RoiBlancJeuxEchecsVerif(ox, oy - 1);
		if (ok == 1)
		{
			return 1; // en haut
		}
	}
	if (oy - 1 >= 0 && ox + 1 < LONGUEUR && nx == ox + 1 && ny == oy - 1 && board[ny][nx] >= 0)
	{
		int ok = RoiBlancJeuxEchecsVerif(ox + 1, oy - 1);
		if (ok == 1)
		{
			return 1; // En haut à droite
		}
	}
	if (ox + 1 < LONGUEUR && ny == oy && nx == ox + 1 && board[ny][nx] >= 0)
	{
		int ok = RoiBlancJeuxEchecsVerif(ox + 1, oy);
		if (ok == 1)
		{
			return 1; // droit
		}
	}
	if (ox + 1 < LONGUEUR && oy + 1 < LONGUEUR && ny == oy + 1 && nx == ox + 1 && board[ny][nx] >= 0)
	{
		int ok = RoiBlancJeuxEchecsVerif(ox + 1, oy + 1);
		if (ok == 1)
		{
			return 1; // en bas à droite
		}
	}
	if (oy + 1 < LONGUEUR && ny == oy + 1 && nx == ox && board[ny][nx] >= 0)
	{
		int ok = RoiBlancJeuxEchecsVerif(ox, oy + 1);
		if (ok == 1)
		{
			return 1; // vers le bas
		}
	}
	if (ox - 1 >= 0 && oy + 1 < LONGUEUR && nx == ox - 1 && ny == oy + 1 && board[ny][nx] >= 0)
	{
		int ok = RoiBlancJeuxEchecsVerif(ox - 1, oy + 1);
		if (ok == 1)
		{
			return 1; //en bas à gauche
		}
	}
	if (ox - 1 >= 0 && ny == oy && nx == ox - 1 && board[ny][nx] >= 0)
	{
		int ok = RoiBlancJeuxEchecsVerif(ox - 1, oy);
		if (ok == 1)
		{
			return 1; // La gauche
		}
	}
	// point à droite
	if (roiBLC == 0 && tourBlancDroit == 0 && board[7][5] == 0 && board[7][6] == 0 && ny == 7 && nx == 6)
	{
		int ok = 1;
		ok = RoiBlancJeuxEchecsVerif(4, 7);
		if (ok == 1)
		{
			ok = RoiBlancJeuxEchecsVerif(5, 7);
			if (ok == 1)
			{
				ok = RoiBlancJeuxEchecsVerif(6, 7);
				if (ok == 1)
				{
					board[7][7] = 0;
					board[7][5] = TourBlanche;
					roiBLC = 1;
					tourBlancDroit = 1;
					return 1;
				}
			}
		}
	}
	//	point à droite
	if (roiBLC == 0 && tourBlancDroit == 0 && board[7][3] == 0 && board[7][2] == 0 && board[7][1] == 0 && ny == 7 && nx == 2)
	{
		int ok = 1;
		ok = RoiBlancJeuxEchecsVerif(4, 7);
		if (ok == 1)
		{
			ok = RoiBlancJeuxEchecsVerif(3, 7);
			if (ok == 1)
			{
				ok = RoiBlancJeuxEchecsVerif(2, 7);
				if (ok == 1)
				{
					ok = RoiBlancJeuxEchecsVerif(1, 7);
					if (ok == 1)
					{
						board[7][0] = 0;
						board[7][3] = TourBlanche;
						roiBLC = 1;
						tourBlancGauche = 1;
						return 1;
					}
				}
			}
		}
	}
	return 0;
}


void posRoiBlanc()
{
	for (int i = 0; i < LONGUEUR; i++)
	{
		for (int j = 0; j < LONGUEUR; j++)
		{
			if (board[i][j] == RoiBLANC)
			{
				roiBlanc.x = j;
				roiBlanc.y = i;
				break;
			}
		}
	}
}

void posRoiNoir()
{
	for (int i = 0; i < LONGUEUR; i++)
	{
		for (int j = 0; j < LONGUEUR; j++)
		{
			if (board[i][j] == RoiNOIRE)
			{
				roiNoir.y = i;
				roiNoir.x = j;
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
															if (saevent.type == Event::Closed)
															{
																Plateaux.close();
															}
															if (saevent.type == Event::MouseButtonPressed)
															{

																if (saevent.mouseButton.button == Mouse::Left)
																{
																	if (transformationBlanc == 1)
																	{
																		if (pos.y >= transformA.y * taille && pos.y <= (transformA.y + 1) * taille && pos.x >= transformA.x * taille && pos.x <= (transformA.x + 1) * taille)
																		{
																			int xx = pos.x % 100, yy = pos.y % 100;

																			if (xx < 50 && yy < 50 && xx > 0 && yy > 0)
																			{
																				board[transformA.y][transformA.x] = TourBlanche;
																				transformationBlanc = 0;
																			}
																			if (xx > 50 && xx < 100 && yy < 50 && yy > 0)
																			{
																				board[transformA.y][transformA.x] = ReineBLANCHE;
																				transformationBlanc = 0;
																			}
																			if (xx > 50 && xx < 100 && yy>50 && yy < 100)
																			{
																				board[transformA.y][transformA.x] = ChevalierBlanc;
																				transformationBlanc = 0;
																			}
																			if (xx < 50 && xx>0 && yy > 50 && y < 100)
																			{
																				board[transformA.y][transformA.x] = FouBLANC;
																				transformationBlanc = 0;
																			}
																			if (transformationBlanc == 0)
																			{
																				posRoiNoir();
																				int h = RoiNoirJeuxEchecsVerif(roiNoir.x, roiNoir.y);
																				if (h == 0)
																				{
																					sahNegru = 1;
																				}
																			}
																		}
																	}
																	if (transformationNoir == 1)
																	{
																		if (pos.y >= transformN.y * taille && pos.y <= (transformN.y + 1) * taille && pos.x >= transformN.x * taille && pos.x <= (transformN.x + 1) * taille)
																		{
																			int xx = pos.x % 100, yy = pos.y % 100;

																			if (xx < 50 && yy < 50 && xx > 0 && yy > 0)
																			{
																				board[transformN.y][transformN.x] = TourNOIR;
																				transformationNoir = 0;
																			}
																			if (xx > 50 && xx < 100 && yy < 50 && yy > 0)
																			{
																				board[transformN.y][transformN.x] = ReineNOIRE;
																				transformationNoir = 0;
																			}
																			if (xx > 50 && xx < 100 && yy>50 && yy < 100)
																			{
																				board[transformN.y][transformN.x] = ChevalierNoir;
																				transformationNoir = 0;
																			}
																			if (xx < 50 && xx>0 && yy > 50 && y < 100)
																			{
																				board[transformN.y][transformN.x] = FouNOIR;
																				transformationNoir = 0;
																			}
																			if (transformationNoir == 0)
																			{
																				posRoiBlanc();
																				int h = RoiBlancJeuxEchecsVerif(roiBlanc.x, roiBlanc.y);
																				if (h == 0)
																				{
																					EchecsBLANC = 1;
																				}
																			}
																		}
																	}
																	if (board[y][x] != 0)
																	{
																		dx = pos.x - x * 100;
																		dy = pos.y - y * 100;
																		if (board[y][x] == PionNOIR && mutare == 1)
																		{
																			numarPiesaMutata = PionNOIR;
																			Mutare = PionNegru;
																			board[y][x] = 0;
																		}
																		if (board[y][x] == PionBLANC && mutare == 0)
																		{
																			numarPiesaMutata = PionBLANC;
																			Mutare = PionAlb;
																			board[y][x] = 0;
																		}
																		if (board[y][x] == TourNOIR && mutare == 1)
																		{
																			numarPiesaMutata = TourNOIR;
																			Mutare = TurnNegru;
																			board[y][x] = 0;

																		}
																		if (board[y][x] == TourBlanche && mutare == 0)
																		{
																			numarPiesaMutata = TourBlanche;
																			Mutare = TurnAlb;
																			board[y][x] = 0;

																		}
																		if (board[y][x] == ChevalierBlanc && mutare == 0)
																		{
																			numarPiesaMutata = ChevalierBlanc;
																			Mutare = CalAlb;
																			board[y][x] = 0;
																		}
																		if (board[y][x] == ChevalierNoir && mutare == 1)
																		{
																			numarPiesaMutata = ChevalierNoir;
																			Mutare = CalNegru;
																			board[y][x] = 0;
																		}
																		if (board[y][x] == FouNOIR && mutare == 1)
																		{
																			numarPiesaMutata = FouNOIR;
																			Mutare = NebunNegru;
																			board[y][x] = 0;
																		}
																		if (board[y][x] == FouBLANC && mutare == 0)
																		{
																			numarPiesaMutata = FouBLANC;
																			Mutare = NebunAlb;
																			board[y][x] = 0;
																		}
																		if (board[y][x] == ReineBLANCHE && mutare == 0)
																		{
																			numarPiesaMutata = ReineBLANCHE;
																			Mutare = ReginaAlb;
																			board[y][x] = 0;
																		}
																		if (board[y][x] == ReineNOIRE && mutare == 1)
																		{
																			numarPiesaMutata = ReineNOIRE;
																			Mutare = ReginaNegru;
																			board[y][x] = 0;
																		}
																		if (board[y][x] == RoiNOIRE && mutare == 1)
																		{
																			numarPiesaMutata = RoiNOIRE;
																			Mutare = RegeNegru;
																			board[y][x] = 0;
																		}
																		if (board[y][x] == RoiBLANC && mutare == 0)
																		{
																			numarPiesaMutata = RoiBLANC;
																			Mutare = RegeAlb;
																			board[y][x] = 0;
																		}
																		if (board[y][x] == 0)
																		{
																			mouvement = 1;
																			ancienPos.x = x;
																			ancienPos.y = y;
																		}
																	}
																}
															}

															if (saevent.type == Event::MouseButtonReleased)
															{
																if (saevent.key.code == Mouse::Left)
																{
																	int ok = 2;
																	if (numarPiesaMutata == PionBLANC && mouvement == 1)
																	{
																		ok = PionB(ancienPos.x, ancienPos.y, x, y);
																	}
																	if (numarPiesaMutata == PionNOIR && mouvement == 1)
																	{
																		ok = PionN(ancienPos.x, ancienPos.y, x, y);
																	}
																	if (numarPiesaMutata == TourBlanche && mouvement == 1)
																	{
																		ok = TourB(ancienPos.x, ancienPos.y, x, y);
																		if (ok == 1 && tourBlancGauche == 0 && ancienPos.y == 7 && ancienPos.x == 0)
																		{
																			tourBlancGauche = 1;

																		}
																		if (ok == 1 && tourBlancDroit == 0 && ancienPos.y == 7 && ancienPos.x == 7)
																		{
																			tourBlancDroit = 1;

																		}
																	}
																	if (numarPiesaMutata == TourNOIR && mouvement == 1)
																	{
																		ok = TourN(ancienPos.x, ancienPos.y, x, y);
																		if (ok == 1 && tourNoirDroit == 0 && ancienPos.y == 0 && ancienPos.x == 7)
																		{
																			tourNoirDroit = 1;

																		}
																		if (ok == 1 && tourNoirGauche == 0 && ancienPos.y == 0 && ancienPos.x == 0)
																		{
																			tourNoirGauche = 1;

																		}
																	}
																	if (numarPiesaMutata == FouBLANC && mouvement == 1)
																	{
																		ok = FouB(ancienPos.x, ancienPos.y, x, y);
																	}
																	if (numarPiesaMutata == FouNOIR && mouvement == 1)
																	{
																		ok = FouN(ancienPos.x, ancienPos.y, x, y);
																	}
																	if (numarPiesaMutata == ReineBLANCHE && mouvement == 1)
																	{
																		ok = ReineB(ancienPos.x, ancienPos.y, x, y);
																	}
																	if (numarPiesaMutata == ReineNOIRE && mouvement == 1)
																	{
																		ok = ReineN(ancienPos.x, ancienPos.y, x, y);
																	}
																	if (numarPiesaMutata == ChevalierBlanc && mouvement == 1)
																	{
																		ok = ChevalB(ancienPos.x, ancienPos.y, x, y);
																	}
																	if (numarPiesaMutata == ChevalierNoir && mouvement == 1)
																	{
																		ok = ChevalN(ancienPos.x, ancienPos.y, x, y);
																	}
																	if (numarPiesaMutata == RoiNOIRE && mouvement == 1)
																	{
																		ok = RoiN(ancienPos.x, ancienPos.y, x, y);
																		if (ok == 1 && roiNR == 0)
																		{
																			roiNR = 1;

																		}
																	}
																	if (numarPiesaMutata == RoiBLANC && mouvement == 1)
																	{
																		ok = RoiB(ancienPos.x, ancienPos.y, x, y);
																		if (ok == 1 && roiBLC == 0)
																		{
																			roiBLC = 1;

																		}
																	}
																	if (ok == 1)
																	{
																		int nr = board[y][x];
																		board[y][x] = numarPiesaMutata;
																		if (y == 0 && numarPiesaMutata == PionBLANC)
																		{
																			transformationBlanc = 1;
																			transformA.x = x;
																			transformA.y = y;
																			board[y][x] = 0;
																		}
																		if (y == 7 && numarPiesaMutata == PionNOIR)
																		{
																			transformationNoir = 1;
																			transformN.x = x;
																			transformN.y = y;
																			board[y][x] = 0;
																		}
																		if (mutare == 0) // blanc a bougé et noir suit
																		{
																			if (EchecsBLANC == 1)
																			{
																				posRoiBlanc();
																				int s = RoiBlancJeuxEchecsVerif(roiBlanc.x, roiBlanc.y);
																				if (s == 0)
																				{
																					board[ancienPos.y][ancienPos.x] = numarPiesaMutata;
																					board[y][x] = nr;
																				}
																				else
																				{
																					EchecsBLANC = 0;
																					posRoiNoir();
																					int sah = RoiNoirJeuxEchecsVerif(roiNoir.x, roiNoir.y);
																					if (sah == 0)
																					{
																						sahNegru = 1;
																					}
																					mutare = 1;
																				}
																			}
																			else
																			{
																				posRoiBlanc();
																				int sa = RoiBlancJeuxEchecsVerif(roiBlanc.x, roiBlanc.y);
																				if (sa == 0)
																				{
																					board[ancienPos.y][ancienPos.x] = numarPiesaMutata;
																					board[y][x] = nr;
																				}
																				else
																				{
																					posRoiNoir();
																					int sah = RoiNoirJeuxEchecsVerif(roiNoir.x, roiNoir.y);
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
																				posRoiNoir();
																				int s = RoiNoirJeuxEchecsVerif(roiNoir.x, roiNoir.y);
																				if (s == 0)
																				{
																					board[ancienPos.y][ancienPos.x] = numarPiesaMutata;
																					board[y][x] = nr;
																				}
																				else
																				{
																					sahNegru = 0;
																					posRoiBlanc();
																					int sah = RoiBlancJeuxEchecsVerif(roiBlanc.x, roiBlanc.y);
																					if (sah == 0)
																					{
																						EchecsBLANC = 1;
																					}
																					mutare = 0;
																				}
																			}
																			else
																			{
																				posRoiNoir();
																				int sa = RoiNoirJeuxEchecsVerif(roiNoir.x, roiNoir.y);
																				if (sa == 0)
																				{
																					board[ancienPos.y][ancienPos.x] = numarPiesaMutata;
																					board[y][x] = nr;
																				}
																				else
																				{
																					posRoiBlanc();
																					int sah = RoiBlancJeuxEchecsVerif(roiBlanc.x, roiBlanc.y);
																					if (sah == 0)
																					{
																						EchecsBLANC = 1;
																					}
																					mutare = 0;
																				}
																			}
																		}
																	}
																	else if (ok == 0)
																	{
																		board[ancienPos.y][ancienPos.x] = numarPiesaMutata;
																	}
																	mouvement = 0;
																}
															}
															if (saevent.type == Event::KeyPressed)
															{
																if (aevent.key.code == Keyboard::Escape)
																{
																	Plateaux.close();
																}
															}

														}

														

														Plateaux.draw(tabla);
														if (transformationBlanc == 1)
														{
															TransformareALB.setPosition(transformA.x* taille, transformA.y* taille);
															Plateaux.draw(TransformareALB);
														}
														if (transformationNoir == 1)
														{
															TransformareNEGRU.setPosition(transformN.x* taille, transformN.y* taille);
															Plateaux.draw(TransformareNEGRU);
														}
														if (mouvement == 1)
														{
															Mutare.setPosition(pos.x - dx, pos.y - dy);
															Plateaux.draw(Mutare);
														}
														for (int i = 0; i < LONGUEUR; i++)
														{
															for (int j = 0; j < LONGUEUR; j++)
															{

																if (board[i][j] != 0)
																{
																	if (board[i][j] == PionNOIR)
																	{
																		PionNegru.setPosition(j * taille, i * taille);
																		Plateaux.draw(PionNegru);
																	}
																	if (board[i][j] == PionBLANC)
																	{
																		PionAlb.setPosition(j * taille, i * taille);
																		Plateaux.draw(PionAlb);
																	}
																	if (board[i][j] == TourNOIR)
																	{
																		TurnNegru.setPosition(j * taille, i * taille);
																		Plateaux.draw(TurnNegru);

																	}
																	if (board[i][j] == TourBlanche)
																	{
																		TurnAlb.setPosition(j * taille, i * taille);
																		Plateaux.draw(TurnAlb);

																	}
																	if (board[i][j] == ChevalierBlanc)
																	{
																		CalAlb.setPosition(j * taille, i * taille);
																		Plateaux.draw(CalAlb);
																	}
																	if (board[i][j] == ChevalierNoir)
																	{
																		CalNegru.setPosition(j * taille, i * taille);
																		Plateaux.draw(CalNegru);
																	}
																	if (board[i][j] == FouNOIR)
																	{
																		NebunNegru.setPosition(j * taille, i * taille);
																		Plateaux.draw(NebunNegru);
																	}
																	if (board[i][j] == FouBLANC)
																	{
																		NebunAlb.setPosition(j * taille, i * taille);
																		Plateaux.draw(NebunAlb);
																	}
																	if (board[i][j] == ReineBLANCHE)
																	{
																		ReginaAlb.setPosition(j * taille, i * taille);
																		Plateaux.draw(ReginaAlb);
																	}
																	if (board[i][j] == ReineNOIRE)
																	{
																		ReginaNegru.setPosition(j * taille, i * taille);
																		Plateaux.draw(ReginaNegru);
																	}
																	if (board[i][j] == RoiNOIRE)
																	{
																		RegeNegru.setPosition(j * taille, i * taille);
																		Plateaux.draw(RegeNegru);
																	}
																	if (board[i][j] == RoiBLANC)
																	{
																		RegeAlb.setPosition(j * taille, i * taille);
																		Plateaux.draw(RegeAlb);
																	}
																}
															}
														}
														
														Plateaux.display();



														
													}
													Plateaux.close();
													
												}
											}
											if (aevent.mouseButton.x >= 343 && aevent.mouseButton.y >= 305)
											{
												if (aevent.mouseButton.x <= 623 && aevent.mouseButton.y <= 341)
												{
													Play.close();
													RenderWindow Multi(VideoMode(800, 800), "Multi");
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
													

													int choix;
													std::cout << "Host (1) - Client (2) ? ";
													std::cin >> choix;
													int idPartie;

													if (choix == 1)
													{
														idPartie = rand() % 100000;
														std::cout << "Id partie = " << idPartie << std::endl;
													}
													else
													{
														std::cout << "Saisir id partie a rejoindre : ";
														std::cin >> idPartie;
													}

													MQTTClient::getInstance()->subscribe("partie" + to_string(idPartie));


													while (Multi.isOpen())
													{

														Vector2i pos = Mouse::getPosition(Multi);
														x = pos.x / taille;
														y = pos.y / taille;

														Event saevent;
														while (Multi.pollEvent(saevent))
														{
															if (saevent.type == Event::Closed)
															{
																Multi.close();
															}
															if (saevent.type == Event::MouseButtonPressed)
															{

																if (saevent.mouseButton.button == Mouse::Left)
																{
																	if (transformationBlanc == 1)
																	{
																		if (pos.y >= transformA.y * taille && pos.y <= (transformA.y + 1) * taille && pos.x >= transformA.x * taille && pos.x <= (transformA.x + 1) * taille)
																		{
																			int xx = pos.x % 100, yy = pos.y % 100;

																			if (xx < 50 && yy < 50 && xx > 0 && yy > 0)
																			{
																				board[transformA.y][transformA.x] = TourBlanche;
																				transformationBlanc = 0;
																			}
																			if (xx > 50 && xx < 100 && yy < 50 && yy > 0)
																			{
																				board[transformA.y][transformA.x] = ReineBLANCHE;
																				transformationBlanc = 0;
																			}
																			if (xx > 50 && xx < 100 && yy>50 && yy < 100)
																			{
																				board[transformA.y][transformA.x] = ChevalierBlanc;
																				transformationBlanc = 0;
																			}
																			if (xx < 50 && xx>0 && yy > 50 && y < 100)
																			{
																				board[transformA.y][transformA.x] = FouBLANC;
																				transformationBlanc = 0;
																			}
																			if (transformationBlanc == 0)
																			{
																				posRoiNoir();
																				int h = RoiNoirJeuxEchecsVerif(roiNoir.x, roiNoir.y);
																				if (h == 0)
																				{
																					sahNegru = 1;
																				}
																			}
																		}
																	}
																	if (transformationNoir == 1)
																	{
																		if (pos.y >= transformN.y * taille && pos.y <= (transformN.y + 1) * taille && pos.x >= transformN.x * taille && pos.x <= (transformN.x + 1) * taille)
																		{
																			int xx = pos.x % 100, yy = pos.y % 100;

																			if (xx < 50 && yy < 50 && xx > 0 && yy > 0)
																			{
																				board[transformN.y][transformN.x] = TourNOIR;
																				transformationNoir = 0;
																			}
																			if (xx > 50 && xx < 100 && yy < 50 && yy > 0)
																			{
																				board[transformN.y][transformN.x] = ReineNOIRE;
																				transformationNoir = 0;
																			}
																			if (xx > 50 && xx < 100 && yy>50 && yy < 100)
																			{
																				board[transformN.y][transformN.x] = ChevalierNoir;
																				transformationNoir = 0;
																			}
																			if (xx < 50 && xx>0 && yy > 50 && y < 100)
																			{
																				board[transformN.y][transformN.x] = FouNOIR;
																				transformationNoir = 0;
																			}
																			if (transformationNoir == 0)
																			{
																				posRoiBlanc();
																				int h = RoiBlancJeuxEchecsVerif(roiBlanc.x, roiBlanc.y);
																				if (h == 0)
																				{
																					EchecsBLANC = 1;
																				}
																			}
																		}
																	}
																	if (board[y][x] != 0)
																	{
																		dx = pos.x - x * 100;
																		dy = pos.y - y * 100;
																		if (board[y][x] == PionNOIR && mutare == 1)
																		{
																			numarPiesaMutataMultiJugador = PionNOIR;
																			Mutare = PionNegru;
																			board[y][x] = 0;
																		}
																		if (board[y][x] == PionBLANC && mutare == 0)
																		{
																			numarPiesaMutataMultiJugador = PionBLANC;
																			Mutare = PionAlb;
																			board[y][x] = 0;
																		}
																		if (board[y][x] == TourNOIR && mutare == 1)
																		{
																			numarPiesaMutataMultiJugador = TourNOIR;
																			Mutare = TurnNegru;
																			board[y][x] = 0;

																		}
																		if (board[y][x] == TourBlanche && mutare == 0)
																		{
																			numarPiesaMutataMultiJugador = TourBlanche;
																			Mutare = TurnAlb;
																			board[y][x] = 0;

																		}
																		if (board[y][x] == ChevalierBlanc && mutare == 0)
																		{
																			numarPiesaMutataMultiJugador = ChevalierBlanc;
																			Mutare = CalAlb;
																			board[y][x] = 0;
																		}
																		if (board[y][x] == ChevalierNoir && mutare == 1)
																		{
																			numarPiesaMutataMultiJugador = ChevalierNoir;
																			Mutare = CalNegru;
																			board[y][x] = 0;
																		}
																		if (board[y][x] == FouNOIR && mutare == 1)
																		{
																			numarPiesaMutataMultiJugador = FouNOIR;
																			Mutare = NebunNegru;
																			board[y][x] = 0;
																		}
																		if (board[y][x] == FouBLANC && mutare == 0)
																		{
																			numarPiesaMutataMultiJugador = FouBLANC;
																			Mutare = NebunAlb;
																			board[y][x] = 0;
																		}
																		if (board[y][x] == ReineBLANCHE && mutare == 0)
																		{
																			numarPiesaMutataMultiJugador = ReineBLANCHE;
																			Mutare = ReginaAlb;
																			board[y][x] = 0;
																		}
																		if (board[y][x] == ReineNOIRE && mutare == 1)
																		{
																			numarPiesaMutataMultiJugador = ReineNOIRE;
																			Mutare = ReginaNegru;
																			board[y][x] = 0;
																		}
																		if (board[y][x] == RoiNOIRE && mutare == 1)
																		{
																			numarPiesaMutataMultiJugador = RoiNOIRE;
																			Mutare = RegeNegru;
																			board[y][x] = 0;
																		}
																		if (board[y][x] == RoiBLANC && mutare == 0)
																		{
																			numarPiesaMutataMultiJugador = RoiBLANC;
																			Mutare = RegeAlb;
																			board[y][x] = 0;
																		}
																		if (board[y][x] == 0)
																		{
																			mouvement = 1;
																			ancienPos.x = x;
																			ancienPos.y = y;
																		}
																	}
																}
															}

															if (saevent.type == Event::MouseButtonReleased)
															{
																if (saevent.key.code == Mouse::Left)
																{
																	int ok = 2;
																	if (numarPiesaMutataMultiJugador == PionBLANC && mouvement == 1)
																	{
																		ok = PionB(ancienPos.x, ancienPos.y, x, y);
																	}
																	if (numarPiesaMutataMultiJugador == PionNOIR && mouvement == 1)
																	{
																		ok = PionN(ancienPos.x, ancienPos.y, x, y);
																	}
																	if (numarPiesaMutataMultiJugador == TourBlanche && mouvement == 1)
																	{
																		ok = TourB(ancienPos.x, ancienPos.y, x, y);
																		if (ok == 1 && tourBlancGauche == 0 && ancienPos.y == 7 && ancienPos.x == 0)
																		{
																			tourBlancGauche = 1;

																		}
																		if (ok == 1 && tourBlancDroit == 0 && ancienPos.y == 7 && ancienPos.x == 7)
																		{
																			tourBlancDroit = 1;

																		}
																	}
																	if (numarPiesaMutataMultiJugador == TourNOIR && mouvement == 1)
																	{
																		ok = TourN(ancienPos.x, ancienPos.y, x, y);
																		if (ok == 1 && tourNoirDroit == 0 && ancienPos.y == 0 && ancienPos.x == 7)
																		{
																			tourNoirDroit = 1;

																		}
																		if (ok == 1 && tourNoirGauche == 0 && ancienPos.y == 0 && ancienPos.x == 0)
																		{
																			tourNoirGauche = 1;

																		}
																	}
																	if (numarPiesaMutataMultiJugador == FouBLANC && mouvement == 1)
																	{
																		ok = FouB(ancienPos.x, ancienPos.y, x, y);
																	}
																	if (numarPiesaMutataMultiJugador == FouNOIR && mouvement == 1)
																	{
																		ok = FouN(ancienPos.x, ancienPos.y, x, y);
																	}
																	if (numarPiesaMutataMultiJugador == ReineBLANCHE && mouvement == 1)
																	{
																		ok = ReineB(ancienPos.x, ancienPos.y, x, y);
																	}
																	if (numarPiesaMutataMultiJugador == ReineNOIRE && mouvement == 1)
																	{
																		ok = ReineN(ancienPos.x, ancienPos.y, x, y);
																	}
																	if (numarPiesaMutataMultiJugador == ChevalierBlanc && mouvement == 1)
																	{
																		ok = ChevalB(ancienPos.x, ancienPos.y, x, y);
																	}
																	if (numarPiesaMutataMultiJugador == ChevalierNoir && mouvement == 1)
																	{
																		ok = ChevalN(ancienPos.x, ancienPos.y, x, y);
																	}
																	if (numarPiesaMutataMultiJugador == RoiNOIRE && mouvement == 1)
																	{
																		ok = RoiN(ancienPos.x, ancienPos.y, x, y);
																		if (ok == 1 && roiNR == 0)
																		{
																			roiNR = 1;

																		}
																	}
																	if (numarPiesaMutataMultiJugador == RoiBLANC && mouvement == 1)
																	{
																		ok = RoiB(ancienPos.x, ancienPos.y, x, y);
																		if (ok == 1 && roiBLC == 0)
																		{
																			roiBLC = 1;

																		}
																	}
																	if (ok == 1)
																	{
																		int nr = board[y][x];
																		//board[y][x] = numarPiesaMutataMultiJugador;
																		std::string deplacement = std::to_string(ancienPos.x) + std::to_string(ancienPos.y) + std::to_string(x) + std::to_string(y);
																		std::string topic = "partie" + std::to_string(idPartie);
																		MQTTClient::getInstance()->sendMessage(topic, deplacement);
																		
																		if (y == 0 && numarPiesaMutataMultiJugador == PionBLANC)
																		{
																			transformationBlanc = 1;
																			transformA.x = x;
																			transformA.y = y;
																			//board[y][x] = 0;
																		}
																		if (y == 7 && numarPiesaMutataMultiJugador == PionNOIR)
																		{
																			transformationNoir = 1;
																			transformN.x = x;
																			transformN.y = y;
																			//board[y][x] = 0;
																		}
																		if (mutare == 0) // blanc a bougé et noir suit
																		{
																			if (EchecsBLANC == 1)
																			{
																				posRoiBlanc();
																				int s = RoiBlancJeuxEchecsVerif(roiBlanc.x, roiBlanc.y);
																				if (s == 0)
																				{
																					//board[ancienPos.y][ancienPos.x] = numarPiesaMutata;
																					//board[y][x] = nr;
																				}
																				else
																				{
																					EchecsBLANC = 0;
																					posRoiNoir();
																					int sah = RoiNoirJeuxEchecsVerif(roiNoir.x, roiNoir.y);
																					if (sah == 0)
																					{
																						sahNegru = 1;
																					}
																					//mutare = 1;
																				}
																			}
																			else
																			{
																				posRoiBlanc();
																				int sa = RoiBlancJeuxEchecsVerif(roiBlanc.x, roiBlanc.y);
																				if (sa == 0)
																				{
																					//board[ancienPos.y][ancienPos.x] = numarPiesaMutata;
																					//board[y][x] = nr;
																				}
																				else
																				{
																					posRoiNoir();
																					int sah = RoiNoirJeuxEchecsVerif(roiNoir.x, roiNoir.y);
																					if (sah == 0)
																					{
																						sahNegru = 1;
																					}
																					//mutare = 1;
																				}
																			}
																		}
																		else // le noir s'est déplacé et le blanc suit
																		{
																			if (sahNegru == 1)
																			{
																				posRoiNoir();
																				int s = RoiNoirJeuxEchecsVerif(roiNoir.x, roiNoir.y);
																				if (s == 0)
																				{
																					//board[ancienPos.y][ancienPos.x] = numarPiesaMutata;
																					//board[y][x] = nr;
																				}
																				else
																				{
																					sahNegru = 0;
																					posRoiBlanc();
																					int sah = RoiBlancJeuxEchecsVerif(roiBlanc.x, roiBlanc.y);
																					if (sah == 0)
																					{
																						EchecsBLANC = 1;
																					}
																					//mutare = 0;
																				}
																			}
																			else
																			{
																				posRoiNoir();
																				int sa = RoiNoirJeuxEchecsVerif(roiNoir.x, roiNoir.y);
																				if (sa == 0)
																				{
																					//board[ancienPos.y][ancienPos.x] = numarPiesaMutata;
																					//board[y][x] = nr;
																				}
																				else
																				{
																					posRoiBlanc();
																					int sah = RoiBlancJeuxEchecsVerif(roiBlanc.x, roiBlanc.y);
																					if (sah == 0)
																					{
																						EchecsBLANC = 1;
																					}
																					//mutare = 0;
																				}
																			}
																		}
																	}
																	else if (ok == 0)
																	{
																		board[ancienPos.y][ancienPos.x] = numarPiesaMutataMultiJugador;
																	}
																	mouvement = 0;
																}
															}

														}

														Multi.clear();

														MQTTClient::getInstance()->loopOnce();

														Multi.draw(tabla);
														if (transformationBlanc == 1)
														{
															TransformareALB.setPosition(transformA.x* taille, transformA.y* taille);
															Multi.draw(TransformareALB);
														}
														if (transformationNoir == 1)
														{
															TransformareNEGRU.setPosition(transformN.x* taille, transformN.y* taille);
															Multi.draw(TransformareNEGRU);
														}
														if (mouvement == 1)
														{
															Mutare.setPosition(pos.x - dx, pos.y - dy);
															Multi.draw(Mutare);
														}
														for (int i = 0; i < LONGUEUR; i++)
														{
															for (int j = 0; j < LONGUEUR; j++)
															{

																if (board[i][j] != 0)
																{
																	if (board[i][j] == PionNOIR)
																	{
																		PionNegru.setPosition(j * taille, i * taille);
																		Multi.draw(PionNegru);
																	}
																	if (board[i][j] == PionBLANC)
																	{
																		PionAlb.setPosition(j * taille, i * taille);
																		Multi.draw(PionAlb);
																	}
																	if (board[i][j] == TourNOIR)
																	{
																		TurnNegru.setPosition(j * taille, i * taille);
																		Multi.draw(TurnNegru);

																	}
																	if (board[i][j] == TourBlanche)
																	{
																		TurnAlb.setPosition(j * taille, i * taille);
																		Multi.draw(TurnAlb);

																	}
																	if (board[i][j] == ChevalierBlanc)
																	{
																		CalAlb.setPosition(j * taille, i * taille);
																		Multi.draw(CalAlb);
																	}
																	if (board[i][j] == ChevalierNoir)
																	{
																		CalNegru.setPosition(j * taille, i * taille);
																		Multi.draw(CalNegru);
																	}
																	if (board[i][j] == FouNOIR)
																	{
																		NebunNegru.setPosition(j * taille, i * taille);
																		Multi.draw(NebunNegru);
																	}
																	if (board[i][j] == FouBLANC)
																	{
																		NebunAlb.setPosition(j * taille, i * taille);
																		Multi.draw(NebunAlb);
																	}
																	if (board[i][j] == ReineBLANCHE)
																	{
																		ReginaAlb.setPosition(j * taille, i * taille);
																		Multi.draw(ReginaAlb);
																	}
																	if (board[i][j] == ReineNOIRE)
																	{
																		ReginaNegru.setPosition(j * taille, i * taille);
																		Multi.draw(ReginaNegru);
																	}
																	if (board[i][j] == RoiNOIRE)
																	{
																		RegeNegru.setPosition(j * taille, i * taille);
																		Multi.draw(RegeNegru);
																	}
																	if (board[i][j] == RoiBLANC)
																	{
																		RegeAlb.setPosition(j * taille, i * taille);
																		Multi.draw(RegeAlb);
																	}
																}
															}
														}
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

							Option Option(Options.getSize().x, Options.getSize().y);

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

								Option.draw(Options);

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