package Stack_Queue;

import LinkedLists.SLL;

/**
 * This is a quick stack implementation using the Single Link List developed
 * and retained in the LinkedLists package.
 * 
 * @author Travis Adsitt
 *
 * 25JUL18
 *
 */
public class Stack<T> {
	
	private int depth;
	private SLL<T> stack;
	
	public Stack(){
		depth = 0;
		stack = new SLL<T>();
		
	}
	
	/**
	 * 
	 * Method to push something onto the stack.
	 * 
	 * @param item
	 */
	public void push(T item){
		stack.addToFront(item);
		depth++;
	}
	
	/**
	 * 
	 * Method to pop something off of the stack.
	 * 
	 * @return T item
	 */
	public T pop(){
		T retVal = stack.removeFirst();
		if(retVal != null) depth--;
		return retVal;
	}
	
	
	
}
