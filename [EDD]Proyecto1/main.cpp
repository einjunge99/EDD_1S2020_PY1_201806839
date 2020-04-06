#include <iostream>
#include "json.hpp"
#include <fstream>
#include <typeinfo>
#include <Windows.h>
#include <conio.h>
#include <sstream>



using json = nlohmann::json;
using namespace std;
using json = nlohmann::json;

//----------------------------------------------------------------//
//---------------------------CONSOLE FUNCTIONS--------------------//
//----------------------------------------------------------------//

void gotoxy(int x,int y){
    HANDLE hCon;
    hCon=GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;
    dwPos.X=x;
    dwPos.Y=y;
    SetConsoleCursorPosition(hCon,dwPos);
}
void hideCursor(){
    HANDLE hCon;
    hCon=GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cci;
    cci.dwSize=2;
    cci.bVisible= FALSE;
    SetConsoleCursorInfo(hCon,&cci);
}

void margins(){
    for(int i=2;i<90;i++) {
        gotoxy(i, 3);
        printf("%c", 205);
        gotoxy(i, 25);
        printf("%c", 205);
    }
    for(int i=4;i<25;i++){
        gotoxy(2,i);
        printf("%c",186);
        gotoxy(89,i);
        printf("%c",186);
    }

}
void mainMenu() {
    gotoxy(7, 6);
    cout<<"UNIVERSIDAD DE SAN CARLOS DE GUATEMALA";
    gotoxy(7, 7);
    cout<<"FACULTAD DE INGENIERIA";
    gotoxy(7, 8);
    cout<<"ESTRUCTURAS DE DATOS";
    gotoxy(7, 9);
    cout<<"PROYECTO 1";
    gotoxy(7, 10);
    cout<<"JULIAN ISAAC MALDONADO LOPEZ";
    gotoxy(7, 11);
    cout<<"201806839";
    gotoxy(7, 18);
    cout<<"MENU";
    gotoxy(7, 19);
    cout<<"1. Lectura de archivo";
    gotoxy(7, 20);
    cout<<"2. Juego";
    gotoxy(7, 21);
    cout<<"3. Salir";

}

void reports() {
    gotoxy(7, 6);
    cout<<"SELECCIONE EL REPORTE A DESPLEGAR";
    gotoxy(7, 8);
    cout<<"0. Palabras en el diccionario";
    gotoxy(7, 9);
    cout<<"1. Cola de fichas disponibles";
    gotoxy(7, 10);
    cout<<"2. Usuarios registrados";
    gotoxy(7, 11);
    cout<<"3. Preorden";
    gotoxy(7, 12);
    cout<<"4. Inorden";
    gotoxy(7, 13);
    cout<<"5. Postorden";
    gotoxy(7, 14);
    cout<<"6. Historial jugador";
    gotoxy(7, 15);
    cout<<"7. Scoreboard";
    gotoxy(7, 16);
    cout<<"8. Tablero actual";
    gotoxy(7, 17);
    cout<<"9. Fichas actuales";

}

void game(){

    gotoxy(5, 6);
    cout<<" %%%%%%%    %%%%%%%* #%%%%%%%%   .%%,/%%   %%%%%%%/  *%%%%%%&   %%      %%%%%%%";
    gotoxy(5, 7);
    cout<<" %%%#     #%#        #%.    &%   %%    %%  %%   %%*  *%/  #%&   %%      %%/     ";
    gotoxy(5, 8);
    cout<<"      %%% %%/        #%%%%%%.    %%....%&  %%    &%/ *%/   %%%  %%     #%%      ";
    gotoxy(5, 9);
    cout<<" (%%//%%%   &&%##%%. #%.   /%&   %%    %%  %%(((%%%. %#((%%%#  %&(((( /%%&((((";

    gotoxy(7, 12);
    cout<<"1. Crear nuevo jugador";
    gotoxy(7, 13);
    cout<<"2. Seleccionar jugador existente";

}

void board(){
    gotoxy(8, 6);
    cout<<"PLAYER 1" ;
    gotoxy(8, 9);
    cout<<"1. Colochar fichas";
    gotoxy(8, 10);
    cout<<"2. Cambiar fichas";
    gotoxy(60, 6);
    cout<<"PLAYER 2";
    gotoxy(60, 9);
    cout<<"1. Colochar fichas";
    gotoxy(60, 10);
    cout<<"2. Cambiar fichas";

    gotoxy(8, 25);
    cout<<"^r(Reportes)";
    gotoxy(25, 25);
    cout<<"^x(Salir)";

}

void erasePlayer(){
    for (int i = 7; i < 75; i++) {
        for(int k=12; k<20;k++){
            gotoxy(i,k);
            cout<<" ";
        }
    }
}
void clearPlayer1(){
    for (int i = 7; i < 45; i++) {
        for(int k=9; k<25;k++){
            gotoxy(i,k);
            cout<<" ";
        }
    }
}
void clearPlayer2(){
    for (int i = 50; i < 89; i++) {
        for(int k=9; k<25;k++){
            gotoxy(i,k);
            cout<<" ";
        }
    }
}

void erase() {
    for (int i = 3; i < 89; i++) {
        for (int k = 4; k < 25; k++) {
            gotoxy(i, k);
            cout << " ";
            gotoxy(i, k);
            cout << " ";
        }
    }
}



//----------------------------------------------------------------//
//----------------------------STRUCTURES--------------------------//
//----------------------------------------------------------------//

class token{
public:
    char letter;
    int score;
    token(char letter, int score){
        this->letter=letter;
        this->score=score;
    }
};

class nodeDoubleLinked{
public:
    nodeDoubleLinked *next;
    nodeDoubleLinked *prev;

    //----------------Player tokens--------------//

    string word;
    nodeDoubleLinked(){
    }
    nodeDoubleLinked(string word) {
        this->word = word;
        next = 0;
        prev = 0;
    }
    //--------------Dictionary words------------//
    token *letter;
    nodeDoubleLinked(token *letter) {
        this->letter = letter;
        next = 0;
        prev = 0;
    }
};


class doubleCircular{
public:
    nodeDoubleLinked *header;
    int size;

    doubleCircular(){
        header=0;
        size=0;
    }

    void add(string word){
        nodeDoubleLinked *node=new nodeDoubleLinked(word);
        if(header==0){
            node->next=node;
            node->prev=node;
            header=node;
        }
        else{
            nodeDoubleLinked *tail=header->prev;

            node->next=header;
            header->prev=node;

            node->prev=tail;
            tail->next=node;
        }
        size++;
    }
    bool searchWord(string word){
        nodeDoubleLinked *temp=header;
        for (int i = 0; i < size; ++i) {
            if(temp->word==word){
                return true;
            }
            temp=temp->next;
        }
        return false;
    }
    void clean(){
        header=0;
        size=0;
    }
};              //--------------DICTIONARY
class doubleLinked{
public:
    nodeDoubleLinked *header;
    nodeDoubleLinked *tail;
    int size;

    doubleLinked(){
        header=0;
        tail=0;
        size=0;
    }

    void add(token *letter){
        nodeDoubleLinked *node=new nodeDoubleLinked(letter);
        if(header==0){
            header=node;
            tail=node;
        }
        else{
            tail->next=node;
            node->prev=tail;
            tail=node;

        }
        size++;
    }
    void deleteFirst(){
        if(header->next==0){
            delete header;
            header=NULL;
            tail=NULL;
            size--;
        }
        else if(header!=0){
            header=header->next;
            delete header->prev;
            header->prev=0;
            size--;
        }
    }
    void deleteLast(){
        if(header->next==0){
            delete header;
            header=0;
            tail=0;
            size--;
        }
        else if(header!=0){
            tail=tail->prev;
            delete tail->next;
            tail->next=0;
            size--;
        }
    }
    void deleteAt(int position){
        if(position<1||position>size+1){
            return;
        }
        else if(position==1){
            deleteFirst();
        }
        else if(position==size){
            deleteLast();
        }
        else if(header!=0){
            nodeDoubleLinked *current=header;
            for(int i=1;i<position;i++){
                current=current->next;
            }
            current->prev->next=current->next;
            current->next->prev=current->prev;
            delete current;
            size--;


        }
    }
    void deleteCharAt(char token){
        int cont=0;
        if(header!=0){
            nodeDoubleLinked *current=header;
            while(current!=0){
                if(current->letter->letter==token) {
                    break;
                }else{
                    current=current->next;
                    cont++;
                }
            }
            if(cont==0){
                deleteFirst();
            }
            else if(cont+1==size){
                deleteLast();
            }
            else {
                current->prev->next = current->next;
                current->next->prev = current->prev;
                delete current;
                size--;
            }

        }
    }
    nodeDoubleLinked *search(int pos) {
        nodeDoubleLinked *temp = header;
        int cont = 1;
        while (cont < pos) {
            temp = temp->next;
            cont++;
        }
        return temp;
    }
    token *searchToken(char token){
        bool found=false;
        nodeDoubleLinked *temp=header;

            while (temp != 0) {
                if (temp->letter->letter == token) {
                    found=true;
                    break;
                } else {
                    temp = temp->next;
                }

            }
            if(found){
               return temp->letter;
            }
            return 0;

    }
    void showTokens(int xPos) {
        int yPos = 15;
        gotoxy(xPos, yPos);
        cout << "Tus fichas: ";
        yPos++;

        for (int i = 16; i < 24; ++i) {
            gotoxy(xPos, i);
            cout << " ";
        }
        nodeDoubleLinked *temp = header;
        while (temp != 0) {
            gotoxy(xPos, yPos);
            cout << temp->letter->letter << "\n";
            temp = temp->next;
            yPos++;
        }
    }
    void clean(){
        header=0;
        tail=0;
        size=0;
    }
};                //--------------PLAYER TOKENS


class nodeQueue{
public:
    nodeQueue *next;
    token *letter;
    nodeQueue(token *letter){
        this->letter=letter;
        next=0;
    }

};
class queue{
public:
    nodeQueue *header;
    nodeQueue *tail;
    int size;

    queue(){
        header=0;
        tail=0;
        size=0;
    }

    void enqueue(token *letter){
        nodeQueue *node=new nodeQueue(letter);
        if(header==0){
            header=node;
            tail=node;
        }
        else{
            tail->next=node;
            tail=node;

        }
        size++;

    }
    nodeQueue *dequeue(){
        nodeQueue *temp=header;
        header=header->next;
        if(header==0){
            tail=0;
        }
        size--;
        return temp;
    }

    bool isEmpty(){
        if(header==0){
            return true;
        }
        return false;
    }
    void clean(){
        header=0;
        tail=0;
        size=0;
    }
};                      //--------------TOKEN BAG


class nodeLinkedList{
public:
    nodeLinkedList *next;

    //-----------------PERSONAL RECORD----------------//
    int score;
    nodeLinkedList(int score){
        this->score=score;
        next=0;
    }
    //------------------SCOREBOARD-------------------//
    string username;


};
class linkedList {
public:
    nodeLinkedList *header;
    nodeLinkedList *tail;
    int size;

    linkedList(){
    header=0;
    tail=0;
    size=0;
    }
    void append(nodeLinkedList *node) {
        tail->next = node;
        tail = node;
    }

    void prepend(nodeLinkedList *node) {
        nodeLinkedList *temp = header;
        header = node;
        node->next = temp;
    }

    void add(int score,string username) {
        int cont = 0;
        string param;
        string compare;
        nodeLinkedList *node = new nodeLinkedList(score);
        node->username=username;
        nodeLinkedList *current = header;

        if (header == 0) {
            header = node;
            tail = node;
        } else {
            param = node->score;
            compare = current->score;
            nodeLinkedList *prev;
            while (current != 0 && param <= compare) {
                prev = current;
                current = current->next;
                cont++;
            }
            if (cont == 0) {
                append(node);
            } else if (cont == size) {
                prepend(node);
            } else {
                prev->next = node;
                node->next = current;
            }
        }
        size++;
    }
    void clean(){
        header=0;
        tail=0;
        size=0;
    }
    int getTop(){
        int top=0;
        if(header!=0) {
             top = header->score;
        }
        return top;
    }
};                 //-----------PERSONAL SCORE AND SCOREBOARD

class player{
public:
    string username;
    int ID;
    int top;
    linkedList *scores=new linkedList();
    doubleLinked *tokens=new doubleLinked();
    player(string user){
        this->username=user;
        ID=0;
        top=0;
    }
    void setTop(){
        this->top=scores->getTop();
    }

};

int yPos=13;
bool duplicated=false;
class nodeBinaryTree{
public:
    nodeBinaryTree *right;
    nodeBinaryTree *left;
    player *user;

    nodeBinaryTree(player *user){
        this->user=user;
        right=0;
        left=0;
    }

};              //------------PLAYERS
class playerABB{
public:
    nodeBinaryTree *root;
    int cont;
    playerABB(){
        root=0;
        cont=0;
    }

    bool add(player *user){
        bool state;
        nodeBinaryTree *node=new nodeBinaryTree(user);
        nodeBinaryTree *result;
        node->user->ID=cont;
        cont++;
        root=recursiveAdd(this->root,node);
        state=duplicated;
        return state;
    }
    nodeBinaryTree *recursiveAdd(nodeBinaryTree *root,nodeBinaryTree *data){
        if(root==0){
            return data;
        }
        if(data->user->username<root->user->username){
            root->left=recursiveAdd(root->left,data);
        }
        else if(data->user->username>root->user->username){
            root->right=recursiveAdd(root->right,data);
        }
        else{
            duplicated=true;
            return root;
        }
        return root;
    }

    bool getSize() {
        if (root != 0) {
            if (root->right != 0 || root->left != 0) {
                return true;
            }
            return false;
        }
    }

    nodeBinaryTree *search(int ID){
        nodeBinaryTree *temp=recursiveSearch(root,ID);
        return temp;
    }
    nodeBinaryTree *recursiveSearch(nodeBinaryTree *node,int ID){

        if(node!=0){
            if(node->user->ID==ID){
                return node;
            }
            else{
                nodeBinaryTree *temp=recursiveSearch(node->left,ID);
                if(temp==0){
                    temp=recursiveSearch(node->right,ID);
                }
                return temp;
            }
        }
        else{
            return 0;
        }
    }

    void showPlayers(){
        showRecursive(root);
    }
    nodeBinaryTree *showRecursive(nodeBinaryTree *player){
        if(player!=0){
            showRecursive(player->left);
            gotoxy(7,yPos);
            cout<<player->user->ID<<".";
            gotoxy(10,yPos);
            cout<<player->user->username;
            yPos++;
            showRecursive(player->right);
        }
    }

};

//----------AUXILIAR STRUCTURES------------------------------------------//
class auxNode{
public:
    auxNode *next;

    //-------------ABB REPORT DATA-------------//
    string username;
    auxNode(string username){
        this->username=username;
        next=0;
    }

    //-------------MATRIX VALIDATION DATA--------//
    int x;
    int y;
    token *gameToken;
    auxNode(int x,int y,token *gameToken){
        this->x=x;
        this->y=y;
        this->gameToken=gameToken;
        next=0;
    }

    //---------------SPECIAL SQUARE--------------//
    int bonus=1;
    bool active=true;
    auxNode(int x,int y,int bonus){
        this->x=x;
        this->y=y;
        this->bonus=bonus;
        next=0;
    }

};
class auxList {
public:
    auxNode *header;
    auxNode *tail;
    int size;
    auxList() {
        header = 0;
        tail = 0;
        size = 0;
    }

    void append(auxNode *node) {

        if(header==0){
            header=node;
            tail=node;
            size++;
        }
        else {
            tail->next = node;
            tail = node;
            size++;
        }
    }
    void clean(){
        header = 0;
        tail = 0;
        size = 0;
    }
    auxNode *searchSquare(int x,int y){
        auxNode *temp=header;
        while(temp!=0){
            if(temp->x==x&&temp->y==y){
                return temp;
            }
            temp=temp->next;
        }
        return 0;
    }


};                  //---------------STORES ABB ELEMENTS

class stack {
public:
    auxNode *top;
    int cont;

    stack() {
        top = 0;
        cont=0;
    }


    void push(int x,int y,token *tokenGame) {

        auxNode *node = new auxNode(x,y,tokenGame);
        if (top == 0) {
            top = node;
        } else {
            node->next = top;
            top = node;
        }
        cont++;
    }
    auxNode *pop(){
        if(top!=NULL){
            auxNode *tempData=top;
            top=top->next;
            cont--;
            return tempData;
        }
        return 0;
    }
    bool isEmpty(){
        if(cont==0){
            return true;
        }
        return false;
    }
};



class listNode{
public:
    auxList *word;
    listNode *next;
    listNode(auxList *word){
        this->word=word;
        next=0;
    }
};
class listList {                      //----------------LIST OF LIST
public:
    listNode *header;
    listNode *tail;
    int size;
    listList() {
        header = 0;
        tail = 0;
        size = 0;
    }

    void append(listNode *node) {

        if(header==0){
            header=node;
            tail=node;
            size++;
        }
        else {
            tail->next = node;
            tail = node;
            size++;
        }
    }
    void clean(){
        header = 0;
        tail = 0;
        size = 0;
    }

};                  //---------------STORES ABB ELEMENTS

//---------------Matrix's structures---------------//
class nodeMatrix{
public:
    token *data;
    int x,y;
    nodeMatrix *up;
    nodeMatrix *down;
    nodeMatrix *right;
    nodeMatrix *left;
    string color;            //----------DOUBLE: gray, TRIPLE: darkolivegreen1, NORMAL: white

    nodeMatrix(token *data,int x, int y,string color){
        this->data=data;
        this->x=x;
        this->y=y;
        this->color=color;
        up=0;
        down=0;
        left=0;
        right=0;
    }
};

class rowList {
public:
    nodeMatrix *header;
    nodeMatrix *tail;
    int size;

    rowList() {
        header = 0;
        tail = 0;
        size = 0;
    }

    void append(nodeMatrix *node) {
        if (header == 0) {
            header = node;
            tail = node;
        } else {
            tail->right = node;
            node->left = tail;
            tail = node;

        }
    }

    void prepend(nodeMatrix *node) {
        if (header == 0) {
            header = node;
            tail = node;
        } else {
            header->left = node;
            node->right = header;
            header = node;
        }
    }

    void add(nodeMatrix *node) {//--------------------------HEEREEEEEE
        int position = node->x;
        if (size == 0) {
            prepend(node);
        } else {
            int cont = 0;
            nodeMatrix *current = header;
            while (current != 0) {
                if (node->x < current->x) {
                    break;
                } else {
                    current = current->right;
                    cont++;
                }
            }
            if (cont == size) {
                append(node);
            }
            else if(cont==0){
                prepend(node);
            }
            else {
                current->left->right = node;
                node->left = current->left;

                node->right = current;
                current->left = node;
            }
        }
        size++;
    }
    //---------------------------------------
    void deleteFirst(){
        if(header->right==0){
            delete header;
            header=0;
            tail=0;
        }
        else if(header!=0){
            header=header->right;
            delete header->left;
            header->left=0;
        }
    }
    void deleteLast(){
        if(header->right==0){
            delete header;
            header=0;
            tail=0;
        }
        else if(header!=0){
            tail=tail->left;
            delete tail->right;
            tail->right=0;
        }
    }
    void deleteAt(int x) {

        int cont = 0;
        nodeMatrix *current = header;
        while (current->x != x) {
            current = current->right;
            cont++;
        }
        if (cont == 0) {
            deleteFirst();
        } else if (cont == size-1) {
            deleteLast();
        } else {
            current->left->right = current->right;
            current->right->left = current->left;
            delete current;
        }
        size--;
    }

    //------------------------------------
    bool search(int x,int y){
        bool found=false;
        nodeMatrix *temp=header;
        while(temp!=0){
            if(temp->x==x&&temp->y==y){
                found=true;
                break;
            }
            else{
                temp=temp->right;
            }
        }
        return found;
    }
    nodeMatrix *searchNode(int x,int y){
        nodeMatrix *temp=header;
        while(temp!=0){
            if(temp->x==x&&temp->y==y){
               return temp;
            }
                temp=temp->right;
        }
        return 0;
    }



    //----------------------VALIDATION SEARCH-----------------//
    auxList *validAdjacent(int x,int y,bool direction,bool set) {             //-----------TRUE: horizontal, FALSE: vertical

        stack *tokenStack = new stack();
        auxList *concat = new auxList();

        nodeMatrix *temp = searchNode(x, y);
        while (temp != 0) {
            tokenStack->push(temp->x,temp->y,temp->data);
            if(direction){
                temp=temp->left;
            }
            else{
                temp = temp->up;
            }

        }
        while (!tokenStack->isEmpty()) {
            auxNode *info=tokenStack->pop();
            int x=info->x;
            int y=info->y;
            if(!set){
                x=0;
                y=0;
            }
            auxNode *temp = new auxNode(x, y, info->gameToken);
            concat->append(temp);
        }
        return concat;
    }


    bool isEmpty(){
        if(size==0){
            return true;
        }
        return false;
    }
};
class columnList{
public:
    nodeMatrix *header;
    nodeMatrix *tail;
    int size;

    columnList(){
        header=0;
        tail=0;
        size=0;
    }

    void append(nodeMatrix *node){
        if(header==0){
            header=node;
            tail=node;
        }
        else{
            tail->down=node;
            node->up=tail;
            tail=node;

        }

    }
    void prepend(nodeMatrix *node){
        if(header==0){
            header=node;
            tail=node;
        }
        else{
            header->up=node;
            node->down=header;
            header=node;
        }
    }
    void add(nodeMatrix *node ){
        int position=node->y;
        if(size==0){
            prepend(node);
        }
        else{
            int cont=0;
            nodeMatrix *current = header;
            while(current!=0) {
                if(node->y<current->y){
                    break;
                }
                else{
                    current = current->down;
                    cont++;
                }

            }
            if (cont == size) {
                append(node);
            }
            else if(cont==0){
                prepend(node);
            }
            else {
                current->up->down = node;
                node->up = current->up;

                node->down = current;
                current->up = node;
            }
        }
        size++;
    }
    //---------------------------------------
    void deleteFirst(){
        if(header->down==0){
            header=0;
            tail=0;
        }
        else if(header!=0){
            header=header->down;
            header->up=0;
        }
    }
    void deleteLast(){
        if(header->down==0){
            header=0;
            tail=0;
        }
        else if(header!=0){
            tail=tail->up;
            tail->down=0;
        }
    }
    void deleteAt(int y) {
        int cont = 0;
        nodeMatrix *current = header;
        while (current->y != y) {
            current = current->down;
            cont++;
        }
        if (cont == 0) {
            deleteFirst();
        } else if (cont == size-1) {
            deleteLast();
        } else {
            current->up->down = current->down;
            current->down->up = current->up;
        }
        size--;
    }

    //------------------------------------
    bool search(int x,int y) {
        bool found = false;
        nodeMatrix *temp = header;
        while (temp != 0) {
            if (temp->x == x && temp->y == y) {
                found = true;
                break;
            } else {
                temp = temp->down;
            }
        }
        return found;
    }
    nodeMatrix *searchNode(int x,int y) {
        nodeMatrix *temp = header;
        while (temp != 0) {
            if (temp->x == x && temp->y == y) {
                return temp;
            }
            temp = temp->down;
        }
        return 0;
    }


    token *searchToken(int x,int y){

        nodeMatrix *temp=header;
        while(temp!=0){
            if(temp->x==x&&temp->y==y){
                return temp->data;
            }
                temp=temp->down;

        }
        return 0;
    }
    bool isEmpty(){
        if(size==0){
            return true;
        }
        return false;
    }
};

class nodeHeader{
public:
    int x;
    nodeHeader *next;
    nodeHeader *prev;
    columnList *columns;

    nodeHeader(int x){
        this->x=x;
        columns =new columnList();
        next=0;
        prev=0;
    }
};
class nodeSider{
public:
    int y;
    nodeSider *next;
    nodeSider *prev;
    rowList *rows;

    nodeSider(int y){
        this->y=y;
        rows = new rowList();
        next=0;
        prev=0;
    }
};

class headerList{
public:
    nodeHeader *header;
    nodeHeader *tail;
    int size;
    int top;

    headerList(int top){
        header=0;
        tail=0;
        size=0;
        this->top=top;

    }

    void append(nodeHeader *node){
        if(header==0){
            header=node;
            tail=node;
        }
        else{
            tail->next=node;
            node->prev=tail;
            tail=node;

        }
    }
    void prepend(nodeHeader *node){
        if(header==0){
            header=node;
            tail=node;
        }
        else{
            header->prev=node;
            node->next=header;
            header=node;
        }
    }
    nodeHeader *add(nodeHeader *node ){
        int position=node->x;
        if(position>0&&position<top+1) {

            if (header == 0) {
                prepend(node);
            } else if (position == 1) {
                prepend(node);
            } else if (position == top) {
                append(node);
            } else {
                int cont = 1;
                nodeHeader *current = header;
                while (current != 0) {
                    if (node->x < current->x) {
                        break;
                    } else {
                        current = current->next;
                        cont++;
                    }
                }
                if (cont == size+1) {
                    append(node);
                }
                else if(cont==1){
                    prepend(node);
                }
                else {
                    current->prev->next = node;
                    node->prev = current->prev;

                    node->next = current;
                    current->prev = node;
                }

            }
            size++;
            return node;
        }
        return 0;
    }
    //---------------------------------------
    void deleteFirst(){
        if(header->next==0){
            delete header;
            header=0;
            tail=0;
        }
        else if(header!=0){
            header=header->next;
            delete header->prev;
            header->prev=0;
        }
    }
    void deleteLast(){
        if(header->next==0){
            delete header;
            header=0;
            tail=0;
        }
        else if(header!=0){
            tail=tail->prev;
            delete tail->next;
            tail->next=0;
        }
    }
    void deleteAt(int x,int y) {
        int cont = 0;
        nodeHeader *current = header;
        while (current->x != x) {
            current = current->next;
            cont++;
        }

        current->columns->deleteAt(y);
        if(current->columns->isEmpty()) {
            if (cont == 0) {
                deleteFirst();
            } else if (cont == size-1) {
                deleteLast();
            } else {
                current->prev->next = current->next;
                current->next->prev = current->prev;
                delete current;
            }
            size--;
        }
    }

    //------------------------------------
    nodeHeader *search(int x){
        nodeHeader *temp=header;
        while(temp!=0&&temp->x!=x){
            temp=temp->next;
        }
        return temp;
    }
};
class siderList{
public:
    nodeSider *header;
    nodeSider *tail;
    int size;
    int top;

    siderList(int top){
        header=0;
        tail=0;
        size=0;
        this->top=top;
    }

    void append(nodeSider *node){
        if(header==0){
            header=node;
            tail=node;
        }
        else{
            tail->next=node;
            node->prev=tail;
            tail=node;
        }
    }
    void prepend(nodeSider *node){
        if(header==0){
            header=node;
            tail=node;
        }
        else{
            header->prev=node;
            node->next=header;
            header=node;
        }
    }
    nodeSider *add( nodeSider *node ) {
        int position = node->y;
        if (position > 0 && position < top + 1) {

            if (header == 0) {
                prepend(node);
            } else if (position == 1) {
                prepend(node);
            } else if (position == top) {
                append(node);
            } else {
                /*Pendientes:
                 *      -Arreglar los ciclos de cada una de las listas, agregando el 'break' para evitar el nullPointer
                 *      -De igual forma, en el tercer if, es position==top
                 *      -De momento, nada mas eso...
                 */
                int cont = 1;
                nodeSider *current = header;
                while (current != 0) {
                    if (node->y < current->y) {
                        break;
                    } else {
                        current = current->next;
                        cont++;
                    }
                }
                if (cont == size+1 ) {
                    append(node);
                }
                else if(cont == 1){
                    prepend(node);
                }else {
                    current->prev->next = node;
                    node->prev = current->prev;

                    node->next = current;
                    current->prev = node;
                }

            }
            size++;
            return node;
        }
        return 0;
    }
    //---------------------------------------
    void deleteFirst(){
        if(header->next==0){
            delete header;
            header=0;
            tail=0;
        }
        else if(header!=0){
            header=header->next;
            delete header->prev;
            header->prev=0;
        }
    }
    void deleteLast(){
        if(header->next==0){
            delete header;
            header=0;
            tail=0;
        }
        else if(header!=0){
            tail=tail->prev;
            delete tail->next;
            tail->next=0;
        }
    }
    void deleteAt(int x,int y) {
        int cont = 0;
        nodeSider *current = header;
        while (current->y != y) {
            current = current->next;
            cont++;
        }

        current->rows->deleteAt(x);
        if(current->rows->isEmpty()) {
            if (cont == 0) {
                deleteFirst();
            } else if (cont == size-1) {
                deleteLast();
            } else {
                current->prev->next = current->next;
                current->next->prev = current->prev;
                delete current;
            }
            size--;
        }
    }

    //------------------------------------
    nodeSider *search(int y){
        nodeSider *temp=header;
        while(temp!=0&&temp->y!=y){
            temp=temp->next;
        }
        return temp;
    }
    bool isEmpty(){
        if(size==0){
            return true;
        }
        return false;
    }
};

class matrix {
public:
    headerList *headers;
    siderList *siders;


    matrix(int dimention) {
        headers = new headerList(dimention);
        siders = new siderList(dimention);
    }

    void add(token *data, int x, int y,string color) {
        nodeMatrix *node = new nodeMatrix(data, x, y,color);

        nodeHeader *headerTemp = headers->search(x);
        nodeSider *siderTemp = siders->search(y);

        if (headerTemp == 0) {
            nodeHeader *temp = new nodeHeader(x);
            headerTemp = headers->add(temp);
        }
        if (siderTemp == 0) {
            nodeSider *temp = new nodeSider(y);
            siderTemp = siders->add(temp);
        }

        //By just checking if headerTemp equals 0, we can tell that either the x or y coordinate was out of range
        if (headerTemp != 0&&siderTemp!=0) {
            if(!headerTemp->columns->search(x,y)){
                headerTemp->columns->add(node);
                siderTemp->rows->add(node);
            }
            else{
                cout<<"Celda ocupada, elija otra posición \n";
            }
        }
        else{
            cout<<"Posición fuera de rango \n";
        }

    }
    bool searchPosition(int x, int y){
        nodeHeader *yTemp=headers->search(x);
        nodeSider *xTemp=siders->search(y);

        if(yTemp!=0&&xTemp!=0){
            return yTemp->columns->search(x,y);
        }

        return false;
    }

    token *searchPositionToken(int x, int y){
        nodeHeader *yTemp=headers->search(x);
        nodeSider *xTemp=siders->search(y);

        if(yTemp!=0&&xTemp!=0){
            return yTemp->columns->searchToken(x,y);
        }

        return 0;
    }

    string showData() {
        string right="";
        string down="";
        string info = "";
        info += "digraph Sparce_Matrix {\n"
                "\n"
                "    node [shape=box]\n"
                "\n"
                "    Mt[ label = \"MATRIZ\", width = 1.5, style = filled, fillcolor = firebrick1, group = 0 ];\n"
                "\n"
                "    e0[ shape = point, width = 0 ];\n"
                "    e1[ shape = point, width = 0 ];\n";
        string same = "";

        string xData="";
        string yData="";
        headerList *xHeaders = headers;
        nodeHeader *yList = xHeaders->header;
        if(yList!=0){
            right+="X"+to_string(yList->x);
        }
        while (yList != 0) {
            info += "X" + to_string(yList->x) + " [label = \"" + to_string(yList->x) +
                    "\"  width = 1.5 style = filled, fillcolor = lightskyblue, group = "+to_string(yList->x)+" ]; \n";
            same += "X" + to_string(yList->x) + "; ";
            if (yList->prev != 0) {
                string curr = to_string(yList->x);
                string prev = to_string(yList->prev->x);
                info += "X" + prev + " -> " + "X" + curr + " \n";
                info += "X" + curr + " -> " + "X" + prev + " \n";

            }

            bool active=true;
            nodeMatrix *yElement=yList->columns->header;
            while (yElement != 0) {

                string sameElement="";
                xData += "X" + to_string(yElement->x) +"_Y"+to_string(yElement->y)+" [label = \"" + yElement->data->letter +
                         "\"  width = 1.5  group = "+to_string(yElement->x)+" fillcolor = "+yElement->color+", style = filled ]; \n";
                sameElement= "X" + to_string(yElement->x) +"_Y"+to_string(yElement->y);
                if (yElement->left!= 0) {
                    string curr = "X" + to_string(yElement->x) +"_Y"+to_string(yElement->y);
                    string prev = "X" + to_string(yElement->left->x) +"_Y"+to_string(yElement->left->y);
                    xData += prev + " -> " + curr+" \n";
                    xData +=  curr + " -> " +prev + " \n";

                }

                if(active){
                    active=false;
                    xData+="X"+to_string(yElement->x)+" -> "+ "X" + to_string(yElement->x) +"_Y"+to_string(yElement->y)+"\n";
                }

                xData+=" { rank = same; Y"+to_string(yElement->y)+"; "+sameElement+" } \n";
                yElement=yElement->down;
            }

            yList=yList->next;
        }

        siderList *ySiders = siders;
        nodeSider *xList = ySiders->header;

        //Ya estamos cerca...no mas creo que hay que arrelgar cual imprimo en el if de active :(
        if(xList!=0){
            down+="Y"+to_string(xList->y);
        }
        while (xList != 0) {
            info += "Y" + to_string(xList->y) + " [label = \"" + to_string(xList->y) +
                    "\"  width = 1.5 style = filled, fillcolor = bisque1, group = 0 ]; \n";

            if (xList->prev != 0) {
                string curr = to_string(xList->y);
                string prev = to_string(xList->prev->y);
                info += "Y" + prev + " -> " + "Y" + curr + " \n";
                info += "Y" + curr + " -> " + "Y" + prev + " \n";
            }
            bool active=true;
            nodeMatrix *xElement=xList->rows->header;
            while (xElement != 0) {

                if (xElement->up != 0) {
                    string curr = "X" + to_string(xElement->x) +"_Y"+to_string(xElement->y);
                    string prev = "X" + to_string(xElement->up->x) +"_Y"+to_string(xElement->up->y);
                    yData += prev + " -> " + curr+" \n";
                    yData +=  curr + " -> " +prev + " \n";

                }

                if(active){
                    active=false;
                    xData+="Y"+to_string(xElement->y)+" -> "+ "X" + to_string(xElement->x) +"_Y"+to_string(xElement->y)+"\n";
                }
                xElement=xElement->right;
            }

            xList=xList->next;
        }
        if(down!=""||right!=""){
            info += "   Mt -> "+down+";\n";
            info += "    Mt -> "+right+";\n";
            info +="    { rank = same; Mt;" + same + "}\n";
        }


        info+=xData+"\n";
        info+=yData+"\n";

        info+="}";
        return info;
    }
    void clean(int dimention){
        headers = new headerList(dimention);
        siders = new siderList(dimention);
    }
};




//-----------------------------------------------------------------------//
//----------------------GLOBAL VARIABLES---------------------------------//
//-----------------------------------------------------------------------//
doubleLinked *tokenBag=new doubleLinked();
queue *tokenQueue=new queue();
playerABB *players=new playerABB();
linkedList *scoreboard=new linkedList();
doubleCircular *dictionary;
auxList *specialSquares;
auxList *validationPositions=new auxList();
listList *validWords=new listList();
int nearbyCont=0;

matrix *matrixBoard;
int xLimit=0;
int yLimit=0;

ofstream file;


player *player1;
player *player2;
int player1Score=0;
int player2Score=0;

bool activeFile=false;

void readFile(string path){

    ifstream i("C:\\Users\\Isaac Maldonado\\Desktop\\"+path);
    if(!i.fail()) {
        activeFile=true;
        gotoxy(40,22);
        cout<<"Todo bien, todo correcto";
       json j3;
        i >> j3;
        xLimit=j3.at("dimension");
        yLimit=xLimit;
        dictionary=new doubleCircular();
        specialSquares=new auxList();
        matrixBoard=new matrix(xLimit);

        for (int x = 0; x < j3.at("casillas").at("dobles").size(); x++) {
            int posX=j3.at("casillas").at("dobles")[x].at("x");
            int posY=j3.at("casillas").at("dobles")[x].at("y");
            auxNode *temp=new auxNode(posX,posY,2);
            specialSquares->append(temp);
         }
        for (int x = 0; x < j3.at("casillas").at("triples").size(); x++) {
            int posX=j3.at("casillas").at("triples")[x].at("x");
            int posY=j3.at("casillas").at("triples")[x].at("y");
            auxNode *temp=new auxNode(posX,posY,3);
            specialSquares->append(temp);
        }
        for (int x = 0; x < j3.at("diccionario").size(); x++) {
            dictionary->add(j3.at("diccionario")[x].at("palabra"));
        }

    }
    else{
        gotoxy(40,22);
        cout<<"Nel.....";

    }
}


int bagsize=96;
void addBag(int score, char letter, int size) {
    token *temp=new token(letter, score);
    for(int i=0;i<size;i++) {
        tokenBag->add(temp);
    }
}
void fillBag() {
    addBag(1, 'A', 12);
    addBag(1,'E',12);
    addBag(1,'O',9);
    addBag(1, 'I', 6);
    addBag(1, 'S', 6);
    addBag(1,'N',6);
    addBag(1, 'L', 4);
    addBag(1,'R',5);
    addBag(1,'U',5);
    addBag(1,'T',4);

    addBag(2,'D', 5);
    addBag(2,'G', 2);

    addBag(3,'C', 4);
    addBag(3,'B', 2);
    addBag(3,'M', 2);
    addBag(3,'P', 2);

    addBag(4,'H', 2);
    addBag(4,'F', 1);
    addBag(4,'V', 1);
    addBag(4,'Y', 1);

    addBag(5,'Q', 1);

    addBag(8,'J', 1);
    addBag(8,'X', 1);

    addBag(10,'Z', 1);

}
void randomFill(){
    for(int i=0;i<96;i++){
        int selection = rand() % bagsize+1;
        token *temp=tokenBag->search(selection)->letter;
        tokenBag->deleteAt(selection-1);
        tokenQueue->enqueue(temp);
        bagsize--;
    }
    fillBag();
    bagsize=96;
}


void nearby(int x,int y,bool up,bool down,bool left, bool right){
    nodeSider *row1 = matrixBoard->siders->search(y-1);
    nodeSider *row2 = matrixBoard->siders->search(y);
    nodeSider *row3 = matrixBoard->siders->search(y+1);
    if(row1!=0){
        if(up){
            if(row1->rows->search(x,y-1)){
                nearbyCont++;
            }
        }
    }
    if(row2!=0){
        if(right){
            if(row2->rows->search(x+1,y)){
                nearbyCont++;
            }
        }
        if(left){
            if(row2->rows->search(x-1,y)){
                nearbyCont++;
            }
        }
    }
    if(row3!=0){
        if(down){
            if(row3->rows->search(x,y+1)){
                nearbyCont++;
            }
        }
    }


}

bool validateList(auxList *entry){
    auxNode *temp=entry->header;
    string concat="";
    if(temp!=0){
        while(temp!=0) {
            concat += tolower(temp->gameToken->letter);
            temp=temp->next;
        }
        return dictionary->searchWord(concat);
    }
    return true;
}

bool iterateWords(){
    listNode *temp=validWords->header;
    while(temp!=0){
        if(validateList(temp->word)){
            temp=temp->next;
        }
        else{
            return false;
        }
    }
    return true;
}



void deleteMatrix(){

    auxNode *temp=validationPositions->header;
    while(temp!=0){
        int x=temp->x;
        int y=temp->y;
        if(x!=0&&y!=0){
            matrixBoard->headers->deleteAt(x,y);
            matrixBoard->siders->deleteAt(x,y);
        }
        temp=temp->next;
    }
}

void refillPlayer(player *p){
    auxNode *temp=validationPositions->header;
    while(temp!=0){
        p->tokens->add(temp->gameToken);
        temp=temp->next;
    }
}

void setScore(bool player){         //--------------FALSE: P2, TRUE: P1
    listNode *current=validWords->header;
    while(current!=0) {
        auxNode *temp = current->word->header;
        while (temp != 0) {
        auxNode *result = specialSquares->searchSquare(temp->x, temp->y);
        if (player) {
            if (result != 0) {

                if (result->active) {
                    player1Score += result->bonus * temp->gameToken->score;
                    result->active = false;
                } else {
                    player1Score += temp->gameToken->score;
                }
            } else {
                player1Score += temp->gameToken->score;
            }
        } else {
            if (result != 0) {
                if (result->active) {
                    player2Score += result->bonus * temp->gameToken->score;
                    result->active = false;
                } else {
                    player2Score += temp->gameToken->score;
                }
            } else {
                player2Score += temp->gameToken->score;
            }
        }
        temp=temp->next;
    }
        current=current->next;
    }
}

void fillPlayer1(){
    for (int var = 0; var < 7; ++var) {
        player1->tokens->add(tokenQueue->dequeue()->letter);
    }
}
void fillPlayer2(){
    for (int var = 0; var < 7; ++var) {
        player2->tokens->add(tokenQueue->dequeue()->letter);
    }
}

void resetPlayers(){
    player1->scores->add(player1Score,player1->username);
    player1->tokens->clean();

    player2->scores->add(player2Score,player2->username);
    player1->tokens->clean();

    gotoxy(30,15);
    cout<<"El ganador es";
    Sleep(500);
    gotoxy(43,15);
    cout<<".";
    Sleep(500);
    gotoxy(44,15);
    cout<<".";
    Sleep(500);
    gotoxy(45,15);
    cout<<".";
    if(player1Score>player2Score){
        gotoxy(46,15);
        cout<<player1->username<<"!";

    }
    else if(player1Score<player2Score){
        gotoxy(46,15);
        cout<<player2->username<<"!";
    }
    else{
        gotoxy(46,15);
        cout<<"...empate!";
    }
    Sleep(2500);

    player1Score=0;
    player2Score=0;

    player1=0;
    player2=0;
}
void resetBonus(){
    auxNode *temp=specialSquares->header;
    while(temp!=0){
        temp->bonus=true;
        temp=temp->next;
    }
}
void endGame(){
    resetPlayers();
    tokenQueue->clean();
    randomFill();
    matrixBoard->clean(xLimit);
    resetBonus();
    erase();

}

//---------------------------GRAPHVIZ REPORTS-----------------------------//

string r1(){
    int cont=0;
    string concat="";
    concat += "digraph D {\n"
              "  rankdir=LR;";
    nodeDoubleLinked *temp=dictionary->header;
    int size=dictionary->size;
    for(int i=0;i<size;i++) { //--------------COMO ES DOBLE CIRCULAR, VER QUE NO SE REPITA EL HEADER
        concat += "N" + to_string(cont)+"[label=\"" + temp->word+"\"] \n";
        temp = temp->next;
        cont++;
    }
    for(int i=0;i<cont-1;i++){
        concat+="N"+to_string(i)+" -> "+"N"+to_string(i+1)+" \n";
    }
    for(int i=cont-1;i>0;i--){
        concat+="N"+to_string(i)+" -> "+"N"+to_string(i-1)+" \n";
    }
    concat+="N0 -> N"+to_string(cont-1)+" \n";
    concat+="N"+to_string(cont-1)+" -> N0 \n";
    concat+="}";
    return concat;
}
string r2(){
    int cont=0;
    string concat="";
    concat+="digraph D {\n"
            "\n"
            "  node [fontname=\"Arial\" shape=box];\n";
    nodeQueue *temp=tokenQueue->header;
    while(temp!=0) {
        string s(1,temp->letter->letter);
        concat += "N" + to_string(cont)+"[label=\"" + s + " x " + to_string(temp->letter->score) + "pts"+"\"] \n";
        temp = temp->next;
        cont++;
    }
    for(int i=0;i<cont-1;i++){
        concat+="N"+to_string(i)+" -> "+"N"+to_string(i+1)+" \n";
    }
    concat+="}";

return concat;
}
string fillR3(nodeBinaryTree *node){
    string concat="";
    concat += "\"" + to_string(node->user->ID);
    concat+= "\" [label=\""+node->user->username+"\"];\n";
    if (node->left != 0) {
        concat += fillR3(node->left) + "\""+to_string(node->user->ID) + "\" -> \""+to_string(node->left->user->ID) + "\";\n";
    }
    if (node->right != 0) {
        concat += fillR3(node->right) + "\"" +to_string(node->user->ID) + "\" -> \""+to_string(node->right->user->ID) + "\";\n";
    }
    return concat;
}
string r3(){

    string concat = "";

    concat += "digraph structs {\n";
    concat += fillR3(players->root);
    concat += " }";
    return concat;
}
auxList *fillR4(nodeBinaryTree *node,auxList *temp){
    auxList *list=temp;
    if(node!=0){
        auxNode *info = new auxNode(node->user->username);
        list->append(info);
       fillR4(node->left,list);
       fillR4(node->right,list);

    }
    return list;
}
string r4() {
    int cont=0;
    auxList *temp=new auxList();
    string concat="";
    concat += "digraph D {\n"
              "  rankdir=LR;";

    temp=fillR4(players->root,temp);
    auxNode *tempNode=temp->header;
    while(tempNode!=0){
        concat+="N"+to_string(cont)+"[label=\""+tempNode->username+"\"] \n";
        tempNode=tempNode->next;
        cont++;
    }
    for(int i=0;i<cont-1;i++){
        concat+="N"+to_string(i)+" -> "+"N"+to_string(i+1)+"\n";
    }
    concat += " }";
    return concat;
}
auxList *fillR5(nodeBinaryTree *node,auxList *temp){
    auxList *list=temp;
    if(node!=0){
        fillR5(node->left,list);
        auxNode *info = new auxNode(node->user->username);
        list->append(info);
        fillR5(node->right,list);
    }
    return list;
}
string r5() {
    int cont=0;
    auxList *temp=new auxList();
    string concat="";
    concat += "digraph D {\n"
              "  rankdir=LR;";

    temp=fillR5(players->root,temp);
    auxNode *tempNode=temp->header;
    while(tempNode!=0){
        concat+="N"+to_string(cont)+"[label=\""+tempNode->username+"\"] \n";
        tempNode=tempNode->next;
        cont++;
    }
    for(int i=0;i<cont-1;i++){
        concat+="N"+to_string(i)+" -> "+"N"+to_string(i+1)+"\n";
    }
    concat += " }";
    return concat;
}
auxList *fillR6(nodeBinaryTree *node,auxList *temp){
    auxList *list=temp;
    if(node!=0){
        fillR6(node->left,list);
        fillR6(node->right,list);
        auxNode *info = new auxNode(node->user->username);
        list->append(info);

    }
    return list;
}
string r6() {
    int cont=0;
    auxList *temp=new auxList();
    string concat="";
    concat += "digraph D {\n"
              "  rankdir=LR;";

    temp=fillR6(players->root,temp);
    auxNode *tempNode=temp->header;
    while(tempNode!=0){
        concat+="N"+to_string(cont)+"[label=\""+tempNode->username+"\"] \n";;
        tempNode=tempNode->next;
        cont++;
    }
    for(int i=0;i<cont-1;i++){
        concat+="N"+to_string(i)+" -> "+"N"+to_string(i+1)+"\n";
    }
    concat += " }";
    return concat;
}
string r7(int ID){
    string concat = "";
    nodeBinaryTree *aux=players->search(ID);
    if(aux!=0) {
        int cont = 0;
        concat += "digraph D {\n"
                  "  rankdir=LR;\n";
        concat += "S0[label=\"" + aux->user->username + "\",penwidth=0]\n";
        nodeLinkedList *temp = aux->user->scores->header;
        while (temp != 0) {
            concat += "N" + to_string(cont) + "[label=\"" + to_string(temp->score) + "\"] \n";
            temp = temp->next;
            cont++;
        }
        for (int i = 0; i < cont - 1; i++) {
            concat += "N" + to_string(i) + " -> " + "N" + to_string(i + 1);
        }
        concat += " }";
    }
    return concat;
}
void fillR8(nodeBinaryTree *node){
    if(node!=0){
        node->user->setTop();
        scoreboard->add(node->user->top,node->user->username);
        fillR8(node->left);
        fillR8(node->right);
    }

}
string r8(){
    scoreboard->clean();
    fillR8(players->root);
    int cont=0;
    string concat="";
    concat += "digraph D {\n"
              "  rankdir=LR;";
    nodeLinkedList *temp=scoreboard->header;
    while(temp!=0){
        concat+="N"+to_string(cont)+"[label=\""+temp->username+", "+to_string(temp->score)+" pts\"] \n";
        temp=temp->next;
        cont++;
    }
    for(int i=0;i<cont-1;i++){
        concat+="N"+to_string(i)+" -> "+"N"+to_string(i+1)+ "\n";
    }
    concat += " }";
    return concat;
}
string r10(){
    int cont=0;
    string concat="";
    concat += "digraph D {\n"
              "  rankdir=LR;";
    concat +="P0[label=\""+player1->username+"\",penwidth=0]\n";
    nodeDoubleLinked *primTemp=player1->tokens->header;
    while(primTemp!=0){
        string s(1,primTemp->letter->letter);
        concat+="N"+to_string(cont)+"[label=\""+s+"\"] \n";
        primTemp=primTemp->next;
        cont++;
    }

    for(int i=0;i<cont-1;i++){
        concat+="N"+to_string(i)+" -> "+"N"+to_string(i+1)+" \n";
    }
    for(int i=cont-1;i>0;i--){
        concat+="N"+to_string(i)+" -> "+"N"+to_string(i-1)+" \n";
    }
    cont=0;
    concat +="P1[label=\""+player2->username+"\",penwidth=0]\n";
    nodeDoubleLinked *secTemp=player2->tokens->header;
    while(secTemp!=0){
        string s(1,secTemp->letter->letter);
        concat+="S"+to_string(cont)+"[label=\""+s+"\"] \n";
        secTemp=secTemp->next;
        cont++;
    }
    for(int i=0;i<cont-1;i++) {
        concat += "S" + to_string(i)+" -> "+"S" + to_string(i + 1)+" \n";
    }
    for(int i=cont-1;i>0;i--){
        concat+="S"+to_string(i)+" -> "+"S"+to_string(i-1)+"\n";
    }
    concat+="}";
    return concat;
}

void showMatrix(){
    file.open("C:/Users/Isaac Maldonado/Desktop/save.dot",ios::out);
    file<<matrixBoard->showData();
    file.close();
    system("cd /D  C:\\Users\\Isaac Maldonado\\Desktop\\ && dot -Tpng save.dot -o save.png");
    system("cd /D  C:\\Users\\Isaac Maldonado\\Desktop\\ && start save.png ");
}

void graphvizReport(char select,int ID){
    string content="";
    switch(select){
        case '0':
            content=r1();
            break;
        case '1':
            content=r2();
            break;
        case '2':
            content=r3();
            break;
        case '3':
            content=r4();
            break;
        case '4':
            content=r5();
            break;
        case '5':
            content=r6();
            break;
        case '6':
            content=r7(ID);
            break;
        case '7':
            content=r8();
            break;
        case '8':
            content=matrixBoard->showData();
            break;
        case '9':
            content=r10();
            break;
    }
    if(content!=""){
        file.open("C:/Users/Isaac Maldonado/Desktop/save.dot",ios::out);
        file<<content;
        file.close();
        system("cd /D  C:\\Users\\Isaac Maldonado\\Desktop\\ && dot -Tpng save.dot -o save.png");
        system("cd /D  C:\\Users\\Isaac Maldonado\\Desktop\\ && start save.png ");

    }


}


/* lo que queda pendiente aca es
 *      completar al jugador 2
 *      hacer las validaciones de los nodos
 *      abrir archivos
 *      ESO TIENE QUE SALIR EN TRES DIAS!
 */

int main() {

    hideCursor();

    fillBag();
    randomFill();

    bool active = true;


    int x = 0;
    int acci=0;

    int xAligment=0;
    int yAligment=0;

    int xCout=0; //--------------------------------P1: xCout=15, P2: xCout=60
    int playerFill=0; //---------------------------Amount of tokens a player has to be refilled


    string name;
    string user="";
    string posConcat="";
    string checkWord=""; //----------------CONCATS WORD TYPED BY PLAYER

    token *tokenPlayer;


    string playerID;        //-------------Concats player ID to search to

    int current = 0;
    int currentPlayer=0;
    int playerCount=0;
    int currentTurn=0;
    int turnState=0;
    int reportState=0;

    int currentAux=0;

    bool alignment=false; //--------------Vertical=false, Horizontal=true
    bool posFlag=false;   //--------------Tells if user has already typed both x and y positions

    while (active) {
        char input;
        switch (current) {
            case 0:
                margins();
                mainMenu();
                input = getch();
                switch (input) {
                    case '1':
                        current = 1;
                        x=40;
                        gotoxy(40,20);
                        cout<<"Ingresa el nombre del archivo:";
                        break;
                    case '2':
                        if(activeFile){
                            current = 3;
                            x=16;
                            erase();
                            game();
                        }
                        else{
                            gotoxy(40,20);
                            cout<<"Por favor, carga un tablero para dar inicio :)";
                            Sleep(2500);
                            gotoxy(40,20);
                            cout<<"                                              ";
                        }


                        break;
                    case '3':
                        active = false;
                        break;
                }

                break;
            case 1:

                input=getch();
                acci=input;
                if (acci == 24) {
                    erase();
                    current = 0;;
                }
                else if(input=='\r'){
                    current=5;
                }
                else{
                    gotoxy(x,21);
                    cout<<input;
                    name+=input;
                    x++;
                }

                break;
            case 3:
                switch(currentPlayer){
                    case 0:
                        input =getch();
                        acci=input;
                        if (acci == 24) {
                            erase();
                            current = 0;;
                        }
                        else if(input=='1'){
                            erasePlayer();
                            gotoxy(7,12);
                            cout<<"Usuario: ";
                            currentPlayer=1;
                        }
                        else if(input=='2'){
                            if(players->getSize()){
                                erasePlayer();
                                gotoxy(7,12);
                                cout<<"Usuarios disponibles";
                                gotoxy(40,12);
                                cout<<"Jugador 1:";
                                gotoxy(60,12);
                                cout<<"Jugador 2:";
                                currentPlayer=2;
                                players->showPlayers();
                                yPos=13;
                            }
                            else {
                                erasePlayer();
                                gotoxy(7,12);
                                cout<<"Se necesitan al menos dos usuarios para iniciar";
                                Sleep(2000);
                                erasePlayer();
                                game();
                            }

                        }
                        break;
                    case 1:
                        input=getch();
                        acci=input;
                        if (acci == 24) {
                            erasePlayer();
                            game();
                            currentPlayer=0;
                            name="";
                            x=16;
                        }
                        else if(input=='\r'){
                            player *temp=new player(name);
                            if(players->add(temp)){
                                gotoxy(7,13);
                                cout<<"Nombre de usuario ya registrado, intentalo de nuevo!";
                            }
                            else{
                                gotoxy(7,13);
                                cout<<"Registro exitoso";
                            }
                            duplicated=false;
                            Sleep(1000);
                            erasePlayer();
                            game();
                            currentPlayer=0;

                            name="";
                            x=16;

                        }
                        else {
                            name += input;
                            gotoxy(x,12);
                            cout<<input;
                            x++;
                        }
                        break;
                    case 2:
                        input=getch();
                        acci=input;
                        if (acci == 24) {
                            erasePlayer();
                            game();
                            currentPlayer=0;
                            playerID="";
                            playerCount=0;

                        }
                        else if(input=='\r') {
                            stringstream parse(playerID);
                            int tempID = 0;
                            parse >> tempID;
                            nodeBinaryTree *aux = players->search(tempID);
                            if (aux != 0) {
                                player *tempNode = aux->user;
                                if (playerCount == 0) {
                                    player1 = tempNode;
                                    tempNode->tokens->clean();
                                    gotoxy(40, 13);
                                    cout << player1->username;
                                    playerCount++;
                                    playerID = "";
                                } else if (tempNode->ID!=player1->ID&& playerCount == 1) {
                                    tempNode->tokens->clean();
                                    player2 = tempNode;
                                    gotoxy(60, 13);
                                    cout << player2->username;
                                    playerCount = 0;
                                    playerID = "";
                                    currentPlayer = 3;
                                    currentTurn = rand() % 2;

                                    fillPlayer1();
                                    fillPlayer2();
                                    erase();


                                    gotoxy(25,7);
                                    cout<<player1Score;
                                    gotoxy(8,7);
                                    cout<<player1->username;

                                    gotoxy(77,7);
                                    cout<<player2Score;
                                    gotoxy(60,7);
                                    cout<<player2->username;
                                }
                                else{
                                    gotoxy(40,14);
                                    cout<<"ID incorrecto, intente de nuevo!";
                                    Sleep(2500);
                                    gotoxy(40,14);
                                    cout<<"                                 ";
                                    playerID="";
                                }
                            }
                            else{
                                gotoxy(40,14);
                                cout<<"ID incorrecto, intente de nuevo!";
                                Sleep(2500);
                                gotoxy(40,14);
                                cout<<"                                 ";
                                playerID="";
                            }

                        }
                        else if(acci>47&&acci<58){
                            playerID+=input;
                        }
                        break;

                        //-----------------------------------------------------------------------------------//
                        //---------------------------------------GAME----------------------------------------//
                        //-----------------------------------------------------------------------------------//
                    case 3:
                        switch (currentTurn){
                            case 0:
                                board();

                                xCout=15;
                                gotoxy(7,7);
                                cout<<">";
                                gotoxy(8,7);
                                cout<<player1->username;
                                gotoxy(25,7);
                                cout<<player1Score;

                                if(!tokenQueue->isEmpty()){                 //----CHECK IF TOKEN BAG IS EMPTY
                                    input=getch();
                                    acci=input;

                                    if(acci==24){
                                        endGame();

                                        current=0;
                                        currentPlayer=0;
                                        currentTurn=0;

                                    }
                                    else if(acci==18){
                                        erase();
                                        reports();
                                        currentTurn=4;
                                        currentAux=0;
                                    }
                                    else if(input=='1') {
                                        currentTurn = 2;                  //------------Board state

                                        clearPlayer1();

                                        gotoxy(8, 9);
                                        cout << "Direccion de la palabra: ";
                                        gotoxy(8, 10);
                                        cout << "1. Vertical";
                                        gotoxy(8, 11);
                                        cout << "2. Horizontal";

                                        turnState = 0;
                                    }
                                    else if(input=='2'){

                                        clearPlayer1();
                                        gotoxy(8,9);
                                        cout<<"Seleccione la letra";
                                        gotoxy(8,10);
                                        cout<<"que desea remplazar: ";
                                        player1->tokens->showTokens(8);
                                        currentTurn=2;
                                        turnState=3;
                                    }

                                }
                                else{
                                    endGame();

                                    current=0;
                                    currentPlayer=0;
                                    currentTurn=0;
                                }

                                break;
                            case 1:
                                board();

                                xCout=67;         //-------------------????

                                gotoxy(59,7);
                                cout<<">";
                                gotoxy(60,7);
                                cout<<player2->username;
                                gotoxy(77,7);
                                cout<<player2Score;

                                if(!tokenQueue->isEmpty()){
                                    input=getch();
                                    acci=input;
                                    if(acci==24) {
                                        endGame();

                                        current=0;
                                        currentPlayer=0;
                                        currentTurn=0;
                                    }
                                    else if(acci==18){
                                        erase();
                                        reports();
                                        currentTurn=4;
                                        currentAux=1;
                                    }
                                    else if(input=='1'){
                                        currentTurn=3;

                                        for (int i = 40; i <70 ; ++i) {
                                            gotoxy(i, 9);
                                            cout << " ";
                                            gotoxy(i, 10);;
                                            cout << " ";
                                        }

                                        clearPlayer2();
                                        gotoxy(59,9);
                                        cout<<"Direccion de la palabra: ";
                                        gotoxy(59, 10);
                                        cout << "1. Vertical";
                                        gotoxy(59, 11);
                                        cout << "2. Horizontal";

                                        turnState=0;
                                    }
                                    else if(input=='2'){
                                        clearPlayer2();
                                        gotoxy(59,9);
                                        cout<<"Seleccione la letra";
                                        gotoxy(59,10);
                                        cout<<"que desea remplazar: ";
                                        player2->tokens->showTokens(59);
                                        currentTurn=3;
                                        turnState=3;
                                    }


                                }
                                else{
                                    endGame();

                                    current=0;
                                    currentPlayer=0;
                                    currentTurn=0;
                                }

                                break;
                                //--------------PLAYER 1 BOARD--------------//
                            case 2:
                                switch(turnState){
                                    case 0:
                                       input=getch();
                                       if(input=='1'){
                                           gotoxy(7,10);
                                           cout<<">";
                                           alignment=false;
                                           gotoxy(8,12);
                                           cout<<"Coordenada inicial: ";
                                           turnState=1;
                                       }
                                       else if(input=='2'){
                                           gotoxy(7,11);
                                           cout<<">";
                                           alignment=true;
                                           gotoxy(8,12);
                                           cout<<"Coordenada inicial: ";
                                           turnState=1;
                                       }

                                        break;
                                    case 1:
                                        input=getch();
                                        acci=input;
                                        if(acci>47&&acci<58||input=='\r'){  //-----------EXPECTS START POSITION TO BE A NUMBER OR NEW LINE
                                            if(!posFlag) {                  //---------------------X POSITION TYPED, posFlag=TRUE
                                                if(input=='\r'){

                                                    stringstream parse(posConcat);
                                                    xAligment=0;
                                                    parse>>xAligment;

                                                    posConcat+=",";

                                                    gotoxy(28, 12);
                                                    cout << posConcat;

                                                    posFlag=true;
                                                    posConcat="";
                                                }
                                                else{
                                                    posConcat+=input;
                                                }


                                            }
                                            else{                          //---------------------Y POSIION EXPECTED
                                                if(input=='\r'){
                                                    stringstream parse(posConcat);
                                                    yAligment=0;
                                                    parse>>yAligment;

                                                    gotoxy(31,12);
                                                    cout<<posConcat;


                                                    posFlag=false;
                                                    posConcat="";

                                                    if(yAligment>yLimit||xAligment>xLimit||yAligment==0||xAligment==0){ //---------------OUT OF BOUNDS POSITION
                                                        gotoxy(8, 13);
                                                        cout << "Posicion fuera del limite ";
                                                        Sleep(2000);
                                                        gotoxy(8, 13);
                                                        cout << "                           ";


                                                        turnState=0;
                                                        currentTurn=1;              //----------P1=0, P2=1

                                                        gotoxy(7,7);
                                                        cout<<" ";
                                                        gotoxy(25,7);
                                                        cout<<player1Score;

                                                        clearPlayer1();
                                                    }
                                                    else {

                                                        nearbyCont=0;
                                                        int x0 = xAligment;
                                                        int y0 = yAligment;
                                                        if(matrixBoard->siders->isEmpty()){
                                                            nearbyCont++;
                                                        }
                                                        else{
                                                            nearby(x0,y0,true,true,true,true);
                                                        }


                                                        turnState = 2;             //------------USER TOKEN INPUT EXPECTED
                                                        gotoxy(8, 13);
                                                        cout << "Despliega tus fichas: ";
                                                        gotoxy(8, 14);
                                                        cout << "(Presiona ENTER para validar)";;

                                                        player1->tokens->showTokens(8);
                                                    }
                                                }
                                                else{
                                                    posConcat+=input;
                                                }


                                            }


                                        }
                                        break;
                                    case 2:
                                        input=getch();
                                        acci=input;
                                        if(acci>64&&acci<91){                   //--------------------------EXPECTS A CAPITAL LETTER
                                            tokenPlayer=player1->tokens->searchToken(input);
                                            if(tokenPlayer!=0){
                                                bool check=true;
                                                    if(xAligment<=xLimit&&yAligment<=yLimit){           //-----POSITION FILTER FOR WHILE LOOP
                                                        while(matrixBoard->searchPosition(xAligment,yAligment)){  //----------ITERATES TILL IT FINDS AN EMPTY SPACE
                                                            nearbyCont++;
                                                            if(alignment){
                                                                if(xAligment<xLimit) {
                                                                    xAligment++;
                                                                }
                                                                else{
                                                                    check=false;        //------------BUT...IF IT REACHES THE LIMIT, NOTHING CAN BE DONE :(
                                                                    break;
                                                                }
                                                            }
                                                            else{
                                                                if(yAligment<yLimit) {
                                                                    yAligment++;
                                                                }
                                                                else{
                                                                    check=false;        //------------BUT...IF IT REACHES THE LIMIT, NOTHING CAN BE DONE :(
                                                                    break;
                                                                }
                                                            }
                                                        }
                                                    }
                                                    else{
                                                        check=false;
                                                    }

                                                if(check){

                                                    auxNode *bonus=specialSquares->searchSquare(xAligment,yAligment);
                                                    if(bonus!=0){
                                                       if(bonus->bonus==2){
                                                           matrixBoard->add(tokenPlayer,xAligment,yAligment,"gray");
                                                       }
                                                       else{
                                                           matrixBoard->add(tokenPlayer,xAligment,yAligment,"darkolivegreen1");
                                                       }
                                                    }
                                                    else{
                                                        matrixBoard->add(tokenPlayer,xAligment,yAligment,"white");
                                                    }

                                                    nodeSider *aux = matrixBoard->siders->search(yAligment);            //----ADYACENT NODE VALIDATION
                                                    auxList *tempValidate=aux->rows->validAdjacent(xAligment,yAligment,!alignment,false);
                                                    if(tempValidate->size>1){
                                                        listNode *word=new listNode(tempValidate);
                                                        validWords->append(word);

                                                        nearbyCont++;
                                                    }



                                                    gotoxy(xCout,18);
                                                    cout<<input;
                                                    xCout++;

                                                    player1->tokens->deleteCharAt(input);       //-----ADD AS WELL THE TOKENS I DELETE IN CASE WORD IS NOT VALID
                                                    player1->tokens->showTokens(8);
                                                    playerFill++;

                                                    //---------------Y POS PARA MAS PLACER..............
                                                    showMatrix();


                                                    if(alignment){
                                                        xAligment++;
                                                    }else {
                                                        yAligment++;
                                                    }
                                                }
                                                else{

                                                    refillPlayer(player1);
                                                    deleteMatrix();
                                                    validationPositions->clean();
                                                    validWords->clean();


                                                    gotoxy(8, 23);
                                                    cout << "Posicion fuera del limite ";
                                                    Sleep(2000);
                                                    gotoxy(8, 23);
                                                    cout << "                           ";

                                                    turnState=0;
                                                    currentTurn=1;

                                                    gotoxy(7,7);
                                                    cout<<" ";
                                                    gotoxy(25,7);
                                                    cout<<player1Score;

                                                    clearPlayer1();
                                                }
                                            }
                                        }
                                        if(input=='\r'){
                                            turnState=0;
                                            currentTurn=1;
                                            int x0=xAligment;
                                            int y0=yAligment;
                                            if(alignment){
                                                x0--;
                                                nearby(x0,y0,true,true,false,true);
                                            }else {
                                                y0--;
                                                nearby(x0,y0,false,true,true,true);
                                            }

                                            nodeSider *temp = matrixBoard->siders->search(y0);
                                            validationPositions = temp->rows->validAdjacent(x0,y0,alignment,true);
                                            listNode *final=new listNode(validationPositions);
                                            validWords->append(final);


                                            if(iterateWords()&&nearbyCont!=0){                   //-----------CHECK IF WORD IS IN THE DICTIONARY. IF NOT REMOVE NODES AND RETURN TOKENS
                                                setScore(true);
                                                for (int i = 0; i <playerFill; ++i) {
                                                    if (!tokenQueue->isEmpty()) {
                                                        player1->tokens->add(tokenQueue->dequeue()->letter);
                                                    }
                                                }
                                            }
                                            else{
                                                gotoxy(50, 18);
                                                cout << "Palabra y/o adyacencia no valida";
                                                Sleep(2000);
                                                gotoxy(50, 18);
                                                cout << "                                ";

                                                refillPlayer(player1);
                                                deleteMatrix();
                                            }
                                            validWords->clean();
                                            validationPositions->clean();

                                            gotoxy(7,7);
                                            cout<<" ";
                                            gotoxy(25,7);
                                            cout<<player1Score;
                                            clearPlayer1();


                                            playerFill=0;
                                        }
                                        break;

                                    case 3:
                                        input=getch();
                                        acci=input;
                                        if(acci==24){
                                            turnState=0;
                                            currentTurn=0;
                                            clearPlayer1();

                                        }
                                        else if(acci>64&&acci<91){

                                            tokenPlayer=player1->tokens->searchToken(input);
                                            if(tokenPlayer!=0) {
                                                player1->tokens->deleteCharAt(input);
                                                player1->tokens->add(tokenQueue->dequeue()->letter);
                                                tokenQueue->enqueue(tokenPlayer);
                                                player1->tokens->showTokens(8);

                                                turnState=0;
                                                currentTurn=1;

                                                Sleep(2000);

                                                clearPlayer1();

                                                gotoxy(7,7);
                                                cout<<" ";

                                            }
                                        }
                                        break;
                                }

                                break;
                                //--------------PLAYER 2 BOARD--------------//
                            case 3:
                                //-------------------INICIO COPIA-------------------//



                                switch(turnState){
                                    case 0:
                                        input=getch();
                                        if(input=='1'){
                                            gotoxy(58,10);
                                            cout<<">";
                                            alignment=false;
                                            gotoxy(59,12);
                                            cout<<"Coordenada inicial: ";
                                            turnState=1;
                                        }
                                        else if(input=='2'){
                                            gotoxy(58,11);
                                            cout<<">";
                                            alignment=true;
                                            gotoxy(59,12);
                                            cout<<"Coordenada inicial: ";
                                            turnState=1;
                                        }

                                        break;
                                    case 1:
                                        input=getch();
                                        acci=input;
                                        if(acci>47&&acci<58||input=='\r'){  //-----------EXPECTS START POSITION TO BE A NUMBER OR NEW LINE
                                            if(!posFlag) {                  //---------------------X POSITION TYPED, posFlag=TRUE
                                                if(input=='\r'){

                                                    stringstream parse(posConcat);
                                                    xAligment=0;
                                                    parse>>xAligment;

                                                    posConcat+=",";

                                                    gotoxy(79, 12);
                                                    cout << posConcat;

                                                    posFlag=true;
                                                    posConcat="";
                                                }
                                                else{
                                                    posConcat+=input;
                                                }


                                            }
                                            else{                          //---------------------Y POSITION EXPECTED
                                                if(input=='\r'){
                                                    stringstream parse(posConcat);
                                                    yAligment=0;
                                                    parse>>yAligment;

                                                    gotoxy(82,12);
                                                    cout<<posConcat;


                                                    posFlag=false;
                                                    posConcat="";

                                                    if(yAligment>yLimit||xAligment>xLimit||yAligment==0||xAligment==0){ //---------------OUT OF BOUNDS POSITION
                                                        gotoxy(59, 13);
                                                        cout << "Posicion fuera del limite ";
                                                        Sleep(2000);
                                                        gotoxy(59, 13);
                                                        cout << "                           ";


                                                        turnState=0;
                                                        currentTurn=0;              //----------P1=0, P2=1

                                                        gotoxy(59,7);
                                                        cout<<" ";
                                                        gotoxy(77,7);
                                                        cout<<player2Score;

                                                        clearPlayer2();
                                                    }
                                                    else {
                                                        nearbyCont=0;
                                                        int x0 = xAligment;
                                                        int y0 = yAligment;
                                                        if(matrixBoard->siders->isEmpty()){
                                                            nearbyCont++;
                                                        }
                                                        else{
                                                            nearby(x0,y0,true,true,true,true);
                                                        }


                                                        turnState = 2;             //------------USER TOKEN INPUT EXPECTED
                                                        gotoxy(59, 13);
                                                        cout << "Despliega tus fichas: ";
                                                        gotoxy(59, 14);
                                                        cout << "(Presiona ENTER para validar)";;

                                                        player2->tokens->showTokens(59);

                                                    }
                                                }
                                                else{
                                                    posConcat+=input;
                                                }


                                            }


                                        }
                                        break;
                                    case 2:
                                        input=getch();
                                        acci=input;
                                        if(acci>64&&acci<91){                   //--------------------------EXPECTS A CAPITAL LETTER
                                            tokenPlayer=player2->tokens->searchToken(input);
                                            if(tokenPlayer!=0){
                                                bool check=true;
                                                if(xAligment<=xLimit&&yAligment<=yLimit){           //-----POSITION FILTER FOR WHILE LOOP
                                                    while(matrixBoard->searchPosition(xAligment,yAligment)){  //----------ITERATES TILL IT FINDS AN EMPTY SPACE

                                                        nearbyCont++;
                                                        if(alignment){
                                                            if(xAligment<xLimit) {
                                                                xAligment++;
                                                            }
                                                            else{
                                                                check=false;        //------------BUT...IF IT REACHES THE LIMIT, NOTHING CAN BE DONE :(
                                                                break;
                                                            }
                                                        }
                                                        else{
                                                            if(yAligment<yLimit) {
                                                                yAligment++;
                                                            }
                                                            else{
                                                                check=false;        //------------BUT...IF IT REACHES THE LIMIT, NOTHING CAN BE DONE :(
                                                                break;
                                                            }
                                                        }
                                                    }
                                                }
                                                else{
                                                    check=false;
                                                }

                                                if(check){

                                                    auxNode *bonus=specialSquares->searchSquare(xAligment,yAligment);
                                                    if(bonus!=0){
                                                        if(bonus->bonus==2){
                                                            matrixBoard->add(tokenPlayer,xAligment,yAligment,"gray");
                                                        }
                                                        else{
                                                            matrixBoard->add(tokenPlayer,xAligment,yAligment,"darkolivegreen1");
                                                        }
                                                    }
                                                    else{
                                                        matrixBoard->add(tokenPlayer,xAligment,yAligment,"white");
                                                    }

                                                    nodeSider *aux = matrixBoard->siders->search(yAligment);            //----ADYACENT NODE VALIDATION
                                                    auxList *tempValidate=aux->rows->validAdjacent(xAligment,yAligment,!alignment,false);
                                                    if(tempValidate->size>1){
                                                        listNode *word=new listNode(tempValidate);
                                                        validWords->append(word);

                                                        nearbyCont++;
                                                    }

                                                    gotoxy(xCout,18);
                                                    cout<<input;
                                                    xCout++;

                                                    player2->tokens->deleteCharAt(input);       //-----ADD AS WELL THE TOKENS I DELETE IN CASE WORD IS NOT VALID
                                                    player2->tokens->showTokens(59);
                                                    playerFill++;

                                                    //---------------Y POS PARA MAS PLACER..............
                                                    showMatrix();


                                                    if(alignment){
                                                        xAligment++;
                                                    }else {
                                                        yAligment++;
                                                    }
                                                }
                                                else{

                                                    refillPlayer(player2);
                                                    deleteMatrix();
                                                    validationPositions->clean();
                                                    validWords->clean();


                                                    gotoxy(59, 23);
                                                    cout << "Posicion fuera del limite ";
                                                    Sleep(2000);
                                                    gotoxy(59, 23);
                                                    cout << "                           ";

                                                    turnState=0;
                                                    currentTurn=0;

                                                    gotoxy(59,7);
                                                    cout<<" ";
                                                    gotoxy(77,7);
                                                    cout<<player2Score;

                                                    clearPlayer2();
                                                }
                                            }
                                        }
                                        if(input=='\r'){
                                            turnState=0;
                                            currentTurn=0;
                                            int x0=xAligment;
                                            int y0=yAligment;

                                            if(alignment){
                                                x0--;
                                                nearby(x0,y0,true,true,false,true);
                                            }else {
                                                y0--;
                                                nearby(x0,y0,false,true,true,true);
                                            }

                                            nodeSider *temp = matrixBoard->siders->search(y0);
                                            validationPositions = temp->rows->validAdjacent(x0,y0,alignment,true);
                                            listNode *final=new listNode(validationPositions);
                                            validWords->append(final);

                                            if(iterateWords()&&nearbyCont!=0){                   //-----------CHECK IF WORD IS IN THE DICTIONARY. IF NOT REMOVE NODES AND RETURN TOKENS
                                                setScore(false);
                                                for (int i = 0; i <playerFill; ++i) {
                                                    if (!tokenQueue->isEmpty()) {
                                                        player2->tokens->add(tokenQueue->dequeue()->letter);
                                                    }
                                                }
                                            }
                                            else{

                                                gotoxy(12, 18);
                                                cout << "Palabra y/o adyacencia no valida";
                                                Sleep(2000);
                                                gotoxy(12, 18);
                                                cout << "                                ";


                                                refillPlayer(player2);
                                                deleteMatrix();
                                            }
                                            validWords->clean();
                                            validationPositions->clean();

                                            gotoxy(59,7);
                                            cout<<" ";
                                            gotoxy(77,7);
                                            cout<<player2Score;
                                            clearPlayer2();


                                            playerFill=0;
                                        }
                                        break;
                                    case 3:
                                        input=getch();
                                        acci=input;
                                        if(acci==24){
                                            turnState=0;
                                            currentTurn=1;
                                            clearPlayer2();

                                        }
                                        else if(acci>64&&acci<91){

                                            tokenPlayer=player2->tokens->searchToken(input);
                                            if(tokenPlayer!=0) {
                                                player2->tokens->deleteCharAt(input);
                                                player2->tokens->add(tokenQueue->dequeue()->letter);
                                                tokenQueue->enqueue(tokenPlayer);
                                                player2->tokens->showTokens(59);

                                                turnState=0;
                                                currentTurn=0;

                                                Sleep(2000);

                                                clearPlayer2();

                                                gotoxy(59,7);
                                                cout<<" ";

                                            }
                                        }
                                        break;
                                }


                                //--------------------FIN COPIA----------------------//
                                break;

                            //-----------------------REPORT MENU------------//
                            case 4:
                                switch(reportState){
                                    case 0:
                                        input=getch();
                                        acci=input;
                                        if (acci == 24) {
                                            erase();
                                            currentTurn = currentAux;
                                            reportState=0;
                                            board();
                                            gotoxy(25,7);
                                            cout<<player1Score;
                                            gotoxy(8,7);
                                            cout<<player1->username;

                                            gotoxy(77,7);
                                            cout<<player2Score;
                                            gotoxy(60,7);
                                            cout<<player2->username;
                                        }
                                        else if(acci>47&&acci<58){
                                            if(input=='6') {
                                                reportState = 1;
                                                gotoxy(45,14);
                                                cout<<"Ingrese el ID del jugador:";
                                            }
                                            else{
                                                graphvizReport(input,0);
                                            }
                                        }
                                        break;
                                    case 1:
                                        input=getch();
                                        acci=input;
                                        if(acci>47&&acci<58) {
                                            playerID=+input;
                                        }
                                        else if(input=='\r'){
                                            stringstream parse(playerID);
                                            int tempID=0;
                                            parse>>tempID;
                                            graphvizReport('6',tempID);
                                            playerID="";
                                            Sleep(1000);
                                            erase();
                                            reports();
                                            reportState=0;
                                        }
                                        break;
                                }

                                break;


                        }
                        break;

                }

                break;

            case 5:
                readFile(name);
                Sleep(1000);
                erase();
                current=0;
                name="";
                break;

        }
    }

    return 0;
}