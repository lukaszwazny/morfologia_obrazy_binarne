//element strukturalny - dowolny kszta�t - punkt centralny to piksel o warto�ci miejszej ni� 10 - reszta pikseli ma warto�� wi�ksz� ni� 245

//piksel o wartosci mniejszej ni� 10 - czarny, o warto�ci wi�kszej ni� 245 - bialy

#include <stdlib.h>


//funkcja szuka wsp�rz�dnych punktu centralnego, parametry: elem - wska�nik na otwarty plik z elementem strukturalnym;
//elem_width - szeroko�� elementu strukturalnego; elem_height - wysoko�� elementu strukturalnego;
//pkt_centralny_x - wska�nik na zmienn�, w kt�rej ma by� zapisana wsp�rz�dna x punktu centralnego;
//pkt_centralny_y - wska�nik na zmienn�, w kt�rej ma by� zapisana wsp�rz�dna y punktu centralnego;
//funkcja zwraca warto�� 0, je�eli uda�o si� znale�� punkt centralny (jego odpowiednie wsp�rz�dne po wywo�aniu funkcji znajduj� si� w zmiennych,
//na kt�re wskazuj� wska�niki pkt_centralny_x oraz pkt_centralny_y); natomiast je�eli si� nie uda�o znale�� tego� punktu zwracana jest warto�� -1
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

//funkcja wykonuje operacj� dylatacji pliku �r�d�owego i zwraca otrzymany wynik (przekszta�cony obraz) w formie wska�nika na dane, kt�re mo�na
//zapisa� do pliku w formacie graficznym; parametry: plik_we - wska�nik na otwarty plik z obrazem �r�d�owym, kt�ry chcemy podda� dylatacji;
//plik_we_width - szeroko�� obrazu �r�d�owego; plik_we_height - wysoko�� obrazu �r�d�owego; elem_width - szeroko�� elementu strukturalnego;
//elem_height - wysoko�� elementu strukturalnego; pkt_centr_x - wsp�rz�dna x punktu centralnego; pkt_centr_y - wsp�rz�dna y punktu centralnego
unsigned char * dylatacja(const unsigned char * plik_we, int plik_we_width, int plik_we_height, int elem_width, int elem_height, int pkt_centr_x, int pkt_centr_y)
{
	unsigned char * bufor;
	bufor = (unsigned char*)malloc(plik_we_width*plik_we_height * sizeof(unsigned char));

	//kopiuj� dane z plik_we do bufora
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
			//sprawdzam, czy w obrebie elementu strukturalnego sa piksele o wartosci < 10, je�eli tak - piksel o wsp. w i h,
			//przyjmuje warto�� 0
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


//funkcja wykonuje operacj� erozji pliku �r�d�owego i zwraca otrzymany wynik (przekszta�cony obraz) w formie wska�nika na dane, kt�re mo�na
//zapisa� do pliku w formacie graficznym; parametry: plik_we - wska�nik na otwarty plik z obrazem �r�d�owym, kt�ry chcemy podda� erozji;
//plik_we_width - szeroko�� obrazu �r�d�owego; plik_we_height - wysoko�� obrazu �r�d�owego; elem_width - szeroko�� elementu strukturalnego;
//elem_height - wysoko�� elementu strukturalnego; pkt_centr_x - wsp�rz�dna x punktu centralnego; pkt_centr_y - wsp�rz�dna y punktu centralnego
unsigned char * erozja(const unsigned char * plik_we, int plik_we_width, int plik_we_height, int elem_width, int elem_height, int pkt_centr_x, int pkt_centr_y)
{
	unsigned char * bufor;
	bufor = (unsigned char*)malloc(plik_we_width*plik_we_height * sizeof(unsigned char));

	//kopiuj� dane z plik_we do bufora
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
			//sprawdzam, czy w obrebie elementu strukturalnego sa piksele o wartosci > 245, je�eli tak - piksel o wsp. w i h,
			//przyjmuje warto�� 255
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

//funkcja wykonuje operacj� otwarcia na pliku �r�d�owym i zwraca otrzymany wynik (przekszta�cony obraz) w formie wska�nika na dane, kt�re mo�na
//zapisa� do pliku w formacie graficznym; parametry: plik_we - wska�nik na otwarty plik z obrazem �r�d�owym, kt�ry chcemy podda� otwarciu;
//plik_we_width - szeroko�� obrazu �r�d�owego; plik_we_height - wysoko�� obrazu �r�d�owego; elem_width - szeroko�� elementu strukturalnego;
//elem_height - wysoko�� elementu strukturalnego; pkt_centr_x - wsp�rz�dna x punktu centralnego; pkt_centr_y - wsp�rz�dna y punktu centralnego
unsigned char * otwarcie(const unsigned char * plik_we, int plik_we_width, int plik_we_height, int elem_width, int elem_height, int pkt_centr_x, int pkt_centr_y)
{
	unsigned char * bufor;
	bufor = erozja(plik_we, plik_we_width, plik_we_height, elem_width, elem_height, pkt_centr_x, pkt_centr_y);  //najpierw erozja pliku �r�d�owego
	unsigned char * bufor_1;
	bufor_1 = dylatacja(bufor, plik_we_width, plik_we_height, elem_width, elem_height, pkt_centr_x, pkt_centr_y); //potem dylatacja wyniku erozji
	free(bufor);
	return bufor_1;
}

//funkcja wykonuje operacj� domkni�cia na pliku �r�d�owym i zwraca otrzymany wynik (przekszta�cony obraz) w formie wska�nika na dane, kt�re mo�na
//zapisa� do pliku w formacie graficznym; parametry: plik_we - wska�nik na otwarty plik z obrazem �r�d�owym, kt�ry chcemy podda� domkni�ciu;
//plik_we_width - szeroko�� obrazu �r�d�owego; plik_we_height - wysoko�� obrazu �r�d�owego; elem_width - szeroko�� elementu strukturalnego;
//elem_height - wysoko�� elementu strukturalnego; pkt_centr_x - wsp�rz�dna x punktu centralnego; pkt_centr_y - wsp�rz�dna y punktu centralnego
unsigned char * domkniecie(const unsigned char * plik_we, int plik_we_width, int plik_we_height, int elem_width, int elem_height, int pkt_centr_x, int pkt_centr_y)
{
	unsigned char * bufor;
	bufor = dylatacja(plik_we, plik_we_width, plik_we_height, elem_width, elem_height, pkt_centr_x, pkt_centr_y); //dylatacja pliku �r�d�owego
	unsigned char * bufor_1;
	bufor_1 = erozja(bufor, plik_we_width, plik_we_height, elem_width, elem_height, pkt_centr_x, pkt_centr_y); //potem erozja wyniku dylatacji
	free(bufor);
	return bufor_1;
}

//funkcja wykonuje operacj� top hat na pliku �r�d�owym i zwraca otrzymany wynik (przekszta�cony obraz) w formie wska�nika na dane, kt�re mo�na
//zapisa� do pliku w formacie graficznym; parametry: plik_we - wska�nik na otwarty plik z obrazem �r�d�owym, kt�ry chcemy podda� operacji top hat;
//plik_we_width - szeroko�� obrazu �r�d�owego; plik_we_height - wysoko�� obrazu �r�d�owego; elem_width - szeroko�� elementu strukturalnego;
//elem_height - wysoko�� elementu strukturalnego; pkt_centr_x - wsp�rz�dna x punktu centralnego; pkt_centr_y - wsp�rz�dna y punktu centralnego
unsigned char * top_hat(const unsigned char * plik_we, int plik_we_width, int plik_we_height, int elem_width, int elem_height, int pkt_centr_x, int pkt_centr_y)
{
	unsigned char * bufor;
	//najpierw operacja otwracia na pliku �r�d�owym
	bufor = otwarcie(plik_we, plik_we_width, plik_we_height, elem_width, elem_height, pkt_centr_x, pkt_centr_y); 

	unsigned char * zrodlo;
	zrodlo = (unsigned char*)malloc(plik_we_width*plik_we_height * sizeof(unsigned char));

	//kopiuj� dane z pliku �r�d�owego do nowego bufora, aby nie dzia�a� bezpo�rednio na pliku �r�d�owym
	for (int j = 0; j < plik_we_height; j++)
	{
		for (int i = 0; i < plik_we_width; i++)
		{
			zrodlo[i + j * plik_we_width] = plik_we[i + j * plik_we_width];
		}
	}

	//"odejmuj�" odpowiadaj�ce piksele obrazu po operacji otwarcia od pikseli pliku �r�d�owego
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

//funkcja wykonuje operacj� bottom hat na pliku �r�d�owym i zwraca otrzymany wynik (przekszta�cony obraz) w formie wska�nika na dane, kt�re mo�na
//zapisa� do pliku w formacie graficznym; parametry: plik_we - wska�nik na otwarty plik z obrazem �r�d�owym, kt�ry chcemy podda� operacji bottom hat;
//plik_we_width - szeroko�� obrazu �r�d�owego; plik_we_height - wysoko�� obrazu �r�d�owego; elem_width - szeroko�� elementu strukturalnego;
//elem_height - wysoko�� elementu strukturalnego; pkt_centr_x - wsp�rz�dna x punktu centralnego; pkt_centr_y - wsp�rz�dna y punktu centralnego
unsigned char * bottom_hat(const unsigned char * plik_we, int plik_we_width, int plik_we_height, int elem_width, int elem_height, int pkt_centr_x, int pkt_centr_y)
{
	unsigned char * bufor;
	//najpierw operacja domkni�cia na pliku �r�d�owym
	bufor = domkniecie(plik_we, plik_we_width, plik_we_height, elem_width, elem_height, pkt_centr_x, pkt_centr_y);

	//od pikseli obrazu po operacji domkni�cia "odejmuj�" odpowiadaj�ce im piksele obrazu �r�d�owego
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