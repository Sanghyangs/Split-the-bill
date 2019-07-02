#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define _CRT_SECURE_NO_WARNINGS


//�̸� / �ɼ�(1: ��O ����O, 2: ��O ����X, 3: ��X ����O, 4: ��X ����X)�� �������� ����.
//ex) ȫ�浿 / 1
typedef struct {
	DETAILS *arr;
	int people;
	int typea;
	int typeb;
	int typec;
	int typed;
}LIST;

typedef struct {
	char *name;
	int type;
	int personalprice;
}DETAILS;


////////////////////////////////////////////////////////////////////////////////
// Prototype declarations

//����ü ����
LIST *createlist(int people) {
	LIST *list = (LIST*)calloc(1, sizeof(LIST));//�̺κ� ó�� �򰥸�
	DETAILS *arr = (DETAILS*)calloc(1, sizeof(DETAILS)*people);
	list->people = people;
	list->typea = 0;
	list->typeb = 0;
	list->typec = 0;
	list->typed = 0;
	return list;
}

void *_createdetails(LIST *list, char *filename) {
	//���� �о �̸�, �ɼ��� LIST ����ü ������ DETAILS ����ü�� ����
	int line = 0;
	while ((nread = getline(&line, &len, stream)) != -1) {
		line++;
		// /������ ������ ��Ʈ��(name)�� �о ����
		list->arr[line - 1]->name = ;
		// /������ ������ ����(type)
		list->arr[line - 1].type = ;
		//personalprice �ʱ�ȭ
		list->arr[line - 1].personalprice = 0;
	}
	return 
}

void *destroylist(LIST *list) {
	if (list == NULL) {
		return;
	}

	_destroydetails(list);
	return;
}

void *_destroydetails(LIST *list) {
	if (list == NULL) {
		return;
	}
	for (int i = 0; i < list->people; i++) {
		if (list->arr[i] == NULL) {
			i++;
			continue;
		}
		else 
			free(list->arr[i]);
	}
	return;
}

//qsort ���� ���Լ�
static int _compare(const void *n1, const void *n2) {
	DETAILS *arg1, *arg2;

	arg1 = (DETAILS *)n1;
	arg2 = (DETAILS *)n2;

	if (arg1->name < arg2->name) {
		return 1;
	}

	if (arg1->name > arg2->name) {
		return -1;
	}

	return 0;
}

//line�� 1�پ� �о� �̸�/Ÿ�� �� �������� �����Ǿ��ִ��� Ȯ�� (������ 0, Ʋ���� 1)
int lineformatcheck(char *filename) {
	FILE *fp = NULL;

	fp = fopen(filename, "r");

	//�̿�
}

//file ����(�̸�/Ÿ��)�� �˸����� üũ (������ 0, Ʋ���� 1)
int fileformatcheck(char *filename, int people) {
	FILE *fp = NULL;
	
	fp = fopen(filename, "r");

	for (int i = 0; i < people; i++) {
		if (lineformatcheck(filename)) {
			printf("���� ������ �߸��Ǿ����ϴ�!\n");
			fclose(fp);
			return 1;
		}
	}

	fclose(fp);
	
	return 0;
}

//������� ���
void printresult(LIST *list) {
	for (int i = 0; i < people; i++) {
		printf("%s:%d��\n", list->arr[i]->name, list->arr[i].personalprice);
	}
}

void typecalculation(LIST *list) {
	for (int i = 0; i < list->people; i++) {
		switch (list->arr[i].type) {//���� �̻��ѵ�..
		case 1:
			list->typea++;
			break;
		case 2:
			list->typeb++;
			break;
		case 3:
			list->typec++;
			break;
		case 4:
			list->typed++;
			break;
		default:
			break;
		}
	}
}

//��°��� ����ϴ� �����Լ�
void calculate(int price, int option, LIST *list) {

	int snackprice = 0;
	int newprice = 0;

	switch (option) {
	case 1: snackprice = 5000;
		break;
	default: snackprice = option * 4000;
		break;
	}

	int newprice = (price + (snackprice * list->typeb) + (4000 * list->typec) + (snackprice + 4000)*list->typed);

	for (int i = 0; i < people; i++) {
		switch (list->arr[i].type) {
		case 1:
			list->arr[i].personalprice = newprice / list->people;
			break;
		case 2:
			list->arr[i].personalprice = (newprice / list->people) - snackprice;
			break;
		case 3:
			list->arr[i].personalprice = (newprice / list->people) - 4000;
			break;
		case 4:
			list->arr[i].personalprice = (newprice / list->people) - (snackprice + 4000);
			break;
		default:
			break;
		}
	}
}

int main(int argc, char **agrv) {

	int price = 0;
	int option = 0;
	int people = 0;
	
	size_t len = 0;
	ssize_t nread;
	FILE *stream = NULL;

	if (argc != 2) {
		fprintf(stderr, "Usage: %s <file>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	stream = fopen(argv[1], "r");
	if (stream == NULL) {
		perror("fopen");
		exit(EXIT_FAILURE);
	}

	printf("�� ��Ǯ�� ����� �Է��ϼ���: ");

	scanf_s("%d", &price);

	printf("\n");

	printf("���̺�� ��Ų ���� ������ �Է��ϼ���: ");

	scanf_s("%d", &option);

	printf("\n");
	
	//���Ͽ��� ��� ���� �д� ����
	while ((nread = getline(&line, &len, stream)) != -1) {
		if ((lineformatcheck(argv[1])) == 0) {
			people++;
		}
	}

	if (fileformatcheck(argv[1]), people) {
		printf("File format error!\n");
		return 0;
	}

	LIST *list = createlist(people);
	
	_createdetails(list, argv[1]);

	qsort(list, sizeof(list) / sizeof(char), sizeof(char), _compare); //�������� ���ľ���, ��� ������� �𸣰���

	typecalculation(list);

	calculate(price, option, list);

	printresult(list);

	destroylist(list);

	fclose(fp);

	return 0;
}

