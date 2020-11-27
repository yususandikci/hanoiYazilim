#include <stdio.h>
#include <stdlib.h>

typedef struct stack{
    int sayi;
    struct stack *sonraki;
}Stack;

Stack *birinciStack = NULL;
Stack *ikinciStack = NULL;
Stack *ucuncuStack = NULL;

int son_eleman(Stack **stackNesne){
    while((*stackNesne)->sonraki != NULL){
        stackNesne = &(*stackNesne)->sonraki;
    }
    return (*stackNesne)->sayi;
}

int pop(Stack** stackNesne){
    int deger;

    Stack* ilkEleman = (Stack*)malloc(sizeof(Stack));
    ilkEleman->sayi = 0;
    ilkEleman->sonraki = (*stackNesne);

    (*stackNesne) = ilkEleman;

    while((*stackNesne)->sonraki != NULL){
        stackNesne = &(*stackNesne)->sonraki;
    }

    deger = (*stackNesne)->sayi;
    free((*stackNesne));
    (*stackNesne) = NULL;

    return deger;
}

void push(Stack** stackNesne,int deger){
    Stack *yeniEleman = (Stack*)malloc(sizeof(Stack));
    yeniEleman->sayi = deger;
    yeniEleman->sonraki = NULL;

    Stack *silinecekIlkElemanAdres = (*stackNesne);
    (*stackNesne) = (*stackNesne)->sonraki;
    free(silinecekIlkElemanAdres);

    while((*stackNesne) != NULL){
        stackNesne = &(*stackNesne)->sonraki;
    }

    (*stackNesne) = yeniEleman;
}

void olustur(Stack **yeniStack,int birinciDeger,int ikinciDeger,int ucuncuDeger){   
    Stack* birinci = (Stack*)malloc(sizeof(Stack));
    birinci->sayi = birinciDeger;
    Stack* ikinci = (Stack*)malloc(sizeof(Stack));
    ikinci->sayi = ikinciDeger;
    Stack* ucuncu = (Stack*)malloc(sizeof(Stack));
    ucuncu->sayi = ucuncuDeger;
    birinci->sonraki = ikinci;
    ikinci->sonraki = ucuncu;
    ucuncu->sonraki = NULL;

    (*yeniStack) = birinci;
}

void yazdir_stack(Stack **yazilacakStack,char *metin){
    printf("%s : ",metin);
    while((*yazilacakStack) != NULL){
        printf("%d ",(*yazilacakStack)->sayi);
        yazilacakStack = &(*yazilacakStack)->sonraki;
    }
    printf("\n");
}

void yazdir(){
    printf("--------------------\n");
    yazdir_stack(&birinciStack,"Stack 1");
    yazdir_stack(&ikinciStack,"Stack 2");
    yazdir_stack(&ucuncuStack,"Stack 3");
    printf("--------------------\n");
}

void hanoi(int katman,Stack **birinciStackAdres,Stack **ikinciStackAdres,Stack **ucuncuStackAdres){
    if(katman > 1){
        hanoi(katman-1,birinciStackAdres,ucuncuStackAdres,ikinciStackAdres);
        hanoi(1,birinciStackAdres,ikinciStackAdres,ucuncuStackAdres);
        hanoi(katman-1,ucuncuStackAdres,ikinciStackAdres,birinciStackAdres);
    }else{
        int birinciSonEleman = son_eleman(birinciStackAdres);
        int ikinciSonEleman = son_eleman(ikinciStackAdres);
        push(ikinciStackAdres,pop(birinciStackAdres));
        printf("%d degeri, %d degerinin ustune gider...\n",birinciSonEleman,ikinciSonEleman);
        yazdir();
    }
}

void temizle(Stack **silinecekStack){
    Stack *temp;
    while((*silinecekStack) != NULL){
        temp = (*silinecekStack)->sonraki;
        free((*silinecekStack));
        *silinecekStack = temp;
    }
}

int main(){
    olustur(&birinciStack,3,2,1);
    olustur(&ikinciStack,0,0,0);
    olustur(&ucuncuStack,0,0,0);

    yazdir();
    
    hanoi(3,&birinciStack,&ucuncuStack,&ikinciStack);

    temizle(&birinciStack);
    temizle(&ikinciStack);
    temizle(&ucuncuStack);

    system("pause");
    return 0;
}