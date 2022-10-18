#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

class Decor
{
public:
	Decor(int x, int y);
	~Decor();


	int PionB(int ox, int oy, int nx, int ny);

	int PionN(int ox, int oy, int nx, int ny);

	int TourB(int ox, int oy, int nx, int ny);

	int TourN(int ox, int oy, int nx, int ny);

	int FouB(int ox, int oy, int nx, int ny);

	int FouN(int ox, int oy, int nx, int ny);

	int ReineB(int ox, int oy, int nx, int ny);

	int ReineN(int ox, int oy, int nx, int ny);

	int ChevalB(int ox, int oy, int nx, int ny);

	int ChevalN(int ox, int oy, int nx, int ny);

	int PionBJeuxEchecs(int posx, int posy, int regex, int regey);

	int TourBJeuxEchecs(int ox, int oy, int regex, int regey);

	int FouBJeuxEchecs(int ox, int oy, int regex, int regey);

	int ReinneBJeuxEchecs(int ox, int oy, int regex, int regey);

	int ChevalBJeuxEchecs(int ox, int oy, int regex, int regey);

	int RoiBJeuxEchecs(int ox, int oy, int regex, int regey);

	int PionNJeuxEchecs(int ox, int oy, int regex, int regey);

	int TourNJeuxEchecs(int ox, int oy, int regex, int regey);

	int FouNJeuxEchecs(int ox, int oy, int regex, int regey);

	int ReinneNJeuxEchecs(int ox, int oy, int regex, int regey);

	int ChevalNJeuxEchecs(int ox, int oy, int regex, int regey);

	int RoiNJeuxEchecs(int ox, int oy, int regex, int regey);

	int RoiNoirJeuxEchecsVerif(int posRegex, int posRegey);

	int RoiN(int ox, int oy, int nx, int ny);

	int RoiBlancJeuxEchecsVerif(int posRegex, int posRegey);

	int RoiB(int ox, int oy, int nx, int ny);

	void posRoiBlanc();

	void posRoiNoir();


private:

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

	int tourBlancDroit = 0, tourBlancGauche = 0, roiBLC = 0;
	int tourNoirDroit = 0, tourNoirGauche = 0, roiNR = 0;

};