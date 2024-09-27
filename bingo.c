#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// citire carduri pe intervale parcurgand fiecare card
void citire_card(int carduri[][5][5], int N) {
  int i, j, a, b, k;

  for (k = 0; k < N; k++) {
    a = 1;  // reinitializez
    b = 15;
    for (i = 0; i < 5; i++) {
      a = 1;
      b = 15;
      j = 0;
      do {
        scanf("%d", &carduri[k][i][j]);
        if (carduri[k][i][j] < a || carduri[k][i][j] > b) {
          printf("depasire interval");
        } else {
          j++;
          a += 15;
          b += 15;
        }
      } while (j < 5);
    }
  }
}

// implementare SHIFT
// parcurg ciclic cat timp Y este diferit de 0 si mut cu cate o pozitie fiecare
// element, am implementat atat pentru numere, cat si pentru #. Retin ultimul
// element pe care il mut pe prima pozitie
void SHIFT(int X, int Y, int carduri[][5][5], int N, char celule[][5][5]) {
  int k, i, aux;
  char aux_celule;

  while (Y != 0) {
    for (k = 0; k < N; k++) {
      // salveaza capatul (ultimul element de pe coloana X)
      aux = carduri[k][4][X];
      // salveaza capatul si din celule
      aux_celule = celule[k][4][X];
      for (i = 4; i > 0; i--) {
        // mutare cu o pozitie mai jos
        celule[k][i][X] = celule[k][i - 1][X];
        carduri[k][i][X] = carduri[k][i - 1][X];
      }
      // adaugam capatul pe prima pozitie
      celule[k][0][X] = aux_celule;
      carduri[k][0][X] = aux;
    }
    Y--;
  }
}

// implementare SWAP, interschimb coloanele cu auxiliar(celule) pentru # si cu
// aux pentru numere(carduri)
void SWAP(int X, int Y, int carduri[][5][5], int N, char celule[][5][5]) {
  int i, k, aux;
  char auxiliar;

  for (k = 0; k < N; k++) {
    for (i = 0; i < 5; i++) {
      if (celule[k][i][X] == '#') {
        // interschimbare pt cazul cu # pe coloana X
        auxiliar = celule[k][i][X];
        celule[k][i][X] = celule[k][i][Y];
        celule[k][i][Y] = auxiliar;
      } else if (celule[k][i][Y] == '#') {
        // interschimbare pt cazul cu # pe coloana Y
        auxiliar = celule[k][i][Y];
        celule[k][i][Y] = celule[k][i][X];
        celule[k][i][X] = auxiliar;
      }
      // interschimbare pt numere
      aux = carduri[k][i][X];
      carduri[k][i][X] = carduri[k][i][Y];
      carduri[k][i][Y] = aux;
    }
  }
}

// implementare DSC (descrescator), parcurg cardurile si compar numerele, apoi
// le interschimb 5 - i - 1, deoarece ultimul pozitionat este deja pozitionat
// corect
void DSC(int Y, int carduri[][5][5], char celule[][5][5], int N) {
  int i, j, aux, k;

  for (k = 0; k < N; k++) {
    for (i = 0; i < 5; i++) {
      for (j = 0; j < 5 - i - 1; j++) {
        if (carduri[k][j][Y] < carduri[k][j + 1][Y]) {
          if (celule[k][j + 1][Y] == '#' && celule[k][j][Y] != '#') {
            celule[k][j + 1][Y] = ' ';
            celule[k][j][Y] = '#';
          } else if (celule[k][j][Y] == '#' && celule[k][j + 1][Y] != '#') {
            celule[k][j][Y] = ' ';
            celule[k][j + 1][Y] = '#';
          }
          aux = carduri[k][j][Y];
          carduri[k][j][Y] = carduri[k][j + 1][Y];
          carduri[k][j + 1][Y] = aux;
        }
      }
    }
  }
}

// implementare ASC (crescator), la fel ca la DSC
void ASC(int Y, int carduri[][5][5], char celule[][5][5], int N) {
  int i, j, aux, k;

  for (k = 0; k < N; k++) {
    for (i = 0; i < 5; i++) {
      for (j = 0; j < 5 - i - 1; j++) {
        if (carduri[k][j][Y] > carduri[k][j + 1][Y]) {
          if (celule[k][j + 1][Y] == '#' && celule[k][j][Y] != '#') {
            celule[k][j + 1][Y] = ' ';
            celule[k][j][Y] = '#';
          } else if (celule[k][j][Y] == '#' && celule[k][j + 1][Y] != '#') {
            celule[k][j][Y] = ' ';
            celule[k][j + 1][Y] = '#';
          }
          aux = carduri[k][j][Y];
          carduri[k][j][Y] = carduri[k][j + 1][Y];
          carduri[k][j + 1][Y] = aux;
        }
      }
    }
  }
}

// colorez celula din mijloc pentru fiecare card, intershimb coloanele si
// intervalele pentru SWAP in bingo_index retin intervalele, in celule colorez
// cu #(matrice tridimensionala)
void initializare_matrice(int N, char celule[][5][5], int *bingo_index) {
  int k, initial = 15;

  // marcare # mijloc

  for (k = 0; k < N; k++) {
    celule[k][2][2] = '#';
  }

  // pentru interschimbare intervale cand se apeleaza SWAP

  for (k = 0; k < 5; k++) {
    bingo_index[k] = initial;
    initial += 15;
  }
}

// colorare celule cu #, parcurg citcel unde am retinut bilele, parcurg
// intervalele salvate in bingo_index, verific daca valoarea din citcel se
// incadreaza in interval, iar daca conditia este indeplinita verific daca
// valoarea se afla in carduri, daca da, o colorez cu #
void celule_colorat(int carduri[][5][5], int N, char celule[][5][5],
                    int *citcel, int M, int *bingo_index) {
  int k, i, r, itv;

  for (r = 0; r < M; r++) {
    for (itv = 0; itv < 5; itv++) {
      if (citcel[r] <= bingo_index[itv]) {
        for (k = 0; k < N; k++) {
          for (i = 0; i < 5; i++) {
            if (citcel[r] == carduri[k][i][itv]) {
              celule[k][i][itv] = '#';
            }
          }
        }
      }
    }
  }
}

// implementare SHOW, afisare card, parcurg ambele matrici, carduri si citcel,
// verific daca celula a fost colorata, daca da afisez continutul din celule,
// adica #, daca nu afisez numerele necolorate din carduri
void SHOW(int k, int carduri[][5][5], char celule[][5][5]) {
  int i, j;
  for (i = 0; i < 5; i++) {
    for (j = 0; j < 5; j++) {
      if (celule[k][i][j] == '#') {
        printf("%c ", celule[k][i][j]);
      } else {
        printf("%d ", carduri[k][i][j]);
      }
    }
    printf("\n");
  }
}

// implementare WINNER, verific daca exista combinatii de # pe coloane, pe
// linii, pe diagonala principala, pe diagonala secundara, retin numarul de
// apartii(in aparitii), cand devine 5 cresc punctele si numarul de
// coloane/linii care au fost completate cu #(in colorat). Daca colorat este mai
// mare decat 0, atunci cardul este castigator, salvez cardul intr-un
// vector(winner), retin astfel si ID-ul,iar in vectorul puncte retin punctele
// pentru fiecare card. Daca ok este 0, atunci cardul este necastigator
void WINNER(int N, char celule[][5][5], int carduri[][5][5], int *winner,
            int *puncteNou, int *winnerfound) {
  int k, i, j, ok = 0, aparitii = 0, puncte = 0, colorat = 0;
  int afisat = 0;

  for (k = 0; k < N; k++) {
    // combinatie # pe coloane

    for (j = 0; j < 5; j++) {
      aparitii = 0;
      for (i = 0; i < 5; i++) {
        if (celule[k][i][j] == '#') {
          // numar de cate ori apare #
          aparitii++;
        }
      }
      if (aparitii == 5) {
        puncte += 10;
        // numar cate coloane au fost completate cu #
        colorat++;
        ok = 1;
      }
    }

    // combinatie # pe linii

    for (i = 0; i < 5; i++) {
      aparitii = 0;
      for (j = 0; j < 5; j++) {
        if (celule[k][i][j] == '#') {
          aparitii++;
        }
      }
      if (aparitii == 5) {
        // numar cate linii au fost completate cu #
        colorat++;
        puncte += 10;
        ok = 1;
      }
    }

    // combinatie # diagonala principala

    aparitii = 0;

    for (i = 0; i < 5; i++) {
      if (celule[k][i][i] == '#') {
        aparitii++;
        if (aparitii == 5) {
          puncte += 10;
          // diagonala principala a fost completata cu #
          colorat++;
          ok = 1;
        }
      }
    }

    // combinatie # diagonala secundara

    aparitii = 0;

    for (i = 0; i < 5; i++) {
      if (celule[k][i][4 - i] == '#') {
        aparitii++;
        if (aparitii == 5) {
          puncte += 10;
          // diagonala secundara a fost completata cu #
          colorat++;
          ok = 1;
        }
      }
    }

    if (colorat > 0) {
      // salvez cardul si ID-ul pt fiecare card castigator
      winner[k] = 1;
      // salvez punctele pt fiecare card
      puncteNou[k] = puncte;
    }

    if (ok == 0) {
      // cardul este necastigator
      winner[k] = 0;
      puncteNou[k] = puncte;
    }

    // reinitializez pt fiecare card

    puncte = 0;
    ok = 0;
    aparitii = 0;
    colorat = 0;
  }

  // testez daca am gasit castigatorul

  for (k = 0; k < N; k++) {
    if (winner[k] == 1 && afisat == 0) {
      printf("%d\n", k);
      // afisez cardul
      SHOW(k, carduri, celule);
      // am afisat un card, conditie de intrerupere
      afisat = 1;
      // am gasit castigatorul
      *winnerfound = 1;
      // afisez punctele
      printf("%d", puncteNou[k]);
      // opresc programul odata ce am gasit castigatorul
      break;
    }
  }
}

// implementare citire bile, apelez initializare_matrice pentru a pregati
// matricea pentru prelucrare, citesc comanda, apoi o impart in subsiruri cu
// strtok, extrag prima parte a comenzii(numele, de ex SHIFT), testez daca mai
// exista subsiruri, apoi compar cu strcmp comenzile, daca este true, convertesc
// cu atoi la intreg si retin numerele, apoi apelez functiile aferente. Retin
// bilele speciale cu -1 in citcel, iar pentru bilele normale salvez numerele
// pentru a realiza mai apoi colorarea cu #. Apelez functia WINNER, daca l-a
// gasit iese din subprogram, altfel printeaza NO WINNER
void citire_bile(int M, int *citcel, int carduri[][5][5], char celule[][5][5],
                 int N, int *bingo_index, int *winner, int *puncteNou,
                 int *winnerfound) {
  char *s = (char *)malloc(100 * sizeof(char));
  initializare_matrice(N, celule, bingo_index);
  int i, nr, j = 0, aux;
  char *nr_bile;
  char tip[10];
  // pt SWAP, extrag 2 numere
  int c1, c2;

  for (i = 0; i < M; i++) {
    scanf("%s", s);
    // separa sirul in subsiruri in functie de sep -
    nr_bile = strtok(s, "-");

    if (nr_bile != NULL) {
      // copiez ce fel de comanda citesc (de ex: B, SHIFT)
      strcpy(tip, nr_bile);
      // testeaza daca mai exista subsiruri dupa -
      nr_bile = strtok(NULL, "-");
      if (nr_bile != NULL) {
        if (strcmp(tip, "DSC") == 0) {
          // convertesc de la string la intreg
          nr = atoi(nr_bile);
          DSC(nr, carduri, celule, N);
          // salvez comanda in vectorul citcel
          citcel[j++] = -1;
        } else if (strcmp(tip, "SHOW") == 0) {
          nr = atoi(nr_bile);
          celule_colorat(carduri, N, celule, citcel, M, bingo_index);
          SHOW(nr, carduri, celule);
          citcel[j++] = -1;
        } else if (strcmp(tip, "ASC") == 0) {
          nr = atoi(nr_bile);
          ASC(nr, carduri, celule, N);
          citcel[j++] = -1;
        } else if (strcmp(tip, "SWAP") == 0) {
          c1 = atoi(nr_bile);
          nr_bile = strtok(NULL, "-");
          if (nr_bile != NULL) {
            c2 = atoi(nr_bile);

            // interschimbare bingo-index si citicel
            aux = bingo_index[c1];
            bingo_index[c1] = bingo_index[c2];
            bingo_index[c2] = aux;
            SWAP(c1, c2, carduri, N, celule);
          }
        } else if (strcmp(tip, "SHIFT") == 0) {
          c1 = atoi(nr_bile);
          nr_bile = strtok(NULL, "-");
          if (nr_bile != NULL) {
            c2 = atoi(nr_bile);
            SHIFT(c1, c2, carduri, N, celule);
          }
        } else {
          nr = atoi(nr_bile);
          citcel[j++] = nr;
          celule_colorat(carduri, N, celule, citcel, M, bingo_index);
        }
      }
    }

    WINNER(N, celule, carduri, winner, puncteNou, winnerfound);

    if (*winnerfound) {
      break;
    }
  }

  if (!(*winnerfound)) {
    printf("NO WINNER");
  }

  free(s);
}

// citesc N carduri, declar matricea tridimensionala carduri(in care nu modific
// nimic, retin numerele), matricea tridimensionala celule(de tip char, in care
// colorez cu #)
int main(void) {
  int N, carduri[100][5][5], M, winnerfound;
  char celule[100][5][5];
  int *bingo_index = (int *)malloc(5 * sizeof(int));

  // nr carduri
  scanf("%d", &N);

  int *winner = (int *)malloc(N * sizeof(int));
  int *puncteNou = (int *)malloc(N * sizeof(int));

  citire_card(carduri, N);
  // nr de bile
  scanf("%d", &M);

  int *citcel = (int *)malloc(M * sizeof(int));

  citire_bile(M, citcel, carduri, celule, N, bingo_index, winner, puncteNou,
              &winnerfound);

  printf("\n");

  free(winner);
  free(puncteNou);
  free(citcel);

  return 0;
}
