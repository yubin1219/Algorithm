#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct BSTNode
{
	char key[30];
	char data[30];
	struct BSTNode* left;
	struct BSTNode* right;
}TNode;

TNode* root = NULL;

int is_empty()
{
	return (root == NULL);
}


TNode* left_search(TNode* p)
{
	if (p == NULL) return NULL;
	else if (p->left == NULL)
	{
		return p;
	}
	else
	{
		left_search(p->left);
	}
}

TNode* right_search(TNode* p)
{
	if (p == NULL) return NULL;
	else if (p->right == NULL)
	{
		return p;
	}
	else
	{
		right_search(p->right);
	}
}

void compareNode(TNode* new_n, TNode* origin)
{
	char a[30], b[30];
	strcpy(a, origin->key);
	strcpy(b, new_n->key);
	_strupr(a);
	_strupr(b);

	if (strcmp(a, b) > 0)
	{
		//new_node가 n보다 작으므로 왼쪽 노드로 보냄
		if (origin->left == NULL)
		{
			new_n->left = origin->left;
		}
		else
		{
			compareNode(new_n, origin->left);
		}
	}
	else if (strcmp(a, b) < 0)
	{
		//new_node가 n보다 크므로 오른쪽 노드로 보냄
		if (origin->right == NULL)
		{
			new_n->right = origin->right;
		}
		else
		{
			compareNode(new_n, origin->right);
		}
	}
	else
	{
		//두 값이 같음
		printf(" This word already exists !!\n");
	}
}

void insert()
{
	TNode* new_node;
	new_node = (TNode*)malloc(sizeof(TNode));
	printf(" Word: ");
	scanf("%s", new_node->key);
	getchar();
	printf(" Meaning: ");
	scanf("%s", new_node->data);
	getchar();
	new_node->left = NULL;
	new_node->right = NULL;

	if (is_empty())
		root = new_node;
	else
		compareNode(new_node, root);
}

TNode* search_word(char word[])
{
	char a[30];
	TNode* p = root;

	_strupr(word);

	while (1)
	{
		if (p == NULL)
			return NULL;

		if (strcmp(a, word) == 0)
			break;
		
		if (strcmp(a, word) > 0)
		{
			p = p->left;
		}
		else if (strcmp(a, word) < 0)
		{
			p = p->right;
		}
	}
	return p;
}

TNode* search_parent(TNode* son)
{
	char a[30], word[30];
	TNode* p = root;
	TNode* s;
	strcpy(word, son->key);
	_strupr(word);
	strcpy(a, p->key);
	_strupr(a);
	if (strcmp(a, word) == 0)
		return p;
	else
	{
		if (p->left == NULL && p->right == NULL)
			return NULL;
	}

	while (1)
	{
		if (strcmp(a, word) > 0)
		{
			s = p->left;
			strcpy(a, s->key);
			_strupr(a);
		}
		else if (strcmp(a, word) < 0)
		{
			s = p->right;
			strcpy(a, s->key);
			_strupr(a);
		}

		if (strcmp(a, word) == 0)
			break;

		p = s;

		if (p->left == NULL && p->right == NULL)
			return NULL;
	}
	return p;
}

void deleteNode(char word[])
{	
	TNode* n;
	TNode* parent;
	TNode* pl, *pr, *l, *r;
	int i, size,num;
	char a[30], b[30], c[30];

	n = search_word(word); // 삭제할 노드
	parent = search_parent(n); //삭제할 노드의 부모노드

	if (n == NULL)
		printf(" This word is not found !!\n");

	else if (strcmp(n->key, parent->key) == 0) // 삭제할 노드=부모노드=root노드
	{
		if ((n->left == NULL) && (n->right == NULL))
		{
			//단말노드 삭제
			n = NULL;
			root = NULL;
			free(n);
		}
		else if ((n->left != NULL) && (n->right == NULL))
		{
			//자식이 왼쪽에만 있는 root 노드 삭제
			root = n->left;
			free(n);
		}
		else if ((n->left == NULL) && (n->right != NULL))
		{
			//자식이 오른쪽에만 있는 root 노드 삭제
			root = n->right;
			free(n);
		}
		else if ((n->left != NULL) && (n->right != NULL))
		{
			//자식이 양쪽에 있는 root 노드 삭제
			pr = n->left;
			r = right_search(pr);
			pl = n->right;
			l = left_search(pl);
			if (strlen(r->key) > strlen(l->key))
			{
				size = strlen(l->key);
				num = 0;
			}
			else
			{
				size = strlen(r->key);
				num = 1;
			}
			strcpy(a, r->key);
			_strupr(a);
			strcpy(b, l->key);
			_strupr(b);
			strcpy(c, n->key);
			_strupr(c);

			for (i = 0; i < size; i++)
			{
				if (abs(a[i] - c[i]) > abs(b[i] - c[i]))
				{
					num = 2;
					break;
				}
				else if (abs(a[i] - c[i]) < abs(b[i] - c[i]))
				{
					num = 3;
					break;
				}
			}
			// r과l의 key값 중 n의 key와 비슷한 노드를 n의 자리로 옮김
			if ((num == 2) || (num = 0))
			{
				pl = search_parent(l);
				pl->left = l->right;
				l->left = n->left;
				l->right = n->right;
				root = l;
				free(n);
			}
			else if ((num == 3) || (num == 1))
			{
				pr = search_parent(r);
				pr->left = r->left;
				r->left = n->left;
				r->right = n->right;
				root = r;
				free(n);
			}
			printf(" This word is deleted successfully from My Dictionary.\n");
		}
	}

	else
	{
		if ((n->left == NULL) && (n->right == NULL))
		{
			//단말노드 삭제
			n = NULL;
			free(n);
		}
		else if ((n->left != NULL) && (n->right == NULL))
		{
			//자식이 왼쪽에만 있는 노드 삭제
			if (strcmp(parent->key, n->key) > 0) // 삭제할 자식노드가 부모노드의 왼쪽에 위치
			{
				parent->left = n->left;
				free(n);
			}
			else if (strcmp(parent->key, n->key) < 0) // 삭제할 자식노드가 부모노드의 오른쪽에 위치
			{
				parent->right = n->left;
				free(n);
			}
		}
		else if ((n->left == NULL) && (n->right != NULL))
		{
			//자식이 오른쪽에만 있는 노드 삭제
			if (strcmp(parent->key, n->key) > 0) // 삭제할 자식노드가 부모노드의 왼쪽에 위치
			{
				parent->left = n->right;
				free(n);
			}
			else if (strcmp(parent->key, n->key) < 0) // 삭제할 자식노드가 부모노드의 오른쪽에 위치
			{
				parent->right = n->right;
				free(n);
			}
		}
		else if ((n->left != NULL) && (n->right != NULL))
		{
			//자식이 양쪽인 노드 삭제
			pr = n->left;
			r = right_search(pr);
			pl = n->right;
			l = left_search(pl);
			if (strlen(r->key) > strlen(l->key))
			{
				size = strlen(l->key);
				num = 0;
			}
			else
			{
				size = strlen(r->key);
				num = 1;
			}
			strcpy(a,r->key);
			_strupr(a);
			strcpy(b,l->key);
			_strupr(b);
			strcpy(c,n->key);
			_strupr(c);
			
			for (i = 0; i < size; i++)
			{
				if (abs(a[i] - c[i]) > abs(b[i] - c[i]))
				{
					num = 2;
					break;
				}
				else if (abs(a[i] - c[i]) < abs(b[i] - c[i]))
				{
					num = 3;
					break;
				}
			}
			// r과l의 key값 중 n의 key와 비슷한 노드를 n의 자리로 옮김
			if ((num==2) || (num=0))
			{
				pl = search_parent(l);
				pl->left = l->right;
				l->left = n->left;
				l->right = n->right;
				if (strcmp(parent->key, n->key) > 0)
					parent->left = l;
				else if (strcmp(parent->key, n->key) < 0)
					parent->right = l;
				free(n);
			}
			else if ((num==3) || (num==1))
			{
				pr = search_parent(r);
				pr->left = r->left;
				r->left = n->left;
				r->right = n->right;
				if (strcmp(parent->key, n->key) > 0)
					parent->left = r;
				else if (strcmp(parent->key, n->key) < 0)
					parent->right = r;
				free(n);
			}
		}
		printf(" This word is deleted successfully from My Dictionary.\n");
	}
}
TNode* search_meaning(TNode* n, char meaning[])
{
	TNode* p;
	if (n != NULL)
	{
		p = search_meaning(n->left, meaning);
		if (p != NULL)
			return p;
		if (_stricmp(meaning, n->data) == 0)
			return n;

		p = search_meaning(n->right, meaning);

		if (p != NULL)
			return p;
	}
	else
		return NULL;
}

void printTree(TNode* n)
{
	if (n!=NULL)
	{
		printTree(n->left);
		printf(" %s : %s\n", n->key, n->data);
		printTree(n->right);
	}
}

int main(void)
{
	int num;
	char k[30];
	TNode* node;

	while (1)
	{
		printf("[1.input 2.delete 3.search(word) 4.serch(meaning) 5.print 0.Exit] : ");
		scanf("%d", &num);
		getchar();

		if (num == 1)
		{
			insert();
		}
		else if (num == 2)
		{
			printf(" Search(Word) : ");
			scanf("%s", k);
			getchar();
			deleteNode(k);
		}
		else if (num == 3)
		{
			printf(" Search(Word) : ");
			scanf("%s", k);
			getchar();

			node = search_word(k);

			if (node == NULL)
				printf(" This word is not found !!\n");
			else
			{
				printf(" << Search Result >>\n");
				printf(" %s : %s", node->key, node->data);
			}
		}
		else if (num == 4)
		{
			printf(" Search(meaning) : ");
			scanf("%s", k);
			getchar();
			node = search_meaning(root,k);
			if(node==NULL)
				printf(" This word is not found !!\n");
			else
			{
				printf(" << Search Result >>\n");
				printf(" %s : %s", node->key, node->data);
			}
		}
		else if (num == 5)
		{
			if (is_empty())
				printf(" Tree is empty!\n");
			else
			{
				printf(" << My Dictionary >>\n");
				printTree(root);
			}
			
		}
		else if (num == 0)
			break;
	}

	getchar();
	return 0;
}
