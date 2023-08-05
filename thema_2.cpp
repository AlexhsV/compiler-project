#include <iostream>
#include <stack>
#include <string>
#include <algorithm>
#include <iterator>
#include <list>

using namespace std;

// function emulating the predictive parsing table
// maps the non-terminal-terminal combinations to the correct grammar production
string return_substitute_symbol(char stack_char, char lookahead_char);
void showlist(list<string> g);

/* parser inside main() */
int main(){
    
  list<string> polish;
  /* get the input from user */
  string input;
  cout << "please enter the string: \n";
  cin >> input;
  
  /* get first lookahead symbol */
  char input_char=input[0];
  
  /* at the end it will contain the production */
  string symbol;
  
  /* declare & initialize stack */
  stack<char> symbols_stack;
  symbols_stack.push('$');
  symbols_stack.push('G');
   
  /* initialize stack top */
  char stack_top=symbols_stack.top();

try{
    /* while there are still symbols to be recognized */
    while (stack_top!='$'){
      /* if stack top matches the next lookup (a) pop the stack and go to the next symbol */
      if(stack_top==input_char){
        symbols_stack.pop();
        input.erase(input.begin());
        input_char=input[0];
      }
      /* if X (stack top) is non-terminal the string does not match */
      else if(stack_top=='a' || stack_top=='b' || stack_top=='*' || stack_top=='-' || stack_top=='(' || stack_top==')' || stack_top=='+')
        throw 3;
      /* pop the stack if we have ε */
      else if(stack_top=='e')
        symbols_stack.pop();
      /* get the following production if it exists, else the string cannot be recognized */
      else {
        symbol=return_substitute_symbol(stack_top, input_char);
	    cout<<"production: "<<stack_top<<"-->"<<symbol<<"\n";
	    polish.push_back(symbol);
	    symbols_stack.pop();
        // push the production symbols in the stack reversed
	    reverse(symbol.begin(), symbol.end());
	    for(int i=0; i<symbol.length(); i++)
          symbols_stack.push(symbol[i]);
        }
      // new stack top
      stack_top = symbols_stack.top();
    }
}
  catch(int n){
    if (n==1)
        cout << "an entry showed and doesn't belong in the ppt (first wrong input char = "<<input_char<<").\n";
    else if(n==2)
        cout << "an entry showed and doesn't belong in the ppt (first wrong input X = "<<stack_top<<").\n";
    else if(n==3)
        cout << "cannot recognize entered character because input string is unrecognizable (char = "<<input_char<<").\n";
  }
  cout<<"\nstring recognized\n";
  cout<<"\npolish notation of the syntx tree: "<<endl;
  showlist(polish);
  return 0;
}

string return_substitute_symbol(char stack_char, char lookahead_char){
    
  string substitute_char;
  
  if(stack_char=='G'){
      if(lookahead_char == '(') 
        substitute_char = "(M)";
      else throw 1; 
  }
  else if(stack_char=='M'){
      if(lookahead_char == 'a' || lookahead_char == 'b' || lookahead_char == '(')
        substitute_char = "YZ";
      else throw 1; 
  }
  else if (stack_char=='Y'){
      if(lookahead_char == 'a') 
        substitute_char = "a";
      else if (lookahead_char == 'b') 
        substitute_char = "b";
      else if (lookahead_char == '(')
        substitute_char = "G";
      else throw 1; 
  }
  else if (stack_char=='Z'){
      if(lookahead_char == '*') 
        substitute_char = "*M";
      else if (lookahead_char == '-') 
        substitute_char = "-M";
      else if (lookahead_char == '+')
        substitute_char = "+M";
      else if (lookahead_char == ')')
        substitute_char = "e";
      else throw 1; 
  }
  else throw 2;
  return substitute_char;
}

void showlist(list<string> g)
{
    list<string>::iterator it;
    for (it = g.begin(); it != g.end(); ++it)
        cout << '\t' << *it << ' ';
}


