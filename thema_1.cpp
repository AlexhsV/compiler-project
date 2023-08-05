#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <list>
#include <iterator>
#include <algorithm>

/*
<Z>::=(<K>)
<K>::=<G><M>
<G>::=ν|<Z>
<M>::=-<K>|+<K>|ε
*/

using namespace std;

void produce_Z();
void produce_K();
void produce_G();
void produce_M();
void showlist(list<char> g);
list<char> production;

int main()
{
  srand((unsigned) clock());  /* srand initialize random number generator while time() returns current calendar time
                                 in order to determine the range from which numbers will be chosen */
                              /* with unsigned we specify that the data type (time) is a non-negative number */

  produce_Z();  //start char is Z

  printf("\nproduced string: ");
  showlist(production);
  return 0;
}

/* rule 1 */
void produce_Z()
{
  printf("(, using production <Z>::=(<K>)\n");
  production.push_back('(');
  produce_K();
  printf("), using production <K>::=<G><M>\n");
  production.push_back(')');
}

/* rule 2 */
void produce_K()
{
  produce_G();
  printf("using production <G>::=ν|<Z>\n");
  produce_M();
  printf("using production <M>::=-<K>|+<K>|ε\n");
}

/* rule 3 */
void produce_G()
{
    int random=rand()%2;  /* division with 2 produces a remainder of 0 or 1 (50% possibility - 2 equal alternatives) */
    if (random==0) {
        printf("v, using production <K>::=<G><M>\n");
        production.push_back('v');
    }
    else
        produce_Z();
        printf("using production <Z>::=(<K>)\n");
}

/* rule 4 */
void produce_M()
{
    int random=rand()%5;  /* division with 5 produces a remainder of 0 or 1 or 2 or 3 or 4 (20% possibility for each number - 3 unequal alternatives) */
    if (random==0) {
        printf("-, using production <M>::=-<K>|+<K>|ε\n");
        production.push_back('-');
        produce_K();
        printf("using production <K>::=<G><M>\n");
    }
    else if (random==1) {
        printf("+, using production <M>::=-<K>|+<K>|ε\n");
        production.push_back('+');
        produce_K();
        printf("using production <K>::=<G><M>\n");
    }
    else { //2,3,4  (ε has higher possibility to occur so that the program terminates at some point)
        //ε (empty)
    }
}

void showlist(list<char> g)
{
    list<char>::iterator it;
    for (it = g.begin(); it != g.end(); ++it)
        printf("%c",*it);
}
