#pragma once

int pkt_centralny(unsigned char *elem, int elem_width, int elem_height, int * pkt_centralny_x, int * pkt_centralny_y);
unsigned char * dylatacja(unsigned char * plik_we, int plik_we_width, int plik_we_height, int elem_width, int elem_height, int pkt_centr_x, int pkt_centr_y);
unsigned char * erozja(unsigned char * plik_we, int plik_we_width, int plik_we_height, int elem_width, int elem_height, int pkt_centr_x, int pkt_centr_y);
unsigned char * otwarcie(unsigned char * plik_we, int plik_we_width, int plik_we_height, int elem_width, int elem_height, int pkt_centr_x, int pkt_centr_y);
unsigned char * domkniecie(unsigned char * plik_we, int plik_we_width, int plik_we_height, int elem_width, int elem_height, int pkt_centr_x, int pkt_centr_y);
unsigned char * top_hat(unsigned char * plik_we, int plik_we_width, int plik_we_height, int elem_width, int elem_height, int pkt_centr_x, int pkt_centr_y);
unsigned char * bottom_hat(unsigned char * plik_we, int plik_we_width, int plik_we_height, int elem_width, int elem_height, int pkt_centr_x, int pkt_centr_y);


