#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    // Rastgele sayi uretimi icin baslangic
    srand(time(NULL));

    // Durum Degiskenleri
    int saglik = 100;
    int enerji = 100;
    int oksijen = 100;
    int suMiktari = 0;
    int yedekParca = 0;
    int modulHasari = 0;
    int kilitMuhurlu = 0; // 0: Muhurlu degil, 1: Muhurlu
    int gun = 1;
    int tur = 0;
    
    char zorlukSecimi;
    int firtinaTurSayisi = 0;

    // Zorluk Seviyesi Secimi (Ayrilmis Switch-Case)
    while (1) { 
        printf("Zorluk Seviyesi Seciniz (K: Kolay, N: Normal, Z: Zor): ");
        scanf(" %c", &zorlukSecimi);

        switch (zorlukSecimi) {
            case 'k':
            case 'K':
               suMiktari = 60; 
                yedekParca = 4;
                firtinaTurSayisi = 3;
                printf("Kolay seviye secildi.\n");
                break;
            case 'n':
            case 'N':
                suMiktari = 40;
                yedekParca = 2;
                firtinaTurSayisi = 5;
                printf("Normal seviye secildi.\n");
                break;
            case 'z':
            case 'Z':
                suMiktari = 20;
                yedekParca = 1;
                firtinaTurSayisi = 7;
                printf("Zor seviye secildi.\n");
                break;
            default:
                printf("Gecersiz secim! Tekrar deneyiniz.\n");
                continue; // Gecersiz durumda secimi tekrar ister
        }
        break;
    }

    char komut;
    int oyunBitti = 0;

    // Ana Komut Dinleme Dongusu (Do-While)
    do {
        int turArtacak = 0; // Gecerli komutlarda tur artisi icin bayrak

        printf("\n--------------------------------------------------\n");
        printf("Gun: %d | Tur: %d | Saglik: %d | Enerji: %d | Oksijen: %d\n", gun, tur, saglik, enerji, oksijen);
        printf("Su: %d | Parca: %d | Hasar: %d | Kilitli: %d\n", suMiktari, yedekParca, modulHasari, kilitMuhurlu);
        printf("Komutlar: [G]esif, [O]ksijen Uret, [T]amir, [D]urum Raporu, [U]yu, [K]um Firtinasi, [H]ava Kilidi, [Q]Cikis\n");
        printf("Komutunuz: ");
        scanf(" %c", &komut);

        // SWITCH-CASE ve Fall-Through (Buyuk/Kucuk Harf Duyarsiz)
        switch (komut) {
            case 'g':
            case 'G': {
                // Enerji kontrolu
                if (enerji < 15) {
                    printf("Yetersiz kaynak: Kesif icin yeterli enerjiniz yok!\n");
                    break;
                }

                enerji -= 15;
                oksijen -= 10;
                turArtacak = 1;

                int zar = rand() % 100;
                
                // Mantiksal operatorler ile su bulma ve esik deger kontrolu
                if (enerji > 40 && oksijen > 30) {
                    printf("Zar: %d / Esik: 50 -> BASARILI\n", zar);
                    if (zar < 33) {
                        suMiktari += 15;
                        printf("Sonuc: Su bulundu! (+15 su)\n");
                    } else if (zar < 66) {
                        yedekParca += 1;
                        printf("Sonuc: Yedek parca bulundu! (+1 parca)\n");
                    } else {
                        printf("Sonuc: Bolge arandi ancak bisi bulunamadi.\n");
                    }
                } else {
                    printf("Zar: %d / Esik: 30 -> DUSUK SEVIYE\n", zar);
                    if (zar < 20) {
                        suMiktari += 10;
                        printf("Sonuc: Az miktarda su bulundu! (+10 su)\n");
                    } else {
                        printf("Sonuc: Eli bostan donuldu.\n");
                    }
                }

                // Yaralanma kontrolu
                int yaraZar = rand() % 100;
                if (yaraZar < 10 || modulHasari > 70) {
                    saglik -= 15;
                    printf("KRITIK: Kesif sirasinda yaralandiniz! (-15 saglik)\n");
                }
                break;
            }

            case 'o':
            case 'O': {
                int istenenSu;
                printf("Harcanacak su miktarini girin (Mevcut Su: %d): ", suMiktari);
                scanf("%d", &istenenSu);

                if (istenenSu <= 0||  istenenSu > suMiktari) {
                    printf("Gecersiz veya depodakinden fazla su girdiniz!\n");
                    break;
                }
                if (enerji < 10) {
                    printf("Yetersiz kaynak: Enerjiniz yetersiz!\n");
                    break;
                }

                enerji -= 10;
                suMiktari -= istenenSu;
                turArtacak = 1;

                // Mod operatoru ile artik su kontrolu
                int donusenSu = istenenSu - (istenenSu % 2);
                int artikSu = istenenSu % 2;
                suMiktari += artikSu; // Tek kalan birimi geri depoya ver

                int uretilenOksijen = (donusenSu / 2) * 3;
                oksijen += uretilenOksijen;

                printf("Basarili: %d birim su harcandi, %d birim oksijen uretildi. Artan su: %d\n", istenenSu, uretilenOksijen, artikSu);
                break;
            }

            case 't':
            case 'T': {
                if (yedekParca <= 0) {
                    printf("Yetersiz kaynak: Hic yedek parcaniz yok!\n");
                    break;
                }
                if (enerji < 10) {
                    printf("Yetersiz kaynak: Enerjiniz yetersiz!\n");
                    break;
                }
                if (modulHasari == 0) {
                    printf("Modulde zaten hic hasar yok.\n");
                    break;
                }

                enerji -= 10;
                yedekParca -= 1;
                turArtacak = 1;

                // IF-ELSE IF-ELSE kademeli tamir
                if (modulHasari <= 30) {
                    modulHasari -= 15;
                    printf("Hafif hasar giderildi. (-15 Hasar)\n");
                } else if (modulHasari <= 70) {
                    modulHasari -= 25;
                    printf("Orta seviye hasar giderildi. (-25 Hasar)\n");
                } else {
                    modulHasari -= 35;
                    printf("Agir hasar onarildi! (-35 Hasar)\n");
                }
                break;
            }

            case 'd':
            case 'D': {
                printf("\n--- DURUM RAPORU ---\n");
                printf("Saglik: %d | Enerji: %d | Oksijen: %d\n", saglik, enerji, oksijen);
                printf("Su: %d | Yedek Parca: %d | Modul Hasari: %d\n", suMiktari, yedekParca, modulHasari);
                
                // Kritik uyari kontrolleri
                if (oksijen < 25) printf("[UYARI] Oksijen kritik seviyede (<25)!\n");
                if (saglik < 30) printf("[UYARI] Saglik kritik seviyede (<30)!\n");
                if (modulHasari > 70) printf("[UYARI] Modul hasari cok yuksek (>70)!\n");

                // && ile birlestirilmis tek kosul
                if (oksijen >= 25 && saglik >= 30 && modulHasari <= 70) {
                    printf("TUM SISTEMLER NORMAL\n");
                }
                break; // D komutu tur harcamaz
            }

            case 'u':
            case 'U': {
                enerji += 25;
                turArtacak = 1;

                // Ic ice if kontrolu
                if (oksijen < 20) {
                    saglik -= 10;
                    printf("Uyari: Oksijen 20'nin altinda oldugu icin dinlenirken saglik kaybettiniz!\n");
                } else {
                    saglik += 15;
                    printf("Dinlenildi. Enerji ve saglik artti.\n");
                }
                break;
            }

            case 'k':
            case 'K': {
                printf("\n[FIRTINA] Kum firtinasi basladi! Sure: %d tur.\n", firtinaTurSayisi);
                
                // FOR Dongusu ile Kum Firtinasi
                for (int i = 1; i <= firtinaTurSayisi; i++) {
                    int firtinaZar = rand() % 100;
                    int etkiCarpani = (i % 2 == 0) ? 2 : 1; // Cift numarali turlarda mod ile artis

                    printf("Tur %d/%d (Carpan: %d): ", i, firtinaTurSayisi, etkiCarpani);

                    // Hava kilidi muhurlu ise continue ile oksijen sizintisi atlaniyor
                    if (kilitMuhurlu == 1) {
                        printf("Hava kilidi muhurlu, sizinti onlendi!\n");
                        continue;
                    }

                    if (firtinaZar < 50) {
                        oksijen -= (5 * etkiCarpani);
                        saglik -= (5 * etkiCarpani);
                        modulHasari += (10 * etkiCarpani);
                        printf("Zar: %d -> Hasar alindi!\n", firtinaZar);
                    } else {
                        printf("Zar: %d -> Firtina hafif atlatildi.\n", firtinaZar);
                    }

                    // Sınırlandırma kontrolü
                    if (saglik < 0) saglik = 0;
                    if (oksijen < 0) oksijen = 0;
                    if (modulHasari > 100) modulHasari = 100;

                    // Saglik veya oksijen 0 olursa break ile donguden cikilir
                    if (saglik <= 0 || oksijen <= 0) {
                        printf("Firtina sirasinda degerler bitti!\n");
                        break;
                    }
                }

                turArtacak = 1;
                break;
            }

            case 'h':
            case 'H': {
                // DO-WHILE Dongusu ile Hava Kilidi Sifresi
                char dogruSifre = 'A' + (gun % 26);
                int denemeHakki = 3;
                char girilenHarf;
                int sifreBildin = 0;

                printf("Hava Kilidi Sifresi! Ipucu: Sifre, alfabede 'A' harfinden gun sayisi (%d) kadar ilerideki harftir.\n", gun);

                do {
                    printf("Kalan hak (%d). Harf girin (A-Z): ", denemeHakki);
                    scanf(" %c", &girilenHarf);

                    // Kucuk harfi buyuk harfe cevirme
                    if (girilenHarf >= 'a' && girilenHarf <= 'z') {
                        girilenHarf -= 32;
                    }

                    if (girilenHarf == dogruSifre) {
                        sifreBildin = 1;
                        break;
                    } else {
                        denemeHakki--;
                        enerji -= 5;
                        if (girilenHarf < dogruSifre) {
                            printf("Yanlis! Ileri git (daha sonraki harf).\n");
                        } else {
                            printf("Yanlis! Geri git (daha onceki harf).\n");
                        }
                    }
                } while (denemeHakki > 0 && sifreBildin == 0);

                if (sifreBildin) {
                    kilitMuhurlu = 1;
                    printf("Basarili! Hava kilidi muhurlendi.\n");
                } else {
                    modulHasari += 20;
                    printf("Deneme hakki bitti! Modul hasari 20 artti.\n");
                }

                turArtacak = 1;
                break;
            }

            case 'q':
            case 'Q': {
                oyunBitti = 1;
                printf("Oyundan cikis yapildi.\n");
                break;
            }

            default: {
                printf("Tanimssiz komut girdiniz! Tur harcanmadi.\n");
                break;
            }
        }

        // Genel Sınırlandırma Kontrolleri (0 - 100 Arasi)
        if (saglik < 0) saglik = 0;
        if (saglik > 100) saglik = 100;
        if (enerji < 0) enerji = 0;
        if (enerji > 100) enerji = 100;
        if (oksijen < 0) oksijen = 0;
        if (oksijen > 100) oksijen = 100;
        if (modulHasari < 0) modulHasari = 0;
        if (modulHasari > 100) modulHasari = 100;

        // Oyun Bitis Kontrolu (Can veya Oksijen 0 oldu mu?)
        if (saglik <= 0 || oksijen <= 0) {
            oyunBitti = 1;
            printf("\n--- OYUN KAYBEDILDI (Karakter oldu veya oksijen bitti) ---\n");
            break;
        }

        // Zaman Akisi ve Gun Baslangici Kontrolu
        if (turArtacak && !oyunBitti) {
            tur++;
            
            // Her 3 turda bir yeni gun baslar (Mod operatoru)
            if (tur % 3 == 0) {
                gun++;
                oksijen -= 8;
                printf("\n>>> Yeni Gun Basladi! Gun: %d (Oksijen -8 azaldi) <<<\n", gun);

                if (modulHasari > 70) {
                    saglik -= 5;
                    printf("KRITIK: Modul hasari 70 uzerinde oldugu icin ek 5 saglik kaybedildi!\n");
                }
            }

            // 15. Gun Tamamlama Kontrolu (Kazanma)
            if (gun > 15) {
                oyunBitti = 1;
                printf("\n--- TEBRIKLER! 15 GÜN TAMAMLANDI, KURTARMA EKIBI GELDI (KAZANILDI) ---\n");
                break;
            }
        }

    } while (!oyunBitti);

    // Sonuc Raporu ve Puan Hesabi
    int puan = (gun * 100) + saglik + oksijen - modulHasari;
    printf("\n========================================\n");
    printf("             SONUC RAPORU\n");
    printf("========================================\n");
    printf(" Hayatta Kalinan Gun : %d\n", gun);
    printf(" Toplam Tur Sayisi   : %d\n", tur);
    printf(" Son Saglik          : %d\n", saglik);
    printf(" Son Enerji          : %d\n", enerji);
    printf(" Son Oksijen         : %d\n", oksijen);
    printf(" Son Modul Hasari    : %d\n", modulHasari);
    printf(" TOPLAM PUAN         : %d\n", puan);
    printf("========================================\n");

    return 0;
}