//Lauren Crowthe lcrowthe
//Steven Morad smorad

import java.util.Scanner;
class jprn{
  static final int empty = -1;
  static int top = empty;
  static double[] stack = new double[16];
  static String next;
  
  public static void main(String[] args){
    readInput(args);
  }
  
  static void readInput(String[] args){
    Scanner sc = new Scanner(System.in);
    while(sc.hasNext()){
      try{
        next = sc.next();
        if(next.startsWith("#")){
          sc.nextLine();
        } 
        if (top<stack.length){
          push(Double.parseDouble(next));
        }
        else{
          System.out.printf("Stack overflow, current number discarded");
        }
      } catch(NumberFormatException e){
        if(next.length()!=1){
          System.out.printf("Invalid string: " + next);
        }
        char operator = next.charAt(0);
        double result;
        switch(operator){
          case '+':result = pop() + pop();
          push(result);
          break;
          case '-':result = -pop() + pop();
          push(result);
          break;
          case '*':result = pop() * pop();
          push(result); 
          break;
          case '/':result = 1/pop() * pop() ; 
          push(result); 
          break;
          case ';': printStack();
          break;    
          case '~': clearStack();
          break;
          default:
            System.out.printf("Invalid operator: " + next);
        }
      }
    }
  }
  static void printStack(){
    for (int i = 0; i <=top; i++){
      System.out.printf("%22.15g\n", stack[i]);
    }
  }
  
  static void clearStack(){
    for(double d: stack){
      d=0;
    }
    top = -1;
  }
  
  static double pop(){
    try{
      double temp = stack[top];
      top--;
      return temp;
    }catch (Exception e){
      e.printStackTrace();
      return -Integer.MAX_VALUE;
    }
  }
  
  
  static void push(double dub){
    top++;
    stack[top] = dub;
  }
}
