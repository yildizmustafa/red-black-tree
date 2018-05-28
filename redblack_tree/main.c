#include "rbtree.c"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#define stepspace  4

static int compare_int(void* sol, void* sag);
static void yazdir(rbtree t);
static void yazdir_helper(rbtree_node n, int step);

int compare_int(void* solp, void* sagp) {
    int sol = (int)solp;
    int sag = (int)sagp;
    if (sol < sag) 
        return -1;
    else if (sol > sag)
        return 1;
    else {
        assert (sol == sag);
        return 0;
    }
}


void yazdir_helper(rbtree_node n, int step);

void yazdir(rbtree t) {
	yazdir_helper(t->root, 0);
    puts("");
}

void yazdir_helper(rbtree_node n, int step) {
    int i;
    if (n == NULL) {
        fputs("<empty tree>", stdout);
        return;
    }
    if (n->sag != NULL) {
		yazdir_helper(n->sag, step + stepspace);
    }
    for(i=0; i<step; i++)
        fputs(" ", stdout);
    if (n->renk == BLACK)
        printf("%d\n", (int)n->key);
    else
        printf("<%d>\n", (int)n->key);
    if (n->sol != NULL) {
		yazdir_helper(n->sol, step + stepspace);
    }
}





main()
{
	int i, j, x;
	rbtree t = rbtree_olustur();
	yazdir(t);
	while (1) {
		printf("Seçenek Gir");
		printf("1.Ürün Ekle");
		printf("2.Ürün Sil");
		printf("3.Listele");
		printf("4.Çýkýþ");

		scanf("%d", &j);
		switch (j)
		{
		case 1:
			printf("Eklenecek Ürünü Giriniz");
			scanf("%d", &x);
			printf("Eklendi");
			rbtree_ekle(t, (void*)x, compare_int);
			break;
		case 2:
			printf("Silinecek Ürünü Giriniz");
			scanf("%d", &x);
			rbtree_delete(t, (void*)x, compare_int);
			break;
		case 3:
			printf("Ürün Listesi");
			yazdir(t);
			break;
		case 4:
			exit(1);
			break;
		default:
			printf("Geçerli bir sayý giriniz");
			break;
		}
	}
}
