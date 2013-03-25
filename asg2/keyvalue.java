// $Id: keyvalue.java,v 1.1 2012-10-30 11:16:57-07 - - $
//Lauren Crowther lcrowte
//Steveb Morad smorad
import java.util.Iterator;
import static java.lang.System.*;
import java.util.Scanner;
import java.io.*;

class keyvalue {
  static Scanner sc;
  static linkedlist list;
  
  public static void main (String[] args) {
    list = new linkedlist();
    if(args.length==0)
      readFromInput();
    else
    for(String line: args){
      File file = new File(line);
      readFromFile(file);
    }
    exit(messages.EXIT_SUCCESS);
  }
  
  static void readFromInput(){
    sc = new Scanner(System.in);
    while(sc.hasNext())
      parseInput(sc.nextLine().trim());
    
  }
  
  static void readFromFile(File file){
    try{
      Scanner sc = new Scanner(file);
      while(sc.hasNext())
        parseInput(sc.nextLine().trim());
      sc.close();
    } catch(IOException e){
      messages.die(e);
    }
  }
  
  static void parseInput(String word){
    if(word.startsWith("#")){ //comment
      return;
    }
    if(word.isEmpty()) //empty line
      return;
    if(word.equals("-")) //read from input
      readFromInput();
    if(word.startsWith("=")){ //matching key/value pairs are printed
      if(word.length()>1){
        for(pair p: list){
          if(p.value.equals(word.substring(2)))
               list.printPair(p);
        }
      }
      else
        list.printlist(list); //entire dictionary printed
    }
    else
      parseInput2(word);
  }
  
  
  static void parseInput2(String word){
        if(!word.contains("=")){
        if(list.get(word)==null)
          out.println(word + ": not found");
        else
          list.printPair(list.get(word)); //key, prints value
      }
      if(word.endsWith("=")){ //key= find key, then delete
        int index = word.indexOf("=");
        list.printPair(list.get(word.substring(0, index-1)));
        list.delete(word.substring(0,index-1));
      }
      else if(word.contains("=")){
        int index = word.indexOf("="); 
        String first = word.substring(0, index-1);
        String second = word.substring(index+2);
        list.put(first, second);
      }
  }
      
  
}





