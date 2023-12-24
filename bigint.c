#include "bigint.h"  // BIGINT Library
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct node {
    int data;
    struct node* next;
    struct node* prev;
};

void makenode(struct node** new, int dataa) {
    *new = (struct node*)malloc(sizeof(struct node));
    (*new)->data = dataa;
    (*new)->next = NULL;
    (*new)->prev = NULL; 
}

void insertAtBegin(struct node** head, int dataa) {
    struct node* newnode;
    makenode(&newnode, dataa);
    newnode->next = *head;
    newnode->prev = NULL; 
    if (*head != NULL) {
        (*head)->prev = newnode; 
    }
    *head = newnode;
}


void strToLL(struct node** head, char str[]) {
    int n = strlen(str);
    for (int i = 0; i < n; i++) {
        insertAtBegin(head, str[i] - '0');
    }
}

char* bigadd(char str1[], char str2[]){

    struct node *head1 , *head2, *badd;
    int carry=0;
    strToLL(&head1 , str1);
    strToLL(&head2 , str2); 
    struct node *temp1= head1;
    struct node *temp2= head2;

    while(temp1 !=NULL || temp2 !=NULL || carry){
        int sum=carry;
        while(temp1->next!=NULL){
            sum+= temp1->data;
            temp1=temp1->next;
        }
        while(temp2->next!=NULL){
            sum+=temp2->data;
            temp2=temp2->next;
        }
        carry= sum / 10;
        int add = sum%10;
        insertAtBegin(&badd, add);  

    }
   
    // Convert the linked list to char arr (as return type is char*)
    int length = 0;
    struct node *current = badd;
    while (current != NULL) {
        length++;
        current = current->next;
    }
    
    char *str = (char*)malloc((length + 1) * sizeof(char));
    current = badd;
    
    for (int i = length-1; i >=0; i--) {
        str[i] = current->data + '0';  //to convert int to char
        current = current->next;
    }
    
    str[length] = '\0';
    
    return str;
}


char* bigsubs(char str1[], char str2[]){

    int cmp = strcmp(str1, str2);
    if(cmp<0){
    struct node *head1 , *head2, *bsub;
    int borrow = 0;
   
    strToLL(&head1, str1);
    strToLL(&head2, str2); 
    struct node *temp1 = head1;
    struct node *temp2 = head2;

    while (temp1 != NULL || temp2 != NULL) {
        int num1 = (temp1 != NULL) ? temp1->data : 0;
        int num2 = (temp2 != NULL) ? temp2->data : 0;
        num1 = num1 - borrow;
        int diff = num1 - num2 ;
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        
        insertAtBegin(&bsub, diff);

        if (temp1 != NULL) {
            temp1 = temp1->next;
        }
        if (temp2 != NULL) {
            temp2 = temp2->next;
        }
    }

    // Remove leading zeros
    while (bsub != NULL && bsub->data == 0) {
        struct node *temp = bsub;
        bsub = bsub->next;
        free(temp);
    }

    if (bsub == NULL) {
        char *result = (char*)malloc(2 * sizeof(char));
        result[0] = '0';
        result[1] = '\0';
        return result;
    }

    // Convert the linked list to a char array
    int length = 0;
    struct node *current = bsub;
    while (current != NULL) {
        length++;
        current = current->next;
    }
    
    char *str = (char*)malloc((length + 1) * sizeof(char));
    current = bsub;
    
    for (int i = 0; i < length; i++) {
        str[i] = current->data + '0';  // Convert int to char
        current = current->next;
    }
    
    str[length] = '\0';
    
    return str;
    }
}





char* bigmulti(char str1[], char str2[]){
    int len1 = strlen(str1);
    int len2 = strlen(str2);

    if (len1 == 0 || len2 == 0) {
        char *result = (char*)malloc(2 * sizeof(char));
        result[0] = '0';
        result[1] = '\0';  
        return result;      // as: number*0=0
    }

    struct node *resultList = NULL;
    struct node *tempResult = NULL;
    int carry = 0;
    int resultLen = len1 + len2;

    // Initialize the result list with zeros
    for (int i = 0; i < resultLen; i++) {
        insertAtBegin(&resultList, 0);
    }

    // multiplication digit by digit
    for (int i = len1 - 1; i >= 0; i--) {
        int num1 = str1[i] - '0';
        carry = 0;
        tempResult = resultList;

        for (int j = len2 - 1; j >= 0; j--) {
            int num2 = str2[j] - '0';
            int product = (num1 * num2) + tempResult->data + carry;
            carry = product / 10;
            tempResult->data = product % 10;

            if (tempResult->prev != NULL) {
                tempResult = tempResult->prev;
            }
        }

        if (carry > 0) {
            if (tempResult->prev != NULL) {
                tempResult = tempResult->prev;
            }
            while (carry > 0) {
                int sum = tempResult->data + carry;
                carry = sum / 10;
                tempResult->data = sum % 10;
                if (tempResult->prev != NULL) {
                    tempResult = tempResult->prev;
                } else {
                    break;
                }
            }
        }
    }

    // Remove leading zeros from the result
    while (resultList != NULL && resultList->data == 0) {
        struct node *temp = resultList;
        resultList = resultList->next;
        free(temp);
    }

    //  linked list to a character array
    int length = 0;
    struct node *current = resultList;
    while (current != NULL) {
        length++;
        current = current->next;
    }

    if (length == 0) {
        char *result = (char*)malloc(2 * sizeof(char));
        result[0] = '0';
        result[1] = '\0';
        return result;
    }

    char *resultStr = (char*)malloc((length + 1) * sizeof(char));
    current = resultList;

    for (int i = 0; i < length; i++) {
        resultStr[i] = current->data + '0';
        current = current->next;
    }

    resultStr[length] = '\0';

    return resultStr;
}





char* bigdiv(char str1[], char str2[]) {
    struct node* dividend = NULL;
    struct node* divisor = NULL;
    struct node* quotient = NULL;
    struct node* tempResult = NULL;
    struct node* tempDivisor = NULL;
    struct node* tempRemainder = NULL;
    struct node* temp = NULL;
    char* resultStr = NULL;

    strToLL(&dividend, str1);
    strToLL(&divisor, str2);

    if (divisor == NULL) {
        return "Division by zero error!";
    }

    // Initialize dividend and divisor
    tempResult = dividend;
    tempDivisor = divisor;

    while (tempResult != NULL) {
        int quotientDigit = 0;

        // Keep subtracting divisor from dividend
        while (1) {
            int comparison = 0;
            temp = tempResult;

            while (tempDivisor != NULL && tempResult != NULL) {
                if (tempResult->data > tempDivisor->data) {
                    comparison = 1;
                    break;
                } else if (tempResult->data < tempDivisor->data) {
                    comparison = -1;
                    break;
                }

                tempResult = tempResult->next;
                tempDivisor = tempDivisor->next;
            }

            if (comparison == 0 || comparison == -1) {
                // If divisor is greater or equal, break the loop
                break;
            } else {
                tempResult = temp;
                tempDivisor = divisor;
                quotientDigit++;
            }
        }

        insertAtEnd(&quotient, quotientDigit);

        // Remove leading zeros in the result
        while (quotient != NULL && quotient->data == 0) {
            struct node* temp = quotient;
            quotient = quotient->next;
            free(temp);
        }

        tempRemainder = tempResult;
        if (tempResult != NULL) {
            tempResult = tempResult->next;
        }
    }

    // Convert the quotient linked list to a character array
    int length = 0;
    struct node* current = quotient;
    while (current != NULL) {
        length++;
        current = current->next;
    }

    if (length == 0) {
        char* result = (char*)malloc(2 * sizeof(char));
        result[0] = '0';
        result[1] = '\0';
        return result;
    }

    resultStr = (char*)malloc((length + 1) * sizeof(char));
    current = quotient;

    for (int i = 0; i < length; i++) {
        resultStr[i] = current->data + '0';
        current = current->next;
    }

    resultStr[length] = '\0';

    // Free allocated memory
    while (dividend != NULL) {
        struct node* temp = dividend;
        dividend = dividend->next;
        free(temp);
    }

    while (divisor != NULL) {
        struct node* temp = divisor;
        divisor = divisor->next;
        free(temp);
    }

    while (quotient != NULL) {
        struct node* temp = quotient;
        quotient = quotient->next;
        free(temp);
    }

    return resultStr;
}







