#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERS 1000
#define MAX_QUEUE 1000

// --- Red-Black Tree Yapisi ---
typedef struct RBNode {
    int user_id;
    char color; // 'R' veya 'B'
    struct RBNode *left, *right, *parent;
} RBNode;

RBNode *rb_root = NULL;

RBNode* create_rb_node(int id) {
    RBNode* node = (RBNode*)malloc(sizeof(RBNode));
    node->user_id = id;
    node->color = 'R';
    node->left = node->right = node->parent = NULL;
    return node;
}

// Kirmizi-Siyah Agaca basit ekleme (detayli dengeleme yok)
void rb_insert_simple(int id) {
    RBNode* node = create_rb_node(id);
    if (rb_root == NULL) {
        node->color = 'B';
        rb_root = node;
        return;
    }
    RBNode* current = rb_root;
    RBNode* parent = NULL;
    while (current != NULL) {
        parent = current;
        if (id < current->user_id)
            current = current->left;
        else
            current = current->right;
    }
    node->parent = parent;
    if (id < parent->user_id)
        parent->left = node;
    else
        parent->right = node;
   
}

int rb_search(int id) {
    RBNode* current = rb_root;
    while (current != NULL) {
        if (id == current->user_id) return 1;
        else if (id < current->user_id) current = current->left;
        else current = current->right;
    }
    return 0;
}

// --- Kullanici Grafigi ---
typedef struct FriendNode {
    int id;
    struct FriendNode* next;
} FriendNode;

typedef struct {
    int user_id;
    FriendNode* friends;
} UserGraph;

UserGraph users[MAX_USERS];
int user_count = 0;

int find_index(int id) {
    int i;
    for (i = 0; i < user_count; i++)
        if (users[i].user_id == id) return i;
    return -1;
}

void add_user(int id) {
    if (find_index(id) != -1) return;
    users[user_count].user_id = id;
    users[user_count].friends = NULL;
    user_count++;
    rb_insert_simple(id);
}

void add_friendship(int u1, int u2) {
    int i = find_index(u1);
    int j = find_index(u2);
    if (i == -1 || j == -1) return;
    FriendNode* f1 = malloc(sizeof(FriendNode));
    f1->id = u2; f1->next = users[i].friends; users[i].friends = f1;
    FriendNode* f2 = malloc(sizeof(FriendNode));
    f2->id = u1; f2->next = users[j].friends; users[j].friends = f2;
}

void print_users() {
    int i;
    for (i = 0; i < user_count; i++) {
        printf("USER %d: ", users[i].user_id);
        FriendNode* f = users[i].friends;
        while (f) {
            printf("%d ", f->id);
            f = f->next;
        }
        printf("\n");
    }
}

// --- DFS: Belirli mesafedeki arkadaslar ---
void dfs(int index, int depth, int current, int* visited) {
    visited[index] = 1;
    if (current == depth) {
        printf("%d ", users[index].user_id);
        return;
    }
    FriendNode* f = users[index].friends;
    while (f) {
        int idx = find_index(f->id);
        if (!visited[idx])
            dfs(idx, depth, current + 1, visited);
        f = f->next;
    }
}

// Ortak arkadaslar
void ortak_arkadaslar(int u1, int u2) {
    int i = find_index(u1), j = find_index(u2);
    if (i == -1 || j == -1) return;
    FriendNode *f1 = users[i].friends, *f2;
    printf("%d ve %d ortak arkadaslari: ", u1, u2);
    while (f1) {
        f2 = users[j].friends;
        while (f2) {
            if (f1->id == f2->id) printf("%d ", f1->id);
            f2 = f2->next;
        }
        f1 = f1->next;
    }
    printf("\n");
}

// Topluluk Tespiti (Bagli Bilesenler)
void dfs_mark(int index, int* visited) {
    visited[index] = 1;
    printf("%d ", users[index].user_id);
    FriendNode* f = users[index].friends;
    while (f) {
        int idx = find_index(f->id);
        if (!visited[idx])
            dfs_mark(idx, visited);
        f = f->next;
    }
}

void topluluklar() {
    int visited[MAX_USERS] = {0};
    int i;
    for (i = 0; i < user_count; i++) {
        if (!visited[i]) {
            printf("Topluluk: ");
            dfs_mark(i, visited);
            printf("\n");
        }
    }
}

// Etki Alani Hesaplama (Kac kisiyi etkiliyor?)
int etkili_kisi_sayisi(int index, int* visited) {
    visited[index] = 1;
    int count = 1;
    FriendNode* f = users[index].friends;
    while (f) {
        int idx = find_index(f->id);
        if (!visited[idx])
            count += etkili_kisi_sayisi(idx, visited);
        f = f->next;
    }
    return count;
}

int main() {
    int secim, id, u1, u2, mesafe;
    while (1) {
        printf("\n1. Kullanici Ekle\n2. Arkadaslik Ekle\n3. Yazdir\n4. DFS ile arkadas ara\n5. Ortak arkadaslar\n6. Topluluklari bul\n7. Etki alani hesapla\n8. ID ara (RB Tree)\n0. Cikis\nSeciminiz: ");
        scanf("%d", &secim);
        if (secim == 0) break;
        switch (secim) {
            case 1:
                printf("Kullanici ID girin: ");
                scanf("%d", &id);
                add_user(id);
                break;
            case 2:
                printf("1. Kullanici ID: "); scanf("%d", &u1);
                printf("2. Kullanici ID: "); scanf("%d", &u2);
                add_user(u1); add_user(u2);
                add_friendship(u1, u2);
                break;
            case 3:
                print_users();
                break;
            case 4:
                printf("Kullanici ID: "); scanf("%d", &id);
                printf("Mesafe: "); scanf("%d", &mesafe);
                u1 = find_index(id);
                if (u1 == -1) printf("Kullanici bulunamadi.\n");
                else {
                    int visited[MAX_USERS] = {0};
                    printf("%d mesafedeki arkadaslar: ", mesafe);
                    dfs(u1, mesafe, 0, visited);
                    printf("\n");
                }
                break;
            case 5:
                printf("1. Kullanici ID: "); scanf("%d", &u1);
                printf("2. Kullanici ID: "); scanf("%d", &u2);
                ortak_arkadaslar(u1, u2);
                break;
            case 6:
                topluluklar();
                break;
            case 7:
                printf("Kullanici ID: "); scanf("%d", &id);
                u1 = find_index(id);
                if (u1 == -1) printf("Kullanici bulunamadi.\n");
                else {
                    int visited[MAX_USERS] = {0};
                    int count = etkili_kisi_sayisi(u1, visited);
                    printf("%d kisiyi etkiliyor.\n", count - 1);
                }
                break;
            case 8:
                printf("Kullanici ID girin: ");
                scanf("%d", &id);
                if (rb_search(id)) printf("Kullanici mevcut (RB Tree).\n");
                else printf("Kullanici bulunamadi (RB Tree).\n");
                break;
        }
    }
    return 0;
}
