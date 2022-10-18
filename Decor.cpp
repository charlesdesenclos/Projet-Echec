#include "Decor.h"

Decor::Decor(int x, int y)
{

}

Decor::~Decor()
{

}

int Decor::PionB(int ox, int oy, int nx, int ny)
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

int Decor::PionN(int ox, int oy, int nx, int ny)
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

int Decor::TourB(int ox, int oy, int nx, int ny)
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

int Decor::TourN(int ox, int oy, int nx, int ny)
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

int Decor::FouB(int ox, int oy, int nx, int ny)
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

int Decor::FouN(int ox, int oy, int nx, int ny)
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

int Decor::ReineB(int ox, int oy, int nx, int ny)
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

int Decor::ReineN(int ox, int oy, int nx, int ny)
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

int Decor::ChevalB(int ox, int oy, int nx, int ny)
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

int Decor::ChevalN(int ox, int oy, int nx, int ny)
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


int Decor::PionBJeuxEchecs(int posx, int posy, int roix, int roiy)
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

int Decor::TourBJeuxEchecs(int ox, int oy, int roix, int roiy)
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

int Decor::FouBJeuxEchecs(int ox, int oy, int roix, int roiy)
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

int Decor::ReinneBJeuxEchecs(int ox, int oy, int roix, int roiy)
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

int Decor::ChevalBJeuxEchecs(int ox, int oy, int roix, int roiy)
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

int Decor::RoiBJeuxEchecs(int ox, int oy, int roix, int roiy)
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


int Decor::PionNJeuxEchecs(int ox, int oy, int roix, int roiy)
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

int Decor::TourNJeuxEchecs(int ox, int oy, int roix, int roiy)
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

int Decor::FouNJeuxEchecs(int ox, int oy, int roix, int roiy)
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

int Decor::ReinneNJeuxEchecs(int ox, int oy, int roix, int roiy)
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

int Decor::ChevalNJeuxEchecs(int ox, int oy, int roix, int roiy)
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

int Decor::RoiNJeuxEchecs(int ox, int oy, int roix, int roiy)
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



int Decor::RoiNoirJeuxEchecsVerif(int posRoix, int posRoiy)
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

int Decor::RoiN(int ox, int oy, int nx, int ny)
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


int Decor::RoiBlancJeuxEchecsVerif(int posRoix, int posRoiy)
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

int Decor::RoiB(int ox, int oy, int nx, int ny)
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


void Decor::posRoiBlanc()
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

void Decor::posRoiNoir()
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
