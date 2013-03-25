// $Id: queue.java,v 1.2 2012-10-31 17:11:14-07 - - $

import java.util.Iterator;
import java.util.NoSuchElementException;

//
// Linked implementation of a generic queue with iteration.
//

class queue<item_t> implements Iterable<item_t> {
   private node head = null;
   private node tail = null;

   private class node {
      item_t item;
      node link = null;
      node (item_t item_) { item = item_; }
   }

   public boolean isempty () {
      return head == null;
   }

   public void insert (item_t item) {
      node tmp = new node (item);
      if (tail == null) head = tmp;
                   else tail.link = tmp;
      tail = tmp;
   }

   public item_t remove() {
      if (isempty()) throw new NoSuchElementException();
      item_t result = head.item;
      head = head.link;
      if (head == null) tail = null;
      return result;
   }

   public Iterator<item_t> iterator() {
      return new iterator();
   }

   protected class iterator implements Iterator<item_t> {
      node nextnode = head;

      public boolean hasNext() {
         return nextnode != null;
      }

      public item_t next() {
         if (nextnode == null) throw new NoSuchElementException();
         item_t nextitem = nextnode.item;
         nextnode = nextnode.link;
         return nextitem;
      }

      public void remove() {
         throw new UnsupportedOperationException();
      }
   }

}
