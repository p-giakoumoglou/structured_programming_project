#include"board.h"
#include<stdlib.h>
#include<stdio.h>
#include"player.h"
#include<math.h>




int CheckEmpty(const Board* b){
    for(int i = 0; i< b->columns; i++){
        if(b->board[b->rows-1][i] != 0){
            return 1;
        }
    }

    return 0;
}

Board* createMirror(const Board* b){//creates a mirror board
    Board *mirror;
	mirror = (Board*) malloc(sizeof(Board));
	InitBoard(mirror, b->rows, b->columns);
    for(int i=0; i<b->rows; i++){
        for(int j=0; j<b->columns; j++){
            mirror->board[i][j]=b->board[i][j];
        }
    }
    return mirror;
}

int scoring(int me, int enemy, Board* mirror){
    int scoremax_me, scoremax_enemy;
    int score;
    int tempdraw=CountScore(mirror, me, &scoremax_me)-CountScore(mirror, enemy, &scoremax_enemy);
    int temp=scoremax_me-scoremax_enemy;
    if(temp<0){
            score=-6;
    }
    else if(temp>0){
            score=2;
    }
    else{
            if(tempdraw>=0){
                score=2;//5=no_of_for-1
            }
            else{
                score=-6;
                }
        }
    return score;
}

int sum_of_row(int **table, int row, int columns, int me, int enemy, Board* mirror){
    int sum=0;
    int counter=0;
    for(int i=0; i<columns; i++){
        if(table[row][i]!=-9999){
        sum+=table[row][i];
        }
        else{
            counter++;
        }
    }
    if(counter<columns){
        return sum;
    }
    else {
        return scoring(me, enemy, mirror);
    }
}



extern int player_10054(const Board* b){
    static int a;
    int me;
    int enemy;
    if(a==0){
        if(CheckEmpty(b)==0){
            me=1;
            enemy=2;
        }
        else{
            me=2;
            enemy=1;
        }
        a++;
    }

    int move;
    int no_of_for;
    no_of_for = 6; //oracle

	Board *mirror;
    mirror=createMirror(b);

	int **table;
	table=(int **)malloc((no_of_for)*sizeof(int));
	for(int i=0; i<no_of_for; i++){
        table[i]=(int *)malloc(b->columns*sizeof(int));
	}
	for(int i=0; i<no_of_for; i++){
        for(int j=0; j<b->columns; j++){
            table[i][j]=-9999;
        }
	}

	for(int player1_1 = 0; player1_1< b->columns; player1_1++){
        move=player1_1;
        Board *mirror1;
        mirror1=createMirror(mirror);
        if(CheckMove(mirror, move))continue;
        InsertInto(mirror, move, me);


		for(int player2_1 = 0; player2_1<b->columns; player2_1++){
            move=player2_1;
            Board *mirror2;
            mirror2=createMirror(mirror);
            if(CheckMove(mirror, move)) continue;
            InsertInto(mirror, move, enemy);


			for(int player1_2 = 0; player1_2< b->columns; player1_2++){
                move=player1_2;
                Board *mirror3;
                mirror3=createMirror(mirror);
				if(CheckMove(mirror, move)) continue;
				InsertInto(mirror, move, me);


				for(int player2_2 = 0; player2_2<b->columns; player2_2++){
                    move=player2_2;
                    Board *mirror4;
                    mirror4=createMirror(mirror);
                    if(CheckMove(mirror, move)) continue;
                    InsertInto(mirror, move, enemy);


                        for(int player1_3 = 0; player1_3< b->columns; player1_3++){

                            move=player1_3;
                            Board *mirror5;
                            mirror5=createMirror(mirror);
                            if(CheckMove(mirror, move)) continue;
                            InsertInto(mirror, move, me);

                            for(int player2_3 = 0; player2_3<b->columns; player2_3++){

                                move=player2_3;
                                Board *mirror6;
                                mirror6=createMirror(mirror);
                                if(CheckMove(mirror, move)) continue;
                                InsertInto(mirror, move, enemy);
                                //int temp5, tempdraw5;
                                table[5][player2_3]=scoring(me, enemy, mirror);
                                DestroyBoard(mirror);
                                mirror=createMirror(mirror6);

                            }
                            //int temp4, tempdraw4;
                            table[4][player1_3]=sum_of_row(table, 5, b->columns, me, enemy, mirror);
                            DestroyBoard(mirror);
                            mirror=createMirror(mirror5);

                        }
                    //int temp3, tempdraw3;
                    table[3][player2_2]=sum_of_row(table, 4, b->columns, me, enemy, mirror);
                    DestroyBoard(mirror);
                    mirror=createMirror(mirror4);

				}
				//int temp2, tempdraw2;
				table[2][player1_2]=sum_of_row(table, 3, b->columns, me, enemy, mirror);
				DestroyBoard(mirror);
                mirror=createMirror(mirror3);

			}
			//int temp1, tempdraw1;
			table[1][player2_1]=sum_of_row(table, 2, b->columns, me, enemy, mirror);
			DestroyBoard(mirror);
            mirror=createMirror(mirror2);

		}
		//int temp0, tempdraw0;
		table[0][player1_1]=sum_of_row(table, 1, b->columns, me, enemy, mirror);
		DestroyBoard(mirror);
        mirror=createMirror(mirror1);

	}
    int max=table[0][0];
    int best_move=0;
    for(int i=0; i<b->columns; i++){
        printf("\n------(%d)------\n", table[0][i]);
        if(max<table[0][i]){
            max=table[0][i];
            best_move=i;
        }
    }




    DestroyBoard(mirror);

	return best_move;
}


