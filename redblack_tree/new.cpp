#include <iostream>

using namespace std

int main()
{
int i, j, x;
	rbtree t = rbtree_olustur();
	yazdir(t);
	while (1) {
		printf("Seçenek Gir");
		printf("1.Ürün Ekle");
		printf("2.Ürün Sil");
		printf("3.Listele");
		printf("4.Çıkış");

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
			printf("Geçerli bir sayı giriniz");
			break;
		}
	}
}
