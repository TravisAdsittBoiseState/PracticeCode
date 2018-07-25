package LinkedLists;

/**
 * 
 * I want to add an iterator to this, but for now this is just a simple PoC 
 * Single Linked List written in Java. 
 * 
 * 24JUL18
 * 
 * @author Travis Adsitt
 *
 * @param <T> - Data Type
 */

public class SLL<T> {

	private SLLNode<T> head;
	public int length;
	
	/**
	 * Creates an empty Single Linked List.
	 * 
	 */
	public SLL(){
		head = null;
		length = 0;
	}
	
	/**
	 * Adds a value to the front of the list.
	 * 
	 * @param value
	 */
	public void addToFront(T value){
		SLLNode<T> newHead = new SLLNode<T>(value);
		
		if(head == null){
			head = newHead;
		}else{
			newHead.next = head;
			head = newHead;
		}
		
		length++;
		
	}
	
	/**
	 * Adds an element to the end of the list.
	 * 
	 * @param value
	 */
	@SuppressWarnings("unchecked")
	public void addToRear(T value){
		SLLNode<T> currNode = head;
		SLLNode<T> newTail = new SLLNode<T>(value);
		
		if(currNode == null){
			head = newTail;
		}else{
			while(currNode.next != null){
				currNode = currNode.next;
			}

			currNode.next = newTail;
		}

		length++;
		
	}
	
	/**
	 * Removes the first element of the list and returns the key.
	 * 
	 * @return
	 */
	@SuppressWarnings("unchecked")
	public T removeFirst(){
		SLLNode<T> retVal = head;
		
		if(head != null){
			head = head.next;
			length--;
		}
		
		
		
		return retVal == null?null:retVal.key;
	}
	
	/**
	 * Removes the last element of the list and returns its key, I don't like the use of multiple
	 * return statements but it saves running time in the corner cases as well
	 * as prevents uncaught exceptions.
	 * 
	 * @return Last Node in the List
	 */
	@SuppressWarnings("unchecked")
	public T removeLast(){
		
		if(head == null){
			return null;
		}else if(head.next == null){
			SLLNode<T> retVal = head;
			
			head = null;
			
			length--;
			
			return retVal.key;
		}
	
		SLLNode<T> prevNode = head;
		SLLNode<T> currNode = head.next;
		
		while(currNode.next != null){
			prevNode = currNode;
			currNode = currNode.next;
		}
		
		length--;
		
		prevNode.next = null;
		
		return currNode.key;
		
	}
	
	public String toString(){
		StringBuilder retStr = new StringBuilder();
		String retVal = "";
		retStr.append("[");
		
		if(head == null){
			retVal = retStr.toString() + "]";
		}else{
			
			SLLNode<T> currNode = head;
			
			while(currNode != null){
				retStr.append(currNode.key + ",");
				currNode = currNode.next;
			}
			
			retVal = retStr.substring(0, retStr.length() - 1) + "]";
			
		}
		
		
		return retVal;
	}
	
	/**
	 * Single Linked List Node object
	 * 
	 * @author Travis Adsitt
	 *
	 * 24JUL18
	 *
	 * @param <T> - Data Type
	 */
	class SLLNode<T> {
		
		public T key;
		public SLLNode next;
		
		public SLLNode(T value){
			key = value;
			next = null;
		}
		
		public SLLNode(T value, SLLNode next){
			key = value;
			this.next = next;
		}
	}
}
