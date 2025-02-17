//STACK USING AN ARRAY

#include<stdio.h>

#define N 5
int stack[N];
int top=-1;

void push()
{
    int x;//x=value
    printf("Enter the value : \n");
    scanf("%d", &x);
    if(top==N-1){
        printf("stack is full.\n");
    }
    else{
        top++;
        stack[top]=x;
    }
}

void pop()
{
    int item;
    if(top==-1){
        printf("Stack is Empty.\n");
    }
    else{
        item=stack[top];
        top--;
        printf("Value %d is popped\n", item);
    }
}

void peek()
{
    if(top==-1){
        printf("Stack is Empty.\n");
    }
    else{
        printf("The top element is %d\n", stack[top]);
    }
}

void show()
{
    int i;
    for(i=top;i>=0;i--){
        printf("%d ", stack[i]);
    }
    printf("\n");
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
