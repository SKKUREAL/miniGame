#include <iostream>
#include <random>

#define LOTTO_MINUS_ONE_SIZE 6

typedef struct _Node {
	int item;
	struct _Node* prev, * next;
} Node;

typedef struct _LinkedList {
	Node* head, * tail;
} LinkedList;


LinkedList * Double_LinkedList_initiate() {

	LinkedList * newList = new LinkedList;
	newList->head = new Node;
	newList->tail = new Node;
	newList->head->next = newList->tail;
	newList->head->prev = NULL;
	newList->tail->next = NULL;
	newList->tail->prev = newList->tail;

	return newList;

}

Node* Generate_Node() {

	Node* node = new Node;
	node->item = 0;
	node->next = NULL;

	return node;
}

int random_number_generator(LinkedList* list) {

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dis(1, 45);

	int random_number = dis(gen);

	Node* node = list->head->next;

	while (node != list->tail) {
		if (node->item == random_number) {
			random_number = dis(gen);
		}
		node = node->next;
	}

	return random_number;
}


void lotto_number_double_linkedList_generate (LinkedList* List, int lotto_count) {

	Node* node = Generate_Node();
	node->next = List->tail;
	node->prev = List->head;
	List->head->next = node;
	List->tail->prev = node;

	

	for (int i = 1; i < lotto_count; i++) {

		node->item = random_number_generator(List);
		Node* newnode = Generate_Node();
		node->next->prev = newnode;
		newnode->next = node->next;
		newnode->prev = node;
		node->next = newnode;

		node = newnode;
	}
	node->item = random_number_generator(List);
}

void printItems(LinkedList *list) {
	Node *node = list->head->next;
	int size = 0;
	std::cout << "\n";
	while (node != list->tail) {
		//printf("%d -> ", node->item);
		if (node->next == list->tail && size == LOTTO_MINUS_ONE_SIZE) std::cout << "" << node->item << " ";
		else std::cout << node->item << " ";
		node = node->next;
		size ++;
	}
	printf("(size: %d)", size);
}

int * lotto_number_check(LinkedList * MyList, LinkedList * PrizeList) {

	Node* Mynode = MyList->head->next;
	Node* PrizeNode = PrizeList->head->next;
	
	int* Winingcount = new int[2] { 0, };

	while (Mynode != MyList->tail) {
		while (PrizeNode != PrizeList->tail) {
			if (Mynode->item == PrizeNode->item) {
				if (PrizeNode->next == PrizeList->tail) Winingcount[1]++;
				else Winingcount[0]++;
			}
			PrizeNode = PrizeNode->next;
		}
		Mynode = Mynode->next;
		PrizeNode = PrizeList->head->next;
	}
	return(Winingcount);
}

void winingResult(int * winingcount, int* Result) {

	
	
	if (winingcount[0] == 6) { Result[0]++; std::cout << " 1µî´çÃ·";}
	else if (winingcount[0] == 5 && winingcount[1] == 1) { Result[1]++; std::cout << " 2µî´çÃ·";}
	else if (winingcount[0] == 5) { Result[2]++; std::cout << " 3µî´çÃ·";}
	else if (winingcount[0] == 4) { Result[3]++; std::cout << " 4µî´çÃ·";}
	else if (winingcount[0] == 3) { Result[4]++; std::cout << " 5µî´çÃ·";}
	else std::cout << " ²Î";
}

void GameStart(LinkedList* RealLottoNumberList, int * Result) {
	LinkedList* DoubleLinkedList = Double_LinkedList_initiate();
	lotto_number_double_linkedList_generate(DoubleLinkedList, 6);
	printItems(DoubleLinkedList);

	int* winning_arr = lotto_number_check(DoubleLinkedList, RealLottoNumberList);

	winingResult(winning_arr, Result);

}




int main() {

	

	std::cout << "\n";

	LinkedList* RealLottoNumberList = Double_LinkedList_initiate();
	lotto_number_double_linkedList_generate(RealLottoNumberList, 7);
	//printItems(RealLottoNumberList);

	int* Result = new int[5] { 0, };

	for (int i = 0; i < 10; i++) {
		GameStart(RealLottoNumberList, Result);
	}
	std::cout << "\n";
	printItems(RealLottoNumberList);
	std::cout << "\n\n";

	std::cout << "´çÃ·È½¼ö  1µî:" << Result[0] << "  2µî:" << Result[1] <<"  3µî:" << Result[2] << "  4µî:"<< Result[3] << "  5µî:" << Result[4];
	std::cout << "\n";

	


	return 0;
}