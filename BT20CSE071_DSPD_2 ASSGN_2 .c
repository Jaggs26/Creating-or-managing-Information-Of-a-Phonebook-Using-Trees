#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include <math.h>

struct personal         // structure definition for personal
{
    char first_name[20];
    char last_name[20];
    char email[20];
    int number;  //key
    int ht,duration;
    struct personal* left;
    struct personal* right;
};

struct professional               // structure definition for professional
{
    char first_name[20];
    char last_name[20];
    char email[20];
    char office_name[20];
    char office_address[20];
    char office_type[20];
    int number;
    int ht;
    struct professional* left;
    struct professional* right;
};

int max(int a,int b)
{
    if(a>b)
    {
        return a;
    }
    else
    {
        return b;
    }
}

int height(struct personal *root)
{
    int retval;
    if(root == NULL)
    {
        retval = -1;
    }
    else
    {
        retval = (max(height(root->left),height(root->right))+1);
    }
    return retval;
}
int height_professional(struct professional *root_professional)
{
    int retval;
    if(root_professional == NULL)
    {
        retval = -1;
    }
    else
    {
        retval = (max(height_professional(root_professional->left),height_professional(root_professional->right))+1);
    }
    return retval;
}


int bf(struct personal *root)
{
    return abs(height(root->left) - height(root->right));
}
int bf_professional(struct professional *root_professional)
{
    return abs(height_professional(root_professional->left) - height_professional(root_professional->right));
}


struct personal * LL(struct personal* x)
{
    struct personal * y = x->left;
    x->left = y->right;
    y->right = x;
    x->ht = height(x);
    y->ht = height(y);
    return y;
}

struct personal *RR(struct personal *x)
{
    struct personal *y = x->right;
    x->right = y->left;
    y->left = x;
    x->ht = height(x);
    y->ht = height(y);
    return y;
}

struct personal *LR(struct personal *x)
{
    x->left = RR(x->left);
    x = LL(x);
    return x;
}

struct personal *RL(struct personal *x)
{
    x->right = LL(x->right);
    x = RR(x);
    return x;
}
struct professional* LL_professional(struct professional* x)
{
    struct professional* y = x->left;
    x->left = y->right;
    y->right = x;
    x->ht = height_professional(x);
    y->ht = height_professional(y);
    return y;
}
struct professional* RR_professional(struct professional* x)
{
    struct professional* y = x->right;
    x->right = y->left;
    y->left = x;
    x->ht = height_professional(x);
    y->ht = height_professional(y);
    return y;
}

struct professional* LR_professional(struct professional* x)
{
    x->left = RR_professional(x->left);
    x = LL_professional(x);
    return x;
}

struct professional* RL_professional(struct professional* x)
{
    x->right = LL_professional(x->right);
    x = RR_professional(x);
    return x;
}


struct personal *insert(struct personal *root, char first_name[20], char last_name[20], char email[20], int number, int duration)
{
    struct personal *nptr = NULL;

    if(root == NULL)
    {
        nptr = (struct personal*) malloc(sizeof(struct personal));
        strcpy (nptr->first_name , first_name);
        strcpy (nptr->last_name , last_name);
        strcpy (nptr->email , email);
        nptr->duration=duration;
        nptr->number = number;
        nptr->ht=0;
        nptr->left = NULL;
        nptr->right = NULL;
        root=nptr;
        return root;
    }
    else if(number < root->number)
    {
        root->left=insert(root->left, first_name, last_name, email, number,duration);
        if(bf(root) == 2)
        {
            if(number < root->left->number)
            {
                return LL(root);
            }
            else
            {
                return LR(root);
            }
        }
    }
     else
    {
         root->right = insert(root->right, first_name, last_name, email, number,duration);
          if (bf(root) == 2)
          {
               if (number > root->right->number)
            {
                return RR(root);
            }
               else
            {
                return RL(root);
            }
          }
    }
    root->ht = height(root);
     return root;
}
struct professional* insert_professional(struct professional* root_professional, char first_name[20], char last_name[20], char email[20],
                           char office_name[20], char office_address[20],char office_type[20], int number)
{
    struct professional* nptr = NULL;

    if(root_professional == NULL)
    {
        nptr = (struct professional*) malloc(sizeof(struct professional));
        strcpy (nptr->first_name , first_name);
        strcpy (nptr->last_name , last_name);
        strcpy (nptr->email , email);
        strcpy (nptr->office_name , office_name);
        strcpy (nptr->office_address , office_address);
        strcpy (nptr->office_type , office_type);
        nptr->number = number;
        nptr->ht = 0;
        nptr->left = NULL;
        nptr->right = NULL;
        root_professional = nptr;
        return root_professional;
    }
    else if(number < root_professional->number)
    {
        root_professional->left = insert_professional(root_professional->left, first_name, last_name, email, office_name, office_address,office_type, number);
        if(bf_professional(root_professional) == 2)
        {
            if(number < root_professional->left->number)
            {
                return LL_professional(root_professional);
            }
            else
            {
                return LR_professional(root_professional);
            }
        }
    }
     else
    {
        root_professional->right = insert_professional(root_professional->right, first_name, last_name, email, office_name, office_address,office_type, number);
          if (bf_professional(root_professional) == 2)
          {
               if (number > root_professional->right->number)
            {
                return RR_professional(root_professional);
            }
               else
            {
                return RL_professional(root_professional);
            }
          }
    }
    root_professional->ht = height_professional(root_professional);
     return root_professional;
}
void range_print_personal(struct personal* ptr)
{
    printf("\nFirst name : %s\n",ptr->first_name);
    printf("Last name : %s\n",ptr->last_name);
    printf("Email id : %s\n",ptr->email);
    printf("personalonal number : %d\n",ptr->number);
}
void inorder_personal(struct personal * root)
{
    if(root != NULL)
     {
        inorder_personal(root->left);
        printf("%s %s %s %d %d \n",root->first_name,root->last_name,root->email,root->number,root->duration);
        inorder_personal(root->right);
    }
}

void inorder_personal_descending(struct personal* root)
{
    if (root != NULL)
    {
          inorder_personal_descending(root->right);
           printf("%s %s %s %d %d\n",root->first_name,root->last_name,root->email,root->number,root->duration);
          inorder_personal_descending(root->left);
    }
}
void inorder_professional(struct professional * root_professional)
{
    if(root_professional != NULL)
     {
        inorder_professional(root_professional->left);
        printf("%s %s %s %s %s %s %d\n",root_professional->first_name,root_professional->last_name,root_professional->email,
            root_professional->office_name,root_professional->office_address,root_professional->office_type,root_professional->number);
        inorder_professional(root_professional->right);
    }
}

void inorder_descending_professional(struct professional* root_professional)
{
    if (root_professional != NULL)
    {
          inorder_descending_professional(root_professional->right);

          printf("%s %s %s %s %s %s %d\n",root_professional->first_name,root_professional->last_name,root_professional->email,
            root_professional->office_name,root_professional->office_address,root_professional->office_type,root_professional->number);
        inorder_descending_professional(root_professional->left);
    }
}
struct personal* findmin(struct personal * root)
{
       struct personal* retval;
       
    if (root == NULL)
    {
        retval = NULL;
    }
       else if(root->left == NULL)
    {
        retval = root;
    }
    else
    {
        retval = findmin(root->left);
    }
    return retval;
}
struct professional* findmin_professional(struct professional* root_professional)
{
       struct professional* retval;
    if (root_professional == NULL)
    {
        retval = NULL;
    }
       else if(root_professional->left == NULL)
    {
        retval = root_professional;
    }
    else
    {
        retval = findmin_professional(root_professional->left);
    }
    return retval;
}

struct personal * delete_fun(struct personal *root, int number)
{
    struct personal *c;
    struct personal *ptr = root;
    int count = 0;
    if(ptr == NULL)
    {
          printf("\nData was not found Error\n");
          return ptr;
    }
    else if( number < ptr->number)
    {
        ptr->left=delete_fun(ptr->left,number);
    }
    else if( number > ptr->number)
    {
        ptr->right=delete_fun(ptr->right,number);
    }
    else
    {
        if(ptr->left == NULL && ptr->right == NULL)
        {
            return NULL;
        }
        else if(ptr->right != NULL && ptr->left == NULL)
        {
            return ptr->right;
        }
        else if(ptr->left != NULL && ptr->right == NULL)
        {
            return ptr->left;
        }
        else
        {
            c = findmin(ptr->right);            //finds the minimum element in right subtree
            strcpy (ptr->first_name, c->first_name);
            strcpy (ptr->last_name, c->last_name);
            strcpy (ptr->email, c->email);
            ptr->number = c->number;           // copy the minimum element value into the ptr
            ptr->right = delete_fun(ptr->right,c->number);  //delete the duplicate element
            count++;
            printf("%d contact deleted succesfully\n",count);    //prints the msg to know deleted.
            
        }
          ptr->ht = height(ptr);
          
          if (bf(ptr) >= 2 && ptr->left && ptr->left->left)
        {
            return LL(ptr);
        }
          else if (bf(ptr) >= 2 && ptr->left && ptr->left->right)
        {
            ptr=LR(ptr);
        }
     
          else if (bf(ptr) >= 2 && ptr->right && ptr->right->right)
        {
            return RR(ptr);
        }
          if (bf(ptr) >= 2 && ptr->right && ptr->right->left)
          {
              ptr=RL(ptr);
           }
    }
    return ptr;
}
struct professional* delete_professional(struct professional *root_professional, int number)
{
    int count = 0;
    struct professional *min;
    struct professional *ptr = root_professional;
    
    if(ptr == NULL)
    {
          printf("\nData not found \n");
          return ptr;
    }
    else if( number < ptr->number)
    {
        ptr->left=delete_professional(ptr->left,number);
    }
    else if( number > ptr->number)
    {
        ptr->right=delete_professional(ptr->right,number);
    }
    else
    {
        if(ptr->left == NULL && ptr->right == NULL)
        {
            return NULL;
        }
        else if(ptr->right != NULL && ptr->left == NULL) //if only right child exists/
        {
            return ptr->right;
        }
        else if(ptr->left != NULL && ptr->right == NULL)  /* if only left child exists*/
        {
            return ptr->left;
        }
        else
        {
            min = findmin_professional(ptr->right);            //find the minimum element in right subtree
            strcpy (ptr->first_name, min->first_name);
            strcpy (ptr->last_name, min->last_name);
            strcpy (ptr->email, min->email);
            strcpy (ptr->office_name, min->office_name);
            strcpy (ptr->office_address, min->office_address);
            ptr->number = min->number;           // copy the minimum element value into the ptr
            ptr->right = delete_professional(ptr->right,min->number);  //delete the duplicate element
            count++;
            printf("%d contact deleted succesfully\n",count);
         
        }
          ptr->ht = height_professional(ptr);
          
          if (bf_professional(ptr) >= 2 && ptr->left && ptr->left->left)
        {
            return LL_professional(ptr);
        }
          else if (bf_professional(ptr) >= 2 && ptr->left && ptr->left->right)
        {
            ptr = LR_professional(ptr);
        }
          else if (bf_professional(ptr) >= 2 && ptr->right && ptr->right->right)
        {
            return RR_professional(ptr);
        }
          if (bf_professional(ptr) >= 2 && ptr->right && ptr->right->left)
          {
              ptr = RL_professional(ptr);
           }
    }
    return ptr;
}

struct personal* edit_personal(struct personal* root, int number)
{
    struct personal* list_ptr = root;
    char first_name[20], last_name[20], email[20];
    int choice;
    
    if(list_ptr == NULL)
    {
        printf("\nData  not found \n");
    }
    else if (number == list_ptr->number)
    {   printf("\nEnter 1 to edit Names 0 to skip");
        scanf("%d",&choice);
        if(choice==1)
    {
        printf("Enter First name to edit : \n");
        scanf("%s",first_name);
        strcpy (list_ptr->first_name , first_name);
    
        printf("Enter Last name to edit : \n");
        scanf("%s",last_name);
        strcpy (list_ptr->last_name , last_name);
    }
        printf("\nEnter 1 to modify email id 0 to skip : ");
        scanf("%d",&choice);
        if(choice==1){
        printf("Enter email id to edit : \n");
        scanf("%s",email);
        strcpy (list_ptr->email , email);
        }
        else if (number < list_ptr->number)
        {
           
            edit_personal(list_ptr->left,number);
        }
        else if(number > list_ptr->number)
        {
           
            edit_personal(list_ptr->right,number);
        }
    }
    return root;
}
struct professional* edit_professional(struct professional* root_professional, int number)
{
    struct professional* list_ptr = root_professional;
    char first_name[20], last_name[20], email[20], office_name[20], office_address[20],office_type[20];
    int choice;
    
    if(list_ptr == NULL)
    {
        printf("\nData  not found !!\n");
    }
    else if (number == list_ptr->number)
    {    printf("\nEnter 1 to edit Names 0 to skip");
        scanf("%d",&choice);
        if(choice==1)
    {
        printf("Enter First name to edit : \n");
        scanf("%s",first_name);
        strcpy (list_ptr->first_name , first_name);
    
        printf("Enter Last name to edit : \n");
        scanf("%s",last_name);
        strcpy (list_ptr->last_name , last_name);
    }
        printf("\nEnter 1 to modify email id or 0 to skip : ");
        scanf("%d",&choice);
        if(choice==1){
        printf("Enter email id to edit : \n");
        scanf("%s",email);
        strcpy (list_ptr->email , email);
        }
        printf("\nEnter 1 to modify office name and type or 0 to skip : ");
        scanf("%d",&choice);
        if(choice==1){
        printf("Enter Office name : \n");
        scanf("%s",office_name);
            scanf("%s",office_type);
        strcpy (list_ptr->office_name, office_name);
        strcpy (list_ptr->office_address, office_address);
        }
        else if (number < list_ptr->number)
        {
            printf("left\n");
            edit_professional(list_ptr->left,number);
        }
        else if(number > list_ptr->number)
        {
            printf("right\n");
            edit_professional(list_ptr->right,number);
        }
       
    }
    
    return root_professional;
}


void search_personal(struct personal* root, int number)
{
   
    int count=0;
    if(root == NULL)
    {
          printf("\nData was not found !!\n");
    }
    else if (number == root->number)
    {
        
        printf("First name : %s\n",root->first_name);
        printf("Last name : %s\n",root->last_name);
        printf("Email id : %s\n",root->email);
        printf("personalonal number : %d\n",root->number);
        count++;
         printf("%d contact found \n",count);
    }
    
    else if (number < root->number)
    {
        search_personal(root->left,number);
    }
    else if(number > root->number)
    {
        search_personal(root->right,number);
    }
}
void search_professional(struct professional* root_professional, int number)
{
    int count=0;
    
    struct professional* ptr = root_professional;
    
    if(ptr == NULL)
    {
          printf("\nData was not found !!\n");
    }
    else if (number == ptr->number)
    {
        printf("First name : %s\n",ptr->first_name);
        printf("Last name : %s\n",ptr->last_name);
        printf("Email id : %s\n",ptr->email);
        printf("Office name : %s\n",ptr->office_name);
        printf("Office Type: %s\n",ptr->office_type);
        printf("Office address : %s\n",ptr->office_address);
        printf("Office number : %d\n",ptr->number);
        count++;
        printf("%d contact searched\n",count);
    }
    
    else if (number < ptr->number)
    {
        search_professional(ptr->left,number);
    }
    else if(number > ptr->number)
    {
        search_professional(ptr->right,number);
    }
}


void range_search_personal(struct personal* root, int start, int end)
{
    if(root!=NULL)
    {
        range_search_personal(root->left,start,end);
        if( root->number<=end && root->number>=start)
        {
            range_print_personal(root);
        }
        range_search_personal(root->right,start,end);
    }
}

void range_print_professional(struct professional* ptr)
{
    printf("\nFirst name : %s\n",ptr->first_name);
    printf("Last name : %s\n",ptr->last_name);
    printf("Email id : %s\n",ptr->email);
    printf("office name : %s \n",ptr->office_name);
    printf("office type : %s \n",ptr->office_type);
    printf("office address : %s \n",ptr->office_address);
    printf("personalonal number : %d\n",ptr->number);
   
}

void range_search_professional(struct professional* root, int start, int end)
{
    if(root!=NULL)
    {
        range_search_professional(root->left,start,end);
        if(root->number>=start && root->number<=end)
        {
            range_print_professional(root);
        }
        range_search_professional(root->right,start,end);
    }
}

int main()
{
    int  entry, flag = 1;
    char first_name[20], last_name[20], email[20];
    char office_name[20];
    char office_address[20],office_type[20];;
    int number,key;
    printf(" 1 for personalonal \n 2. For professionalesional \n");
    scanf("%d",&key);
    if(key==1)
    {
        
     struct personal *root=NULL;
    
    while(flag == 1)
    {
        printf("\nPress 1. To Insert / Add Contact \nPress 2. Edit Contact \nPress 3. Delete Contact \nPress 4. Search a contact \nPress 5. Sort Based on Numbers \nPress 6. To Display \nPress 7.Range Search \nPress 8. sort Based on names  \n");
        scanf("%d",&entry);
        
        if(entry == 1 )     //to add (or) insert
        {
            int duration;
                printf("first name : ");
                scanf("%s",first_name);
                printf("last name : ");
                scanf("%s",last_name);
                printf("email : ");
                scanf("%s",email);
                printf("number : ");
                scanf("%d",&number);
                printf("enter duration in min");
                printf("Enter 0 if there is no calls made \n");
                scanf("%d",&duration);
                root = insert(root, first_name, last_name, email, number,duration);
                printf(" contacts are created\n");
             
        }
        else if(entry == 2)     //edit
        {
            
            int number;
            printf("Enter the Number to edit : ");
            scanf("%d",&number);
            root = edit_personal(root, number);
            printf("Contact modified");
        }
        else if(entry == 3)         //delete by any field
        {
               printf("enter the number to be deleted\n");
               scanf("%d",&number);
               root = delete_fun(root,number);
            
        }
        else if(entry == 4)
        {
            int number;
            printf("Enter any number to search : ");
            scanf("%d",&number);
            search_personal(root,number);
            
         
        }
        else if(entry == 5)     //sorting based on key( number)
        {
            int order;
            printf("Press 1. Ascending \nPress 2. Descending \n");
            printf("Enter the choice : ");
            scanf("%d",&order);
            if(order == 1)
            {
                printf("\nFirst name  Last name  Email id number Duration \n");
                inorder_personal(root);
            }
            else if(order == 2)
            {
                printf("\nFirst name  Last name  Email id  number Duration\n");
                inorder_personal_descending(root);
            }
         
        }
        else if(entry == 6)         // full display
        {
            printf("\nFirst name  Last name  Email id  number \n");
            inorder_personal(root);
           
        }
        else if (entry ==7)
        { int num1,num2;
            printf("enter number 1");
            scanf("%d",&num1);
            printf("enter number 2");
            scanf("%d",&num2);
            range_search_personal(root, num1, num2);
        }
        
        else if(entry == 0)
        {
            exit(0);
        }
    }
    }
    else if (key == 2)
    {
        int entry,flag = 1;
        struct professional *root_prof = NULL;
        
        while(flag == 1)
        {  printf("\nPress 1. To Insert / Add Contact \nPress 2. Edit Contact \nPress 3. Delete Contact \nPress 4. Search a contact \nPress 5. Sort Based on Numbers \nPress 6. To Display \n Press 7. Range Search \nPress 8. sort Based on names  \n");
        
            scanf("%d",&entry);
            
            if(entry == 1 )
            {
                
                    printf("first name : ");
                    scanf("%s",first_name);
                    printf("last name : ");
                    scanf("%s",last_name);
                   printf("email : ");
                   scanf("%s",email);
                    printf("office name : ");
                   scanf("%s",office_name);
                    printf("office address : ");
                    scanf("%s",office_address);
                   printf("enter office type");
                   scanf("%s",office_type);
                    printf("number : ");
                    scanf("%d",&number);

                   root_prof = insert_professional(root_prof, first_name, last_name, email, office_name, office_address,office_type, number);

                printf("contacts  created\n");
            
                
            }
            else if(entry == 2)          //edit
            {
                int number;
                printf("Enter the any number edit : ");
                scanf("%d",&number);
                root_prof = edit_professional(root_prof, number);
                
            }
            else if(entry == 3)          //delete
            {
                int number;
                printf("enter the number to be deleted\n");
                   scanf("%d",&number);
                   root_prof = delete_professional(root_prof,number);
                  
            }
            else if (entry == 4)         //search
            {
                int number;
                printf("Enter any number to search ");
                scanf("%d",&number);
                search_professional(root_prof,number);
                
               
            }
            else if(entry == 5)             //sort
            {
                int order;
                printf("Press 1. Ascending \nPress 2. Descending \n");
                printf("Enter the choice : ");
                scanf("%d",&order);
                if(order == 1)
                {
                 
                    inorder_professional(root_prof); // for Ascending
                }
                else if(order == 2)
                {
                  
                    inorder_descending_professional(root_prof); // for Descending
                }
                
            }
            else if(entry == 6)           // full display
            {
                printf("\nFirst name  Last name  Email id  Office name  Office address Office Type Office number \n");
                inorder_professional(root_prof);
                
            }
            else if(entry == 7)
            {
                int start, end;
                printf("Enter Start and End limits of number to do Range search : ");
                scanf("%d%d",&start,&end);
                range_search_professional(root_prof, start, end);
                printf("\nThese are the contacts with in the Range\n");
                
            }
            else if(entry == 0)
            {
                flag=0;
            }
        }
    }
    return 0;
}


