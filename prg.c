//BT20CSE009 AMAN KUMAR
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

// struct definition for record for members-Tree
typedef struct record_for_members
{
	int member_id;
    int age;
    char name[30];
    char gender[7];
    int no_of_prog;
    int paid_fees;
	struct record_for_members *left;
	struct record_for_members *right;
	int height_mem;
}m_node;

// struct definition for record for trainers-Tree
typedef struct record_for_trainers
{
    int trainer_id;
    char name[30];
    char list_prog[30];
    int remuneration;
    int count_remur;        //for sort acc remur 
    int assign_mem_id;      //for assigned member id
    struct record_for_trainers *left;
    struct record_for_trainers *right;
	int height_tr;
}t_node;

			////FUNCTION DEFINITIONS------/////
int max(int x, int y);

//Function for members:----------
int height_mem(m_node *N);
m_node* newrecord_for_members(int member_id, char name[30],int age,char gender[7],int nop,int fees);
m_node *right_rotate_mem(m_node *y);
m_node *left_rotate_mem(m_node *x);
int get_balance_mem(m_node *N);
m_node* min_value_mem(m_node* node);
void print_top_mem();

m_node* add_member(m_node* root_mem, int member_id, char name[30],int age,char gender[7],int nop,int fees);
void print_member_list(m_node *root_mem);
m_node* delete_member(m_node* root_mem, int member_id);
m_node* search_member(m_node* root_mem, int member_id);
m_node* range_Search(m_node* root_mem,int from_mem,int to_mem);

//Function for Trainers:------------
int height_tr(t_node *N);
t_node* newrecord_for_trainer(int trainer_id,char name[30],char list_pr[30],int remur);
t_node *right_rotate_tr(t_node *y);
t_node *left_rotate_tr(t_node *x);
int get_balance_tr(t_node *N);
t_node* min_value_tr(t_node* node);
void print_top_tr();

t_node* add_trainer(t_node* root_tr_tr, int trainer_id,char name[30],char list_pr[30],int remur);
void print_trainer_list(t_node *root_tr);
t_node* delete_trainer(t_node* root_tr, int trainer_id);
t_node* search_trainer(t_node* root_tr, int trainer_id);


//Function to get maximum of two integers
int max(int x, int y)
{
	return (x > y)? x : y;
}

//Function to get the height  of the m_node tree
int height_mem(m_node *N)
{
	if (N == NULL)
		return 0;
	return 1+max(height_mem(N->left), height_mem(N->right));
}

//Function to allocate memory for new members
m_node* newrecord_for_members(int member_id, char name[30],int age,char gender[7],int nop,int fees)
{
	m_node* new_mem = (m_node*) malloc(sizeof(m_node));
	new_mem->member_id = member_id;
    new_mem->age=age;
    new_mem->no_of_prog=nop;
    new_mem->paid_fees=fees;
    strcpy(new_mem->name,name);
    strcpy(new_mem->gender,gender);
	new_mem->left = NULL;
	new_mem->right = NULL;
	new_mem->height_mem = 0; // new record_for_members is initially added at leaf of the tree
	return(new_mem);
}

//Function to right rotate this AVL tree if got unbalanced...
m_node *right_rotate_mem(m_node *y)
{
	m_node *x = y->left;
	m_node *T2 = x->right;

	// Perform rotation
	x->right = y;
	y->left = T2;

	// Updating heights
	y->height_mem = height_mem(y);
	x->height_mem = height_mem(x);

	return x;
}

//Function to left rotate this AVL tree if got unbalanced...
m_node *left_rotate_mem(m_node *x)
{
	m_node *y = x->right;
	m_node *T2 = y->left;

	// Perform rotation
	y->left = x;
	x->right = T2;

	// Updating heights
	x->height_mem = height_mem(x);
	y->height_mem = height_mem(y);

	return y;
}

// Get Balance factor of record_for_members 
int get_balance_mem(m_node *N)
{
	if (N == NULL)
		return 0;
	return height_mem(N->left) - height_mem(N->right);
}

//Recursive function to add Member
m_node* add_member(m_node* root_mem, int member_id, char name[30],int age,char gender[7],int nop,int fees)
{
	if (root_mem == NULL)
		return(newrecord_for_members(member_id,name,age,gender,nop,fees));

	if (member_id < root_mem->member_id)
		root_mem->left = add_member(root_mem->left, member_id,name,age,gender,nop,fees);
	else if (member_id > root_mem->member_id)
		root_mem->right = add_member(root_mem->right, member_id,name,age,gender,nop,fees);
	else            // Equal member_ids are not allowed
		return root_mem;

	//Updating height
	root_mem->height_mem = height_mem(root_mem);

    //getting balance factor
	int balance = get_balance_mem(root_mem);

	// If this record_for_root_mem becomes unbalanced, then
	// there are 4 cases

	// Left Left Case
	if (balance > 1 && member_id < root_mem->left->member_id)
		return right_rotate_mem(root_mem);

	// Right Right Case
	if (balance < -1 && member_id > root_mem->right->member_id)
		return left_rotate_mem(root_mem);

	// Left Right Case
	if (balance > 1 && member_id > root_mem->left->member_id)
	{
		root_mem->left = left_rotate_mem(root_mem->left);
		return right_rotate_mem(root_mem);
	}

	// Right Left Case
	if (balance < -1 && member_id < root_mem->right->member_id)
	{
		root_mem->right = right_rotate_mem(root_mem->right);
		return left_rotate_mem(root_mem);
	}

	return root_mem;
}

//function to print member list
void print_member_list(m_node *root_mem)
{
    
	if(root_mem != NULL)
	{
        printf("%-8d | %-10s | %4d | %7s | %11d | %9d  \n",root_mem->member_id,root_mem->name,root_mem->age,root_mem->gender,root_mem->no_of_prog,root_mem->paid_fees);
        
		print_member_list(root_mem->left);
		print_member_list(root_mem->right);
	}
}

//-----FOR TRAINER---------//
//Function to get the height  of the t_node tree
int height_tr(t_node *N)
{
	if (N == NULL)
		return 0;
	return 1+max(height_tr(N->left), height_tr(N->right));
}

//Function to allocate memory for new trainers
t_node* newrecord_for_trainer(int trainer_id,char name[30],char list_pr[30],int remur)
{
	t_node* new_trainer = (t_node*) malloc(sizeof(t_node));
						
	new_trainer->trainer_id = trainer_id;
	new_trainer->remuneration=remur;
	strcpy(new_trainer->name,name);
	strcpy(new_trainer->list_prog,list_pr);
	// strcpy(new_trainer->)
	new_trainer->left = NULL;
	new_trainer->right = NULL;
	new_trainer->height_tr = 0; // new record_for_trainer is initially added at leaf
	return(new_trainer);
}

//Function to right rotate this AVL tree if got unbalanced...
t_node *right_rotate_tr(t_node *y)
{
	t_node *x = y->left;
	t_node *T2 = x->right;

	// Perform rotation
	x->right = y;
	y->left = T2;

	// Update height_trs
	y->height_tr = height_tr(y);
	x->height_tr = height_tr(x);

	// Return new root_tr
	return x;
}

//Function to left rotate this AVL tree if got unbalanced...
t_node *left_rotate_tr(t_node *x)
{
	t_node *y = x->right;
	t_node *T2 = y->left;

	// Perform rotation
	y->left = x;
	x->right = T2;

	// Update height_trs
	x->height_tr = height_tr(x);
	y->height_tr = height_tr(y);

	// Return new root_tr
	return y;
}

// Get Balance factor of record_for_trainers
int get_balance_tr(t_node *N)
{
	if (N == NULL)
		return 0;
	return height_tr(N->left) - height_tr(N->right);
}

//Recursive function to add Trainer
t_node* add_trainer(t_node* root_tr_tr, int trainer_id,char name[30],char list_pr[30],int remur)
{
	if (root_tr_tr == NULL)
		return(newrecord_for_trainer(trainer_id, name, list_pr,remur));

	if (trainer_id < root_tr_tr->trainer_id)
		root_tr_tr->left = add_trainer(root_tr_tr->left, trainer_id, name, list_pr,remur);
	else if (trainer_id > root_tr_tr->trainer_id)
		root_tr_tr->right = add_trainer(root_tr_tr->right, trainer_id, name, list_pr,remur);
	else        // Equal trainer_ids are not allowed
		return root_tr_tr;

	//Updating height
	root_tr_tr->height_tr = height_tr(root_tr_tr);

	//getting balance factor
	int balance = get_balance_tr(root_tr_tr);

	// If this root_tr_tr becomes unbalanced, then
	// there are 4 cases

	// Left Left Case
	if (balance > 1 && trainer_id < root_tr_tr->left->trainer_id)
		return right_rotate_tr(root_tr_tr);

	// Right Right Case
	if (balance < -1 && trainer_id > root_tr_tr->right->trainer_id)
		return left_rotate_tr(root_tr_tr);

	// Left Right Case
	if (balance > 1 && trainer_id > root_tr_tr->left->trainer_id)
	{
		root_tr_tr->left = left_rotate_tr(root_tr_tr->left);
		return right_rotate_tr(root_tr_tr);
	}

	// Right Left Case
	if (balance < -1 && trainer_id < root_tr_tr->right->trainer_id)
	{
		root_tr_tr->right = right_rotate_tr(root_tr_tr->right);
		return left_rotate_tr(root_tr_tr);
	}

	return root_tr_tr;
}

//function to print trainer list
void print_trainer_list(t_node *root_tr)
{
	if(root_tr != NULL)
	{
		// printf("%d ", root_tr->trainer_id);
		printf("%-9d | %-10s | %12s | %14d\n",root_tr->trainer_id,root_tr->name,root_tr->list_prog,root_tr->remuneration);
		print_trainer_list(root_tr->left);
		print_trainer_list(root_tr->right);
	}
}

//Function to find minimum value node for member
m_node* min_value_mem(m_node* node)
{
    m_node* current = node;
 
    /* loop down to find the leftmost leaf */
    while (current->left != NULL)
        current = current->left;
 
    return current;
}

//Function to delete member
m_node* delete_member(m_node* root_mem, int member_id)
{
    if (root_mem == NULL)
        return root_mem;
 
    // If the member_id to be deleted is smaller than the
    // root_mem's member_id, then it lies in left subtree
    if ( member_id < root_mem->member_id )
        root_mem->left = delete_member(root_mem->left, member_id);
 
    // If the member_id to be deleted is greater than the
    // root_mem's member_id, then it lies in right subtree
    else if( member_id > root_mem->member_id )
        root_mem->right = delete_member(root_mem->right, member_id);
 
    // if member_id is same as root_mem's member_id, then This is
    // the node to be deleted
    else
    {
        // node with only one child or no child
        if( (root_mem->left == NULL) || (root_mem->right == NULL) )
        {
            m_node *temp = root_mem->left ? root_mem->left :root_mem->right;
 
            // No child case
            if (temp == NULL)
            {
                temp = root_mem;
                root_mem = NULL;
            }
            else // One child case
             *root_mem = *temp; // Copy the contents of
                            // the non-empty child
            free(temp);
        }
        else
        {
            m_node* temp = min_value_mem(root_mem->right);
 
            // Copy the inorder successor's data to this node
            root_mem->member_id = temp->member_id;
 
            // Delete the inorder successor
            root_mem->right = delete_member(root_mem->right, temp->member_id);
        }

    }
 
    // If the tree had only one node then return
    if (root_mem == NULL)
      return root_mem;
 
    //updating height
    root_mem->height_mem = 1 + max(height_mem(root_mem->left),height_mem(root_mem->right));
 
    int balance = get_balance_mem(root_mem);
 
    // If this node becomes unbalanced, then there are 4 cases
 
    // Left Left Case
    if (balance > 1 && get_balance_mem(root_mem->left) >= 0)
        return right_rotate_mem(root_mem);
 
    // Left Right Case
    if (balance > 1 && get_balance_mem(root_mem->left) < 0)
    {
        root_mem->left =  left_rotate_mem(root_mem->left);
        return right_rotate_mem(root_mem);
    }
 
    // Right Right Case
    if (balance < -1 && get_balance_mem(root_mem->right) <= 0)
        return left_rotate_mem(root_mem);
 
    // Right Left Case
    if (balance < -1 && get_balance_mem(root_mem->right) > 0)
    {
        root_mem->right = right_rotate_mem(root_mem->right);
        return left_rotate_mem(root_mem);
    }
	// printf("Trainer ID %d deleted successfully\n",&member_id);
    return root_mem;
}

//search member
m_node* search_member(m_node* root_mem, int member_id)
{
    if (root_mem == NULL){
        printf("Not Found\n");
        return root_mem;
    }
    // If the member_id to be deleted is smaller than the
    // root_mem's member_id, then it lies in left submemee
    if ( member_id < root_mem->member_id )
        root_mem->left = search_member(root_mem->left, member_id);
 
    // If the member_id to be deleted is greater than the
    // root_mem's member_id, then it lies in right submemee
    else if( member_id > root_mem->member_id )
        root_mem->right = search_member(root_mem->right, member_id);
 
    // if member_id is same as root_mem's member_id, then This is
    // the node to be searched
    else
    {
		char *row1[] = {"MemberId", "Name", "Age", "Gender", "Num_Of_Prog", "Fees_Paid"};
		printf("%*s | %*s | %*s | %*s | %*s | %*s\n", -8, row1[0], -10, row1[1], 4, row1[2],7,row1[3],11,row1[4],9,row1[5]);
		printf("%-8d | %-10s | %4d | %7s | %11d | %9d  \n",root_mem->member_id,root_mem->name,root_mem->age,root_mem->gender,root_mem->no_of_prog,root_mem->paid_fees);
	}
	return root_mem;
}

//function to search a given range of member IDs of members
m_node* range_Search(m_node* root_mem,int from_mem,int to_mem){
	for(int i=from_mem;i<=to_mem;i++){
		m_node* temp;
		temp=search_member(root_mem,i);
	}
}

//Function to find minimum value node for trainer
t_node* min_value_tr(t_node* node)
{
    t_node* current = node;
 
    /* loop down to find the leftmost leaf */
    while (current->left != NULL)
        current = current->left;
 
    return current;
}

//Function to delete trainer
t_node* delete_trainer(t_node* root_tr, int trainer_id)
{
    if (root_tr == NULL)
        return root_tr;
 
    // If the trainer_id to be deleted is smaller than the
    // root_tr's trainer_id, then it lies in left subtree
    if ( trainer_id < root_tr->trainer_id )
        root_tr->left = delete_trainer(root_tr->left, trainer_id);
 
    // If the trainer_id to be deleted is greater than the
    // root_tr's trainer_id, then it lies in right subtree
    else if( trainer_id > root_tr->trainer_id )
        root_tr->right = delete_trainer(root_tr->right, trainer_id);
 
    // if trainer_id is same as root_tr's trainer_id, then This is
    // the node to be deleted
    else
    {
        // node with only one child or no child
        if( (root_tr->left == NULL) || (root_tr->right == NULL) )
        {
            t_node *temp = root_tr->left ? root_tr->left : root_tr->right;
 
            // No child case
            if (temp == NULL)
            {
                temp = root_tr;
                root_tr = NULL;
            }
            else // One child case
             *root_tr = *temp; // Copy the contents of
                            // the non-empty child
            free(temp);
        }
        else
        {
            t_node* temp = min_value_tr(root_tr->right);
 
            // Copy the inorder successor's data to this node
            root_tr->trainer_id = temp->trainer_id;
 
            // Delete the inorder successor
            root_tr->right = delete_trainer(root_tr->right, temp->trainer_id);
        }
    }
 
    // If the tree had only one node then return
    if (root_tr == NULL)
      return root_tr;
 
    //updating height
    root_tr->height_tr = 1 + max(height_tr(root_tr->left),height_tr(root_tr->right));
 
    int balance = get_balance_tr(root_tr);
 
    // If this node becomes unbalanced, then there are 4 cases
 
    // Left Left Case
    if (balance > 1 && get_balance_tr(root_tr->left) >= 0)
        return right_rotate_tr(root_tr);
 
    // Left Right Case
    if (balance > 1 && get_balance_tr(root_tr->left) < 0)
    {
        root_tr->left =  left_rotate_tr(root_tr->left);
        return right_rotate_tr(root_tr);
    }
 
    // Right Right Case
    if (balance < -1 && get_balance_tr(root_tr->right) <= 0)
        return left_rotate_tr(root_tr);
 
    // Right Left Case
    if (balance < -1 && get_balance_tr(root_tr->right) > 0)
    {
        root_tr->right = right_rotate_tr(root_tr->right);
        return left_rotate_tr(root_tr);
    }
	// printf("Trainer ID %d deleted successfully\n",&trainer_id);
    return root_tr;
}

//search
t_node* search_trainer(t_node* root_tr, int trainer_id)
{
 
    if (root_tr == NULL){
        
        printf("Not Found\n");
        return root_tr;
    }
 
    // If the trainer_id to be deleted is smaller than the
    // root_tr's trainer_id, then it lies in left subtree
    if ( trainer_id < root_tr->trainer_id )
        root_tr->left = search_trainer(root_tr->left, trainer_id);
 
    // If the trainer_id to be deleted is greater than the
    // root_tr's trainer_id, then it lies in right subtree
    else if( trainer_id > root_tr->trainer_id )
        root_tr->right = search_trainer(root_tr->right, trainer_id);
 
    // if trainer_id is same as root_tr's trainer_id, then This is
    // the node to be searched
    else
    {
		char *row3[] = {"TrainerId", "Name", "Prog_Offered", "Remuneration"};
    	printf("%*s | %*s | %*s | %*s\n", -9, row3[0], -10, row3[1], 12, row3[2],14,row3[3]);
		printf("%-9d | %-10s | %12s | %14d\n",root_tr->trainer_id,root_tr->name,root_tr->list_prog,root_tr->remuneration);
	}
	return root_tr;
}

//function to print heading of members
void print_top_mem(){
	char *row1[] = {"MemberId", "Name", "Age", "Gender", "Num_Of_Prog", "Fees_Paid"};
	printf("%*s | %*s | %*s | %*s | %*s | %*s\n", -8, row1[0], -10, row1[1], 4, row1[2],7,row1[3],11,row1[4],9,row1[5]);
}

//function to print heading of trainers
void print_top_tr(){
	char *row1[] = {"TrainerId", "Name", "Prog_Offered", "Remuneration"};
    printf("%*s | %*s | %*s | %*s\n", -9, row1[0], -10, row1[1], 12, row1[2],14,row1[3]);
}


///////-----------------------MAIN FUNCTION------------/////

int main()
{
    int count_m=0,count_t=0,count_sh=0; //variables to assign member and trainer IDs
    m_node *root_mem = NULL;
	t_node *root_tr = NULL;
	//Variables for member
    int m_id,age,no_of_prog,paid_fees;
    char name[30],gender[7];

	//Variables for trainer
	int t_id,remur;
    char list_pr[30];
/////////////------------------------//////////////////
	int exit_status=1,choice=0,mem_id,tr_id;
	int from_mem,to_mem;
	m_id=1000+(count_m);
	t_id=6000+(count_t); 
	printf("        ---Welcome TO The HEALTH CLUB---        \n");
    while(exit_status==1){

        printf("1.Add Member: \n");
        printf("2.Add Trainer: \n");
        printf("3.Schedule Slot: \n");
        printf("4.Print Hour Wise List: \n");
        printf("5.Delete Member: \n");
        printf("6.Delete Trainer: \n");
        printf("7.Search Member: \n");
        printf("8.Search Trainer: \n");
        printf("9.Print Member List: \n");
        printf("10.Print Trainer List: \n");
        printf("11.Print sorted remuneration list: \n");
        printf("12.Range Search for Members: \n");

        printf("Please choose key according to given data.\n");
        scanf("%d",&choice);

        switch (choice)
        {
        case 1:
            printf("Enter Member details as specified: \n");
			printf("Name(Without Spaces): ");
			scanf("%s",name);
			// printf("\nFirst Name: ");
			//this can take both first and last names separately,but required extra memory
			// printf("\nLast Name: ");
			printf("\nAge: ");
			scanf("%d",&age);
			printf("\nGender: ");
			scanf("%s",gender);
			printf("\nNumber of programms : ");
			scanf("%d",&no_of_prog);
			printf("\nPaid Fees: ");
			scanf("%d",&paid_fees);
			root_mem =add_member(root_mem,m_id,name,age,gender,no_of_prog,paid_fees);
			printf("New member with member_ID %d registered successfully.\nPlease note this ID for future reference.\n",m_id);
			m_id++; 
			break;
        
        case 2:
			printf("Enter trainer details as specified: \n");
			printf("Name(Without Spaces): ");
			scanf("%s",name);
			printf("\nSpecified Program (Only 1(Without Spaces)): ");
			scanf("%s",list_pr);
			printf("\nRemuneration for every 1 hour: ");
			scanf("%d",&remur);
			root_tr = add_trainer(root_tr, t_id, name, list_pr,remur);
			printf("New trainer with trainer_ID %d registered successfully.\nPlease note this ID for future reference.\n",t_id);
			t_id++;
            break;

        case 3:
            printf("Sorry,currently no data available\n");
            break;

        case 4:
            printf("Sorry,currently no data available\n");
            // Print_hour_wise_list();
            break;

        case 5:
			printf("Enter a valid member ID for deletion\n");
			scanf("%d",&mem_id);
            root_mem=delete_member(root_mem,mem_id);
			printf("Member ID %d deleted successfully\n",mem_id);
            break;

        case 6:
			printf("Enter a valid trainer ID for deletion\n");
			scanf("%d",&tr_id);
            root_tr = delete_trainer(root_tr, tr_id);
			printf("Trainer ID %d deleted successfully\n",tr_id);
            break;

        case 7:
			printf("Enter the member ID to search\n");
			scanf("%d",&mem_id);
            root_mem=search_member(root_mem,mem_id);
            break;

        case 8:
			printf("Enter the trainer ID to search\n");
			scanf("%d",&tr_id);
            root_tr=search_trainer(root_tr,tr_id);
            break;

        case 9:
			print_top_mem();
			print_member_list(root_mem);
            break;

        case 10:
            print_top_tr();
			print_trainer_list(root_tr);
			break;

        case 11:
            // Print_sorted_remuneration_list();
            printf("Sorry,currently no data available\n");
            break;

        case 12:
			printf("Enter starting and ending Member IDs respectively for range search\n ");
			scanf("%d %d",&from_mem,&to_mem);
			root_mem=range_Search(root_mem,from_mem,to_mem);
            break;
                                                   
        default:
            printf("Press a valid key.\n");
            break;
        }
        printf("If you want to continue,press 1 else any other key: \n");
        scanf("%d",&exit_status);

    }


    return 0;
}
