#include <stdio.h>

void printHeart(int number);

int main() {
	//只能单数，不能双数
	printHeart(9);
	return 0;
}

void printHeart(int number) {
	//打印上半段
	int space;
	int star;
	int n = number / 2 + 1;//上三角行数

	for (int i = 1; i < n; i++) {
		//打印空格
		for (space = 0; space < n - i - 1; space++) {
			printf(" ");
		}
		//打印星
		for (star = 0; star < i+1; star++) {
			printf("* ");
		}
		//打印空格
		for (space = 0; space < 2 * (n - i - 1); space++) {
			printf(" ");
		}
	
		//打印星
		for (star = 0; star < i + 1; star++) {
			printf("* ");
		}
		printf("\n");
	}
	
	//打印下半段
	for (int i = 0; i < number; i++) {
		//i是多少，就打印多少空格
		for (int j = 0; j <= i; ++j) {
			printf(" ");
		}
		for (int j = i; j < number; ++j) {
			printf("* ");
		}
		printf("\n");
	}
}
