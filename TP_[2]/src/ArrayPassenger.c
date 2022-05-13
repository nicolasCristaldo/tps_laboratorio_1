/*
 * ArrayPassenger.c
 *
 *  Created on: 23 abr. 2022
 *      Author: nicolas cristaldo
 */
#include <stdio.h>
#include <stdlib.h>
#include "utn.h"
#include "ArrayPassenger.h"
#include <string.h>
#include "arraysChar.h"

static int sortUpName(Passenger* list, int len);
static int sortDownName(Passenger* list, int len);
static int sortUpCode(Passenger* list, int len);
static int sortDownCode(Passenger* list, int len);
static void printPassenger(int id, char* name, char* lastName, char* flyCode, float price, char* type);
static int calcPrices(Passenger* list, int len,float* total, float* average, int* aboveAverage);
static int aboveAveragePassengers(Passenger* list, int len, float* average);

static int aboveAveragePassengers(Passenger* list, int len, float* average)
{
	int ret = -1;
	int i;

	if(list != NULL && len > 0 && average != NULL)
	{
		ret = 0;
		for(i = 0; i < len; i++)
		{
			if(list[i].isEmpty == 0 && *average < list[i].price)
			{
				ret++;
			}
		}
	}
	return ret;
}

static int calcPrices(Passenger* list, int len,float* total, float* average, int* aboveAverage)
{
	int ret = -1;
	int i;
	float cont = 0;
	int positions = 0;

	if(list != NULL && len > 0 && total != NULL && average != NULL && aboveAverage != NULL)
	{
		ret = 0;
		for(i = 0; i < len; i++)
		{
			if(list[i].isEmpty == 0)
			{
				positions++;
				cont = cont + list[i].price;
			}
		}

		*total = cont;
		*average = cont / (float)positions;
		*aboveAverage = aboveAveragePassengers(list, len, average);
	}
	return ret;
}

static void printPassenger(int id, char* name, char* lastName, char* flyCode, float price, char* type)
{
	printf(" %-22s %-20s %-11d %-20.2f %-14s %-20s\n",lastName,name,id,price,flyCode,type);
}

static int sortUpName(Passenger* list, int len)
{
	int ret = -1;
	Passenger aux;
	int flag;
	int i;
	int max;

	if(list != NULL && len > 0)
	{
		max = len -1;
		do
		{
			flag = 0;

			for(i = 0; i < max ; i++)
			{
				if(list[i].typePassenger > list[i+1].typePassenger)
				{
					flag = 1;
					aux = list[i];
					list[i] = list[i+1];
					list[i+1] = aux;
				}
				else if((strcmp(list[i].lastName, list[i+1].lastName) > 0) && (list[i].typePassenger == list[i+1].typePassenger))
				{
					flag = 1;
					aux = list[i];
					list[i] = list[i+1];
					list[i+1] = aux;
				}
			}
			max--;
		}while(flag);
	}
	return ret;
}

static int sortDownName(Passenger* list, int len)
{
	int ret = -1;
	Passenger aux;
	int max = len-1;
	int i;
	int flag;

	if(list != NULL && len > 0)
	{
		ret = 0;
		do
		{
			flag = 0;

			for(i = 0; i < max ; i++)
			{
				if(list[i].typePassenger < list[i+1].typePassenger)
				{
					flag = 1;
					aux = list[i];
					list[i] = list[i+1];
					list[i+1] = aux;
				}
				else if((strcmp(list[i].lastName, list[i+1].lastName) < 0) && (list[i].typePassenger == list[i+1].typePassenger))
				{
					flag = 1;
					aux = list[i];
					list[i] = list[i+1];
					list[i+1] = aux;
				}
			}
			max--;
		}while(flag);
	}
	return ret;
}

static int sortDownCode(Passenger* list, int len)
{
	int ret = -1;
	Passenger aux;
	int max = len-1;
	int i;
	int flag;

	if(list != NULL && len > 0)
	{
		ret = 0;
		do
		{
			flag = 0;

			for(i = 0; i < max; i++)
			{
				if(list[i].statusFlight < list[i+1].statusFlight)
				{
					flag = 1;
					aux = list[i];
					list[i] = list[i+1];
					list[i+1] = aux;
				}
				else if((strcmp(list[i].flyCode, list[i+1].flyCode) < 0) && (list[i].statusFlight == list[i+1].statusFlight))
				{
					flag = 1;
					aux = list[i];
					list[i] = list[i+1];
					list[i+1] = aux;
				}
			}
			max--;
		}while(flag);
	}
	return ret;
}

static int sortUpCode(Passenger* list, int len)
{
	int ret = -1;
	Passenger aux;
	int max = len-1;
	int i;
	int flag;

	if(list != NULL && len > 0)
	{
		ret = 0;
		do
		{
			flag = 0;

			for(i = 0; i < max; i++)
			{

				if(list[i].statusFlight < list[i+1].statusFlight)
				{
					flag = 1;
					aux = list[i];
					list[i] = list[i+1];
					list[i+1] = aux;
				}
				else if((strcmp(list[i].flyCode, list[i+1].flyCode) > 0) && (list[i].statusFlight == list[i+1].statusFlight))
				{
					flag = 1;
					aux = list[i];
					list[i] = list[i+1];
					list[i+1] = aux;
				}
			}
			max--;
		}while(flag);
	}
	return ret;
}

int initPassengers(Passenger* list, int len)
{
	int ret = -1;
	int i;

	if(list != NULL && len > 0)
	{
		ret = 0;

		for(i = 0; i < len; i++)
		{
			list[i].isEmpty = 1;
			list[i].id = -1;
			strcpy(list[i].name,"");
			strcpy(list[i].lastName,"");
			strcpy(list[i].flyCode,"");
			list[i].price = -1;
			list[i].typePassenger = -1;
			list[i].statusFlight = -1;
		}

	}
	return ret;
}

int addPassenger(Passenger* list, int len, int id, char name[],char lastName[],float price,int typePassenger, char flycode[], int status, int* position)
{
	int ret = -1;
	int pos;

	if(position != NULL && list != NULL && len > 0 && id > 0 && name != NULL && lastName != NULL && price > 0 && (status == 0 || status == 1) && (typePassenger >= 1 && typePassenger <= 3) && flycode > 0)
	{
		ret = 0;

		pos = findFreePosition(list, len);
		if(pos != -1)
		{
			list[pos].isEmpty = 0;
			list[pos].id = id;
			strncpy(list[pos].name,name,sizeof(list[pos].name));
			strncpy(list[pos].lastName,lastName,sizeof(list[pos].lastName));
			list[pos].price = price;
			list[pos].typePassenger = typePassenger;
			strncpy(list[pos].flyCode,flycode,sizeof(list[pos].flyCode));
			list[pos].statusFlight = status;
			*position = *position + 1;
		}
		else
		{
			*position = len;
		}
	}
	return ret;
}

int loadPassenger(Passenger* list, int len, int* actualId,int* pos)
{
	int ret = -1;
	char res;
	int id = *actualId;
	char name[51];
	char lastName[51];
	float price;
	int type;
	char flyCode[10];
	int status;
	int position = *pos;

	if(list != NULL && len > 0)
	{
		ret = 0;
		do
		{
			if(position == len)
			{
				printf("\nNo hay mas espacios disponibles.\n");
				break;
			}

			strncpy(name,"",sizeof(name));
			strncpy(lastName,"",sizeof(lastName));
			strncpy(flyCode,"",sizeof(flyCode));
			if(utn_getNombre(name, "\nIngrese su nombre: ", "\nError.\n",3, 51, 3) == -1)
			{
				break;
			}
			if(utn_getNombre(lastName, "\nIngrese su apellido: ", "\nError.\n",3, 51, 3) == -1)
			{
				break;
			}
			if(utn_getFlotante(&price, "\nIngrese precio: ", "\nError.\n", 10000, 3000000, 3) == -1)
			{
				break;
			}

			if(utn_getNumero(&type,"\nIngrese el tipo de pasajero\n1-Menor\n2-Adulto\n3-Jubilado ", "\nError.\n", 1, 3, 3) == -1)
			{
				break;
			}

			if(utn_getAlfanumerico(flyCode, "\nIngrese codigo de vuelo: ", "\nError.\n", 4, 10, 3) == -1)
			{
				break;
			}

			if(utn_getNumero(&status,"\nIngrese estado de vuelo\n0-Inactivo.\n1-Activo ", "\nError.\n", 0, 1, 3) == -1)
			{
				break;
			}

			addPassenger(list, len, id, name, lastName, price, type, flyCode, status, &position);
			id++;

			printf("desea continuar? s/n ");
			fflush(stdin);
			scanf("%c", &res);
		}while(res == 's');
		*actualId = id;
		*pos = position;
	}

	return ret;
}

int findPassengerById(Passenger* list, int len,int id)
{
	int ret = -1;
	int i;

	if(list != NULL && len > 0 && id > 0)
	{
		for(i = 0; i < len; i++)
		{
			if((list[i].id == id) && (list[i].isEmpty == 0))
			{
				ret = i;
				break;
			}
		}
	}
	return ret;
}

int removePassenger(Passenger* list, int len, int id)
{
	int ret = -1;
	int position;

	if(list != NULL && len > 0 && id > 0)
	{
		position = findPassengerById(list, len, id);
		if(position >= 0)
		{
			ret = 0;
			list[position].isEmpty = 1;
		}
	}
	return ret;
}

int deletePassenger(Passenger* list, int len, int actualId, int* pos)
{
	int ret = -1;
	int id;
	int res;

	if(list != NULL && len > 0)
	{
		res = utn_getNumero(&id, "\nIngrese id del pasajero: ", "\nError\n", 1, actualId, 3);
		if(!res)
		{
			if(removePassenger(list, len, id) != -1)
			{
				ret = 0;
				*pos = *pos -1;
			}
			else
			{
				printf("\nNo se encontr� el id del pasajero.\n");
			}
		}
	}

	return ret;
}

int modifyPassenger(Passenger* list, int len, int actualId)
{
	int ret = -1;
	int id;
	int res;
	int position;
	int camp;
	char name[51];
	char lastName[51];
	float price;
	int type;
	char flyCode[10];

	if(list != NULL && len > 0)
	{
		res = utn_getNumero(&id, "\nIngrese id del pasajero: ", "\nError.\n", 1, actualId, 3);

		if(!res)
		{
			position = findPassengerById(list, len, id);

			if(position >= 0)
			{
				res = utn_getNumero(&camp, "\nIngrese campo a modificar: \n1-Nombre.\n2-Apellido.\n3-Precio.\n4-Tipo.\n5-Codigo.", "\nError.\n", 1, 5, 3);
				if(!res)
				{
					ret = 0;
					switch(camp)
					{
						case 1:
							if(utn_getNombre(name, "\nIngrese su nombre: ", "\nError.\n",3, 51, 3) == 0)
							{
								strncpy(list[position].name,name,sizeof(list[position].name));
							}
							break;
						case 2:
							if(utn_getNombre(lastName, "\nIngrese su apellido: ", "\nError.\n",3, 51, 3) == 0)
							{
								strncpy(list[position].lastName,lastName,sizeof(list[position].lastName));
							}
							break;
						case 3:
							if(utn_getFlotante(&price, "\nIngrese precio: ", "\nError.\n", 10000, 3000000, 3) == 0)
							{
								list[position].price = price;
							}
							break;
						case 4:
							if(utn_getNumero(&type,"\nIngrese el tipo de pasajero\n1-Menor\n2-Adulto\n3-Jubilado ", "\nError.\n", 1, 3, 3) == 0)
							{
								list[position].typePassenger = type;
							}
							break;
						case 5:
							if(utn_getAlfanumerico(flyCode, "\nIngrese codigo de vuelo: ", "\nError.\n", 4, 10, 3) == 0)
							{
								strncpy(list[position].flyCode,flyCode,sizeof(list[position].flyCode));
							}
							break;
					}
				}
			}
		}
	}

	return ret;
}

int sortPassengers(Passenger* list, int len, int order)
{
	int ret = -1;

	if(list != NULL && len > 0 && (order == 0 || order == 1))
	{
		if(order == 1)
		{
			sortUpName(list, len);
		}
		else
		{
			sortDownName(list,len);
		}
	}
	return ret;
}

int sortPassengersByCode(Passenger* list, int len, int order)
{
	int ret = -1;

	if(list != NULL && len > 0 && (order == 0 || order == 1))
	{
		if(order == 1)
		{
			sortUpCode(list, len);
		}
		else
		{
			sortDownCode(list,len);
		}
	}
	return ret;
}

int printPassengers(Passenger* list,typePassenger* types, int length)
{
	int ret = -1;
	int i;
	int j;

	if(list != NULL && length > 0)
	{
		ret = 0;

		printf("\n*****************************************************************************************************\n");
		printf(" APELLIDO               NOMBRE               ID          PRECIO               CODIGO         TIPO\n");
		printf("\n");
		for(i = 0; i < length; i++)
		{
			if(list[i].isEmpty == 0)
			{
				for(j = 0; j < 3;j++)
				{
					if(types[j].idType == list[i].typePassenger)
					{
						printPassenger(list[i].id, list[i].name, list[i].lastName, list[i].flyCode, list[i].price, types[j].description);
					}
				}
			}
		}
		printf("\n");
		printf("*****************************************************************************************************\n");
	}
	return ret;
}

int inform(Passenger* list, int len,typePassenger* types)
{
	int ret = -1;
	int res;
	int selectedNum;
	float total;
	float average;
	int aboveAverage;

	if(list != NULL && len > 0)
	{
		res = utn_getNumero(&selectedNum,"\nInformar:\n1-Listado por tipo y orden alfabetico.\n2-Total y promedio de los precios, pasajeros que superan el promedio.\n3-Listado por codigo.","\nError.\n",1,3,3);
		if(!res)
		{
			switch(selectedNum)
			{
			case 1:
				res = utn_getNumero(&selectedNum,"\n0-Ordenar decrecientemente.\n1-Ordenar crecientemente. ","\nError.\n",0,1,3);
				if(!res)
				{
					ret = 0;
					sortPassengers(list, len, selectedNum);
					printPassengers(list,types, len);
				}
				break;
			case 2:
				if(calcPrices(list, len, &total, &average, &aboveAverage) == 0)
				{
					ret = 0;
					printf("\nTotal: $%.2f\nPromedio: $%.2f\nPasajeros por sobre el promedio: %d\n\n",total,average,aboveAverage);
				}
				break;
			case 3:
				res = utn_getNumero(&selectedNum,"\n0-Ordenar decrecientemente.\n1-Ordenar crecientemente. ","\nError.\n",0,1,3);
				if(!res)
				{
					ret = 0;
					sortPassengersByCode(list, len, selectedNum);
					printPassengers(list,types, len);
				}
				break;
			}
		}
	}
	return ret;
}

int findFreePosition(Passenger* list, int len)
{
	int ret = -1;
	int i;

	if(list != NULL && len > 0)
	{
		for(i = 0; i < len; i++)
		{
			if(list[i].isEmpty == 1)
			{
				ret = i;
				break;
			}
		}
	}
	return ret;
}
