/* Steven Morad and Lauren Crowther
 * smorad@ucsc.edu lcrowthe@ucsc.edu
 */

import java.io.*;
import java.util.Scanner;
import java.util.regex.*;
import static java.lang.System.*;
public class jgrep{
  public static boolean optionsPresent;
  
  static void scanfile(Scanner input, String filename, Pattern pattern){
    int numLines = 1;
    while (input.hasNextLine()) {
      String line = input.nextLine();
      boolean matches = pattern.matcher(line).find();
      if (matches && !options.reverse_match) {
        messages.exit_status = messages.EXIT_SUCCESS;
        if(options.filename_only){
          out.printf(filename + "\n");
          return;
        }
        else if(options.number_lines){
          out.printf(numLines + ": " + "%s:%s%n", filename, line);
        }
        else{
          out.printf("%s:%s%n", filename, line);
        }
      }
      else if(!matches && options.reverse_match){
        if(options.number_lines){
          out.printf(numLines + ": " + "%s:%s%n", filename, line);
        } 
        else {
          out.printf("%s:%s%n", filename, line);
        }
        messages.exit_status = messages.EXIT_SUCCESS;
      }
      numLines++;
    }
  }
  
  public static void main(String[] args) {
    checkSyntax(args);
    if(optionsPresent)
      setOptions(args);
    compileRegex(args);
    parseFiles(args);
    searchFiles();
    exit(messages.exit_status);
  }
  
  static void checkSyntax(String[] args){
    if (args.length == 0) {
      err.printf("Usage: %s [-ilnv] regex [filename...]%n",
                 messages.program_name);
      exit(messages.exit_status = messages.EXIT_FAILURE);
    }
    if(args[0].startsWith("-"))
      optionsPresent=true;
  }
  
  static void setOptions(String[] args){
    for(int pos=0; pos<args[0].length(); pos++){
      switch(args[0].charAt(pos)){
        case '-':;
        break;
        case ' ':;
        break;
        case 'i': options.insensitive=true;
        break;
        case 'l': options.filename_only=true;
        break;
        case 'n': options.number_lines=true;
        break;
        case 'v': options.reverse_match=true;
        break;
        default:       
          err.printf("Usage: %s [-ilnv] regex [filename...]%n",
                     messages.program_name);
          messages.die();
      }
    }
  }
  
  static void compileRegex(String[] args){
    int i;
    if(optionsPresent){
      i = 1;
    }
    else {
      i = 0;
    }
    options.regex = args[i];
    try{
      if (options.insensitive) {
        options.pattern = Pattern.compile(options.regex, 
                                          Pattern.CASE_INSENSITIVE);
      } else {
        options.pattern = Pattern.compile(options.regex);
      }
    } catch (PatternSyntaxException e){
      messages.die(e.getMessage());  
    }
  }
  
  static void parseFiles(String[] args){
    int offset;
    if(optionsPresent)
      offset = 2;
    else
      offset = 1;
    options.filenames = new String[args.length-offset];
    for(int i=0; i<args.length-offset; i++){
      options.filenames[i] = args[i+offset];
    }
  }
  
  static void searchFiles(){
    try{
      for(int i = 0; i<options.filenames.length; i++){
        Scanner input = new Scanner(new File(options.filenames[i]));
        scanfile(input, options.filenames[i], options.pattern);
        input.close();
      }
    } catch (IOException e){
      messages.warn(e.getMessage());
      messages.exit_status = messages.EXIT_NOMATCH;
    } 
  }
}

