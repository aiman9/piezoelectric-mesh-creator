#include <stdlib.h>
#include <stdio.h>

int main()
{
	double a;
	FILE *f = fopen("../OpenCascade/mshElSz.txt", "w");
	if (f == NULL)
	{
	    printf("Error opening file!\n");
	    exit(1);
	}
	printf("Enter the mesh Element size: ");
	scanf("%lf",&a);
	fprintf(f,"%lf\n",a);
	fclose(f);	
}
