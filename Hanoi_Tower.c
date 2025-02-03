#include <err.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef int dato_t;
int numero_legnetti = 0, mossa = 0, count = 0;

struct nodo {
  dato_t dato;
  struct nodo *succ;
};
typedef struct nodo nodo;
size_t size_nodo = sizeof(nodo);

void push(nodo **, dato_t);
dato_t pop(nodo **);
bool isEmpty(nodo **);
void stampa_pila(nodo **);
void inizio(nodo **);
void stampa_iniziale(nodo **);
void asseganzione_iniziale(nodo **, nodo **);
void move(nodo **, nodo **, nodo **);
int mossa_valida(nodo **, nodo **);
void stampa_tutte_pile(nodo **, nodo **, nodo **);
int vittoria(nodo **);
int towerOfHanoi(int, int, int, int, nodo **PilaA, nodo **PilaB, nodo **PilaC);

int main(void) {
  int scelta = 0;
  nodo *PilaA = NULL;
  nodo *PilaB = NULL;
  nodo *PilaC = NULL;
  inizio(&PilaA);
  printf("Seconda pila\n");
  stampa_pila(&PilaB);
  printf("Terza pila\n");
  stampa_pila(&PilaC);
  printf("\n1.COMPUTER RESOLVER\n2.YOU SOLVE\n\n");
  do {
    scanf("%d", &scelta);
    scelta=1;
  } while (scelta != 1 && scelta != 2);
  if (scelta == 1) {
    towerOfHanoi(numero_legnetti, 1, 3, 2, &PilaA, &PilaB, &PilaC);
  } else {
    while (1) {
      move(&PilaA, &PilaB, &PilaC);
      stampa_tutte_pile(&PilaA, &PilaB, &PilaC);
      count++;
      if (vittoria(&PilaC) == 0) {
        printf("Hai vinto complimenti\nMOSSE USATE %d  -  MOSSE MINIME %0.0f",
               count, pow(2, numero_legnetti) - 1);
        return 0;
      }
    }
  }
  free(PilaA);
  free(PilaB);
  free(PilaC);
}

void stampa_tutte_pile(nodo **pilaA, nodo **pilaB, nodo **pilaC) {
  printf("Prima pila\n");
  stampa_pila(pilaA);
  printf("Seconda pila\n");
  stampa_pila(pilaB);
  printf("Terza pila\n");
  stampa_pila(pilaC);
}

int vittoria(nodo **pilaC) {
  int count = 1;
  nodo *t = *pilaC;
  printf("\n");
  if (t == NULL) {
    return 1;
  }
  for (; t != NULL; t = t->succ) {
    if (t->dato != count) {
      return 1;
    }
    count++;
  }

  if (count != numero_legnetti + 1) {
    return 1;
  }
  printf("\n\n");
  return 0;
}

void move(nodo **pilaA, nodo **pilaB, nodo **pilaC) {
  int dato_aggiungere;
  do {
    printf("Che mossa vuoi effettuare?\n1. 1-->2\n2. 1-->3\n3. 2-->1\n4. "
           "2-->3\n5. 3-->1\n6. 3-->2\n>");
    scanf("%d", &mossa);
  } while (mossa > 6 || mossa < 1);
  switch (mossa) {
  case 1: {
    if (mossa_valida(pilaA, pilaB) != 0) {
      dato_aggiungere = mossa_valida(pilaA, pilaB);
      pop(pilaA);
      push(pilaB, dato_aggiungere);
    }
    break;
  }
  case 2: {
    if (mossa_valida(pilaA, pilaC) != 0) {
      dato_aggiungere = mossa_valida(pilaA, pilaC);
      pop(pilaA);
      push(pilaC, dato_aggiungere);
    }
    break;
  }
  case 3: {
    if (mossa_valida(pilaB, pilaA) != 0) {
      dato_aggiungere = mossa_valida(pilaB, pilaA);
      pop(pilaB);
      push(pilaA, dato_aggiungere);
    }
    break;
  }
  case 4: {
    if (mossa_valida(pilaB, pilaC) != 0) {
      dato_aggiungere = mossa_valida(pilaB, pilaC);
      pop(pilaB);
      push(pilaC, dato_aggiungere);
    }
    break;
  }
  case 5: {
    if (mossa_valida(pilaC, pilaA) != 0) {
      dato_aggiungere = mossa_valida(pilaC, pilaA);
      pop(pilaC);
      push(pilaA, dato_aggiungere);
    }
    break;
  }
  case 6: {
    if (mossa_valida(pilaC, pilaB) != 0) {
      dato_aggiungere = mossa_valida(pilaC, pilaB);
      pop(pilaC);
      push(pilaB, dato_aggiungere);
    }
    break;
  }
  default: {
    break;
  }
  }
}

int mossa_valida(nodo **pila1, nodo **pila2) {
  if (isEmpty(pila1) == 0 && isEmpty(pila2) == 0 &&
      ((*pila1)->dato < (*pila2)->dato)) {
    return (*pila1)->dato;
  } else if (isEmpty(pila1) == 0 && isEmpty(pila2)) {
    return (*pila1)->dato;
  } else {
    printf("Mossa non valida\n");
    return 0;
  }
  return 0;
}

void asseganzione_iniziale(nodo **pilaB, nodo **pilaC) {
  for (int i = numero_legnetti; i > 0; i--) {
    push(pilaB, 0);
    push(pilaC, 0);
  }
}

void stampa_iniziale(nodo **pilaA) {
  for (int i = numero_legnetti; i > 0; i--) {
    push(pilaA, i);
  }
  stampa_pila(pilaA);
}

void inizio(nodo **testa) {
  printf("###TORRE DI HANOI###\n\n");
  printf("Inserire il numero di 'legnetti' con cui si vuole giocare\n>");
  scanf("%d", &numero_legnetti);
  printf("Prima pila\n");
  stampa_iniziale(testa);
}

void push(nodo **testa, dato_t d) {
  if (testa == NULL) {
    perror("Pila non inizializzata!");
    err(1, NULL);
  }
  nodo *nuovo;
  if ((nuovo = malloc(size_nodo)) == NULL) {
    perror("Errore nel push");
    err(1, NULL);
  }
  nuovo->dato = d;
  nuovo->succ = *testa;
  *testa = nuovo;
}

dato_t pop(nodo **testa) {
  if (testa == NULL) {
    printf("Mossa non valida!");
    return 1;
  }
  if (*testa == NULL) {
    printf("Mossa non valida!");
    return 1;
  }

  dato_t ret = (*testa)->dato;

  nodo *temp = *testa;
  *testa = (*testa)->succ;
  free(temp);

  return ret;
}

bool isEmpty(nodo **testa) {
  if (testa == NULL) {
    printf("Mossa non valida!");
    return 1;
  }
  if (*testa == NULL) {
    return true;
  }
  return false;
}

void stampa_pila(nodo **testa) {
  nodo *t = *testa;
  printf("\n");
  for (; t != NULL; t = t->succ) {
    for (int i = 0; i < t->dato; i++) {
      printf("■");
    }
    printf("  %d\n", t->dato);
  }
  printf("\n\n");
}

int towerOfHanoi(int n, int from_rod, int to_rod, int aux_rod, nodo **pilaA,
                 nodo **pilaB, nodo **pilaC) {
  if (n == 0) {
    return 1;
  }
  towerOfHanoi(n - 1, from_rod, aux_rod, to_rod, pilaA, pilaB, pilaC);
  printf("\nMOSSA NUMERO %d\n", count + 1);
  if (from_rod == 1 && to_rod == 2) {
    int dato_aggiungere = mossa_valida(pilaA, pilaB);
    pop(pilaA);
    push(pilaB, dato_aggiungere);
  }
  if (from_rod == 1 && to_rod == 3) {
    if (mossa_valida(pilaA, pilaC) != 0) {
      int dato_aggiungere = mossa_valida(pilaA, pilaC);
      pop(pilaA);
      push(pilaC, dato_aggiungere);
    }
  }
  if (from_rod == 2 && to_rod == 1) {
    if (mossa_valida(pilaB, pilaA) != 0) {
      int dato_aggiungere = mossa_valida(pilaB, pilaA);
      pop(pilaB);
      push(pilaA, dato_aggiungere);
    }
  }
  if (from_rod == 2 && to_rod == 3) {
    if (mossa_valida(pilaB, pilaC) != 0) {
      int dato_aggiungere = mossa_valida(pilaB, pilaC);
      pop(pilaB);
      push(pilaC, dato_aggiungere);
    }
  }
  if (from_rod == 3 && to_rod == 1) {
    if (mossa_valida(pilaC, pilaA) != 0) {
      int dato_aggiungere = mossa_valida(pilaC, pilaA);
      pop(pilaC);
      push(pilaA, dato_aggiungere);
    }
  }
  if (from_rod == 3 && to_rod == 2) {
    if (mossa_valida(pilaC, pilaB) != 0) {
      int dato_aggiungere = mossa_valida(pilaC, pilaB);
      pop(pilaC);
      push(pilaB, dato_aggiungere);
    }
  }
  stampa_tutte_pile(pilaA, pilaB, pilaC);
  sleep(1);
  if (vittoria(pilaC) == 1) {
    printf("\e[1;1H\e[2J");
    count++;
    printf("\nMOSSA NUMERO %d\n", count+1);
    towerOfHanoi(n - 1, aux_rod, to_rod, from_rod, pilaA, pilaB, pilaC);
  } else {
    printf("VITTORIA\n");
  }
  return 0;
}