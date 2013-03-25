// $Id: linkedlist.java,v 1.1 2012-10-18 13:19:38-07 - - $
//Lauren Crowther lcrowthe
//Steven Morad smorad

import java.util.Iterator;
import java.util.NoSuchElementException;

class linkedlist implements Iterable<pair> {

   void printlist(linkedlist list){
     for(pair curr: list)
       printPair(curr);
  }
   
   void printPair(pair curr){
     if(curr!=null && curr.key!=null){
     System.out.println(curr.key + ": " + curr.value);
     }
     else{
       System.out.println("Key not found");
     }
   }
  private class node {
    pair item;
    node link;
  }
  private node head = null;
  
  public pair get (String key) {
    for(pair curr: this){
      if(curr.key.equals(key)){
        return curr;
      }
    }
    return null;
  }
  
    public pair getValue (String value) {
    for(pair curr: this){
      if(curr.value.equals(value)){
        //getValue(value);
        return curr;
      }
    }
    return null;
  }
    
  
  public String put(String key, String value){
    node n = new node();
    pair p = new pair(key,value);
    n.item=p;
    node prev = null;
    node curr = head;
    int cmp = 1;
    while(curr!=null){
      cmp = curr.item.key.compareTo(key);
      if(cmp>=0) break;
      prev=curr;
      curr=curr.link;
  }
    if(cmp!=0){
      n.link = curr;
      if(prev==null) 
        head=n;
      else
        prev.link=n;
    }
    if(cmp==0){
      curr.item.value=value;
    }
    return n.item.value;
    
  }
    
    public String delete (String key) {
      node curr = head;
      node prev = null;
      while(curr!=null){
        if(curr.item.key.equals(key)){
          if(prev==null)
            head=head.link;
          else{
          prev.link = curr.link;
          return curr.item.value;
          }
      }
        prev = curr;
        curr =curr.link;
           }
      
      return key+": not found";
    }
  
    public Iterator<pair> iterator () {
      return new itor ();
    }
    
    private class itor implements Iterator<pair> {
      private node nextnode = head;
      
      public boolean hasNext () {
        return nextnode != null;
      }
      
      public pair next () {
        if (! hasNext()) throw new NoSuchElementException ();
        pair result = nextnode.item;
        nextnode = nextnode.link;
        return result;
      }
      
      public void remove () {
        throw new UnsupportedOperationException ();
      }
    }
  }
