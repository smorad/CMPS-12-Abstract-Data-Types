// $Id: counted_queue.java,v 1.2 2012-10-31 17:12:51-07 - - $

class counted_queue<item_t> extends queue<item_t>
                            implements Iterable<item_t> {
   private int count = 0;

   public void insert (item_t item) {
      super.insert (item);
      ++count;
   }

   public item_t remove() {
      item_t result = super.remove();
      --count;
      return result;
   }

   public int count() {
      return count;
   }

   public String toString() {
      return "[" + count + ", " + super.toString() + "]";
   }

}
