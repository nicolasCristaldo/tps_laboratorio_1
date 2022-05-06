/*
 * utn.c
 *
 *  Created on: 9 abr. 2022
 *      Author: nicolas cristaldo
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

static int getInt(int* pResultado);
static int getFloat(float* fResultado);
static int esNumerica(char* cadena);
static int esFlotante(char* cadena);
static int myGets(char* cadena, int longitud);

static int getInt(int* pResultado)
{
	int ret = -1;
	char buffer[2000];

	if(myGets(buffer,sizeof(buffer))==0 && esNumerica(buffer))
	{
		*pResultado = atoi(buffer);
		ret = 0;
	}
	return ret;
}

static int getFloat(float* fResultado)
{
	int ret = -1;
	char buffer[2000];

	if(myGets(buffer,sizeof(buffer))==0 && esFlotante(buffer))
	{
		*fResultado = atof(buffer);
		ret = 0;
	}
	return ret;
}

static int esNumerica(char* cadena)
{
	int ret = 1;
	int i = 0;

	if(cadena[i] == '-')
	{
		i = 1;
	}
	for(; cadena[i] != '\0'; i++)
	{
		if(cadena[i] > '9' || cadena[i] < '0')
		{
			ret = 0;
			break;
		}
	}
	return ret;
}

static int esFlotante(char* cadena)
{
	int ret = 1;
	int i = 0;
	int flag = 0;

	if(cadena[i] == '-')
	{
		i = 1;
	}

	for(; cadena[i] != '\0'; i++)
	{
		if(cadena[i] > '9' || cadena[i] < '0')
		{
			if(cadena[i] == '.' && flag == 0)
			{
				flag++;
			}
			else
			{
				ret = 0;
				break;
			}
		}
	}
	return ret;
}

static int myGets(char* cadena, int longitud)
{
	fflush(stdin);
	fgets(cadena, longitud, stdin);

	cadena[strlen(cadena)-1] = '\0';
	return 0;
}

int utn_getNumero(int* pResultado,char* mensaje,char* mensajeError,int minimo,int maximo,int reintentos)
{
	int ret = -1;
	int num;

	if(pResultado != NULL && mensaje != NULL && mensajeError != NULL && minimo <= maximo && reintentos >= 0)
	{
		do
		{
			printf(mensaje);
			if(getInt(&num) == 0 && num >= minimo && num <= maximo)
			{
				*pResultado = num;
				ret = 0;
				break;
			}
			reintentos--;
			printf("%s",mensajeError);
		}while(reintentos >= 0);
	}

	return ret;
}


int utn_getFlotante(float* fResultado,char* mensaje,char* mensajeError,int minimo,int maximo,int reintentos)
{
	int ret = -1;
	float num;

	if(fResultado != NULL && mensaje != NULL && mensajeError != NULL && minimo <= maximo && reintentos >= 0)
	{
		do
		{
			printf(mensaje);
			if(getFloat(&num) == 0 && num >= minimo && num <= maximo)
			{
				*fResultado = num;
				ret = 0;
				break;
			}
			reintentos--;
			printf("%s",mensajeError);
		}while(reintentos >= 0);
	}

	return ret;
}
