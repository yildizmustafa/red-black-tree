enum rbtree_node_renk { RED, BLACK };

typedef struct rbtree_node_t {
    void* key;
    struct rbtree_node_t* sol;
    struct rbtree_node_t* sag;
    struct rbtree_node_t* parent;
    enum rbtree_node_renk renk;
} *rbtree_node;

typedef struct rbtree_t {
    rbtree_node root;
} *rbtree;

typedef int (*karsilastir)(void* sol, void* sag);

rbtree rbtree_olustur();
void* rbtree_incele(rbtree t, void* key, karsilastir compare);
void rbtree_ekle(rbtree t, void* key, karsilastir compare);
void rbtree_sil(rbtree t, void* key, karsilastir compare);
typedef rbtree_node node;
typedef enum rbtree_node_renk renk;


static node grandparent(node n);
static node sibling(node n);
static node uncle(node n);
static void ozeller(rbtree t);
static void ozel_1(node root);
static void ozel_2(node root);
static renk node_renk(node n);
static void ozel_4(node root);
static void ozel_5(node root);
static void ozel_5_helper(node n, int siyahsayisi, int* siyahsayisip);

static node yeni_node(void* key, renk node_renk, node sol, node sag);
static node incele_node(rbtree t, void* key, karsilastir compare);
static void don_sol(rbtree t, node n);
static void don_sag(rbtree t, node n);


static void degistir(rbtree t, node eskinode, node yeninode);
static void ekle_case1(rbtree t, node n);
static void ekle_case2(rbtree t, node n);
static void ekle_case3(rbtree t, node n);
static void ekle_case4(rbtree t, node n);
static void ekle_case5(rbtree t, node n);
static node maximum_node(node root);
static void sil_case1(rbtree t, node n);
static void sil_case2(rbtree t, node n);
static void sil_case3(rbtree t, node n);
static void sil_case4(rbtree t, node n);
static void sil_case5(rbtree t, node n);
static void sil_case6(rbtree t, node n);
