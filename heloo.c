# include <stdio.h>
# include <string.h>

typedef struct BankAccount {
    int accountNo;
    char name[100];

} acc ;

int main() {
    acc acc1= {123,"shree"};
    acc acc2= {124,"sher"};
    acc acc3= {125,"shrr"};

    printf("acc no = %d",acc1.accountNo);
    printf("acc no = %s",acc1.name);
    return 0;

}