// $Id: options.java,v 1.1 2012-11-24 10:05:24-08 - - $

class options {
  boolean count_only = false;
  boolean dump_tree = false;
  boolean fold_cases = false;
  String[] filenames = null;
  
  options (String[] args) {
    int pos = 0;
    if(args[0].startsWith("-")){
         readOpts(args[0]);
         pos = 1;
         filenames = new String[args.length-1];
    }
    else
      filenames = new String[args.length];
    for(int argi = 0; pos<args.length; pos++){
      filenames[argi] = args[pos];
      argi++;
    }
    if(filenames.length == 0)
      filenames = new String[]{"-"};
  }
  
  void readOpts(String opts){
    for(int argi = 0; argi<opts.length(); argi++){
      switch(opts.charAt(argi)){
        case 'c': count_only = true;
        break;
        case 'd': dump_tree = true;
        break;
        case 'f': fold_cases = true;
        break;
        case '-': break;
        default:
          System.out.println("Invalid option");
          messages.die();        
      }
    }
  }
  
}
