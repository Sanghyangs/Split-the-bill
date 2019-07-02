#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define _CRT_SECURE_NO_WARNINGS


//이름 / 옵션(1: 술O 안주O, 2: 술O 안주X, 3: 술X 안주O, 4: 술X 안주X)의 형식으로 받음.
//ex) 홍길동 / 1
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

//구조체 생성
LIST *createlist(int people) {
	LIST *list = (LIST*)calloc(1, sizeof(LIST));//이부분 처리 헷갈림
	DETAILS *arr = (DETAILS*)calloc(1, sizeof(DETAILS)*people);
	list->people = people;
	list->typea = 0;
	list->typeb = 0;
	list->typec = 0;
	list->typed = 0;
	return list;
}

void *_createdetails(LIST *list, char *filename) {
	//파일 읽어서 이름, 옵션을 LIST 구조체 내부의 DETAILS 구조체에 저장
	int line = 0;
	while ((nread = getline(&line, &len, stream)) != -1) {
		line++;
		// /나오기 전까지 스트링(name)을 읽어서 저장
		list->arr[line - 1]->name = ;
		// /이후의 정수를 저장(type)
		list->arr[line - 1].type = ;
		//personalprice 초기화
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

//qsort 위한 비교함수
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

//line을 1줄씩 읽어 이름/타입 의 형식으로 구성되어있는지 확인 (맞으면 0, 틀리면 1)
int lineformatcheck(char *filename) {
	FILE *fp = NULL;

	fp = fopen(filename, "r");

	//미완
}

//file 형식(이름/타입)이 알맞은지 체크 (맞으면 0, 틀리면 1)
int fileformatcheck(char *filename, int people) {
	FILE *fp = NULL;
	
	fp = fopen(filename, "r");

	for (int i = 0; i < people; i++) {
		if (lineformatcheck(filename)) {
			printf("파일 형식이 잘못되었습니다!\n");
			fclose(fp);
			return 1;
		}
	}

	fclose(fp);
	
	return 0;
}

//결과값을 출력
void printresult(LIST *list) {
	for (int i = 0; i < people; i++) {
		printf("%s:%d원\n", list->arr[i]->name, list->arr[i].personalprice);
	}
}

void typecalculation(LIST *list) {
	for (int i = 0; i < list->people; i++) {
		switch (list->arr[i].type) {//조금 이상한데..
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

//출력값을 계산하는 내부함수
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

	printf("총 뒷풀이 비용을 입력하세요: ");

	scanf_s("%d", &price);

	printf("\n");

	printf("테이블당 시킨 안주 개수를 입력하세요: ");

	scanf_s("%d", &option);

	printf("\n");
	
	//파일에서 사람 수를 읽는 과정
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

	qsort(list, sizeof(list) / sizeof(char), sizeof(char), _compare); //전달인자 고쳐야함, 어떻게 써야할지 모르겠음

	typecalculation(list);

	calculate(price, option, list);

	printresult(list);

	destroylist(list);

	fclose(fp);

	return 0;
}

