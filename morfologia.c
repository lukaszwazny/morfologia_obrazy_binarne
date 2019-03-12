//element strukturalny - dowolny kszta³t - punkt centralny to piksel o wartoœci miejszej ni¿ 10 - reszta pikseli ma wartoœæ wiêksz¹ ni¿ 245

//piksel o wartosci mniejszej ni¿ 10 - czarny, o wartoœci wiêkszej ni¿ 245 - bialy

#include <stdlib.h>


//funkcja szuka wspó³rzêdnych punktu centralnego, parametry: elem - wskaŸnik na otwarty plik z elementem strukturalnym;
//elem_width - szerokoœæ elementu strukturalnego; elem_height - wysokoœæ elementu strukturalnego;
//pkt_centralny_x - wskaŸnik na zmienn¹, w której ma byæ zapisana wspó³rzêdna x punktu centralnego;
//pkt_centralny_y - wskaŸnik na zmienn¹, w której ma byæ zapisana wspó³rzêdna y punktu centralnego;
//funkcja zwraca wartoœæ 0, je¿eli uda³o siê znaleŸæ punkt centralny (jego odpowiednie wspó³rzêdne po wywo³aniu funkcji znajduj¹ siê w zmiennych,
//na które wskazuj¹ wskaŸniki pkt_centralny_x oraz pkt_centralny_y); natomiast je¿eli siê nie uda³o znaleŸæ tego¿ punktu zwracana jest wartoœæ -1
int pkt_centralny(unsigned char *elem, int elem_width, int elem_height, int * pkt_centralny_x, int * pkt_centralny_y)
{
	unsigned char * pkt = elem;
	int pkt_x = *pkt_centralny_x;
	int pkt_y = *pkt_centralny_y;
	for (pkt_y = 0; pkt_y < elem_height; pkt_y++)
	{
		for (pkt_x = 0; pkt_x < elem_width; pkt_x++)
		{
			if (*pkt < 10)
			{
				break;
			}
			pkt = ++elem;
		}
		if (*pkt < 10)
		{
			break;
		}
	}

	if (*pkt >= 10)
	{
		return -1;
	}
	else
	{
		*pkt_centralny_x = pkt_x;  //wsp. x pkt centralnego (0,1,2,...)
		*pkt_centralny_y = pkt_y;  //wsp. y pkt centralnego (0,1,2,...)
		return 0;
	}
}

//funkcja wykonuje operacjê dylatacji pliku Ÿród³owego i zwraca otrzymany wynik (przekszta³cony obraz) w formie wskaŸnika na dane, które mo¿na
//zapisaæ do pliku w formacie graficznym; parametry: plik_we - wskaŸnik na otwarty plik z obrazem Ÿród³owym, który chcemy poddaæ dylatacji;
//plik_we_width - szerokoœæ obrazu Ÿród³owego; plik_we_height - wysokoœæ obrazu Ÿród³owego; elem_width - szerokoœæ elementu strukturalnego;
//elem_height - wysokoœæ elementu strukturalnego; pkt_centr_x - wspó³rzêdna x punktu centralnego; pkt_centr_y - wspó³rzêdna y punktu centralnego
unsigned char * dylatacja(const unsigned char * plik_we, int plik_we_width, int plik_we_height, int elem_width, int elem_height, int pkt_centr_x, int pkt_centr_y)
{
	unsigned char * bufor;
	bufor = (unsigned char*)malloc(plik_we_width*plik_we_height * sizeof(unsigned char));

	//kopiujê dane z plik_we do bufora
	for (int j = 0; j < plik_we_height; j++)
	{
		for (int i = 0; i < plik_we_width; i++)
		{
			bufor[i + j * plik_we_width] = plik_we[i + j * plik_we_width];
		}
	}

	for (int h = 0; h < plik_we_height; h++)
	{
		for (int w = 0; w < plik_we_width; w++)
		{
			//sprawdzam, czy w obrebie elementu strukturalnego sa piksele o wartosci < 10, je¿eli tak - piksel o wsp. w i h,
			//przyjmuje wartoœæ 0
			if (h <= pkt_centr_y && w <= pkt_centr_x)
			{
				int czy_jest = 0;
				for (int j = 0; j < elem_height - h && h + j < plik_we_height && !czy_jest; j++)
				{
					for (int i = 0; i < elem_width - w && w + i < plik_we_width && !czy_jest; i++)
					{
						if (plik_we[i + j * plik_we_width] < 10)
						{
							czy_jest = 1;
							bufor[w + h * plik_we_width] = 0;
						}
					}
				}
			}
			else
			{
				if (h <= pkt_centr_y)
				{
					int czy_jest = 0;
					for (int j = 0; j < elem_height - h && h + j < plik_we_height && !czy_jest; j++)
					{
						for (int i = 0; i < elem_width && w + i < plik_we_width && !czy_jest; i++)
						{
							if (plik_we[w - pkt_centr_x + i + j * plik_we_width] < 10)
							{
								czy_jest = 1;
								bufor[w + h * plik_we_width] = 0;
							}
						}
					}
				}
				else if (w <= pkt_centr_x)
				{
					int czy_jest = 0;
					for (int j = 0; j < elem_height && h + j < plik_we_height && !czy_jest; j++)
					{
						for (int i = 0; i < elem_width - w && w + i < plik_we_width && !czy_jest; i++)
						{
							if (plik_we[h * plik_we_width - plik_we_width * pkt_centr_y + i + j * plik_we_width] < 10)
							{
								czy_jest = 1;
								bufor[w + h * plik_we_width] = 0;
							}
						}
					}
				}
				else
				{
					int czy_jest = 0;
					for (int j = 0; j < elem_height && h + j < plik_we_height && !czy_jest; j++)
					{
						for (int i = 0; i < elem_width && w + i < plik_we_width && !czy_jest; i++)
						{
							if (plik_we[w + h * plik_we_width - plik_we_width * pkt_centr_y - pkt_centr_x + i + j * plik_we_width] < 10)
							{
								czy_jest = 1;
								bufor[w + h * plik_we_width] = 0;
							}
						}
					}
				}
			}
		}
	}
	return bufor;
}


//funkcja wykonuje operacjê erozji pliku Ÿród³owego i zwraca otrzymany wynik (przekszta³cony obraz) w formie wskaŸnika na dane, które mo¿na
//zapisaæ do pliku w formacie graficznym; parametry: plik_we - wskaŸnik na otwarty plik z obrazem Ÿród³owym, który chcemy poddaæ erozji;
//plik_we_width - szerokoœæ obrazu Ÿród³owego; plik_we_height - wysokoœæ obrazu Ÿród³owego; elem_width - szerokoœæ elementu strukturalnego;
//elem_height - wysokoœæ elementu strukturalnego; pkt_centr_x - wspó³rzêdna x punktu centralnego; pkt_centr_y - wspó³rzêdna y punktu centralnego
unsigned char * erozja(const unsigned char * plik_we, int plik_we_width, int plik_we_height, int elem_width, int elem_height, int pkt_centr_x, int pkt_centr_y)
{
	unsigned char * bufor;
	bufor = (unsigned char*)malloc(plik_we_width*plik_we_height * sizeof(unsigned char));

	//kopiujê dane z plik_we do bufora
	for (int j = 0; j < plik_we_height; j++)
	{
		for (int i = 0; i < plik_we_width; i++)
		{
			bufor[i + j * plik_we_width] = plik_we[i + j * plik_we_width];
		}
	}

	for (int h = 0; h < plik_we_height; h++)
	{
		for (int w = 0; w < plik_we_width; w++)
		{
			//sprawdzam, czy w obrebie elementu strukturalnego sa piksele o wartosci > 245, je¿eli tak - piksel o wsp. w i h,
			//przyjmuje wartoœæ 255
			if (h <= pkt_centr_y && w <= pkt_centr_x)
			{
				int czy_jest = 0;
				for (int j = 0; j < elem_height - h && h + j < plik_we_height && !czy_jest; j++)
				{
					for (int i = 0; i < elem_width - w && w + i < plik_we_width && !czy_jest; i++)
					{
						if (plik_we[i + j * plik_we_width] > 245)
						{
							czy_jest = 1;
							bufor[w + h * plik_we_width] = 255;
						}
					}
				}
			}
			else
			{
				if (h <= pkt_centr_y)
				{
					int czy_jest = 0;
					for (int j = 0; j < elem_height - h && h + j < plik_we_height && !czy_jest; j++)
					{
						for (int i = 0; i < elem_width && w + i < plik_we_width && !czy_jest; i++)
						{
							if (plik_we[w - pkt_centr_x + i + j * plik_we_width] > 245)
							{
								czy_jest = 1;
								bufor[w + h * plik_we_width] = 255;
							}
						}
					}
				}
				else if (w <= pkt_centr_x)
				{
					int czy_jest = 0;
					for (int j = 0; j < elem_height && h + j < plik_we_height && !czy_jest; j++)
					{
						for (int i = 0; i < elem_width - w && w + i < plik_we_width && !czy_jest; i++)
						{
							if (plik_we[h * plik_we_width - plik_we_width * pkt_centr_y + i + j * plik_we_width] > 245)
							{
								czy_jest = 1;
								bufor[w + h * plik_we_width] = 255;
							}
						}
					}
				}
				else
				{
					int czy_jest = 0;
					for (int j = 0; j < elem_height && h + j < plik_we_height && !czy_jest; j++)
					{
						for (int i = 0; i < elem_width && w + i < plik_we_width && !czy_jest; i++)
						{
							if (plik_we[w + h * plik_we_width - plik_we_width * pkt_centr_y - pkt_centr_x + i + j * plik_we_width] > 245)
							{
								czy_jest = 1;
								bufor[w + h * plik_we_width] = 255;
							}
						}
					}
				}
			}
		}
	}
	return bufor;
}

//funkcja wykonuje operacjê otwarcia na pliku Ÿród³owym i zwraca otrzymany wynik (przekszta³cony obraz) w formie wskaŸnika na dane, które mo¿na
//zapisaæ do pliku w formacie graficznym; parametry: plik_we - wskaŸnik na otwarty plik z obrazem Ÿród³owym, który chcemy poddaæ otwarciu;
//plik_we_width - szerokoœæ obrazu Ÿród³owego; plik_we_height - wysokoœæ obrazu Ÿród³owego; elem_width - szerokoœæ elementu strukturalnego;
//elem_height - wysokoœæ elementu strukturalnego; pkt_centr_x - wspó³rzêdna x punktu centralnego; pkt_centr_y - wspó³rzêdna y punktu centralnego
unsigned char * otwarcie(const unsigned char * plik_we, int plik_we_width, int plik_we_height, int elem_width, int elem_height, int pkt_centr_x, int pkt_centr_y)
{
	unsigned char * bufor;
	bufor = erozja(plik_we, plik_we_width, plik_we_height, elem_width, elem_height, pkt_centr_x, pkt_centr_y);  //najpierw erozja pliku Ÿród³owego
	unsigned char * bufor_1;
	bufor_1 = dylatacja(bufor, plik_we_width, plik_we_height, elem_width, elem_height, pkt_centr_x, pkt_centr_y); //potem dylatacja wyniku erozji
	free(bufor);
	return bufor_1;
}

//funkcja wykonuje operacjê domkniêcia na pliku Ÿród³owym i zwraca otrzymany wynik (przekszta³cony obraz) w formie wskaŸnika na dane, które mo¿na
//zapisaæ do pliku w formacie graficznym; parametry: plik_we - wskaŸnik na otwarty plik z obrazem Ÿród³owym, który chcemy poddaæ domkniêciu;
//plik_we_width - szerokoœæ obrazu Ÿród³owego; plik_we_height - wysokoœæ obrazu Ÿród³owego; elem_width - szerokoœæ elementu strukturalnego;
//elem_height - wysokoœæ elementu strukturalnego; pkt_centr_x - wspó³rzêdna x punktu centralnego; pkt_centr_y - wspó³rzêdna y punktu centralnego
unsigned char * domkniecie(const unsigned char * plik_we, int plik_we_width, int plik_we_height, int elem_width, int elem_height, int pkt_centr_x, int pkt_centr_y)
{
	unsigned char * bufor;
	bufor = dylatacja(plik_we, plik_we_width, plik_we_height, elem_width, elem_height, pkt_centr_x, pkt_centr_y); //dylatacja pliku Ÿród³owego
	unsigned char * bufor_1;
	bufor_1 = erozja(bufor, plik_we_width, plik_we_height, elem_width, elem_height, pkt_centr_x, pkt_centr_y); //potem erozja wyniku dylatacji
	free(bufor);
	return bufor_1;
}

//funkcja wykonuje operacjê top hat na pliku Ÿród³owym i zwraca otrzymany wynik (przekszta³cony obraz) w formie wskaŸnika na dane, które mo¿na
//zapisaæ do pliku w formacie graficznym; parametry: plik_we - wskaŸnik na otwarty plik z obrazem Ÿród³owym, który chcemy poddaæ operacji top hat;
//plik_we_width - szerokoœæ obrazu Ÿród³owego; plik_we_height - wysokoœæ obrazu Ÿród³owego; elem_width - szerokoœæ elementu strukturalnego;
//elem_height - wysokoœæ elementu strukturalnego; pkt_centr_x - wspó³rzêdna x punktu centralnego; pkt_centr_y - wspó³rzêdna y punktu centralnego
unsigned char * top_hat(const unsigned char * plik_we, int plik_we_width, int plik_we_height, int elem_width, int elem_height, int pkt_centr_x, int pkt_centr_y)
{
	unsigned char * bufor;
	//najpierw operacja otwracia na pliku Ÿród³owym
	bufor = otwarcie(plik_we, plik_we_width, plik_we_height, elem_width, elem_height, pkt_centr_x, pkt_centr_y); 

	unsigned char * zrodlo;
	zrodlo = (unsigned char*)malloc(plik_we_width*plik_we_height * sizeof(unsigned char));

	//kopiujê dane z pliku Ÿród³owego do nowego bufora, aby nie dzia³aæ bezpoœrednio na pliku Ÿród³owym
	for (int j = 0; j < plik_we_height; j++)
	{
		for (int i = 0; i < plik_we_width; i++)
		{
			zrodlo[i + j * plik_we_width] = plik_we[i + j * plik_we_width];
		}
	}

	//"odejmujê" odpowiadaj¹ce piksele obrazu po operacji otwarcia od pikseli pliku Ÿród³owego
	for (int j = 0; j < plik_we_height; j++)
	{
		for (int i = 0; i < plik_we_width; i++)
		{
			if (zrodlo[i + j * plik_we_width] < 10 && bufor[i + j * plik_we_width] < 10)
			{
				zrodlo[i + j * plik_we_width] = 255;
			}
		}
	}

	free(bufor);
	return zrodlo;
}

//funkcja wykonuje operacjê bottom hat na pliku Ÿród³owym i zwraca otrzymany wynik (przekszta³cony obraz) w formie wskaŸnika na dane, które mo¿na
//zapisaæ do pliku w formacie graficznym; parametry: plik_we - wskaŸnik na otwarty plik z obrazem Ÿród³owym, który chcemy poddaæ operacji bottom hat;
//plik_we_width - szerokoœæ obrazu Ÿród³owego; plik_we_height - wysokoœæ obrazu Ÿród³owego; elem_width - szerokoœæ elementu strukturalnego;
//elem_height - wysokoœæ elementu strukturalnego; pkt_centr_x - wspó³rzêdna x punktu centralnego; pkt_centr_y - wspó³rzêdna y punktu centralnego
unsigned char * bottom_hat(const unsigned char * plik_we, int plik_we_width, int plik_we_height, int elem_width, int elem_height, int pkt_centr_x, int pkt_centr_y)
{
	unsigned char * bufor;
	//najpierw operacja domkniêcia na pliku Ÿród³owym
	bufor = domkniecie(plik_we, plik_we_width, plik_we_height, elem_width, elem_height, pkt_centr_x, pkt_centr_y);

	//od pikseli obrazu po operacji domkniêcia "odejmujê" odpowiadaj¹ce im piksele obrazu Ÿród³owego
	for (int j = 0; j < plik_we_height; j++)
	{
		for (int i = 0; i < plik_we_width; i++)
		{
			if (plik_we[i + j * plik_we_width] < 10 && bufor[i + j * plik_we_width] < 10)
			{
				bufor[i + j * plik_we_width] = 255;
			}
		}
	}
	return bufor;
}