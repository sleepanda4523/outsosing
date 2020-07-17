#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define _CRT_SECURE_NO_WARNINGS

typedef struct _node {
	char name[20];			//�̸�
	char phonenum[13];		//��ȭ��ȣ
	char email[40];			//�̸��� �ּ�
	struct _node* next;	//���� ����� �ּҸ� ��Ƴ� ������
}NODE;

//void start();					//���Ͼ� ������ �ҷ����� �Լ�
void plus(NODE *);				//node�߰�.
void del(NODE *,NODE *);					//node ����.
NODE *find_plus(NODE*, NODE *);		//plus�Լ� �� �Լ�. �ߺ����� Ȯ��.
NODE* find_del(NODE*, NODE*);		//del�Լ� �� �Լ�. �����Ϸ��� ����� ������� Ž����.
void formal(NODE *);					//node �� data ����.
//void end();						//���Ͽ� �� ����.

int main()
{
	int input = 0;;										//��ɾ� �Է�
	NODE* hnode = (NODE*)malloc(sizeof(NODE));		//�Ӹ� ��� ����. ������ X
	hnode->next = NULL;

	printf("PIMS�� ���Ű��� ȯ���մϴ�.\n ������ ���������� �����մϴ�.\n ");
	printf("1 : ���ο� ����� ����ϰų� ��ϵ� ����� ������ ���� �� ������ �� �ֽ��ϴ�.\n");
	printf("2 : �̸��� �� ���� �̻� �Է��ϸ� �� ����� ����մϴ�\n");
	printf("3 : ������������ �����ϰ� ���α׷��� �����մϴ�.\n");
	while (1) {
		printf("\n ��ɾ �Է����ּ���! >> ");
		scanf("%d", &input);
		switch (input)
		{
		case 1:
			plus(hnode);
			break;
		case 2:
			//find();
			break;
		case 3:
			//end();
			return 0;
			break;
		default:
			printf("�߸��� ��ɾ� �Դϴ�\n");
			break;
		}
	}
	return 0;
}

void plus(NODE * target)		//node �߰�
{
	NODE* newNode = (NODE*)malloc(sizeof(NODE));
	NODE *temp = (NODE*)malloc(sizeof(NODE));

	printf("�̸��� �Է����ּ��� >> ");
	scanf("%s", temp->name);
	printf("��ȭ��ȣ�� �Է����ּ��� (-����)>> ");
	scanf("%s", temp->phonenum);
	
	NODE * found = find_plus(temp,target);			//�ߺ����θ� �ľ��ϱ� ���� Ž�� �Լ� ���.
	if (found == NULL)		//�̸��� ��ȭ��ȣ�� ���� ���� ���� �� = ���ο� ��� �߰��ϴ� ���
	{
		printf("�̸����ּҸ� �Է����ּ��� >> ");
		scanf("%s", temp->email);
		newNode->next = target->next;
		strcpy(newNode->name,temp->name);
		strcpy(newNode->phonenum ,temp->phonenum);
		strcpy(newNode->email, temp->email);
		target->next = newNode;
		printf("��ϵǾ����ϴ�!\n >> ");
	}
	else
	{
		int n;
		printf("�̹� ��ϵǾ� �ִ� ���̽ʴϴ�.\n ������ ���Ͻø� 1, ������ ���Ͻø� 2, �ƹ� �۾��� ���� �����Ŵٸ� 0�� �Է����ּ��� >> ");
		scanf("%d", &n);
		switch (n)
		{
		case 1:
			formal(found);
			break;
		case 2:
			del(found,target);
			break;
		default:
			break;
		}
	}

}
NODE *find_plus(NODE *data,NODE * node)		//Ž��-�ߺ��� ��� ã��
{
	if (node == NULL) {			//�ƹ���嵵 ���� ���
		return NULL;
	}
	NODE* tmp = node->next;	
	for (; tmp != NULL; tmp = tmp->next) {		//next�� NULL�� ������ ������ Ž��.
		if (!strcmp(tmp->name ,data->name) && !strcmp(tmp->phonenum ,data->phonenum)) {			//���� �̸��� ��ȭ��ȣ�� �������
			return tmp;
		}
	}
	return NULL;					//Ž������ ���� ���
}
NODE* find_del(NODE* data, NODE* node)			//�����Ϸ��� ����� ������带 ã������ Ž��.
{
	if (node == NULL) {
		return NULL;
	}
	NODE* tmp = node->next;
	for (; tmp != NULL; tmp = tmp->next) {
		if (tmp->next == data) {							//next�� �����Ϸ��� ����� �ּҰ� ����ִ� ��� = �������
			return tmp;
		}
	}
	return NULL;
}
void formal(NODE* data)									//�� ����.
{
	printf("�̸� : ");
	scanf("%s", data->name);
	printf("��ȭ��ȣ : ");
	scanf("%s", data->phonenum);
	printf("�̸��� : ");
	scanf("%s", data->email);
}
void del(NODE* del,NODE *target)
{
	NODE *del_f =find_del(del, target);		//�����Ϸ��� ����� ������� Ž��
	printf("p\n");
	del_f->next = del->next;								//next = ����Ű�� ����� ����. ������忡 next�� �����Ϸ��� ����� next�� �־���.
	printf("p\n");
	free(del);
	printf("�����Ǿ����ϴ�\n");
}