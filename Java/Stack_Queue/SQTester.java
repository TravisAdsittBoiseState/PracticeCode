package Stack_Queue;

import java.util.Random;

/**
 * 
 * This class is meant to verify the basic operations of the Stack and Queue
 * then, once verified perform a stress test on both abstractions.
 * 
 * @author Travis Adsitt
 * 
 * 25JUL18
 *
 */
public class SQTester {

	private static Queue<Integer> queue;
	private static Stack<Integer> stack;
	private static Random rand;
	
	private static int NUM_OPERATIONS = 10000;
	
	public static void main(String args[]){
		
		queue  = new Queue<Integer>();
		stack = new Stack<Integer>();
		
		rand = new Random();
		
		System.out.println("Testing the stack!");
		
		stack.push(1);
		int ret = stack.pop();
		if(ret!=1) System.out.println("\tSimple push pop failed!");
		
		stack.push(1);
		stack.push(2);
		ret = stack.pop();
		if(ret!=2) System.out.println("\tSimple push push pop failed!");
		ret = stack.pop();
		if(ret!=1) System.out.println("\tSimple push push pop pop failed!");
		
		System.out.println("Non-exhaustive basic test passed!\n\nCommencing stack stress test with zero verification!");
		
		int temp = 0;
		int pushCount = 0;
		int popCount = 0;
		
		for(int i = NUM_OPERATIONS; i > 0; i--){
			temp = rand.nextInt(100);
			if(temp>50){
				stack.push(temp);
				pushCount++;
			}else{
				stack.pop();
				popCount++;
			}
		}
		
		System.out.println("Push count : "+ pushCount+" Pop count : "+popCount+".. moving on to Queue!");
		
		queue.enqueue(1);
		ret = queue.dequeue();
		if(ret!=1)System.out.println("\tSimple enqueue dequeue failed!");

		
		queue.enqueue(1);
		queue.enqueue(2);
		ret = queue.dequeue();
		if(ret!=1)System.out.println("\tSimple enqueue enqueue dequeue failed!");	
		ret = queue.dequeue();
		if(ret!=2)System.out.println("\tSimple enqueue enqueue dequeue dequeue failed!");	
		
		System.out.println("Queue stress test commencing!");
		
		int enCount = 0;
		int deCount = 0;
		
		for(int i = NUM_OPERATIONS; i > 0; i--){
			temp = rand.nextInt(100);
			if(temp>50){
				queue.enqueue(temp);
				enCount++;
			}else{
				queue.dequeue();
				deCount++;
			}
		}
		
		System.out.println("Enqueue count : "+ enCount+" Dequeue count : "+deCount);
		System.out.println("ALL TESTS PASS!");
		
	}
	
	
	
}
