//operacje morfologiczne na obrazach binarnych
//£ukasz Wa¿ny

//wykorzystywana biblioteka graficzna - stb_image

//element strukturalny - dowolny kszta³t - punkt centralny to piksel o wartoœci miejszej ni¿ 10 - reszta pikseli ma wartoœæ wiêksz¹ ni¿ 245

//piksel o wartosci mniejszej ni¿ 10 - czarny, o wartoœci wiêkszej ni¿ 245 - bialy


#include "morfologia.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STBI_MSC_SECURE_CRT
#include "stb_image_write.h"

#include <vld.h>


int main (int argc, char **argv) //wejscie: plik wejsciowy, plik wyjsciowy, elem strukturalny, operacja
{	
	if (argc != 5)
	{
		printf("Nieprawidlowa liczba parametrow!\n");
	}
	else
	{
		int elem_width, elem_height, elem_n;
		unsigned char *elem = stbi_load(argv[3], &elem_width, &elem_height, &elem_n, 1);
		if (elem == NULL)
		{
			printf("Nie udalo sie otworzyc elementu strukturalnego!\n");
		}
		else
		{
			int plik_we_width, plik_we_height, plik_we_n;
			unsigned char * plik_we = stbi_load(argv[1], &plik_we_width, &plik_we_height, &plik_we_n, 1);
				
			if (plik_we == NULL)
			{
				printf("Nie udalo sie otworzyc pliku wejsciowego!\n");
			}
			else
			{
				char * wejscie[6] = { "-dylatacja", "-erozja", "-otwarcie", "-domkniecie", "-top_hat", "-bottom_hat"};
				if (strcmp(argv[4], wejscie[0]) && strcmp(argv[4], wejscie[1]) && strcmp(argv[4], wejscie[2]) && strcmp(argv[4], wejscie[3]) && strcmp(argv[4], wejscie[4]) && strcmp(argv[4], wejscie[5]))
				{
					printf("Nieprawidlowa nazwa operacji!\n");
				}
				else
				{
					int pkt_centralny_x, pkt_centralny_y;
					if (pkt_centralny(elem, elem_width, elem_height, &pkt_centralny_x, &pkt_centralny_y) == -1)
					{
						printf("Nie znaleziono punktu centralnego w elemencie strukturalnym!\n");
					}
					else
					{
						unsigned char * bufor;
						if (!strcmp(argv[4], wejscie[0]))
						{
							bufor = dylatacja(plik_we, plik_we_width, plik_we_height, elem_width, elem_height, pkt_centralny_x, pkt_centralny_y);
						}
						if (!strcmp(argv[4], wejscie[1]))
						{
							bufor = erozja(plik_we, plik_we_width, plik_we_height, elem_width, elem_height, pkt_centralny_x, pkt_centralny_y);
						}
						if (!strcmp(argv[4], wejscie[2]))
						{
							//otwarcie, najpierw erozja, potem dylatacja
							bufor = otwarcie(plik_we, plik_we_width, plik_we_height, elem_width, elem_height, pkt_centralny_x, pkt_centralny_y);
						}
						if (!strcmp(argv[4], wejscie[3]))
						{
							//domkniêcie, najpierw dylatacja, potem erozja
							bufor = domkniecie(plik_we, plik_we_width, plik_we_height, elem_width, elem_height, pkt_centralny_x, pkt_centralny_y);
						}
						if (!strcmp(argv[4], wejscie[4]))
						{
							//top hat, od Ÿród³a odejmujemy ¿ród³o po otwarciu, czarne piksele to lokalne maksimum
							bufor = top_hat(plik_we, plik_we_width, plik_we_height, elem_width, elem_height, pkt_centralny_x, pkt_centralny_y);
						}
						if (!strcmp(argv[4], wejscie[5]))
						{
							//bottom hat, od Ÿród³a po domknieciu odejmujemy Ÿród³o, czarne piksele to lokalne minimum 
							bufor = bottom_hat(plik_we, plik_we_width, plik_we_height, elem_width, elem_height, pkt_centralny_x, pkt_centralny_y);
						}

						if (!stbi_write_png(argv[2], plik_we_width, plik_we_height, 1, bufor, plik_we_width))
						{
							printf("Nie udalo sie zapisac pliku!");
						}
						free(bufor);
					}
				}
				stbi_image_free(plik_we);
			}
			stbi_image_free(elem);
		}
	}
}