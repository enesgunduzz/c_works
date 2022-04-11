#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>


struct Reklam
{
	int reklamID;
    int baslangic;
    int sure;
    int bitis;
    int fiyat;
};



// Mevcut reklamla çakýþmayan en son reklamý bulmak için kullandýðým Binary Search tabanlý bir iþlev
// "indeks",geçerli reklamýn dizinidir.
// Bu iþlev, dizinden önceki tüm reklamlar onunla çakýþýrsa -1 döndürür. Reklamlar[] dizisi, artan bitiþ zamanýna göre sýralanýr.
int binarySearch(struct Reklam ads[],int index)
{
    // lo= 0.index , hi= dizideki sonuncu index
    int lo = 0 , hi = index-1; 
   
    while(lo<=hi)
    {
        int mid = (lo + hi) / 2;
        if(ads[mid].bitis <= ads[index].baslangic)
        {
            if(ads[mid+1].bitis <= ads[index].baslangic)
                lo = mid + 1;
            else
                return mid;
        }
        else
            hi=mid-1;
    }
    return-1;
}

//Bulunan max deðerleri karþýlaþtýrmak ve büyük olaný bulmak için oluþturulan fonksiyon


void bsortDesc(struct Reklam dizi[],int N)
{
    int i,j;
    struct Reklam temp;
    
    for(i=0;i<N-1;i++)
    {
        for(j=0;j<(N-1-i);j++)
        {
            if(dizi[j].bitis > dizi[j+1].bitis)
            {
                temp = dizi[j];
                dizi[j] = dizi[j+1];
                dizi[j+1] = temp;
            }
        }
    }
}

// Reklam dizisinden gelenlerle maksimum kazancý döndüren fonksiyon
int kazancliYol(struct Reklam dizi[], int n)
{
    bsortDesc(dizi,n);
    
    int*table = (int*)malloc(n*sizeof(int));;
    table[0]=dizi[0].fiyat;
    int i;
    
     for(i=1;i<n;i++)
    {
    	
        int P = dizi[i].fiyat;
        int l = binarySearch(dizi,i);
        if(l!= -1){
        	 P+= table[1];
		}else{
			printf("Kazancli bulunan diziler: %d\n", i);
		}       
        int max;
        if(P>table[i-1]){max=P;
		}else{max=table[i-1];
		}
		
        table[i]=max;
    }
    
    int sonuc = table[n-1];
    free(table);
    
    return sonuc;
}

void display(struct Reklam list[80], int s)
{
    int i;
    
    printf("\n\nReklamID\tBaslangicSaati\tBitisSaati\tFiyat\n");
    for (i = 0; i < s; i++)
    {
        printf("%d\t\t%d\t\t%d\t\t%d\n", list[i].reklamID, list[i].baslangic, list[i].bitis, list[i].fiyat);

    } 
    
     printf("\n\n");
}

//Kullanýcý girdileri ve reklam bilgileri gibi giriþlerin alýndýðý main fonksiyonu
int main()
{
	
	
	printf("\n16011112");

    printf("\nEnes Gunduz\n");


  char fileName[] = "Sample.txt";   
  char line[512];               
  int i, j;
  struct Reklam dizi[80];
 
  int sayi1, sayi2, sayi3, c=0;

  FILE *fs = fopen(fileName, "r");  // FILE pointer
  if (!fs) {
    printf("Dosya acilamadi!");
    return 0;
  }

  fseek(fs, 0, SEEK_SET);
  do{
  	
    	fscanf(fs, "%d", &sayi1);
        fscanf(fs, "%d", &sayi2);
        fscanf(fs, "%d", &sayi3);
        
        
        
        
        dizi[c].baslangic=sayi1;
        dizi[c].sure=sayi2;
        dizi[c].fiyat=sayi3;
        dizi[c].reklamID=c+1;
        dizi[c].bitis= dizi[c].baslangic + dizi[c].sure;
        
        
        
        printf("%d. Nokta: %d ve %d ve %d \n", c+1, sayi1, sayi2, sayi3);
        c++;
    
  } while (fgets(line, 512, fs));
    
    printf("\nC: %d\n",c);
    fclose(fs);
    
   
    int sonuc= kazancliYol(dizi,c);
    
    printf("\nSiralanmadan sonra");
    display(dizi, c);
    printf("\nReklam icin toplam kazanc :::::::::: ");
    printf("%d", sonuc);
    return 0;
}
