#include<stdio.h>
#include<stdlib.h>

struct node
	{
		int data;
		struct node *left, *right;
	}*root;

struct node *newNode(int item)
	{
		struct node *temp = (struct node *)malloc(sizeof(struct node));
		temp->data = item;
		temp->left = temp->right = NULL;
		return temp;
	}

struct node * minValueNode(struct node* node)
	{
		struct node* current = node;
		while (current->left != NULL)
		current = current->left;
		return current;
	}

struct node* search(int x,struct node* ptr){
		if(ptr){
			int y = ptr-> data;

			if(y == x) return ptr;
			else if( y < x ) return search(x,ptr->right);
			else return search(x,ptr->left);
		}
		else
		 return 0;
	}

struct node* left(int x,struct node* ptr)
	{
		struct node* temp;
		if(temp = search(x,ptr))
		{
			return temp-> left;
		}
		else 
			return 0;
	}

struct node* right(int x,struct node* ptr)
	{
		struct node* temp;
		if(temp = search(x,ptr))
		{
			return temp-> right;
		}
		else
		 return 0;
	}

struct node* delete_node(struct node* root, int data)
	{
		if (root == NULL)
		return root;

		if (data < root->data)
		root->left = delete_node(root->left, data);

		else if (data > root->data)
		root->right = delete_node(root->right, data);
		else
		{
			if (root->left == NULL)
			{
				struct node *temp = root->right;
				free(root);
				return temp;
			}
			else if (root->right == NULL)
			{
				struct node *temp = root->left;
				free(root);
				return temp;
			}
			struct node* temp = minValueNode(root->right);
			root->data = temp->data;
			root->right = delete_node(root->right, temp->data);
		}
		return root;
	}

void inorder(struct node *root)
	{
		if (root != NULL)
		{
			inorder(root->left);
			printf("%d ", root->data);
			inorder(root->right);
		}
	}

void preorder(struct node *root)
	{
		if (root != NULL)
		{
			
			printf("%d ", root->data);
			preorder(root->left);
			preorder(root->right);
		}
	}

void postorder(struct node *root)
	{
		if (root != NULL)
		{		
			postorder(root->left);
			postorder(root->right);
			printf("%d ", root->data);
		}
	}

struct node* insert(struct node* node, int data)
	{
		if (node == NULL)
		return newNode(data);

		if (data < node->data)
		node->left = insert(node->left, data);
		

		else if (data > node->data)
		node->right = insert(node->right, data);
		return node;
	}

int main()
	{
		int n;
		root = NULL;
		printf("\nEnter the number of nodes : ");
		scanf("%d", &n);
		int i;
		int data;
		printf("\nInput the nodes of the binary search tree : ");

		if(n > 0)
		{
			scanf("%d", &data);
			root = insert(root, data);
		}
		for(i = 1; i < n; i++)
		{
			scanf("%d", &data);
			insert(root, data);
		}


		printf("\nInorder : ");
		inorder(root);
		printf("\n");


		printf("\npreorder : ");
		preorder(root);


		printf("\n");
		printf("\npostorder : ");
		postorder(root);
		printf("\n");

		int add;
		printf("\n");
		printf("insert another node :");
		scanf("%d",&add);
		insert(root,add);

		int x;
		printf("\n");
		printf("enter the search element");
		scanf("%d",&x);
		if(x == search(x,root)->data)
		{
		printf("search : %d found\n",search(x,root)->data);
		}
		int del_ele;
		printf("\nEnter the node to be deleted : ");
		scanf("%d", &del_ele);
		delete_node(root, del_ele);
		printf("\nInorder traversal after deletion : ");
		inorder(root);
		printf("\n");
		return 0;
	}
