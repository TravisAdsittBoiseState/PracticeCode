package Stack_Queue;

import LinkedLists.SLL;

/**
 * 
 * This is a simple queue implementation using the Single Linked List
 * implementation located in the LinkedLists package.
 * 
 * @author Travis Adsitt
 * 
 * 
 * 25JUL18
 * 
 *
 */
public class Queue<T> {

	private int length;
	private SLL<T> queue;
	
	public Queue(){
		length = 0;
		queue = new SLL<T>();
	}
	
	/**
	 * 
	 * A method to enqueue an item
	 * 
	 * @param item
	 */
	public void enqueue(T item){
		queue.addToRear(item);
		length++;
	}
	
	/**
	 * 
	 * A method to dequeue and item
	 * 
	 * @return T item
	 */
	public T dequeue(){
		T retVal = queue.removeFirst();
		if(retVal!=null)length--;
		return retVal;
	}
	
}
