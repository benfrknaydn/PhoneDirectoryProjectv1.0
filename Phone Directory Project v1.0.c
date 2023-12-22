#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <curses.h>
struct telephone {
    char isim[50];
    char kod[15];
    char numara[11];
};

int menuHazirla(void);
//void AramaYap(void);
//void MesajAt(void);
int telefonEkle(void);
int telefonlariListele(void);
int isimaramasiYap(char *);
int numaraaramasiYap(char *);
void duzenleme(void);
void KayitSil(void);

int menuHazirla(void) {
    printf("\t\t                                         \n");
    printf("\t\t*---------------------------------------*\n");
    printf("\t\t|                                       |\n");
    printf("\t\t|           TELEFON REHBERİ             |\n");
    printf("\t\t|               ANA MENÜ                |\n");
    printf("\t\t|                                       |\n");
    printf("\t\t|                                       |\n");
    printf("\t\t|          1. YENİ KAYIT                |\n");
    printf("\t\t|          2. TELEFONLARI LİSTELE       |\n");
    printf("\t\t|          3. KAYDI DÜZENLE             |\n");
    printf("\t\t|          4. NUMARA İLE KAYDI BUL      |\n");
    printf("\t\t|          5. İSİM İLE KAYDI BUL        |\n");
    printf("\t\t|          6. KAYIT SİL                 |\n");
    printf("\t\t|          0. ÇIKIŞ                     |\n");
    printf("\t\t|                                       |\n");
    printf("\t\t*---------------------------------------*\n");
    printf("\t\t                                         \n");
      
      return 1;
}

int telefonEkle(void) {
    printf("\n\n\t\t           TELEFON EKLEME          \n\n");
    struct telephone yeniKayit;
    FILE *ptVeritabani;

    // dosyaya ac:
    if ((ptVeritabani = fopen("TelefonRehber.rtf", "a")) == NULL) {
        return -1;
    }

    printf("\n\n");
    printf("Lütfen isim giriniz(max 15 karakter): ");
    scanf("%s", yeniKayit.isim);
    printf("Kod giriniz(max 100 e kadar): ");
    scanf("%s", yeniKayit.kod);
    printf("Lütfen telefon numarasini giriniz: ");
    scanf("%s", yeniKayit.numara);

    if (fwrite(&yeniKayit, sizeof(yeniKayit), 1, ptVeritabani) != 1) {
        printf("Yazmım hatasi!\n");
        exit(1);
    }

    printf("\n");
    fclose(ptVeritabani);
    return 0;
}

int telefonlariListele(void) {
    printf("\n\n\t\t         TELEFON LİSTELEME          \n\n");

    // dosyadaki tum telefonlari listele
    // dosyaya ac:
    FILE *ptVeritabani;
    struct telephone aktifKayit;

    if ((ptVeritabani = fopen("TelefonRehber.rtf", "r")) == NULL) {
        return -1;
    }

    printf("\n\nİSİM\t\t\t     KOD\t\t    TELEFON NO\n");
    printf("-----\t\t\t     ----\t\t    ----------\n");

    // dosya sonuna kadar tum verileri oku:
    while (!feof(ptVeritabani)) {
        if (fread(&aktifKayit, sizeof(aktifKayit), 1, ptVeritabani) != 1) {
            continue;
        }

        printf("%s\t\t      ", aktifKayit.isim);
        printf("%s\t\t     ", aktifKayit.kod);
        printf("%s\n", aktifKayit.numara);
    }

    fclose(ptVeritabani);
    return 0;
}

void duzenleme(void) {
    int i = 0, p, l;
    FILE *ptVeritabani;
    FILE *tp; ///temporary-gecici isareti
    tp = fopen("TelefonRehber-2.rtf", "wb+");
    ptVeritabani = fopen("TelefonRehber.rtf", "rb+");
    struct telephone aktifKayit;
    char dtel[15];

    printf("\nDüzeltilecek kişinin numarasını giriniz:");
    scanf("%s", dtel);

    while (!feof(ptVeritabani)) {
        i++;
        fread(&aktifKayit, sizeof(aktifKayit), 1, ptVeritabani);
        if (strcmp(aktifKayit.numara, dtel) == 0) {
            p = 10;
            printf("Yeni isim:");
            scanf("%s", aktifKayit.isim);
            printf("Yeni kod:");
            scanf("%s", aktifKayit.kod);
            printf("Yeni numara:");
            scanf("%s", aktifKayit.numara);
        }

        if (feof(ptVeritabani)) {
            break;
        }

        fseek(tp, (i - 1) * sizeof(aktifKayit), 0);
        fwrite(&aktifKayit, sizeof(aktifKayit), 1, tp);
    }

    if (p != 10) {
        printf("Kayıt bulunamadı.\n");
        printf("Tekrar kayıt düzenleme yapmak için 1 e basınız:\n");
        printf("Ana menüye dönmek için 2 ye basınız:\t");
        scanf("%d", &l);

        if (l == 1)
            duzenleme();
        if (l == 2)
              menuHazirla();
    }

    fclose(ptVeritabani);
    remove("TelefonRehber.rtf");
    fclose(tp);
    rename("TelefonRehber-2.rtf", "TelefonRehber.rtf");
}

int isimaramasiYap(char *arananIsim) {
    printf("\n\n\t\t*         İSİM ARAMA          *\n\n");

    // dosyadaki tum telefonlarini ara
    // dosyaya ac:
    FILE *ptVeritabani;
    struct telephone aktifKayit;
    int bulunan = 0;

    if ((ptVeritabani = fopen("TelefonRehber.rtf", "r")) == NULL) {
        return -1;
    }

    // dosya sonuna kadar tum verileri oku:
    while (!feof(ptVeritabani)) {
        if (fread(&aktifKayit, sizeof(aktifKayit), 1, ptVeritabani) != 1) {
            continue;
        }

        if (!strcmp(arananIsim, aktifKayit.isim)) { // bulundu!
            printf("%s\t\t\t", aktifKayit.isim);
            printf("%s\t\t\t", aktifKayit.kod);
            printf("%s\n", aktifKayit.numara);
            bulunan++;
        }
    }

    fclose(ptVeritabani);
    return bulunan;
}

int numaraaramasiYap(char *arananNumara) {
    printf("\n\n\t\t*         NUMARA ARAMA         *\n\n");

    // dosyadaki tum telefonlarini ara
    // dosyaya ac:
    FILE *ptVeritabani;
    struct telephone aktifKayit;
    int bulunan2 = 0;

    if ((ptVeritabani = fopen("TelefonRehber.rtf", "r")) == NULL) {
        return -1;
    }

    // dosya sonuna kadar tum verileri oku:
    while (!feof(ptVeritabani)) {
        if (fread(&aktifKayit, sizeof(aktifKayit), 1, ptVeritabani) != 1) {
            continue;
        }

        if (!strcmp(arananNumara, aktifKayit.numara)) { // bulundu!
            printf("%s\t\t\t", aktifKayit.isim);
            printf("%s\t\t\t", aktifKayit.kod);
            printf("%s\n", aktifKayit.numara);
            bulunan2++;
        }
    }

    fclose(ptVeritabani);
    return bulunan2;
}

void KayitSil(void) {
    printf("\n\n\t\t*         KAYIT SİLME          *\n\n");

    int e = 0, v, a;
    FILE *ptVeritabani;
    FILE *gecicibellek; ///temporary-geçici işaretçi
    gecicibellek = fopen("TelefonRehber-3.rtf", "wb+");
    ptVeritabani = fopen("TelefonRehber.rtf", "rb+");
    struct telephone aktifKayit;
    char kod2[15];

    printf("\nSilinecek kisinin kodunu giriniz:");
    scanf("%s", kod2);

    while (!feof(ptVeritabani)) {
        e++;
        fread(&aktifKayit, sizeof(aktifKayit), 1, ptVeritabani);

        if (strcmp(aktifKayit.kod, kod2) == 0) {
            v = 100;
            continue;
        }

        if (feof(ptVeritabani)) {
            break;
        }

        if (feof(ptVeritabani)) {
            continue;
        }

        fseek(gecicibellek, (e - 1) * sizeof(aktifKayit), 0);
        fwrite(&aktifKayit, sizeof(aktifKayit), 1, gecicibellek);
    }

    if (v != 100) {
        printf("kayıt bulunamadı\n");
        printf("tekrar kayıt silme yapmak için 1 e basınız:\n");
        printf("Ana menüye dönmek için 2 ye basınız:\t");
        scanf("%d", &a);

        if (a == 1)
            KayitSil();
        if (a == 2)
              menuHazirla();
    }

    fclose(ptVeritabani);

    // Dosya silinir.
    remove("TelefonRehber.rtf");
    fclose(gecicibellek);

    // Geçici dosyanın ismi asıl dosya ismi değiştirilir.
    rename("TelefonRehber-3.rtf", "TelefonRehber.rtf");
}

int main(void) {
    setlocale(LC_ALL, "Turkish");
    char arananNumara[11];
    char secim = '0';
    char aranacakIsim[16];
    int numaraAra = -1;
    int numaraAra2 = -1;
    struct telephone aktifKayit;
    struct telephone yeniKayit;

    // Menu hazırla:
    menuHazirla();

    do {
        printf("\n\nSeciminiz: ");
        secim = getchar(); // Kullanıcının girişini okumak için getchar() kullanın.

        switch (secim) {
            case '1':
                if (telefonEkle() == 0) {
                    printf("\nTelefon numarasi basariyla eklendi.");
                } else {
                    printf("\nHATA: Telefon numarasi eklenemedi!");
                }
                break;
            case '2':
                if (telefonlariListele() == 0) {
                    printf("\nTelefonlar basariyla listelendi.");
                } else {
                    printf("\nHATA: Telefon numaralari listelenemedi!");
                }
                break;
            case '3':
                duzenleme();
                break;
            case '4':
                printf("\nAranacak numarayi giriniz(max 10 karakter):");
                scanf("%s", arananNumara);
                numaraAra2 = numaraaramasiYap(arananNumara);
                if (numaraAra2 == 0) {
                    printf("\nAranan numara kayitlarda bulunamadi.");
                } else {
                    if (numaraAra2 > 0)
                        printf("\nToplam %d kayit bulundu.", numaraAra2);
                    else
                        printf("\nHATA: Numara aranamadı!");
                }
                break;
            case '5':
                printf("\nAranacak ismi giriniz(max 15 karakter):");
                scanf("%s", aranacakIsim);
                numaraAra = isimaramasiYap(aranacakIsim);
                if (numaraAra == 0) {
                    printf("\nAranan isim kayitlarda bulunamadi.");
                } else {
                    if (numaraAra > 0)
                        printf("\nToplam %d kayit bulundu.", numaraAra);
                    else
                        printf("\nHATA: İsim aranamadi!");
                }
                break;
            case '6':
                KayitSil();
                printf("Kayit basariyla silindi!\n");
                break;
            case '0':
                printf("\nProgrami kullandiginiz icin tesekkurler.");
                return 0;
                break;
            default:
                printf("\nLutfen 1-6 arasinda bir secim yapiniz.");
        }
    } while (secim != '6');
    return 0;
}

