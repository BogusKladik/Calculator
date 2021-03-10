/*
 ============================================================================
 Name        : Ohae.c
 Author      : Vladislav Bogushov
 Version     :
 Copyright   : IVT
 Description : calculator
 ============================================================================
 */

#include <stdio.h>

int main(int argc, char *argv[])
{
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
	char operation, con;//operation - ��� ���� ��������, con - ���������� ���������� ��� ���
	double a, b, res;//a - 1 �����, b - 2 �����, res - ���������
	printf("All operation: \"+\" - addition, \"-\" - subtraction, \"*\" - multiplication, \"/\" - division, \"\\\" - division without remainder, \"#\" - modulo, \"!\" - factorial, \"^\" - exponentiation.\n");// ���������� ��� ��������� ��������
	do// ����� do ����� ����������� ���������� ���� �� 1 ���
	{
		printf("Write expression: ");
		scanf("%lf %c", &a, &operation);// �������� �� ������������ ������
		if (operation != '!')// ���� ����� ���������, �� ��� �� ����� ������ �����, � � ���������� �����
			scanf("%lf", &b);
		switch (operation)// ��������� ����
		{
		case '+':// �����
			res = a + b;
			printf("%lf + %lf = %lf", a, b, res); // ����� �����
			break;
		case '-': // ��������
			res = a - b;
			printf("%lf - %lf = %lf", a, b, res);// ����� ��������
			break;
		case '*':// ���������
			res = a * b;
			printf("%lf * %lf = %lf", a, b, res);// ����� ���������
			break;
		case '/':// �������
			if (b == 0)
			{
				printf("Cannot be divided by 0\n"); // ����������� ������� ��� �� ����
				continue;// ����� ��������� � ������ ����� ��� "Continue?"
			}
			res = a / b;
			printf("%lf / %lf = %lf", a, b, res);// ����� �������
			break;
		case '\\':// ������� ��� �������
			if (b == 0)
			{
				printf("Cannot be divided by 0\n");// ����������� ������� ��� �� ����
				continue;// ����� ��������� � ������ ����� ��� "Continue?"
			}
			res = a / b;
			printf("%lf \\ %lf = %i", a, b, (int)res);// ����� ������� ��� �������
			break;
		case '#':// ������� �� �������
			if (b == 0)
			{
				printf("Cannot be divided by 0\n");// ����������� ������� ��� �� ����
				continue;// ����� ��������� � ������ ����� ��� "Continue?"
			}
			res = a / b;
			printf("%lf # %lf = %lf", a, b, a - ((int)res * b));// ����� ������� �� �������
			break;
		case '!':// ���������, ����� � ������� �����, ����� �� ���� ������ ��-�� ������������� fuct
			if ((a - (int)a) == 0)// �������� �� ��, ��� ��� ����� �����
			{
				unsigned long int fuct = a; // ��������� ���������� ����������
				if ((int)a > 0)// �������� �� ������������ �������� �����, � ����� ������������� double, ��� int
				{
					for (int i = 1; i < (int)a; i++)
					{
						fuct = fuct * i;// ������� ���������� ����������
					}
					printf("%i ! = %lu", (int)a, fuct);// ����� ����������
				}
				else if (a == 0) // ��������� �� 0 ����� 1
					printf("%i ! = 1", (int)a);// ���������� �����
				else
					printf("Write down a positive number");// ���� ������������ ���� ����������� ����� Write down a positive number
			}
			else// ���� ����� �� �����
			{
				printf("Write an integer\n");// ����������� ������� ��� �� ����
				continue;// ����� ��������� � ������ ����� ��� "Continue?"
			}
			break;
		case '^':// �������
			if ((b - (int)b) == 0)// �������� �� ��, ��� ������� - ����� �����
			{
				res = a;
				if ((int)b > 0)// �������� ����� �������, � ����� �� double � int, ������� ��������� ������ � ����� �������
				{
					for (int j = 0; j < (int)b - 1; j++)
					{
						res = res * a;// ������� ���������� ������� �����
					}
					printf("%lf ^ %i = %lf", a, (int)b, res);// ����� �������� �������
				}
				else if ((int)b < 0)// ����� � ������������� ��������
				{

					double c, d;// ��������� �����, ����� ����������� a ��� 1/a � �������� � ������������� �������
					res = 1 / a;
					c = 1 / a;
					d = -b;
					for (int j = 0; j < (int)d - 1; j++)
					{
						res = res * c;// ������� ���������� ������� �����
					}
					printf("%lf ^ %i = %lf", a, (int)b, res);// ����� �������� ������������� �������
				}
				else
					printf("%lf ^ %i = 1", a, (int)b); // ���� ������� ����� 0, �� ����� � ���� ������� ����� 1
			}
			else// ���� ����� �� �����
			{
				printf("Write an integer to a power\n");// ����������� ������� ��� �� ����
				continue;// ����� ��������� � ������ ����� ��� "Continue?"
			}
			break;
		default:
			printf("I dont know this operation");// ���� �������� �� ��������, ������� ��� ������
		}
		puts("");// ������� �� ����� ������
		printf("Continue?(y/n)\n");// ����� ������, � ��������, ���������� �� ����������
		scanf(" %c", &con);// ������ ������, ���� y - ����������, ���� n - ���������
		while ((con != 'y') && (con !='n'))// �������� �� ��������� ��������� y ��� n
		{
			printf("invalid character, write \"y\" or \"n\"\n");
			scanf(" %c", &con);
		}
	} while (con == 'y'); // ����� ���������� ���� ������������ ����� ������� "y" ����� ���������� ����������
	return 0;
}
