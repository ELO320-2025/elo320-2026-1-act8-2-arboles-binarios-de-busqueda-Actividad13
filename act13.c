#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Mascota {
    char tipo[20];
    char nombre[20];
} Mascota;

typedef struct Nodo {
    Mascota mascota;
    struct Nodo *izq, *der;
} Nodo;

// Crear un nuevo nodo
Nodo* crearNodo(Mascota m) {
    Nodo* nuevo = (Nodo*) malloc(sizeof(Nodo));
    if (!nuevo) {
        printf("Error al asignar memoria\n");
        exit(1);
    }
    nuevo->mascota = m;
    nuevo->izq = nuevo->der = NULL;
    return nuevo;
}

// Insertar en el BST ordenado por nombre
Nodo* insertar(Nodo* raiz, Mascota m) {
    if (raiz == NULL) {
        return crearNodo(m);
    }
    if (strcmp(m.nombre, raiz->mascota.nombre) < 0) {
        raiz->izq = insertar(raiz->izq, m);
    } else if (strcmp(m.nombre, raiz->mascota.nombre) > 0) {
        raiz->der = insertar(raiz->der, m);
    }
    // Si el nombre ya existe, no lo insertamos de nuevo
    return raiz;
}

// Buscar mascota por nombre
Nodo* buscar(Nodo* raiz, const char* nombre) {
    if (raiz == NULL) return NULL;

    int cmp = strcmp(nombre, raiz->mascota.nombre);
    if (cmp == 0) {
        return raiz;
    } else if (cmp < 0) {
        return buscar(raiz->izq, nombre);
    } else {
        return buscar(raiz->der, nombre);
    }
}

// Recorrido in-order (para mostrar mascotas en orden alfabético por nombre)
void inOrder(Nodo* raiz) {
    if (raiz != NULL) {
        inOrder(raiz->izq);
        printf("%s (%s)\n", raiz->mascota.nombre, raiz->mascota.tipo);
        inOrder(raiz->der);
    }
}

int main() {
    Nodo* raiz = NULL;

    Mascota mascotas[15] = {
        {"Perro", "Rocky"},
        {"Gato", "Michi"},
        {"Pez", "Nemo"},
        {"Perro", "Fido"},
        {"Ave", "Piolin"},
        {"Conejo", "Bugs"},
        {"Perro", "Lassie"},
        {"Gato", "Garfield"},
        {"Pez", "Dory"},
        {"Ave", "Coco"},
        {"Perro", "Rex"},
        {"Gato", "Tom"},
        {"Perro", "Snoopy"},
        {"Tortuga", "Manuelita"},
        {"Perro", "Pluto"}
    };

    // Insertamos todas las mascotas
    for (int i = 0; i < 15; i++) {
        raiz = insertar(raiz, mascotas[i]);
    }

    printf("Listado de mascotas (ordenadas por nombre):\n");
    inOrder(raiz);

    printf("\nBuscando a 'Garfield'...\n");
    Nodo* resultado = buscar(raiz, "Garfield");
    if (resultado) {
        printf("Encontrado: %s (%s)\n", resultado->mascota.nombre, resultado->mascota.tipo);
    } else {
        printf("Mascota no encontrada\n");
    }

    printf("\nBuscando a 'Bolt'...\n");
    resultado = buscar(raiz, "Bolt");
    if (resultado) {
        printf("Encontrado: %s (%s)\n", resultado->mascota.nombre, resultado->mascota.tipo);
    } else {
        printf("Mascota no encontrada\n");
    }

    return 0;
}
