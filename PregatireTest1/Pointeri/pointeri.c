int main()  
{    
	int x = 10;
int* p = &x;

printf("%d\n", x);       // Output: 10 (valoarea lui x)
printf("%d\n", *p);      // Output: 10 (valoarea de la adresa p)
printf("%p\n", &x);      // Output: 0x1000 (adresa lui x)
printf("%p\n", p);       // Output: 0x1000 (p stochează această adresă)

*p = 20;                 // MODIFICĂ x prin pointer
printf("%d\n", x);       // Output: 20 (x s-a schimbat)    		


	char *strings[] = {"Bruh", "What"};
	printf("%p\n",strings); //adresa
	printf("%s\n",*strings); // Bruh
	printf("%s\n",*(strings+1)); //What
	printf("%c\n",**strings); //B
	printf("%c\n",**(strings+1));

	return 0;


}    				 			  									