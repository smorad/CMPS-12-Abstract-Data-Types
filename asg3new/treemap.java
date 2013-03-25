// $Id: treemap.java,v 1.1 2012-11-24 10:05:24-08 - - $

import java.io.*;
import static java.lang.System.*;

class treemap <key_t extends Comparable<key_t>, value_t> implements
 visitor<key_t, value_t> {
  
  private class bstree {
    //bstree(){}
    bstree(key_t key, value_t value){
      this.key = key;
      this.value = value;
    }
    key_t key;
    value_t value;
    bstree left;
    bstree right;
  }
  private bstree root = null;
  
  public value_t put (key_t key, value_t value) {
    bstree leaf = new bstree(key, value);
    bstree curr = root;
    bstree parent = null;
    boolean wentLeft = false;
    while(curr!=null){
      int cmp = curr.key.compareTo(key);
      if(cmp==0){
        value_t temp = curr.value;
        curr.value = value;
        return temp;
      }
      parent = curr;
      if(cmp > 0){
        curr=curr.left;
        wentLeft = true;
      }
      else{
        curr=curr.right;
        wentLeft = false;      
      }
    }
    if(root==null){
      root=leaf;
      return null;
    }
    if(wentLeft){
      parent.left = leaf;
      return null;
    }
    else{
      parent.right = leaf;
      return null;
    }
  }
  
  public value_t get (key_t key) { 
    bstree curr = root;
    while(curr!=null){
      int cmp = curr.key.compareTo(key);
      if(cmp==0)
        return curr.value;
      if(cmp<0)
        curr=curr.right;
      if(cmp>0)
        curr=curr.left;
    }
    return null;
  }
  
  public value_t remove (key_t key) {
    throw new UnsupportedOperationException ();
  }
  
  public void visit_all (visitor <key_t, value_t> visitor_fn) {
    visit_all_inorder (root, visitor_fn);
  }
  
  private void visit_all_inorder (bstree tree,
                                  visitor <key_t, value_t> visitor_fn) {
    if(tree==null)
      return;
    visit_all_inorder(tree.left, visitor_fn);
    visitor_fn.visit (tree.key, tree.value); //visit
    visit_all_inorder(tree.right, visitor_fn);
  }
  
  public void visit (key_t key, value_t value){
    out.println(key + ": " + value); 
  }
  
  public void debug_dump () {
    debug_dump_inorder (root, 0);
  }
  
  private void debug_dump_inorder (bstree tree, int depth) {
    if (tree == null) return;
    debug_dump_inorder (tree.left, depth + 1);
    String sfmt = "%" + (depth > 0 ? depth * 3 : "") + "s";
    out.printf (sfmt + "%d: %s => %s%n",
                "", depth, tree.key, tree.value);
    debug_dump_inorder (tree.right, depth + 1);
  }
  
}

