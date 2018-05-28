#include "rbtree.h"
#include <assert.h>
#include <stdlib.h>

node grandparent(node n) {
    assert (n != NULL);
    assert (n->parent != NULL);
    assert (n->parent->parent != NULL);
    return n->parent->parent;
}

node sibling(node n) {
    assert (n != NULL);
    assert (n->parent != NULL);
    if (n == n->parent->sol)
        return n->parent->sag;
    else
        return n->parent->sol;
}

node uncle(node n) {
    assert (n != NULL);
    assert (n->parent != NULL);
    assert (n->parent->parent != NULL);
    return sibling(n->parent);
}

void ozeller(rbtree t) {
	ozel_1(t->root);
	ozel_2(t->root);
	ozel_4(t->root);
	ozel_5(t->root);
}

void ozel_1(node n) {
    assert(node_renk(n) == RED || node_renk(n) == BLACK);
    if (n == NULL) return;
	ozel_1(n->sol);
	ozel_1(n->sag);
}

void ozel_2(node root) {
    assert(node_renk(root) == BLACK);
}

renk node_renk(node n) {
    return n == NULL ? BLACK : n->renk;
}

void ozel_4(node n) {
    if (renk(n) == RED) {
        assert (node_renk(n->sol)   == BLACK);
        assert (node_renk(n->sag)  == BLACK);
        assert (node_renk(n->parent) == BLACK);
    }
    if (n == NULL) return;
	ozel_4(n->sol);
	ozel_4(n->sag);
}

void ozel_5(node root) {
    int siyahsayisip = -1;
	ozel_5_helper(root, 0, &siyahsayisip);
}

void ozel_5_helper(node n, int siyahsayisi, int* psiyahsayisi) {
    if (node_renk(n) == BLACK) {
		siyahsayisi++;
    }
    if (n == NULL) {
        if (*psiyahsayisi == -1) {
            *psiyahsayisi = siyahsayisi;
        } else {
            assert (siyahsayisi == *psiyahsayisi);
        }
        return;
    }
	ozel_5_helper(n->sol, siyahsayisi, psiyahsayisi);
	ozel_5_helper(n->sag, siyahsayisi, psiyahsayisi);
}

rbtree rbtree_olustur() {
    rbtree t = malloc(sizeof(struct rbtree_t));
    t->root = NULL;
    ozeller(t);
    return t;
}

node yeni_node(void* key , renk node_renk, node sol, node sag) {
    node sonuc = malloc(sizeof(struct rbtree_node_t));
	sonuc->key = key;
	sonuc->renk = node_renk;
	sonuc->sol = sol;
	sonuc->sag = sag;
    if (sol  != NULL)  sol->parent = sonuc;
    if (sag != NULL) sag->parent = sonuc;
	sonuc->parent = NULL;
    return sonuc;
}

node incele_node(rbtree t, void* key, karsilastir compare) {
    node n = t->root;
    while (n != NULL) {
        int comp_sonuc = compare(key, n->key);
        if (comp_sonuc == 0) {
            return n;
        } else if (comp_sonuc < 0) {
            n = n->sol;
        } else {
            assert(comp_sonuc > 0);
            n = n->sag;
        }
    }
    return n;
}

void* rbtree_incele(rbtree t, void* key, karsilastir compare) {
    node n = incele_node(t, key, compare);
    return n == NULL ? NULL : n->key;
}

void don_sol(rbtree t, node n) {
    node r = n->sag;
	degistir(t, n, r);
    n->sag = r->sol;
    if (r->sol != NULL) {
        r->sol->parent = n;
    }
    r->sol = n;
    n->parent = r;
}

void don_sag(rbtree t, node n) {
    node L = n->sol;
    degistir(t, n, L);
    n->sol = L->sag;
    if (L->sag != NULL) {
        L->sag->parent = n;
    }
    L->sag = n;
    n->parent = L;
}

void degistir(rbtree t, node eskinode, node yeninode) {
    if (eskinode->parent == NULL) {
        t->root = yeninode;
    } else {
        if (eskinode == eskinode->parent->sol)
			eskinode->parent->sol = yeninode;
        else
			eskinode->parent->sag = yeninode;
    }
    if (yeninode != NULL) {
		yeninode->parent = eskinode->parent;
    }
}

void rbtree_ekle(rbtree t, void* key, karsilastir compare) {
    node eklenmis_node = yeni_node(key, RED, NULL, NULL);
    if (t->root == NULL) {
        t->root = eklenmis_node;
    } else {
        node n = t->root;
        while (1) {
            int comp_sonuc = compare(key, n->key);
            if (comp_sonuc == 0) {
                free (eklenmis_node);
                return;
            } else if (comp_sonuc < 0) {
                if (n->sol == NULL) {
                    n->sol = eklenmis_node;
                    break;
                } else {
                    n = n->sol;
                }
            } else {
                assert (comp_sonuc > 0);
                if (n->sag == NULL) {
                    n->sag = eklenmis_node;
                    break;
                } else {
                    n = n->sag;
                }
            }
        }
		eklenmis_node->parent = n;
    }
    ekle_case1(t, eklenmis_node);
    ozeller(t);
}

void ekle_case1(rbtree t, node n) {
    if (n->parent == NULL)
        n->color = BLACK;
    else
		ekle_case2(t, n);
}

void ekle_case2(rbtree t, node n) {
    if (node_color(n->parent) == BLACK)
        return;
    else
		ekle_case3(t, n);
}

void ekle_case3(rbtree t, node n) {
    if (node_color(uncle(n)) == RED) {
        n->parent->color = BLACK;
        uncle(n)->color = BLACK;
        grandparent(n)->color = RED;
		ekle_case1(t, grandparent(n));
    } else {
		ekle_case4(t, n);
    }
}

void ekle_case4(rbtree t, node n) {
    if (n == n->parent->sag && n->parent == grandparent(n)->sol) {
        don_sol(t, n->parent);
        n = n->sol;
    } else if (n == n->parent->sol && n->parent == grandparent(n)->sag) {
        don_sag(t, n->parent);
        n = n->sag;
    }
	ekle_case5(t, n);
}

void ekle_case5(rbtree t, node n) {
    n->parent->color = BLACK;
    grandparent(n)->color = RED;
    if (n == n->parent->sol && n->parent == grandparent(n)->sol) {
        don_sag(t, grandparent(n));
    } else {
        assert (n == n->parent->sag && n->parent == grandparent(n)->sag);
        don_sol(t, grandparent(n));
    }
}

void rbtree_sil(rbtree t, void* key, karsilastir compare) {
    node child;
    node n = incele_node(t, key, compare);
    if (n == NULL) return; 
    if (n->sol != NULL && n->sag != NULL) {
        node pred = maximum_node(n->sol);
        n->key   = pred->key;
        n = pred;
    }

    assert(n->sol == NULL || n->sag == NULL);
    child = n->sag == NULL ? n->sol  : n->sag;
    if (node_renk(n) == BLACK) {
        n->renk = node_renk(child);
        sil_case1(t, n);
    }
	degistir(t, n, child);
    if (n->parent == NULL && child != NULL)
        child->renk = BLACK;
    free(n);

    ozeller(t);
}

static node maximum_node(node n) {
    assert (n != NULL);
    while (n->sag != NULL) {
        n = n->sag;
    }
    return n;
}

void sil_case1(rbtree t, node n) {
    if (n->parent == NULL)
        return;
    else
		sil_case2(t, n);
}

void sil_case2(rbtree t, node n) {
    if (node_renk(sibling(n)) == RED) {
        n->parent->renk = RED;
        sibling(n)->renk = BLACK;
        if (n == n->parent->sol)
           don_sol(t, n->parent);
        else
            don_sag(t, n->parent);
    }
	sil_case3(t, n);
}

void sil_case3(rbtree t, node n) {
    if (node_renk(n->parent) == BLACK &&
        node_renk(sibling(n)) == BLACK &&
        node_renk(sibling(n)->sol) == BLACK &&
        node_renk(sibling(n)->sag) == BLACK)
    {
        sibling(n)->renk = RED;
		sil_case1(t, n->parent);
    }
    else
		sil_case4(t, n);
}

void sil_case4(rbtree t, node n) {
    if (node_renk(n->parent) == RED &&
        node_renk(sibling(n)) == BLACK &&
        node_renk(sibling(n)->sol) == BLACK &&
        node_renk(sibling(n)->sag) == BLACK)
    {
        sibling(n)->renk = RED;
        n->parent->renk = BLACK;
    }
    else
		sil_case5(t, n);
}

void sil_case5(rbtree t, node n) {
    if (n == n->parent->sol &&
        node_renk(sibling(n)) == BLACK &&
        node_renk(sibling(n)->sol) == RED &&
        node_renk(sibling(n)->sag) == BLACK)
    {
        sibling(n)->renk = RED;
        sibling(n)->sol->renk = BLACK;
        don_sag(t, sibling(n));
    }
    else if (n == n->parent->sag &&
             node_renk(sibling(n)) == BLACK &&
             node_renk(sibling(n)->sag) == RED &&
             node_renk(sibling(n)->sol) == BLACK)
    {
        sibling(n)->renk = RED;
        sibling(n)->sag->renk = BLACK;
        don_sol(t, sibling(n));
    }
	sil_case6(t, n);
}

void sil_case6(rbtree t, node n) {
    sibling(n)->renk = node_renk(n->parent);
    n->parent->renk = BLACK;
    if (n == n->parent->sol) {
        assert (node_renk(sibling(n)->sag) == RED);
        sibling(n)->sag->renk = BLACK;
        don_sol(t, n->parent);
    }
    else
    {
        assert (node_renk(sibling(n)->sol) == RED);
        sibling(n)->sol->renk = BLACK;
       don_sag(t, n->parent);
    }
}


