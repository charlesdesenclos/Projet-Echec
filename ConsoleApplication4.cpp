#include <stdio.h>
#include <malloc.h>
#include <limits.h>
#include <windows.h>

/*------------------*/
/*    PRE-PROCESSEUR    */
/*------------------*/

#define N 8

#define NBTOUR 28*2 /* Contient le nombre max de déplacement d'une piece, *2 car le tableau contient x et y */ 
#define NBCHEVAL 8*2 
#define NBFOU 28*2 
#define NBDAME 56*2 
#define NBROI 8*2
#define NBPION 4*2

#define RECU 4

/*----------------------*/
/*    VARIABLES GLOBALES    */
/*----------------------*/

enum ls_piece {
	VIDE,
	BPION, BTOUR, BCHEVAL, BFOU, BDAME, BROI,
	NPION, NTOUR, NCHEVAL, NFOU, NDAME, NROI
};

int dept[NBTOUR]; /* Contient tous les déplacements possibles d'une piece */
int depc[NBCHEVAL];
int depf[NBFOU];
int depd[NBDAME];
int depr[NBROI];
int deppn[NBPION];
int deppb[NBPION];

int echecn; /* echecn={0,1} si echec ou pas */

/*--------------*/
/*    FONCTIONS    */    /* Fonction s'apellant l'une l'autre */
/*--------------*/

int coup(int cases[N][N], int tour);
int coup2(int cases[N][N], int tour);
int coup3(int cases[N][N], int tour);

/*--------------*/
/*    CASES_INIT    */    /* Initialise l'échiquier */
/*--------------*/

void cases_init(int cases[N][N])
{
	int i, j;

	for (i = 0; i < N; i++)
	{
		cases[1][i] = NPION;
		cases[6][i] = BPION;
	}
	for (i = 2; i <= 5; i++)
	{
		for (j = 0; j < N; j++)
			cases[i][j] = VIDE;
	}
	cases[0][0] = NTOUR;
	cases[0][1] = NCHEVAL;
	cases[0][2] = NFOU;
	cases[0][3] = NDAME;
	cases[0][4] = NROI;
	cases[0][5] = NFOU;
	cases[0][6] = NCHEVAL;
	cases[0][7] = NTOUR;
	cases[7][0] = BTOUR;
	cases[7][1] = BCHEVAL;
	cases[7][2] = BFOU;
	cases[7][3] = BDAME;
	cases[7][4] = BROI;
	cases[7][5] = BFOU;
	cases[7][6] = BCHEVAL;
	cases[7][7] = BTOUR;

	return;
}

/*--------------*/
/*    CASES_SPE    */    /* Pour la transformation de %d de ls_pieces en %c ex VIDE -> . */
/*--------------*/

char cases_spe(int x)
{
	if (x == 0)
		return '.';
	if (x == 1)
		return 'P';
	if (x == 2)
		return 'T';
	if (x == 3)
		return 'C';
	if (x == 4)
		return 'F';
	if (x == 5)
		return 'D';
	if (x == 6)
		return 'R';
	if (x == 7)
		return 'p';
	if (x == 8)
		return 't';
	if (x == 9)
		return 'c';
	if (x == 10)
		return 'f';
	if (x == 11)
		return 'd';
	if (x == 12)
		return 'r';

	return -1;
}

/*------------------*/
/*    CASES_AFFICHE    */    /* Affiche l'échiquier */
/*------------------*/

void cases_affiche(int cases[N][N])
{
	int i, j;

	for (i = 0; i < N; i++)
		printf(" -");
	printf("\n");
	for (i = 0; i < N; i++)
	{
		printf("|");
		for (j = 0; j < N; j++)
			printf("%c ", cases_spe(cases[i][j]));
		printf("| %d", i);
		printf("\n");
	}
	for (i = 0; i < N; i++)
		printf(" -");
	printf("\n");
	for (i = 0; i < N; i++)
		printf(" %d", i);
	system("pause");
	printf("\n\n");
	return;
}

/*--------------*/
/*    DEP_CHEVAL    */ /* Initialise les deplacements du cheval */
/*--------------*/

void dep_cheval()
{
	depc[0] = -2;
	depc[1] = 1;
	depc[2] = -1;
	depc[3] = 2;
	depc[4] = 1;
	depc[5] = 2;
	depc[6] = 2;
	depc[7] = 1;
	depc[8] = 2;
	depc[9] = -1;
	depc[10] = 1;
	depc[11] = -2;
	depc[12] = -1;
	depc[13] = -2;
	depc[14] = -2;
	depc[15] = -1;

	return;
}

/*--------------*/
/*    DEP_TOUR    */ /* Initialise les deplacements de la tour */
/*--------------*/

void dep_tour()
{
	int i, n = 0;

	for (i = 1; i < N; i++)
	{
		dept[n++] = -i;    /* Deplacement vers le nord */
		dept[n++] = 0;
		dept[n++] = i;    /* Deplacement vers le sud */
		dept[n++] = 0;
		dept[n++] = 0;    /* Deplacement vers l'est */
		dept[n++] = i;
		dept[n++] = 0;    /* Deplacement vers l'ouest */
		dept[n++] = -i;
	}

	return;
}

/*--------------*/
/*    DEP_FOU        */    /* Initialise les deplacements du fou */
/*--------------*/

void dep_fou()
{
	int i, n = 0;

	for (i = 1; i < N; i++)
	{
		depf[n++] = -i; /* Deplacement vers les nord-est */
		depf[n++] = i;
		depf[n++] = i; /* Deplacement vers les sud-est */
		depf[n++] = i;
		depf[n++] = i; /* Deplacement vers les sud-ouest */
		depf[n++] = -i;
		depf[n++] = -i; /* Deplacement vers les nord-ouest */
		depf[n++] = -i;
	}
	return;
}

/*--------------*/
/*    DEP_DAME    */ /* Initialise les deplacements de la dame */
/*--------------*/

void dep_dame()
{
	int i, n = 0;

	for (i = 1; i < N; i++)
	{
		depd[n++] = -i; /* Deplacement vers les nord-est */    /* Deplacement du fou */
		depd[n++] = i;
		depd[n++] = i; /* Deplacement vers les sud-est */
		depd[n++] = i;
		depd[n++] = i; /* Deplacement vers les sud-ouest */
		depd[n++] = -i;
		depd[n++] = -i; /* Deplacement vers les nord-ouest */
		depd[n++] = -i;

		depd[n++] = -i;    /* Deplacement vers le nord */        /* Deplacement de la tour */
		depd[n++] = 0;
		depd[n++] = 0;    /* Deplacement vers l'est */
		depd[n++] = i;
		depd[n++] = 0;    /* Deplacement vers l'ouest */
		depd[n++] = -i;
	}

	return;
}

/*--------------*/
/*    DEP_ROI        */ /* Initialise les deplacements du roi */
/*--------------*/

void dep_roi()
{
	depr[0] = -1;
	depr[1] = 0;
	depr[2] = -1;
	depr[3] = 1;
	depr[4] = 0;
	depr[5] = 1;
	depr[6] = 1;
	depr[7] = 1;
	depr[8] = 1;
	depr[9] = 0;
	depr[10] = 1;
	depr[11] = -1;
	depr[12] = 0;
	depr[13] = -1;
	depr[14] = -1;
	depr[15] = -1;

	return;
}

/*--------------*/
/*    DEP_PIONN    */ /* Initialise les deplacements du pion noir */
/*--------------*/

void dep_pionn()
{
	deppn[0] = 1;
	deppn[1] = 0;
	deppn[2] = 1;
	deppn[3] = -1;
	deppn[4] = 1;
	deppn[5] = 1;
	deppn[6] = 2;
	deppn[7] = 0;

	return;
}

/*--------------*/
/*    DEP_PIONB    */ /* Initialise les deplacements du pion blanc */
/*--------------*/

void dep_pionb()
{
	deppb[0] = -1;
	deppb[1] = 0;
	deppb[2] = -1;
	deppb[3] = -1;
	deppb[4] = -1;
	deppb[5] = 1;
	deppb[6] = -2;
	deppb[7] = 0;

	return;
}

/*--------------*/
/*    DEP_INIT    */    /* On initialise les déplacements de chaque pion */
/*--------------*/

void deplacement_init()
{
	dep_cheval();
	dep_tour();
	dep_fou();
	dep_dame();
	dep_roi();
	dep_pionn();
	dep_pionb();
	return;
}

/*----------*/
/*    VIDE    */    /* Test si une case est vide */
/*----------*/

int vide(int cases[N][N], int x, int y)
{
	return (cases[x][y] == VIDE);
}

/*----------*/
/*    TESTPN    */    /* Test si le pion n'a pas commis d'erreur lors de son deplacement */
/*----------*/

int testpn(int cases[N][N], int x, int y, int a, int b)
{
	int m = x - a, n = y - b; /* m et n : valeur du deplacement joué */


	if (m == 1)
	{
		if (n == 0) /* Si le déplacement est tout droit on regarde si la case est vide */
		{
			if (cases[x][y] != VIDE)
				return 0;
			else
				return 1;
		}
		else /* Deplacement on diagonale, on teste s'il y a qqch a manger */
		{
			if (cases[x][y] == BPION || cases[x][y] == BTOUR || cases[x][y] == BCHEVAL ||
				cases[x][y] == BFOU || cases[x][y] == BDAME || cases[x][y] == BROI)
				return 1;
			else return 0;
		}
	}

	else    /* Si le déplacement est un +2,0 alors on teste si la case sautée est vide et la case d'arrivée */
	{

		return(a == 1 && vide(cases, x, y) && vide(cases, x + 1, y));
	}
}

/*----------*/
/*    TESTB    */    /* Test si le pion n'a pas commis d'erreur lors de son deplacement */
/*----------*/

int testpb(int cases[N][N], int x, int y, int a, int b)
{

	int m = x - a, n = y - b; /* m et n : valeur du deplacement joué */
	if (m == -1)
	{
		if (n == 0) /* Si le déplacement est tout droit on regarde si la case est vide */
		{
			if (cases[x][y] != VIDE)
				return 0;
			else
				return 1;
		}
		else /* Deplacement on diagonale, on teste s'il y a qqch a manger */
		{
			if (cases[x][y] == NPION || cases[x][y] == NTOUR || cases[x][y] == NCHEVAL ||
				cases[x][y] == NBFOU || cases[x][y] == NDAME || cases[x][y] == NROI)
				return 1;
			else return 0;
		}
	}

	else    /* Si le déplacement est un +2,0 alors on teste si la case sautée est vide et la case d'arrivée */
		return(a == 6 && vide(cases, x, y) && vide(cases, x - 1, y));
}

/*----------*/
/*    TESTT    */    /* Test si la tour n'a pas commis d'erreur lors de son deplacement */
/*----------*/

int testt(int cases[N][N], int x, int y, int a, int b)
{
	int m = x - a, n = y - b; /* m et n : valeur du deplacement joué */
	int i;

	if (m > 0) /* Deplacement vers le sud */
	{
		for (i = a + 1; i < x; i++)
		{
			if (!vide(cases, i, b))
				return 0;
		}
	}
	else if (m < 0) /* Deplacement vers le nord */
	{
		for (i = a - 1; i > x; i--)
		{
			if (!vide(cases, i, b))
				return 0;
		}
	}
	else if (n > 0) /* Deplacement vers l'est */
	{
		for (i = b + 1; i < y; i++)
		{
			if (!vide(cases, a, i))
				return 0;
		}
	}
	else if (n < 0) /* Deplacement vers l'ouest */
	{
		for (i = b - 1; i > y; i--)
		{
			if (!vide(cases, a, i))
				return 0;
		}
	}

	return 1;
}

/*----------*/
/*    TESTF    */    /* Test si le fou n'a pas commis d'erreur lors de son deplacement */
/*----------*/

int testf(int cases[N][N], int x, int y, int a, int b)
{

	int m = x - a, n = y - b; /* m et n : valeur du deplacement joué */
	int i;

	if (m < 0 && n>0) /* Deplacement vers le nord-est */
	{
		for (i = 1; i < n; i++)
		{
			if (!vide(cases, a - i, b + i))
				return 0;
		}
	}
	else if (m > 0 && n > 0) /* Deplacement vers le sud-est */
	{
		for (i = 1; i < n; i++)
		{
			if (!vide(cases, a + i, b + i))
				return 0;
		}
	}
	else if (m > 0 && n < 0) /* Deplacement vers le sud-ouest */
	{
		for (i = 1; i < -n; i++)
		{
			if (!vide(cases, a + i, b - i))
				return 0;
		}
	}
	else if (m < 0 && n < 0) /* Deplacement vers le nord-ouest */
	{
		for (i = 1; i < -n; i++)
		{
			if (!vide(cases, a - i, b - i))
				return 0;
		}
	}

	return 1;
}

/*----------*/
/*    TESTD    */    /* Test si la dame n'a pas commis d'erreur lors de son deplacement */
/*----------*/

int testd(int cases[N][N], int x, int y, int a, int b)
{
	int m = x - a, n = y - b; /* m et n : valeur du deplacement joué */
	int i;

	if (m > 0 && n == 0) /* Deplacement vers le sud */
	{
		for (i = a + 1; i < x; i++)
		{
			if (!vide(cases, i, b))
				return 0;
		}
	}
	else if (m < 0 && n == 0) /* Deplacement vers le nord */
	{
		for (i = a - 1; i > x; i--)
		{
			if (!vide(cases, i, b))
				return 0;
		}
	}
	else if (n > 0 && m == 0) /* Deplacement vers l'est */
	{
		for (i = b + 1; i < y; i++)
		{
			if (!vide(cases, a, i))
				return 0;
		}
	}
	else if (n < 0 && m == 0) /* Deplacement vers l'ouest */
	{
		for (i = b - 1; i > y; i--)
		{
			if (!vide(cases, a, i))
				return 0;
		}
	}
	else if (m < 0 && n>0) /* Deplacement vers le nord-est */
	{
		for (i = 1; i < n; i++)
		{
			if (!vide(cases, a - i, b + i))
				return 0;
		}
	}
	else if (m > 0 && n > 0) /* Deplacement vers le sud-est */
	{
		for (i = 1; i < n; i++)
		{
			if (!vide(cases, a + i, b + i))
				return 0;
		}
	}
	else if (m > 0 && n < 0) /* Deplacement vers le sud-ouest */
	{
		for (i = 1; i < -n; i++)
		{
			if (!vide(cases, a + i, b - i))
				return 0;
		}
	}
	else if (m < 0 && n < 0) /* Deplacement vers le nord-ouest */
	{
		for (i = 1; i < -n; i++)
		{
			if (!vide(cases, a - i, b - i))
				return 0;
		}
	}


	return 1;
}
/*----------*/
/*    TEST    */    /* Test si le coup joué est valide */
/*----------*/

int test(int cases[N][N], int x, int y, int a, int b) /* (x,y) : coup joué, (a,b) : piece en mouvement */
{
	int cible = cases[x][y]; /* cible : valeur de la case cible */
	int pion = cases[a][b]; /* pion : valeur du pion en mouvement */

	/* Test si le coup joué n'est pas en dehors de l'échiquier */
	if (x >= N || x < 0 || y >= N || y < 0)
		return 0;

	/* Test si le coup joué n'atterit pas sur pion de la même équipe */
	if (pion == NPION || pion == NTOUR || pion == NCHEVAL || pion == NFOU || pion == NDAME || pion == NROI)
	{
		if (cible == NPION || cible == NTOUR || cible == NCHEVAL || cible == NFOU || cible == NDAME || cible == NROI)
			return 0;
	}
	if (pion == BPION || pion == BTOUR || pion == BCHEVAL || pion == BFOU || pion == BDAME || pion == BROI)
	{
		if (cible == BPION || cible == BTOUR || cible == BCHEVAL || cible == BFOU || cible == BDAME || cible == BROI)
			return 0;
	}

	if (pion == NPION)
		return(testpn(cases, x, y, a, b));
	else if (pion == BPION)
		return(testpb(cases, x, y, a, b));
	else if (pion == NTOUR || pion == BTOUR)
		return(testt(cases, x, y, a, b));
	else if (pion == NFOU || pion == BFOU)
		return(testf(cases, x, y, a, b));
	else if (pion == NDAME || pion == BDAME)
		return(testd(cases, x, y, a, b));
	else
		return 1;
}

/*----------*/
/*    DEPLACE    */    /* DEPLACE (a,b) vers (x,y) sur un plateau cases */
/*----------*/

void deplace(int x, int y, int a, int b, int cases[N][N])
{
	int piece;

	piece = cases[a][b];
	cases[a][b] = VIDE;

	cases[x][y] = piece;

	return;
}

/*----------*/
/*    COUPADV    */    /* Coup de l'adversaire */
/*----------*/

void coupadv(int cases[N][N])
{
	char jeu[2];
	int a, b, x, y;

	printf("> ");
	fflush(stdin);
	fgets(jeu, 3, stdin);
	a = (int)(jeu[0]) - 48;
	b = (int)(jeu[1]) - 48;

	printf("> ");
	fflush(stdin);
	fgets(jeu, 3, stdin);
	x = (int)(jeu[0]) - 48;
	y = (int)(jeu[1]) - 48;

	deplace(x, y, a, b, cases);

	printf("\n");

	return;
}

/*----------*/
/*    VALEUR    */    /* Calcule la valeur du plateau (+,-) : avantageux ou pas */
/*----------*/

int valeur(int cases[N][N])
{
	int i, j, piece, valeur = 0;
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
		{
			piece = cases[i][j];

			if (piece == BPION)
				valeur -= 1;
			else if (piece == NPION)
				valeur += 1;
			else if (piece == BTOUR)
				valeur -= 5;
			else if (piece == NTOUR)
				valeur += 5;
			else if (piece == BCHEVAL)
				valeur -= 3;
			else if (piece == NCHEVAL)
				valeur += 3;
			else if (piece == BFOU)
				valeur -= 3;
			else if (piece == NFOU)
				valeur += 3;
			else if (piece == BDAME)
				valeur -= 10;
			else if (piece == NDAME)
				valeur += 10;
		}
	}

	return valeur;
}

/*--------------*/
/*    COPY_CASES    */    /* Copie un échiquier vers un autre */
/*--------------*/

void copy_cases(int cases[N][N], int cases2[N][N])
{
	int i, j;

	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
			cases2[i][j] = cases[i][j];
	}

	return;

}

/*----------*/
/*    ANALYSE    */    /* Analyse une position donné en prenant un parametre notament le numéro du coup a jouer (k) */
/*----------*/    /* Renvoie la valeur du coup joué */

int analyse(int cases[N][N], int cases2[N][N], int i, int j, int k)
{
	int temp;

	if (cases[i][j] == NPION)
	{
		if (test(cases, deppn[k] + i, deppn[k + 1] + j, i, j))
		{
			deplace(deppn[k] + i, deppn[k + 1] + j, i, j, cases2);
			temp = valeur(cases2);
			copy_cases(cases, cases2);
			return temp;
		}
	}
	if (cases[i][j] == BPION)
	{
		if (test(cases, deppb[k] + i, deppb[k + 1] + j, i, j))
		{
			deplace(deppb[k] + i, deppb[k + 1] + j, i, j, cases2);
			temp = valeur(cases2);
			copy_cases(cases, cases2);
			return temp;
		}
	}
	else if (cases[i][j] == NTOUR || cases[i][j] == BTOUR)
	{
		if (test(cases, dept[k] + i, dept[k + 1] + j, i, j))
		{
			deplace(dept[k] + i, dept[k + 1] + j, i, j, cases2);
			temp = valeur(cases2);
			copy_cases(cases, cases2);
			return temp;
		}
	}
	else if (cases[i][j] == NCHEVAL || cases[i][j] == BCHEVAL)
	{
		if (test(cases, depc[k] + i, depc[k + 1] + j, i, j))
		{
			deplace(depc[k] + i, depc[k + 1] + j, i, j, cases2);
			temp = valeur(cases2);
			copy_cases(cases, cases2);
			return temp;
		}
	}
	else if (cases[i][j] == NFOU || cases[i][j] == BFOU)
	{
		if (test(cases, depf[k] + i, depf[k + 1] + j, i, j))
		{
			deplace(depf[k] + i, depf[k + 1] + j, i, j, cases2);
			temp = valeur(cases2);
			copy_cases(cases, cases2);
			return temp;
		}
	}
	else if (cases[i][j] == NDAME || cases[i][j] == BDAME)
	{
		if (test(cases, depd[k] + i, depd[k + 1] + j, i, j))
		{
			deplace(depd[k] + i, depd[k + 1] + j, i, j, cases2);
			temp = valeur(cases2);
			copy_cases(cases, cases2);
			return temp;
		}
	}
	else if (cases[i][j] == NROI || cases[i][j] == BROI)
	{
		if (test(cases, depr[k] + i, depr[k + 1] + j, i, j))
		{
			deplace(depr[k] + i, depr[k + 1] + j, i, j, cases2);
			temp = valeur(cases2);
			copy_cases(cases, cases2);
			return temp;
		}
	}
	if (cases[i][j] == NPION || cases[i][j] == NTOUR || cases[i][j] == NCHEVAL || cases[i][j] == NFOU || cases[i][j] == NDAME || cases[i][j] == NROI)
		return INT_MIN;
	else
		return INT_MAX;
}

/*----------*/
/*    COUP    */    /* Coup de l'ordi avec listage des pions, test du coup et création de la valeur max (meilleur coup) */
/*----------*/

int coup(int cases[N][N], int tour)
{
	int i, j, k, piece, max = INT_MIN, temp, coup1x, coup1y, coup2x, coup2y; /* coupn(x,y) contient le meilleur coup a réaliser*/
	int cases2[N][N]; /* Contient le second tableau modifié par un coup temporaire */

	copy_cases(cases, cases2);
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
		{
			piece = cases[i][j];
			if (piece == NPION)
			{
				for (k = 0; k < NBPION; k += 2)
				{
					if (test(cases, deppn[k] + i, deppn[k + 1] + j, i, j))
					{
						deplace(deppn[k] + i, deppn[k + 1] + j, i, j, cases2);
						temp = coup2(cases2, tour + 1);
						copy_cases(cases, cases2);
					}
					else
						temp = INT_MIN;
					if (temp >= max)
					{
						coup1x = i;
						coup1y = j;
						coup2x = deppn[k];
						coup2y = deppn[k + 1];
						max = temp;
					}
				}
			}
			else if (piece == NTOUR)
			{

				for (k = 0; k < NBTOUR; k += 2)
				{
					if (test(cases, dept[k] + i, dept[k + 1] + j, i, j))
					{
						deplace(dept[k] + i, dept[k + 1] + j, i, j, cases2);
						temp = coup2(cases2, tour + 1);
						copy_cases(cases, cases2);
					}
					else
						temp = INT_MIN;
					if (temp >= max)
					{
						coup1x = i;
						coup1y = j;
						coup2x = dept[k];
						coup2y = dept[k + 1];
						max = temp;
					}

				}
			}
			else if (piece == NCHEVAL)
			{
				for (k = 0; k < NBCHEVAL; k += 2)
				{

					if (test(cases, depc[k] + i, depc[k + 1] + j, i, j))
					{
						deplace(depc[k] + i, depc[k + 1] + j, i, j, cases2);
						temp = coup2(cases2, tour + 1);
						copy_cases(cases, cases2);
					}
					else
						temp = INT_MIN;
					if (temp >= max)
					{
						coup1x = i;
						coup1y = j;
						coup2x = depc[k];
						coup2y = depc[k + 1];
						max = temp;
					}
				}
			}
			else if (piece == NFOU)
			{
				for (k = 0; k < NBFOU; k += 2)
				{

					if (test(cases, depf[k] + i, depf[k + 1] + j, i, j))
					{
						deplace(depf[k] + i, depf[k + 1] + j, i, j, cases2);
						temp = coup2(cases2, tour + 1);
						copy_cases(cases, cases2);
					}
					else
						temp = INT_MIN;
					if (temp >= max)
					{
						coup1x = i;
						coup1y = j;
						coup2x = depf[k];
						coup2y = depf[k + 1];
						max = temp;
					}
				}
			}
			else if (piece == NDAME)
			{
				for (k = 0; k < NBDAME; k += 2)
				{
					if (test(cases, depd[k] + i, depd[k + 1] + j, i, j))
					{
						deplace(depd[k] + i, depd[k + 1] + j, i, j, cases2);
						temp = coup2(cases2, tour + 1);
						copy_cases(cases, cases2);
					}
					else
						temp = INT_MIN;
					if (temp >= max)
					{
						coup1x = i;
						coup1y = j;
						coup2x = depd[k];
						coup2y = depd[k + 1];
						max = temp;
					}
				}
			}
			else if (piece == NROI)
			{
				for (k = 0; k < NBROI; k += 2)
				{
					if (test(cases, depr[k] + i, depr[k + 1] + j, i, j))
					{
						deplace(depr[k] + i, depr[k + 1] + j, i, j, cases2);
						temp = coup2(cases2, tour + 1);
						copy_cases(cases, cases2);
					}
					else
						temp = INT_MIN;
					if (temp >= max)
					{
						coup1x = i;
						coup1y = j;
						coup2x = depr[k];
						coup2y = depr[k + 1];
						max = temp;
					}
				}
			}

		}
	}
	deplace(coup1x + coup2x, coup1y + coup2y, coup1x, coup1y, cases);

	return 0;
}

/*----------*/
/*    COUP2    */    /* Coup de l'humain avec listage des pions, test du coup et création de la valeur max (meilleur coup) */
/*----------*/

int coup2(int cases[N][N], int tour)
{
	int i, j, k, piece, min = INT_MAX, temp; /* coupn(x,y) contient le meilleur coup a réaliser*/
	int cases2[N][N]; /* Contient le second tableau modifié par un coup temporaire */

	copy_cases(cases, cases2);
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
		{

			piece = cases[i][j];
			if (piece == BPION)
			{
				for (k = 0; k < NBPION; k += 2)
				{
					if (tour == RECU)
						temp = analyse(cases, cases2, i, j, k);
					else
					{
						if (test(cases, deppb[k] + i, deppb[k + 1] + j, i, j))
						{
							deplace(deppb[k] + i, deppb[k + 1] + j, i, j, cases2);
							temp = coup3(cases2, tour + 1);
							copy_cases(cases, cases2);
						}
						else
							temp = INT_MAX;
					}
					if (temp < min)
						min = temp;
				}
			}
			else if (piece == BTOUR)
			{

				for (k = 0; k < NBTOUR; k += 2)
				{
					if (tour == RECU)
						temp = analyse(cases, cases2, i, j, k);
					else
					{
						if (test(cases, dept[k] + i, dept[k + 1] + j, i, j))
						{
							deplace(dept[k] + i, dept[k + 1] + j, i, j, cases2);
							temp = coup3(cases2, tour + 1);
							copy_cases(cases, cases2);
						}
						else
							temp = INT_MAX;
					}
					if (temp < min)
						min = temp;

				}
			}
			else if (piece == BCHEVAL)
			{
				for (k = 0; k < NBCHEVAL; k += 2)
				{
					if (tour == RECU)
						temp = analyse(cases, cases2, i, j, k);
					else
					{
						if (test(cases, depc[k] + i, depc[k + 1] + j, i, j))
						{
							deplace(depc[k] + i, depc[k + 1] + j, i, j, cases2);
							temp = coup3(cases2, tour + 1);
							copy_cases(cases, cases2);
						}
						else
							temp = INT_MAX;
					}
					if (temp < min)
						min = temp;
				}
			}
			else if (piece == BFOU)
			{
				for (k = 0; k < NBFOU; k += 2)
				{
					if (tour == RECU)
						temp = analyse(cases, cases2, i, j, k);
					else
					{
						if (test(cases, depf[k] + i, depf[k + 1] + j, i, j))
						{
							deplace(depf[k] + i, depf[k + 1] + j, i, j, cases2);
							temp = coup3(cases2, tour + 1);
							copy_cases(cases, cases2);
						}
						else
							temp = INT_MAX;
					}
					if (temp < min)
						min = temp;
				}
			}
			else if (piece == BDAME)
			{
				for (k = 0; k < NBDAME; k += 2)
				{
					if (tour == RECU)
						temp = analyse(cases, cases2, i, j, k);
					else
					{
						if (test(cases, depd[k] + i, depd[k + 1] + j, i, j))
						{
							deplace(depd[k] + i, depd[k + 1] + j, i, j, cases2);
							temp = coup3(cases2, tour + 1);
							copy_cases(cases, cases2);
						}
						else
							temp = INT_MAX;
					}
					if (temp < min)
						min = temp;
				}
			}
			else if (piece == BROI)
			{
				for (k = 0; k < NBROI; k += 2)
				{
					if (tour == RECU)
						temp = analyse(cases, cases2, i, j, k);
					else
					{
						if (test(cases, depr[k] + i, depr[k + 1] + j, i, j))
						{
							deplace(depr[k] + i, depr[k + 1] + j, i, j, cases2);
							temp = coup3(cases2, tour + 1);
							copy_cases(cases, cases2);
						}
						else
							temp = INT_MAX;
					}
					if (temp < min)
						min = temp;
				}
			}

		}
	}
	return min;

}

/*----------*/
/*    COUP3    */    /* Coup de l'humain avec listage des pions, test du coup et création de la valeur max (meilleur coup) */
/*----------*/

int coup3(int cases[N][N], int tour)
{
	int i, j, k, piece, max = INT_MIN, temp; /* coupn(x,y) contient le meilleur coup a réaliser*/
	int cases2[N][N]; /* Contient le second tableau modifié par un coup temporaire */

	copy_cases(cases, cases2);
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
		{

			piece = cases[i][j];
			if (piece == NPION)
			{
				for (k = 0; k < NBPION; k += 2)
				{
					if (tour == RECU)
						temp = analyse(cases, cases2, i, j, k);
					else
					{
						if (test(cases, deppn[k] + i, deppn[k + 1] + j, i, j))
						{
							deplace(deppn[k] + i, deppn[k + 1] + j, i, j, cases2);
							temp = coup2(cases2, tour + 1);
							copy_cases(cases, cases2);
						}
						else
							temp = INT_MIN;
					}
					if (temp > max)
						max = temp;
				}
			}
			else if (piece == NTOUR)
			{

				for (k = 0; k < NBTOUR; k += 2)
				{
					if (tour == RECU)
						temp = analyse(cases, cases2, i, j, k);
					else
					{
						if (test(cases, dept[k] + i, dept[k + 1] + j, i, j))
						{
							deplace(dept[k] + i, dept[k + 1] + j, i, j, cases2);
							temp = coup2(cases2, tour + 1);
							copy_cases(cases, cases2);
						}
						else
							temp = INT_MIN;
					}
					if (temp > max)
						max = temp;

				}
			}
			else if (piece == NCHEVAL)
			{
				for (k = 0; k < NBCHEVAL; k += 2)
				{
					if (tour == RECU)
						temp = analyse(cases, cases2, i, j, k);
					else
					{
						if (test(cases, depc[k] + i, depc[k + 1] + j, i, j))
						{
							deplace(depc[k] + i, depc[k + 1] + j, i, j, cases2);
							temp = coup2(cases2, tour + 1);
							copy_cases(cases, cases2);
						}
						else
							temp = INT_MIN;
					}
					if (temp > max)
						max = temp;
				}
			}
			else if (piece == NFOU)
			{
				for (k = 0; k < NBFOU; k += 2)
				{
					if (tour == RECU)
						temp = analyse(cases, cases2, i, j, k);
					else
					{
						if (test(cases, depf[k] + i, depf[k + 1] + j, i, j))
						{
							deplace(depf[k] + i, depf[k + 1] + j, i, j, cases2);
							temp = coup2(cases2, tour + 1);
							copy_cases(cases, cases2);
						}
						else
							temp = INT_MIN;
					}
					if (temp > max)
						max = temp;
				}
			}
			else if (piece == NDAME)
			{
				for (k = 0; k < NBDAME; k += 2)
				{
					if (tour == RECU)
						temp = analyse(cases, cases2, i, j, k);
					else
					{
						if (test(cases, depd[k] + i, depd[k + 1] + j, i, j))
						{
							deplace(depd[k] + i, depd[k + 1] + j, i, j, cases2);
							temp = coup2(cases2, tour + 1);
							copy_cases(cases, cases2);
						}
						else
							temp = INT_MIN;
					}
					if (temp > max)
						max = temp;
				}
			}
			else if (piece == NROI)
			{
				for (k = 0; k < NBROI; k += 2)
				{
					if (tour == RECU)
						temp = analyse(cases, cases2, i, j, k);
					else
					{
						if (test(cases, depr[k] + i, depr[k + 1] + j, i, j))
						{
							deplace(depr[k] + i, depr[k + 1] + j, i, j, cases2);
							temp = coup2(cases2, tour + 1);
							copy_cases(cases, cases2);
						}
						else
							temp = INT_MIN;
					}
					if (temp > max)
						max = temp;
				}
			}

		}
	}
	return max;

}

/*----------*/
/*    MAIN    */    /* La belle fonction Main */
/*----------*/

int main()
{
	int cases[N][N];
	echecn = 0;
	cases_init(cases);
	deplacement_init();
	
	/*FIN_*/
	cases_affiche(cases);
	printf("Valeur : %d", valeur(cases));
	system("pause");

	while (1)
	{
		coupadv(cases);
		coup(cases, 1);
		cases_affiche(cases);
	}

	return 0;
}