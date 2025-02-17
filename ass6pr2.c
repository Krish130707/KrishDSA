//STACK USING LINKED LIST

#include<stdio.h>
#include<stdlib.h>
struct Node{
    int data;
    struct Node* link;
};

struct Node* top=0;

void push()
{
    int x;//x=value
    printf("Enter the value : ");
    scanf("%d", &x);
    struct Node* newnode;
    newnode=(struct Node*)malloc(sizeof(struct Node));
    newnode->data=x;
    newnode->link=top;
    top=newnode; 
}

void show()
{
    struct Node* temp=top;
    if(top==0){
        printf("STACK is Empty.\n");
    }
    else{
        while(temp!=0){
            printf("%d ", temp->data);
            temp=temp->link;
        }
        printf("\n");
    }

}

void peek()
{
    if(top==0){
        printf("STACK is Empty.\n");
    }
    else{
        printf("top value is : %d\n", top->data);

    }
}

void pop()
{
    struct Node* temp=top;
    if(top==0){
        printf("STACK is Empty.\n");
    }
    else{
        printf("popped element is : %d",  top->data);
        top=top->link;
        free(temp);
    }
}


int main()
{
    int choice;
    while(1){
        printf("1.push\n2.pop\n3.peek\n4.show\n5.exit\n");
        printf("Enter your choice : ");
        scanf("%d", &choice);
        switch(choice)
        {
            case 1:
                push();
                break;
            case 2:
                pop();
                break;
            case 3:
                peek();
                break;
            case 4:
                show();
                break;
            case 5: 
            return 0;
        }
    }
}