#include<iostream>
#include<curses.h>
#include<thread>
#include<chrono>
// #include<unistd.h>  

int main()
{
  initscr();
  endwin();
//   keypad(stdscr, TRUE);
// //   noecho();
//   cbreak();
//   start_color();
//   nodelay(stdscr, TRUE);

//   box ( stdscr, 0, 0 );
//   int i = 1;
//   int x,y;
//   char c;

//   while ( i++ )
//   {
// 	std::this_thread::sleep_for(std::chrono::seconds(1));
// 	getbegyx( stdscr, y,x );
// 	mvprintw( y + 1, x + 1 ,"%d", i );
//     refresh();

// 	if ( ( c = getch() ) != ERR )
// 	{
// 	  switch ( c )
// 	  {
// 	    case ( '1' ):
// 		{
// 		  WINDOW * win = newwin ( 10, 10, 2, 5 );
// 		  box( win, 0, 0 );
//           mvwprintw( win, 1, 1 ,"Attack" );
// 		  wrefresh( win );
// 		//   endwin_sp(win);
// 		  break;

// 		};
// 		case ( '2' ):
// 		{
// 		  WINDOW * win = newwin ( 10, 10, 2, 5 );
// 		  box( win, 0, 0 );
//           mvwprintw( win, 1, 1 ,"Talents" );
// 		  wrefresh( win );
// 		  wstandend(win);
// 		  break;
// 		}
// 	  }
// 	}
// 	else
// 	{
// 	  clear();
// 	  box ( stdscr, 0, 0 );
	
// 	}

//   }
// int xPar, yPar;

	// WINDOW * win = newwin ( 10, 30, 0, 0 );
	// WINDOW * win1 = newwin ( 5, 15, 3, 3 );
	// refresh();

	// // box ( stdscr, 0, 0 );
	// // box ( win, (int)'+', (int)'#' );
	// wborder(win, (int)'|', (int)'|', (int)'-', (int)'-',
	// 		     (int)'*', (int)'*', (int)'*', (int)'*' );
	// wborder(win1, (int)'|', (int)'|', (int)'-', (int)'-',
	// 		     (int)'*', (int)'*', (int)'*', (int)'*' );
	// wrefresh( win );
	// wrefresh( win1 );

	// int x = 10, y = 10;

	// move ( y, x );
	// wattron( win, A_REVERSE );
	// mvwprintw( win, 1, 1, "Hello world!" );
	// wattroff( win, A_REVERSE );
	// wrefresh(win);

	// move ( y, x );
	// wattron( win1, A_REVERSE );
	// mvwprintw( win1, 1, 1, "Hello world!" );
	// wattroff( win1, A_REVERSE );
	// wrefresh(win1);

    // init_pair( 1, COLOR_CYAN, COLOR_GREEN );
	// move ( y, x );
	// wattron( win1, COLOR_PAIR ( 1 ) );
	// mvwprintw( win1, 2, 1, "I am small w" );
	// wattroff( win1, COLOR_PAIR ( 1 ) );
	// wrefresh(win1);

	// // getyx( win1, yPar, xPar );
	// getmaxyx( win, yPar, xPar );
	// wprintw ( stdscr, "%d %d", yPar, xPar);

	// char c = getch();

	// move ( 0, 0 );

	// printw( "%c", c  );

    // mvprintw( 0, 10, "|" );
    // mvprintw( 1, 10, "|" );
	// // refresh();

	// getch();

	// clear();

	// getch();
	// endwin();
}